#ifndef COMMONNETCLIENT_HEAD_FILE
#define COMMONNETCLIENT_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
#include "AirCommonNetSendThread.h"
#include "AirCommonNetReceiveThread.h"
#include "AirCommonNetConnect.h"
namespace Air{
	
	namespace Common{
	
		class	COMMON_EXPORT	NetClient	:	
			public	IProduct,
			public	NetConnect
		{
		public:
			static AString	ProductTypeName;
			struct	Info{
				Info(){	
					pListener	=	NULL;
				};
				AString			strIP;
				AString			strPort;
				NetListener*	pListener;
			};
		public:
			NetClient(CAString&	strName,Info*	pInfo);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		NetClient
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		NetClient
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
			/**	\brief	连接完成
			*   
			*	@remarks 	连接完成（客户端这里是连接服务器成功 如果是服务端 表明有客户端连入）
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 socket
			*	@param		AString& strIP
			*	@param		AString& strtPort
			*	@note
			*
			**/
			virtual	U1	OnConnected(U32	socket,AString&	strIP,AString&	strPort);
			/**	\brief	网络关闭回调
			*   
			*	@remarks 	网络关闭回调	可能是正常关闭或者异常关闭
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@note
			*
			**/
			virtual	U1	OnClose(U32	uiSocket);
	
			/**	\brief	当接收到网络数据
			*   
			*	@remarks 	当接收到网络数据
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@param		AChar * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);
	
			/**	\brief	是否已连接
			*   
			*	@remarks 	是否已连接
			*	@see		NetClient
			*	@return   	U1
			*	@note
			*
			**/
			U1			IsConnected();
	
			/**	\brief	连接服务器
			*   
			*	@remarks 	连接服务器
			*	@see		NetClient
			*	@return   	U1
			*	@param		Info & info
			*	@note
			*
			**/
			U1			Connect(Info&	info);
			/**	\brief	断开连接
			*   
			*	@remarks 	断开连接
			*	@see		NetClient
			*	@return   	U1
			*	@note
			*
			**/
			U1			DisConnect();
	
	
			Info				m_Info;
			NetReceiveThread	m_ThreadReceive;
		};
	
	};
};
#endif // COMMONNETCLIENT_HEAD_FILE