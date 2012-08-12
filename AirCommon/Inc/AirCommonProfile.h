#ifndef AirCommonProfile_h__
#define AirCommonProfile_h__

#include "AirCommonHeader.h"
#include "AirCommonLock.h"

namespace	Air{
	namespace	Common{
		class	NetServer;
		class	NetClient;
		class	StreamReader;
	}

	class	COMMON_EXPORT	Profile{
	public:
		Profile(U8	index);
		~Profile();
		U8	id;
		S64	LastTime;
	};
	class	COMMON_EXPORT	ProfileManager	:	
		public	Singleton<ProfileManager>{
	public:
		ProfileManager();
		virtual	~ProfileManager();

		void	AddTime(U8	id,S64	timeDelta);
		U8		AddProfile(CAString&	strName);
		void	SetProfileName(U8	id,CAString&	strName);
		void	EndFrame();

		S64					m_Profile[256];
		AString				m_ProfileName[256];
		Common::NetServer*	m_pServer;
		static	AString		m_strProfilePort;
		U8					m_uiProfileIndex;
		S64					m_Freq;
	};

	class	COMMON_EXPORT	ProfileMonitor	:	
		public	Singleton<ProfileMonitor>{
	public:
		struct	ClientInfo{
			Common::NetClient*	m_pClient;
			S64					m_Profile[256];
			AString				m_ProfileName[256];
		};

		ProfileMonitor();
		virtual	~ProfileMonitor();

		void	AddClient(CAString&	strServerIP);
		void	RemoveClient(CAString&	strServerIP);

		void	OnRecvProfileName(U32	uiSocket,Common::StreamReader&	reader);
		void	OnRecvProfileData(U32	uiSocket,Common::StreamReader&	reader);
		S64*	GetProfile(CAString&	strName);
		void	GetProfileName(CAString&	strName,AString*	strProfileName);
		
		
		std::map<U32,ClientInfo>				m_mapClientInfo;
		std::map<AString,Common::NetClient*>	m_mapClient;
		Common::CriticalSection					m_CS;
	};
}

#ifdef	USE_PROFILE
#define PROFILE_FUNCTION	static	Air::U8	profile_index				=	Air::ProfileManager::GetSingleton()->AddProfile(__FUNCTION__);\
							Profile	profile_function(profile_index);

#define PROFILE_END_FRAME	Air::ProfileManager::GetSingleton()->EndFrame();
#else
#define PROFILE_FUNCTION	
#define PROFILE_END_FRAME
#endif

#endif // AirCommonProfile_h__
