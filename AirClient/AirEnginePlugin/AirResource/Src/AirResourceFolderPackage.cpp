#include "AirResourceFolderPackage.h"

namespace	Air{
	namespace	Engine{
		namespace	Resource{
			AString FolderPackage::ProductTypeName="Folder";
			FolderPackage::FolderPackage( CAString& strName ):IPackage(strName){
				m_pTempListener	=	NULL;
				AChar cEnd	=	strName[strName.size()-1];
				if(cEnd!='\\'&&	cEnd!='/'){
					m_strRealPath	=	strName	+	"/";
				}else{
					m_strRealPath	=	strName;
				}
			}

			U32			FolderPackage::Find(CAString&	strName,Data&	data){
				return	FindWithFullPath(m_strRealPath	+	strName,data);
			}

			void FolderPackage::FindWithPostfix( CAString& strPostfix,IFindFileListener* pListener ){
				m_pTempListener		=	pListener;
				m_strTempPostfix	=	AString(".")+strPostfix;
				File::FolderTraversal(m_strRealPath,this);
				m_pTempListener		=	NULL;
			}

			Air::U1 FolderPackage::Create(){
				return	true;
			}

			Air::U1 FolderPackage::OnFindFile( CAString& strName ){
				if(!Common::EndWith(strName,m_strTempPostfix))
					return	false;

				Data	data;
				FindWithFullPath(strName,data);
				if(	m_pTempListener	!=	NULL){
						m_pTempListener->OnFindFile(strName,&data);
				}
				return	true;
			}

			Air::U1 FolderPackage::OnFindDirectory(CAString& strName ){
				return	true;
			}

			U32		FolderPackage::FindWithFullPath( CAString& filename ,Data&	data){
				
				if(Common::File::Load(filename,data)){
					return	data.size;
				}
				return	NULL;
			}
		}
	}
}