#include "MDownloadSystem.h"
#include "MFileSystem.h"
#include "MFile.h"
#include "MIOSystem.h"



MDownloadSystem::MDownloadSystem()
{
	m_pClient	=	NULL;
	m_pDownloadingFile	=	NULL;
	m_uiCurrent			=	0;
}

MDownloadSystem::~MDownloadSystem()
{
	m_pClient			=	NULL;
	m_pDownloadingFile	=	NULL;
}

U1 MDownloadSystem::Initialization()
{


	Air::Common::NetClient::Info info;
	info.pListener	=	this;
	info.strIP	=	"127.0.0.1";
	info.usPort	=	54322;
	m_pClient	=	MFileSystem::GetSingleton()->CreateProduct<Air::Common::NetClient>("MDS",&info);
	return true;
}

U1 MDownloadSystem::Release()
{
	SAFE_RELEASE_REF(m_pClient);
	SAFE_RELEASE_REF(m_pDownloadingFile);

	m_CS.Enter();
	STD_LIST<MFile*>::iterator	i	=	m_lstFile.begin();
	for(;i!=m_lstFile.end();i++){
		SAFE_RELEASE_REF((*i));
	}
	m_lstFile.clear();
	m_CS.Leave();
	return true;
}

U1 MDownloadSystem::OnConnected( U32 socket,CAString& strIP,CAString& strPort )
{
	return true;
}

U1 MDownloadSystem::OnClose( U32 uiSocket )
{
	return true;
}

U1 MDownloadSystem::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
{
	if(pData==NULL)
		return false;
	NetHeader* pHeader	=	(NetHeader*)pData;
	switch(pHeader->t){
		case enNT_Return:{
			return OnReturn((NT_Return*)pHeader);
					 }break;
		case enNT_SF_FileData:{
			NT_Data<NT_FS_FileData>* pFileData	=	(NT_Data<NT_FS_FileData>*)pHeader;
			NT_FS_FileData& data = pFileData->data;
			m_pDownloadingFile->OnDownloading(data.uiOffset,data.data,data.uiSize);
			if(data.uiComplated){
				OnDownloadComplated(m_pDownloadingFile,true);
			}
							  }break;
	}
	return true;
}

U1 MDownloadSystem::AddFile( MFile* pFile )
{
	pFile->AddRef();
	m_CS.Enter();
	m_lstFile.push_front(pFile);
	m_CS.Leave();
	return true;
}

U1 MDownloadSystem::OnReturn( NT_Return* pRet )
{
	switch(pRet->lastType){
		case enNT_FS_Hello:{
			NT_ReturnT<NT_SF_Hello>* pRetT	=	(NT_ReturnT<NT_SF_Hello>*)pRet;
			if(pRetT->retValue!=1){
				OutputDebugString(_T("Server/Client Version Isn't Matched! Disconnected!\n"));
				m_pClient->DisConnect();	
			}else{
				TCHAR strName[MAX_PATH];
				swprintf_s(strName,_T("%d %d\n"),pRetT->data.uiClient,pRetT->data.uiTaskCount);
				OutputDebugString(strName);

			}
					 }break;
		case enNT_FS_LoadFile:{
			if(pRet->retValue==0){
				OutputDebugString(_T("File isn't exist!\n"));
				OnDownloadComplated(m_pDownloadingFile,false);
			
			}
						   }break;
	}

	return false;
}



void MDownloadSystem::Update( U32 uiTickTime )
{
	if(!m_pClient->IsConnected()){
		Air::Common::NetClient::Info info;
		Air::Common::GetLocalIP(info.strIP);
		info.usPort		=	54322;
		info.pListener	=	this;
		if(!m_pClient->Connect(info)){
			return;
		}
	}

	if(m_pDownloadingFile!=NULL){
		return;
	}
	STD_LIST<MFile*> releaseFile;
	//check high prority list
	m_CS.Enter();
	STD_LIST<MFile*>::iterator	i	=	m_lstFile.begin();
	for(;i!=m_lstFile.end();){
		//file is already download!
		if(!(*i)->IsDownloading()){
			releaseFile.push_back(*i);//->ReleaseRef();
			i	=	m_lstFile.erase(i);
			continue;
		}else{
			m_pDownloadingFile	=	*i;
			m_lstFile.erase(i);
			break;
		}
	}
	m_CS.Leave();
	//Release File
	i	=	releaseFile.begin();
	for(;i!=releaseFile.end();i++){
		(*i)->ReleaseRef();
	}
	releaseFile.clear();

	//check bakcground low prority list
	if(m_pDownloadingFile==NULL){
		U32	uiCount	=	MFileSystem::GetSingleton()->GetFileCount();
		FileInfo* pDownload	=	NULL;
		for(;m_uiCurrent<uiCount;m_uiCurrent++){
			pDownload	=	&MFileSystem::GetSingleton()->GetFileInfo(m_uiCurrent);;
			if((pDownload->idx&0xffff0000)==0){
				//m_uiCurrent++;
				break;
			}else{
				pDownload=NULL;
			}
		}
		if(pDownload!=NULL){
			m_pDownloadingFile	=	MFileSystem::GetSingleton()->CreateMFile(pDownload->fileid);
		}
	}
	
	if(m_pDownloadingFile!=NULL){
		char str[256];
		sprintf_s(str,"%d Download Start\n",m_uiCurrent);
		OutputDebugStringA(str);

		NtPack<FileDataInfo> data(enNT_FS_LoadFile);
		data.t		=	enNT_FS_LoadFile;
		FileInfo& finfo		=	m_pDownloadingFile->GetFileInfo();
		data.data.idx		=	finfo.idx;
		data.data.uiOffset	=	finfo.offset;
		data.data.uiSize	=	finfo.compressize;
		m_pClient->Send(&data,data.uiSize+4);

	}
}

void MDownloadSystem::OnDownloadComplated( MFile* pFile,U1 bOK )
{
	if(pFile==NULL){
		return;
	}
	pFile->OnDownloadComplated(bOK);
	if(bOK){
		FileInfo* pBKInfo	=	&MFileSystem::GetSingleton()->GetFileInfo(m_uiCurrent);
		FileInfo* pInfo		=	&pFile->GetFileInfo();
		char str[256];
		sprintf_s(str,"%d Download Complated!\n",m_uiCurrent);
		OutputDebugStringA(str);

		if(pInfo==pBKInfo){
			m_uiCurrent++;
		}
		MIOSystem::GetSingleton()->SaveFileBackground(pFile);

	}else{
		SAFE_RELEASE_REF(pFile);
	}
	m_pDownloadingFile=NULL;

	MFileSystem::GetSingleton()->OnDownloadComplate();
}
