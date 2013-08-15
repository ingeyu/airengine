#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptSyntaxConstant.h"

namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError ExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			//U32 uiSize = vecInfo.size();
			//WordInfo& info = vecInfo[idx];
			//WordType t = info.eType;
			//Node* p	=	FindNode(info.str);
			//if(p==NULL){
			//	return enSE_Unrecognized_Variable;
			//}
			//if(p->GetType()!=enNT_Variable &&	p->GetType()!=enNT_Parameter){
			//	return enSE_Unrecognized_Variable;
			//}
			//pLeftNode	=	p;
			//if(idx+1>=uiSize){
			//	return enSE_UnexpectedEnd; 
			//}
			//t	=	vecInfo[++idx].eType;
			//if(t.eWordtype==enWT_Operator){
			//	eOperator	=	t.eKeyword;
			//	if(idx+1>=uiSize){
			//		return enSE_UnexpectedEnd; 
			//	}
			//	t	=	vecInfo[++idx].eType;
			//}

			////if(t.eWordtype)

			enumSyntaxError	e	=	__ParseNode<ExpressionElementNode>(vecInfo,idx);
			if(e!=enSE_OK){
				e	=	__ParseNode<FunctionCallExpressionNode>(vecInfo,idx);
				if(e!=enSE_OK){
					return e;
				}
			}
			U32 uiSize = vecInfo.size();
			if(idx<uiSize){
				e	=	__ParseNode<ExpressionOperatorNode>(vecInfo,idx);
				if(e!=enSE_OK){
					return	enSE_UnexpectedEnd;
				}
				e	=	__ParseNode<ExpressionNode>(vecInfo,idx);
				if(e!=enSE_OK){
					return	enSE_UnexpectedEnd;
				}
			}
			return e;
		}

		Air::CppScript::enumSyntaxError ExpressionNode::ParseExpression( WordInfoVector& vecInfo,U32& idx )
		{
			return	enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			pFunction	=	__CheckNextNodeType(vecInfo,idx,enNT_Function);
			if(pFunction==NULL)
				return enSE_UnDefine_Function;
			if(idx+1>=uiSize)
				return enSE_UnexpectedEnd;
			WordType t = vecInfo[idx].eType;
			if(t.uiType!=MakeType(enWT_Delimiter,enWDT_PreBracket)){
				return enSE_UnexpectedEnd;
			}
			if(idx+1>=uiSize)
				return enSE_UnexpectedEnd;
			t = vecInfo[++idx].eType;
			for(;idx<uiSize;){

				if(t.uiType==MakeType(enWT_Delimiter,enWDT_Comma)){
					if(idx+1>=uiSize)
						return enSE_UnexpectedEnd;
					t = vecInfo[++idx].eType;
					continue;
				}else if(t.uiType==MakeType(enWT_Delimiter,enWDT_PostBracket)){
					idx++;
					return enSE_OK;
				}else if(t.eWordtype	==	enWT_Constant){
					ConstantNode* pNode = new ConstantNode();
					enumSyntaxError	e	=	pNode->Parse(vecInfo,idx);
					if(e==enSE_OK){
						AddChild(pNode);
						pParameterArray.push_back(pNode);
						continue;
					}else{
						return enSE_UnexpectedEnd;
					}
				}else if(t.eWordtype	==	enWT_Unknown){
					Node* pNode	=	FindNode(vecInfo[idx].str);
					if(pNode==NULL){
						return enSE_Unrecognized_Variable;
					}
					enumNodeType eNT = pNode->GetType();
					if(eNT==enNT_Variable	||	eNT == enNT_Parameter){
						pParameterArray.push_back(pNode);
						if(idx+1>=uiSize)
							return enSE_UnexpectedEnd;
						t = vecInfo[++idx].eType;
						continue;
					}
				}else{
					return enSE_UnexpectedEnd;
				}
				return enSE_UnexpectedEnd;
			}

			return enSE_UnexpectedEnd;
		}




		Air::CppScript::enumSyntaxError ExpressionElementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			WordType t = vecInfo[idx].eType;
			enumSyntaxError e=enSE_OK;
			CheckSelfOperator(vecInfo,idx,0);

			if(t.uiType	==	MakeType(enWT_Operator,enOT_Mul)){
				bValue	=	true;
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[++idx].eType;
			}
			if(t.uiType	==	MakeType(enWT_Operator,enOT_Mul)){
				bValue2	=	true;
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[++idx].eType;
			}
			if(t.uiType	==	MakeType(enWT_Delimiter,enWDT_PreBracket)){
				e	=	ParseObjectCast( vecInfo,idx);
				if(e!=enSE_OK){
					return e;
				}
			}
			t = vecInfo[idx].eType;
			if(t.uiType	==	MakeType(enWT_Operator,enOT_And)){
				bAddress	=	true;
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[++idx].eType;
			}
			if(t.eWordtype	==	enWT_Unknown){
				pObj	=	FindNode(vecInfo[idx].str);
				if(pObj==NULL){
					return enSE_UnexpectedEnd;
				}
				if(pObj->GetType()==enNT_Variable||pObj->GetType()==enNT_Parameter){
					idx++;
				}else{
					return enSE_UnexpectedEnd;
				}
			}else if(t.eWordtype	==	enWT_Constant){
				pObj = GetRootNode()->FindNode(vecInfo[idx].str);;
				if(pObj==NULL){
					pObj	=	new ConstantNode;
					pObj->Parse(vecInfo,idx);
					GetRootNode()->AddChild(pObj);
				}else{
					idx++;
				}
				
			}else{
				return enSE_UnexpectedEnd;
			}
			CheckSelfOperator(vecInfo,idx,1);
			return	enSE_OK;
		}

		Air::CppScript::enumSyntaxError ExpressionElementNode::ParseObjectCast( WordInfoVector& vecInfo,U32& idx )
		{
			return	enSE_UnexpectedEnd;
		}

		enumSyntaxError ExpressionElementNode::CheckSelfOperator( WordInfoVector& vecInfo,U32& idx,U32 bPost )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_OK;
			WordType t = vecInfo[idx].eType;
			if(t.uiType	==	MakeType(enWT_Operator,enOT_Add)){
				if(bPost==0)
					eSelfOperator[bPost]	=	enOT_Add;
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[++idx].eType;
				if(t.uiType	==	MakeType(enWT_Operator,enOT_Add)){
					eSelfOperator[bPost]	=	enOT_Increment;
					if(idx+1>=uiSize)
						return enSE_UnexpectedEnd;
					t = vecInfo[++idx].eType;
				}else{
					if(bPost==1){
						idx--;
					}
				}
			}else	if(t.uiType	==	MakeType(enWT_Operator,enOT_Sub)){
				if(bPost==0)
					eSelfOperator[bPost]	=	enOT_Sub;
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[++idx].eType;
				if(t.uiType	==	MakeType(enWT_Operator,enOT_Sub)){
					eSelfOperator[bPost]	=	enOT_Decrement;
					if(idx+1>=uiSize)
						return enSE_UnexpectedEnd;
					t = vecInfo[++idx].eType;
				}else{
					if(bPost==1){
						idx--;
					}
				}
			}
			return enSE_OK;
		}


		Air::CppScript::enumSyntaxError ExpressionOperatorNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			WordType t = vecInfo[idx].eType;
			enumSyntaxError e=enSE_OK;
			if(t.eWordtype	!=	enWT_Operator)
				return	enSE_Expression_Need_A_Operator;
			eOperator	=	t.eKeyword;
			CheckMultiOperator(vecInfo[idx+1].eType,idx);
			
			
			idx++;
			return	enSE_OK;
		}

		void ExpressionOperatorNode::CheckMultiOperator( WordType t,U32& idx)
		{
			if(t.eWordtype!=enWT_Operator)
				return;
			switch(eOperator){
			case enOT_Add:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_AddEqual;
					idx++;
				}
						  }break;
			case enOT_Sub:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_SubEqual;
					idx++;
				}
						  }break;
			case enOT_Mul:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_MulEqual;
					idx++;
				}
						  }break;
			case enOT_Div:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_DivEqual;
					idx++;
				}
						  }break;
			case enOT_And:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_AndEqual;
					idx++;
				}else if(t.eKeyword	==	enOT_And){
					eOperator	=	enOT_LogicAnd;
					idx++;
				}
						  }break;
			case enOT_Or:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_OrEqual;
					idx++;
				}else if(t.eKeyword	==	enOT_And){
					eOperator	=	enOT_LogicOr;
					idx++;
				}
						 }break;
			case enOT_Remain:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_RemainEqual;
					idx++;
				}
							 }break;
			case enOT_Greater:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_GreaterEqual;
					idx++;
				}else if(t.eKeyword	==	enOT_Greater){
					eOperator	=	enOT_RightShift;
					idx++;
				}
						  }break;
			case enOT_Less:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_LessEqual;
					idx++;
				}else if(t.eKeyword	==	enOT_Less){
					eOperator	=	enOT_LeftShift;
					idx++;
				}
						  }break;
			case enOT_Mov:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_Equal;
					idx++;
				}
						   }break;
			case enOT_LogicNot:{
				if(t.eKeyword	==	enOT_Mov){
					eOperator	=	enOT_NotEqual;
					idx++;
				}
						   }break;
			}
		}

	}
}