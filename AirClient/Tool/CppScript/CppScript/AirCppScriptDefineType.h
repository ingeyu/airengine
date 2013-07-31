#ifndef AirCppScriptDefineType_h__
#define AirCppScriptDefineType_h__

namespace	Air{
	namespace	CppScript{
		struct WorldType{
			U32				wordtype	:	8;
			U32				main		:	8;
			U32				sub			:	8;
			U32				flag		:	8;
		};
		struct WordInfo{
			union{
				WorldType	eType;
				U32			uiType;
			};
			U32				line;
			U32				file;
		};
	}
}
#endif // AirCppScriptDefineType_h__
