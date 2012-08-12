#ifndef RESOURCESYSTEM_HEAD_FILE
#define RESOURCESYSTEM_HEAD_FILE

#include "AirResourceHeader.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Resource{
			class	Package;
			/**	\brief	数据信息
			*
			*	数据信息
			*
			***/
	 		struct	FileDataInfo{
	 			FileDataInfo(){
	 				pData	=	NULL;
				};
	 			Data*	pData;
	 			AString		strName;
	 		};
			
			typedef	std::map<AString,Data*>	DataMap;
			typedef	std::map<Data*,AString>	DataRMap;
			typedef	DataMap::iterator				DataMapItr;
			typedef	DataRMap::iterator				DataRMapItr;
	
			typedef	std::list<Data*>			DataReleaseList;
			typedef	DataReleaseList::iterator		DataReleaseListItr;
	
	
			/**	\brief	资源系统类
			*
			*	资源系统类
			*
			***/
			class	System	:	
				public	ISystem{
			public:
				System();
	
				/**	\brief	初始化
				*   
				*	@remarks 	初始化
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			Initialization();
	
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			Release();
				/**	\brief	查找数据
				*   
				*	@remarks 	查找数据
				*	@see		System
				*	@return   	U32
				*	@param		AString & strName
				*	@param		Data&	data
				*	@note
				*
				**/
				virtual	U32	Find(CAString&	strName,Data&	data);
	
				/**	\brief	查找后缀名文件
				*   
				*	@remarks 	查找后缀名文件
				*	@see		ISystem
				*	@return   	void
				*	@param		AString strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);

	
				/**	\brief	释放缓冲区
				*   
				*	@remarks 	释放缓冲区
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			ReleaseCache();
	
				/**	\brief	设置缓冲区大小
				*   
				*	@remarks 	设置缓冲区大小
				*	@see		System
				*	@return   	void
				*	@param		SInt uiSize
				*	@note
				*
				**/
				virtual	void		SetCacheSize(SInt	uiSize);
	
				/**	\brief	获取缓冲区大小
				*   
				*	@remarks 	获取缓冲区大小
				*	@see		System
				*	@return   	SInt
				*	@note
				*
				**/
				virtual	SInt		GetCacheSize();
	
				/**	\brief	存入数据
				*   
				*	@remarks 	存入数据
				*	@see		System
				*	@param   	Data*	pData
				*	@note
				*
				**/
				virtual	void			PushData2Cache(Data*	pData);
	
				/**	\brief	添加一个资源包
				*   
				*	@remarks 	添加一个资源包
				*	@see		ISystem
				*	@return   	U1
				*	@param		CAString& strPackageName
				*	@param		AString strType
				*	@note
				*
				**/
				virtual	U1			AddPackage(CAString&	strPackageName);
			
			private:
	
	
				DataMap			m_mapCache;				///<	缓冲数据索引
				DataRMap		m_mapRCache;			///<	缓冲数据逆向索引
				DataReleaseList	m_lstReleaseData;		///<	自动释放列表
				SInt			m_uiMaxCacheSize;		///<	缓冲区最大值
				SInt			m_uiCacheSize;			///<	当前缓冲大小
				IPackage*		m_pResource;			///<	基本资源包
				IPackage*		m_pCustom;				///<	自定义资源包
			private:
				Data*		m_pTempData;			///<	临时数据指针
				AString			m_strTempName;			///<	临时数据名
	
				std::map<AString,IPackage*>	m_mapPackage;
			};
		}
	
	};
};
#endif // RESOURCESYSTEM_HEAD_FILE