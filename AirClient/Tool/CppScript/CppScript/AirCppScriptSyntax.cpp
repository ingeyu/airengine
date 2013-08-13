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
					case enCKWT_Unknown:{
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
					default:{
						return enSE_UnexpectedEnd;
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
			if(t.eWordtype!=enWT_Constant){
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
			}else if(t.eWordtype==enWT_Constant){
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
				case enCKWT___declspec:{
					Node* pNode = new ImportFunctionNode();
					AddChild(pNode);
					idx++;
					enumSyntaxError e = pNode->Parse(vecInfo,idx);
					if(enSE_OK != e){
						RemoveChild(pNode);
						delete pNode;
						return e;
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
				}else if(tObjType.eWordtype	==	enWT_Constant){
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

		Air::CppScript::enumSyntaxError Node::FindBlock( WordInfoVector& vecInfo,U32& idx,WordInfoVector& outInfo,U32 uiKeyBegin,U32 uiKeyEnd )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			U32 uiBeginIndx	=	0XFFFFFFFF;
			U32 uiEndIndex	=	0XFFFFFFFF;
			U32 uiDepth		=	0;
			for(U32 i=idx;i<uiSize;i++){
				if(uiKeyBegin	==	vecInfo[i].eType.uiType){
					if(uiDepth==0){
						uiBeginIndx	=	i;
					}
					uiDepth++;
					continue;
				}
				if(uiKeyEnd	==	vecInfo[i].eType.uiType){
					if(uiDepth==1){
						uiEndIndex	=	i;
						break;
					}
					uiDepth--;
					continue;
				}
			}
			if(uiDepth!=0){
				return	enSE_UnexpectedEnd;
			}
			if(uiBeginIndx==0XFFFFFFFF||uiEndIndex==0XFFFFFFFF){
				return enSE_UnexpectedEnd;
			}
			U32 uiCount	=	uiEndIndex	-	uiBeginIndx+1;
			outInfo.resize(uiCount);
			for(U32 i=0;i<uiCount;i++){
				outInfo[i]=vecInfo[uiBeginIndx+i];
			}
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::FindStatementEnd( WordInfoVector& vecInfo,U32& idx,WordInfoVector& outInfo )
		{

			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			U32 uiBeginIndx	=	0XFFFFFFFF;
			U32 uiEndIndex	=	0XFFFFFFFF;
			U32 uiKeyEnd	=	MakeType(enWT_Delimiter,enWDT_Semicolon,0,0);
			for(U32 i=idx;i<uiSize;i++){

				if(uiKeyEnd	==	vecInfo[i].eType.uiType){
					uiEndIndex	=	i;
					break;

				}
			}
			if(uiBeginIndx==0XFFFFFFFF||uiEndIndex==0XFFFFFFFF){
				return enSE_UnexpectedEnd;
			}
			U32 uiCount	=	uiEndIndex	-	uiBeginIndx+1;
			outInfo.resize(uiCount);
			for(U32 i=0;i<uiCount;i++){
				outInfo[i]=vecInfo[uiBeginIndx+i];
			}
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
			}else if(t.eWordtype==enWT_Constant){
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
			}else if(tObjType.eWordtype	==	enWT_Unknown){
				CAString& strKey	=	vecInfo[idx].str;
				Node* pNode			=	FindNode(strKey);
				if(pNode==NULL){
					return enSE_Unrecognized_Variable_Init_Value;
				}
				switch(pNode->GetType()){
					case enNT_Variable:
					case enNT_Parameter:{
						
						U32 uiTempIdx	=	idx;
						Node* pNode = new ExpressionNode();
						AddChild(pNode);
						enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							return e;
						}else{
							idx	=	uiTempIdx;
						}
									   }break;
					case enNT_Function:
					case enNT_ImportFunction:{
						idx++;
						U32 uiTempIdx	=	idx;
						FunctionCallExpressionNode* pExpression = new FunctionCallExpressionNode();
						pExpression->pFunction	=	pNode;
						AddChild(pExpression);
						enumSyntaxError	e = pExpression->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							return e;
						}else{
							idx	=	uiTempIdx;
							return enSE_OK;
							
						}
									   }break;
					default:{
						return enSE_Unrecognized_Variable_Init_Value;
							}break;
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
							U32 uiTempIdx	=	idx;
							Node* pNode = new IfStatementNode();
							AddChild(pNode);
							enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
							if(e!=enSE_OK){
								return e;
							}else{
								idx	=	uiTempIdx;
							}
								   }break;
						case enCKWT_For:{
							U32 uiTempIdx	=	idx;
							Node* pNode = new ForStatementNode();
							AddChild(pNode);
							enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
							if(e!=enSE_OK){
								return e;
							}else{
								idx	=	uiTempIdx;
							}
									   }break;
						case enCKWT_While:{
							U32 uiTempIdx	=	idx;
							Node* pNode = new WhileStatementNode();
							AddChild(pNode);
							enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
							if(e!=enSE_OK){
								return e;
							}else{
								idx	=	uiTempIdx;
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
								Node* pNode = new VariableStatementNode();
								AddChild(pNode);
								enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
								if(e!=enSE_OK){
									return enSE_Unknown_Error;
								}else{
									idx	=	uiTempIdx;
								}
							}break;
						default:{
							return enSE_UnexpectedEnd;
								}break;
					}
				}else if(tObjType.eWordtype	==	enWT_Unknown){
					ObjectNode*		pObj	=	(ObjectNode*)FindNode(vecInfo[idx].str,enNT_Object);
					if(pObj!=NULL){
						U32 uiTempIdx	=	idx;
						Node* pNode = new VariableNode();
						AddChild(pNode);
						enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							return e;
						}else{
							idx	=	uiTempIdx;
						}
						continue;
					}
					VariableNode*		pVar	=	(VariableNode*)FindNode(vecInfo[idx].str,enNT_Variable);
					if(pObj!=NULL){
						U32 uiTempIdx	=	idx;
						Node* pNode = new ExpressionNode();
						AddChild(pNode);
						enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							return e;
						}else{
							idx	=	uiTempIdx;
						}
						continue;
					}
					ParameterNode*		pParam	=	(ParameterNode*)FindNode(vecInfo[idx].str,enNT_Parameter);
					if(pParam!=NULL){
						U32 uiTempIdx	=	idx;
						Node* pNode = new ExpressionNode();
						AddChild(pNode);
						enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							return e;
						}else{
							idx	=	uiTempIdx;
						}
						continue;
					}
					FunctionNode*		pFunction	=	(FunctionNode*)FindNode(vecInfo[idx].str,enNT_Function);
					if(pParam!=NULL){
						U32 uiTempIdx	=	idx;
						Node* pNode = new FunctionCallExpressionNode();
						AddChild(pNode);
						enumSyntaxError	e = pNode->Parse(vecInfo,uiTempIdx);
						if(e!=enSE_OK){
							return e;
						}else{
							idx	=	uiTempIdx;
						}
						continue;
					}
					return enSE_Unrecognized_Variable;
				}else{
					return enSE_UnexpectedEnd;
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


		Air::CppScript::enumSyntaxError ExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize = vecInfo.size();
			WordInfo& info = vecInfo[idx];
			WordType t = info.eType;
			Node* p	=	FindNode(info.str);
			if(p==NULL){
				return enSE_Unrecognized_Variable;
			}
			if(p->GetType()!=enNT_Variable &&	p->GetType()!=enNT_Parameter){
				return enSE_Unrecognized_Variable;
			}
			pLeftNode	=	p;
			if(idx+1>=uiSize){
				return enSE_UnexpectedEnd; 
			}
			t	=	vecInfo[++idx].eType;
			if(t.eWordtype==enWT_Operator){
				eOperator	=	t.eKeyword;
				if(idx+1>=uiSize){
					return enSE_UnexpectedEnd; 
				}
				t	=	vecInfo[++idx].eType;
			}

			//if(t.eWordtype)

			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError ImportFunctionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			WordType t = vecInfo[idx].eType;
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


			return FunctionNode::Parse(vecInfo,idx);
		}


		Air::CppScript::enumSyntaxError FunctionCallExpressionNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
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
					if(idx+1>=uiSize)
						return enSE_UnexpectedEnd;
					t = vecInfo[++idx].eType;
					break;
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
			
			if(t.uiType!=MakeType(enWT_Delimiter,enWDT_Semicolon)){
				return enSE_UnexpectedEnd;
			}else{
				if(idx+1>=uiSize)
					return enSE_UnexpectedEnd;
				t = vecInfo[++idx].eType;
				return enSE_OK;
			}
			return enSE_UnexpectedEnd;
		}


		Air::CppScript::enumSyntaxError ConstantNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			ConstInfo	=	vecInfo[idx];
			if(ConstInfo.eType.eWordtype==enWT_Constant){
				idx++;
				return enSE_OK;
			}
			return enSE_UnexpectedEnd;
		}

	}
}