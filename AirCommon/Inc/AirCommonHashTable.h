/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/07/26
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonHashTable.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONHASHTABLE_HEAD_FILE
#define COMMONHASHTABLE_HEAD_FILE

#include "AirCommonHeader.h"

namespace	Air{
	namespace Common{

		template<typename	T_Type>
		class	T_Handle{
		public:
			T_Handle(){
				m_pValue	=	NULL;
			};

			T_Type*	operator->(){
				return	m_pValue;
			};
			T_Type*	m_pValue;
		};
	
		
		template<typename	T_Type>
		class	T_HashTable{
		public:
			T_Type*	Hash(const T_Type& t){
				stdext::hash_set<T_Type>::iterator	i	=	m_setValue.find(t);
				if(i==m_setValue.end()){
					i	=	m_setValue.insert(t).first;
				}
				return	(T_Type*)&(*i);
			};

			stdext::hash_set<T_Type>	m_setValue;
		};

	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONHASHTABLE_HEAD_FILE