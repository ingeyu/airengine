/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonRequest.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONREQUEST_HEAD_FILE
#define COMMONREQUEST_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"


#define		UNKNOWN_REQUEST	0

namespace	Air{
	namespace Common{
	
		
		/**	\brief	基本请求
		*
		*	
		*
		***/
		class	IRequest{
		public:
			IRequest()
				:	type(UNKNOWN_REQUEST)
			{
			}
			virtual	~IRequest(){};

			U1	IsValid(){
				return	type	!=	UNKNOWN_REQUEST;
			}
			UInt	type;
		};

		typedef	std::list<IRequest*>		RequestList;	///<	请求列表

		typedef	IFunction<IRequest>			RFunction;

		typedef	std::map<UInt,RFunction*>	FunctionMap;

		/**	\brief	请求管理器
		*
		*	请求管理器
		*
		***/
		class	COMMON_EXPORT	RequestManager{
		public:
			RequestManager(){

			};
			virtual	~RequestManager();

			/**	\brief	添加一个请求
			*   
			*	@remarks 	添加一个请求
			*	@see		RequestManager
			*	@return   	void
			*	@param		IRequest * pRequest
			*	@note
			*
			**/
			virtual	void		AddRequest(IRequest*	pRequest);
			/**	\brief	获取一个请求
			*   
			*	@remarks 	获取一个请求
			*	@see		RequestManager
			*	@return   	IRequest*
			*	@note
			*
			**/
			virtual	IRequest*	GetRequest();

			/**	\brief	判断是否有请求
			*   
			*	@remarks 	判断是否有请求
			*	@see		RequestManager
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1			HasReuqest();

			/**	\brief	处理请求
			*   
			*	@remarks 	处理请求
			*	@see		RequestManager
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		ProcessRequest();

			/**	\brief	执行回调
			*   
			*	@remarks 	执行回调
			*	@see		RequestManager
			*	@return   	void
			*	@param		const IRequest & request
			*	@note
			*
			**/
			virtual	void		ExcuteFunction(const IRequest&	request);

			/**	\brief	添加一个回调函数
			*   
			*	@remarks 	添加一个回调函数
			*	@see		RequestManager
			*	@return   	void
			*	@param		UInt iRequestID
			*	@param		RFunction * pFunction
			*	@note
			*
			**/
			void				AddFunction(UInt iRequestID,RFunction*	pFunction);

			RequestList			m_lstRequest;		///<	请求列表
			FunctionMap			m_mapFunction;		///<	函数列表
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONREQUEST_HEAD_FILE