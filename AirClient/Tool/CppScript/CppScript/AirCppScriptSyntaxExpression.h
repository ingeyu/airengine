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
		};

		class	ExpressionNode	:	public	Node{
		public:
			ExpressionNode(){
				m_Type		=	enNT_Expression;
				eType		=	enET_Unknown;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseExpression(WordInfoVector& vecInfo,U32& idx);
			enumExpressionType	eType;
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
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseObjectCast(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				CheckSelfOperator(WordInfoVector& vecInfo,U32& idx,U32 bPost);
			Node*	pObj;
			Node*	pCast;
			U1		bAddress;
			U1		bValue;
			U1		bValue2;
			enumCppKeyWordType	eSelfOperator[2];
		};
		class	ExpressionOperatorNode	:	public	ExpressionNode{
		public:
			ExpressionOperatorNode(){
				eType		=	enET_Operator;
				uiPre		=	false;
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
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*							pFunction;
			std::vector<Node*>				pParameterArray;
		};

	}
}
#endif // AirCppScriptSyntaxExpression_h__
