#ifndef INTERFACEUSERDATA_HEAD_FILE
#define INTERFACEUSERDATA_HEAD_FILE

#include "AirEngineHeader.h"

namespace Air{
	namespace Client{
	
		/**	\brief	用户数据类
		*
		*	用户数据类
		*
		***/
		class	IUserData{
		public:
			IUserData(){
				m_pUserData	=	NULL;
			};
	
			/**	\brief	获取用户字符串
			*   
			*	@remarks 	获取用户字符串
			*	@see		IUserData
			*	@return   	AString
			*	@note
			*
			**/
			inline	AString		GetUserString(){
				return	m_strUserString;
			};
			/**	\brief	设置用户字符串
			*   
			*	@remarks 	设置用户字符串
			*	@see		IUserData
			*	@return   	void
			*	@param		AString str
			*	@note
			*
			**/
			inline	void		SetUserString(AString	str){
				m_strUserString	=	str;
			};
			/**	\brief	获取用户数据
			*   
			*	@remarks 	获取用户数据
			*	@see		IUserData
			*	@return   	void*
			*	@note
			*
			**/
			inline	void*		GetUserData(){
				return	m_pUserData;
			};
			/**	\brief	设置用户数据
			*   
			*	@remarks 	设置用户数据
			*	@see		IUserData
			*	@return   	void
			*	@param		void * pData
			*	@note
			*
			**/
			inline	void		SetUserData(void*	pData){
				m_pUserData	=	pData;
			};
	
			AString	m_strUserString;		///<	用户数据
			void*	m_pUserData;			///<	用户数据
		};
	
	};
};
#endif // INTERFACEUSERDATA_HEAD_FILE