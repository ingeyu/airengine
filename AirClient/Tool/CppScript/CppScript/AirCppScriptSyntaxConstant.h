#ifndef AirCppScriptSyntaxConstant_h__
#define AirCppScriptSyntaxConstant_h__

#include "AirCppScriptSyntaxNode.h"

namespace	Air{
	namespace	CppScript{		


		class	ConstantNode	:	public	Node{
		public:
			ConstantNode(){
				m_Type			=	enNT_Constant;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			WordInfo ConstInfo;
		};
	}
}
#endif // AirCppScriptSyntaxConstant_h__
