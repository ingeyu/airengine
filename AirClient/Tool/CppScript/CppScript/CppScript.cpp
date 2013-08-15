// CppScript.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <string>

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

__declspec(dllimport) int Call(int x,int y,int z);
//__declspec(dllimport) int a;

int _tmain(int argc, _TCHAR* argv[])
{
	//A a = Call(1,2,3);
	//if(argc	<	2){
	//	wprintf(L"CppScript *.cpp\n");
	//	getchar();
	//	return -1;
	//}

	wchar_t str[1024];
	GetCurrentDirectory(1024,str);
	std::wstring	strPath		=	str;
	GetModuleFileName(NULL,str,1024);
	Air::CppScript::SplitFilePath(str,&strPath,NULL,NULL);
	SetCurrentDirectory(strPath.c_str());

	Air::CppScript::Compiler c;
	c.Initialization();

	c.Compile(L"1.cpp");
	getchar();
	return 0;
}

