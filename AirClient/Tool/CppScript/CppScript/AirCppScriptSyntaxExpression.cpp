#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptSyntaxConstant.h"
#include "AirCppScriptSyntaxVariable.h"

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

		Air::CppScript::enumSyntaxError ExpressionNode::GenerateFunctionCode( AString& Buffer,U32& idx )
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
				return pNode->GenerateFunctionCode(Buffer,idx);
			}
			if(m_lstChild.size()==3){
				ExpressionNode* p[3];
				int i=0;
				NodeList::iterator	itr	=	m_lstChild.begin();
				for(;itr!=m_lstChild.end();itr++,i++){
					p[i]	=	(ExpressionNode*)(*itr);
				}
				ExpressionElementNode* pLeft	=	(ExpressionElementNode*)(p[0]);
				p[2]->GenerateFunctionCode(Buffer,idx);
				printf("push eax\n");
				p[0]->GenerateFunctionCode(Buffer,idx);
				printf("pop ebx\n");
				ExpressionOperatorNode* pOperator	=	(ExpressionOperatorNode*)p[1];
				switch(pOperator->eOperator){
					case enOT_Add:					///<	+
						{
							printf("add eax,ebx\n");
						}break;
					case enOT_Sub:					///<	-
						{
							printf("sub eax,ebx\n");
						}break;
					case enOT_Mul:					///<	*
						{
							printf("imul eax,ebx\n");
						}break;
					case enOT_Div:					///<	/
						{
							printf("div eax,ebx\n");
						}break;
					case enOT_Remain:				///<	%
						{

						}break;
					case enOT_Mov:					///<	=
						{
							printf("mov eax,ebx\n");
							if(pLeft->pObj->GetType()==enNT_Parameter){
								printf("mov [ebp+14h],eax\n");
							}else{
								VariableNode* pVar	=	(VariableNode*)(pLeft->pObj);
								if(pVar->IsLocal()){
									printf("mov [esi+%d],eax\n",pVar->m_uiOffset);
								}else{
									printf("mov [%d],eax\n",pVar->m_uiOffset);
								}
							}
							return enSE_OK;
						}break;
					case enOT_And:					///<	&
						{
							printf("and eax,ebx");
						}break;
					case enOT_Or:					///<	|
						{
							printf("or eax,ebx");
						}break;
					case enOT_Xor:					///<	^
						{
							printf("xor eax,ebx");
						}break;
					case enOT_Not:					///<	~
						{

						}break;
					case enOT_Equal:					///<	==
						{
							printf("sub eax,ebx\n");
						}break;
					case enOT_NotEqual:				///<	!=
						{
							printf("sub eax,ebx\n");
						}break;
					case enOT_Greater:				///<	>
						{
							printf("sub eax,ebx\n");
						}break;
					case enOT_Less:					///<	<
						{
							printf("sub eax,ebx\n");
						}break;
					case enOT_GreaterEqual:			///<	>=
						{

						}break;
					case enOT_LessEqual:			///<	<=
						{

						}break;
					case enOT_Increment:			///<	++
						{

						}break;
					case enOT_Decrement:			///<	--
						{

						}break;
					case enOT_AddEqual:				///<	+=
						{
							printf("add eax,ebx\n");
							if(pLeft->pObj->GetType()==enNT_Parameter){
								printf("mov [ebp+14h],eax\n");
							}else{
								VariableNode* pVar	=	(VariableNode*)(pLeft->pObj);
								if(pVar->IsLocal()){
									printf("mov [esi+%d],eax\n",pVar->m_uiOffset);
								}else{
									printf("mov [%d],eax\n",pVar->m_uiOffset);
								}
							}

							return enSE_OK;
						}break;
					case enOT_SubEqual:				///<	-=
						{
							printf("sub eax,ebx\n");
							if(pLeft->pObj->GetType()==enNT_Parameter){
								printf("mov [ebp+14h],eax\n");
							}else{
								VariableNode* pVar	=	(VariableNode*)(pLeft->pObj);
								if(pVar->IsLocal()){
									printf("mov [esi+%d],eax\n",pVar->m_uiOffset);
								}else{
									printf("mov [%d],eax\n",pVar->m_uiOffset);
								}
							}
						}break;
					case enOT_MulEqual:				///<	*/
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

		Air::CppScript::enumSyntaxError ExpressionElementNode::GenerateFunctionCode( AString& Buffer,U32& idx )
		{
			if(pObj->GetType()==enNT_Constant){
				ConstantNode* pConstant	=	(ConstantNode*)pObj;
				printf("mov eax,%xh\n",pConstant->ConstInfo.iVal);
				return enSE_OK;
			}
			VariableNode* pVar	=	(VariableNode*)(pObj);
			char str[32];
			
			if(pVar->GetType()==enNT_Parameter){
				sprintf_s(str,"[ebp+%xh]",pVar->m_uiOffset+0x14);
				
			}else{
				if(!pVar->IsLocal()){
					sprintf_s(str,"[%xh]",pVar->m_uiOffset);
				}else{
					sprintf_s(str,"[esi+%d]",pVar->m_uiOffset);
				}
			}
			

			printf("mov eax,%s\n",str);

			if(eSelfOperator[1]==enOT_Increment){
				printf("mov ebx,eax\n");
				printf("add ebx,1\n");
				printf("mov %s,ebx\n",str);
			}else if(eSelfOperator[1]==enOT_Decrement){
				printf("mov ebx,eax\n");
				printf("sub ebx,1\n");
				printf("mov %s,ebx\n",str);
			}else if(eSelfOperator[1]==enOT_Decrement){;
				printf("add eax,1\n");
				printf("mov %s,eax\n",str);
			}else if(eSelfOperator[1]==enOT_Decrement){
				printf("sub eax,1\n");
				printf("mov %s,eax\n",str);
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