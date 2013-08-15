#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptSyntaxConstant.h"

namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError ExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize = vecInfo.size();
			WordInfo& info = vecInfo[idx];
			WordType t = info.eType;
			Node* p	=	FindNode(info.str);
			if(p==NULL){
				return enSE_Unrecognized_Variable;
			}
			if(p->GetType()!=enNT_Variable &&	p->GetType()!=enNT_Parameter){
				return enSE_Unrecognized_Variable;
			}
			pLeftNode	=	p;
			if(idx+1>=uiSize){
				return enSE_UnexpectedEnd; 
			}
			t	=	vecInfo[++idx].eType;
			if(t.eWordtype==enWT_Operator){
				eOperator	=	t.eKeyword;
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				t	=	vecInfo[++idx].eType;
			}

			//if(t.eWordtype)

			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
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

	}
}