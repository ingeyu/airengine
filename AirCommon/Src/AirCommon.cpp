// Common.cpp : 定义 DLL 应用程序的入口点。
//

#include "AirCommon.h"
#include <windows.h>
#include "AirRandom.h"
#include "AirCompress.h"
#include "AirCommonLog.h"
#include "AirCommonNet.h"
#include "AirCommonProfile.h"
#include "AirWinVer.h"


BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved){
	switch (ul_reason_for_call){
		
		case DLL_PROCESS_ATTACH:{//第一次加载此Dll
			Air::Common::Number::InitSrand();
 			Air::Common::Compress::Init();
 			Air::Common::InitNet();
			CXWinVersion version;		
			OutputDebugStringA(version.GetWinVersionString().c_str());
			break;}
		case DLL_THREAD_ATTACH://每一次创建线程

		break;
		case DLL_THREAD_DETACH://每一次线程结束
			
		break;
		case DLL_PROCESS_DETACH:{//卸载该Dll
 			Air::Common::Compress::Release();	
 			Air::ProfileManager::ReleaseSingleton();
 			Air::Common::ReleaseNet();
			Air::Common::Log::ReleaseSingleton();
			break;}
	}
    return TRUE;
}


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