#ifndef AirCppScriptSyntaxFunction_h__
#define AirCppScriptSyntaxFunction_h__

#include "AirCppScriptSyntaxVariable.h"

namespace	Air{
	namespace	CppScript{
		class	ParameterNode	:	public	VariableNode{
		public:
			ParameterNode(){
				m_Type	=	enNT_Parameter;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
		};
		typedef std::vector<ParameterNode*>	ParameterVector;

		enum enumFunctionType{
			enFT_CFunction,
			enFT_MemberFunction,
			enFT_Construct,
			enFT_DisConstruct,
		};

		class	FunctionNode	:	public	Node{
		public:
			FunctionNode(){
				m_Type			=	enNT_Function;
				m_bOnlyDeclare	=	true;
				m_bVirtual		=	0;
				ieType			=	enCKWT_Unknown;
				m_uiLocalVariableSize	=	0;
				pEntry			=	NULL;
				RefCount		=	0;
				callType		=	enCKWT___stdcall;
				FunctionType	=	enFT_CFunction;
			};

			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseImportExport(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseParameter(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseReturnType_Name(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseCallType(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);

			U1							IsParamNameExist(CAString& strName);
			U1							IsVartual(){return m_bVirtual!=0;};
			U1							IsStatic(){return m_bIsStatic!=0;};
			U1							IsMemberFunction();
			U32							GetVirtualIndex();
			ParameterNode*				FindParameter(CAString& strName);
			U32							GetParameterCount(){
				return m_vecParameter.size();
			};
			U32							GetEntry(){
				return pEntry;
			};
			enumCppKeyWordType			GetCallType(){
				return callType;
			};
			enumFunctionType			GetFunctionType(){
				return FunctionType;
			};
			ParameterNode				m_ReturnType;
			ParameterVector				m_vecParameter;
			U32							m_bOnlyDeclare;
			U32							m_bVirtual;
			U32							m_uiVirtualIndex;
			U32							m_bIsStatic;
			enumCppKeyWordType			ieType;
			U32							pEntry;
			U32							RefCount;
			enumCppKeyWordType			callType;
			enumFunctionType			FunctionType;
		protected:
			U32							m_uiLocalVariableSize;
		};
	
	}
}
#endif // AirCppScriptSyntaxFunction_h__
