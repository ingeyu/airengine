#ifndef AirCppScriptSyntaxVariable_h__
#define AirCppScriptSyntaxVariable_h__

#include "AirCppScriptSyntaxNode.h"

namespace	Air{
	namespace	CppScript{		


		class	VariableNode	:	public	Node{
		public:
			VariableNode(){
				m_bHasInitValue	=	0;
				m_bSub			=	0;
				m_Type			=	enNT_Variable;
				pNodePtr		=	NULL;
				uiArrayCount	=	NULL;
				bHasDefault		=	0;
				m_pRightExpression	=	NULL;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			ObjectType					VariableType;
			AString						strDefault;
			U32							bHasDefault;
			U32							uiArrayCount;
			Node*						pNodePtr;
			AString						m_strInitValue;
			U32							m_bHasInitValue;
			U32							m_bSub;
			WordInfo					m_InitInfo;
			Node*						m_pRightExpression;
		};
	}
}
#endif // AirCppScriptSyntaxVariable_h__
