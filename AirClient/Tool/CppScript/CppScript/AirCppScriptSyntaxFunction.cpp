#include "AirCppScriptSyntaxFunction.h"
#include "AirCppScriptSyntaxStatement.h"
#include "AirCppScriptSyntaxObject.h"
#include "AirCppScriptSyntaxExpression.h"

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
			
			e	=	ParseObjectType(vecInfo,idx,m_ReturnType.VariableType,(Node**)&m_ReturnType.pNodePtr);
			if(e!=enSE_OK)
				return e;
			e	=	ParseVariableName(vecInfo,idx,m_strName);
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

		Air::CppScript::enumSyntaxError FunctionNode::GenerateFunctionCode(Assemble& asmGen)
		{
			if(ieType!=enCKWT_Unknown){
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
			CalcLocalVariableSize(m_uiLocalVariableSize);

			printf("Function=%s\n",m_strName.c_str());
			printf("push ebp\n");
			printf("push ebx\n");
			printf("push edx\n");
			printf("push esi\n");
			printf("mov ebp,esp\n");
			if(m_uiLocalVariableSize!=0){
				printf("sub esp,%d\n",m_uiLocalVariableSize);
				printf("mov esi,esp\n");
			}

			i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Statement){
						pNode->GenerateFunctionCode(asmGen);
					}
				}
			}
			printf("mov esp,ebp\n");
			printf("pop esi\n");
			printf("pop edx\n");
			printf("pop ebx\n");
			printf("pop ebp\n");
			
			if(iParamIndex==0){
				printf("ret\n");
			}else{
				printf("ret %d\n",iParamIndex*4);
			}
			return enSE_OK;
		}


	}
}