#include "MFileSystem.h"
#include "MDownloadSystem.h"
#include "MFile.h"
#include "MIOSystem.h"

MFileSystem::MFileSystem()
{
	m_pServer	=	NULL;
}

MFileSystem::~MFileSystem()
{

}

U1 MFileSystem::Initialization()
{
	AddFactory(new Air::ParamFactory<Air::FileMapping>());
	AddFactory(new Air::ParamFactory<Air::Common::NetServer>());
	AddFactory(new Air::ParamFactory<Air::Common::NetClient>());

	MIOSystem::GetSingleton()->Initialization();
	
	MDownloadSystem::GetSingleton()->Initialization();




	Air::Common::NetServer::Info info;
	info.usPort		=	54321;
	info.pListener	=	this;
	m_pServer	=	CreateProduct<Air::Common::NetServer>("MFS_Server",&info);

	
	return true;
}

U1 MFileSystem::Release()
{

	SAFE_RELEASE_REF(m_pServer);

	MDownloadSystem::GetSingleton()->Release();
	MDownloadSystem::ReleaseSingleton();

	MIOSystem::GetSingleton()->Release();
	MIOSystem::ReleaseSingleton();

	return true;
}

U1 MFileSystem::OnConnected( U32 socket,CAString& strIP,CAString& strPort )
{
	return true;
}

U1 MFileSystem::OnClose( U32 uiSocket )
{
	return true;
}

U1 MFileSystem::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
{
	return true;
}

MFile* MFileSystem::CreateFile( U64 id )
{
	char str[MAX_PATH];
	sprintf_s(str,"%016llx",id);
	return CreateProduct<MFile>(str,&id);
}

void MFileSystem::SendToClient( U32 uiSocket,const void* p,U32 uiSize )
{
	if(m_pServer!=NULL)
		m_pServer->Send(uiSocket,p,uiSize);

}

void MFileSystem::DisConnectClient( U32 uiSocket )
{
	if(m_pServer!=NULL)
		m_pServer->OnClose(uiSocket);
}
