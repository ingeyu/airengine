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
						if(t.eKeyword	==	enWDT_Semicolon){
							idx++;
							if(idx >=uiSize){
								return enSE_OK;
							}
							continue;
						}
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
				if(t.eKeyword	!=	enWDT_PreBracket){
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
						RemoveChild(pNode);
						delete pNode;
						return e;
					}
					
										 }break;
				case enCKWT_Struct:
				case enCKWT_Class:	{
					Node* pNode = new ObjectNode();
					pNode->SetParent(this);
					pNode->SetType(enNT_Object);
					AddChild(pNode);
					idx++;
					enumSyntaxError e = pNode->Parse(vecInfo,idx);
					if(enSE_OK != e){
						RemoveChild(pNode);
						delete pNode;
						return e;
					}
					
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
						U32 uiTempIdx	=	idx;
						Node* pNode = new VariableNode();
						AddChild(pNode);
						enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							RemoveChild(pNode);
							delete pNode;
							uiTempIdx	=	idx;
							pNode		=	new	FunctionNode();
							AddChild(pNode);
							e = pNode->Parse(vecInfo,uiTempIdx);
							if(e!=enSE_OK){
								RemoveChild(pNode);
								delete pNode;
								return enSE_Unknown_Error;
							}else{
								idx	=	uiTempIdx;
							}
						}else{
							
							idx	=	uiTempIdx;
						}
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

		Node* Node::FindNode( CAString& strName,enumNodeType type,U1 bFindParent )
		{
			for(NodeList::iterator i = m_lstChild.begin();i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(type!=enNT_Unknown){
						if(pNode->GetType()!=type)
							continue;
					}
					if(pNode->GetName()	==	strName){
						return pNode;
					}
				}
			}
			if(bFindParent&&m_pParent!=NULL){
				return m_pParent->FindNode(strName,type);
			}
			return NULL;
		}

		void Node::AddChild( Node* p )
		{
			if(p!=NULL){
				p->SetParent(this);
				m_lstChild.push_back(p);
			}
		}

		void Node::RemoveChild( Node* p )
		{
			if(p==NULL)
				return;
			for(NodeList::iterator i = m_lstChild.begin();i!=m_lstChild.end();){
				if(*i==p){
					p->SetParent(NULL);
					i = m_lstChild.erase(i);
				}else{
					i++;
				}
			}
		}


		Air::CppScript::enumSyntaxError Node::ParseObjectType( WordInfoVector& vecInfo,U32& idx,ObjectType& t ,Node** pObjectNode)
		{
			U32 uiSize =	vecInfo.size();

			WordType	tObjType	=	vecInfo[idx].eType;
			if(tObjType.eWordtype	==	enWT_CppKeyWord){
				if(tObjType.eKeyword	==	enCKWT_Const){
					t.bConst	=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}
			if(tObjType.eWordtype	==	enWT_CppKeyWord){
				if(tObjType.eKeyword	==	enCKWT_Static){
					t.bStatic	=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}
			if(tObjType.eWordtype	==	enWT_CppKeyWord){
				if(tObjType.eKeyword	==	enCKWT_Unsigned){
					t.bUnsign	=	1;
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
					if(t.bUnsign==1){
						return enSE_Void_Cant_Be_Unsigned;
					}
					t.iSize	=	0;
					t.t		=	enBOT_Void;
								 }break;
				case enCKWT_Bool:{
					if(t.bUnsign==1){
						return enSE_Bool_Cant_Be_Unsigned;
					}
					t.iSize	=	1;
					t.t		=	enBOT_Bool;
								 }break;
				case enCKWT_Char:{
					t.iSize	=	1;
					t.t		=	enBOT_S8;
								 }break;
				case enCKWT_Short:{
					t.iSize	=	2;
					t.t		=	enBOT_S16;
								  }break;
				case enCKWT_Int:
				case enCKWT_Long:{
					t.iSize	=	4;
					t.t		=	enBOT_S32;
								 }break;
				case enCKWT_Int64:{
					t.iSize	=	8;
					t.t		=	enBOT_S64;
								  }break;
				case enCKWT_Float:{
					if(t.bUnsign==1){
						return enSE_Float_Cant_Be_Unsigned;
					}
					t.iSize	=	4;
					t.t		=	enBOT_F32;
								  }break;
				case enCKWT_Double:{
					if(t.bUnsign==1){
						return enSE_Float_Cant_Be_Unsigned;
					}
					t.iSize	=	8;
					t.t		=	enBOT_F64;
								   }break;
				default:{
					if(t.bUnsign==0){
						return enSE_Unrecognized_Variable_Type;
					}
						}break;
				}
			}else{

				if(t.bUnsign==0){
					Node* pNode	=	GetParent()->FindNode(vecInfo[idx].str,enNT_Object);
					if(pNode==NULL){
						return enSE_Unrecognized_Variable_Type;
					}
					ObjectNode* pObj = (ObjectNode*)pNode;
					t.t		=	enBOT_Obj;
					t.iSize	=	pObj->GetObjectSize();
					if(pObjectNode!=NULL){
						*pObjectNode	=	pObj;
					}
				}
			}
			if(idx+1>=uiSize){
				return enSE_UnexpectedEnd; 
			}
			tObjType	=	vecInfo[++idx].eType;


			if(tObjType.eWordtype == enWT_Operator){
				if( tObjType.eKeyword	==	enOT_Mul){
					t.bPointor	=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}

			if(tObjType.eWordtype == enWT_Operator){
				if( tObjType.eKeyword	==	enOT_Mul){
					t.bpp		=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}
			if(tObjType.eWordtype == enWT_Operator){
				if( tObjType.eKeyword	==	enOT_And){
					t.bRef		=	1;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}
			}
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::ParseVariableName( WordInfoVector& vecInfo,U32& idx,AString& strName,U1 bCheckExist )
		{
			U32 uiSize	=	vecInfo.size();

			WordType tObjType	=	vecInfo[idx].eType;

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
			}else{
				Node* pParent = GetParent();
				if(bCheckExist&&pParent&&pParent->FindNode(vecInfo[idx].str,enNT_Unknown,false)!=NULL){
					return enSE_Variable_Name_Already_Declaration;
				}
			}
			strName	=	vecInfo[idx].str;
			if(idx+1>=uiSize){
				return enSE_UnexpectedEnd; 
			}
			tObjType	=	vecInfo[++idx].eType;
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
				if(t.eWordtype	==	enWT_Delimiter	&&	t.eKeyword	==	enWDT_PostBrace){
					idx++;
					return enSE_OK;
				}
				if(t.eWordtype	==	enWT_Delimiter	&&	t.eKeyword	==	enWDT_PreBrace){
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
			enumSyntaxError	e	=	enSE_OK;
			e	=	ParseObjectType(vecInfo,idx,m_VariableType.type,&m_VariableType.pNodePtr);
			if(e!=enSE_OK)
				return e;
			e	=	ParseVariableName(vecInfo,idx,m_strName);
			if(e!=enSE_OK)
				return e;
			U32 uiSize	=	vecInfo.size();
			WordType tObjType	=	vecInfo[idx].eType;

			if(tObjType.eWordtype	==	enWT_Operator	&&	tObjType.eKeyword	==	enOT_Mov){
				m_bHasInitValue	=	1;
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				tObjType	=	vecInfo[++idx].eType;
			}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
				idx++;
				return enSE_OK;
			}else{
				return	enSE_Variable_Miss_Delimiter_End_Of_Statement;
			}

			if(tObjType.eWordtype == enWT_CppKeyWord && tObjType.eKeyword	==	enOT_Sub){
				if(m_VariableType.type.bUnsign==1){
					return enSE_Unsigned_Object_Cant_Be_A_Negative_Value;
				}
				if(m_VariableType.type.t	==	enBOT_Bool){
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
			
			if(tObjType.eWordtype	==	enWT_Variable){
				if(	m_VariableType.type.t	==	enBOT_S8	&&	
					m_VariableType.type.bPointor	==	1	&&
					m_VariableType.type.bUnsign	==	0	&&
					m_VariableType.type.bpp		==	0	&&
					tObjType.eKeyword		==	enVT_String)
				{
					m_InitInfo	=	vecInfo[idx];
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
					
				}else if(	m_VariableType.type.t	==	enBOT_S8	||
					m_VariableType.type.t	==	enBOT_S16	||
					m_VariableType.type.t	==	enBOT_S32	||
					m_VariableType.type.t	==	enBOT_S64	||
					m_VariableType.type.bPointor	==	1)
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
				else	if(m_VariableType.type.t	==	enBOT_F32	||	m_VariableType.type.t	==	enBOT_F64)
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
			}else if(m_VariableType.type.bPointor==1	&&	tObjType.eKeyword	==	enCKWT_Null){
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
			}else{
				return enSE_Unrecognized_Variable_Init_Value;
			}
			
			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError FunctionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	 = vecInfo.size();
			WordType tObjType	=	vecInfo[idx].eType;

			if(tObjType.eWordtype	==	enWT_CppKeyWord	&&	tObjType.eKeyword	==	enCKWT_Virtual){
				m_bVirtual	=	1;
				if(idx+1 > uiSize){
					return enSE_UnexpectedEnd;
				}
				idx++;
			}
			enumSyntaxError	e	=	enSE_OK;
			e	=	ParseObjectType(vecInfo,idx,m_ReturnType.type,(Node**)&m_ReturnType.pNodePtr);
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
				
				Parameter p;
				enumSyntaxError e = enSE_OK;
				e =	ParseObjectType(vecInfo,idx,p.type,(Node**)&p.pNodePtr);
				if(e!=enSE_OK){
					return e;
				}
				e	=	ParseVariableName(vecInfo,idx,p.strName,false);
				if(e!=enSE_OK)
					return e;
				if(IsParamNameExist(p.strName)){
					return enSE_Function_Parameter_Name_Already_Exist;
				}
				tObjType	=	vecInfo[idx].eType;
				if(tObjType.eWordtype	==	enWT_Operator	&&	tObjType.eKeyword	==	enOT_Mov){
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					tObjType	=	vecInfo[++idx].eType;
				}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Comma){
					m_vecParameter.push_back(p);
					idx++;
					if(idx+1>=uiSize){
						return enSE_UnexpectedEnd; 
					}
					continue;
				}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBracket){
					m_vecParameter.push_back(p);
				}else{
					return enSE_Unrecognized_Parameter;
				}
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
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBrace){
					idx++;
					return enSE_OK;
				}
				U32 uiTempIndex	=	idx;
				ObjectType			tempType;
				Node*				pObjectNode=NULL;
				e	=	ParseObjectType(vecInfo,uiTempIndex,tempType,&pObjectNode);
				if(e!=enSE_OK){
					uiTempIndex	=	idx;
				}else{
					AString strName;
					e	=	ParseVariableName(vecInfo,uiTempIndex,strName);
					if(e!=enSE_OK){
						return e;
					}else{
						idx	=	uiTempIndex;
					}
				}

				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					continue;
				}
			}
			return enSE_UnexpectedEnd;
		}

		Air::U1 FunctionNode::IsParamNameExist( CAString& strName )
		{
			if(strName.empty())
				return false;
			U32 uiSize	=	m_vecParameter.size();
			for(U32 i=0;i<uiSize;i++){
				if(m_vecParameter[i].strName	==	strName){
					return true;
				}
			}
			return false;
		}


		Air::CppScript::enumSyntaxError ObjectNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	 = vecInfo.size();
			if(idx > uiSize)
				return enSE_UnexpectedEnd;
			WordType tObjType	=	vecInfo[idx].eType;
			//Class Name
			if(tObjType.eWordtype	==	enWT_Unknown	&&	tObjType.eKeyword	==	enCKWT_Unknown){
				AString& str =	vecInfo[idx].str;
				Node* pNode =	GetParent()->FindNode(str);
				if(pNode!=NULL){
					return enSE_Class_Or_Struct_Name_Already_Exist;
				}
				m_strName	=	str;
				if(idx+1 > uiSize)
					return enSE_UnexpectedEnd;
				tObjType	=	vecInfo[++idx].eType;
			}else{
				return enSE_Illegal_Class_Or_Struct_Name;
			}

			if(tObjType.eWordtype	==	enWT_Delimiter&&tObjType.eKeyword==enWDT_Semicolon){
				m_bDeclare	=	true;
				idx++;
				return enSE_OK;
			}
			//Is Inherit
			if(tObjType.eWordtype	==	enWT_Operator	&&	tObjType.eKeyword	==	enOT_Colon){
				m_bInherit	=	true;
				if(idx+1 > uiSize)
					return enSE_UnexpectedEnd;
				tObjType	=	vecInfo[++idx].eType;
				//Is Public Private Protected
				if(tObjType.eWordtype	!=	enWT_CppKeyWord){
					if(	tObjType.eKeyword	==	enCKWT_Public	||
						tObjType.eKeyword	==	enCKWT_Private	||
						tObjType.eKeyword	==	enCKWT_Protected	){
							m_InheritType	=	tObjType.eKeyword;
							if(idx+1 > uiSize)
								return enSE_UnexpectedEnd;
							tObjType	=	vecInfo[++idx].eType;
					}else{
						return enSE_Unrecognized_Inherit_Type;
					}
				}	
				if(tObjType.eWordtype	!=	enWT_Unknown	||		tObjType.eKeyword	!=	enCKWT_Unknown){
					return enSE_Illegal_Class_Or_Struct_Name;
				}
				AString& strParentName	=	vecInfo[idx].str;
				m_pInherit	=	(ObjectNode*)FindNode(strParentName,enNT_Object);
				if(m_pInherit==NULL){
					return enSE_Unrecognized_Inherit_Object;
				}
			}

			if(tObjType.eWordtype	==	enWT_Delimiter	&&		tObjType.eKeyword	==	enWDT_PreBrace){
				if(idx+1 > uiSize)
					return enSE_UnexpectedEnd;
				tObjType	=	vecInfo[++idx].eType;
			}else{
				return enSE_UnexpectedEnd;
			}

			enumCppKeyWordType memberType = enCKWT_Public;

			enumSyntaxError	e = enSE_OK;
			for(;;){
				tObjType	=	vecInfo[idx].eType;
				if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_PostBrace){
					idx++;
					return enSE_OK;
				}
				
				if(tObjType.eWordtype!=enWT_CppKeyWord){
					return enSE_Unrecognized_Class_Or_Struct_Word;
				}
				switch(tObjType.eKeyword){
				case enCKWT_Public:
				case enCKWT_Private:
				case enCKWT_Protected:{
					memberType	=	tObjType.eKeyword;
					if(idx+1 > uiSize)
						return enSE_UnexpectedEnd;
					tObjType	=	vecInfo[++idx].eType;
					if(tObjType.eWordtype==enWT_Operator||tObjType.eKeyword==enOT_Colon){
						if(idx+1 > uiSize)
							return enSE_UnexpectedEnd;
						tObjType	=	vecInfo[++idx].eType;
					}else{
						return enSE_Public_Private_Protected_Must_Fallow_Colon;
					}
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
						U32 uiTempIdx	=	idx;
						Node* pNode = new VariableNode();
						AddChild(pNode);
						enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							RemoveChild(pNode);
							delete pNode;
							uiTempIdx	=	idx;
							pNode		=	new	FunctionNode();
							AddChild(pNode);
							e = pNode->Parse(vecInfo,uiTempIdx);
							if(e!=enSE_OK){
								RemoveChild(pNode);
								delete pNode;
								return enSE_Unknown_Error;
							}else{
								idx	=	uiTempIdx;
							}
						}else{

							idx	=	uiTempIdx;
						}
					}break;
				}
			}
			return enSE_UnexpectedEnd;
		}

		Air::U32 ObjectNode::GetObjectSize()
		{
			if(m_pInherit!=NULL){
				return m_uiObjSize+m_pInherit->GetObjectSize();
			}
			return m_uiObjSize;
		}

	}
}