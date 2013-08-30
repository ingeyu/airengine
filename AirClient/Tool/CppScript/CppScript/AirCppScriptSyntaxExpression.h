#ifndef AirCppScriptSyntaxExpression_h__
#define AirCppScriptSyntaxExpression_h__

#include "AirCppScriptSyntaxNode.h"

namespace	Air{
	namespace	CppScript{
		enum enumExpressionType{
			enET_Unknown,
			enET_Element,
			enET_Operator,
			enET_FunctionCall,
			enET_ThisCall,
			enET_New,
		};

		class	ExpressionNode	:	public	Node{
		public:
			ExpressionNode(){
				m_Type		=	enNT_Expression;
				eType		=	enET_Unknown;
				m_strName			=	"Exp";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseExpression(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			enumSyntaxError				LogicAnd(ExpressionNode* p[3],Assemble& asmGen);
			enumSyntaxError				LogicOr(ExpressionNode* p[3],Assemble& asmGen);
			enumSyntaxError				OpEqual(ExpressionNode* p[3],enumCppKeyWordType op,Assemble& asmGen);
			U32							GetJumpCondition();


			virtual	void				GenerateWriteCode(enumCppKeyWordType op,Assemble& asmGen);
			virtual	U1					WriteJumpAddress(Assemble& asmGen);
			virtual	U32					HasJump();
			enumExpressionType			eType;
			std::list<U32>				m_lstJump;
			};
		class	ExpressionElementNode	:	public	ExpressionNode{
		public:
			ExpressionElementNode(){
				eType		=	enET_Element;
				pObj		=	NULL;
				pCast		=	NULL;
				bAddress	=	false;
				bValue		=	false;
				bValue2		=	false;

				eSelfOperator[0]	=	enCKWT_Unknown;
				eSelfOperator[1]	=	enCKWT_Unknown;
				m_pIndex			=	NULL;
				m_strName			=	"ExpElement";
				bNot				=	false;
				bLogicNot			=	false;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseObjectCast(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				CheckSelfOperator(WordInfoVector& vecInfo,U32& idx,U32 bPost);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			virtual	void				GenerateWriteCode(enumCppKeyWordType op,Assemble& asmGen);
			Node*	pObj;
			Node*	pCast;
			U1		bAddress;
			U1		bValue;
			U1		bValue2;
			U1		bNot;
			U1		bLogicNot;
			enumCppKeyWordType	eSelfOperator[2];
			Node*				m_pIndex;
		};
		class	ExpressionOperatorNode	:	public	ExpressionNode{
		public:
			ExpressionOperatorNode(){
				eType		=	enET_Operator;
				uiPre		=	false;
				m_strName			=	"ExpOperator";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			void						CheckMultiOperator(WordType t,U32& idx);
			enumCppKeyWordType	eOperator;
			U1					uiPre;
		};
		class	FunctionCallExpressionNode	:	public	ExpressionNode{
		public:
			FunctionCallExpressionNode(){
				eType		=	enET_FunctionCall;
				pFunction	=	NULL;
				m_strName			=	"ExpFunctionCall";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseParameter(WordInfoVector& vecInfo,U32& idx);
			Node*						ParseFunctionName(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			Node*							pFunction;
			std::vector<Node*>				pParameterArray;
		};
		class	ThisCallExpressionNode	:	public	FunctionCallExpressionNode{
		public:
			ThisCallExpressionNode(){
				eType		=	enET_ThisCall;
				m_strName	=	"ExpThisCall";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
		};
		class	NewExpressionNode	:	public	FunctionCallExpressionNode{
		public:
			NewExpressionNode(){
				eType		=	enET_New;
				pFunction	=	NULL;
				m_strName	=	"New";
				m_pNewObject=NULL;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			ObjectType					m_NewType;
			Node*						m_pNewObject;
		};
	}
}
#endif // AirCppScriptSyntaxExpression_h__
