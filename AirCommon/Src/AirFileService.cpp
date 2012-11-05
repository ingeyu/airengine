#include "AirFileService.h"

namespace	Air{


	FileServer::FileServer()
	{
		m_pConnect	=	NULL;
	}

	FileServer::~FileServer()
	{

	}

	Air::U1 FileServer::OnConnected( U32 socket,AString& strIP,AString& strPort )
	{
		ClientInfoMap::iterator	i	=	m_mapClientInfo.find(socket);
		if(i!=m_mapClientInfo.end()){
			ClientInfo& info	=	i->second;
			info.uiClientSocket	=	socket;
			info.strIP			=	strIP;
			info.strPort		=	strPort;
			if(info.m_pFile!=NULL){
				info.m_pFile->ReleaseRef();
				info.m_pFile	=	NULL;
			}
		}else{
			ClientInfo info;
			info.uiClientSocket	=	socket;
			info.strIP			=	strIP;
			info.strPort		=	strPort;
			info.m_pFile		=	NULL;
			m_mapClientInfo[socket]	=	info;
		}
		return true;
	}

	Air::U1 FileServer::OnClose( U32 uiSocket )
	{
		ClientInfoMap::iterator	i	=	m_mapClientInfo.find(uiSocket);
		if(i!=m_mapClientInfo.end()){
			ClientInfo& info	=	i->second;
			if(info.m_pFile!=NULL){
				info.m_pFile->ReleaseRef();
				info.m_pFile	=	NULL;
			}
			m_mapClientInfo.erase(i);
		}

		return true;
	}

	Air::U1 FileServer::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
	{
		if(pData==NULL||uiSize==0)
			return false;
		NetBaseCommand*	pBase	=	(NetBaseCommand*)pData;
		switch(pBase->type){
		case	enNCT_CS_CreateMappingFile:{
			OnCreateFileMapping(uiSocket,(NetCommand<NCT_CS_CreateMappingFile>*)pBase);
										   }break;
		case	enNCT_CS_RequestLoadFile:{
			OnRequestLoadFile(uiSocket,(NetCommand<NCT_CS_RequestLoadFile>*)pBase);
										 }break;
		case	enNCT_SC_LoadFileComplate:{

										  }break;
		case	enNCT_CS_RequestUnloadFile:{
			OnRequestUnLoadFile(uiSocket,(NetCommand<NCT_CS_Return>*)pBase);
										   }break;
		}
		return true;
	}

	void FileServer::OnCreateFileMapping( U32 uiSocket,NetCommand<NCT_CS_CreateMappingFile>* p )
	{
		NetCommand<NCT_SC_Return>	r(enNCT_SC_Return);
		r.data.uiReturnValue	=	0;
		r.data.uiUserData		=	0;
		r.data.type				=	p->type;

		ClientInfoMap::iterator	i	=	m_mapClientInfo.find(uiSocket);
		if(i!=m_mapClientInfo.end()){
			ClientInfo& info	=	i->second;
			char strTempName[256];
			sprintf(strTempName,"%s_%d",p->data.strName,p->data.ProcessId);
			FileMapping::Info finfo;
			finfo.type			=	FileMapping::enFMT_Create;
			finfo.uiFileSize	=	24*1024*1024;
			info.m_pFile	=	new FileMapping(strTempName,&finfo);
			info.m_pFile->AddRef();
			r.data.uiReturnValue	=	1;
		}

		SendCommand(uiSocket,r);
	}

	void FileServer::OnRequestLoadFile( U32 uiSocket,NetCommand<NCT_CS_RequestLoadFile>* p )
	{
		NetCommand<NCT_SC_Return>	r(enNCT_SC_Return);
		r.data.uiReturnValue	=	1;
		r.data.uiUserData		=	0;
		r.data.type				=	p->type;

		SendCommand(uiSocket,r);
	}

	void FileServer::OnRequestUnLoadFile( U32 uiSocket,NetCommand<NCT_CS_Return>* p )
	{
		NetCommand<NCT_SC_Return>	r(enNCT_SC_Return);
		r.data.uiReturnValue	=	1;
		r.data.uiUserData		=	0;
		r.data.type				=	p->type;

		SendCommand(uiSocket,r);
	}

	Air::U1 FileServer::Create()
	{
		Common::NetServer::Info sinfo;
		sinfo.pListener	=	this;
		sinfo.strPort	=	"60000";
		m_pConnect	=	new Common::NetServer("ResourceServer",&sinfo);
		m_pConnect->AddRef();

		

		return true;
	}

	Air::U1 FileServer::Destroy()
	{
		SAFE_RELEASE_REF(m_pConnect);
		return true;
	}

	Air::U1 FileServer::LoadFile( CAString& strName,void*& pData,U32& uiSize )
	{
		if(strName.empty())
			return false;
		HANDLE	h	=	CreateFileA(strName.c_str(),PAGE_READONLY,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
		if(h==INVALID_HANDLE_VALUE){
			return false;
		}
		GetFileSize(h,&uiSize);
		pData	=	__Alloc(uiSize);
		ReadFile(h,pData,0,&uiSize,0);
		CloseHandle(h);
		return true;
	}


	FileClient::FileClient(CAString& strName):m_strName(strName)
	{
		m_pConnect	=	NULL;
		m_pFile		=	NULL;
	}

	FileClient::~FileClient()
	{

	}

	Air::U1 FileClient::Create()
	{
		Common::NetClient::Info info;
		info.strIP		=	"127.0.0.1";
		info.strPort	=	"60000";
		info.pListener	=	this;
		m_pConnect		=	new Common::NetClient("ResourceClient",&info);
		m_pConnect->AddRef();

		if(!m_pConnect->Connect(info)){
			Destroy();
			return false;
		};
		return true;
	}

	Air::U1 FileClient::Destroy()
	{
		SAFE_RELEASE_REF(m_pConnect);
		SAFE_RELEASE_REF(m_pFile)
		return true;
	}

	Air::U1 FileClient::OnConnected( U32 socket,AString& strIP,AString& strPort )
	{
		NetCommand<NCT_CS_CreateMappingFile> r(enNCT_CS_CreateMappingFile);
		r.data.ProcessId	=	GetCurrentProcessId();
		strcpy(r.data.strName,m_strName.c_str());
		m_pConnect->Send(&r,sizeof(r));

		return true;
	}

	Air::U1 FileClient::OnClose( U32 uiSocket )
	{
		return true;
	}

	Air::U1 FileClient::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
	{
		NetBaseCommand* pBase	=	(NetBaseCommand*)pData;
		switch(pBase->type){
			case	enNCT_SC_LoadFileComplate:{
				OnLoadFileComplate();
											  }break;
			case	enNCT_SC_Return:{
				OnReturn((NetCommand<NCT_SC_Return>*)pBase);
									}break;
		}
		return true;
	}

	void FileClient::OnLoadFileComplate()
	{

	}

	void FileClient::OnReturn( NetCommand<NCT_SC_Return>* p )
	{

	}

}