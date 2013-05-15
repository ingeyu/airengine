#include "AirCommonLog.h"
#include "AirCommonPlugin.h"
#include "AirCommonIniFile.h"
#include "AirCommonConverter.h"
#define USE_PROFILE
#include "AirCommonProfile.h"
#include "AirDump.h"


using	namespace	Air;
// IsInsideVPC&#39;s exception filter
DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
	PCONTEXT ctx = ep->ContextRecord;

	ctx->Ebx = -1; // Not running VPC
	ctx->Eip += 4; // skip past the "call VPC" opcodes
	return EXCEPTION_CONTINUE_EXECUTION; // we can safely resume execution since we skipped faulty instruction
}

// high level language friendly version of IsInsideVPC()
bool IsInsideVPC()
{
	bool rc = false;

	__try
	{
		_asm push ebx
			_asm mov ebx, 0 // Flag
			_asm mov eax, 1 // VPC function number

			// call VPC 
			_asm __emit 0Fh
			_asm __emit 3Fh
			_asm __emit 07h
			_asm __emit 0Bh

			_asm test ebx, ebx
			_asm setz [rc]
		_asm pop ebx
	}
	// The except block shouldn&#39;t get triggered if VPC is running!!
	__except(IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
	}

	return rc;
}
//检测 VMWare的代码
bool IsInsideVMWare()
{
	bool rc = true;

	__try
	{
		__asm
		{
			push  edx
				push  ecx
				push  ebx

				mov  eax,'VMXh';
			mov  ebx, 0 // any value but not the MAGIC VALUE
				mov  ecx, 10 // get VMWare version
				mov  edx, 'VX'; // port number

			in   eax, dx // read port
				// on return EAX returns the VERSION
				cmp  ebx, 'VMXh'; // is it a reply from VMWare?
			setz  [rc] // set return value

			pop  ebx
				pop  ecx
				pop  edx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		rc = false;
	}

	return rc;
}



struct	EngineParam{
	EngineParam(){
		hParentWnd	=	NULL;
		hWnd		=	NULL;
		InputWnd	=	NULL;
		ZeroMemory(strPlugin,128);
		ZeroMemory(strGamePlugin,128);
		ZeroMemory(strMedia,128);
		ZeroMemory(strCustomMedia,128);
		ZeroMemory(strDisplay,128);
	};
	HWND	hParentWnd;
	HWND	hWnd;
	HWND	InputWnd;
	AChar	strPlugin[128];
	AChar	strGamePlugin[128];
	AChar	strMedia[128];
	AChar	strCustomMedia[128];
	AChar	strDisplay[128];
};


static	AChar						g_EngineVersion[]	=	"Air";
Common::Plugin*						g_pEngine			=	NULL;
EngineParam							g_Param;
AString								g_EngineLibraryName	=	"AirEngine.dll";


U1	ParseCommandLine(LPTSTR	strCommandLine){

	

	AString	strIniFile	=	"..\\Data\\Config\\Application.ini";


	if(strCommandLine!=NULL &&strlen(strCommandLine)>0)
		strIniFile	=	strCommandLine;


	Common::IniFile	cfg;
	if(!cfg.LoadFile(strIniFile)){
		MessageBoxA(NULL,"Config File Open Failed!",NULL,NULL);
		return	false;
	}

	

	g_EngineLibraryName	=	cfg.Get("Config","Library");
	AString	str;
	str	=	cfg.Get("Config","Plugin");		strcpy_s(g_Param.strPlugin,128,str.c_str());
	str	=	cfg.Get("Config","GamePlugin");	strcpy_s(g_Param.strGamePlugin,128,str.c_str());
	str	=	cfg.Get("Config","Media");		strcpy_s(g_Param.strMedia,128,str.c_str());
	str	=	cfg.Get("Config","CustomMedia");strcpy_s(g_Param.strCustomMedia,128,str.c_str());
	str	=	cfg.Get("Config","Display");	strcpy_s(g_Param.strDisplay,128,str.c_str());

	return	true;
};

#include "AirCommonParse.h"
//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
extern "C" int WINAPI 
	_tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPTSTR lpCmdLine, int nCmdShow) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	Air::Dump_Init();
	//AString str = "0Xffffffff";
	//StringVector vec;
	//U32 index = 0;
	//Air::Common::Parse::StringToWord((U8*)&str[0],str.size()+1,vec,true);

	//int f=Air::Common::Parse::ParseInt(vec,index);


	//检测是否在虚拟机里
	//if(IsInsideVPC()||IsInsideVMWare())
	//	return	-2;
	char strModuleName[1024];
	GetModuleFileNameA(hInstance,strModuleName,1024);

	Air::AString	strPath,strName,strExe;
	
	Air::Common::Converter::SplitFilePath(strModuleName,&strPath,&strName,&strExe);

	SetCurrentDirectoryA(strPath.c_str());

	//Common::LogTitle("Application",g_EngineVersion);
	//static_assert(__is_empty(Air::Common::Plugin),"dasdiaspodiasdo");


	if(ParseCommandLine(lpCmdLine))
	{
		Common::Plugin	plugin(g_EngineLibraryName,&g_Param);
		//Common::Plugin	plugin("AirRender11.dll",&g_Param);
		plugin.Create();


		//开始执行引擎的循环
		plugin.Excute(Common::Plugin::enStart);

		//卸载引擎
		//plugin.Excute(Common::Plugin::enStop);
		

		plugin.Destroy();

	
	}
	//_CrtDumpMemoryLeaks();
	return 0;
}