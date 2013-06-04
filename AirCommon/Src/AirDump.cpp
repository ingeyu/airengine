#include "AirDump.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <new.h>
#include <signal.h>
#include <exception>
#include <stdio.h>
#pragma comment(lib,"dbghelp")

namespace	Air{

#define PRINT_FUNCTION	OutputDebugStringA(__FUNCTION__);OutputDebugStringA("\n");
	static enumDumpLevel	g_DumpLevel	=	enDL_Normal;
	MINIDUMP_TYPE	GetMiniDumpType(enumDumpLevel level){
		MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)0;
		switch(level){
			case enDL_Tiny:{
				mdt	= MiniDumpNormal; 
						   }break;
			case enDL_Mini:{
				mdt	= (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory); 
						   }break;
			case enDL_Normal:{
				mdt	=	(MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory | 
										MiniDumpWithDataSegs | 
										MiniDumpWithHandleData |
										MiniDumpWithFullMemoryInfo | 
										MiniDumpWithThreadInfo | 
										MiniDumpWithUnloadedModules ); 
							 
							 }break;
			case enDL_Full:{
				mdt	= (MINIDUMP_TYPE)(MiniDumpWithFullMemory | 
					MiniDumpWithFullMemoryInfo | 
					MiniDumpWithHandleData | 
					MiniDumpWithThreadInfo | 
					MiniDumpWithUnloadedModules );
						   }break;
			default:{
				mdt	= MiniDumpNormal; 
					}break;
		}
		return mdt;
	}

	BOOL CALLBACK __MiniDumpCallback(
		PVOID                            pParam, 
		const PMINIDUMP_CALLBACK_INPUT   pInput, 
		PMINIDUMP_CALLBACK_OUTPUT        pOutput 
		) 
	{
		BOOL bRet = FALSE; 


		// Check parameters 

		if( pInput == 0 ) 
			return FALSE; 

		if( pOutput == 0 ) 
			return FALSE; 


		// Process the callbacks 

		switch( pInput->CallbackType ) 
		{
		case IncludeModuleCallback: 
			{
				// Include the module into the dump 
				bRet = TRUE; 
			}
			break; 

		case IncludeThreadCallback: 
			{
				// Include the thread into the dump 
				bRet = TRUE; 
			}
			break; 

		case ModuleCallback: 
			{
				// Are data sections available for this module ? 

				if( pOutput->ModuleWriteFlags & ModuleWriteDataSeg ) 
				{
					// Yes, they are, but do we need them? 

					//if( !IsDataSectionNeeded( pInput->Module.FullPath ) ) 
					//{
					//	wprintf( L"Excluding module data sections: %s \n", pInput->Module.FullPath ); 

					//	pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg); 
					//}
				}

				bRet = TRUE; 
			}
			break; 

		case ThreadCallback: 
			{
				// Include all thread information into the minidump 
				bRet = TRUE;  
			}
			break; 

		case ThreadExCallback: 
			{
				// Include this information 
				bRet = TRUE;  
			}
			break; 

		case MemoryCallback: 
			{
				// We do not include any information here -> return FALSE 
				bRet = FALSE; 
			}
			break; 

		case CancelCallback: 
			break; 
		}

		return bRet; 

	}

	void	GetTimeString(char* str){
		SYSTEMTIME t;
		GetLocalTime(&t);
		sprintf_s(str,256,"MiniDump\\%02d_%02d_%02d__%02d_%02d_%02d.dmp",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);
	};

	void CreateMiniDump( EXCEPTION_POINTERS* pep ) 
	{
		
		CreateDirectoryA("MiniDump",NULL);
		char strName[256];
		GetTimeString(strName);

		// Open the file 
		HANDLE hFile = CreateFileA( strName, GENERIC_READ | GENERIC_WRITE, 
			0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 

		if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
		{
			// Create the minidump 

			MINIDUMP_EXCEPTION_INFORMATION mdei; 

			mdei.ThreadId           = GetCurrentThreadId(); 
			mdei.ExceptionPointers  = pep; 
			mdei.ClientPointers     = FALSE; 

			MINIDUMP_CALLBACK_INFORMATION mci; 

			mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)__MiniDumpCallback; 
			mci.CallbackParam       = 0; 


			MINIDUMP_TYPE mdt       = GetMiniDumpType(g_DumpLevel); 

			BOOL rv = MiniDumpWriteDump( 
				GetCurrentProcess(), 
				GetCurrentProcessId(), 
				hFile, 
				mdt, 
				(pep != 0) ? &mdei : 0, 
				0, 
				&mci ); 

			//if( !rv ) 
			//	_tprintf( _T("MiniDumpWriteDump failed. Error: %u \n"), GetLastError() ); 
			//else 
			//	_tprintf( _T("Minidump created.\n") ); 

			// Close the file 

			CloseHandle( hFile ); 

		}
		else 
		{
			//_tprintf( _T("CreateFile failed. Error: %u \n"), GetLastError() ); 
		}
		MessageBoxA(NULL,"Program Crash","Error",NULL);
	}

	LONG WINAPI __TOP_LEVEL_EXCEPTION_FILTER(
		__in struct _EXCEPTION_POINTERS *ExceptionInfo
		)
	{
		PRINT_FUNCTION

		CreateMiniDump(ExceptionInfo);
		return	EXCEPTION_EXECUTE_HANDLER;
	};

	void __cdecl __InvalidParameterHandler(const wchar_t* expression,
		const wchar_t* function, 
		const wchar_t* file, 
		unsigned int line, 
		uintptr_t pReserved)
	{
		PRINT_FUNCTION
		// function、file、line在Release下无效
		//wprintf(L"Invalid parameter detected in function %s."
		//	L" File: %s Line: %d\n", function, file, line);
		//wprintf(L"Expression: %s\n", expression);
		// 必须抛出异常，否则无法定位错误位置
		//_exception_info();
		throw 1;
	}
	void __HandlePureVirtualCall(void)
	{
		PRINT_FUNCTION
		// 必须抛出异常，否则无法定位错误位置
		throw 1;
	}

	// C++ terminate handler
	void __cdecl __TerminateHandler()
	{
		PRINT_FUNCTION
	};
	// C++ unexpected handler
	void __cdecl __UnexpectedHandler()
	{
		PRINT_FUNCTION
	};
#if _MSC_VER>=1300
	// C++ new operator fault (memory exhaustion) handler
	int __cdecl __NewHandler(size_t){
		PRINT_FUNCTION
		return 1;
	};
#endif

	void __SigabrtHandler(int){
		PRINT_FUNCTION
	};
	void __SigfpeHandler(int /*code*/){
		PRINT_FUNCTION
	};
	void __SigintHandler(int){
		PRINT_FUNCTION
	};
	void __SigillHandler(int){
		PRINT_FUNCTION
	};
	void __SigsegvHandler(int){
		PRINT_FUNCTION
		//throw 1;
	};
	void __SigtermHandler(int){
		PRINT_FUNCTION
	};
	void Dump_Init( enumDumpLevel level )
	{
		g_DumpLevel	=	level;
		SetUnhandledExceptionFilter(__TOP_LEVEL_EXCEPTION_FILTER);
#if _MSC_VER	>=	1400
		_set_invalid_parameter_handler(__InvalidParameterHandler);
#endif
#if _MSC_VER	>=	1300
		_set_purecall_handler(__HandlePureVirtualCall);
		_set_new_mode(1); // Force malloc() to call new handler too
		_set_new_handler(__NewHandler);
#endif
		// Catch illegal instruction handler
		//signal(SIGINT, __SigintHandler);
		// Catch a termination request
		//signal(SIGTERM, __SigtermHandler);

		//set_terminate(__TerminateHandler);
		//set_unexpected(__UnexpectedHandler);
		//signal(SIGFPE, __SigfpeHandler);
		//signal(SIGILL, __SigillHandler);
		//signal(SIGSEGV, __SigsegvHandler);
	}

	COMMON_EXPORT	void GenDump( enumDumpLevel level /*= enDL_Normal*/ )
	{
		CONTEXT c;
		RtlCaptureContext(&c);
		EXCEPTION_RECORD	e;
		e.ExceptionAddress	=	(void*)c.Eip;
		e.ExceptionCode		=	EXCEPTION_ACCESS_VIOLATION ;
		e.ExceptionFlags	=	EXCEPTION_NONCONTINUABLE;
		e.ExceptionRecord	=	NULL;
		e.NumberParameters	=	1;
		e.ExceptionInformation[0]	=	0;
		e.ExceptionInformation[1]	=	c.Ecx;
		//e.ExceptionInformation	=	
		EXCEPTION_POINTERS	exc;
		exc.ContextRecord	=	&c;
		exc.ExceptionRecord	=	&e;
		CreateMiniDump(&exc);
	}

}