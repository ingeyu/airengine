#include "MClient.h"
#include "MFileSystem.h"
#include "MFile.h"

struct CSInfo 
{
	U32	mark;
	U32	ret;
	U64	FileID;
	U32	uiOffset;
};

AString	MClient::ProductTypeName="MClient";
MClient::MClient( CAString& strName,Info* pInfo ):Air::Common::IProduct(strName)
{
	if(pInfo!=NULL)
		m_pSocket	=	*pInfo;
	m_pFile	=	NULL;

}

U1 MClient::Create()
{
	return	true;
}

U1 MClient::Destroy()
{

	SAFE_RELEASE_REF(m_pFile);
	return true;
}

U1 MClient::OnConnected( U32 socket,CAString& strIP,CAString& strPort )
{
	return true;
}

U1 MClient::OnClose( U32 uiSocket )
{
	return true;
}

U1 MClient::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
{
	NetHeader* pHeader	=	(NetHeader*)pData;
	switch(pHeader->t){
	case enNT_CF_Hello:{
		NT_CF_Hello* pHello = (NT_CF_Hello*)pHeader;
		if(pHello->Version!=NET_VERSION){
			MFileSystem::GetSingleton()->DisConnectClient(m_pSocket);
			ReleaseRef();
			return false;
		}

		char strName[MAX_PATH];
		sprintf_s(strName,"FileSystem%d",pHello->PID);
		Air::FileMapping::Info info;
		info.type		=	Air::FileMapping::enFMT_Open;
		info.uiFileSize	=	pHello->BufferSize;
		m_pFile	=	MFileSystem::GetSingleton()->CreateProduct<Air::FileMapping>(strName,&info);
		

		NT_ReturnT<NT_CF_Hello>	data;
		data.t	=	enNT_Return;
		data.lastType	=	pHeader->t;
		data.ret		=	NET_VERSION;
		data.last		=	*pHello;
		MFileSystem::GetSingleton()->SendToClient(uiSocket,&data,sizeof(data));
					   }break;
	case enNT_CF_LoadFile:{
		NT_CF_LoadFile* pLoadFile = (NT_CF_LoadFile*)pLoadFile;
		LoadFile(pLoadFile->id);
						  }break;
	}
	return true;
}

void MClient::OnFileLoadComplated( U32 uiOffset,MFile* pFile )
{
	CSInfo*	pInfo		=	(CSInfo*)m_pFile->GetLockedBuffer();

	U8*	pBuffer			=	(U8*)(++pInfo);
	
	pFile->GetData(pBuffer,0xffffffff);
	pInfo->ret		=	1;
	pInfo->mark		=	0xFFFFFFFF;
}

void MClient::OnFileLoadFailed( U32 uiOffset,MFile* pFile )
{
	CSInfo*	pInfo		=	(CSInfo*)m_pFile->GetLockedBuffer();
	pInfo->ret		=	0;
	pInfo->mark		=	0xFFFFFFFF;
}

void MClient::Update( float fTimeDelta )
{
	m_FSWaitClient.Wait();
	CSInfo*	pInfo		=	(CSInfo*)m_pFile->GetLockedBuffer();
	if(pInfo->mark==1){
		LoadFile(pInfo->FileID);
	}
}

void MClient::LoadFile( U64 fileID )
{
	char strName[MAX_PATH];
	sprintf_s(strName,"%016llx",fileID);
	MFile*	pFile	=	MFileSystem::GetSingleton()->CreateProduct<MFile>(strName,&fileID);
	if(pFile!=NULL){
		NotifyInfo info;
		info.pClient	=	this;
		info.uiOffset	=	0;
		pFile->AddNotify(info);
		pFile->ReleaseRef();
	}
}
