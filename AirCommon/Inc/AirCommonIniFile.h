//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/22
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  IniFile.h
 \note     
       
 \attention:
			配置文件类INI
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONINIFILE_HEAD_FILE
#define COMMONINIFILE_HEAD_FILE


#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonFile.h"
namespace Air{
	
	namespace Common{
	
	#ifndef MAX_NAME
	#define MAX_NAME 256
	#endif
	
	#ifndef READ_FILE
	#define READ_FILE(strName,strFile)	\
		{\
			FILE* file = fopen(strName,"rb");\
			fseek(file,0,SEEK_END);\
			int size = ftell(file) - 1;\
			fseek(file,0,SEEK_SET);\
			char* str = new char[size+1];\
			str[size]='\0';\
			fread(str,size,1,file);\
			strFile = str;\
			delete str;\
			fclose(file);\
		}
	
	#endif
	
	#ifndef WRITE_LINE
	#define WRITE_LINE(str,file)	\
		{\
			AString s = AString(str) + AString("\n");\
			fwrite((void*)s.c_str(),s.size(),1,file);\
		}
	#endif
	
	#ifndef WRITE_STR
	#define WRITE_STR
	#endif

	
		/** \brief 配置文件类
		*
		*	主要用于基本配置文件的解析
		*	而不依赖XML或者其他的组件
		*
		****/
	
		class COMMON_EXPORT	IniFile	:	public	MemoryObject{
		public:
	
		public:
			IniFile();
			virtual	~IniFile();
			/**	\brief	载入文件
			*   
			*	@remarks 	载入文件 并解析到链表中以供查询
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileName
			*	@note
			*
			**/
			bool LoadFile(CAString& strFileName);
			/**	\brief	从内存中载入
			*   
			*	@remarks 	从内存中载入
			*	@see		IniFile
			*	@return   	U1
			*	@param		AString strContent
			*	@note
			*
			**/
			U1	LoadFileFromMemory(U8*	pData,U32	uiSize);
			U1	LoadFileFromMemory(Data*	pData){
				if(pData==NULL)
					return	false;
				return	LoadFileFromMemory(pData->buff,pData->size);
			};
			/**	\brief	从字符串载入
			*   
			*	@remarks 	从字符串载入
			*	@see		IniFile
			*	@return   	U1
			*	@param		CAString& str
			*	@note
			*
			**/
			U1	LoadFileFromString(CAString&	str);
			/**	\brief	新建文件
			*   
			*	@remarks 	新建文件不解析
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileName
			*	@note
			*
			**/
			bool NewFile(AString strFileName);
			/**	\brief	设置文件内容
			*   
			*	@remarks 	在已有文件的基础上设置内容
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileContent
			*	@note
			*
			**/
			bool Replace(AString strFileContent);
			/**	\brief	追加一行
			*   
			*	@remarks 	在文件尾追加一行
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strStringLine
			*	@note
			*
			**/
			bool AddLine(AString strStringLine);
			/**	\brief	修改属性
			*   
			*	@remarks 	修改其对应分类 对应索引 对应索引序号的内容
			*	@see		IniFile
			*	@return   	bool
			*	@param		char * strSortName
			*	@param		char * strName
			*	@param		char * strValue
			*	@param		int iIndex
			*	@note
			*
			**/
			bool Set(const char* strSortName,const char* strName,const char* strValue,int iIndex = 0);
			/**	\brief	保存
			*   
			*	@remarks 	保存文件内容
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileName
			*	@note
			*
			**/
			bool Save(AString strFileName = "");
		private:
			/**	\brief	解析
			*   
			*	@remarks 	解析整个文件内容
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strContent
			*	@note
			*
			**/
			bool Parse(S8*	strContent,UInt uiSize);
			/**	\brief	解析行
			*   
			*	@remarks 	解析文本中的行
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strLine
			*	@note
			*
			**/
			bool ParseLine(AString strLine);
			/**	\brief	解析主分类
			*   
			*	@remarks 	解析分类名   标示符 [Sort]  []
			*	@see		IniFile
			*	@return   	AString
			*	@param		AString strSort
			*	@note
			*
			**/
			AString ParseSort(AString strSort);
			/**	\brief	解析配置信息
			*   
			*	@remarks 	解析具体的信息  标示符 Name=Value  =
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strSource
			*	@param		AString & strName
			*	@param		AString & strValue
			*	@note
			*
			**/
			bool ParseNameAndValue(AString strSource,AString &strName,AString &strValue);
		public:
			/**	\brief	查询
			*   
			*	@remarks 	通过分类名 索引名 索引序号 SortName Name Index
			*	@see		IniFile
			*	@return   	AString
			*	@param		const char * strSort
			*	@param		const char * strName
			*	@param		int iIndex
			*	@note
			*
			**/
			AString Get(const char* strSort,const char* strName,UInt iIndex = 0);
			/**	\brief	查询索引个数
			*   
			*	@remarks 	根据分类名 索引名 查询索引个数
			*	@see		IniFile
			*	@return   	int
			*	@param		const char * strSort
			*	@param		const char * strName
			*	@note
			*
			**/
			int GetCount(const char* strSort,const char* strName);
			/**	\brief	查询分类
			*   
			*	@remarks 	查询是否存在该名的分类  如果没有返回NULL
			*	@see		IniFile
			*	@return   	SortMap*
			*	@param		const char * strSort
			*	@note
			*
			**/
			SortMap* GetSort(const char* strSort);
			/**	\brief	查询索引
			*   
			*	@remarks 	根据索引名 在分类列表中查询索引  如果存在则返回索引列表
			*	@see		IniFile
			*	@return   	StringList*
			*	@param		const char * strName
			*	@param		SortMap * pMap
			*	@note
			*
			**/
			StringVector* GetStringList(const char* strName,SortMap* pMap);
			/**	\brief	查询索引
			*   
			*	@remarks 	根据索引名 在分类列表中查询索引  如果存在则返回索引列表
			*	@see		IniFile
			*	@return   	StringList*
			*	@param		const char * strName
			*	@param		const char* strSort
			*	@note
			*
			**/
			StringVector* GetStringList(const char* strName,const char* strSort);

			SortList&		GetSortMap(){
				return	m_lstSort;
			};
		private:
	#ifdef _DEBUG
			AString						m_strFileContent;		///<	配置文件内容	用于调试
	#endif
			AString						m_strFileName;			///<	配置文件名
			SortList					m_lstSort;				///<	信息主分类
		};
	
	
	};
};


#endif