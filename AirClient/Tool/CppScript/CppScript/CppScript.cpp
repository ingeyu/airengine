// CppScript.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <string>

#include "AirCppScriptCompiler.h"
#include "AirCppScriptFunction.h"
#include "AirCppScriptModule.h"
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

typedef int (__stdcall *ScriptFunc)(int iCount,int iStart);

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc	<	2){
		wprintf(L"CppScript *.proj\n");
		wprintf(L"CppScript *.cpp\n");
		wprintf(L"CppScript *.module\n");
		getchar();
		return -1;
	}
	Air::CppScript::InitWorkDirectory();

	

	
	std::wstring	strPath,strName,strExt;
	
	Air::CppScript::SplitFilePath(argv[1],&strPath,&strName,&strExt);
	
	Air::CppScript::ToLower(&strExt[0]);
	if(strExt==L"cpp"){
		Air::CppScript::Compiler c;
		c.Initialization();

		c.Compile(argv[1]);
		std::wstring	strOutputName	=	strPath+strName+L".module";
		c.Link(strOutputName.c_str());
		c.Release();
	}else if (strExt==L"proj"){
		Air::CppScript::Compiler c;
		c.Initialization();
		c.BuildProj(argv[1]);
		c.Release();
	}else if(strExt==L"module"){
		getchar();
		Air::CppScript::Module module;
		if(module.Load(argv[1])!=Air::CppScript::enLE_OK){
			printf("Load Module (%s) Failed!\n",argv[1]);
		}
		ScriptFunc	f	=	(ScriptFunc)module.FindFunction("main");
		int ret=(*f)(101,0);
		printf("main = (%08x,%d)\n",ret,ret);
		module.UnLoad();
	}

	getchar();
	return 0;
}

