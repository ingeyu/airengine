// SetupFinshed.cpp : 实现文件
//

#include "stdafx.h"
#include "MSetup.h"
#include "SetupFinshed.h"
#include "afxdialogex.h"
#include "atlconv.h"

// CSetupFinshed 对话框

IMPLEMENT_DYNAMIC(CSetupFinshed, CDialog)

CSetupFinshed::CSetupFinshed(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupFinshed::IDD, pParent)
{
	memset(strGamePath,0,sizeof(wchar_t)*1024);
}

CSetupFinshed::~CSetupFinshed()
{
}

void CSetupFinshed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetupFinshed, CDialog)
	ON_BN_CLICKED(IDOK, &CSetupFinshed::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetupFinshed 消息处理程序




bool CreatLinkToStartMenu(wchar_t * pszPeFileName)
{

	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		IShellLink *pisl;
		hr = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pisl);
		if (SUCCEEDED(hr))
		{
			IPersistFile* pIPF;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//这里是我们要创建快捷方式的原始文件地址
			pisl->SetPath(pszPeFileName);
			hr = pisl->QueryInterface(IID_IPersistFile, (void**)&pIPF);
			if (SUCCEEDED(hr))
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//这里是我们要创建快捷方式的目标地址
				wchar_t szStartPath[1024] = {0};
				SHGetSpecialFolderPath(NULL,szStartPath, CSIDL_DESKTOP, 0);
				wcscat(szStartPath,L"\\零世界.lnk");

				USES_CONVERSION;
				//LPCOLESTR lpOleStr = A2COLE(szStartPath);

				pIPF->Save(szStartPath, FALSE);

				pIPF->Release();
			}
			pisl->Release();
		}
		CoUninitialize();
	}

	return true;
}



void CSetupFinshed::OnBnClickedOk()
{
	wchar_t	strGameExe[1024];
	swprintf_s(strGameExe,L"%Autopatch.exe",strGamePath);
	// TODO: 在此添加控件通知处理程序代码
	if(IsDlgButtonChecked(IDC_CHECK_DESKTOP_SHOTCUT))
	{
		
		//if(SHGetSpecialFolderPathW(GetDesktopWindow()->m_hWnd,strDeskTop,CSIDL_DESKTOP,NULL))
		//{
		//	AfxMessageBox(strDeskTop);
		//}
		CreatLinkToStartMenu(L"F:\\wz\\Autopatch.exe");
		//CreatLinkToStartMenu(strGameExe);

	}
	if(IsDlgButtonChecked(IDC_CHECK_START_GAME)){
		swprintf_s(strGameExe,L"F:\\wz\\Autopatch.exe");
		swprintf_s(strGamePath,L"F:\\wz\\");
		STARTUPINFO si = { sizeof(si) };     
		PROCESS_INFORMATION pi;     
		si.dwFlags = STARTF_USESHOWWINDOW; // 指定wShowWindow成员有效     
		si.wShowWindow = FALSE; // 此成员设为TRUE的话则显示新建进程的主窗口     
		BOOL bRet = CreateProcess (     NULL,// 不在此指定可执行文件的文件名     
			strGameExe,//命令行参数     
			NULL,// 默认进程安全性     
			NULL,// 默认进程安全性     
			FALSE,// 指定当前进程内句柄不可以被子进程继承     
			0,// 为新进程创建一个新的控制台窗口     
			NULL,// 使用本进程的环境变量     
			strGamePath,// 使用本进程的驱动器和目录     
			&si,     
			&pi) ;   
	}
	CDialog::OnOK();

}
