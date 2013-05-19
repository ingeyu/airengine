#include "AirCommonFile.h"
#include "AirCommonPackage.h"
namespace Air{
	
	namespace	Common{
	
		static SInt	g_FileCount	=	0;
	
		File::File(){
			m_uiLength	= 0;
			g_FileCount++;
			//AChar c[128];
			//sprintf(c,"File Ref Count ==%d !\n",g_FileCount);
			//OutputDebugStringA(c);
		}
	
		File::File( CAString& strName ){
			m_strName	= strName;
			m_uiLength	= 0;
			g_FileCount++;
			//AChar c[128];
			//sprintf(c,"File Ref Count ==%d !\n",g_FileCount);
			//OutputDebugStringA(c);
		}
	
		File::~File(){
			Clear();
			g_FileCount--;
			//AChar c[128];
			//sprintf(c,"File Ref Count ==%d !\n",g_FileCount);
			//OutputDebugStringA(c);
		}
	
		U1 File::Open(Package*	pPackage,enFileType	iType){
			//判断文件名是否为空
			if(m_strName.empty())
				return	false;
	
			//尝试从资源包打开
			if(pPackage!=NULL	&&	OpenFromPackage(pPackage))
				return true;
	
			//打开文件(以读取 和 二进制 方式)
			FILE*	f	=	NULL;
			AString	strOption;
			switch(iType){
				case	enBinary:{
					strOption	=	"rb";
					break;}
				case	enASCII:{
					strOption	=	"r";
					break;}
				default:{
					strOption	=	"rb";
					break;}
			}
			fopen_s(&f,m_strName.c_str(),strOption.c_str());
			if(f==NULL)
				return	false;
			//将文件指针 移动到文件尾
			fseek(f,0,SEEK_END);
			//获取当前文件指针的位置
			U32	uiLength	=	ftell(f);
			//将文件指针 移动到文件头
			fseek(f,0,SEEK_SET);
			//判断文件内容长度
			if(uiLength	== 0)
				return false;
			Data*	pData		=	new	Data;
			//申请内存空间
			U8*	pBuff	=	pData->ReSize(uiLength);
			//读取文件数据
			fread(pBuff,uiLength,1,f);
			//关闭文件指针
			fclose(f);
			//存入数据
			PushData(pData);
	
			//SAF_D(pData);
			
			return	true;
		}
	
		U1 File::Save(Package*	pPackage){
			//判断文件名是否为空
			if(m_strName.empty())
				return	false;
	
			//获取数据
			Data*	pData	= GetData();
			if(pData->IsNull())
				return false;
	
			//打开文件(以写入 和 二进制 方式)
			FILE*	f	=	NULL;
			fopen_s(&f,m_strName.c_str(),"wb");
			if(f==NULL)
				return	false;
	
			//向文件写入数据
			fwrite(pData->GetBuff(),pData->GetSize(),1,f);
			fclose(f);
			return	true;
		}
	
		U1 File::Save( CAString& strName,U8* pData,U32 uiSize ){
			if(strName.empty()	||	pData==NULL	||	uiSize	==	0)
				return	false;
			FILE*	pFile	=	fopen(strName.c_str(),"wb");
			if(pFile==NULL)
				return	false;
			fwrite(pData,uiSize,1,pFile);
			fclose(pFile);
			return	true;
		}
	
		U1 File::Save( CAString& strName,AString& strContent ){
			if(strName.empty()	||	strContent.empty())
				return	false;
			FILE*	pFile	=	fopen(strName.c_str(),"w");
			if(pFile==NULL)
				return	false;
			fwrite(strContent.c_str(),strContent.size(),1,pFile);
			fclose(pFile);
			return	true;
		}
		U1 File::PushData( Data* pData ){
			if(pData==NULL)
				return false;
			m_lstData.push_back(pData);
			m_uiLength	+=	pData->GetSize();
			return true;
		}
	
		U1 File::Clear(){
			DataListItr	i	= m_lstData.begin();
			for(;i!=m_lstData.end();i++){
				Data* pData	= (Data*)(*i);
				SAF_D(pData);
			}
			m_lstData.clear();
			m_uiLength	= NULL;
			return true;
		}
	
		Data* File::GetData(){
			if(m_uiLength==0)
				return	NULL;
			if(m_lstData.size()==1){
				DataListItr	itr	=	m_lstData.begin();
				return (Data*)(*itr);
			}
			Data*	pData	= new Data;
			//申请空间
			U8*	pBuff	= pData->ReSize(m_uiLength);
			//记录数据块 已写入数据的结束位置
			U32	uiBuffPos	= 0;
	
			//遍历数据列表
			DataListItr	i	= m_lstData.begin();
			for(;i!=m_lstData.end();i++){
				Data*	pTempData	= (Data*)(*i);
				if(pTempData==NULL)
					continue;
				if(pTempData->IsNull())
					continue;
				//拷贝至缓冲区
				memcpy(&pBuff[uiBuffPos],pTempData->GetBuff(),pTempData->GetSize());
				//更新数据缓冲区结束位置
				uiBuffPos	= pTempData->GetSize();
				SAF_D(pTempData);
				//迭代器置空
				*i	=	NULL;
			}
			//清空数据列表
			m_lstData.clear();
			//放入新的连续的数据块
			m_lstData.push_back(pData);
			return	pData;
		}
	
		U1 File::SaveAs( CAString& strAnotherName ){
			if(strAnotherName.empty())
				return false;
			ReName(strAnotherName);
			return	Save();
		}
	
		U1 File::OpenFromPackage( Package* pPackage ){
			if(m_strName.empty())
				return false;
			if(pPackage==NULL)
				return false;
			Data*	pData	= pPackage->GetFileData((S8*)m_strName.c_str());
			if(pData==NULL)
				return false;
			m_lstData.push_back(pData);
			m_uiLength	+= pData->GetSize();
			return	true;
		}
	
		U1 File::SaveToPackage( Package* pPackage ){
			if(!IsValid())
				return false;
			if(pPackage==NULL)
				return false;
	
			Data*	pData	= GetData();
			return	pPackage->AddFileFromMemery((S8*)m_strName.c_str(),pData->GetBuff(),pData->GetSize());
		}
	
		U1 File::Load( CAString& strName,Data& data ){
			if(strName.empty())
				return	false;
			FILE*	f	=	fopen(strName.c_str(),"rb");
			if(f==NULL)
				return	false;
			//将文件指针 移动到文件尾
			fseek(f,0,SEEK_END);
			//获取当前文件指针的位置
			U32 uiSize	=	ftell(f);
			//将文件指针 移动到文件头
			fseek(f,0,SEEK_SET);
			//判断文件内容长度
			if(uiSize	== 0)
				return false;

			data.ReSize(uiSize);
	
			fread(data.buff,uiSize,1,f);
			fclose(f);
	
			return	true;
		}

		Air::U1 File::FolderTraversal( CAString& strPath,TraversalCallBack* pCB ){

			//find(char * lpPath)
			{
				AChar szFind[MAX_PATH];
				WIN32_FIND_DATAA FindFileData;

				strcpy(szFind,strPath.c_str());
				strcat(szFind,"*.*");

				HANDLE hFind=::FindFirstFileA(szFind,&FindFileData);
				if(INVALID_HANDLE_VALUE == hFind)
					return	false;

				while(TRUE)
				{
					if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if(strcmp(FindFileData.cFileName,".")!=0&&strcmp(FindFileData.cFileName,"..")!=0&&strcmp(FindFileData.cFileName,".svn")!=0)
						{
							AChar szFile[MAX_PATH];
							strcpy(szFile,strPath.c_str());
							strcat(szFile,FindFileData.cFileName);
							strcat(szFile,"/");
							if(pCB!=NULL){
								pCB->OnFindDirectory(szFile);
							}
							FolderTraversal(szFile,pCB);
						}
					}
					else
					{
						if(pCB!=NULL){
							pCB->OnFindFile(strPath+FindFileData.cFileName);
						}
					}
					if(!FindNextFileA(hFind,&FindFileData))
						break;
				}
				FindClose(hFind);
			}

			return	true;
		}
	}
};