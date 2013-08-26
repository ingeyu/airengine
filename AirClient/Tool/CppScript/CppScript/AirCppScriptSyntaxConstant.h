#ifndef AirCppScriptSyntaxConstant_h__
#define AirCppScriptSyntaxConstant_h__

#include "AirCppScriptSyntaxNode.h"

namespace	Air{
	namespace	CppScript{		


		class	ConstantNode	:	public	Node{
		public:
			ConstantNode(){
				m_Type			=	enNT_Constant;
				m_uiOffset		=	0;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			WordInfo	ConstInfo;
			U32			m_uiOffset;
		};
	}
}
#endif // AirCppScriptSyntaxConstant_h__
