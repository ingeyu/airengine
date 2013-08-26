#include "AirCppScriptSyntaxNode.h"
#include "AirCppScriptSyntaxVariable.h"
#include "AirCppScriptSyntaxFunction.h"
#include "AirCppScriptSyntaxObject.h"
#include "AirCppScriptSyntaxNameSpace.h"
#include "AirCppScriptSyntaxExpression.h"
#include "AirCppScriptSyntaxStatement.h"
#include "AirCppScriptSyntaxConstant.h"
#include "AirCppScriptAssemble.h"
#include "AirCppScriptModule.h"
#include <string>
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
				if(idx>=uiSize)
					return enSE_OK;
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
					}else if(t.eKeyword	==	enWDT_PostBrace){
						return enSE_OK;
					}
					return enSE_Unrecognized_Delimiter;
									}break;
				case enCKWT_Unknown:{
					Node* pNode	=	FindNode(vecInfo[idx].str);
					if(pNode==NULL){
						return enSE_UnexpectedEnd;
					}
					if(pNode->GetType()	==	enNT_Object){
						
						e	=	__ParseNode<VariableNode>(vecInfo,idx);
						if(e!=enSE_OK){
							e = __ParseNode<FunctionNode>(vecInfo,idx);
							if(e!=enSE_OK){
								return enSE_Unknown_Error;
							}
						}
					}else	if(pNode->GetType()	==	enNT_Variable){
						
						e	=	__ParseNode<StatementNode>(vecInfo,idx);
						if(e!=enSE_OK){
							return e;
						}
					}else{

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
			enumSyntaxError e	=	enSE_OK;
			switch(t.eKeyword){
				case	enCKWT_NameSpace:{
					e = __ParseNode<NameSpaceNode>(vecInfo,idx);
										 }break;
				case enCKWT_Struct:
				case enCKWT_Class:	{
					e = __ParseNode<ObjectNode>(vecInfo,idx);
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
						if(e!=enSE_OK)
							e = __ParseNode<FunctionNode>(vecInfo,idx);
					}break;
				case enCKWT___declspec:{
					e = __ParseNode<FunctionNode>(vecInfo,idx);
									   }break;
				default:{
					e	=	enSE_UnexpectedEnd;
						}break;
			}

			return e;
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

		Air::CppScript::enumSyntaxError Node::FindBlock( WordInfoVector& vecInfo,U32& idx,WordInfoVector& outInfo,U32 uiKeyBegin,U32 uiKeyEnd ,U1 bIncludeKey)
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
						if(!bIncludeKey)
							uiBeginIndx++;
					}
					uiDepth++;
					continue;
				}
				if(uiKeyEnd	==	vecInfo[i].eType.uiType){
					if(uiDepth==1){
						uiEndIndex	=	i;
						uiDepth--;
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
			U32 uiCount	=	uiEndIndex	-	uiBeginIndx;
			if(uiCount==0){
				return enSE_OK;
			}
			if(bIncludeKey)
				uiCount++;
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

			U32 uiEndIndex	=	0XFFFFFFFF;
			U32 uiKeyEnd	=	MakeType(enWT_Delimiter,enWDT_Semicolon,0,0);
			for(U32 i=idx;i<uiSize;i++){

				if(uiKeyEnd	==	vecInfo[i].eType.uiType){
					uiEndIndex	=	i;
					break;

				}
			}
			if(uiEndIndex==0XFFFFFFFF){
				return enSE_UnexpectedEnd;
			}
			U32 uiCount	=	uiEndIndex	-	idx;
			outInfo.resize(uiCount);
			for(U32 i=0;i<uiCount;i++){
				outInfo[i]=vecInfo[idx+i];
			}
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::ParseExpression( WordInfoVector& vecInfo,U32& idx )
		{
			for(;idx<vecInfo.size();idx++){
				WordType t = vecInfo[idx].eType;
				if(t.uiType	==	MakeType(enWT_CppKeyWord,enCKWT_New)){

				}else if(t.eWordtype	==	enWT_Unknown){
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
							RemoveChild(pNode);
							delete pNode;
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

						}
											 }break;
					default:{
						return enSE_Unrecognized_Variable_Init_Value;
							}break;
					}
				}else if(t.eWordtype	==	enWT_Operator){
					idx++;
				}else if(t.eWordtype	==	enWT_Operator){
					idx++;
				}else{
					return enSE_Unrecognized_Variable_Init_Value;
				}
			}
			return enSE_OK;
		}

		Node* Node::__CheckNextNodeType( WordInfoVector& vecInfo,U32& idx,enumNodeType eType )
		{
			Node* pNode =	FindNode(vecInfo[idx].str);
			if(pNode==NULL){
				return NULL;
			}
			if(pNode->GetType()!=eType){
				return NULL;
			}
			idx++;
			return pNode;
		}

		Air::CppScript::enumSyntaxError Node::__CheckNextWordType( WordInfoVector& vecInfo,U32& idx,U32 uiType )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx+1	>=	uiSize){
				return enSE_UnexpectedEnd;
			}
			WordType	t	=	vecInfo[idx].eType;
			if(t.uiType	!=	uiType){
				return enSE_UnexpectedEnd;
			}
			return enSE_OK;
		}
		Air::CppScript::enumSyntaxError Node::ParseFunctionCode( WordInfoVector& vecInfo,U32& idx )
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

			}
			return enSE_UnexpectedEnd;
		}
		std::string strType[]={
			"enNT_Unknown",
			"enNT_Global",
			"enNT_NameSpace",
			"enNT_ImportFunction",
			"enNT_Variable",
			"enNT_Constant",
			"enNT_Function",
			"enNT_Object",
			"enNT_Parameter",
			"enNT_Statement",
			"enNT_Expression",
			"enNT_Block"
		};
		void Node::Print( std::string str )
		{
			
			printf("%sType[%s] Name[%s]\n",str.c_str(),strType[GetType()].c_str(),GetName().c_str());
			str+="----+";
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				(*i)->Print(str);
			}
		}

		Air::CppScript::enumSyntaxError Node::GenerateFunctionCode(Assemble& asmGen)
		{
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Function){
						pNode->GenerateFunctionCode(asmGen);
					}else if(pNode->GetType()==enNT_NameSpace){
						pNode->GenerateFunctionCode(asmGen);
					}
				}
			}
			return enSE_OK;
		}

		Air::U32 Node::CalcLocalVariableSize( U32& uiSize,U1 bChild )
		{
			//uiSize	=	0;
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Variable){
						VariableNode* pVar	=	(VariableNode*)pNode;
						U32 uiObjSize	=	pVar->VariableType.iSize;
						if(pVar->VariableType.t	==	enBOT_Obj){
							ObjectNode* pObj	=	(ObjectNode*)pVar->pNodePtr;
							uiObjSize	=	pObj->GetObjectSize();
						}
						if(pVar->VariableType.bPointor){
							uiObjSize=4;
						}
						U32 uiObjCount	=	1;
						if(pVar->uiArrayCount!=0){
							uiObjCount	=	pVar->uiArrayCount;
						}
						pVar->m_uiOffset	=	uiSize;
						uiSize+=	(uiObjCount*uiObjSize+1)&0xfffffffc;
					}else{
						if(bChild){
							pNode->CalcLocalVariableSize(uiSize);
						}
					}
				}
			}
			return uiSize;
		}

		Node* Node::FindNodeDown( CAString& strName,enumNodeType type /*= enNT_Unknown*/,U1 bFindChild /*= true*/ )
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
			if(bFindChild){
				for(NodeList::iterator i = m_lstChild.begin();i!=m_lstChild.end();i++){
					Node* pNode	=	(*i);
					if(pNode!=NULL){
						pNode->FindNodeDown(strName,type,bFindChild);
					}
				}
			}
			return NULL;
		}

		void Node::FindNodeDown( CAString& strName,std::list<Node*>& lstNode,enumNodeType type /*= enNT_Unknown*/ )
		{
			for(NodeList::iterator i = m_lstChild.begin();i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(type!=enNT_Unknown){
						if(pNode->GetType()==type){
							if(pNode->GetName()	==	strName){
								lstNode.push_back(pNode);
							}
						}
					}else{
						if(pNode->GetName()	==	strName){
							lstNode.push_back(pNode);
						}
					}
					
					pNode->FindNodeDown(strName,lstNode,type);
				}
			}
		}

		void Node::FindNodeDown( std::list<Node*>& lstNode,enumNodeType type /*= enNT_Unknown*/ )
		{
			for(NodeList::iterator i = m_lstChild.begin();i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(type!=enNT_Unknown){
						if(pNode->GetType()==type){
							lstNode.push_back(pNode);
						}
					}else{
						lstNode.push_back(pNode);
					}
					pNode->FindNodeDown(lstNode,type);
				}
			}
		}

		Air::CppScript::enumSyntaxError Node::Link( Assemble& asmGen )
		{
			enumSyntaxError	e	=	enSE_OK;

			ModuleHeader moduleHeader;
			InitModuleHeader(moduleHeader);
			asmGen.PushBuffer(moduleHeader);

			e	=	LinkImportFunction(asmGen);
			if(e!=enSE_OK)
				return e;

			e	=	LinkGolbalVariable(asmGen);
			if(e!=enSE_OK)
				return e;

			e	=	GenerateGlobalFunctionCode(asmGen);
			if(e!=enSE_OK)
				return e;



			e	=	GenerateFunctionCode(asmGen);
			if(e!=enSE_OK)
				return e;

			e	=	LinkExportFunction(asmGen);
			if(e!=enSE_OK)
				return e;

			ModuleHeader* pHeader	=	(ModuleHeader*)asmGen.GetBuffer();
			pHeader->ImageSize		=	asmGen.GetCurrentOffset();

			return e;
		}

		Air::CppScript::enumSyntaxError Node::LinkGolbalVariable( Assemble& asmGen )
		{
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();

			U32	uiOldOffset	=	asmGen.GetCurrentOffset();
			U32 uiOffset	=	uiOldOffset;
			NodeList::iterator i = m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* p =	(*i);
				if(p!=NULL){
					if(p->GetType()==enNT_Variable){
						VariableNode* pVar	=	(VariableNode*)p;
						U32 uiObjSize	=	pVar->VariableType.iSize;
						if(pVar->VariableType.t	==	enBOT_Obj){
							ObjectNode* pObj	=	(ObjectNode*)pVar->pNodePtr;
							uiObjSize	=	pObj->GetObjectSize();
						}
						if(pVar->VariableType.bPointor){
							uiObjSize=4;
						}
						U32 uiObjCount	=	1;
						if(pVar->uiArrayCount!=0){
							uiObjCount	=	pVar->uiArrayCount;
						}
						pVar->m_uiOffset	=	uiOffset;
						uiOffset+=	uiObjCount*uiObjSize;
					}else if(p->GetType()==enNT_Constant){
						ConstantNode* pCon	=	(ConstantNode*)p;
						if(pCon->ConstInfo.eType.eKeyword	==	enVT_String){
							pCon->m_uiOffset	=	uiOffset;
							uiOffset+=	pCon->ConstInfo.str.size()+1;
							memcpy(asmGen.GetBuffer(pCon->m_uiOffset),pCon->ConstInfo.str.c_str(),pCon->ConstInfo.str.size()+1);
						}
					}
				}
			}
			asmGen.AddOffset(uiOffset-uiOldOffset);

			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::LinkImportFunction( Assemble& asmGen )
		{

			ModuleHeader* pHeader	=	(ModuleHeader*)asmGen.GetBuffer();
			pHeader->IATArray_RA	=	asmGen.GetCurrentOffset();

			IAT iat;
			
			NodeList::iterator i = m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* p =	(*i);
				if(p!=NULL){
					if(p->GetType()==enNT_Function){
						FunctionNode* pFunc = (FunctionNode*)(p);
						if(	pFunc->ieType	==	enCKWT_dllimport &&
							pFunc->RefCount	!=	0)
						{
							memset(&iat,0,sizeof(iat));
							iat.jump[0]	=	eC_JMP_REL32;
							strcpy(&iat.Name[0],pFunc->GetName().c_str());
							pFunc->pEntry	=	asmGen.PushBuffer(iat);
							pHeader->IATCount++;
						}
						
					}
				}
			}
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			asmGen.Nop();
			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::GenerateGlobalFunctionCode( Assemble& asmGen )
		{
			ModuleHeader* pHeader	=	(ModuleHeader*)asmGen.GetBuffer();
			pHeader->Entry_RA		=	asmGen.GetCurrentOffset();

			asmGen.Code(eC_PUSH_EBP);
			asmGen.Code(eC_PUSH_EBX);
			asmGen.Code(eC_PUSH_EDX);
			asmGen.Code(eC_PUSH_ESI);
			asmGen.Mov_R32R32(eAR_EBP,eAR_ESP);

			NodeList::iterator i = m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* p =	(*i);
				if(p!=NULL){
					if(p->GetType()==enNT_Statement){
						p->GenerateFunctionCode(asmGen);
					}
				}
			}
			asmGen.Mov_R32R32(eAR_ESP,eAR_EBP);
			asmGen.Code(eC_POP_ESI);
			asmGen.Code(eC_POP_EDX);
			asmGen.Code(eC_POP_EBX);
			asmGen.Code(eC_POP_EBP);
			asmGen.Ret(4);
			asmGen.Code(eC_NOP);
			asmGen.Code(eC_NOP);
			asmGen.Code(eC_NOP);
			asmGen.Code(eC_NOP);

			return enSE_OK;
		}

		Air::CppScript::enumSyntaxError Node::LinkExportFunction( Assemble& asmGen )
		{
			ModuleHeader* pHeader	=	(ModuleHeader*)asmGen.GetBuffer();

			NodeList::iterator i = m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* p =	(*i);
				if(p!=NULL){
					if(p->GetType()==enNT_Function){
						FunctionNode* pFunc = (FunctionNode*)(p);
						if(pFunc->ieType	==	enCKWT_dllexport){
							EAT& eat	=	pHeader->EATArray[pHeader->EATCount];
							strcpy(&eat.Name[0],pFunc->GetName().c_str());
							eat.EAT_RA	=	pFunc->GetEntry();
							pHeader->EATCount++;
						}

					}
				}
			}
			return enSE_OK;
		}

	}
}