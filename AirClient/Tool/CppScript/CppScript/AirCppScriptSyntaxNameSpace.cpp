#include "AirCppScriptSyntaxNameSpace.h"


namespace	Air{
	namespace	CppScript{

		Air::CppScript::enumSyntaxError NameSpaceNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			if(idx+1>=vecInfo.size())
				return enSE_UnexpectedEnd;
			SetErrorInfo(vecInfo[idx]);
			WordType& t = vecInfo[++idx].eType;

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
			WordInfoVector vTemp;
			enumSyntaxError e =	FindBlock(vecInfo,idx,vTemp,MakeType(enWT_Delimiter,enWDT_PreBrace),MakeType(enWT_Delimiter,enWDT_PostBrace),false);
			if(e!=enSE_OK){
				return	e;
			}
			U32 uiTemp = 0;
			e = Node::Parse(vTemp,uiTemp);
			if(e!=enSE_OK){
				return e;
			}
			idx+=vTemp.size()+2;
			return enSE_OK;
			/*for(;idx<vecInfo.size();){
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
			*/

			return enSE_UnexpectedEnd;
		}
	}
}