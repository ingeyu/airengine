#include "AirCppScriptSyntaxObject.h"
#include "AirCppScriptSyntaxVariable.h"
#include "AirCppScriptSyntaxFunction.h"
namespace	Air{
	namespace	CppScript{


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