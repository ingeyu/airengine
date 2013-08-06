#ifndef AirCppScriptParse_h__
#define AirCppScriptParse_h__

#include "AirCppScriptDefineType.h"

namespace	Air{
	namespace	CppScript{
		U1	IsNumber(const CAString& str );
		U1	IsHexNumber( CAString& str );
		S32 ToS32( const AString& str );
		U32 ToHex( const AString& str );
		U1	IsFloatEnd(const AString& str);
		Real ToFloat( const AString& str );
		U1	StringToWord( U8*	pData,U32	uiSize,StringVector& vecWord);
		
	}
}
#endif // AirCppScriptParse_h__