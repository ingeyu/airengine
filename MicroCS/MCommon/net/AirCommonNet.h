#ifndef COMMONNET_HEAD_FILE
#define COMMONNET_HEAD_FILE

#include "MCommon.h"


#ifndef MAX_NET_BUFF
#define	MAX_NET_BUFF	1024
#endif

#ifndef REAL_NET_BUFF
#define REAL_NET_BUFF	MAX_NET_BUFF-4
#endif
namespace Air{
	
	namespace Common{
	
		/**	\brief	初始化网络
		*   
		*	@remarks 	初始化网络
		*	@see		
		*	@return   	U1
		*	@note
		*
		**/
		MCOMMON_EXPORT	U1		InitNet();
		/**	\brief	卸载网络
		*   
		*	@remarks 	卸载网络
		*	@see		
		*	@return   	U1
		*	@note
		*
		**/
		MCOMMON_EXPORT	U1		ReleaseNet();
	
		MCOMMON_EXPORT	void	GetLocalIP(AString& strIP);
		//发送数据包
		struct	NetPack{
			NetPack(){
				uiSocket	=	0;
				uiSize		=	0;
				pData		=	NULL;
			};
	
			NetPack(U32 sock,U32 size,const void*	p){
				if(sock==0||size==0||p==NULL)
					return;
				uiSocket	=	sock;
				uiSize		=	size+4;
				pData		=	new	S8[uiSize];
				memcpy(pData,&size,4);
				memcpy(&pData[4],p,size);
			};
	
			~NetPack(){
				SAF_DA(pData);
			}
			/**	\brief	数据包是否有效
			*   
			*	@remarks 	数据包是否有效
			*	@see		SendPack
			*	@return   	U1
			*	@note
			*
			**/
			U1	IsValid(){
				if(	uiSocket	==	NULL	||
					uiSize		==	0		||
					pData		==	NULL)
				{
					return	false;
				}
				return	true;
			};
			U32		uiSocket;
			U32		uiSize;
			S8*		pData;
	
		};
	
		/**	\brief	网路监听器
		*
		*	网路监听器
		*
		***/
		class	NetListener{
		public:
			virtual	~NetListener(){};
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
			virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort)	=	NULL;
			/**	\brief	网络关闭回调
			*   
			*	@remarks 	网络关闭回调	可能是正常关闭或者异常关闭
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@note
			*
			**/
			virtual	U1	OnClose(U32	uiSocket)					=	NULL;
	
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
			virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize)	=	NULL;
		};
	
		//网络数据
		struct	INetData{
			INetData(){
				MainID	=	0;
				SubID	=	0;
			};
			U32		MainID;
			U32		SubID;
		};
	
		/**	\brief	IP转化为字符串
		*   
		*	@remarks 	IP转化为字符串
		*	@see		
		*	@return   	MCOMMON_EXPORT	AString
		*	@param		U32 ip
		*	@note
		*
		**/
		MCOMMON_EXPORT	AString	IP2String(U32	ip);
		/**	\brief	字符串转换为IP
		*   
		*	@remarks 	字符串转换为IP
		*	@see		
		*	@return   	MCOMMON_EXPORT	U32
		*	@param		AString strIP
		*	@note
		*
		**/
		MCOMMON_EXPORT	U32		String2IP(AString	strIP);
	};
};
#endif // COMMONNET_HEAD_FILE