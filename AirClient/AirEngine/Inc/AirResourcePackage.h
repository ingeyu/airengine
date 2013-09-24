/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/04/23
 \version   ver 0.6.0.0
 \filepath  f:\EngineSource\Air\AirClient\AirEnginePlugin\AirResource
 \filename  ResourceFolderPackage.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRRESOURCEPACKAGE_HEAD_FILE
#define AIRRESOURCEPACKAGE_HEAD_FILE

#include "AirEngineHeader.h"

namespace	Air{
	namespace Engine{
	
		namespace	Resource{
			struct FileInfo{
				/// Compressed size
				size_t compressedSize;
				/// Uncompressed size
				size_t uncompressedSize;
			};
			typedef STD_HASHMAP<AString,FileInfo> FileInfoMap;

			interface FindFileCallback{
				virtual	U1	OnFindFile(CAString&	strName,Data*	pData)=	NULL;
			};
			/**	\brief	文件夹
			*
			*	文件夹
			*
			***/
			class	ENGINE_EXPORT	Package:
				public	IProduct{
			public:
				static AString ProductTypeName;
				Package(CAString&	strName);

				virtual	U1	Create();
				virtual	U1	Destroy();

				/**	\brief	查找文件
				*	
				*	@remarks 	查找文件
				*	@see		ZipPackage
				*	@return   	Data*
				*	@param		AString & filename
				*	@note
				*
				**/
				virtual	U32			Find(CAString&	strName,Data&	data);
				virtual	U1			GetFileModifyTime( CAString& strFileName,FILETIME* p );
				U32					FindWithFullPath(CAString& filename,Data&	data);
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
				virtual	void		FindWithPostfix(CAString&	strPostfix,FindFileCallback*	pCB);
			public:	
				/**	\brief	查询资源是否存在
				*   
				*	@remarks 	查询资源是否存在
				*	@see		Package
				*	@return   	U32
				*	@param		AString & strName
				*	@note
				*
				**/
				virtual	U32		IsExist(CAString&	strName);;
	
			protected:
				AString				m_strTempPostfix;
				AString				m_strRealPath;
				FileInfoMap			m_mapFileInfo;
			};

		}
		typedef	STD_LIST<Resource::Package*>	PackageList;
	};//end of	namespace	Client
};//end of namespace Air
#endif // RESOURCEFOLDERPACKAGE_HEAD_FILE