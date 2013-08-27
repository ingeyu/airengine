#include "AirCppScriptSyntaxStatement.h"
#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptSyntaxFunction.h"
#include "AirCppScriptAssemble.h"
namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError StatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			enumSyntaxError	e	=	enSE_OK;
			WordInfoVector statement;
			e	=	FindStatementEnd(vecInfo,idx,statement);
			if(e!=enSE_OK){
				return e;
			}
			U32 uiTempSize	=	statement.size();
			U32 uiTemp	=	0;
			if(__ParseNode<ExpressionNode>(statement,uiTemp)==enSE_OK){
				idx+=uiTempSize;
				return enSE_OK;
			}
			//for(;uiTemp<uiTempSize;){
			//	WordType t	=	statement[uiTemp].eType;
			//	if(t.eWordtype	==	enWT_Unknown){
			//		Node* pNode	=	__CheckNextNodeType(statement,uiTemp,enNT_Variable);
			//		if(pNode==NULL){
			//			pNode	=	__CheckNextNodeType(statement,uiTemp,enNT_Parameter);
			//		}
			//		if(pNode==NULL){
			//			pNode	=	__CheckNextNodeType(statement,uiTemp,enNT_Function);
			//			if(pNode==NULL){
			//				return enSE_UnexpectedEnd;
			//			}
			//			uiTemp--;
			//			e	=	__ParseNode<FunctionCallExpressionNode>(statement,uiTemp);
			//			if(e!=enSE_OK){
			//				return	e;
			//			}

			//		}else{
			//			uiTemp--;
			//			e	=	__ParseNode<ExpressionNode>(statement,uiTemp);
			//			if(e!=enSE_OK){
			//				return	e;
			//			}
			//		}
			//	}else if(t.uiType	==	MakeType(enWT_Delimiter,enWDT_PreBracket)){
			//		uiTemp++;
			//		e	=	ParseSubStatement(statement,uiTemp);
			//		if(e!=enSE_OK){
			//			return e;
			//		}

			//	}else	if(t.uiType	==	MakeType(enWT_Operator,enOT_Mul)){
			//		Node* pNode	=	__CheckNextNodeType(statement,uiTemp,enNT_Variable);
			//		if(pNode==NULL)
			//			return enSE_UnexpectedEnd;

			//	}else	if(t.uiType	==	MakeType(enWT_Operator,enOT_Add)){
			//		if(__CheckNextWordType(statement,uiTemp,MakeType(enWT_Operator,enOT_Add))){
			//			return enSE_UnexpectedEnd;
			//		}
			//		Node* pNode	=	__CheckNextNodeType(statement,uiTemp,enNT_Variable);
			//		if(pNode==NULL)
			//			return enSE_UnexpectedEnd;
			//	}else	if(t.uiType	==	MakeType(enWT_Operator,enOT_Sub)){
			//		if(__CheckNextWordType(statement,uiTemp,MakeType(enWT_Operator,enOT_Sub))){
			//			return enSE_UnexpectedEnd;
			//		}
			//		Node* pNode	=	__CheckNextNodeType(statement,uiTemp,enNT_Variable);
			//		if(pNode==NULL)
			//			return enSE_UnexpectedEnd;
			//	}
			//}

			return enSE_UnexpectedEnd;
		}

		Air::CppScript::enumSyntaxError StatementNode::ParseSubStatement( WordInfoVector& vecInfo,U32& idx )
		{
			return enSE_UnexpectedEnd;
		}

		Air::CppScript::enumSyntaxError StatementNode::GenerateFunctionCode( Assemble& asmGen )
		{
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Expression){
						pNode->GenerateFunctionCode(asmGen);
					}
				}
			}
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError NewStatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError DeleteStatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError ReturnStatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			idx++;
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize){
				return enSE_Return_Miss_Value;
			}
			WordType t = vecInfo[idx].eType;

			Node* pFinction	=	GetParent();
			while(pFinction->GetType()==enNT_Function){
				if(pFinction==NULL){
					break;
				}
				pFinction=pFinction->GetParent();
			}
			if(pFinction==NULL){
				return enSE_Return_Must_In_A_Function_Block;
			}
			FunctionNode* pFN	=	(FunctionNode*)pFinction;
			if(pFN->m_ReturnType.VariableType.t	==	enBOT_Void){
				if(t.eKeyword	==	enWDT_Semicolon){
					return enSE_OK;
				}else{
					return enSE_Function_Return_Type_Not_Match;
				}
			}else{
				WordInfoVector vTemp;
				enumSyntaxError	e	=	FindStatementEnd(vecInfo,idx,vTemp);
				if(e!=enSE_OK){
					return e;
				}
				U32 uiTemp=0;
				e	=	__ParseNode<ExpressionNode>(vTemp,uiTemp,&pReturn);
				if(e!=enSE_OK){
					return e;
				}
				idx+=uiTemp;
				return enSE_OK;
			}
			return enSE_UnexpectedEnd;
		}

		Air::CppScript::enumSyntaxError ReturnStatementNode::GenerateFunctionCode( Assemble& asmGen )
		{
			__super::GenerateFunctionCode(asmGen);
			m_uiJump	=	asmGen.GetCurrentOffset()+5;
			asmGen.Jmp(m_uiJump);
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError ForStatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			enumSyntaxError	e	=	enSE_OK;
			WordInfoVector statement;
			e	=	FindBlock(vecInfo,idx,statement,MakeType(enWT_Delimiter,enWDT_PreBracket),MakeType(enWT_Delimiter,enWDT_PostBracket));
			if(e!=enSE_OK){
				return e;
			}
			if(statement.empty()){
				return enSE_For_Statement_Must_Fallow_A_Pre_Bracket;
			}
			U32 uiTempSize	=	statement.size();
			U32 uiTemp	=	0;
			WordType t = statement[uiTemp].eType;
			if(t.uiType!=MakeType(enWT_Delimiter,enWDT_PreBracket)){
				return enSE_For_Statement_Must_Fallow_A_Pre_Bracket;
			}
			
			e	=	ParseCondition(statement,uiTemp);
			if(e==enSE_OK){
				idx+=uiTempSize;
			}else{
				return e;
			}
			
			if(idx+1>=uiSize){
				return enSE_UnexpectedEnd;
			}
			idx++;
			if(vecInfo[idx].eType.uiType==MakeType(enWT_Delimiter,enWDT_PreBrace)){
				statement.clear();
				e	=	FindBlock(vecInfo,idx,statement,MakeType(enWT_Delimiter,enWDT_PreBrace),MakeType(enWT_Delimiter,enWDT_PostBrace));
				if(e!=enSE_OK){
					return e;
				}
				uiTempSize	=	statement.size();
				uiTemp		=	0;
				e			=	ParseCode(statement,uiTemp);
				if(e==enSE_OK){
					idx+=uiTempSize;
				}
				return e;
			}else{
				return	enSE_UnexpectedEnd; 
			}

			return enSE_UnexpectedEnd;
		}

		Air::CppScript::enumSyntaxError ForStatementNode::ParseCondition( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			U32 uiSemicolon	=	0;
			for(U32 i=0;i<uiSize;i++){
				if(vecInfo[i].eType.uiType==MakeType(enWT_Delimiter,enWDT_Semicolon)){
					uiSemicolon++;
				}
			}
			if(uiSemicolon!=2){
				return enSE_For_Statement_Condition_Must_Have_2_Semicolon;
			}
			idx++;
			uiSemicolon=0;
			WordInfoVector v[3];
			U32 uiSemicolonIndx=0;
			for(U32 i=0;i<uiSize;i++){
				if(vecInfo[i].eType.uiType==MakeType(enWT_Delimiter,enWDT_Semicolon)){
					uiSemicolon++;
					if(uiSemicolon==1){
						for(U32 j=idx;j<=i;j++){
							v[0].push_back(vecInfo[j]);
						}
						uiSemicolonIndx=i;
					}else if(uiSemicolon==2){
						for(U32 j=uiSemicolonIndx+1;j<=i;j++){
							v[1].push_back(vecInfo[j]);
						}
						for(U32 j=i+1;j<uiSize-1;j++){
							v[2].push_back(vecInfo[j]);
						}
						WordInfo vSemi;
						vSemi.eType.uiType	=	MakeType(enWT_Delimiter,enWDT_Semicolon);
						vSemi.str			=	";";
						v[2].push_back(vSemi);
						break;
					}
				}
			}
			WordInfoVector& vInit		=	v[0];
			WordInfoVector& vCondition	=	v[1];
			WordInfoVector& vIter		=	v[2];
			enumSyntaxError e	=	enSE_OK;
			if(vInit.size()>1){
				e	=	ParseSubCondition_Init(vInit);
				if(e!=enSE_OK)
					return	e;
			}
			if(vCondition.size()>1){
				e	=	ParseSubCondition_Condition(vCondition);
				if(e!=enSE_OK)
					return	e;
			}
			if(vIter.size()>1){
				e	=	ParseSubCondition_Iter(vIter);
				if(e!=enSE_OK)
					return	e;
			}

			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError ForStatementNode::ParseCode( WordInfoVector& vecInfo,U32& idx )
		{
			return ParseFunctionCode(vecInfo,idx);
		}

		Air::CppScript::enumSyntaxError ForStatementNode::ParseSubCondition_Init( WordInfoVector& vecInfo )
		{
			U32 i=0;
			enumSyntaxError e	=	__ParseNode<VariableNode>(vecInfo,i);
			e					=	__ParseNode<StatementNode>(vecInfo,i,&pInitExp);
			
			return e;
		}

		Air::CppScript::enumSyntaxError ForStatementNode::ParseSubCondition_Condition( WordInfoVector& vecInfo )
		{
			U32 i=0;
			enumSyntaxError	e	=	__ParseNode<StatementNode>(vecInfo,i,&pConditionExp);

			return e;
		}

		Air::CppScript::enumSyntaxError ForStatementNode::ParseSubCondition_Iter( WordInfoVector& vecInfo )
		{
			U32 i=0;
			enumSyntaxError	e	=	__ParseNode<StatementNode>(vecInfo,i,&pIterExp);

			return e;
		}

		Air::CppScript::enumSyntaxError ForStatementNode::GenerateFunctionCode( Assemble& asmGen )
		{
			pInitExp->GenerateFunctionCode(asmGen);
			
			U32 pCondition	=	asmGen.GetCurrentOffset();
			
			pConditionExp->GenerateFunctionCode(asmGen);
			asmGen.Test(eAR_EAX);
			asmGen.JumpCondition(
					InserveJumpCondition(
						(Code1Ex)((ExpressionNode*)pConditionExp)->GetJumpCondition()
					)
				);
			U32 uiJump	=	asmGen.GetCurrentOffset();
			
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL&&pNode!=pInitExp&&pNode!=pConditionExp&&pNode!=pIterExp){
					if(pNode->GetType()==enNT_Statement){
						pNode->GenerateFunctionCode(asmGen);
					}
				}
			}
			
			pIterExp->GenerateFunctionCode(asmGen);
			asmGen.Jmp(pCondition);
			asmGen.WriteAddress_JumpHere(uiJump);
			
			return enSE_OK;
		}


		Air::CppScript::enumSyntaxError IfStatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			idx++;
			U32 uiSize	=	vecInfo.size();
			enumSyntaxError	e	=	enSE_OK;
			WordInfoVector statement;
			e	=	FindBlock(vecInfo,idx,statement,MakeType(enWT_Delimiter,enWDT_PreBracket),MakeType(enWT_Delimiter,enWDT_PostBracket),false);
			if(e!=enSE_OK){
				return e;
			}
			if(statement.empty()){
				return enSE_For_Statement_Must_Fallow_A_Pre_Bracket;
			}
			
			U32 uiTemp=0;
			e	=	__ParseNode<ExpressionNode>(statement,uiTemp,&pConditionExp);
			if(e!=enSE_OK){
				return e;
			}else{
				idx+=statement.size()+2;
			}
			e = ParseFunctionCode(vecInfo,idx);
			if(e != enSE_OK){
				return e;
			}
			
			for(;idx<uiSize;){
				WordType	t = vecInfo[idx].eType;
				if(t.uiType	==	MakeType(enWT_CppKeyWord,enCKWT_Else)){
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd;
					}
					t = vecInfo[idx+1].eType;
					if(t.uiType	==	MakeType(enWT_CppKeyWord,enCKWT_If)){
						idx++;
						e	=	__ParseNode<ElseIfStatementNode>(vecInfo,idx);
						if(e!=enSE_OK){
							return e;
						}
					}else if(t.uiType	==	MakeType(enWT_Delimiter,enWDT_PreBrace)){
						
						e	=	__ParseNode<ElseStatementNode>(vecInfo,idx);
						if(e!=enSE_OK){
							return e;
						}
					}else{
						return enSE_UnexpectedEnd;
					}
				}else{
					return e;
				}
			}
			return e;
		}

		Air::CppScript::enumSyntaxError IfStatementNode::GenerateFunctionCode( Assemble& asmGen )
		{
			//m_uiEntry	=	asmGen.GetCurrentOffset();
			pConditionExp->GenerateFunctionCode(asmGen);

			//Condition JUMP To End
			U32 uiConditionJMP	=	0;
			if(((ExpressionNode*)pConditionExp)->HasJump()==0){
				asmGen.Test(eAR_EAX);
				asmGen.JumpCondition(InserveJumpCondition((Code1Ex)((ExpressionNode*)pConditionExp)->GetJumpCondition()));
				uiConditionJMP	=	asmGen.GetCurrentOffset();
			}
			NodeList	lstElse;

			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL&&pNode!=pConditionExp){
					if(pNode->GetType()==enNT_Statement){
						StatementNode* pState	=	(StatementNode*)pNode;
						if(pState->m_sType==enST_ElseIf	||	pState->m_sType==enST_Else){
							lstElse.push_back(pState);
							continue;
						}
						pNode->GenerateFunctionCode(asmGen);
					}
				}
			}
			asmGen.Jmp(0);
			m_uiJump	=	asmGen.GetCurrentOffset();
			
			if(((ExpressionNode*)pConditionExp)->HasJump()==0){
				asmGen.WriteAddress_JumpHere(uiConditionJMP);
			}else{
				((ExpressionNode*)pConditionExp)->WriteJumpAddress(asmGen);
			}
			//GenCode
			i	=	lstElse.begin();
			for(;i!=lstElse.end();i++){
				(*i)->GenerateFunctionCode(asmGen);
			}
			//Write JUMP
			i	=	lstElse.begin();
			for(;i!=lstElse.end();i++){
				ElseStatementNode* pElse	=	(ElseStatementNode*)(*i);
				
				if(pElse->m_sType==enST_ElseIf){
					asmGen.WriteAddress_JumpHere(pElse->m_uiJump);//->GenerateFunctionCode(asmGen);
				}
			}
			
			asmGen.WriteAddress_JumpHere(m_uiJump);
			
			return enSE_OK;
		}


		Air::CppScript::enumSyntaxError ElseStatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			idx++;
			return ParseFunctionCode(vecInfo,idx);
		}

		Air::CppScript::enumSyntaxError ElseStatementNode::GenerateFunctionCode( Assemble& asmGen )
		{
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Statement){
						pNode->GenerateFunctionCode(asmGen);
					}
				}
			}
			return enSE_OK;
		}



		Air::CppScript::enumSyntaxError ElseIfStatementNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			idx++;
			U32 uiSize	=	vecInfo.size();
			enumSyntaxError	e	=	enSE_OK;
			WordInfoVector statement;
			e	=	FindBlock(vecInfo,idx,statement,MakeType(enWT_Delimiter,enWDT_PreBracket),MakeType(enWT_Delimiter,enWDT_PostBracket),false);
			if(e!=enSE_OK){
				return e;
			}
			if(statement.empty()){
				return enSE_For_Statement_Must_Fallow_A_Pre_Bracket;
			}

			U32 uiTemp=0;
			e	=	__ParseNode<ExpressionNode>(statement,uiTemp,&pConditionExp);
			if(e!=enSE_OK){
				return e;
			}else{
				idx+=statement.size()+2;
			}
			return ParseFunctionCode(vecInfo,idx);
		}

		Air::CppScript::enumSyntaxError ElseIfStatementNode::GenerateFunctionCode( Assemble& asmGen )
		{
			//m_uiEntry	=	asmGen.GetCurrentOffset();
			pConditionExp->GenerateFunctionCode(asmGen);
			//Condition JUMP To End
			asmGen.Test(eAR_EAX);
			asmGen.JumpCondition((Code1Ex)((ExpressionNode*)pConditionExp)->GetJumpCondition());
			U32 uiConditionJMP	=	asmGen.GetCurrentOffset();

			NodeList	lstElse;

			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL&&pNode!=pConditionExp){
					if(pNode->GetType()==enNT_Statement){
						StatementNode* pState	=	(StatementNode*)pNode;
						if(pState->m_sType==enST_ElseIf	||	pState->m_sType==enST_Else){
							lstElse.push_back(pState);
							continue;
						}
						pNode->GenerateFunctionCode(asmGen);
					}
				}
			}
			asmGen.Jmp(0);
			m_uiJump	=	asmGen.GetCurrentOffset();
			asmGen.WriteAddress_JumpHere(uiConditionJMP);
			return enSE_OK;
		}

	}
}