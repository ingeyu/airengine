#ifndef AirCppScriptDefineType_h__
#define AirCppScriptDefineType_h__

#include "AirCppScriptDefine.h"

namespace	Air{
	namespace	CppScript{
		
		union WordType{
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
				WordType				eType;
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
		struct ObjectType{
			ObjectType(){
				iSize		=	4;
				t			=	enBOT_S32;
				bConst		=	0;
				bStatic		=	0;
				bUnsign		=	0;
				bPointor	=	0;
				bpp			=	0;
				bRef		=	0;
				bVirtual	=	0;
				bFloat		=	0;
				bConstruct	=	0;
				bDestruct	=	0;
			};
			U32					iSize		:	16;
			enumBaseObjectType	t			:	6;
			U32					bStatic		:	1;
			U32					bConst		:	1;
			U32					bUnsign		:	1;
			U32					bPointor	:	1;
			U32					bpp			:	1;	//Pointor To Pointor
			U32					bRef		:	1;
			U32					bVirtual	:	1;
			U32					bFloat		:	1;
			U32					bConstruct	:	1;
			U32					bDestruct	:	1;
		};
		U32		MakeType(enumWordType w,U32 main,U32 sub=0,U32 flag=0);
	}
}
#endif // AirCppScriptDefineType_h__
