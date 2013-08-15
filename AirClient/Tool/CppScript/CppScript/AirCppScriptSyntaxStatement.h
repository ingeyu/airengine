#ifndef AirCppScriptSyntaxStatement_h__
#define AirCppScriptSyntaxStatement_h__

#include "AirCppScriptSyntaxVariable.h"

namespace	Air{
	namespace	CppScript{
		class	StatementNode	:	public	Node{
		public:
			StatementNode(){
				m_Type			=	enNT_Statement;
			};

		};
		class	VariableStatementNode	:	public	VariableNode{
		public:
			VariableStatementNode(){
				m_Type			=	enNT_Statement;
			};

		};
		class	IfStatementNode	:	public	StatementNode
		{
		public:
			IfStatementNode(){
				m_Type			=	enNT_IfStatement;
			};
		};
		class	ForStatementNode	:	public	StatementNode
		{
		public:
			ForStatementNode(){
				m_Type			=	enNT_ForStatement;
			};
		};
		class	WhileStatementNode	:	public	StatementNode
		{
		public:
			WhileStatementNode(){
				m_Type			=	enNT_WhileStatement;
			};
		};
	}
}
#endif // AirCppScriptSyntaxStatement_h__
