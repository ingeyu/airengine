// dllmain.cpp: DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "EffectorHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CEffectorHandlersModule _AtlModule;

class CEffectorHandlersApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CEffectorHandlersApp, CWinApp)
END_MESSAGE_MAP()

CEffectorHandlersApp theApp;

BOOL CEffectorHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
	return CWinApp::InitInstance();
}

int CEffectorHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
