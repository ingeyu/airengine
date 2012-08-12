/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/23
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonString.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONSTRING_HEAD_FILE
#define COMMONSTRING_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

namespace	Air{
	namespace Common{
		
		/**	\brief	判断字符串是否以某字符打头
		*   
		*	@remarks 	判断字符串是否以某字符打头
		*	@see		
		*	@return   	COMMON_EXPORT	U1
		*	@param		CAString & strWhole
		*	@param		CAString & strPart
		*	@note
		*
		**/
		COMMON_EXPORT	U1	StartWith(CAString&	strWhole,CAString&	strPart);
		/**	\brief	判断字符串是否以字符串结尾
		*   
		*	@remarks 	判断字符串是否以字符串结尾
		*	@see		
		*	@return   	COMMON_EXPORT	U1
		*	@param		CAString & strWhole
		*	@param		CAString & strPart
		*	@note
		*
		**/
		COMMON_EXPORT	U1	EndWith(CAString&	strWhole,CAString&	strPart);

		/**	\brief	获取后缀名
		*   
		*	@remarks 	获取后缀名
		*	@see		
		*	@return   	COMMON_EXPORT	AString
		*	@param		CAString & strName
		*	@note
		*
		**/
		COMMON_EXPORT	AString	GetPostfix(CAString&	strName);
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONSTRING_HEAD_FILE