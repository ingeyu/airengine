/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/04/21
 \version   ver 0.6.0.0
 \filepath  f:\EngineSource\Air\AirClient\AirEnginePlugin\AirResource
 \filename  ResourcePackageManager.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef RESOURCEPACKAGEMANAGER_HEAD_FILE
#define RESOURCEPACKAGEMANAGER_HEAD_FILE

#include "AirResourceHeader.h"

namespace	Air{
	namespace Client{
	
		namespace	Resource{
			typedef	std::list<IPackage*>	PackageList;
			typedef	PackageList::iterator	PackageListItr;

			class	System;

			/**	\brief	资源包管理器
			*
			*	资源包管理器
			*
			***/
			class	PackageManager	:
				public	Singleton<PackageManager>{
			public:
				PackageManager();

				virtual	~PackageManager();

				/**	\brief	添加一个资源包
				*   
				*	@remarks 	添加一个资源包
				*	@see		PackageManager
				*	@return   	Air::U1
				*	@param		CAString&	strName
				*	@note
				*
				**/
				U1	AddPackage(CAString&	strName);
				/**	\brief	查找文件
				*   
				*	@remarks 	查找文件
				*	@see		PackageManager
				*	@return   	Data*
				*	@param		AString & strName
				*	@note
				*
				**/
				U32		Find(CAString&	strName,Data&	data);
				/**	\brief	查找后缀名文件
				*   
				*	@remarks 	查找后缀名文件
				*	@see		ISystem
				*	@return   	void
				*	@param		AString& strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);

				/**	\brief	设置系统指针
				*   
				*	@remarks 	设置系统指针
				*	@see		PackageManager
				*	@return   	void
				*	@param		System * pSys
				*	@note
				*
				**/
				void				SetSystem(System*	pSys);
			protected:

				System*			m_pSystem;
				PackageList		m_lstPackage;
			};
		};
	};//end of	namespace	Client
};//end of namespace Air
#endif // RESOURCEPACKAGEMANAGER_HEAD_FILE