//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonReference.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONREFERENCE_HEAD_FILE
#define COMMONREFERENCE_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
namespace Air{
	
	namespace Common{
	
		class COMMON_EXPORT	IReference{
		public:
			IReference();
			virtual	~IReference();
	
			/**	\brief	增加引用
			*   
			*	@remarks 	增加引用
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual U32		AddRef();
			/**	\brief	减少引用
			*   
			*	@remarks 	减少引用
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U32		ReleaseRef();
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Create()	=	NULL;
			/**	\brief	释放
			*   
			*	@remarks 	
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Destroy()	=	NULL;
			/**	\brief	获取引用对象指针
			*   
			*	@remarks 	获取引用对象指针
			*	@see		IReference
			*	@return   	UInt*
			*	@note
			*
			**/
			inline	void*	GetObject(){return	m_pObject;};
			/**	\brief	获取引用对象指针
			*   
			*	@remarks 	获取引用对象指针（模板）
			*	@see		IReference
			*	@return   	T_Object
			*	@note
			*
			**/
			template	<typename	T_Object>
			T_Object		GetObjectT(){return	(T_Object)(m_pObject);};
	
			/**	\brief	是否为空
			*   
			*	@remarks 	是否为空
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		IsNull(){return	(m_pObject	==	NULL);};
	
			/**	\brief	获取引用计数
			*   
			*	@remarks 	获取引用计数
			*	@see		IReference
			*	@return   	UInt
			*	@note
			*
			**/
			inline	U32	GetRefCount(){return m_uiNumRef;};
		protected:
			void*	m_pObject;		///<	引用对象指针
			U32		m_uiNumRef;		///<	引用计数
		private:
		};
	
	};
};
#endif // COMMONREFERENCE_HEAD_FILE