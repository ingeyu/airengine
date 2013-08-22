#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptSyntaxConstant.h"
#include "AirCppScriptSyntaxVariable.h"
#include "AirCppScriptSyntaxFunction.h"
#include "AirCppScriptAssemble.h"

namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError ExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			enumSyntaxError	e	=	enSE_OK;
			e	=	ParseExpression(vecInfo,idx);
			U32 uiSize = vecInfo.size();
			if(idx<uiSize){
				e	=	__ParseNode<ExpressionOperatorNode>(vecInfo,idx);
				if(e!=enSE_OK){
					return	enSE_UnexpectedEnd;
				}
				e	=	ParseExpression(vecInfo,idx);
				if(e!=enSE_OK){
					return	enSE_UnexpectedEnd;
				}
			}
			return e;
		}

		Air::CppScript::enumSyntaxError ExpressionNode::ParseExpression( WordInfoVector& vecInfo,U32& idx )
		{
			enumSyntaxError	e	=	enSE_OK;
			U32 uiSize = vecInfo.size();
			WordInfo& info = vecInfo[idx];
			WordType t = info.eType;
			if(t.eKeyword	==	enWDT_PreBracket){
				WordInfoVector firstStatement;
				e	=	FindBlock(vecInfo,idx,firstStatement,MakeType(enWT_Delimiter,enWDT_PreBracket),MakeType(enWT_Delimiter,enWDT_PostBracket),false);
				if(e!=enSE_OK){
					return	e;
				}
				U32 uiTemp	=	0;
				e	=	__ParseNode<ExpressionNode>(firstStatement,uiTemp);
				if(e!=enSE_OK){
					return e;
				}
				idx+=firstStatement.size()+2;
				if(idx>=vecInfo.size()){
					return enSE_OK;
				}
			}else{
				e	=	__ParseNode<ExpressionElementNode>(vecInfo,idx);
				if(e!=enSE_OK){
					e	=	__ParseNode<FunctionCallExpressionNode>(vecInfo,idx);
					if(e!=enSE_OK){
						return e;
					}
				}
			}
			return enSE_OK;
		}

		void	SaveValue(Node* pNode,Assemble& asmGen){
			VariableNode* pVar	=	(VariableNode*)(pNode);
			if(pVar->GetType()==enNT_Parameter){
				
				asmGen.Operator(eC_MOV_RM32_R32,eAR_EBP,0X14+pVar->m_uiOffset,eAR_EAX);
			}else{

				if(pVar->IsLocal()){
					asmGen.Operator(eC_MOV_RM32_R32,eAR_ESI,pVar->m_uiOffset,eAR_EAX);
				}else{

					asmGen.Operator(eC_MOV_R32_RM32,eAR_EBX,eAR_EAX);
					asmGen.Operator(eC_MOV_EAX_IMM32,eAR_EAX,pVar->m_uiOffset);
					asmGen.Operator(eC_MOV_RM32_R32,eAR_EAX,0,eAR_EBX);
				}
			}
		}

		Air::CppScript::enumSyntaxError ExpressionNode::GenerateFunctionCode( Assemble& asmGen )
		{
			if(m_lstChild.empty())
			{
				return enSE_Unknown_Error;
			}
			if(m_lstChild.size()==1){
				Node* pNode	=	*(m_lstChild.begin());
				if(pNode->GetType()!=enNT_Expression){
					return	enSE_Unknown_Error;
				}
				//ExpressionNode* pExp	=	(ExpressionNode*)pNode;
				//if(pExp->eType	==enET_Element){

				//}else if(pExp->eType	==enET_FunctionCall){

				//}else{
				//	return	enSE_Unknown_Error;
				//}
				return pNode->GenerateFunctionCode(asmGen);
			}
			if(m_lstChild.size()==3){
				ExpressionNode* p[3];
				int i=0;
				NodeList::iterator	itr	=	m_lstChild.begin();
				for(;itr!=m_lstChild.end();itr++,i++){
					p[i]	=	(ExpressionNode*)(*itr);
				}
				ExpressionElementNode* pLeft	=	(ExpressionElementNode*)(p[0]);
				p[2]->GenerateFunctionCode(asmGen);
				asmGen.Code(eC_PUSH_EAX);
				p[0]->GenerateFunctionCode(asmGen);
				asmGen.Code(eC_POP_EBX);
				ExpressionOperatorNode* pOperator	=	(ExpressionOperatorNode*)p[1];
				switch(pOperator->eOperator){
					case enOT_Add:					///<	+
						{
							asmGen.Operator(eC_ADD_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Sub:					///<	-
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Mul:					///<	*
						{
							//asmGen.Operator(eC_IMUL_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Div:					///<	/
						{
							//printf("div eax,ebx\n");
						}break;
					case enOT_Remain:				///<	%
						{

						}break;
					case enOT_Mov:					///<	=
						{
							
							asmGen.Operator(eC_MOV_R32_RM32,eAR_EAX,eAR_EBX);
							SaveValue(pLeft->pObj,asmGen);
							return enSE_OK;
						}break;
					case enOT_And:					///<	&
						{
							asmGen.Operator(eC_AND_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Or:					///<	|
						{
							asmGen.Operator(eC_OR_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Xor:					///<	^
						{
							asmGen.Operator(eC_XOR_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Not:					///<	~
						{

						}break;
					case enOT_Equal:					///<	==
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_NotEqual:				///<	!=
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Greater:				///<	>
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Less:					///<	<
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_GreaterEqual:			///<	>=
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_LessEqual:			///<	<=
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
						}break;
					case enOT_Increment:			///<	++
						{

						}break;
					case enOT_Decrement:			///<	--
						{

						}break;
					case enOT_AddEqual:				///<	+=
						{
							asmGen.Operator(eC_ADD_R32_RM32,eAR_EAX,eAR_EBX);
							SaveValue(pLeft->pObj,asmGen);

							return enSE_OK;
						}break;
					case enOT_SubEqual:				///<	-=
						{
							asmGen.Operator(eC_SUB_R32_RM32,eAR_EAX,eAR_EBX);
							SaveValue(pLeft->pObj,asmGen);
						}break;
					case enOT_MulEqual:				///<	*=
						{

						}break;
					case enOT_DivEqual:				///<	/=
						{

						}break;
					case enOT_RemainEqual:			///<	%=
						{

						}break;
					case enOT_AndEqual:				///<	&=
						{

						}break;
					case enOT_OrEqual:				///<	|=
						{

						}break;
					case enOT_LeftShift:			///<	<<
						{

						}break;
					case enOT_RightShift:			///<	>>
						{

						}break;
					case enOT_SquareBracketBegin:	///<	[
						{

						}break;
					case enOT_SquareBracketEnd:		///<	]
						{

						}break;
					case enOT_Colon:				///<	:
						{

						}break;
					case enOT_Question:				///<	?
						{

						}break;
					case enOT_LogicAnd:				///<	&&
						{

						}break;
					case enOT_LogicOr:				///<	||
						{

						}break;
					case enOT_LogicNot:				///<	!
						{

						}break;
					case enOT_PointorMember:		///<	->
						{

						}break;
					case enOT_Domain:				///<	::
						{

						}break;
				}


			}

			return enSE_Unknown_Error;
		}


		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			pFunction	=	ParseFunctionName(vecInfo,idx);//__CheckNextNodeType(vecInfo,idx,enNT_Function);
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
					
					FunctionNode* p	=	(FunctionNode*)pFunction;
					if(p->GetParameterCount()!=pParameterArray.size()){
						return enSE_Function_Parameter_Count_Not_Match;
					}
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

		Node* FunctionCallExpressionNode::ParseFunctionName( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiOld	=	idx;
			U32 uiSize	=	vecInfo.size();
			Node* pNode	=	FindNode(vecInfo[uiOld].str);
			if(pNode==NULL){
				return NULL;
			}
			if(pNode->GetType()==enNT_Function){
				idx++;
				return pNode;
			}else if(pNode->GetType()==enNT_NameSpace){
				while(pNode){
					
					if(uiOld+2>=uiSize){
						return NULL;
					}
					WordType t0= vecInfo[uiOld+1].eType;
					WordType t1= vecInfo[uiOld+2].eType;
					if(t0.eKeyword!=enOT_Colon||t1.eKeyword!=enOT_Colon){
						return NULL;
					}
					uiOld+=2;
					if(uiOld+1>=uiSize){
						return NULL;
					}
					uiOld++;
					pNode	=	pNode->FindNode(vecInfo[uiOld].str,enNT_Unknown,false);
					if(pNode==NULL){
						return NULL;
					}
					if(pNode->GetType()==enNT_Function){
						uiOld++;
						idx=uiOld;
						return	pNode;
					}
					if(pNode->GetType()==enNT_NameSpace){
						uiOld++;
						continue;
					}
				}
			}
			return NULL;
		}

		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::GenerateFunctionCode( Assemble& asmGen )
		{
			U32 uiParamSize	=	pParameterArray.size();
			for(U32 i=0;i<uiParamSize;i++){
				U32 idx	=	uiParamSize-i-1;
				pParameterArray[idx]->GenerateFunctionCode(asmGen);
				asmGen.Code(eC_PUSH_EAX);
			}
			FunctionNode* p	=	(FunctionNode*)pFunction;
			asmGen.Call(p->GetEntry());
			return enSE_OK;
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
			if(idx<vecInfo.size()){
				t = vecInfo[idx].eType;
				if(t.uiType	==	MakeType(enWT_Operator,enOT_SquareBracketBegin)){
					idx++;
					e	=	__ParseNode<ExpressionElementNode>(vecInfo,idx,&m_pIndex);
					if(e!=enSE_OK){
						return e;
					}
					t = vecInfo[idx].eType;
					if(t.uiType	!=	MakeType(enWT_Operator,enOT_SquareBracketEnd)){
						return enSE_Index_Operator_Miss_End_Of_SquareBracket;
					}else{
						idx++;
					}
				}
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
					
					idx++;
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
					
					idx++;
				}else{
					if(bPost==1){
						idx--;
					}
				}
			}
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError ExpressionElementNode::GenerateFunctionCode( Assemble& asmGen )
		{
			if(pObj->GetType()==enNT_Constant){
				ConstantNode* pConstant	=	(ConstantNode*)pObj;
				asmGen.Operator(eC_MOV_EAX_IMM32,eAR_EAX,pConstant->ConstInfo.iVal);
				return enSE_OK;
			}
			VariableNode* pVar	=	(VariableNode*)(pObj);
			char str[32];
			AssembleRegister r = eAR_EBP;
			U32	uiOffset		=	pVar->m_uiOffset;
			if(pVar->GetType()==enNT_Parameter){
				
				uiOffset	=	pVar->m_uiOffset+0x14;
			}else{
				if(!pVar->IsLocal()){
					sprintf_s(str,"[%xh]",pVar->m_uiOffset);
				}else{
					
					r	=	eAR_ESI;
				}
			}
			

			
			asmGen.Operator(eC_MOV_R32_RM32,eAR_EAX,r,uiOffset);

			if(eSelfOperator[1]==enOT_Increment){
				asmGen.Operator(eC_MOV_R32_RM32,eAR_EBX,eAR_EAX);
				asmGen.Code(eC_INC_EBX);
				asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EBX);
			}else if(eSelfOperator[1]==enOT_Decrement){
				asmGen.Operator(eC_MOV_R32_RM32,eAR_EBX,eAR_EAX);
				asmGen.Code(eC_DEC_EBX);
				asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EBX);
			}else if(eSelfOperator[1]==enOT_Decrement){;
				asmGen.Code(eC_INC_EAX);
				asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EAX);
			}else if(eSelfOperator[1]==enOT_Decrement){
				asmGen.Code(eC_DEC_EAX);
				asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EAX);
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
			if(t.eWordtype!=enWT_Operator){
				return;
			}
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
				}else if(t.eKeyword	==	enOT_Greater){
					eOperator	=	enOT_PointorMember;
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
			case	enOT_Colon:{
				if(t.eKeyword	==	enOT_Colon){
					eOperator	=	enOT_Domain;
					idx++;
				}
							   }break;
			}
			
		}

	}
}