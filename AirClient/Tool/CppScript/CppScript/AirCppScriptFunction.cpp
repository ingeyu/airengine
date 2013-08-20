#include "AirCppScriptFunction.h"

#include "AirCppScriptAssemble.h"
namespace	Air{
	namespace	CppScript{
		__declspec(naked) int __stdcall TestMemcpy(){
			//return memcpy(pDst,pSrc,isize);
			__asm{
				push ebp
					push ebx
					push edx
					push esi
					mov ebp,esp
					sub esp,8
					mov esi,esp
					mov eax,0h
					push eax
					mov eax,[esi+0]
				pop ebx
					mov eax,ebx
					mov [esi+0],eax
					mov eax,[ebp+18h]
				push eax
					mov eax,[esi+4]
				pop ebx
					mov eax,ebx
					mov [esi+4],eax
FORCOMPARE:mov eax,[ebp+14h]
				push eax
					mov eax,[esi+4]
				pop ebx
					sub eax,ebx
					test eax,eax
					jz FOREND
					mov eax,[esi+4]
				push eax
					mov eax,[esi+0]
				pop ebx
					add eax,ebx
					mov [esi+0],eax
					mov eax,[esi+4]
				mov ebx,eax
					add ebx,1
					mov [esi+4],ebx
					jmp FORCOMPARE
FOREND:mov eax,[esi+0]
				mov esp,ebp
					pop esi
					pop edx
					pop ebx
					pop ebp
					ret 8h

			}
		}

		Function::Function()
		{
			pFunction	=	(void*)TestMemcpy;
			strName		=	"TestMemcpy";
			//std::string strCode;
			//strCode+="Disassemble__\n";
			//Disassemble(pFunction,128,strCode);
			//printf(strCode.c_str());
		}

		Air::U32 Function::GetParameterCount()
		{
			return 3;
		}

		Air::U1 Function::HasReturnValue()
		{
			return 1;
		}

		enumCallError Function::Call( void* pRetValue,void** ppParameter,U32 uiCount )
		{
			if(pFunction==NULL){
				return	enCE_Function_Address_InValid;
			}
			U32 Func	=	(U32)pFunction;
			
			U32	uiRet		=	0;
			__asm{
				push ebx
				mov	eax,uiCount
ParameterCmp:	test eax,eax
				je	FunctionCall
				sub	eax,1
				mov	ebx,ppParameter;//[eax*4]
				push dword ptr[ebx+eax*4]
				jmp ParameterCmp
FunctionCall:	call Func
				mov	uiRet,eax
				pop ebx
			}
			if(pRetValue!=NULL){
				*(U32*)pRetValue=uiRet;
			}
			return enCE_OK;
		}

	}
}