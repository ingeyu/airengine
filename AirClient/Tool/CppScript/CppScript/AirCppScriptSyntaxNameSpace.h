#ifndef AirCppScriptSyntaxNameSpace_h__
#define AirCppScriptSyntaxNameSpace_h__

#include "AirCppScriptSyntaxNode.h"
namespace	Air{
	namespace	CppScript{		

		class	NameSpaceNode	:	public	Node{
		public:
			NameSpaceNode(){
				m_Type			=	enNT_NameSpace;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
		};
	}
}
#endif // AirCppScriptSyntaxNameSpace_h__
