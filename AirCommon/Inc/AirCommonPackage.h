//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Package.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONPACKAGE_HEAD_FILE
#define COMMONPACKAGE_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonFile.h"


namespace Air{
	
	namespace Common{
		class COMMON_EXPORT	Package	:	public	MemoryObject{
		public:
			enum	enumVersion{
				enUnKnown,			//位置版本
				enV_1_0,			//1版本
				enMaxVersion		//最大版本号
			};
			typedef	stdext::hash_map<AString,File::Info>				FileInfoMap;
			typedef stdext::hash_map<AString,File::Info>::iterator		FileInfoMapItr;
			typedef stdext::hash_map<AString,File::Info>::value_type	FileInfoMapPair;
	
			typedef	std::vector<File::Info>									FileInfoVector;
			typedef	std::vector<File::Info>::iterator						FileInfoVectorItr;
	
	
			Package();
			virtual	~Package();
	
			/**	\brief	载入资源包信息
			*   
			*	@remarks 	载入资源包信息
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strPackageName
			*	@note
			*
			**/
			virtual	bool			Load(S8*	strPackageName);
			/**	\brief	新建资源包
			*   
			*	@remarks 	新建资源包
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strPackageName
			*	@note
			*
			**/
			virtual	bool			New(S8*		strPackageName);
			/**	\brief	添加资源
			*   
			*	@remarks 	添加资源
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	bool			AddFile(S8*	strName);
			/**	\brief	从内存中添加资源
			*   
			*	@remarks 	从内存中添加资源
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@param		U8 * pData
			*	@param		U32 uiDataSize
			*	@note
			*
			**/
			virtual	bool			AddFileFromMemery(S8*	strName,U8*	pData,U32	uiDataSize);
			/**	\brief	移除资源
			*   
			*	@remarks 	移除资源
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual bool			RemoveFile(S8*	strName);
			//virtual bool			AddFileList();
			//virtual	bool			MegrePackage(S8*	strPackageName);
			/**	\brief	卸载索引信息
			*   
			*	@remarks 	卸载索引信息
			*	@see		Package
			*	@return   	void
			*	@note
			*
			**/
			virtual	void			UnLoad();
	
			/**	\brief	检测资源是否存在
			*   
			*	@remarks 	检测资源是否存在
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	bool			Exist(S8*	strName);
			/**	\brief	获取资源数据
			*   
			*	@remarks 	获取资源数据
			*	@see		Package
			*	@return   	Data*
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	Data*		GetFileData(S8*	strName);
			/**	\brief	获取资源信息
			*   
			*	@remarks 	获取资源信息
			*	@see		Package
			*	@return   	File::Info*
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	File::Info*		GetFileInfo(S8*	strName);
		private:
			/**	\brief	检查版本信息
			*   
			*	@remarks 	检测是否是支持的版本
			*	@see		Package
			*	@return   	bool
			*	@param		enumVersion enVer
			*	@note
			*
			**/
			bool	CheckVersion(enumVersion	enVer);
			/**	\brief	载入资源列表信息
			*   
			*	@remarks 	载入资源列表信息
			*	@see		Package
			*	@return   	bool
			*	@param		enumVersion enVer
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	LoadFileInfo(enumVersion	enVer,void*	pFilePtr);
			/**	\brief	载入资源列表信息1（代表版本号）
			*   
			*	@remarks 	载入资源列表信息1（代表版本号）
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	LoadFileInfo_1(void*	pFilePtr);
			/**	\brief	写入资源列表信息
			*   
			*	@remarks 	写入资源列表信息
			*	@see		Package
			*	@return   	bool
			*	@param		enumVersion enVer
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	WriteFileInfo(enumVersion	enVer,void*	pFilePtr);
			/**	\brief	写入资源列表信息1（代表版本号）
			*   
			*	@remarks 	写入资源列表信息1（代表版本号）
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	WriteFileInfo_1(void*	pFilePtr);
			/**	\brief	获取资源数据的结束位置
			*   
			*	@remarks 	获取资源数据的结束位置
			*	@see		Package
			*	@return   	U32
			*	@param		enumVersion enVer
			*	@note
			*
			**/
			U32		GetDataEndPosition(enumVersion enVer);
			/**	\brief	获取资源结束位置
			*   
			*	@remarks 	获取资源结束位置
			*	@see		Package
			*	@return   	U32
			*	@note
			*
			**/
			U32		GetDataEndPosition_1();
	
			/**	\brief	写入版本信息1（代表版本号）
			*   
			*	@remarks 	写入版本信息1（代表版本号）
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	WriteVersion(void*	pFilePtr);
			/**	\brief	读取版本信息
			*   
			*	@remarks 	读取版本信息
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	ReadVersion(void*	pFilePtr);
	
		private:
			FileInfoMap				m_mapFileInfo;					///<	用于文件快速索引	搜索
			FileInfoVector			m_vecFileInfo;					///<	记录文件顺序
			enumVersion				m_enVersion;					///<	资源包版本
			U32						m_uiSize;						///<	资源包总大小
			void*					m_pFilePtr;						///<	文件指针
		};
		
	
	};
};
#endif // PACKAGE_HEAD_FILE