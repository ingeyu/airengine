#include "AirCppScriptSyntaxVariable.h"
#include "AirCppScriptSyntaxExpression.h"

namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError VariableNode::Parse( WordInfoVector& vecInfo,U32& idx )
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
				if(uiArrayCount>1){
					if(tObjType.uiType	==	MakeType(enWT_Delimiter,enWDT_PreBrace)){
						WordInfoVector vecTempInfo;
						e	=	FindBlock(vecInfo,idx,vecTempInfo,MakeType(enWT_Delimiter,enWDT_PreBrace,0,0),MakeType(enWT_Delimiter,enWDT_PostBrace,0,0));
						if(e!=enSE_OK){
							return e;
						}else{
							//not finished!add code here

						}
					}
				}
			}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
				idx++;
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

				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
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
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					return enSE_OK;
				}else{
					return enSE_Variable_Miss_Delimiter_End_Of_Statement;
				}
			}else if(VariableType.bPointor==1	&&	tObjType.eKeyword	==	enCKWT_New){
				m_pRightExpression = new NewObjectExpressionNode();
				idx++;

				e	=	m_pRightExpression->Parse(vecInfo,idx);
				if(e!=enSE_OK){
					return e;
				}
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					return enSE_OK;
				}else{
					return enSE_Variable_Miss_Delimiter_End_Of_Statement;
				}
			}else{
				WordInfoVector vExpression;
				e = FindStatementEnd(vecInfo,idx,vExpression);
				if(e!=enSE_OK){
					return e;
				}
				U32 uiTemp = 0;
				Node* pExp = new ExpressionNode();
				AddChild(pExp);
				e = pExp->ParseExpression(vExpression,uiTemp);
				if(e!=enSE_OK){
					RemoveChild(pExp);
					delete pExp;
					return e;
				}
				idx+=vExpression.size();
				tObjType	=	vecInfo[idx].eType;
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					return enSE_OK;
				}else{
					return enSE_Variable_Miss_Delimiter_End_Of_Statement;
				}
			} 


			return enSE_UnexpectedEnd;
		}
	}
}