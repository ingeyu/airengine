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
				e	=	ParseFunction(vecInfo,idx);
				if(e!=enSE_OK){
					return e;
				}
				tObjType	=	vecInfo[idx].eType;
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBrace){
					idx++;
					return enSE_OK;
				}
			}

			return enSE_UnexpectedEnd;
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

		Air::CppScript::enumSyntaxError FunctionNode::ParseFunction( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	 = vecInfo.size();
			enumSyntaxError	e = enSE_OK;
			for(;;){
				if(idx	>=	uiSize){
					return enSE_UnexpectedEnd;
				}
				WordType tObjType	=	vecInfo[idx].eType;
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PreBrace){
					idx++;
					continue;
				}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBrace){
					idx++;
					return enSE_OK;
				}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					continue;
				}
				tObjType	=	vecInfo[idx].eType;

				if(tObjType.eWordtype==enWT_CppKeyWord){
					switch(tObjType.eKeyword){
					case enCKWT_If:{
						e = __ParseNode<IfStatementNode>(vecInfo,idx);
								   }break;
					case enCKWT_For:{
						e = __ParseNode<ForStatementNode>(vecInfo,idx);
									}break;
					case enCKWT_While:{
						e = __ParseNode<WhileStatementNode>(vecInfo,idx);
									  }break;
					case enCKWT_Switch:{
						e = __ParseNode<SwitchStatementNode>(vecInfo,idx);
									   }break;
					case enCKWT_New:{
						e = __ParseNode<NewStatementNode>(vecInfo,idx);
									   }break;
					case enCKWT_Delete:{
						e = __ParseNode<DeleteStatementNode>(vecInfo,idx);
									   }break;
					case enCKWT_Return:{
						e = __ParseNode<ReturnStatementNode>(vecInfo,idx);
									   }break;
					case enCKWT_Const:
					case enCKWT_Static:
					case enCKWT_Unsigned:
					case enCKWT_Void:
					case enCKWT_Bool:		//	bool
					case enCKWT_Char:		//	char
					case enCKWT_Short:		//	short
					case enCKWT_Int:			//	int
					case enCKWT_Long:		//	long
					case enCKWT_Int64:		//	_int64
					case enCKWT_Float:		//	float
					case enCKWT_Double:		//	double
						{
						e = __ParseNode<VariableNode>(vecInfo,idx);
						}break;
					default:{
						e = __ParseNode<StatementNode>(vecInfo,idx);
							}break;
					}
					if(e==enSE_OK){
						continue;
					}else{
						return e;
					}
				}else{
					e = __ParseNode<StatementNode>(vecInfo,idx);
					if(e==enSE_OK){
						continue;
					}else{
						return e;
					}
				} 

				//if(tObjType.eWordtype	==	enWT_Unknown){
				//	ObjectNode*		pObj	=	(ObjectNode*)FindNode(vecInfo[idx].str,enNT_Object);
				//	if(pObj!=NULL){
				//		U32 uiTempIdx	=	idx;
				//		Node* pNode = new VariableNode();
				//		AddChild(pNode);
				//		enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
				//		if(e!=enSE_OK){
				//			return e;
				//		}else{
				//			idx	=	uiTempIdx;
				//		}
				//		continue;
				//	}
				//	VariableNode*		pVar	=	(VariableNode*)FindNode(vecInfo[idx].str,enNT_Variable);
				//	if(pObj!=NULL){
				//		U32 uiTempIdx	=	idx;
				//		Node* pNode = new ExpressionNode();
				//		AddChild(pNode);
				//		enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
				//		if(e!=enSE_OK){
				//			return e;
				//		}else{
				//			idx	=	uiTempIdx;
				//		}
				//		continue;
				//	}
				//	ParameterNode*		pParam	=	(ParameterNode*)FindNode(vecInfo[idx].str,enNT_Parameter);
				//	if(pParam!=NULL){
				//		U32 uiTempIdx	=	idx;
				//		Node* pNode = new ExpressionNode();
				//		AddChild(pNode);
				//		enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
				//		if(e!=enSE_OK){
				//			return e;
				//		}else{
				//			idx	=	uiTempIdx;
				//		}
				//		continue;
				//	}
				//	FunctionNode*		pFunction	=	(FunctionNode*)FindNode(vecInfo[idx].str,enNT_Function);
				//	if(pParam!=NULL){
				//		U32 uiTempIdx	=	idx;
				//		Node* pNode = new FunctionCallExpressionNode();
				//		AddChild(pNode);
				//		enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
				//		if(e!=enSE_OK){
				//			return e;
				//		}else{
				//			idx	=	uiTempIdx;
				//		}
				//		continue;
				//	}
				//	return enSE_Unrecognized_Variable;
				//}else{
				//	return enSE_UnexpectedEnd;
				//}

				//if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
				//	idx++;
				//	continue;
				//}
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


	}
}