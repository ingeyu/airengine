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

//#include "stdafx.h"
#include "AirDataBase.h"
//#include ".\_PRIVE\Mutex.h"
namespace Air{
	
	using DataBase::CConnection;
	using DataBase::CRecordset;
	using DataBase::CDebugOutPut;
	
	
	//////////////////////////////////////////////////////////////
	CDebugOutPut::OutPut CDebugOutPut::m_ErrOut = NULL;
	CDebugOutPut::OutPut CDebugOutPut::m_LogOut = NULL;
	
	void CDebugOutPut::SetLogOut(const CDebugOutPut::OutPut proc)
	{
	// #ifdef _MT
	//     CAutoIntLock lock;
	// #endif
	    m_LogOut = proc;
	}
	
	void CDebugOutPut::SetErrorOut(const CDebugOutPut::OutPut proc)
	{
	// #ifdef _MT
	//     CAutoIntLock lock;
	// #endif
	    m_ErrOut = proc;
	}
	
	void CDebugOutPut::LogOut(const BSTR szText)
	{
	    if (m_LogOut!=NULL)
	    {
	        static char szBuff[40000] = {0};
	        WideCharToMultiByte(CP_ACP, 0, szText, -1, szBuff, sizeof(szBuff), NULL, NULL);
	        m_LogOut(szBuff);
	    }
	}
	
	void CDebugOutPut::ErrOut(const BSTR szText)
	{
	    if (m_ErrOut!=NULL)
	    {
	        static char szBuff[40000] = {0};
	        WideCharToMultiByte(CP_ACP, 0, szText, -1, szBuff, sizeof(szBuff), NULL, NULL);
	        m_ErrOut(szBuff);
	    }
	}
	
	void CDebugOutPut::LogOut(const char* szText)
	{
	    if (m_LogOut!=NULL)
	    {
	        m_LogOut(szText);
	    }
	}
	
	void CDebugOutPut::ErrOut(const char* szText)
	{
	    if (m_ErrOut!=NULL)
	    {
	        m_ErrOut(szText);
	    }
	}
	
	/////////////////////////////////////////////////////////
	
	
	
	////////////////////////////////////////////////////////
	CConnection::CConnection()
	{
	    m_pCon.CreateInstance(/*__uuidof(Connection)*/"ADODB.Connection");
	}
	
	CConnection::CConnection(const CConnection&)
	{
	//    防止被vector等容器包含时带来的问题
	    m_pCon.CreateInstance(/*__uuidof(Connection)*/"ADODB.Connection");
	}
	
	CConnection& CConnection::operator = (const CConnection&)
	{
	    return *this;
	}
	
	CConnection::~CConnection()
	{
	    if (m_pCon != NULL)
	    {
	        if (IsOpen())
	        {
	            Close();
	        }
	//        m_pCon->Release();
	    }
	}
	
	bool CConnection::IsOpen() const
	{
	    try
	    {
	        return (m_pCon != NULL && (m_pCon->State & adStateOpen));
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(m_strConnect.c_str());
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	        return false;
	    }
	}
	
	void CConnection::Close()
	{
	    try
	    {
	        if (m_pCon != NULL && IsOpen())
	        {
	            m_pCon->Close();
	        }
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(m_strConnect.c_str());
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	    }
	}
	
	//由用户提供普通信息进行设置连接字串
	bool CConnection::Open(const char* szIP, 
	                       const char* szDBName, 
	                       const char* szUserName, 
	                       const char* szPassword)
	{
	    if (szIP==NULL || strlen(szIP)==0 || 
	        szDBName==NULL || strlen(szDBName)==0 || 
	        szUserName==NULL || strlen(szUserName)==0 ||
	        szPassword==NULL/* || strlen(szPassword)==0*/)      //允许密码为空
	    {
	        return false;
	    }
	
	    std::string strConn;
	
	    strConn="Driver=SQL Server;Server=";
	    strConn+=szIP;
		strConn+=";Database=";
		strConn+=szDBName;
		strConn+=";UID=";
	    strConn+=szUserName;
	    strConn+=";PWD=";
		strConn+=szPassword;
	
	    //调用连接字串函数连接
	    return Open(strConn.c_str());
	}
	
	//由用户自定义连接字串进行连接
	bool CConnection::Open(const char* szConnectString)
	{
	// #ifdef _MT
	//     CAutoIntLock lock;
	// #endif
	    if (szConnectString==NULL || strlen(szConnectString)==0)
	    {
	        return false;
	    }
	
	    m_strConnect = szConnectString;
	
	    try
	    {
	        if (m_pCon==NULL)
	        {
	            m_pCon.CreateInstance(__uuidof(Connection));
	        }
	        if (m_pCon->GetState() != 0)
	        {
	            m_pCon->Close();
	        }
	        CDebugOutPut::LogOut(m_strConnect.c_str());
	
	        HRESULT hRet = m_pCon->Open(m_strConnect.c_str(), "", "", -1);
	        if (SUCCEEDED(hRet))
	        {
	            CDebugOutPut::LogOut("连接成功");
	            return true;
	        }
	        else
	        {
	            CDebugOutPut::LogOut("连接失败");
	            return false;
	        }
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(m_strConnect.c_str());
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	
	        return false;
	    }
	}
	
	bool CConnection::Open(const char* szDSN, const char* szUserName, const char* szPassword)
	{
	    if (szDSN==NULL || strlen(szDSN)==0 ||
	        szUserName==NULL || strlen(szUserName)==0 ||
	        szPassword==NULL)
	    {
	        return false;
	    }
	    std::string strConn;
	
	    strConn = "DSN=";
	    strConn += szDSN;
	    strConn += ";UID=";
	    strConn += szUserName;
	    strConn += ";PWD=";
	    strConn += szPassword;
	
	    //调用连接字串函数连接
	    return Open(strConn.c_str());
	}
	
	/////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	/////////////////////////////////////////////////////////////////////////
	//执行SQL语句返回一个记录集
	CRecordset CConnection::Execute(const char* szSQL, VARIANT * RecordsAffected, long Options)
	{
	    CDebugOutPut::LogOut(szSQL);
	
	    try
	    {
	        _RecordsetPtr recordset = m_pCon->Execute(_bstr_t(szSQL), RecordsAffected, Options);
			CDebugOutPut::LogOut("执行完成");
	        return CRecordset(recordset);
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(szSQL);
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	
	        //重连
	        Open(m_strConnect.c_str());
	
	//        throw e;
	        return NULL;
	    }
	}
	
	CRecordset::CRecordset()
	{
	//    m_pRecordset.CreateInstance(__uuidof(Recordset));
	}
	
	CRecordset::CRecordset(const CRecordset&)
	{
	//    防止被vector等容器包含时带来的问题
	//    m_pRecordset.CreateInstance(__uuidof(Recordset));
	}
	        
	CRecordset::CRecordset(const _RecordsetPtr &recordset)
	{
	    m_pRecordset = recordset;
	}
	
	CRecordset& CRecordset::operator = (const CRecordset &recordset)
	{
	    m_pRecordset = recordset.GetRecordsetPtr();
	    return *this;
	}
	
	CRecordset::~CRecordset()
	{
	//    m_pRecordset.Release();
	}
	
	const char* CRecordset::Get(const char* szField, bool bLog)
	{
	    static char szBuff[4096];
	    try
	    {
	        _variant_t tmp;
	        _bstr_t tmp2;
	        tmp = m_pRecordset->GetCollect(szField);
	        if (tmp.vt==VT_NULL)
	        {
	            return NULL;
	        }
	        tmp2 = tmp;
	        char* tmp3 = _com_util::ConvertBSTRToString(tmp2);
	        m_strRet = tmp3;
	        delete [] tmp3;
	        tmp3 = NULL;
	
	        if (bLog)
	        {
	            _snprintf(szBuff, sizeof(szBuff)-1, "获取字段：%s", szField);
	            CDebugOutPut::LogOut(szBuff);
	            CDebugOutPut::LogOut(m_strRet.c_str());
	        }
	        return m_strRet.c_str();
	    }
	    catch (_com_error &e)
	    {
	        _snprintf(szBuff, sizeof(szBuff)-1, "获取字段：%s", szField);
	        CDebugOutPut::ErrOut(szBuff);
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	        return NULL;
	    }
	}
	
	bool CRecordset::MoveNext()
	{
	    try
	    {
	        return SUCCEEDED(m_pRecordset->MoveNext());
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	        return false;
	    }
	}
	
	//游标向前移动
	bool CRecordset::MoveFirst()
	{
	    try
	    {
	        return SUCCEEDED(m_pRecordset->MoveFirst());
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	        return false;
	    }
	}
	
	//返回记录集内是否为空
	//当发生错误时,返回为true.
	bool CRecordset::IsEmpty() const
	{
	    try
	    {
	        if (m_pRecordset->GetFirstOfFile() && m_pRecordset->GetEndOfFile())
	        {
	            return true;
	        }
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	        return true;
	    }
	    return false;
	}
	
	bool CRecordset::IsEOF() const
	{
	    try
	    {
	//        //暂时将警告等级设置为2,忽略bool强制类型转换警告
	//        #pragma warning (push, 2)
	//        return static_cast<bool>(m_pRecordset->GetEndOfFile());
	//        #pragma warning (pop)
	        if (m_pRecordset->GetEndOfFile())
	        {
	            return true;
	        }
	        else
	        {
	            return false;
	        }
	    }
	    catch (_com_error &e)
	    {
	        CDebugOutPut::ErrOut(e.Description().GetBSTR());
	        return true;
	    }
	}
	
	bool CRecordset::IsOpen() const
	{
	    return (m_pRecordset!=NULL);
	}
};