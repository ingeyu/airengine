#ifndef AirCppScriptFunction_h__
#define AirCppScriptFunction_h__

#include "AirCppScriptDefineType.h"

namespace	Air{
	namespace	CppScript{
		enum	enumCallError{
			enCE_OK,
			enCE_ParameterCount_Not_Match,
			enCE_Need_Return_Value,
			enCE_Function_Address_InValid,
			enCE_Unknown_Error,
		};
		class	Function{
		public:
			Function();
			U32				GetParameterCount();
			U1				HasReturnValue();
			enumCallError	Call(void* pRetValue=NULL,void** ppParameter=NULL,U32 uiCount=0);
			void			SetFunctionEntry(void*	p);
			void*			GetFunctionEntry();
		protected:
			AString	strName;
			void*	pFunction;
		};
	}
}
#endif // AirCppScriptFunction_h__
