#include "AirCppScript.h"
#include <malloc.h>

namespace	Air{
	namespace	CppScript{


		void* __Alloc( U32 uiSize )
		{
			return malloc(uiSize);
		}

		void __Free( void* p )
		{
			return free(p);
		}

	}

}