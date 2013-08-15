#ifndef AirCppScriptSyntaxExpression_h__
#define AirCppScriptSyntaxExpression_h__

#include "AirCppScriptSyntaxNode.h"

namespace	Air{
	namespace	CppScript{

		class	ExpressionNode	:	public	Node{
		public:
			ExpressionNode(){
				m_Type		=	enNT_Expression;
				pLeftNode	=	NULL;
				pRightNode	=	NULL;
				eOperator	=	enCKWT_Unknown;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*				pLeftNode;
			Node*				pRightNode;
			enumCppKeyWordType	eOperator;
		};
		class	FunctionCallExpressionNode	:	public	Node{
		public:
			FunctionCallExpressionNode(){
				m_Type		=	enNT_FunctionCall_Expression;
				pFunction	=	NULL;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*							pFunction;
			std::vector<Node*>				pParameterArray;
		};
		class	NewObjectExpressionNode	:	public	Node{
		public:
			NewObjectExpressionNode(){
				m_Type		=	enNT_New_Object_Expression;
				pObject		=	NULL;
				uiNewCount	=	1;
			};
			Node*							pObject;
			std::vector<Node*>				pParameterArray;
			U32								uiNewCount;
		};
		class	DeleteObjectExpressionNode	:	public	Node{
		public:
			DeleteObjectExpressionNode(){
				m_Type		=	enNT_Delete_Object_Expression;
				pObject		=	NULL;
			};
			Node*							pObject;
		};
		class	ReturnExpressionNode	:	public	Node{
		public:
			ReturnExpressionNode(){
				m_Type		=	enNT_Return_Object_Expression;
				pReturn		=	NULL;
			};
			Node*							pReturn;
		};
	}
}
#endif // AirCppScriptSyntaxExpression_h__
