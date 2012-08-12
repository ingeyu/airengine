/*++

Copyright (c) 2005

Module Name:

    DataBase.h
    DataBase.cpp
    .\_PRIVE\Mutex.h

Abstract:

    提供一个简单的数据库访问接口

    注意:因为ADO为COM组件,所以在使用前应该调用 CoInitialize(NULL);
         结束时应该调用 CoUninitialize();

Author:

    好人(yukun1984@gmail.com) 7-Oct-2005

Revision History:

    修正一个异常处理可能导致的细微内存泄漏  14-Mar-2006
    异常处理优化掉一个无用的对象操作        27-Mar-2006

--*/

#ifndef _DB_DATA_BASE_H
#define _DB_DATA_BASE_H

#include "AirCommon.h"
//#include "AirCommonHeader.h"
#include <string>


#pragma comment(lib, "comsupp.lib")
//导入ADO的COM DLL (DLL具体路径看情况而定,可以改变)
#import "C:\Program Files\common files\system\ado\msado15.dll" no_namespace rename("EOF","EndOfFile") rename("BOF","FirstOfFile")

using std::string;
namespace Air{
	
	namespace DataBase
	{
	    class COMMON_EXPORT	CDebugOutPut
	    {
	        //用户自定义日志输出函数格式
	        typedef void (*OutPut)(const char*); 
	
	    public:
	        //设置用户自定义日志和错误处理函数地址
	        void static SetLogOut(const OutPut proc);
	        void static SetErrorOut(const OutPut proc);
	
	    protected:
	        //提供给CConnection与CRecordset访问
	        friend class CConnection;
	        friend class CRecordset;
	
	        //调用函数输出日志或错误处理
	        void static LogOut(const BSTR szText);
	        void static LogOut(const char* szText);
	
	        void static ErrOut(const BSTR szText);
	        void static ErrOut(const char* szText);
	
	    private:
	        static OutPut m_LogOut;
	        static OutPut m_ErrOut;
	    };
	
	
	    class COMMON_EXPORT CRecordset
	    {
	    public:
	        //获取字段值
	        const char* Get(const char* szField, bool bLog = false);
	
	    public:
	        //游标向后移动一次
	        bool MoveNext();
	        //游标移至最顶端
	        bool MoveFirst();
	
	    public:
	        //游标记录是否为空
	        bool IsEmpty() const;
	        //游标是否已至最后
	        bool IsEOF() const;
	        //游标是否打开
	        bool IsOpen() const;
	
	    public:
	        CRecordset();
	        CRecordset(const CRecordset &recordset);
	        CRecordset(const _RecordsetPtr &recordset);
	        virtual ~CRecordset();
	
	    public:
	        CRecordset& operator = (const CRecordset &recordset);
	
	    protected:
	        _RecordsetPtr GetRecordsetPtr()const{return m_pRecordset;}
	
	    private:
	        _RecordsetPtr m_pRecordset;
	        string m_strRet;            //返回的记录值临时存储指针
	    };
	
	    class COMMON_EXPORT CConnection
	    {
	    public:
	        //打开一个连接
	        bool Open(const char* szIP, 
	                  const char* szDBName, 
	                  const char* szUserName, 
	                  const char* szPassword);
	        
	        //直接使用连接字串
	        bool Open(const char* szConnectString);
	        
	        //使用DSN连接
	        bool Open(const char* szDSN, const char* szUserName, const char* szPassword);
	
	    public:
	        //执行SQL语句返回一个记录集
	        CRecordset Execute(const char* szSQL, VARIANT * RecordsAffected = NULL, long Options = -1);
	
	    public:
	        //检测连接是否打开
	        bool IsOpen() const;
	        //关闭连接
	        void Close();
	        
	
	    public:
	        CConnection();
	        virtual ~CConnection();
	
	    private:
	        _ConnectionPtr m_pCon;      //ADO连接类
	        string m_strConnect;        //ADO连接字串
	
	    private:
	        CConnection(const CConnection &conn);
	        CConnection& operator = (const CConnection &conn);
	    };
	};
};
#endif