#include "AirCppScriptSyntaxObject.h"
#include "AirCppScriptSyntaxVariable.h"
#include "AirCppScriptSyntaxFunction.h"
#include "AirCppScriptAssemble.h"
namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError ObjectNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	 = vecInfo.size();
			if(idx+1 > uiSize)
				return enSE_UnexpectedEnd;
			SetErrorInfo(vecInfo[idx]);
			WordType tObjType	=	vecInfo[++idx].eType;
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
				if(tObjType.eWordtype	==	enWT_CppKeyWord){
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
				idx++;
				tObjType	=	vecInfo[idx].eType;
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
				}else if(tObjType.eWordtype	==	enWT_Delimiter	&&	tObjType.eKeyword	==	enWDT_Semicolon){
					idx++;
					continue;
				}

			
				if(tObjType.uiType	==	MakeType(enWT_Unknown,enCKWT_Unknown)){
					Node* pObj	=	FindNode(vecInfo[idx].str);
					if(pObj==NULL){
						//if its a DisConstruct Function
						if(vecInfo[idx].str	==	AString("~")+GetName()){
							e = __ParseNode<FunctionNode>(vecInfo,idx);
							if(e!=enSE_OK){
								return e;
							}else{
								continue;
							}
						}
						return enSE_Unrecognized_Class_Or_Struct_Word;
					}
					if(pObj->GetType()!=enNT_Object){
						return enSE_Unrecognized_Class_Or_Struct_Word;
					}
					e = __ParseNode<VariableNode>(vecInfo,idx);
					if(e!=enSE_OK){
						Node* pFunc	=	NULL;
						e = __ParseNode<FunctionNode>(vecInfo,idx,&pFunc);
						AddVirtualFunction((FunctionNode*)pFunc);
					}
					continue;
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
				case enCKWT_Virtual:
				case enOT_Not:{
					Node* pFunc	=	NULL;
					e = __ParseNode<FunctionNode>(vecInfo,idx,&pFunc);
					AddVirtualFunction((FunctionNode*)pFunc);
					if(e!=enSE_OK)
						return e;
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
						if(e!=enSE_OK){
							Node* pFunc	=	NULL;
							e = __ParseNode<FunctionNode>(vecInfo,idx,&pFunc);
							AddVirtualFunction((FunctionNode*)pFunc);
						}
						
					}break;
				default:{
					Node* pFunc	=	NULL;
					e = __ParseNode<FunctionNode>(vecInfo,idx,&pFunc);
					AddVirtualFunction((FunctionNode*)pFunc);
					if(e!=enSE_OK){
						return e;
					}
						}break;
				}
			}
			return enSE_UnexpectedEnd;
		}

		Air::U32 ObjectNode::GetObjectSize()
		{
			//if(m_pInherit!=NULL){
			//	return m_uiObjSize+m_pInherit->GetObjectSize();
			//}
			return m_uiObjSize;
		}

		Air::U32 ObjectNode::GetVirtualFunctionCount()
		{
			if(m_pInherit!=NULL){
				return m_pInherit->GetVirtualFunctionCount()+m_uiVirtualCount;
			}
			return m_uiVirtualCount;
		}

		void ObjectNode::AddVirtualFunction( FunctionNode* p )
		{
			if(p==NULL)
				return;
			if(!p->IsVartual())
				return;
			m_vecVirtualFunction.push_back(p);

			if(m_pInherit!=NULL){
				Node* pNode = m_pInherit->FindNodeDown(p->GetName(),enNT_Function,false);
				if(pNode!=NULL){
					if(((FunctionNode*)pNode)->IsVartual()){
						p->m_uiVirtualIndex	=	((FunctionNode*)pNode)->GetVirtualIndex();
						return;
					}
				}
			}
			m_uiVirtualCount++;
			p->m_uiVirtualIndex	=	GetVirtualFunctionCount()-1;
		}

		Air::CppScript::enumSyntaxError ObjectNode::GenerateCode( Assemble& asmGen )
		{
			if(m_pInherit!=NULL){
				m_uiObjSize	=	((ObjectNode*)m_bInherit)->GetObjectSize();
			}
			if(GetVirtualFunctionCount()>0){
				if(m_pInherit!=0&&((ObjectNode*)m_pInherit)->GetVirtualFunctionCount()==0){
					m_uiObjSize+=4;
				}else if(m_pInherit==NULL){
					m_uiObjSize+=4;
				}
			}
			//Calc Member Offset
			NodeList::iterator	i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Variable){
						VariableNode* pVar = (VariableNode*)pNode;
						pVar->m_uiOffset	=	m_uiObjSize;
						m_uiObjSize	+=pVar->GetSize();
					}
				}
			}
			
			
			i	=	m_lstChild.begin();
			for(;i!=m_lstChild.end();i++){
				Node* pNode	=	(*i);
				if(pNode!=NULL){
					if(pNode->GetType()==enNT_Function){
						pNode->GenerateCode(asmGen);
					}
				}
			}
			//Build Virtual Function Table
			U32* pVFT	=	GetVFTPtr(asmGen);
			if(m_pInherit!=NULL&&((ObjectNode*)m_pInherit)->GetVirtualFunctionCount()>0){
				memcpy(pVFT,((ObjectNode*)m_pInherit)->GetVFTPtr(asmGen),sizeof(U32)*((ObjectNode*)m_pInherit)->GetVirtualFunctionCount());
			}
			
			for(U32 idx=0;idx!=m_vecVirtualFunction.size();idx++){
				FunctionNode* pNode	=	m_vecVirtualFunction[idx];
				pVFT[pNode->GetVirtualIndex()]	=	pNode->GetEntry();
			}
			

			return enSE_OK;
			return enSE_OK;
		}

		Node* ObjectNode::FindNode( CAString& strName,enumNodeType type /*= enNT_Unknown*/,U1 bFindParent /*= true*/ )
		{
			Node* pNode = NULL;
			if(m_pInherit!=NULL){
				pNode	=	m_pInherit->FindNode(strName,type,false);
			}
			if(pNode==NULL){
				pNode	=	__super::FindNode(strName,type,bFindParent);
			}
			return pNode;
		}

		Node* ObjectNode::FindNodeDown( CAString& strName,enumNodeType type /*= enNT_Unknown*/,U1 bFindChild /*= true*/ )
		{
			Node* pNode = NULL;
			if(m_pInherit!=NULL){
				pNode	=	m_pInherit->FindNodeDown(strName,type,false);
			}
			if(pNode==NULL){
				pNode	=	__super::FindNodeDown(strName,type,bFindChild);
			}
			return pNode;
		}

		U32* ObjectNode::GetVFTPtr(Assemble& asmGen)
		{
			return (U32*)asmGen.GetBuffer(m_uiVFTOffset);
		}

		void ObjectNode::AllocVFT( Assemble& asmGen )
		{
			U32 uiVFTCount	=	GetVirtualFunctionCount();
			if(uiVFTCount==0){
				return ;
			}
			m_uiVFTOffset	=	asmGen.AddOffset(uiVFTCount*sizeof(U32));
		}

		Air::U32 ObjectNode::GetVFTOffset()
		{
			return m_uiVFTOffset;
		}

		FunctionNode* ObjectNode::GetConstructFunction()
		{
			FunctionNode* p	=	(FunctionNode*)FindNode(GetName(),enNT_Function,false);
			if(p->IsConstructFunction())
			{
				return p;
			}
			return NULL;
		}

		FunctionNode* ObjectNode::GetDisConstructFunction()
		{
			FunctionNode* p	=	(FunctionNode*)FindNode(AString("~")+GetName(),enNT_Function,false);
			if(p->IsDisConstructFunction())
			{
				return p;
			}
			return NULL;
		}

	}
	
}