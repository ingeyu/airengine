
// MSetup.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MSetup.h"
#include "MSetupDlg.h"
#include "SetupBegin.h"
#include "SetupSelectPath.h"
#include "SetupFinshed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMSetupApp

BEGIN_MESSAGE_MAP(CMSetupApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMSetupApp 构造

CMSetupApp::CMSetupApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMSetupApp 对象

CMSetupApp theApp;

BOOL   EnableDebugPrivilege(BOOL   fEnable   =TRUE   )
{   
	BOOL   fOK =   FALSE;   
	HANDLE hToken =   NULL;   
	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken))
	{   
		TOKEN_PRIVILEGES tp;   
		tp.PrivilegeCount =1;   
		LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tp.Privileges[0].Luid);   
		tp.Privileges[0].Attributes =   fEnable   ?   SE_PRIVILEGE_ENABLED   :   0;   
		AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(tp),NULL,NULL);   
		fOK =   (GetLastError()==ERROR_SUCCESS);   
		CloseHandle(hToken);   
	}   
	return   fOK;   
}



// CMSetupApp 初始化

BOOL CMSetupApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	EnableDebugPrivilege(TRUE);

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("SNDA"));

	CSetupBegin	dlgBegin;
	//m_pMainWnd = &dlgBegin;
	INT_PTR nResponse = dlgBegin.DoModal();
	if (nResponse == IDOK)
	{
		CSetupSelectPath	dlgPath;
		//m_pMainWnd = &dlgPath;
		nResponse = dlgPath.DoModal();
		if (nResponse == IDOK)
		{
			CMSetupDlg dlg;
			//m_pMainWnd = &dlg;
			nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{
				CSetupFinshed	dlgFinshed;
				//m_pMainWnd = &dlgFinshed;
				wcscpy_s(dlgFinshed.strGamePath,dlgPath.m_strSetupPath);
				nResponse = dlgFinshed.DoModal();
				if (nResponse == IDOK)
				{

				}
			}
		}

	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

