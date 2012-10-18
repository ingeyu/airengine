/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonRequestProduct.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONREQUESTPRODUCT_HEAD_FILE
#define COMMONREQUESTPRODUCT_HEAD_FILE

#include "AirCommonProduct.h"
#include "AirCommonRequest.h"

namespace	Air{
	namespace Common{
	
		class	COMMON_EXPORT	RequestProduct	:
			public	IProduct,
			public	RequestManager
		{
		public:
			RequestProduct(const AString&	strName);
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
		protected:
			CriticalSection		m_CS;
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONREQUESTPRODUCT_HEAD_FILE