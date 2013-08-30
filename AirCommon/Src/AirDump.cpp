#include "AirDump.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <new.h>
#include <signal.h>
#include <exception>
#include <stdio.h>
#include "winternl.h"
#include "AirCommonConverter.h"
#include "psapi.h"
#pragma comment(lib,"psapi")

#pragma comment(lib,"dbghelp")
typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;
typedef LONG KPRIORITY;
typedef struct _THREAD_BASIC_INFORMATION
{
	NTSTATUS ExitStatus;
	PVOID TebBaseAddress;
	CLIENT_ID ClientId;
	KAFFINITY AffinityMask;
	KPRIORITY Priority;
	KPRIORITY BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;
typedef enum _THREAD_INFORMATION_CLASS
{
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,
	//ThreadIsIoPending,
	ThreadHideFromDebugger=17
}THREAD_INFORMATION_CLASS,*PTHREAD_INFORMATION_CLASS;

typedef NTSTATUS
	(NTAPI 
	*T_NtQueryInformationThread) (
	IN HANDLE ThreadHandle,
	IN THREADINFOCLASS ThreadInformationClass,
	OUT PVOID ThreadInformation,
	IN ULONG ThreadInformationLength,
	OUT PULONG ReturnLength OPTIONAL
	);

namespace	Air{
	

	



#define PRINT_FUNCTION	OutputDebugStringA(__FUNCTION__);OutputDebugStringA("\n");
	static enumDumpLevel	g_DumpLevel	=	enDL_Tiny;
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
		StackWalker walker;
		walker.CallStack(pep->ContextRecord);
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

	BOOL
		CALLBACK COSTOM_ENUMLOADED_MODULES_CALLBACK64( __in PCSTR ModuleName, __in DWORD64 ModuleBase, __in ULONG ModuleSize, __in_opt PVOID UserContext )
	{
		MODULEINFO info;
		DWORD cb=0;
		GetModuleInformation(GetCurrentProcess(),(HMODULE)ModuleBase,&info,cb);
		StackWalker* pWalker	=	(StackWalker*)UserContext;
		pWalker->AddModule(ModuleName,ModuleBase,ModuleSize);
		return true;
	}
	struct PDBINFO{
		DWORD						unknown;
		MODLOAD_PDBGUID_PDBAGE		pdbage;
		char						pdbName[128];
	};

	StackWalker::StackWalker()
	{
		memset(m_vecModule,0,sizeof(Module)*200);
		m_uiModuleCount	=	0;
	}
	PIMAGE_SECTION_HEADER GetSectionHeader(PIMAGE_SECTION_HEADER section,IMAGE_NT_HEADERS* ntHeader,PSTR name)
	{
		unsigned i;

		for ( i=0; i < ntHeader->FileHeader.NumberOfSections; i++, section++ )
		{
			if ( 0 == strncmp((char *)section->Name,name,IMAGE_SIZEOF_SHORT_NAME) )
				return section;
		}

		return 0;
	};
	PIMAGE_SECTION_HEADER GetEnclosingSectionHeader(PIMAGE_SECTION_HEADER section,IMAGE_NT_HEADERS* ntHeader,DWORD rva)
	{
		
		unsigned i;

		for ( i=0; i < ntHeader->FileHeader.NumberOfSections; i++, section++ )
		{
			// Is the RVA within this section?
			if ( (rva >= section->VirtualAddress) && 
				(rva < (section->VirtualAddress + section->Misc.VirtualSize)))
				return section;
		}

		return 0;
	}
	void StackWalker::AddModule( const char* ModuleName,unsigned long long ModuleBase,unsigned long ModuleSize)
	{
		
		int iModuleIndex	=	m_uiModuleCount;
		m_uiModuleCount++;
		Module& module		=	m_vecModule[iModuleIndex];
		module.ModuleBase	=	ModuleBase;
		module.ModuleSize	=	ModuleSize;

		AString strFile,strExt;
		Common::Converter::SplitFilePath(ModuleName,NULL,&strFile,&strExt);
		strFile	+=	"."+strExt;
		Common::Converter::ToLowerCase(strFile);
		strcpy(module.ModuleName,strFile.c_str());

		unsigned char* pData = (unsigned char*)ModuleBase;
		if(pData[0]==0X4D&&pData[1]==0X5A){

		}
		IMAGE_DOS_HEADER* dosHeader=(IMAGE_DOS_HEADER*)pData;
		pData	+=	dosHeader->e_lfanew;//sizeof(IMAGE_DOS_HEADER);


		IMAGE_NT_HEADERS* ntHeader=(IMAGE_NT_HEADERS*)pData;
		pData+=sizeof(IMAGE_NT_HEADERS);//-sizeof(IMAGE_OPTIONAL_HEADER)+ntHeader->FileHeader.SizeOfOptionalHeader;

		//int iBack = (16-file.OptionalHeader.NumberOfRvaAndSizes)*sizeof(IMAGE_DATA_DIRECTORY);
		//pData-=iBack;

		IMAGE_SECTION_HEADER* sectionHeader=(IMAGE_SECTION_HEADER*)pData;
		pData+=(ntHeader->FileHeader.NumberOfSections)*sizeof(IMAGE_SECTION_HEADER);
		{
			module.TimeStamp=ntHeader->FileHeader.TimeDateStamp;
		}


		PIMAGE_SECTION_HEADER header;
		DWORD va_debug_dir;
		DWORD size;
		IMAGE_DATA_DIRECTORY& data	=	ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG];

		va_debug_dir = data.VirtualAddress;

		if ( va_debug_dir == 0 )
			return;
		PIMAGE_DEBUG_DIRECTORY debugDir=NULL;
		// If we found a .debug section, and the debug directory is at the
		// beginning of this section, it looks like a Borland file
		header = GetSectionHeader(sectionHeader,ntHeader,".debug");
		if ( header && (header->VirtualAddress == va_debug_dir) )
		{
			debugDir = (PIMAGE_DEBUG_DIRECTORY)((unsigned char*)ModuleBase+header->PointerToRawData);
			size = data.Size* sizeof(IMAGE_DEBUG_DIRECTORY);
		}
		else    // Look for the debug directory
		{
			header = GetEnclosingSectionHeader( sectionHeader,ntHeader,va_debug_dir );
			if ( !header )
				return ;

			size = data.Size;

			debugDir = (PIMAGE_DEBUG_DIRECTORY)((unsigned char*)ModuleBase+DWORD(header->PointerToRawData+va_debug_dir - header->VirtualAddress));
		}

		switch( debugDir->Type )
		{
		case IMAGE_DEBUG_TYPE_CODEVIEW:
			PDBINFO* pdbInfo		=	(PDBINFO*)((unsigned char*)ModuleBase + debugDir->PointerToRawData);
			module.Guid	=	pdbInfo->pdbage.PdbGuid;
			module.Age	=	pdbInfo->pdbage.PdbAge;
			strcpy(module.ModulePDBName,pdbInfo->pdbName);
			break;
		}

	}
	#define STEP_FLAG 0x00000100 /* single step flag */
	#define V86_FLAG  0x00020000
	#define IS_VM86_MODE(ctx) (ctx->EFlags & V86_FLAG)
	static ADDRESS_MODE get_selector_type(HANDLE hThread, const CONTEXT* ctx, WORD sel)
	{
		LDT_ENTRY	le;

		if (IS_VM86_MODE(ctx)) return AddrModeReal;
		/* null or system selector */
		if (!(sel & 4) || ((sel >> 3) < 17)) return AddrModeFlat;
		if (hThread && GetThreadSelectorEntry(hThread, sel, &le))
			return le.HighWord.Bits.Default_Big ? AddrMode1632 : AddrMode1616;
		/* selector doesn't exist */
		return (ADDRESS_MODE)-1;
	}
	static unsigned i386_build_addr(HANDLE hThread, const CONTEXT* ctx, ADDRESS64* addr,
		unsigned seg, unsigned long offset)
	{
		addr->Mode    = AddrModeFlat;
		addr->Segment = seg;
		addr->Offset  = offset;
		if (seg)
		{
			switch (addr->Mode = get_selector_type(hThread, ctx, seg))
			{
			case AddrModeReal:
			case AddrMode1616:
				addr->Offset &= 0xffff;
				break;
			case AddrModeFlat:
			case AddrMode1632:
				break;
			default:
				return FALSE;
			}
		}
		return TRUE;
	}
	enum cpu_addr {cpu_addr_pc, cpu_addr_stack, cpu_addr_frame};
	unsigned i386_get_addr(HANDLE hThread, const CONTEXT* ctx,
		enum cpu_addr ca, ADDRESS64* addr)
	{

		switch (ca)
		{
		case cpu_addr_pc:    return i386_build_addr(hThread, ctx, addr, ctx->SegCs, ctx->Eip);
		case cpu_addr_stack: return i386_build_addr(hThread, ctx, addr, ctx->SegSs, ctx->Esp);
		case cpu_addr_frame: return i386_build_addr(hThread, ctx, addr, ctx->SegSs, ctx->Ebp);
		}

		return FALSE;
	}
	 void* GetThreadStackTop(	HANDLE	hThread	,
								const void* teb_addr,
								const CONTEXT* ctx)
	{
		NT_TIB      tib;
		ADDRESS64   addr;

		if (ReadProcessMemory(GetCurrentProcess(), teb_addr, &tib, sizeof(tib), NULL)&&i386_get_addr(hThread,ctx,cpu_addr_stack, &addr) && addr.Mode == AddrModeFlat)
		{
			ULONG_PTR pStack=NULL;
			if (addr.Offset)
			{
				addr.Offset -= 4;//dbghelp_current_cpu->word_size;
				/* make sure stack pointer is within the established range of the stack.  It could have
				   been clobbered by whatever caused the original exception. */
				if (addr.Offset < (ULONG_PTR)tib.StackLimit || addr.Offset > (ULONG_PTR)tib.StackBase)
					pStack = (ULONG_PTR)tib.StackLimit;

				else
					pStack = addr.Offset;
			}
			else
				pStack = (ULONG_PTR)tib.StackLimit;
			DWORD DataSize = (ULONG_PTR)tib.StackBase - pStack;
			return tib.StackBase;
		}
		return NULL;
	}

	 bool IsCall( const void* p )
	 {
		 unsigned char* pCode = (unsigned char*)p;
		 unsigned short* pCode2	=	( unsigned short*)(pCode+4);
		 unsigned short c2 = *pCode2;
		 c2 = c2&0xf0ff;
		 if(c2 == 0x10FF || c2==0xD0FF || c2 == 0x50FF){
			 return true;
		 }
		 unsigned short* pCode3	=	( unsigned short*)(pCode+3);
		 unsigned short c3_1	=	*pCode3;
		 unsigned short c3		=	*pCode3;
		 c3=c3&0xf0ff;
		 if(c3 == 0x50FF ||c3_1==0x14ff){
			 return true;
		 }
		  unsigned short* pCode4	=	( unsigned short*)(pCode+2);
		  unsigned short c4		=	*pCode4;
		 if(c4 == 0x54ff){
			 return true;
		 }

		  unsigned char c5	=	*(pCode+1);
		 if(c5==0xe8){
			 return true;
		 }

		  unsigned short* pCode6	=	( unsigned short*)(pCode);
		  unsigned short c6 = *pCode6;
		 if(c6==0x15FF){
			 return true;
		 }

		 return false;
	 }

	void StackWalker::CallStack( void* pContext )
	{
		MessageBox(0,0,0,0);
		HANDLE	hProcess	=	GetCurrentProcess();
		memset(m_vecModule,0,sizeof(Module)*200);
		EnumerateLoadedModules64(hProcess,COSTOM_ENUMLOADED_MODULES_CALLBACK64,this);
		
		PCONTEXT p	=	(PCONTEXT)pContext;
		HANDLE	hThread	=	NULL;
		DWORD tid	=	GetCurrentThreadId();
		if ((hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, tid)) == NULL){
			return;
		}

		T_NtQueryInformationThread pQueryThread = (T_NtQueryInformationThread)GetProcAddress(GetModuleHandle("ntdll.dll"),"NtQueryInformationThread");
		if(pQueryThread==NULL)
			return ;
		THREAD_BASIC_INFORMATION    tbi;
		if ((*pQueryThread)(hThread, (THREADINFOCLASS)ThreadBasicInformation,//ThreadBasicInformation,
			&tbi, sizeof(tbi), NULL) == 0)
		{
			DWORD* pEnd = (DWORD*)GetThreadStackTop(hThread,tbi.TebBaseAddress,p);
			DWORD* pBegin	= (DWORD*)p->Esp;
			
			for(;pBegin!=pEnd;pBegin++){
				DWORD pAddr	=	*pBegin;
				for(DWORD i=0;i<m_uiModuleCount;i++){
					Module& module = m_vecModule[i];
					DWORD	uiOffset	=	pAddr	-	(DWORD)module.ModuleBase;
					if(module.ModuleBase <= pAddr && uiOffset < module.ModuleSize){
						unsigned char code[6];
						memset(code,0,6);
						SIZE_T uiReadSize=0;
						ReadProcessMemory(hProcess,(unsigned char*)pAddr-6,code,6,&uiReadSize);
						if(IsCall(code)){
							char str[256];
							sprintf(str,"%d %08x %08x %08x %s\n",tid,pAddr,uiOffset,module.TimeStamp,module.ModuleName);
							OutputDebugStringA(str);
						}
						break;
					}
				}
			}
		}
	}

}