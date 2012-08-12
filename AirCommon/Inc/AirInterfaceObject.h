//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/21
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  InterfaceObject.h
 \note     
       
 \attention:
			基本物体类接口
       
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACEOBJECT_HEAD_FILE
#define INTERFACEOBJECT_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

namespace	Air{
	
	namespace Common{
		/**	\brief	基本物体接口类
		*
		*	基本的物体属性
		*
		***/
		class IObject{
		public:
			IObject(){
				m_pUserData	=	NULL;
			};
			virtual	~IObject(){};
			/**	\brief	获取名字
			*			
			*	@remarks		获取名字	
			*	@see		IObject
			*	@return   	Client::String
			*	@note
			*
			**/
			inline	Air::AString GetName(){
				return m_strName;
			}
			/**	\brief	设置名字
			*   
			*	@remarks 	设置名字
			*	@see		IObject
			*	@return   	void
			*	@param		String strName
			*	@note
			*
			**/
			inline	void	SetName(const Air::AString& strName){
				m_strName	= strName;
			};
			/**	\brief	设置用户数据
			*   
			*	@remarks 	设置用户数据
			*	@see		IObject
			*	@return   	void
			*	@param		void* pUserData
			*	@note
			*
			**/
			inline	void	SetUserData(void*	pUserData){
				m_pUserData	=	pUserData;
			};
			/**	\brief	获取用户数据
			*   
			*	@remarks 	获取用户数据
			*	@see		IObject
			*	@return   	void*
			*	@note
			*
			**/
			inline	void*	GetUserData(){
				return	m_pUserData;
			};
			/**	\brief	设置用户字符串
			*   
			*	@remarks 	设置用户字符串
			*	@see		IObject
			*	@return   	void
			*	@param		const Air::AString & strUserString
			*	@note
			*
			**/
			inline	void	SetUserString(const Air::AString&	strUserString){
				m_strUserString	=	strUserString;
			};
			/**	\brief	获取用户字符串
			*   
			*	@remarks 	获取用户字符串
			*	@see		IObject
			*	@return   	Air::AString
			*	@note
			*
			**/
			inline	Air::AString	GetUserString(){
				return	m_strUserString;
			};
		protected:
			Air::AString	m_strName;			///<	物体名称
			Air::AString	m_strUserString;	///<	用户字符信息
			void*			m_pUserData;		///<	用户数据
		};
	};
};
#endif