
#include "AirResourceSystem.h"
#include "AirGlobalSetting.h"

#include "AirResourceRarPackage.h"
#include "AirResourceZipPackage.h"
#include "AirResourceFolderPackage.h"

#include "AirResourceFileStream.h"

#include "AirResourcePackageManager.h"

namespace Air{
	
	namespace	Client{
	
		namespace	Resource{
	
			System::System():ISystem("ResourceSystem"){
				m_pResource			=	NULL;
				m_pCustom			=	NULL;
				m_pTempData			=	NULL;
				m_uiMaxCacheSize	=	50*1024*1024;	///<	设定50M的缓冲区
				m_uiCacheSize		=	0;
				m_strName			=	"Default ResourceSystem";
				
			}
	
			U1 System::ReleaseCache(){
// 				m_mapCache.clear();
// 				m_mapRCache.clear();
// 				DataReleaseListItr	i	=	m_lstReleaseData.begin();
// 				for(;i!=m_lstReleaseData.end();i++){
// 					Data*	pData	=	(Data*)(*i);
// 					SAF_D(pData);
// 				}
// 				m_lstReleaseData.clear();
				return	true;
			}
	
			U1 System::Initialization(){
	
				AddFactory(new	ZipPackageFactory());
				AddFactory(new	RarPackageFactory());
				AddFactory(new	FolderPackageFactory());
				//AddFactory(new	FileStreamFactory(),this);


				PackageManager::GetSingleton()->SetSystem(this);
			
	
				//AddPackage(AString(GetGlobalSetting().m_EngineParam.strMedia));
				//AddPackage(AString(GetGlobalSetting().m_EngineParam.strCustomMedia));
	
				return	true;
			}
	
			U1 System::Release(){

				PackageManager::ReleaseSingleton();

				m_mapPackage.clear();
	
				DestroyAllProduct();
	
				ReleaseCache();
				
				return	true;
			}
	
			U32 System::Find( CAString& strName,Data&	data ){
				if(strName.empty())
					return	NULL;
				//转化为小写
				AString	str	=	strName;
				Converter::ToLowerCase(str);

				return	PackageManager::GetSingleton()->Find(str,data);
	
				//从缓冲区中查找
// 				DataMapItr	i	=	m_mapCache.find(m_strTempName.c_str());
// 				if(i!=m_mapCache.end()){
// 					Data*	pData	=	i->second;
// 					//放到释放队列的最后面
// 					m_lstReleaseData.remove(pData);
// 					m_lstReleaseData.push_back(pData);
// 					//返回数据
// 					return	pData;
// 				}else{
// 					
// 					std::map<AString,IPackage*>::iterator	i	=	m_mapPackage.begin();
// 					for(;i!=m_mapPackage.end();i++){
// 						if(i->second->IsExist(m_strTempName)){
// 							Data*	pData	=	i->second->Find(m_strTempName);
// 							if(pData!=NULL)
// 								PushData2Cache(pData);
// 							return	pData;
// 						}
// 					}
// 					return	NULL;
// 				}
			}
	
			void System::PushData2Cache(Data*	pData){
				Data*	p	=	pData;
				//缓冲区大小计数
				m_uiCacheSize	+=	p->GetSize();
				//存入索引列表中
				m_mapCache[m_strTempName.c_str()]	=	p;
				m_mapRCache[m_pTempData]			=	m_strTempName.c_str();
				//存入自动释放列表中
				m_lstReleaseData.push_back(p);
				//判断是否超过缓冲限制
				while(m_uiCacheSize	>	m_uiMaxCacheSize){
					DataReleaseListItr	i	=	m_lstReleaseData.begin();
					Data*	pData	=	(Data*)(*i);
					m_uiCacheSize	-=	pData->GetSize();
					m_lstReleaseData.erase(i);
					
					DataRMapItr	ii		=	m_mapRCache.find(pData);
					if(ii!=m_mapRCache.end()){
						AString	str	=	ii->second;
						DataMapItr	iii	=	m_mapCache.find(str.c_str());
						if(iii!=m_mapCache.end()){
							m_mapCache.erase(iii);
						}
						m_mapRCache.erase(ii);
					}
					SAF_D(pData);
				}
			}
	
			void System::SetCacheSize( SInt uiSize ){
				if(uiSize	>	200*1024*1024)
					uiSize	=	200*1024*1024;
				m_uiMaxCacheSize	=	uiSize;
			}
	
			SInt System::GetCacheSize(){
				return	m_uiMaxCacheSize;
			}
	
	
	
			void System::FindWithPostfix( CAString& strPostfix,IFindFileListener* pListener ){
				
				if(	pListener==NULL	||
					strPostfix.empty())
				{
					return;
				}
	
// 				AString	strTempName	=	strPostfix;
// 				Converter::ToLowerCase(strTempName);
// 	
// 				std::map<AString,IPackage*>::iterator	i	=	m_mapPackage.begin();
// 				for(;i!=m_mapPackage.end();i++){
// 					i->second->FindWithPostfix(strTempName,pListener);
// 				}
				PackageManager::GetSingleton()->FindWithPostfix(strPostfix,pListener);
			}
	
			U1 System::AddPackage( CAString& strPackageName ){
// 				if(strPackageName.empty()	||
// 					strType.empty())
// 				{
// 					return	false;
// 				}
// 				std::map<AString,IPackage*>::iterator	i	=	m_mapPackage.find(strPackageName.c_str());
// 				if(i!=m_mapPackage.end()){
// 					//资源包已经加载
// 					return	true;
// 				}
// 				//转化为小写
// 				AString	t	=	strType;
// 				Converter::ToLowerCase(t);
// 				m_mapPackage[strPackageName.c_str()]	=	Create<IPackage*>(strPackageName,t);

				
	
				return	PackageManager::GetSingleton()->AddPackage(strPackageName);
			}
		}
	}
};