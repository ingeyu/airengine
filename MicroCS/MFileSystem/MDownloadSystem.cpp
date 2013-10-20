#include "MDownloadSystem.h"
#include "MFileSystem.h"
#include "MFile.h"
#include "MIOSystem.h"



MDownloadSystem::MDownloadSystem()
{
	m_pClient	=	NULL;
	m_pBackDownloadFile	=	NULL;
	m_pDownloadingFile	=	NULL;
}

MDownloadSystem::~MDownloadSystem()
{
	m_pClient			=	NULL;
	m_pDownloadingFile	=	NULL;
	m_pBackDownloadFile	=	NULL;
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
			NT_FS_FileData* pFileData	=	(NT_FS_FileData*)pHeader;
			m_pDownloadingFile->OnDownloading(pFileData->uiOffset,pFileData->data,pFileData->uiSize);
			if(pFileData->uiComplated){
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

void MDownloadSystem::Update( const float fTimeDelta )
{
	if(!m_pClient->IsConnected()){
		Air::Common::NetClient::Info info;
		info.strIP		=	"127.0.0.1";
		info.usPort		=	54322;
		info.pListener	=	this;
		if(!m_pClient->Connect(info)){
			return;
		}
	}

	if(m_pDownloadingFile!=NULL){
		return;
	}

	//check high prority list
	m_CS.Enter();
	STD_LIST<MFile*>::iterator	i	=	m_lstFile.begin();
	if(i!=m_lstFile.end()){
		m_pDownloadingFile	=	*i;
		m_lstFile.erase(i);
	}
	m_CS.Leave();
	//check bakcground low prority list
	if(m_pDownloadingFile==NULL){
		U32	uiCount	=	MFileSystem::GetSingleton()->GetFileCount();
		FileInfo* pDownload	=	NULL;
		for(;m_uiCurrent<uiCount;m_uiCurrent++){
			pDownload	=	&MFileSystem::GetSingleton()->GetFileInfo(m_uiCurrent);;
			if(pDownload->idx&0xffff0000==0){
				//m_uiCurrent++;
				break;
			}else{
				pDownload=NULL;
			}
		}
		if(pDownload!=NULL){
			m_pBackDownloadFile	=	MFileSystem::GetSingleton()->CreateMFile(pDownload->fileid);
			m_pDownloadingFile	=	m_pBackDownloadFile;
		}
	}
	//if has task,send request
	if(m_pDownloadingFile!=NULL){
		NT_Data<FileDataInfo> data(enNT_FS_LoadFile);
		data.t		=	enNT_FS_LoadFile;
		data.data.idx		=	m_pDownloadingFile->GetFileID();
		data.data.uiOffset	=	0;
		data.data.uiSize	=	m_pDownloadingFile->GetFileInfo().compressize;
		m_pClient->Send(&data,sizeof(data));
	}
}

void MDownloadSystem::OnDownloadComplated( MFile* pFile,U1 bOK )
{
	pFile->OnDownloadComplated(bOK);
	if(m_pBackDownloadFile==pFile){
		U32 ret	=	1;
		if(!bOK)
			ret = 0xffffffff;
		FileInfo& info = MFileSystem::GetSingleton()->GetFileInfo(m_uiCurrent);;
		info.idx	|=	ret<<16;
		m_pBackDownloadFile	=	NULL;
		m_uiCurrent++;
	}
	if(bOK){
		pFile->OnDownloadComplated(true);
		MIOSystem::GetSingleton()->SaveFileBackground(pFile);
	}else{
		SAFE_RELEASE_REF(pFile);
	}
	
}
