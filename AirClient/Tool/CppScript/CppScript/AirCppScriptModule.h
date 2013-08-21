#ifndef AirCppScriptModule_h__
#define AirCppScriptModule_h__

#include "AirCppScriptSyntaxNode.h"

namespace	Air{
	namespace	CppScript{
		class	Function;

		class	Module{
		public:

			Function*	FindFunction(const char* strFunctionName);
			
		};
	}
}
#endif // AirCppScriptModule_h__