#include "AirCppScriptSyntax.h"
#include <Windows.h>

namespace	Air{
	namespace	CppScript{


		void Print( const char* str )
		{
			OutputDebugStringA(str);
			OutputDebugStringA("\n");
		}









	}
}