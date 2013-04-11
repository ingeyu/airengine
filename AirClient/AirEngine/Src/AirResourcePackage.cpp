#include "AirResourcePackage.h"
#include "AirCommonFile.h"
namespace	Air{
	namespace	Engine{
		namespace	Resource{

			class FindCB : public	Common::File::TraversalCallBack{
			public:
				FindCB(CAString& str,Package* pPkg,FindFileCallback* pCB):strPostfix(str){
					pCallBack	=	pCB;
					pPackage	=	pPkg;
				}
				virtual	U1	OnFindFile(CAString&	strName){
					if(!Common::EndWith(strName,strPostfix))
						return	false;
					Data	data;
					pPackage->FindWithFullPath(strName,data);
					if(data.IsNull())
						return false;
					if(	pCallBack	!=	NULL){
						pCallBack->OnFindFile(strName,&data);
					}
					return true;
				};
				virtual	U1	OnFindDirectory(CAString&	strName){
					return true;
				};
				FindFileCallback*	pCallBack;
				CAString&			strPostfix;
				Package*			pPackage;
			};


			Air::U32 Package::IsExist( CAString& strName )
			{
				FileInfoMap::iterator	i	=	m_mapFileInfo.find(strName.c_str());
				if(i!=m_mapFileInfo.end()){
					return	i->second.uncompressedSize;
				}else{
					return	0;
				}
			}
			AString Package::ProductTypeName="Package";
			Package::Package( CAString& strName ):IProduct(strName)
			{
				AChar cEnd	=	strName[strName.size()-1];
				if(cEnd!='\\'&&	cEnd!='/'){
					m_strRealPath	=	strName	+	"/";
				}else{
					m_strRealPath	=	strName;
				}
			}

			Air::U1 Package::Create()
			{

				return true;
			}

			Air::U1 Package::Destroy()
			{

				return true;
			}

			Air::U32 Package::Find( CAString& strName,Data& data )
			{
				return	FindWithFullPath(m_strRealPath	+	strName,data);
			}

			Air::U32 Package::FindWithFullPath( CAString& filename,Data& data )
			{
				if(Common::File::Load(filename,data)){
					return	data.size;
				}
				return	true;
			}

			void Package::FindWithPostfix( CAString& strPostfix,FindFileCallback* pCB )
			{
				FindCB cb(strPostfix,this,pCB);
				File::FolderTraversal(m_strRealPath,&cb);
			}

		}
	}
}