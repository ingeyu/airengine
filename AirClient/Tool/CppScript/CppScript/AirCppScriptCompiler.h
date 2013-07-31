#ifndef AirCppScriptCompiler_h__
#define AirCppScriptCompiler_h__

#include "AirCppScript.h"
#include <unordered_map>

namespace	Air{
	namespace	CppScript{
		U32		WordToType(const char* str);
		U32		MakeType(enumWordType w,U32 main,U32 sub,U32 flag);
		class	Compiler{
		public:
			Compiler();
			virtual	~Compiler();

			bool	Initialization();
			bool	Release();

			bool	Compile(const void* pBuffer,unsigned int uiSize);
			bool	Compile(const char* pName);
		protected:
			void	AllocWordInfo();
			void	FreeWordInfo();
		protected:
			AChar*		m_pWordBuffer;
			WordInfo*	m_pWordInfo;
			U32			m_uiWordCount;
			std::tr1::unordered_map<std::string,U32>	m_mapWordType;

		};
	}
}
#endif // AirCppScriptCompiler_h__
