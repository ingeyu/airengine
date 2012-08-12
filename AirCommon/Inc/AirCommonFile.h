//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  FileStream.h
 \note     
       
 \attention:
			文件类	包括从文件读取，文件夹保存 
					资源包读取，资源包保存

					支持先保存在内存
					再整理
					最后保存到指定位置
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONFILE_HEAD_FILE
#define COMMONFILE_HEAD_FILE

#include "AirCommonData.h"

namespace Air{
	
	enum	enFileType{
		enBinary,
		enASCII,
	};
	namespace Common{
	
		class Package;


	
	
		/**	\brief	文件流
		*
		*	文件流
		*
		***/
		class COMMON_EXPORT	File{
		public:
			class COMMON_EXPORT	Info{
			public:
				Info(){
					memset(m_strName,0,MAX_NAME);
					_ZERO(m_uiFilePtr);
					_ZERO(m_uiCompressSize);
					_ZERO(m_uiOriginalSize);
				}
				Info(S8* strName,U32 uiFilePtr,U32 uiSize,U32	uiCompressSize){
					strcpy_s(m_strName,MAX_NAME,strName);
					m_uiFilePtr			= uiFilePtr;
					m_uiOriginalSize	= uiSize;
					m_uiCompressSize	= m_uiCompressSize;
				}
				/**	\brief	获取名字
				*   
				*	@remarks 	获取名字
				*	@see		Info
				*	@return   	char*
				*	@note
				*
				**/
				inline S8*		GetFullName(){
					return m_strName;
				};
				/**	\brief	获取名字
				*   
				*	@remarks 	获取名字
				*	@see		Info
				*	@return   	char*
				*	@note
				*
				**/
				inline S8*		GetName(){
					UInt	iLength	= strlen(m_strName);
					for(UInt i=iLength-1;i>=0;i--){
						if(m_strName[i] == '\\' || m_strName[i] == '/'){
							return &m_strName[i+1];
						}
					}
					return m_strName;
				};
				/**	\brief	设置在资源包中的新位置
				*   
				*	@remarks 	设置在资源包中的新位置
				*	@see		Info
				*	@return   	void
				*	@param		U32 FilePtr
				*	@note
				*
				**/
				inline	void	SetNewPosition(U32 FilePtr){
					m_uiFilePtr	= FilePtr;
				}
				/**	\brief	设置在数据包中的偏移量
				*   
				*	@remarks 	设置在数据包中的偏移量
				*	@see		Info
				*	@return   	void
				*	@param		U32 FilePtrOffset
				*	@note
				*
				**/
				inline	void	SetPositionOffset(U32 FilePtrOffset){
					m_uiFilePtr	+=	FilePtrOffset;
				}
				S8			m_strName[MAX_NAME];///<	文件名 包含路径
				U32			m_uiOriginalSize;	///<	原始大小
				U32			m_uiCompressSize;	///<	压缩之后的大小
				U32			m_uiFilePtr;		///<	文件数据在资源包的位置
			};
		public:
			File();
			File(CAString&	strName);
			virtual ~File();
	
			/**	\brief	从资源包中打开
			*   
			*	@remarks 	
			*	@see		File
			*	@return   	U1
			*	@param		Package * pPackage
			*	@note
			*
			**/
			U1		OpenFromPackage(Package*	pPackage);
			/**	\brief	保存到资源包
			*   
			*	@remarks 	保存到资源包
			*	@see		File
			*	@return   	U1
			*	@param		Package * pPackage
			*	@note
			*
			**/
			U1		SaveToPackage(Package*	pPackage);
	
			/**	\brief	打开文件
			*   
			*	@remarks 	打开文件
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			U1		Open(Package*	pPackage	= NULL,enFileType	iType	=	enBinary);
			/**	\brief	保存文件
			*   
			*	@remarks 	保存文件
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			U1		Save(Package*	pPackage	= NULL);
			/**	\brief	另存为
			*   
			*	@remarks 	另存为
			*	@see		File
			*	@return   	U1
			*	@param		CAString& strAnotherName
			*	@note
			*
			**/
			U1		SaveAs(CAString&	strAnotherName);
			/**	\brief	获取数据
			*   
			*	@remarks 	注意：调用此函数将会整合数据为一个连续的内存块
			*	@see		File
			*	@return   	Data*
			*	@note
			*
			**/
			Data*	GetData();
			/**	\brief	存入数据
			*   
			*	@remarks 	注意：这里的数据时零碎的，由std::list来存储而已，只有调用GetData才会整合
			*	@see		File
			*	@return   	U1
			*	@param		Data * pData
			*	@note
			*
			**/
			U1		PushData(Data* pData);
			/**	\brief	判断文件名是否有效
			*   
			*	@remarks 	判断文件名是否有效
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		NameIsValid(){return m_strName.empty();};
			/**	\brief	判断文件流是否有效
			*   
			*	@remarks 	判断文件名  并判断是否有数据
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsValid(){return	NameIsValid() && m_uiLength > 0;};
			/**	\brief	重命名
			*   
			*	@remarks 	重命名
			*	@see		File
			*	@return   	void
			*	@param		CAString& strName
			*	@note
			*
			**/
			inline	void	ReName(CAString&	strName){m_strName	= strName;};
			/**	\brief	清理数据
			*   
			*	@remarks 	清理数据
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			U1		Clear();
			
	
			/**	\brief	存入数据
			*   
			*	@remarks 	存入数据
			*	@see		File
			*	@return   	bool
			*	@param		T_Type * p
			*	@note
			*
			**/
			template	<typename	T_Type>
			bool	Push(T_Type*	p){
				if(p==NULL)
					return	false;
				return	PushData(new	Data(p));
			};
	
			/**	\brief	加载文件
			*   
			*	@remarks 	加载文件 从文件夹
			*	@see		File
			*	@return   	U1
			*	@param		CAString& strName
			*	@param		U8 * & pData
			*	@param		U32 & uiSize
			*	@note
			*
			**/
			static	U1	Load(CAString& strName,U8*&	pData,U32& uiSize);
			/**	\brief	保存文件
			*   
			*	@remarks 	保存文件到文件夹 二进制文件
			*	@see		File
			*	@return   	U1
			*	@param		AString strName
			*	@param		U8 * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			static	U1	Save(CAString& strName,U8*	pData,U32 uiSize);
			/**	\brief	保存文件
			*   
			*	@remarks 	保存文件 保存明文字符串
			*	@see		File
			*	@return   	U1
			*	@param		AString strName
			*	@param		AString & strContent
			*	@note
			*
			**/
			static	U1	Save(CAString& strName,AString&	strContent);

			/**	\brief	遍历回调
			*
			*	遍历回调
			*
			***/
			class	TraversalCallBack{
			public:
				/**	\brief	当查找到文件之后
				*   
				*	@remarks 	当查找到文件之后
				*	@see		TraversalCallBack
				*	@return   	Air::U1
				*	@param		CAString & strName
				*	@note
				*
				**/
				virtual	U1	OnFindFile(CAString&	strName)		=	NULL;
				/**	\brief	当查找到文件夹之后
				*   
				*	@remarks 	当查找到文件夹之后
				*	@see		TraversalCallBack
				*	@return   	Air::U1
				*	@param		CAString & strName
				*	@note
				*
				**/
				virtual	U1	OnFindDirectory(CAString&	strName)	=	NULL;
			};
	
			/**	\brief	文件夹遍历
			*   
			*	@remarks 	
			*	@see		File
			*	@return   	Air::U1
			*	@param		CAString & strPath
			*	@param		TraversalCallBack * pCB
			*	@note
			*
			**/
			static	U1	FolderTraversal(CAString&	strPath,TraversalCallBack*	pCB);
		protected:
	
		private:
			AString		m_strName;			///<	名字
			U32			m_uiLength;			///<	长度
			DataList	m_lstData;			///<	数据列表
		};
	
	};
};
#endif // FILESTREAM_HEAD_FILE