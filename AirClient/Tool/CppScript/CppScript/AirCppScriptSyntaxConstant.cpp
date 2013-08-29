#include "AirCppScriptSyntaxConstant.h"
#include <Windows.h>

namespace	Air{
	namespace	CppScript{


		Air::CppScript::enumSyntaxError ConstantNode::Parse( WordInfoVector& vecInfo,U32& idx )
		{
			U32 uiSize	=	vecInfo.size();
			if(idx>=uiSize)
				return enSE_UnexpectedEnd;
			SetErrorInfo(vecInfo[idx]);

			ConstInfo	=	vecInfo[idx];
			m_strName	=	ConstInfo.str;
			if(ConstInfo.eType.eWordtype==enWT_Constant){
				idx++;
				return enSE_OK;
			}
			return enSE_UnexpectedEnd;
		}

	}
}