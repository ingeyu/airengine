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
			if(pRet->ret!=NET_VERSION){
				OutputDebugString(_T("Server/Client Version Isn't Matched! Disconnected!\n"));
				m_pClient->DisConnect();	
			}
					 }break;
		case enNT_FS_LoadFile:{
			if(pRet->ret==0){
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
		DownloadFile* pDownload	=	NULL;
		for(;m_uiCurrent<m_vecDownload.size();m_uiCurrent++){
			pDownload	=	&(m_vecDownload[m_uiCurrent]);
			if(pDownload->state==0){
				//m_uiCurrent++;
				break;
			}else{
				pDownload=NULL;
			}
		}
		char strName[MAX_PATH];
		sprintf_s(strName,"%016llx",pDownload->fileID);
		m_pBackDownloadFile	=	MFileSystem::GetSingleton()->CreateProduct<MFile>(strName,&pDownload->fileID);
		m_pDownloadingFile	=	m_pBackDownloadFile;
	}
	//if has task,send request
	if(m_pDownloadingFile!=NULL){
		NT_FS_LoadFile data;
		data.t		=	enNT_FS_LoadFile;
		data.id		=	m_pDownloadingFile->GetFileID();
		data.val	=	0;
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
		m_vecDownload[m_uiCurrent].state	=	ret;
		m_pBackDownloadFile	=	NULL;
		m_uiCurrent++;
	}
	if(bOK){
		pFile->OnDownloadComplated(true);
		MIOSystem::GetSingleton()->SaveFileBackground(pFile);
	}
	SAFE_RELEASE_REF(pFile);
}
