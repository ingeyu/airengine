#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptSyntaxConstant.h"
#include "AirCppScriptSyntaxVariable.h"
#include "AirCppScriptSyntaxFunction.h"
#include "AirCppScriptAssemble.h"
#include "AirCppScriptSyntaxObject.h"

namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError ExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			enumSyntaxError	e	=	enSE_OK;
			SetErrorInfo(vecInfo[idx]);
			e	=	ParseExpression(vecInfo,idx);
			if(e!=enSE_OK)
				return e;
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
				if(vecInfo[idx].eType.uiType	==	MakeType(enWT_CppKeyWord,enCKWT_New)){
					e	=	__ParseNode<NewExpressionNode>(vecInfo,idx);
					if(e!=enSE_OK){
						return e;
					}
				}else{
					e	=	__ParseNode<ThisCallExpressionNode>(vecInfo,idx);
					if(e!=enSE_OK){
						e	=	__ParseNode<ExpressionElementNode>(vecInfo,idx);
						if(e!=enSE_OK){
							e	=	__ParseNode<FunctionCallExpressionNode>(vecInfo,idx);
							if(e!=enSE_OK){
								return e;
							}
						}
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
					asmGen.Operator(eC_MOV_RM32_R32,eAR_EBP,pVar->m_uiOffset,eAR_EAX);
				}else if(pVar->IsMember()){
					asmGen.Operator(eC_MOV_RM32_R32,eAR_ESI,pVar->m_uiOffset,eAR_EAX);
				}else{
					//代码实现 全局变量重定位问题
					//Code Impl Global Variable Load Relocaltion
					asmGen.Call(asmGen.GetCurrentOffset()+5);
					U32	uiOffset	=	pVar->m_uiOffset	-	asmGen.GetCurrentOffset();
					asmGen.Pop(eAR_EBX);
					asmGen.Mov_RM32R32(eAR_EBX,uiOffset,eAR_EAX);
				}
			}
		}
		U32 ExpressionNode::GetJumpCondition()
		{
			U32 uiSize	=	m_lstChild.size();
			if(uiSize==1){
				ExpressionNode* pExp	=	(ExpressionNode*)(*m_lstChild.begin());
				return pExp->GetJumpCondition();
			}
			if(uiSize<3)
			{
				return eCEx_JZ_REL32;
			}

			ExpressionNode* p[3];
			int i=0;
			NodeList::iterator	itr	=	m_lstChild.begin();
			for(;itr!=m_lstChild.end();itr++,i++){
				p[i]	=	(ExpressionNode*)(*itr);
			}
			ExpressionOperatorNode* pOperator	=	(ExpressionOperatorNode*)p[1];
			switch(pOperator->eOperator){
				case enOT_LogicAnd:
				case enOT_LogicOr:{
					return p[2]->GetJumpCondition();
								  }break;
				case enOT_Equal:
				case enOT_NotEqual:{
					return eCEx_JZ_REL32;
								}break;
				case enOT_Greater:				///<	>
					{
						return eCEx_JG_REL32;
					}break;
				case enOT_Less:					///<	<
					{
						return eCEx_JL_REL32;
					}break;
				case enOT_GreaterEqual:			///<	>=
					{
						return eCEx_JGE_REL32;
					}break;
				case enOT_LessEqual:			///<	<=
					{
						return eCEx_JLE_REL32;
					}break;
			};
			return eCEx_JZ_REL32;
		}
		Air::CppScript::enumSyntaxError ExpressionNode::GenerateCode( Assemble& asmGen )
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

				return pNode->GenerateCode(asmGen);
			}
			if(m_lstChild.size()==3){
				ExpressionNode* p[3];
				int i=0;
				NodeList::iterator	itr	=	m_lstChild.begin();
				for(;itr!=m_lstChild.end();itr++,i++){
					p[i]	=	(ExpressionNode*)(*itr);
				}
				ExpressionOperatorNode* pOperator	=	(ExpressionOperatorNode*)p[1];

				if(pOperator->eOperator ==	enOT_LogicAnd){
					return LogicAnd(p,asmGen);
				}else if(pOperator->eOperator ==	enOT_LogicOr){
					return LogicOr(p,asmGen);
				}else  if(
					pOperator->eOperator	==	enOT_Mov		||
					pOperator->eOperator	==	enOT_AddEqual	||
					pOperator->eOperator	==	enOT_SubEqual	||
					pOperator->eOperator	==	enOT_AndEqual	||
					pOperator->eOperator	==	enOT_OrEqual	||
					pOperator->eOperator	==	enOT_MulEqual	||
					pOperator->eOperator	==	enOT_DivEqual
					)
				{
					return OpEqual(p,pOperator->eOperator,asmGen);
				}
				ExpressionElementNode* pLeft	=	(ExpressionElementNode*)(p[0]);
				p[2]->GenerateCode(asmGen);
				asmGen.Code(eC_PUSH_EAX);
				p[0]->GenerateCode(asmGen);
				asmGen.Code(eC_POP_EBX);
				
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
							asmGen.IMulR32R32(eAR_EAX,eAR_EBX);
						}break;
					case enOT_Div:					///<	/
						{
							asmGen.Mov_R32R32(eAR_ECX,eAR_EBX);
							asmGen.IDiv();
							//printf("div eax,ebx\n");
						}break;
					case enOT_Remain:				///<	%
						{
							asmGen.Mov_R32R32(eAR_ECX,eAR_EBX);
							asmGen.IDiv();
							asmGen.Mov_R32R32(eAR_EAX,eAR_EDX);
						}break;
					case enOT_Mov:					///<	=
						{
							
							asmGen.Mov_R32R32(eAR_EAX,eAR_EBX);
							SaveValue(pLeft->pObj,asmGen);
							return enSE_OK;
						}break;
					case enOT_And:					///<	&
						{
							asmGen.AndR32R32(eAR_EAX,eAR_EBX);
						}break;
					case enOT_Or:					///<	|
						{
							asmGen.OrR32R32(eAR_EAX,eAR_EBX);
						}break;
					case enOT_Xor:					///<	^
						{
							asmGen.XorR32R32(eAR_EAX,eAR_EBX);
						}break;
					case enOT_Not:					///<	~
						{
							asmGen.Not(eAR_EAX);
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
							asmGen.IMulR32R32(eAR_EAX,eAR_EBX);
							SaveValue(pLeft->pObj,asmGen);
						}break;
					case enOT_DivEqual:				///<	/=
						{
							asmGen.Mov_R32R32(eAR_ECX,eAR_EBX);
							asmGen.IDiv();
							SaveValue(pLeft->pObj,asmGen);
						}break;
					case enOT_RemainEqual:			///<	%=
						{
							asmGen.Mov_R32R32(eAR_ECX,eAR_EBX);
							asmGen.IDiv();
							asmGen.Mov_R32R32(eAR_EAX,eAR_EDX);
							SaveValue(pLeft->pObj,asmGen);
						}break;
					case enOT_AndEqual:				///<	&=
						{
							asmGen.AndR32R32(eAR_EAX,eAR_EBX);
							SaveValue(pLeft->pObj,asmGen);
						}break;
					case enOT_OrEqual:				///<	|=
						{
							asmGen.OrR32R32(eAR_EAX,eAR_EBX);
							SaveValue(pLeft->pObj,asmGen);
						}break;
					case enOT_LeftShift:			///<	<<
						{
							//p[2]->
						}break;
					case enOT_RightShift:			///<	>>
						{
							//
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
							asmGen.AndR32R32(eAR_EAX,eAR_EBX);
						}break;
					case enOT_LogicOr:				///<	||
						{
							asmGen.OrR32R32(eAR_EAX,eAR_EBX);
						}break;
					case enOT_LogicNot:				///<	!
						{
							//asmGen.LogicNot(eAR_EAX);
							//不合法
						}break;
					case enOT_PointorMember:		///<	->
						{

						}break;
					case enOT_Domain:				///<	::
						{
							//asmGen.Mov_R32R32(eAR_ECX,eAR_EBX);
							//asmGen.IDiv();
							//asmGen.Mov_R32R32(eAR_EAX,eAR_EDX);
						}break;
				}


			}

			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError ExpressionNode::LogicAnd( ExpressionNode* p[3],Assemble& asmGen )
		{
			
			asmGen.Code(eC_PUSH_EAX);
			p[0]->GenerateCode(asmGen);
			asmGen.Test(eAR_EAX);
			asmGen.JumpCondition(InserveJumpCondition((Code1Ex)p[0]->GetJumpCondition()));
			m_lstJump.push_back(asmGen.GetCurrentOffset());
			p[2]->GenerateCode(asmGen);
			asmGen.Test(eAR_EAX);
			asmGen.JumpCondition(InserveJumpCondition((Code1Ex)p[2]->GetJumpCondition()));
			m_lstJump.push_back(asmGen.GetCurrentOffset());
			return enSE_OK;
		}
		Air::CppScript::enumSyntaxError ExpressionNode::LogicOr( ExpressionNode* p[3],Assemble& asmGen )
		{
			asmGen.Code(eC_PUSH_EAX);
			p[0]->GenerateCode(asmGen);
			asmGen.Test(eAR_EAX);
			asmGen.JumpCondition((Code1Ex)p[0]->GetJumpCondition());
			U32 uiJump0	=	asmGen.GetCurrentOffset();
			p[2]->GenerateCode(asmGen);
			asmGen.Test(eAR_EAX);
			asmGen.JumpCondition(InserveJumpCondition((Code1Ex)p[0]->GetJumpCondition()));
			asmGen.WriteAddress_JumpHere(uiJump0);
			m_lstJump.push_back(asmGen.GetCurrentOffset());
			return enSE_OK;
		}
		void ExpressionNode::GenerateWriteCode( enumCppKeyWordType op,Assemble& asmGen )
		{
			if(m_lstChild.size()==1){
				Node* pNode	=	*(m_lstChild.begin());
				if(pNode->GetType()!=enNT_Expression){
					return;
				}
				return ((ExpressionNode*)pNode)->GenerateWriteCode(op,asmGen);
			}
		}

		Air::CppScript::enumSyntaxError ExpressionNode::OpEqual( ExpressionNode* p[3],enumCppKeyWordType op,Assemble& asmGen )
		{
			p[2]->GenerateCode(asmGen);
			p[0]->GenerateWriteCode(op,asmGen);
			return enSE_OK;
		}

		U1 ExpressionNode::WriteJumpAddress(Assemble& asmGen)
		{
			U1	bWrite	=	false;
			std::list<U32>::iterator i = m_lstJump.begin();
			for(;i!=m_lstJump.end();i++){
				asmGen.WriteAddress_JumpHere(*i);
				bWrite=true;
			}
			m_lstJump.clear();
			return bWrite;
		}

		Air::U32 ExpressionNode::HasJump()
		{
			U32	uiSize	=	0;
			NodeList::iterator	itr	=	m_lstChild.begin();
			for(;itr!=m_lstChild.end();itr++){
				uiSize+=((ExpressionNode*)(*itr))->HasJump();
			}
			return uiSize+m_lstJump.size();
		}


		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			SetErrorInfo(vecInfo[idx]);
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
			

			return ParseParameter(vecInfo,idx);
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
				((FunctionNode*)pNode)->RefCount++;
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
						((FunctionNode*)pNode)->RefCount++;
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

		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::GenerateCode( Assemble& asmGen )
		{
			
			U32 uiParamSize	=	pParameterArray.size();
			for(U32 i=0;i<uiParamSize;i++){
				U32 idx	=	uiParamSize-i-1;
				pParameterArray[idx]->GenerateCode(asmGen);
				asmGen.Code(eC_PUSH_EAX);
			}
			FunctionNode* p	=	(FunctionNode*)pFunction;
			{
				asmGen.Call(p->GetEntry());
			}
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::ParseParameter( WordInfoVector& vecInfo,U32& idx )
		{
			WordInfoVector 	vParameter;

			S32 uiDepth=0;
			enumSyntaxError	e	=	enSE_OK;

			idx++;
			U32	uiSize	=	vecInfo.size();
			for(;idx<uiSize;idx++){
				WordType t = vecInfo[idx].eType;
				if(t.uiType==MakeType(enWT_Delimiter,enWDT_Comma)){
					if(uiDepth==0){
						U32 uiTemp=0;
						Node* pNode=NULL;
						e	=	__ParseNode<ExpressionElementNode>(vParameter,uiTemp,&pNode);
						if(e!=enSE_OK){
							e	=	__ParseNode<FunctionCallExpressionNode>(vecInfo,idx,&pNode);
							if(e!=enSE_OK){
								return e;
							}
						}
						
						pParameterArray.push_back(pNode);
					}
					vParameter.clear();
					continue;
				}
				else if(t.uiType==MakeType(enWT_Delimiter,enWDT_PreBracket)){
					uiDepth++;
				}else if(t.uiType==MakeType(enWT_Delimiter,enWDT_PostBracket)){
					uiDepth--;
					if(uiDepth==-1){
						U32 uiTemp=0;
						Node* pNode=NULL;
						e	=	__ParseNode<ExpressionElementNode>(vParameter,uiTemp,&pNode);
						if(e!=enSE_OK){
							e	=	__ParseNode<FunctionCallExpressionNode>(vecInfo,idx,&pNode);
							if(e!=enSE_OK){
								return e;
							}
						}

						pParameterArray.push_back(pNode);
						idx++;
						return enSE_OK;
					}
				}
				vParameter.push_back(vecInfo[idx]);
			}
			return enSE_OK;
		}




		Air::CppScript::enumSyntaxError ExpressionElementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			SetErrorInfo(vecInfo[idx]);
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

			t = vecInfo[idx].eType;
			if(t.uiType	==	MakeType(enWT_Operator,enOT_Not)){
				bNot	=	true;
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[++idx].eType;
			}else if(t.uiType	==	MakeType(enWT_Operator,enOT_LogicNot)){
				bLogicNot	=	true;
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

		Air::CppScript::enumSyntaxError ExpressionElementNode::GenerateCode( Assemble& asmGen )
		{
			if(pObj->GetType()==enNT_Constant){
				ConstantNode* pConstant	=	(ConstantNode*)pObj;
				if(pConstant->ConstInfo.eType.eKeyword==enVT_String){
					//,pConstant->m_uiOffset-asmGen.GetCurrentOffset()
					asmGen.Mov_Imm(eAR_EBX,pConstant->m_uiOffset-asmGen.GetCurrentOffset()-10);
					asmGen.Call(asmGen.GetCurrentOffset()+5);
					asmGen.Pop(eAR_EAX);
					asmGen.Operator(eC_ADD_R32_RM32,eAR_EAX,eAR_EBX);
				}else{
					U32 val = pConstant->ConstInfo.iVal;
					if(bNot){
						val	=	~val;
					}else if(bLogicNot){
						val	=	!val;
					}
					asmGen.Mov_Imm(eAR_EAX,val);
				}
				return enSE_OK;
			}
			VariableNode* pVar	=	(VariableNode*)(pObj);
			
			AssembleRegister r = eAR_EBP;
			U32	uiOffset		=	pVar->m_uiOffset;
			if(pVar->GetType()==enNT_Parameter){
				
				uiOffset	=	pVar->m_uiOffset+0x14;
			}else{
				if(!pVar->IsLocal()){
					//代码实现 全局变量重定位问题
					//Code Impl Global Variable Load Relocaltion
					asmGen.Call(asmGen.GetCurrentOffset()+5);
					uiOffset	=	pVar->m_uiOffset	-	asmGen.GetCurrentOffset();
					asmGen.Pop(eAR_EAX);
					r	=	eAR_EAX;
				}else if(pVar->IsMember()){
					r	=	eAR_ESI;
				}else{
					r	=	eAR_EBP;
				}
			}
			

			
			
			
			if(m_pIndex!=NULL){
				
				asmGen.Mov_R32RM32(eAR_EDX,r,uiOffset);
	
				//asmGen.AddR32Imm(eAR_EDX,uiOffset);
				m_pIndex->GenerateCode(asmGen);
				U32 uiRegOffset	=	1;
				if(pVar->pNodePtr!=0){
					uiRegOffset	=	((ObjectNode*)pVar->pNodePtr)->GetObjectSize();
				}else{
					uiRegOffset	=	pVar->VariableType.iSize;
				}
				if(uiRegOffset>1){
					asmGen.IMulR32Imm(eAR_EAX,uiRegOffset);
				}
				asmGen.Operator(eC_ADD_R32_RM32,eAR_EDX,eAR_EAX);

				if(uiRegOffset==4){
					asmGen.Operator(eC_MOV_R32_RM32,eAR_EAX,eAR_EDX,0);
				}else{
					asmGen.Operator(eC_MOV_R8_RM8,eAR_EAX,eAR_EDX,0);
				}

				return enSE_OK;
			}else{
				asmGen.Operator(eC_MOV_R32_RM32,eAR_EAX,r,uiOffset);
			}
			
			if(eSelfOperator[1]==enOT_Increment){
				asmGen.Mov_R32R32(eAR_EBX,eAR_EAX);
				asmGen.Code(eC_INC_EBX);
				asmGen.Mov_RM32R32(r,uiOffset,eAR_EBX);
			}else if(eSelfOperator[1]==enOT_Decrement){
				asmGen.Mov_R32R32(eAR_EBX,eAR_EAX);
				asmGen.Code(eC_DEC_EBX);
				asmGen.Mov_RM32R32(r,uiOffset,eAR_EBX);
			}else if(eSelfOperator[0]==enOT_Decrement){;
				asmGen.Code(eC_INC_EAX);
				asmGen.Mov_RM32R32(r,uiOffset,eAR_EAX);
			}else if(eSelfOperator[0]==enOT_Decrement){
				asmGen.Code(eC_DEC_EAX);
				asmGen.Mov_RM32R32(r,uiOffset,eAR_EAX);
			}
			if(bNot){
				asmGen.Not(eAR_EAX);
			}else if(bLogicNot){
				asmGen.LogicNot(eAR_EAX);
			}
			return enSE_OK;
		}

		void ExpressionElementNode::GenerateWriteCode(enumCppKeyWordType op, Assemble& asmGen )
		{
			if(pObj->GetType()==enNT_Constant){
				return;
			}
			VariableNode* pVar	=	(VariableNode*)(pObj);

			AssembleRegister r = eAR_EBP;
			U32	uiOffset		=	pVar->m_uiOffset;
			if(pVar->GetType()==enNT_Parameter){

				uiOffset	=	pVar->m_uiOffset+0x14;
			}else{
				if(!pVar->IsLocal()){
					//代码实现 全局变量重定位问题
					//Code Impl Global Variable Load Relocaltion
					asmGen.Call(asmGen.GetCurrentOffset()+5);
					uiOffset	=	pVar->m_uiOffset	-	asmGen.GetCurrentOffset();
					asmGen.Pop(eAR_EBX);
					r	=	eAR_EBX;
				}else if(pVar->IsMember()){
					r	=	eAR_ESI;
				}else{
					r	=	eAR_EBP;
				}
			}

			if(m_pIndex==NULL){
				switch(op){
					case	enOT_Mov		:{
						asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EAX);
											 }break;
					case	enOT_AddEqual	:{
						asmGen.Operator(eC_ADD_RM32_R32,r,uiOffset,eAR_EAX);
											 }break;
					case	enOT_SubEqual	:{
						asmGen.Operator(eC_SUB_RM32_R32,r,uiOffset,eAR_EAX);
											 }break;
					case	enOT_AndEqual	:{
						asmGen.Operator(eC_AND_RM32_R32,r,uiOffset,eAR_EAX);
											 }break;
					case	enOT_OrEqual	:{
						asmGen.Operator(eC_OR_RM32_R32,r,uiOffset,eAR_EAX);
											 }break;
					case	enOT_MulEqual	:{
						asmGen.Operator(eC_MOV_R32_RM32,eAR_EBX,r,uiOffset);
						asmGen.IMulR32Imm(eAR_EBX,eAR_EAX);
						asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EBX);
											 }break;
					case	enOT_DivEqual	:{
						asmGen.Mov_R32R32(eAR_ECX,eAR_EAX);
						asmGen.Operator(eC_MOV_R32_RM32,eAR_EAX,r,uiOffset);
						asmGen.IDiv();
						asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EAX);
											 }break;
				}
				
			}else{
				asmGen.Mov_R32R32(eAR_EDX,eAR_EAX);
				//asmGen.AddR32Imm(eAR_EDX,uiOffset);
				m_pIndex->GenerateCode(asmGen);
				U32 uiRegOffset	=	1;
				if(pVar->pNodePtr!=0){
					uiRegOffset	=	((ObjectNode*)pVar->pNodePtr)->GetObjectSize();
				}else{
					uiRegOffset	=	pVar->VariableType.iSize;
				}
				if(uiRegOffset>1){
					asmGen.IMulR32Imm(eAR_EAX,uiRegOffset);
				}
				asmGen.Mov_R32RM32(eAR_EBX,r,uiOffset);
				asmGen.Operator(eC_ADD_R32_RM32,eAR_EBX,eAR_EAX);
				switch(op){
				case	enOT_Mov		:{
					if(uiRegOffset==4){
						asmGen.Operator(eC_MOV_RM32_R32,eAR_EBX,0,eAR_EDX);
					}else{
						asmGen.Operator(eC_MOV_RM8_R8,eAR_EBX,0,eAR_EDX);
					}
										 }break;
				case	enOT_AddEqual	:{
					if(uiRegOffset==4){
						asmGen.Operator(eC_ADD_RM32_R32,eAR_EBX,0,eAR_EDX);
					}else{
						asmGen.Operator(eC_ADD_RM8_R8,eAR_EBX,0,eAR_EDX);
					}
										 }break;
				case	enOT_SubEqual	:{
					if(uiRegOffset==4){
						asmGen.Operator(eC_SUB_RM32_R32,eAR_EBX,0,eAR_EDX);
					}else{
						asmGen.Operator(eC_SUB_RM8_R8,eAR_EBX,0,eAR_EDX);
					}
										 }break;
				case	enOT_AndEqual	:{
					if(uiRegOffset==4){
						asmGen.Operator(eC_AND_RM32_R32,eAR_EBX,0,eAR_EDX);
					}else{
						asmGen.Operator(eC_AND_RM8_R8,eAR_EBX,0,eAR_EDX);
					}
										 }break;
				case	enOT_OrEqual	:{
					if(uiRegOffset==4){
						asmGen.Operator(eC_OR_RM32_R32,eAR_EBX,0,eAR_EDX);
					}else{
						asmGen.Operator(eC_OR_RM8_R8,eAR_EBX,0,eAR_EDX);
					}
										 }break;
				case	enOT_MulEqual	:{
					//asmGen.Operator(eC_MOV_R32_RM32,eAR_EBX,r,uiOffset);
					//asmGen.IMulR32Imm(eAR_EBX,eAR_EAX);
					//asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EBX);
										 }break;
				case	enOT_DivEqual	:{
					//asmGen.Mov_R32R32(eAR_ECX,eAR_EAX);
					//asmGen.Operator(eC_MOV_R32_RM32,eAR_EAX,r,uiOffset);
					//asmGen.IDiv();
					//asmGen.Operator(eC_MOV_RM32_R32,r,uiOffset,eAR_EAX);
										 }break;
				}
				
			}


			
		}


		Air::CppScript::enumSyntaxError ExpressionOperatorNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			SetErrorInfo(vecInfo[idx]);
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


		Air::CppScript::enumSyntaxError NewExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			//Skip New
			idx++;
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			SetErrorInfo(vecInfo[idx]);
			enumSyntaxError	e	=	enSE_OK;
			e	=	ParseObjectType(vecInfo,idx,m_NewType,(Node**)&m_pNewObject);
			if(e!=enSE_OK)
				return e;

			if(idx+1>=uiSize)
				return enSE_UnexpectedEnd;
			WordType t = vecInfo[idx].eType;
			if(t.uiType==MakeType(enWT_Delimiter,enWDT_PreBracket)){
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[idx+1].eType;
				if(t.uiType==MakeType(enWT_Delimiter,enWDT_PostBracket)){
					return enSE_OK;
				}
				
			}

			return ParseParameter(vecInfo,idx);
		}

		Air::CppScript::enumSyntaxError NewExpressionNode::GenerateCode( Assemble& asmGen )
		{
			ObjectNode* pNode = (ObjectNode*)m_pNewObject;
			asmGen.Push(pNode->GetObjectSize());
			FunctionNode* pAlloc = (FunctionNode*)GetRootNode()->FindNode("__Alloc",enNT_Function,false);
			if(pAlloc!=NULL){
				asmGen.Call(pAlloc->GetEntry());
			}else{
				asmGen.Call(0x88888888);
			}
			FunctionNode* pConstruct = (FunctionNode*)pNode->FindNode(pNode->GetName(),enNT_Function,false);
			if(pConstruct!=NULL&&pConstruct->IsConstructFunction()){
				asmGen.Push(eAR_EAX);
				asmGen.Mov_R32R32(eAR_ECX,eAR_EAX);
				asmGen.Call(pConstruct->GetEntry());
				asmGen.Pop(eAR_EAX);
			}
			return enSE_OK;
		}


		Air::CppScript::enumSyntaxError ThisCallExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			SetErrorInfo(vecInfo[idx]);
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize){
				return enSE_UnexpectedEnd;
			}
			U32 uiTemp = idx;
			for(;uiTemp<uiSize;){
				WordType t	=	vecInfo[uiTemp].eType;
				if(t.uiType!=0){
					return enSE_This_Call_Object_Variable_Name_Unrecognized;
				}
				Node* pNode	=	FindNode(vecInfo[uiTemp].str);
				if(pNode==NULL)
					break;
				enumNodeType	nt	=	pNode->GetType();
				if(nt==enNT_Variable||nt==enNT_Parameter){
					m_vecObject.push_back((VariableNode*)pNode);
					if(uiTemp+1>=uiSize){
						return enSE_UnexpectedEnd;
					}
					t	=	vecInfo[++uiTemp].eType;
					if(t.uiType==MakeType(enWT_Delimiter,enWDT_Period)){
						uiTemp++;
						continue;
					}else if(t.uiType==MakeType(enWT_Operator,enOT_Sub)){
						t	=	vecInfo[++uiTemp].eType;
						if(t.uiType==MakeType(enWT_Operator,enOT_Greater)){
							uiTemp++;
							continue;
						}
					}else{
						return enSE_UnexpectedEnd;
					}
				}else{
					break;
				}
				
			}
			AString& strFunctionName	=	vecInfo[uiTemp].str;
			U32 uiObjSize		=	m_vecObject.size();
			VariableNode* pVar	=	NULL;
			if(uiObjSize>0){
				pVar	=	m_vecObject[uiObjSize-1];
				ObjectNode* pObj	=	(ObjectNode*)pVar->pNodePtr;
				if(pObj!=NULL){
					pFunction	=	pObj->FindNode(strFunctionName,enNT_Function,false);
				}
			}else{
				pFunction	=	FindNode(strFunctionName,enNT_Function);
			}
			if(pFunction==NULL){
				return enSE_UnDefine_Function_Name;
			}
			if(((FunctionNode*)pFunction)->IsStatic()){
				return enSE_This_Call_Isnt_Match_Static_Function;
					//return enSE_This_Call_Object_Variable_Name_Unrecognized;
			}
			if(((FunctionNode*)pFunction)->GetParent()->GetType()!=enNT_Object){
				return enSE_This_Call_Object_Variable_Name_Unrecognized;
			}
			
			idx=uiTemp;
			return ParseParameter(vecInfo,idx);
		}

		Air::CppScript::enumSyntaxError ThisCallExpressionNode::GenerateCode( Assemble& asmGen )
		{
			VariableNode* pObj		=	NULL;
			U32			uiOffset	=	0;
			for(U32 i=0;i<m_vecObject.size();i++){
				VariableNode* p = m_vecObject[i];
				if(i==0){
					if(p->GetType()==enNT_Variable&&p->GetParent()->GetType()!=enNT_Object){
						pObj	=	m_vecObject[i];
						continue;
					}
				}
				if(p->pNodePtr!=NULL&&p->pNodePtr->GetType()==enNT_Object){
					if(((ObjectNode*)p->pNodePtr)->GetVirtualFunctionCount()>0){
						uiOffset+=4;
					}
				}
				uiOffset	+=	p->m_uiOffset;
				
			}
			U32 uiParamSize	=	pParameterArray.size();
			for(U32 i=0;i<uiParamSize;i++){
				U32 idx	=	uiParamSize-i-1;
				pParameterArray[idx]->GenerateCode(asmGen);
				asmGen.Code(eC_PUSH_EAX);
			}

			FunctionNode* p	=	(FunctionNode*)pFunction;

			if(pObj==NULL){
				asmGen.Mov_R32R32(eAR_ECX,eAR_ESI);
			}else{
				ExpressionElementNode element;
				element.pObj	=	pObj;
				element.GenerateCode(asmGen);
				asmGen.Mov_R32R32(eAR_ECX,eAR_EAX);
			}
			if(uiOffset!=0){
				asmGen.AddR32Imm(eAR_ECX,uiOffset);
			}
			//Virtual Call
			if(p->IsVartual()){
				asmGen.Mov_R32RM32(eAR_EAX,eAR_ECX,0);
				asmGen.Mov_R32RM32(eAR_EAX,eAR_EAX,4*p->GetVirtualIndex());
				asmGen.Call(eAR_EAX);
			}else{
				asmGen.Call(p->GetEntry());
			}
			return enSE_OK;
		}

	}
}


