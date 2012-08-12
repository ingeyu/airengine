#ifndef SLKREADER_HEAD_FILE
#define SLKREADER_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"


	/*slk格式
	*	
	发现;Y，得到行号
	发现;X,得到列号
	发现;K,得到数值,数值以"\r\n"结束
	    if K"  是字符串，以"结束比如K"hello  dhdhhd" 
	    	字符串中的换行用 1b 20 3a 替换
	    else 数值
	    
	    数值以\r\n或者;结束
	    
	    ;;表示一个;
	    
	当开始新得一行时，判定
		;Y 
		;X 
			后续数字和;或者换行
		;K
			如果后续"
				则为字符串数据，
					转义:1b 20 3a  -> \r\n
					     ;;        -> ;
			
		其他：忽略，等待下一个单独的;
	 */
	
	//written by dfk[2003/10/29]
	/*
	 	使用方法：
			先调用ReadFromFile 或者 ReadFromString 解析slk信息
			然后依次调用
				//第一行是1
				GotoNextLine()
			RETURN
				//成功挑转到行
				ret_succ
				//没有这个行
				,ret_nothisline
				//读取结束
				,ret_readover
	
	
				//第一个域是1
				和 GetFieldOfLine()取得具体域的值
	 */
	#pragma pack(push,1) 
	class CFlyMemAllocer;
	//解析后，顺序读取
	/**	\brief	Excel文档读取类
	*
	*	Excel文档读取类
	*
	***/
	class COMMON_EXPORT	CSlkReader //: public CSemiAutoIntLock 
	{
	public:
		enum enumFieldType
		{
			field_int
			,field_string
			,field_float
		};
		struct SField
		{
			SField()
			{
				data.iValue = 0;
			}
			int iFieldType;
			union unionFieldData
			{
				int iValue;
				float fValue;
				char *szValue;
			}data;
		};
		
	
	private:
		typedef std::vector<SField*> vectorField;
		
		struct SLine
		{
			int iLineNo;
			vectorField vector;
		};
		typedef std::list<SLine*> listLine;
		typedef std::map<int,SLine*> mapLine;
	    
		char						m_szTest0[ 1000 ];
	    std::map<std::string,int> m_mapFiledNameToId;
		char						m_szTest1[ 1000 ];
	
		SLine *	m_pLastFindLine;
	
		listLine m_list;
		mapLine m_mapIndex;
		SLine *m_pCurGetLine;
		int		m_iMaxLineNo;
	
		
		void FreeLine(SLine*pLine);
		
		
		char *GetFieldValue( char *szString,SField &field );
	
		char* GetRowOrLineNO(char *szString,int &iValue );
	
		SLine *FindLine( int iLine,bool bAddIfNotFound = true );
		void SetValue( SLine *pLine,int iX,SField &field );
		void OutDebugLine(SLine*pLine,FILE *fp);
	
		void ClearBlankRow(void);
	public:
		CSlkReader(void);
		~CSlkReader();
		void FreeAll(void);
		bool ReadFromString( char *szString,int iSize );
		bool ReadFromFile( const char *szFile );
	
		//目前行的第 个值
		SField *GetFieldOfLine( int iFieldNo );
		int		GetFieldNumOfLine(void);
	    
	    
	
		enum enumGotoRet
		{
			//成功挑转到行
			ret_succ
			//没有这个行
			,ret_nothisline
			//读取结束
			,ret_readover
		};
		int GotoNextLine( int iLine );
	
		void OutDebugInfo(void);
	
		int	 FindFirstLineByIntField( int iFieldNo,int iValue );
		//return  -1:Not found
		int	 FindLineByIntField( int iFieldNo,int iValue );
	
		//读取整数
		bool GetIntField( int iCol,int &iValue );
		//读取string
		bool GetStringField( int iCol,std::string& pstrRetValue);
		//读取string
		bool GetStringField( int iCol,char **pstrRetValue,CFlyMemAllocer*pAllocer );
		//读取浮点
		bool GetFloatField( int iCol, float &fValue );
	
		// realrender added 2004.09.06
		// 
		int ConvHeaderToId( const char* pszCol );
		bool GetIntField( const char* pszCol,int &iValue );
		//读取string
		bool GetStringField( const char* pszCol,std::string& pstrRetValue);
		//读取string
		bool GetStringField( const char* pszCol,char **pstrRetValue,CFlyMemAllocer*pAllocer );
		//读取浮点
		bool GetFloatField( const char* pszCol, float &fValue );
	
	    void InitFiledName();
	
	    int GetFiledNameID( const char * strName );
	
	    bool GetIntFieldByName( const char* pszColName,int &iValue );
		bool GetIntFieldByName( const char* pszColName,short &shValue );
	    //读取string
	    bool GetStringFieldByName( const char* pszColName,std::string& pstrRetValue);
	    //读取string
	    bool GetStringFieldByName( const char* pszColName,char **pstrRetValue,CFlyMemAllocer*pAllocer );
	    //读取浮点
	    bool GetFloatFieldByName( const char* pszColName, float &fValue );
	
	};
	#pragma pack( pop ) 

#endif // SLKREADER_HEAD_FILE
