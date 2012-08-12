#include "AirCommonProfile.h"
#include "AirCommonNetServer.h"
#include "AirCommonNetClient.h"
#include "AirCommonStreamIO.h"

namespace	Air{

	AString	ProfileManager::m_strProfilePort	=	"9205";

	class	ServerCB	:	public	Common::NetListener{
	public:
		virtual	U1	OnConnected(U32	socket,AString&	strIP,AString&	strPort){

			ProfileManager*	pMgr	=	ProfileManager::GetSingleton();
			U32	uiSize	=	4+4;
			for(U32 i=0;i<256;i++){
				uiSize+=4;
				uiSize+=pMgr->m_ProfileName[i].size();
			}
			Common::MemoryWriter	writer(uiSize);
			
			U32	uiType	=	0;
			writer.Write(uiType);
			uiType		=	256;
			writer.Write(uiType);
			for(U32 i=0;i<256;i++){
				writer.WriteString(pMgr->m_ProfileName[i]);
			}
			pMgr->m_pServer->Send(socket,writer.GetDataPtr(),writer.GetDataSize());

			return	true;
		};
		virtual	U1	OnClose(U32	uiSocket){

			return	true;
		};
		virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize){
			return	true;
		};

	};

	ServerCB	g_ServerCB;
	class	ClientCB	:	public	Common::NetListener{
	public:
		virtual	U1	OnConnected(U32	socket,AString&	strIP,AString&	strPort){
			return	true;
		};
		virtual	U1	OnClose(U32	uiSocket){

			return	true;
		};
		virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize){
			U32	uiType	=	0;
			Common::StreamReader	reader(pData,uiSize);
			reader.Read(uiType);
			switch(uiType){
				case	0:{
					ProfileMonitor::GetSingleton()->OnRecvProfileName(uiSocket,reader);
// 					U32	uiCount	=	0;
// 					reader.Read(uiCount);
// 
// 					ProfileMonitor::ClientInfo*	pInfo	=	NULL;
// 					std::map<AString,ProfileMonitor::ClientInfo*>&	mapClient	=	ProfileMonitor::GetSingleton()->m_mapClient;
// 					std::map<AString,ProfileMonitor::ClientInfo*>::iterator	itr	=	mapClient.begin();
// 					for(;itr!=mapClient.end();itr++){
// 						pInfo	=	itr->second;
// 						Common::NetClient*	pClient	=	pInfo->m_pClient;
// 						if(pClient!=NULL){
// 							if(pClient->GetSocket()	==	uiSocket){
// 								break;
// 							}
// 						}
// 					}
// 					if(pInfo!=NULL){
// 						for(U32	i=0;i<uiCount;i++){
// 							AString&	str	=	pInfo->m_ProfileName[i];
// 							reader.ReadString(str);
// 						}
// 					}
					break;}
				case	1:{
					ProfileMonitor::GetSingleton()->OnRecvProfileData(uiSocket,reader);
					break;}
			}
			return	true;
		};

	};
	ClientCB g_ClientCB;


	ProfileManager::ProfileManager()
	{
		Common::NetServer::Info	info;
		info.pListener	=	NULL;
		info.strPort	=	m_strProfilePort;
		m_pServer	=	new Common::NetServer("PROFILE",&info);
		if(m_pServer!=NULL){
			m_pServer->Create();
		}

		LARGE_INTEGER	freq;
		QueryPerformanceCounter(&freq);
		m_Freq			=	freq.QuadPart;

		m_uiProfileIndex	=	0;
	}

	ProfileManager::~ProfileManager()
	{
		if(m_pServer!=NULL){
			m_pServer->Destroy();
			delete m_pServer;
			m_pServer	=	NULL;
		}
	}

	void ProfileManager::AddTime( U8 id,S64 timeDelta )
	{
		m_Profile[id]	+=	timeDelta;
	}

	void ProfileManager::SetProfileName( U8 id,CAString& strName )
	{
		m_ProfileName[id]	=	strName;
	}

	void ProfileManager::EndFrame()
	{
		U32	uiType	=	1;
		Common::MemoryWriter	writer(2052);
		writer.Write(uiType);

		for(U32	i=0;i<256;i++){
			S64 val	=	m_Profile[i]*1000000/m_Freq;
			writer.Write(val);
			m_Profile[i]	=	0;
		}

		if(m_pServer!=NULL){
			m_pServer->SendAll(writer.GetDataPtr(),writer.GetDataSize());
		}
	}

	Air::U8 ProfileManager::AddProfile( CAString& strName )
	{
		U8	index	=	m_uiProfileIndex;
		m_uiProfileIndex++;
		m_ProfileName[index]	=	strName;
		return	index;
	}


	Profile::Profile( U8 index )
	{
		id	=	index;
		LARGE_INTEGER	l;
		QueryPerformanceCounter(&l);
		LastTime	=	l.QuadPart;
	}

	Profile::~Profile()
	{
		LARGE_INTEGER	l;
		QueryPerformanceCounter(&l);
		LastTime	=	l.QuadPart	-	LastTime;
		ProfileManager::GetSingleton()->AddTime(id,LastTime);
	}


	ProfileMonitor::ProfileMonitor()
	{
		
	}

	ProfileMonitor::~ProfileMonitor()
	{
		std::map<AString,Common::NetClient*>::iterator	i	=	m_mapClient.begin();
		for(;i!=m_mapClient.end();i++){
			Common::NetClient*&	p	=	i->second;
			if(p!=NULL){
				p->Destroy();
				delete p;
				p=NULL;
			}
		}
		m_mapClient.clear();
		m_mapClientInfo.clear();
	}

	void ProfileMonitor::AddClient( CAString& strServerIP )
	{
		if(strServerIP.empty())
			return;

		m_CS.Enter();
		Common::NetClient::Info	info;
		info.strIP		=	strServerIP;
		info.strPort	=	ProfileManager::m_strProfilePort;
		info.pListener	=	&g_ClientCB;
		Common::NetClient*	pClient	=	new	Common::NetClient(strServerIP,&info);

		m_mapClient[strServerIP]	=	pClient;
		if(pClient!=NULL){
			pClient->Create();
			if(!pClient->Connect(info)){
				pClient->Destroy();
				delete pClient;
				pClient	=	NULL;

				m_mapClient[strServerIP]	=	NULL;
			}
		}
		m_CS.Leave();

	}

	void ProfileMonitor::OnRecvProfileName( U32 uiSocket,Common::StreamReader& reader )
	{
		m_CS.Enter();
		std::map<U32,ClientInfo>::iterator	i	=	m_mapClientInfo.find(uiSocket);//[uiSocket]	=	ClientInfo();
		if(i!=m_mapClientInfo.end()){
			memset(i->second.m_Profile,0,2048);
			for(U32	ii=0;ii<256;ii++){
				reader.ReadString(i->second.m_ProfileName[ii]);
			}

		}else{
			m_mapClientInfo[uiSocket]	=	ClientInfo();
			ClientInfo&	info	=	m_mapClientInfo[uiSocket];
			memset(info.m_Profile,0,2048);
			for(U32	ii=0;ii<256;ii++){
				reader.ReadString(info.m_ProfileName[ii]);
			}
		}
		m_CS.Leave();
	}

	void ProfileMonitor::OnRecvProfileData( U32 uiSocket,Common::StreamReader& reader )
	{
		m_CS.Enter();
		std::map<U32,ClientInfo>::iterator	i	=	m_mapClientInfo.find(uiSocket);
		if(i!=m_mapClientInfo.end()){
			reader.ReadBufferNoSize(i->second.m_Profile,2048);
		}
		m_CS.Leave();
	}

	S64* ProfileMonitor::GetProfile( CAString& strName )
	{
		S64*	pInfo	=	NULL;
		U32	uiSocket		=	m_mapClient[strName]->GetSocket();
		m_CS.Enter();
		std::map<U32,ClientInfo>::iterator	i	=	m_mapClientInfo.find(uiSocket);
		if(i!=m_mapClientInfo.end()){
			pInfo	=	i->second.m_Profile;
		}
		m_CS.Leave();
		return	pInfo;
	}

	void ProfileMonitor::GetProfileName( CAString& strName,AString* strProfileName )
	{
		U32	uiSocket		=	m_mapClient[strName]->GetSocket();
		m_CS.Enter();
		std::map<U32,ClientInfo>::iterator	i	=	m_mapClientInfo.find(uiSocket);
		if(i!=m_mapClientInfo.end()){
			for(U32	ii=0;ii<256;ii++){
				strProfileName[ii]	=	i->second.m_ProfileName[ii];
			}
		}
		m_CS.Leave();
	}

}