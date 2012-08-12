#include "AirCommonPackage.h"
#include "AirCompress.h"
namespace Air{
	
	namespace Common{
	
	
	
		Package::Package(){
			_ZERO(m_uiSize);
			_ZERO(m_pFilePtr);
		}
	
		Package::~Package(){
			UnLoad();
		}
	
		bool Package::Load( S8* strPackageName ){
			if(strPackageName==NULL)
				return false;
			FILE*	pFile	= NULL;
			fopen_s(&pFile,strPackageName,"rb");
			if(pFile==NULL)
				return false;
	
	
			fseek(pFile,0,SEEK_END);
			U32	uiPackageSize	= ftell(pFile);
			//资源包文件大小小于4 必定资源包错误
			if(uiPackageSize<4){
				fclose(pFile);
				return false;
			}
			m_uiSize	= uiPackageSize;
	
	
			enumVersion	enVer		= enUnKnown;
			fseek(pFile,sizeof(enVer),SEEK_END);
			fread(&enVer,sizeof(enVer),1,pFile);
			//检查版本号
			if(!CheckVersion(enVer)){
				fclose(pFile);
				return false;
			}
			m_enVersion	= enVer;
	
	
	
			//载入文件信息
			if(!LoadFileInfo(enVer,pFile)){
				fclose(pFile);
				return false;
			}
			//fclose(pFile);
			m_pFilePtr	= pFile;
			return true;
		}
	
		void Package::UnLoad(){
			fclose((FILE*)m_pFilePtr);
			m_vecFileInfo.clear();
			m_mapFileInfo.clear();
			_ZERO(m_uiSize);
			_ZERO(m_pFilePtr);
		}
	
		bool Package::CheckVersion( enumVersion enVer ){
			if(enVer<=enUnKnown || enVer >= enMaxVersion){
				return false;
			}
			return true;
		}
	
		bool Package::LoadFileInfo( enumVersion enVer,void* pFilePtr ){
			if(pFilePtr==NULL)
				return false;
			switch(enVer){
				case	enV_1_0:{
					LoadFileInfo_1(pFilePtr);
				break;}
				default:
					return false;
				break;
			}
			return true;
		}
	
		bool Package::LoadFileInfo_1( void* pFilePtr ){
			U32	uiNumFile	= 0;
			FILE*	p	= (FILE*)pFilePtr;
			SInt iOffset	= sizeof(uiNumFile);
			fseek(p,-iOffset,SEEK_CUR);
			fread(&uiNumFile,iOffset,1,p);
			if(uiNumFile==0){
				return true;
			}
			m_vecFileInfo.resize(uiNumFile);
			iOffset	= sizeof(File::Info)*uiNumFile;
			fseek(p,-iOffset,SEEK_CUR);
			fread(&m_vecFileInfo[0],iOffset,1,p);
	
			for(U32 i=0;i<uiNumFile;i++){
				m_mapFileInfo.insert(FileInfoMapPair(m_vecFileInfo[i].GetFullName(),m_vecFileInfo[i]));
			}
			return true;
		}
	
		bool Package::New( S8* strPackageName ){
			if(!m_vecFileInfo.empty()){
				UnLoad();
			}
	
			S8 strName[MAX_NAME];
			if(strPackageName	== NULL){
				strcpy_s(strName,MAX_NAME,"UnName.package");
			}else{
				strcpy_s(strName,MAX_NAME,strPackageName);
			}
	
			FILE* pFile	= NULL;
			fopen_s(&pFile,strName,"wb");
			if(pFile==NULL)
				return false;
			enumVersion enVer		= (enumVersion)(enMaxVersion - 1);
			U32			uiNumFile	= 0;
			fwrite(&uiNumFile,sizeof(uiNumFile),1,pFile);
			fwrite(&enVer,sizeof(enVer),1,pFile);
			fclose(pFile);
	
			return Load(strName);
		}
	
		bool Package::AddFile( S8* strName ){
			if(strName==NULL)
				return false;
			//读取源文件
			FILE* pSrcFile	= NULL;
			fopen_s(&pSrcFile,strName,"rb");
			if(pSrcFile==NULL)
				return false;
			fseek(pSrcFile,0,SEEK_END);
			U32	uiSrcFileSize	= ftell(pSrcFile);
			fseek(pSrcFile,0,SEEK_SET);
	
			U8*	pData	= new U8[uiSrcFileSize];
			fwrite(pData,uiSrcFileSize,1,pSrcFile);
			fclose(pSrcFile);
	
			if(!AddFileFromMemery(strName,pData,uiSrcFileSize)){
				delete[] pData;
				return false;
			}
			delete[] pData;
			return true;
		}
	
		U32 Package::GetDataEndPosition( enumVersion enVer ){
			switch(enVer){
				case	enV_1_0:{
					return GetDataEndPosition_1();
				break;}
				default:
					return 0;
				break;
			}
			return 0;
		}
	
		U32 Package::GetDataEndPosition_1(){
			return	m_uiSize - m_vecFileInfo.size()*sizeof(File::Info) - sizeof(U32) - sizeof(enumVersion);
		}
	
		bool Package::AddFileFromMemery( S8* strName,U8* pData,U32 uiDataSize ){
			U8*	pCompressData	= new U8[uiDataSize];
			U32	uiCompressSize	= 0;
			Compress::ToLZO(pData,uiDataSize,pCompressData,&uiCompressSize);
			
			U32	uiFileDataEndPos	= GetDataEndPosition(m_enVersion);
			FILE* pFile	= (FILE*)m_pFilePtr;
			fseek(pFile,uiFileDataEndPos,SEEK_SET);
			
			FileInfoMapItr	i	= m_mapFileInfo.find(strName);
			if(i==m_mapFileInfo.end()){
				File::Info	info(strName,uiFileDataEndPos,uiDataSize,uiCompressSize);
				m_mapFileInfo.insert(FileInfoMapPair(info.GetFullName(),info));
				m_vecFileInfo.push_back(info);
				fwrite(pCompressData,uiCompressSize,1,pFile);
				WriteFileInfo(m_enVersion,pFile);
				delete[] pCompressData;
				return true;
			}else{
				if(i->second.m_uiCompressSize > uiCompressSize){
					i->second.m_uiOriginalSize	= uiDataSize;
					i->second.m_uiCompressSize	= uiCompressSize;
					fseek(pFile,0,i->second.m_uiFilePtr);
					fwrite(pCompressData,uiCompressSize,1,pFile);
					delete[] pCompressData;
					return true;
				}else{
					File::Info	info(strName,uiFileDataEndPos,uiDataSize,uiCompressSize);
					m_mapFileInfo.erase(i);
					m_mapFileInfo.insert(FileInfoMapPair(info.GetFullName(),info));
	
					FileInfoVector vecFileInfo	= m_vecFileInfo;
					m_vecFileInfo.clear();
					UInt	iNumFile	= vecFileInfo.size();
					if(iNumFile == 1){
						m_vecFileInfo.push_back(info);
					}else{
						m_vecFileInfo.resize(vecFileInfo.size() - 1);
						for(UInt j =0;j<iNumFile;i++){
							if(strcmp(strName,vecFileInfo[j].GetFullName())==0){
								if(j==0){
									memcpy(&m_vecFileInfo[0],&vecFileInfo[1],sizeof(File::Info)*(iNumFile - 1));
								}else if(j == iNumFile - 1){
									memcpy(&m_vecFileInfo[0],&vecFileInfo[0],sizeof(File::Info)*(iNumFile - 1));
								}else{
									memcpy(&m_vecFileInfo[0],&vecFileInfo[0],sizeof(File::Info)*(j));
									memcpy(&m_vecFileInfo[j],&vecFileInfo[j+1],sizeof(File::Info)*(iNumFile - j - 1));
								}
							}
						}
					}
	
					m_vecFileInfo.push_back(info);
					fwrite(pCompressData,uiCompressSize,1,pFile);
					WriteFileInfo(m_enVersion,pFile);
					delete[] pCompressData;
					return true;
				}
				return false;
			}
		}
	
		bool Package::RemoveFile( S8* strName ){
	
			return false;
		}
	
		bool Package::Exist( S8* strName ){
			FileInfoMapItr	i	= m_mapFileInfo.find(strName);
			if(i==m_mapFileInfo.end()){
				return false;
			}
			return true;
		}
	
		Data* Package::GetFileData( S8* strName ){
			FileInfoMapItr	i	= m_mapFileInfo.find(strName);
			if(i==m_mapFileInfo.end()){
				return NULL;
			}
			//从资源包中读取
			U32	uiFilePos		= i->second.m_uiFilePtr;
			U32	uiCompressSize	= i->second.m_uiCompressSize;
			U32	uiOriginalSize	= i->second.m_uiOriginalSize;
			U8* pCompressData	= new U8[uiCompressSize];
			U8*	pOriginalData	= new U8[uiOriginalSize];
			FILE* p	= (FILE*)m_pFilePtr;
			fseek(p,uiFilePos,SEEK_SET);
			fread(pCompressData,uiCompressSize,1,p);
	
			//解压
			Compress::FromLZO(pCompressData,uiCompressSize,pOriginalData,&uiOriginalSize);
			delete[] pCompressData;
	
			Data* pData	= new Data(pOriginalData,uiOriginalSize);
			delete[] pOriginalData;
			return pData;
		}
	
		File::Info* Package::GetFileInfo( S8* strName ){
			FileInfoMapItr	i	= m_mapFileInfo.find(strName);
			if(i==m_mapFileInfo.end()){
				return NULL;
			}
			return &i->second;
		}
	
		bool Package::WriteVersion( void* pFilePtr ){
			FILE* p	= (FILE*)pFilePtr;
			fwrite(&m_enVersion,sizeof(enumVersion),1,p);
			return true;
		}
	
		bool Package::ReadVersion( void* pFilePtr ){
			FILE* p	= (FILE*)pFilePtr;
			fread(&m_enVersion,sizeof(enumVersion),1,p);
			return true;
		}
	
		bool Package::WriteFileInfo( enumVersion enVer,void* pFilePtr ){
			if(pFilePtr==NULL)
				return false;
			switch(enVer){
				case	enV_1_0:{
					return WriteFileInfo_1(pFilePtr);
					break;}
				default:
					return false;
					break;
			}
			return false;
		}
	
		bool Package::WriteFileInfo_1( void* pFilePtr ){
			FILE* p	= (FILE*)pFilePtr;
			U32	uiNumFile	= m_vecFileInfo.size();
			fwrite(&m_vecFileInfo[0],sizeof(File::Info)*uiNumFile,1,p);
			fwrite(&uiNumFile,sizeof(U32),1,p);
			return true;
		}
	}
};