#ifndef COMMONNETSERVER_HEAD_FILE
#define COMMONNETSERVER_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
#include "AirCommonNetSendThread.h"
#include "AirCommonNetReceiveThread.h"
#include "AirCommonNetListenThread.h"
#include "AirCommonNetConnect.h"
namespace Air{
	
	namespace Common{
	
		/**	\brief	服务器
		*
		*	服务器
		*
		***/
		class	MCOMMON_EXPORT	NetServer	:
			public	IProduct,
			public	NetConnect
		{
		public:
			static AString	ProductTypeName;
			struct	Info{
				Info(){
					pListener	=	NULL;
				};
				U16				usPort;
				NetListener*	pListener;
			};
		public:
			NetServer(CAString&	strName,Info*	pInfo);
	
			
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		NetServer
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		NetServer
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
			*	@param		AString& strPort
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
	
			/**	\brief	发送数据
			*   
			*	@remarks 	发送数据
			*	@see		NetConnect
			*	@return   	U1
			*	@param		const void * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	SendAll(const void*	pData,U32	uiSize);
	
			/**	\brief	向自定目标发送数据
			*   
			*	@remarks 	向自定目标发送数据
			*	@see		NetServer
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@param		const void * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	Send(U32	uiSocket,const void*	pData,U32	uiSize);
		protected:
		private:
			Info				m_Info;				///<	创建信息
	
			NetListenThread		m_ThreadListen;		///<	监听线程
			ReceiveThreadMap	m_mapReceiveThread;	///<	接收线程
	
			ReceiveThreadList	m_lstUnUsedThread;	///<	未使用的线程
			CriticalSection		m_ReceiveCS;
		};

	};
};
#endif // COMMONNETSERVER_HEAD_FILE