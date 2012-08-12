/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/07/26
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonStringHandle.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONSTRINGHANDLE_HEAD_FILE
#define COMMONSTRINGHANDLE_HEAD_FILE

#include <AirCommonHashTable.h>
#include "AirCommonLock.h"


namespace	Air{
	namespace Common{

		class	COMMON_EXPORT	StringHashTable	:	
			public	T_HashTable<AString>,
			public	Singleton<StringHashTable>
		{
		public:
			AString*		HashString(const AString&	str);
			AString*		HashString(const AChar*		str);
			CriticalSection	m_CS;
		};
	
		/**	\brief	字符串句柄
		*
		*	仅针对 对比字符串句柄之间的对比速度快 可以减少内存碎片 节省创建销毁时间
		*
		***/
		class	COMMON_EXPORT	StringHandle	:	
			public	T_Handle<AString>{
		public:
			StringHandle();
			StringHandle(const AString&	str);
			StringHandle(const AString*	pStr);
			StringHandle(const AChar*	str);
			StringHandle(const StringHandle&	handle);

			StringHandle&	operator	=	(const StringHandle&	handle);
			StringHandle&	operator	=	(const AString&			str);
			StringHandle&	operator	=	(const AString*			pStr);
			StringHandle&	operator	=	(const AChar*			str);

			bool			operator	==	(const StringHandle&	handle);
			bool			operator	!=	(const StringHandle&	handle);
			bool			operator	>	(const StringHandle&	handle);
			bool			operator	<	(const StringHandle&	handle);
			bool			operator	<=	(const StringHandle&	handle);
			bool			operator	>=	(const StringHandle&	handle);

			const AChar*		c_str()const ;
			AString*	get(){
				return	m_pValue;
			};
			AChar&	operator[](const U32	index);
		};

	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONSTRINGHANDLE_HEAD_FILE