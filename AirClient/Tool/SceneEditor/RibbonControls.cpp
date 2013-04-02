// RibbonControls.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RibbonControls.h"

#include "MainFrm.h"
#include "RibbonControlsDoc.h"
#include "RibbonControlsView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsApp

BEGIN_MESSAGE_MAP(CRibbonControlsApp, CWinApp)
	//{{AFX_MSG_MAP(CRibbonControlsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsApp construction

CRibbonControlsApp::CRibbonControlsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}






Air::Engine::EngineParam							g_Param;



bool __ParseCommandLine(LPTSTR	strCommandLine){



	Air::AString	strIniFile	=	"..\\Data\\Config\\Application.ini";


	if(strCommandLine!=NULL &&strlen(strCommandLine)>0)
		strIniFile	=	strCommandLine;


	Air::Common::IniFile	cfg;
	if(!cfg.LoadFile(strIniFile)){
		MessageBoxA(NULL,"Config File Open Failed!",NULL,NULL);
		return	false;
	}



	Air::AString	str;
	str	=	cfg.Get("Config","Plugin");		strcpy_s(g_Param.strPlugin,128,str.c_str());
	str	=	cfg.Get("Config","GamePlugin");	strcpy_s(g_Param.strGamePlugin,128,str.c_str());
	str	=	cfg.Get("Config","Media");		strcpy_s(g_Param.strMedia,128,str.c_str());
	str	=	cfg.Get("Config","CustomMedia");strcpy_s(g_Param.strCustomMedia,128,str.c_str());
	str	=	cfg.Get("Config","Display");	strcpy_s(g_Param.strDisplay,128,str.c_str());

	return	true;
};
/////////////////////////////////////////////////////////////////////////////
// The one and only CRibbonControlsApp object

CRibbonControlsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsApp initialization
void __stdcall TimerCallback(HWND hWindow,UINT,UINT_PTR,DWORD){
	Air::GetTimer().AddFrame();
	Air::Engine::EngineSystem::GetSingleton()->ExecuteOneFrame(Air::GetTimer().m_FrameTime);
}
BOOL CRibbonControlsApp::InitInstance()
{
	AfxEnableControlContainer();
	CXTPWinDwmWrapper().SetProcessDPIAware();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER <= 1200 //MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
#endif

	char strModuleName[1024];
	GetModuleFileNameA(NULL,strModuleName,1024);

	Air::AString	strPath,strName,strExe;

	Air::Common::Converter::SplitFilePath(strModuleName,&strPath,&strName,&strExe);

	SetCurrentDirectoryA(strPath.c_str());

	__ParseCommandLine(NULL);

	memcpy(&Air::Engine::GetGlobalSetting().m_EngineParam,&g_Param,sizeof(g_Param));

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CRibbonControlsDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CRibbonControlsView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();


	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CView* pView = (CView*)pMainFrame->GetActiveView();
	Air::Engine::GetGlobalSetting().m_EngineParam.hWnd	=	pView->GetSafeHwnd();
	Air::Engine::GetGlobalSetting().m_EngineParam.InputWnd	=	m_pMainWnd->GetSafeHwnd();
	Air::Engine::EngineSystem::GetSingleton()->Initialization();

	SetTimer(pView->GetSafeHwnd(),100,16,TimerCallback);
	return TRUE;
}

// App command to run the dialog
void CRibbonControlsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CRibbonControlsApp::OnIdle( LONG lCount )
{

	return __super::OnIdle(lCount);
}

int CRibbonControlsApp::ExitInstance()
{
	Air::Engine::EngineSystem::GetSingleton()->Release();
	Air::Engine::EngineSystem::ReleaseSingleton();
	return __super::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsApp message handlers

