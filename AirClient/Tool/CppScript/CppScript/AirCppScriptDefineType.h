#ifndef AirCppScriptDefineType_h__
#define AirCppScriptDefineType_h__

#include "AirCppScriptDefine.h"

namespace	Air{
	namespace	CppScript{
		
		union WorldType{
			struct{
				unsigned char				wordtype			:	8;
				unsigned char				main				:	8;
				unsigned char				sub					:	8;
				unsigned char				Variable			:	6;
				unsigned char				PreFlag				:	1;
				unsigned char				PostFlag			:	1;
			};
			U32	uiType;
			
		};
		struct WordInfo{
			union{
				WorldType				eType;
				unsigned long			uiType;
			};
			unsigned long				line;
			unsigned long				file;
		};
	}
}
#endif // AirCppScriptDefineType_h__
