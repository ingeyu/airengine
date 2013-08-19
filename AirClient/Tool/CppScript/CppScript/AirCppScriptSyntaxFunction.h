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

		class	FunctionNode	:	public	Node{
		public:
			FunctionNode(){
				m_Type			=	enNT_Function;
				m_bOnlyDeclare	=	true;
				m_bVirtual		=	0;
				ieType			=	enCKWT_Unknown;
				m_uiLocalVariableSize	=	0;
			};

			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseImportExport(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseParameter(WordInfoVector& vecInfo,U32& idx);
			//virtual	enumSyntaxError		ParseFunction(WordInfoVector& vecInfo,U32& idx);

			virtual	enumSyntaxError		GenerateFunctionCode(AString& Buffer,U32& idx);

			U1							IsParamNameExist(CAString& strName);
			ParameterNode*				FindParameter(CAString& strName);
			
			ParameterNode				m_ReturnType;
			ParameterVector				m_vecParameter;
			U32							m_bOnlyDeclare;
			U32							m_bVirtual;
			enumCppKeyWordType			ieType;
		protected:
			U32							m_uiLocalVariableSize;
		};
	
	}
}
#endif // AirCppScriptSyntaxFunction_h__