#ifndef AirCppScriptDefineType_h__
#define AirCppScriptDefineType_h__

#include "AirCppScriptDefine.h"

namespace	Air{
	namespace	CppScript{
		
		union WorldType{
			struct{
				enumWordType				eWordtype			:	8;
				//union{
					enumCppKeyWordType		eKeyword			:	8;
				//	enumOperatorType		eOperator			:	8;
				//	enumWordDelamiterType	eDelamiter			:	8;
				//};
				//union{
					enumBaseObjectType		eBaseObj			:	8;
				//	enumVariableType		eVariable			:	8;
				//};
				unsigned int				Flag				:	8;

			};
			U32	uiType;
			
		};
		struct WordInfo{
			WordInfo(){
				uiType	=	0;
				iVal	=	0;
				line	=	0;
				file	=	0;
			};
			union{
				WorldType				eType;
				unsigned long			uiType;
			};
			union{
				U32		iVal;
				float	fVal;
			};
			AString						str;
			unsigned long				line;
			unsigned long				file;
		};
		typedef std::vector<WordInfo>	WordInfoVector;
	}
}
#endif // AirCppScriptDefineType_h__
