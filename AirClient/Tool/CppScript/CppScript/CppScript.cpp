// CppScript.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "AirCppScriptCompiler.h"
_declspec(naked) void* __stdcall	__alloca(int iSize){
	__asm{
		mov		eax,dword ptr[esp+4];
		push	ebp;
		mov		ebp,esp;
		add		eax,1;
		and		eax,0xfffffffc;
		sub		esp,eax;
		add		eax,4;
		push	eax;
		mov		eax,esp;
		add		eax,4;
		push	dword ptr[ebp+8];
		push	dword ptr[ebp+4];
		mov		ebp,dword ptr[ebp];
		ret		4;
	}
}
_declspec(naked)	void	__stdcall	__freea(void* p){
	__asm{
		mov		eax,dword ptr[esp+4];
		mov		eax,dword ptr[eax-4];
		add		eax,10h;
		push	ebp;
		mov		ebp,esp;
		add		esp,eax;
		mov		eax,dword ptr[ebp+4];
		mov		dword ptr[esp],eax;
		mov		ebp,dword ptr[ebp];
		ret		4;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	if(argc	<	2){
		wprintf(L"CppScript *.cpp\n");
		getchar();
		return -1;
	}
	Air::CppScript::Compiler c;
	c.Initialization();

	c.Compile(argv[1]);
	getchar();
	return 0;
}

