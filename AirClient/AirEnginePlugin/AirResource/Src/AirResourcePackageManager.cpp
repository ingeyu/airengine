#include "AirResourcePackageManager.h"
#include "AirResourceSystem.h"


namespace	Air{
	namespace	Client{
		namespace	Resource{


			PackageManager::PackageManager(){
				m_pSystem	=	NULL;
			}

			Air::U1 PackageManager::AddPackage( CAString& strName ){
				if(strName.empty())
					return	false;

				IPackage*	p	=	NULL;

				if(strName.size()	<	4){
					p	=	m_pSystem->CreateProduct<IPackage*>(strName,AString("Folder"));

				}else{
					AString	strPostfix	=	Converter::ToLowerCase(Common::GetPostfix(strName));
					if(strPostfix.empty()	||	strPostfix.size()	>	3){
						p	=	m_pSystem->CreateProduct<IPackage*>(strName,AString("Folder"));
					}else{
						p	=	m_pSystem->CreateProduct<IPackage*>(strName,strPostfix);
					}
				}

				if(p!=NULL){
					m_lstPackage.push_back(p);
				}

				return	true;
			}

			U32 PackageManager::Find( CAString& strName ,Data&	data){
				PackageListItr	i	=	m_lstPackage.begin();
				for(;i!=m_lstPackage.end();i++){
					IPackage*	p	=	(IPackage*)(*i);
					if(p!=NULL){
						U32	uiSize	=	p->Find(strName,data);
						if(uiSize!=0)
							return	uiSize;

					}
				}

				return	0;
			}

			void PackageManager::FindWithPostfix( CAString& strPostfix,IFindFileListener* pListener ){
				PackageListItr	i	=	m_lstPackage.begin();
				for(;i!=m_lstPackage.end();i++){
					IPackage*	p	=	(IPackage*)(*i);
					if(p!=NULL){
						p->FindWithPostfix(strPostfix,pListener);
					}
				}
			}

			PackageManager::~PackageManager(){
				if(m_pSystem!=NULL){
					PackageListItr	i	=	m_lstPackage.begin();
					for(;i!=m_lstPackage.end();i++){
						IPackage*	p	=	(IPackage*)(*i);
						m_pSystem->DestroyProduct(p);
						p	=	NULL;
					}
					m_lstPackage.clear();
				}
			}

			void PackageManager::SetSystem( System* pSys ){
				m_pSystem	=	pSys;
			}
		}
	}
}