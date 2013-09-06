#include "AirCppScriptSyntaxFunction.h"
#include "AirCppScriptSyntaxStatement.h"
#include "AirCppScriptSyntaxObject.h"
#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptAssemble.h"

namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError ParameterNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			enumSyntaxError	e	=	enSE_OK;
			e	=	ParseObjectType(vecInfo,idx,VariableType,&pNodePtr);
			if(e!=enSE_OK)
				return e;
			e	=	ParseVariableName(vecInfo,idx,m_strName);
			if(e!=enSE_OK)
				return e;
			U32 uiSize	=	vecInfo.size();
			WordType tObjType	=	vecInfo[idx].eType;

			if(tObjType.eWordtype	==	enWT_Operator	&&	tObjType.eKeyword	==	enOT_SquareBracketBegin){
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				tObjType	=	vecInfo[++idx].eType;
				if(tObjType.eWordtype	==	enWT_Constant	&&	tObjType.eKeyword	==	enVT_IntNumber){
					uiArrayCount	=	vecInfo[idx].iVal;
					if(uiArrayCount==0){
						return enSE_Variable_Array_Count_Must_Greater_Than_Zero;
					}
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
					if(tObjType.eWordtype	==	enWT_Operator	&&	tObjType.eKeyword	==	enOT_SquareBracketEnd){
						if(idx+1>=uiSize){
							return enSE_UnexpectedEnd; 
						}
						tObjType	=	vecInfo[++idx].eType;
					}else{
						return enSE_Miss_End_Of_SquareBracket;
					}
				}else{
					return enSE_Variable_Array_Count_Must_Be_Int_Number;
				}
			}

			if(tObjType.eWordtype	==	enWT_Operator	&&	tObjType.eKeyword	==	enOT_Mov){
				m_bHasInitValue	=	1;
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				tObjType	=	vecInfo[++idx].eType;

			}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Comma ){
				idx++;
				return enSE_OK;
			}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBracket ){
				return enSE_OK;
			}else{
				return	enSE_Variable_Miss_Delimiter_End_Of_Statement;
			}

			if(tObjType.eWordtype == enWT_CppKeyWord && tObjType.eKeyword	==	enOT_Sub){
				if(VariableType.bUnsign==1){
					return enSE_Unsigned_Object_Cant_Be_A_Negative_Value;
				}
				if(VariableType.t	==	enBOT_Bool){
					return enSE_Bool_Object_Cant_Be_A_Negative_Value;
				}
				m_bSub	=	1;
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				tObjType	=	vecInfo[++idx].eType;
			}else if(tObjType.eWordtype == enWT_CppKeyWord && tObjType.eKeyword	==	enOT_Add){
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				tObjType	=	vecInfo[++idx].eType;
			}

			if(tObjType.eWordtype	==	enWT_Constant){
				if(	VariableType.t	==	enBOT_S8	&&	
					VariableType.bPointor	==	1	&&
					VariableType.bUnsign	==	0	&&
					VariableType.bpp		==	0	&&
					tObjType.eKeyword		==	enVT_String)
				{
					m_InitInfo	=	vecInfo[idx];
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;

				}else if(	VariableType.t	==	enBOT_S8	||
					VariableType.t	==	enBOT_S16	||
					VariableType.t	==	enBOT_S32	||
					VariableType.t	==	enBOT_S64	||
					VariableType.bPointor	==	1)
				{
					if(tObjType.eKeyword	!=	enVT_IntNumber){
						return enSE_Int_Variable_Need_A_Int_Init_Value;
					}else{
						m_InitInfo	=	vecInfo[idx];
						if(idx+1>=uiSize){
							return enSE_UnexpectedEnd; 
						}
						tObjType	=	vecInfo[++idx].eType;
					}
				}
				else	if(VariableType.t	==	enBOT_F32	||	VariableType.t	==	enBOT_F64)
				{
					if(tObjType.eKeyword	!=	enVT_FloatNumber){
						return enSE_Float_Variable_Need_A_Float_Init_Value;
					}else{
						m_InitInfo	=	vecInfo[idx];
						if(idx+1>=uiSize){
							return enSE_UnexpectedEnd; 
						}
						tObjType	=	vecInfo[++idx].eType;
					}
				}

				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Comma ){
					idx++;
					return enSE_OK;
				}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBracket ){
					return enSE_OK;
				}else{
					return enSE_Variable_Miss_Delimiter_End_Of_Statement;
				}
			}else if(VariableType.bPointor==1	&&	tObjType.eKeyword	==	enCKWT_Null){
				m_InitInfo	=	vecInfo[idx];
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				tObjType	=	vecInfo[++idx].eType;
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Comma ){
					idx++;
					return enSE_OK;
				}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBracket ){
					return enSE_OK;
				}else{
					return enSE_Variable_Miss_Delimiter_End_Of_Statement;
				}
			}else{
				return enSE_Unrecognized_Variable_Init_Value;
			}

			return enSE_UnexpectedEnd;
		}
		Air::CppScript::enumSyntaxError FunctionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			enumSyntaxError e = enSE_OK;
			SetErrorInfo(vecInfo[idx]);
			e	=	ParseImportExport(vecInfo,idx);
			if(e!=enSE_OK)
				return e;
			U32 uiSize	 = vecInfo.size();
			WordType tObjType	=	vecInfo[idx].eType;

			if(tObjType.eWordtype	==	enWT_CppKeyWord	&&	tObjType.eKeyword	==	enCKWT_Virtual){
				m_bVirtual	=	1;
				if(idx+1 > uiSize){
					return enSE_UnexpectedEnd;
				}
				idx++;
			}

			
			e = ParseReturnType_Name(vecInfo,idx);
			if(e!=enSE_OK)
				return e;
			

			if(idx+2 > uiSize){
				return enSE_UnexpectedEnd;
			}

			tObjType	=	vecInfo[idx].eType;
			if(tObjType.eWordtype == enWT_Delimiter &&	tObjType.eKeyword	==	enWDT_PreBracket){
				if(idx+1 > uiSize){
					return enSE_UnexpectedEnd;
				}
				tObjType	=	vecInfo[++idx].eType;
			}else{
				return enSE_Function_Declare_Must_Fallow_Parameter;
			}


			if(tObjType.eWordtype == enWT_Delimiter &&	tObjType.eKeyword	==	enWDT_PostBracket){
				if(idx+1 > uiSize){
					return enSE_UnexpectedEnd;
				}
				tObjType	=	vecInfo[++idx].eType;
				if(tObjType.eWordtype == enWT_Delimiter &&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					m_bOnlyDeclare	=	1;
					return enSE_OK;
				}
			}else if(tObjType.eWordtype == enWT_CppKeyWord &&	tObjType.eKeyword	==	enCKWT_Void){
				if(tObjType.eWordtype == enWT_Delimiter &&	tObjType.eKeyword	==	enWDT_PostBracket){
					if(idx+1 > uiSize){
						return enSE_UnexpectedEnd;
					}
					tObjType	=	vecInfo[++idx].eType;
					if(tObjType.eWordtype == enWT_Delimiter &&	tObjType.eKeyword	==	enWDT_Semicolon){
						idx++;
						m_bOnlyDeclare	=	1;
						return enSE_OK;
					}
				}else{
					e = ParseParameter(vecInfo,idx);
					if(e!=enSE_OK){
						return e;
					}
					tObjType	=	vecInfo[idx].eType;
					if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
						idx++;
						m_bOnlyDeclare	=	1;
						return enSE_OK;
					}
				}
			}else{
				e = ParseParameter(vecInfo,idx);
				if(e!=enSE_OK){
					return e;
				}
				tObjType	=	vecInfo[idx].eType;
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					m_bOnlyDeclare	=	1;
					return enSE_OK;
				}

			}
			//e	=	ParseFunctionCode(vecInfo,idx);
			//if(e!=enSE_OK){
			//	return e;
			//}
			//if(idx<uiSize){
			//	tObjType	=	vecInfo[idx].eType;
			//	if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBrace){
			//		idx++;
			//		return enSE_OK;
			//	}
			//}else{
			//	return enSE_OK;
			//}

			return ParseFunctionCode(vecInfo,idx);;
		}

		Air::CppScript::enumSyntaxError FunctionNode::ParseParameter( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	 = vecInfo.size();

			for(;;){
				WordType tObjType	=	vecInfo[idx].eType;
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBracket){
					idx++;
					return enSE_OK;
				}

				ParameterNode* p	=	new ParameterNode();
				enumSyntaxError e = enSE_OK;
				e =	p->Parse(vecInfo,idx);
				if(e!=enSE_OK){
					return e;
				}
				AddChild(p);
				m_vecParameter.push_back(p);
			}

			return enSE_UnexpectedEnd;
		}

		

		Air::U1 FunctionNode::IsParamNameExist( CAString& strName )
		{
			if(strName.empty())
				return false;
			U32 uiSize	=	m_vecParameter.size();
			for(U32 i=0;i<uiSize;i++){
				if(m_vecParameter[i]->GetName()	==	strName){
					return true;
				}
			}
			return false;
		}

		ParameterNode* FunctionNode::FindParameter( CAString& strName )
		{
			U32 uiSize	=	m_vecParameter.size();
			for(U32 i=0;i<uiSize;i++){
				if(m_vecParameter[i]->GetName()	==	strName)
					return	m_vecParameter[i];
			}
			return NULL;
		}

		Air::CppScript::enumSyntaxError FunctionNode::ParseImportExport( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			WordType t = vecInfo[idx].eType;
			if(t.uiType!=MakeType(enWT_CppKeyWord,enCKWT___declspec)){
				return enSE_OK;
			}
			if(idx+1>=uiSize)
				return enSE_UnexpectedEnd;
			t = vecInfo[++idx].eType;
			if(t.uiType!=MakeType(enWT_Delimiter,enWDT_PreBracket)){
				return enSE_UnexpectedEnd;
			}

			if(idx+1>=uiSize)
				return enSE_UnexpectedEnd;
			t = vecInfo[++idx].eType;
			if(t.uiType==MakeType(enWT_CppKeyWord,enCKWT_dllimport)){
				ieType	=	enCKWT_dllimport;
			}else if(t.uiType==MakeType(enWT_CppKeyWord,enCKWT_dllexport)){
				ieType	=	enCKWT_dllexport;
			}else{
				return enSE_UnexpectedEnd;
			}

			if(idx+1>=uiSize)
				return enSE_UnexpectedEnd;
			t = vecInfo[++idx].eType;
			if(t.uiType!=MakeType(enWT_Delimiter,enWDT_PostBracket)){
				return enSE_UnexpectedEnd;
			}

			if(idx+1>=uiSize)
				return enSE_UnexpectedEnd;
			t = vecInfo[++idx].eType;
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError FunctionNode::GenerateCode(Assemble& asmGen)
		{
			if(ieType==enCKWT_dllimport){
				return enSE_OK;
			}
			U32 iParamIndex=0;
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Parameter){
						ParameterNode* pParam = (ParameterNode*)pNode;
						pParam->m_uiOffset	=	iParamIndex*4;
						iParamIndex++;
					}
				}
			}
			m_uiLocalVariableSize=0;
			CalcLocalVariableSize(m_uiLocalVariableSize,true);

			//Call Parent Construct Function
			pEntry	=	0xffffffff;
			if(IsConstructFunction()){
				ObjectNode* pObj		= (ObjectNode*)GetParent();
				ObjectNode* pInherit	= pObj->GetInherit();
				if(pInherit!=NULL){
					FunctionNode* pFunc = (FunctionNode*)pInherit->FindNode(pInherit->GetName(),enNT_Function,false);
					if(pFunc!=NULL&&pFunc->IsConstructFunction()){
						pEntry	=	asmGen.Call(pFunc->GetEntry());
					
					}
				}
			}
			if(pEntry==0xffffffff)
				pEntry	=	asmGen.GetCurrentOffset();

			asmGen.Code(eC_PUSH_EBP);
			asmGen.Code(eC_PUSH_EBX);
			asmGen.Code(eC_PUSH_EDX);
			//Only Member Function Need Save ESI
			//if(IsMemberFunction()&&!IsStatic())
			{
				asmGen.Code(eC_PUSH_ESI);
			}
			asmGen.Mov_R32R32(eAR_EBP,eAR_ESP);
			if(m_uiLocalVariableSize!=0){
				asmGen.SubR32Imm(eAR_ESP,m_uiLocalVariableSize);
			}
			if(IsMemberFunction()&&!IsStatic())
			{
				asmGen.Mov_R32R32(eAR_ESI,eAR_ECX);
			}
			

			i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Statement){
						pNode->GenerateCode(asmGen);
					}else if(pNode->GetType()==enNT_Variable){
						if(((VariableNode*)pNode)->IsObject()){
							ThisCallExpressionNode construct;
							construct.m_vecObject.push_back((VariableNode*)pNode);
							ObjectNode* pObj	=	(ObjectNode*)((VariableNode*)pNode)->pNodePtr;
							construct.pFunction	=	pObj->GetConstructFunction();
							construct.GenerateCode(asmGen);
						}
					}
				}
			}
			std::list<Node*> lstNode;
			FindNodeDown(lstNode,enNT_Statement);
			for(i=lstNode.begin();i!=lstNode.end();i++){
				StatementNode* pNode = (StatementNode*)(*i);
				if(pNode!=NULL){
					if(pNode->m_sType	==	enST_Return){
						asmGen.WriteAddress_JumpHere(((ReturnStatementNode*)pNode)->m_uiJump);
					}
				}
			}

			//Save Return Value
			if(	!IsConstructFunction()		&&
				!IsDisConstructFunction()	&&
				m_ReturnType.VariableType.t!=enBOT_Void)
			{
				asmGen.Push(eAR_EAX);
			}
			//Build Local Variable DisConstruct
			NodeList::reverse_iterator	itr	=	m_lstChild.rbegin();
			for(;itr!=m_lstChild.rend();itr++){
				Node* pNode	=	(*itr);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Variable){
						if(((VariableNode*)pNode)->IsObject()){
							ThisCallExpressionNode construct;
							construct.m_vecObject.push_back((VariableNode*)pNode);
							ObjectNode* pObj	=	(ObjectNode*)((VariableNode*)pNode)->pNodePtr;
							construct.pFunction	=	pObj->GetDisConstructFunction();
							construct.GenerateCode(asmGen);
						}
					}
				}
			}

			//Construct Virtual Function Table
			if(IsConstructFunction()){
				ObjectNode* pObj		= (ObjectNode*)GetParent();
				if(pObj->GetVirtualFunctionCount()>0){
					asmGen.MovEaxGlobalVarAddr(pObj->GetVFTOffset());
					asmGen.Mov_RM32R32(eAR_ESI,0,eAR_EAX);
				}
			}else if(IsDisConstructFunction()){
				ObjectNode* pObj		= (ObjectNode*)GetParent();
				if(pObj->GetInherit()!=NULL){
					ObjectNode* pInherit	=	pObj->GetInherit();
					FunctionNode* pDisConstruct =	pInherit->GetDisConstructFunction();
					if(pDisConstruct!=NULL){
						asmGen.Mov_R32R32(eAR_ECX,eAR_ESI);
						if(pDisConstruct->IsVirtual()){
							asmGen.Mov_R32RM32(eAR_EAX,eAR_EAX,0);
							asmGen.Mov_R32RM32(eAR_EAX,eAR_EAX,pDisConstruct->GetVirtualIndex()*4);
							asmGen.Call(eAR_EAX);
						}else{
							asmGen.Call(pDisConstruct->GetEntry());
						}
					}
				}
			}
			if(	!IsConstructFunction()		&&
				!IsDisConstructFunction()	&&
				m_ReturnType.VariableType.t!=enBOT_Void)
			{
				asmGen.Pop(eAR_EAX);
			}
			asmGen.Mov_R32R32(eAR_ESP,eAR_EBP);
			//if(IsMemberFunction()&&!IsStatic())
			{
				asmGen.Code(eC_POP_ESI);
			}
			asmGen.Code(eC_POP_EDX);
			asmGen.Code(eC_POP_EBX);
			asmGen.Code(eC_POP_EBP);
			
			
			asmGen.Ret((U16)iParamIndex*4);
			
			asmGen.Code(eC_NOP);
			asmGen.Code(eC_NOP);
			asmGen.Code(eC_NOP);
			asmGen.Code(eC_NOP);
			return enSE_OK;
		}

		Air::U1 FunctionNode::IsMemberFunction()
		{
			if(GetParent()->GetType()==enNT_Object){
				return true;
			}
			return false;
		}

		Air::U32 FunctionNode::GetVirtualIndex()
		{
			if(!IsVirtual())
				return 0xffffffff;
			return m_uiVirtualIndex;
		}

		Air::CppScript::enumSyntaxError FunctionNode::ParseReturnType_Name( WordInfoVector& vecInfo,U32& idx )
		{
			if(m_pParent!=NULL&&m_pParent->GetType()==enNT_Object){
				FunctionType	=	enFT_MemberFunction;

				AString& str = vecInfo[idx].str;
				if(str == m_pParent->GetName()){
					FunctionType	=	enFT_Construct;
					m_strName	=	str;
					idx++;
					return enSE_OK;
				}else if(str == AString("~")+m_pParent->GetName()){
					FunctionType	=	enFT_DisConstruct;
					idx++;
					m_strName	=	str;
					return enSE_OK;
				}
				
			}
			enumSyntaxError	e;

			e	=	ParseObjectType(vecInfo,idx,m_ReturnType.VariableType,(Node**)&m_ReturnType.pNodePtr);
			if(e!=enSE_OK)
				return e;

			e	=	ParseCallType(vecInfo,idx);
			if(e!=enSE_OK)
				return e;

			e	=	ParseVariableName(vecInfo,idx,m_strName,false);
			if(e!=enSE_OK)
				return e;
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError FunctionNode::ParseCallType( WordInfoVector& vecInfo,U32& idx )
		{
			WordType tObjType	=	vecInfo[idx].eType;
			if(tObjType.eWordtype == enWT_CppKeyWord){
				switch(tObjType.eKeyword){
				case enCKWT___cdecl:
				case enCKWT___fastcall:
				case enCKWT___stdcall:
				case enCKWT___thiscall:{
					callType	=	tObjType.eKeyword;
					if(idx+1 > vecInfo.size()){
						return enSE_UnexpectedEnd;
					}
					idx++;
									   }break;
				}
			}
			return enSE_OK;
		}

		Air::U1 FunctionNode::IsConstructFunction()
		{
			if(!IsMemberFunction())
				return false;
			if(IsStatic())
				return	false;
			return FunctionType	==	enFT_Construct;
		}

		Air::U1 FunctionNode::IsDisConstructFunction()
		{
			if(!IsMemberFunction())
				return false;
			if(IsStatic())
				return	false;
			return FunctionType	==	enFT_DisConstruct;
		}


	}
}