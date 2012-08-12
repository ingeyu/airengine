#include "AirResourceRarPackage.h"
#include "dll.hpp"

#include "AirResourceSystem.h"

namespace Air{
	
	
	
	namespace	Client{
	
		namespace	Resource{
	
			Data*	g_TempData	=	NULL;
			U32		g_TempPos	=	0;
	
			SInt PASCAL ReceivedFunction(U8*	pData,SInt iSize){
				//拷贝数据
				memcpy(&g_TempData->buff[g_TempPos],pData,iSize);
				g_TempPos+=iSize;
				return 1;
			};
	
			RarPackage::RarPackage( CAString& strName ):IPackage(strName){
				//m_Handle	=	NULL;
	#ifndef	_DEBUG
				OutputDebugStringA(strName.c_str());
				OutputDebugStringA("\n");
	#endif
			}
	
			U1 RarPackage::Create(){
				if(m_strProductName.empty())
					return	false;
	
				RAROpenArchiveData	data;
				data.ArcName	=	(char*)m_strProductName.c_str();
				data.CmtBuf		=	NULL;
				data.CmtBufSize	=	0;
				data.CmtSize	=	0;
				data.CmtState	=	0;
				data.OpenMode	=	RAR_OM_LIST;
				data.OpenResult	=	0;
	
				//打开资源包
				HANDLE	h	=	RAROpenArchive(&data);
	
	#ifndef	_DEBUG
				//RARSetPassword(h,"InfernalHell");
	#endif
	
				RARHeaderData	DataHeader;
	
				SInt	ret	=	-1;
				//循环遍历列表 查找文件
				while   ((ret=RARReadHeader(h,&DataHeader))==0){
					AString	str	=	DataHeader.FileName;
					//转化为小写
					Converter::ToLowerCase(str);
					FileInfo info;
					info.uncompressedSize	=	DataHeader.UnpSize;
					info.compressedSize		=	DataHeader.PackSize;
					m_mapFileInfo[str.c_str()]	=	info;
					ret	=	RARProcessFile(h,RAR_SKIP,NULL,NULL);
				}
	
				if(h!=NULL){
					int r		=	RARCloseArchive(h);
					h	=	NULL;
				}
	
	
				return	true;
			}
	
			U1 RarPackage::Destroy(){
				m_mapFileInfo.clear();
				return	true;
			}
	
			U32	RarPackage::Find( CAString& strName ,Data&	data){

				U32	uiSize	=	IsExist(strName);
				if(uiSize	==	0)
					return	0;
				data.ReSize(uiSize);
				g_TempData	=	&data;
				g_TempPos	=	0;

				RAROpenArchiveData	arc;
				arc.ArcName	=	(char*)m_strProductName.c_str();
				arc.CmtBuf		=	NULL;
				arc.CmtBufSize	=	0;
				arc.CmtSize		=	0;
				arc.CmtState	=	0;
				arc.OpenMode	=	RAR_OM_EXTRACT;
				arc.OpenResult	=	0;
	
				//打开资源包
				HANDLE	h	=	RAROpenArchive(&arc);
				RARSetProcessDataProc(h,ReceivedFunction);
	
	#ifndef	_DEBUG
				//RARSetPassword(h,"InfernalHell");
	#endif
	
				RARHeaderData	DataHeader;
	
				SInt	ret	=	-1;
				//循环遍历列表 查找文件
				while   ((ret=RARReadHeader(h,&DataHeader))==0)   
				{   
					AString	str	=	DataHeader.FileName;
					//转化为小写
					Converter::ToLowerCase(str);
					//在这里可以判断文件名是否正确
					if(str	!=	strName){
						//如果不是需要查找的文件 则跳过查找下一个文件
						ret	=	RARProcessFile(h,RAR_SKIP,NULL,NULL);
					}else{
						//第一个参数 填资源包句柄
						//第三四个参数为解压路径 ，前提是第二个参数为RAR_EXTRACT 然后解压(如果需要解压出来 则填入文件路径) NULL为解压到工作目标
						//第二个参数 如果只需要解压到内存中 则填RAR_TEST
						ret	=	RARProcessFile(h,RAR_TEST,NULL,NULL);
						if(h!=NULL){
							int r		=	RARCloseArchive(h);
							h	=	NULL;
						}
						return	data.size;//CombineData();
					}
				}
	
				if(h!=NULL){
					int r		=	RARCloseArchive(h);
					h	=	NULL;
				}
				return	NULL;
			}
	
	
			void RarPackage::FindWithPostfix( CAString& strPostfix,IFindFileListener* pListener ){

				g_TempData	=	new	Data;
				g_TempPos	=	0;

				RAROpenArchiveData	data;
				data.ArcName	=	(char*)m_strProductName.c_str();
				data.CmtBuf		=	NULL;
				data.CmtBufSize	=	0;
				data.CmtSize	=	0;
				data.CmtState	=	0;
				data.OpenMode	=	RAR_OM_EXTRACT;
				data.OpenResult	=	0;
	
				//打开资源包
				HANDLE	h	=	RAROpenArchive(&data);
				RARSetProcessDataProc(h,ReceivedFunction);
	
	#ifndef	_DEBUG
				//RARSetPassword(h,"InfernalHell");
	#endif
	
				RARHeaderData	DataHeader;
	
				SInt	ret	=	-1;
				//循环遍历列表 查找文件
				while   ((ret=RARReadHeader(h,&DataHeader))==0)   
				{   
					AString	strPost;
					AString	strName	=	DataHeader.FileName;
					GlobalSetting::ParsePath(DataHeader.FileName,&strPost);
					//转化为小写
					Converter::ToLowerCase(strPost);
	
					//在这里可以判断文件名是否正确
					if(strPost	!=	strPostfix){
						//如果不是需要查找的文件 则跳过查找下一个文件
						ret	=	RARProcessFile(h,RAR_SKIP,NULL,NULL);
					}else{
						g_TempData->ReSize(DataHeader.UnpSize);
						//第一个参数 填资源包句柄
						//第三四个参数为解压路径 ，前提是第二个参数为RAR_EXTRACT 然后解压(如果需要解压出来 则填入文件路径) NULL为解压到工作目标
						//第二个参数 如果只需要解压到内存中 则填RAR_TEST
						ret	=	RARProcessFile(h,RAR_TEST,NULL,NULL);
						//回调
						pListener->OnFindFile(strName,g_TempData);

					}
				}

				delete	g_TempData;
				g_TempData	=	NULL;
				g_TempPos	=	0;
	
				if(h!=NULL){
					int r		=	RARCloseArchive(h);
					h	=	NULL;
				}	
			}
	
			Data* RarPackage::CombineData(){
// 				Data*	pData	=	NULL;
// 				if(g_lstTempData.size()	==	1){
// 					std::list<Data*>::iterator	i	=	g_lstTempData.begin();
// 					pData	=	(Data*)(*i);
// 					g_uiTempDataSize	=	0;
// 					g_lstTempData.clear();
// 					return	pData;
// 				}else{
// 					pData	=	new	Data();
// 					pData->ReSize(g_uiTempDataSize);
// 					UInt	uiPos			=	0;
// 					U8*	pDataPointer		=	pData->GetBuff();
// 					std::list<Data*>::iterator	i	=	g_lstTempData.begin();
// 					for(;i!=g_lstTempData.end();i++){
// 						Data*	p	=	(Data*)(*i);
// 						memcpy(&pDataPointer[uiPos],p->GetBuff(),p->GetSize());
// 						uiPos	+=	p->GetSize();
// 						SAF_D(p);
// 					}
// 					g_uiTempDataSize	=	0;
// 					g_lstTempData.clear();
// 					return	pData;
// 				}
				return NULL;
			}
		}
	}
};