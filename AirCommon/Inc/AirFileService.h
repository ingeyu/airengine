#ifndef AirFileService_h__
#define AirFileService_h__

#include "AirFileMapping.h"
#include "AirCommonNetServer.h"
#include "AirCommonNetClient.h"

namespace	Air{
	enum enumNetCommandType{
		enNCT_Unknown,
		enNCT_CS_CreateMappingFile,
		enNCT_CS_RequestLoadFile,
		enNCT_SC_LoadFileComplate,
		enNCT_CS_RequestUnloadFile,

		enNCT_SC_Return,
		enNCT_CS_Return,

		enNCT_Max,
	};
	struct NetBaseCommand{
		enumNetCommandType	type;
	};
	template<typename T>
	struct NetCommand	:	public	NetBaseCommand{
		NetCommand(enumNetCommandType t){
			type	=	t;
		};
		U32	GetSize(){
			return	sizeof(*this);
		};
		T	data;
	};

	struct	NCT_CS_CreateMappingFile{
		char	strName[32];
		U32		ProcessId;
	};
	struct	NCT_CS_RequestLoadFile{
		char	strFileName[256];
	};
	struct	NCT_SC_Return{
		U32					uiReturnValue;
		enumNetCommandType	type;
		U32					uiUserData;
	};
	typedef	NCT_SC_Return	NCT_CS_Return;

	struct	ClientInfo{
		U32				uiClientSocket;
		AString			strIP;
		AString			strPort;
		FileMapping*	m_pFile;
	};
	typedef STD_HASHMAP<U32,ClientInfo>	ClientInfoMap;

	class	FileIOThread	:	public	Common::Thread{
	public:

	};

	class	FileServer	:
		public	Common::NetListener{
	public:
		FileServer();
		virtual	~FileServer();

		virtual	U1	Create();
		virtual	U1	Destroy();

		virtual	U1	OnConnected(U32	socket,AString&	strIP,AString&	strPort);
		virtual	U1	OnClose(U32	uiSocket);
		virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);

		virtual	U1	LoadFile(CAString& strName,void*& pData,U32& uiSize);

	protected:
		void		OnCreateFileMapping(U32 uiSocket,NetCommand<NCT_CS_CreateMappingFile>* p);
		void		OnRequestLoadFile(U32 uiSocket,NetCommand<NCT_CS_RequestLoadFile>* p);
		void		OnRequestUnLoadFile(U32 uiSocket,NetCommand<NCT_CS_Return>* p);

		template<typename T>
		void		SendCommand(U32 uiSocket,const T& t){
			m_pConnect->Send(uiSocket,&t,sizeof(T));
		};
	protected:
		Common::NetServer*	m_pConnect;
		ClientInfoMap		m_mapClientInfo;
	};

	class	FileClient	:
		public	Common::NetListener{
	public:
		FileClient(CAString& strName);
		virtual	~FileClient();

		virtual	U1	Create();
		virtual	U1	Destroy();

		virtual	U1	OnConnected(U32	socket,AString&	strIP,AString&	strPort);
		virtual	U1	OnClose(U32	uiSocket);
		virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);
	protected:
		Common::NetClient*	m_pConnect;
		FileMapping*		m_pFile;
		AString				m_strName;
	};
}
#endif // AirFileService_h__
