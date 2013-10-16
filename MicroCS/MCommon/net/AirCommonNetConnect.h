#ifndef COMMONNETCONNECT_HEAD_FILE
#define COMMONNETCONNECT_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonNetSendThread.h"
namespace Air{
	
	namespace Common{
	
		/**	\brief	网络连接
		*
		*	网络连接
		*
		***/
		class	MCOMMON_EXPORT	NetConnect	:
			public	NetListener{
		public:
			NetConnect();
			virtual	~NetConnect();
	
			/**	\brief	创建SOCKET
			*   
			*	@remarks 	创建SOCKET
			*	@see		NetConnect
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateSocket();
			/**	\brief	摧毁SOCKET
			*   
			*	@remarks 	摧毁SOCKET
			*	@see		NetConnect
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	DestroySocket();
	
			/**	\brief	发送数据
			*   
			*	@remarks 	发送数据
			*	@see		NetConnect
			*	@return   	U1
			*	@param		void * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	Send(void*	pData,U32	uiSize);
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
			virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort);
	
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
			/**	\brief	获取SOCKET
			*   
			*	@remarks 	获取SOCKET
			*	@see		NetConnect
			*	@return   	U32
			*	@note
			*
			**/
			U32			GetSocket();
		protected:	
			U32				m_Socket;					///<	SOCKET ID
			NetSendThread	m_ThreadSend;
			NetListener*	m_pListener;
		};
	
		
	
	};
};
#endif // COMMONNETCONNECT_HEAD_FILE