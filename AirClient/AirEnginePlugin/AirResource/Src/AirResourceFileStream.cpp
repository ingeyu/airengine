// #include "AirResourceFileStream.h"
// #include "AirResourcePackageManager.h"
// 
// namespace	Air{
// 	namespace	Client{
// 		namespace	Resource{
// 
// 
// 			Air::U1 FileStream::Create(){
// 				//查找文件
// 				Data*	pData	=	PackageManager::GetSingleton()->Find(m_strProductName);
// 
// 				if(pData==NULL)
// 					return	false;
// 				
// 				if(pData->GetSize()	==	0){
// 					SAF_D(pData);
// 					return	false;
// 				}
// 				//申请空间
// 				m_Data.ReSize(pData->GetSize());
// 
// 				//拷贝数据
// 				memcpy(m_Data.GetBuff(),pData->GetBuff(),pData->GetSize());
// 
// 				SAF_D(pData);
// 
// 				return	true;
// 			}
// 		}
// 	}
// }