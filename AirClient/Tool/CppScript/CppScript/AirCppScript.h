#ifndef AirCppScript_h__
#define AirCppScript_h__

#include "AirCppScriptDefine.h"
#include "AirCppScriptDefineType.h"

namespace	Air{
	namespace	CppScript{
		void*	__Alloc(U32	uiSize);
		void	__Free(void* p);
		void ToLower(wchar_t* str);
		void ToLower(char* str);
		bool SplitFilePath( const std::wstring& str, std::wstring* strPath = NULL, std::wstring* strFileName = NULL, std::wstring* strExe = NULL );

	}
}

#endif // AirCppScript_h__