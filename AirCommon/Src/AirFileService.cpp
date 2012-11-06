#include "AirFileService.h"

#define DEFAULT_SHARE_MEMORY_SIZE	24*1024*1024

namespace	Air{


	FileServer::FileServer()
	{
		m_pConnect	=	NULL;
		m_bExit		=	false;
	}

	FileServer::~FileServer()
	{

	}

	Air::U1 FileServer::OnConnected( U32 socket,AString& strIP,AString& strPort )
	{
		OutputDebugStringA("Client Connected!\n");
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

		if(m_mapClientInfo.empty()){
			m_bExit	=	true;
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
		OutputDebugStringA("Create FileMapping!");

		NetCommand<NCT_SC_Return>	r(enNCT_SC_Return);
		r.data.uiReturnValue	=	0;
		r.data.uiUserData		=	0;
		r.data.type				=	p->type;

		ClientInfoMap::iterator	i	=	m_mapClientInfo.find(uiSocket);
		if(i!=m_mapClientInfo.end()){
			ClientInfo& info	=	i->second;
			char strTempName[256];
			sprintf_s(strTempName,256,"%s_%d",p->data.strName,p->data.ProcessId);
			FileMapping::Info finfo;
			finfo.type			=	FileMapping::enFMT_Create;
			finfo.uiFileSize	=	DEFAULT_SHARE_MEMORY_SIZE;
			info.m_pFile	=	AirNew< FileMapping>(strTempName,&finfo);
			info.m_pFile->AddRef();
			r.data.uiReturnValue	=	1;

			if(info.m_pFile==NULL){
				OutputDebugStringA("Error!\n");
			}else{
				OutputDebugStringA("OK!\n");
			}
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

		ClientInfoMap::iterator	i	=	m_mapClientInfo.find(uiSocket);
		if(i!=m_mapClientInfo.end()){
			ClientInfo& info	=	i->second;
			void*	pData	=	info.m_pFile->GetLockedBuffer();
			r.data.uiReturnValue	=	LoadFile(p->data.strFileName,pData,r.data.uiUserData);

			r.data.type				=	enNCT_SC_LoadFileComplate;
			SendCommand(uiSocket,r);
		}
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
		m_pConnect	=	AirNew< Common::NetServer>("ResourceServer",&sinfo);
		m_pConnect->AddRef();

		while(!m_bExit){
			Sleep(1000);
		}

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
		HANDLE	h	=	CreateFileA(strName.c_str(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
		if(h==INVALID_HANDLE_VALUE){
			return false;
		}
		uiSize	=	GetFileSize(h,0);
		DWORD dwRSize=0;
		//static char str[16*1024];
		ReadFile(h,pData,uiSize,&dwRSize,0);
		//ReadFile(h,str,uiSize,&dwRSize,0);
		//memcpy(pData,str,uiSize);
		CloseHandle(h);
		return true;
	}


	FileClient::FileClient(CAString& strName):m_strName(strName)
	{
		m_pConnect	=	NULL;
		m_pFile		=	NULL;
		char str[256];
		sprintf_s(str,256,"%s_%d",strName.c_str(),GetCurrentProcessId());
		m_strFileMappingName	=	str;
		m_pCurrentCallback		=	NULL;
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
		m_pConnect		=	AirNew< Common::NetClient>("ResourceClient",&info);
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
		strcpy_s(r.data.strName,32,m_strName.c_str());
		m_pConnect->Send(&r,sizeof(r));

		return true;
	}

	Air::U1 FileClient::OnClose( U32 uiSocket )
	{
		OutputDebugStringA("Server Exit!\n");
		return true;
	}

	Air::U1 FileClient::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
	{
		NetBaseCommand* pBase	=	(NetBaseCommand*)pData;
		switch(pBase->type){
			case	enNCT_SC_Return:{
				OnReturn((NetCommand<NCT_SC_Return>*)pBase);
									}break;
		}
		return true;
	}

	void FileClient::OnLoadFileComplate(U32 uiFileSize)
	{
		void*	pData	=	m_pFile->GetLockedBuffer();
		//Callback
		if(m_pCurrentCallback!=NULL)
			m_pCurrentCallback->OnLoadComplate(m_strCurrentName,pData,uiFileSize);

		m_pCurrentCallback	=	NULL;
	}

	void FileClient::OnReturn( NetCommand<NCT_SC_Return>* p )
	{
		switch(p->data.type){
			case enNCT_CS_CreateMappingFile:{
				FileMapping::Info info;
				info.type		=	FileMapping::enFMT_Open;
				info.uiFileSize	=	DEFAULT_SHARE_MEMORY_SIZE;
				m_pFile	=	AirNew<FileMapping>(m_strFileMappingName,&info);
				m_pFile->AddRef();
				
											}break;
			case enNCT_CS_RequestLoadFile:{

										  }break;
			case enNCT_SC_LoadFileComplate:{
				OnLoadFileComplate(p->data.uiUserData);
										   }break;
			case enNCT_CS_RequestUnloadFile:{

											}break;
		}
	}

	Air::U1 FileClient::RequestFile( CAString& strName,LoadFileCallback* pCB )
	{
		if(m_pCurrentCallback==NULL){
			strcpy_s(m_strCurrentName,256,strName.c_str());
			m_pCurrentCallback	=	pCB;

			NetCommand<NCT_CS_RequestLoadFile>	r(enNCT_CS_RequestLoadFile);
			strcpy_s(r.data.strFileName,256,strName.c_str());

			m_pConnect->Send(&r,sizeof(r));
		}else{
			LoadFileRequest req;
			req.strFileName	=	strName;
			req.pCB			=	pCB;
			m_lstRequest.push_back(req);
		}
		return true;
	}

}