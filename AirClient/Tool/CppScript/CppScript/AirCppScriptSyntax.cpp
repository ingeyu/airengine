#include "AirCppScriptSyntax.h"
#include <Windows.h>

namespace	Air{
	namespace	CppScript{


		Node::Node()
		{
			m_Type		=	enNT_Global;
			m_pParent	=	NULL;
		}

		Node::~Node()
		{
			DeleteAllElement(m_lstChild);
		}

		enumSyntaxError Node::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize = vecInfo.size();
			if(idx >=uiSize){
				return enSE_UnexpectedEnd;
			}
			
			for(;idx<uiSize;){
				enumSyntaxError	e	=	enSE_OK;
				WordType& t = vecInfo[idx].eType;
				switch(t.eWordtype){
					case enWT_PreDeclare:{
						idx++;
						e	=	ParsePreDeclare(vecInfo,idx);
									 }break;
					case enWT_CppKeyWord:{
						e	=	ParseCppKeyword(vecInfo,idx);
										 }break;
					case enWT_Operator:{
						return enSE_Unrecognized_Operator;
										 }break;
					case enWT_Delimiter:{
						return enSE_Unrecognized_Delimiter;
										}break;

				}
				if(e!=enSE_OK){
					return e;
				}
			}
			return enSE_OK;
		}

		enumSyntaxError Node::ParsePreDeclare( WordInfoVector& vecInfo,U32& idx )
		{
			if(idx>=vecInfo.size())
				return enSE_UnexpectedEnd;

			WordType& t = vecInfo[idx].eType;
			if(t.eWordtype!=enWT_CppKeyWord){
				return	enSE_PreDeclare_Must_Fallow_A_CppKeyword;
			}
			switch(t.eKeyword){
				case	enCKWT_Include:{
					return ParseInclude(vecInfo,idx);
									   }break;
				case	enCKWT_Define:{
					return ParseDefine(vecInfo,idx);
									   }break;
				case	enCKWT_Typedef:{
					idx++;
									   }break;
				case	enCKWT_Program:{
					idx++;
									   }break;
				case	enCKWT_Warning:{
					idx++;
									   }break;
				case	enCKWT_Error:{
					idx++;
									   }break;
				case	enCKWT_If:{
					idx++;
									   }break;
				case	enCKWT_Else:{
					idx++;
									   }break;
				case	enCKWT_ElseIf:{
					idx++;
									   }break;
				case	enCKWT_EndIf:{
					idx++;
									   }break;
				case	enCKWT_Ifdef:{
					idx++;
									 }break;
				case	enCKWT_Ifndef:{
					idx++;
									  }break;
				
			}
			return enSE_PreDeclare_Fallow_Unknown;
		}

		Air::CppScript::enumSyntaxError Node::ParseInclude( WordInfoVector& vecInfo,U32& idx )
		{
			if(idx>=vecInfo.size())
				return enSE_UnexpectedEnd;
			WordType& t = vecInfo[idx].eType;
			if(t.eWordtype!=enWT_Variable){
				return	enSE_Include_Must_Fallow_A_String;
			}
			if(t.eKeyword!=enVT_String){
				return	enSE_Include_Must_Fallow_A_String;
			}
			return GetRootNode()->AddInclude(vecInfo[idx++].str);
		}

		Node* Node::GetRootNode()
		{
			if(m_pParent!=NULL){
				return m_pParent->GetRootNode();
			}else{
				return this;
			}
		}

		Air::CppScript::enumSyntaxError Node::AddInclude( CAString& strName )
		{
			Print("INCLUDE=");
			Print(strName.c_str());
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::ParseDefine( WordInfoVector& vecInfo,U32& idx )
		{
			if(idx>=vecInfo.size())
				return enSE_UnexpectedEnd;
			WordType& t = vecInfo[idx].eType;
			if(t.eWordtype==enWT_CppKeyWord){
				return	enSE_Define_Cant_Fallow_A_CppKeyword;
			}else if(t.eWordtype==enWT_Operator){
				return	enSE_Define_Cant_Fallow_A_Operator;
			}else if(t.eWordtype==enWT_Delimiter){
				if(t.eKeyword	!=	enWDT_PrePriority){
					return	enSE_Define_Cant_Fallow_A_Delimiter;
				}
			}else if(t.eWordtype==enWT_Variable){
				if(t.eKeyword	==	enVT_IntNumber	||	t.eKeyword	==	enVT_FloatNumber){
					return	enSE_Define_Cant_Fallow_A_Number;
				}else if(t.eKeyword	==	enVT_String){
					return	enSE_Define_Cant_Fallow_A_String;
				}
			}

			return GetRootNode()->AddDefine(vecInfo[idx++].str);
		}

		Air::CppScript::enumSyntaxError Node::AddDefine( CAString& strName )
		{
			Print("DEFINE=");
			Print(strName.c_str());
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::ParseCppKeyword( WordInfoVector& vecInfo,U32& idx )
		{
			if(idx>=vecInfo.size())
				return enSE_UnexpectedEnd;

			WordType& t = vecInfo[idx].eType;
			
			switch(t.eKeyword){
				case	enCKWT_NameSpace:{
					Node* pNode = new NameSpaceNode();
					pNode->SetParent(this);
					pNode->SetType(enNT_NameSpace);
					AddChild(pNode);
					idx++;
					enumSyntaxError e = pNode->Parse(vecInfo,idx);
					if(enSE_OK != e){
						delete pNode;
					}
					return e;
										 }break;
				case enCKWT_Const:{
					idx++;
					return enSE_OK;
								  }break;
				case enCKWT_Static:{
					idx++;
					return enSE_OK;
								   }break;
				case enCKWT_Unsigned:{
					idx++;
					return enSE_OK;
									 }break;
				case enCKWT_Void:{

								 }break;
			}
			return enSE_OK;
		}

		enumSyntaxError Node::IsVariableDeclare( WordInfoVector& vecInfo,U32& idx )
		{
			WordType	tObjType	=	vecInfo[idx].eType;
			AString		strObjName;
			U32 i = idx+1;
			U32 uiSize =	vecInfo.size();
			if(i>=uiSize){
				return enSE_UnexpectedEnd; 
			}
			WordType t = vecInfo[i].eType;
			if(t.eWordtype == enWT_Operator	&&	t.eKeyword	==	enOT_Mul){
				//tObjType.eBaseObj
			}

		
			return enSE_OK;
		}

		enumSyntaxError Node::IsFunctionDeclare( WordInfoVector& vecInfo,U32& idx )
		{
			return enSE_OK;
		}

		void Print( const char* str )
		{
			OutputDebugStringA(str);
			OutputDebugStringA("\n");
		}


		Air::CppScript::enumSyntaxError NameSpaceNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			if(idx>=vecInfo.size())
				return enSE_UnexpectedEnd;

			WordType& t = vecInfo[idx].eType;

			if(t.eWordtype==enWT_CppKeyWord){
				return	enSE_NameSpace_Cant_Fallow_A_CppKeyword;
			}else if(t.eWordtype==enWT_Operator){
				return	enSE_NameSpace_Cant_Fallow_A_Operator;
			}else if(t.eWordtype==enWT_Delimiter){
				return	enSE_NameSpace_Cant_Fallow_A_Delimiter;
			}else if(t.eWordtype==enWT_Variable){
				if(t.eKeyword	==	enVT_IntNumber	||	t.eKeyword	==	enVT_FloatNumber){
					return	enSE_NameSpace_Cant_Fallow_A_Number;
				}else if(t.eKeyword	==	enVT_String){
					return	enSE_NameSpace_Cant_Fallow_A_String;
				}
			}
			m_strName	=	vecInfo[idx].str;
			idx++;

			for(;idx<vecInfo.size();){
				WordType& t = vecInfo[idx].eType;
				if(t.eWordtype	==	enWT_Delimiter	&&	t.eKeyword	==	enWDT_BlockEnd){
					idx++;
					return enSE_OK;
				}
				if(t.eWordtype	==	enWT_Delimiter	&&	t.eKeyword	==	enWDT_BlockBegin){
					idx++;
					continue;
				}
				enumSyntaxError e = Node::Parse(vecInfo,idx);
				if(e!=enSE_OK){
					return e;
				}
			}


			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError VariableNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize =	vecInfo.size();

			WordType	tObjType	=	vecInfo[idx].eType;
			if(tObjType.eWordtype	==	enWT_CppKeyWord){
				if(tObjType.eKeyword	==	enCKWT_Const){
					m_VariableType.bConst	=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}
			if(tObjType.eWordtype	==	enWT_CppKeyWord){
				if(tObjType.eKeyword	==	enCKWT_Static){
					m_VariableType.bStatic	=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}
			if(tObjType.eWordtype	==	enWT_CppKeyWord){
				if(tObjType.eKeyword	==	enCKWT_Static){
					m_VariableType.bUnsign	=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
					if(tObjType.eWordtype	==	enWT_CppKeyWord){
						if(tObjType.eKeyword	==	enCKWT_Void){
							return enSE_Unsigned_Not_Match_Void;
						}else if(tObjType.eKeyword	==	enCKWT_Bool){
							return enSE_Unsigned_Not_Match_Bool;
						}else if(tObjType.eKeyword	==	enCKWT_Float){
							return enSE_Unsigned_Not_Match_Float;
						}else if(tObjType.eKeyword	==	enCKWT_Double){
							return enSE_Unsigned_Not_Match_Double;
						}
					}
					
				}
			}
			if(tObjType.eWordtype	==	enWT_CppKeyWord){
				switch(tObjType.eKeyword){
					case enCKWT_Void:{
						m_VariableType.iSize	=	0;
						m_VariableType.t		=	enBOT_Void;
									 }break;
					case enCKWT_Bool:{
						m_VariableType.iSize	=	1;
						m_VariableType.t		=	enBOT_Bool;
									 }break;
					case enCKWT_Char:{
						m_VariableType.iSize	=	1;
						m_VariableType.t		=	enBOT_S8;
									 }break;
					case enCKWT_Short:{
						m_VariableType.iSize	=	2;
						m_VariableType.t		=	enBOT_S16;
									 }break;
					case enCKWT_Int:
					case enCKWT_Long:{
						m_VariableType.iSize	=	4;
						m_VariableType.t		=	enBOT_S32;
									 }break;
					case enCKWT_Int64:{
						m_VariableType.iSize	=	8;
						m_VariableType.t		=	enBOT_S64;
									 }break;
					case enCKWT_Float:{
						m_VariableType.iSize	=	4;
						m_VariableType.t		=	enBOT_F32;
									  }break;
					case enCKWT_Double:{
						m_VariableType.iSize	=	8;
						m_VariableType.t		=	enBOT_F64;
									  }break;
					default:{
						if(m_VariableType.bUnsign==0){
							return enSE_Unrecognized_Variable_Type;
						}
							}break;
				}
			}else{
				if(m_VariableType.bUnsign==0){
					return enSE_Unrecognized_Variable_Type;
				}
			}
			if(idx+1>=uiSize){
				return enSE_UnexpectedEnd; 
			}
			tObjType	=	vecInfo[++idx].eType;


			if(tObjType.eWordtype == enWT_Operator){
				if( tObjType.eKeyword	==	enOT_Mul){
					m_VariableType.bPointor	=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}

			if(tObjType.eWordtype == enWT_Operator){
				if( tObjType.eKeyword	==	enOT_Mul){
					m_VariableType.bpp		=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}
			if(tObjType.eWordtype == enWT_Operator){
				if( tObjType.eKeyword	==	enOT_And){
					m_VariableType.bRef		=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}

			if(tObjType.eWordtype	!=	enWT_Unknown){
				if(	tObjType.eWordtype	==	enWT_Operator	||
					tObjType.eWordtype	==	enWT_Delimiter	)
				{
					return enSE_Miss_Variable_Name;
				}else if(tObjType.eWordtype	==	enWT_CppKeyWord){
					return enSE_Variable_Name_Cant_Be_A_CppKeyword;
				}else if(tObjType.eWordtype	==	enWT_Variable){
					if(tObjType.eKeyword	==	enVT_IntNumber	||	tObjType.eKeyword	==	enVT_FloatNumber){
						return enSE_Variable_Name_Cant_Be_A_Number;
					}else if(tObjType.eKeyword	==	enVT_String){
						return enSE_Variable_Name_Cant_Be_A_String;
					}
				}
				return enSE_Illegal_Variable_Name;
			}
			m_strName	=	vecInfo[idx].str;
			if(idx+1>=uiSize){
				return enSE_UnexpectedEnd; 
			}
			tObjType	=	vecInfo[++idx].eType;
			if(tObjType.eWordtype	==	enWT_Operator	&&	tObjType.eKeyword	==	enOT_Mov){
				m_bHasInitValue	=	1;
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				tObjType	=	vecInfo[++idx].eType;
			}

			if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Statement){
				idx++;
				return enSE_OK;
			}


			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError FunctionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError ClassNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			return enSE_UnexpectedEnd;
		}

	}
}