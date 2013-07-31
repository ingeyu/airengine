#ifndef AirCppScript_h__
#define AirCppScript_h__

#include "AirCppScriptDefine.h"
#include "AirCppScriptDefineType.h"

namespace	Air{
	namespace	CppScript{
		void*	__Alloc(U32	uiSize);
		void	__Free(void* p);
	}
}

#endif // AirCppScript_h__
