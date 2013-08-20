#ifndef AirCppScriptSyntaxStatement_h__
#define AirCppScriptSyntaxStatement_h__

#include "AirCppScriptSyntaxVariable.h"

namespace	Air{
	namespace	CppScript{
		enum	enumStatementType{
			enST_Unknown,
			enST_If,
			enST_For,
			enST_While,
			enST_Switch,
			enST_New,
			enST_Delete,
			enST_Return,
		};
		class	StatementNode	:	public	Node{
		public:
			StatementNode(){
				m_Type			=	enNT_Statement;
				m_sType			=	enST_Unknown;
			};
			virtual	enumSyntaxError	Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError			ParseSubStatement(WordInfoVector& vecInfo,U32& idx);

			virtual	enumSyntaxError		GenerateFunctionCode(Assemble& asmGen);
			enumStatementType		m_sType;
		};

		class	IfStatementNode	:	public	StatementNode
		{
		public:
			IfStatementNode(){
				m_sType			=	enST_If;
				pConditionExp	=	NULL;
				m_strName		=	"If";
			};
			virtual	enumSyntaxError	Parse(WordInfoVector& vecInfo,U32& idx);
			Node*	pConditionExp;
		};
		class	ForStatementNode	:	public	StatementNode
		{
		public:
			ForStatementNode(){
				m_sType			=	enST_For;
				pInitExp		=	NULL;
				pConditionExp	=	NULL;
				pIterExp		=	NULL;
				m_strName		=	"For";
			};
			virtual	enumSyntaxError	Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError	ParseCondition(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError	ParseCode(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError	ParseSubCondition_Init(WordInfoVector& vecInfo);
			enumSyntaxError	ParseSubCondition_Condition(WordInfoVector& vecInfo);
			enumSyntaxError	ParseSubCondition_Iter(WordInfoVector& vecInfo);

			virtual	enumSyntaxError		GenerateFunctionCode(Assemble& asmGen);

			Node*	pInitExp;
			Node*	pConditionExp;
			Node*	pIterExp;
		};
		class	WhileStatementNode	:	public	StatementNode
		{
		public:
			WhileStatementNode(){
				m_sType			=	enST_While;
			};
		};
		class	SwitchStatementNode	:	public	StatementNode
		{
		public:
			SwitchStatementNode(){
				m_sType			=	enST_Switch;
			};
		};
		class	NewStatementNode	:	public	StatementNode{
		public:
			NewStatementNode(){
				m_sType		=	enST_New;
				pObject		=	NULL;
				uiNewCount	=	1;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*							pObject;
			U32								uiNewCount;
		};
		class	DeleteStatementNode	:	public	StatementNode{
		public:
			DeleteStatementNode(){
				m_sType		=	enST_Delete;
				pObject		=	NULL;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*							pObject;
		};
		class	ReturnStatementNode	:	public	StatementNode{
		public:
			ReturnStatementNode(){
				m_sType		=	enST_Return;
				pReturn		=	NULL;
				m_strName		=	"Return";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*							pReturn;
		};
	}
}
#endif // AirCppScriptSyntaxStatement_h__
