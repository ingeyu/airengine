#ifndef AirCppScriptCompiler_h__
#define AirCppScriptCompiler_h__

#include "AirCppScript.h"
#include <unordered_map>
#include <string>

namespace	Air{
	namespace	CppScript{
		class	Node;
		U32		WordToType(const char* str);
		
		class	Compiler{
		public:
			Compiler();
			virtual	~Compiler();

			bool	Initialization();
			bool	Release();
			bool	BuildProj( const wchar_t* pName);
			bool	Compile(const wchar_t* pName);
			bool	Link(const wchar_t* pName,U32	uiLinkFlag	=	0);
		protected:
			bool	Compile(const void* pBuffer,unsigned int uiSize);
			U32		WordToWordInfo(StringVector& vecWord,PosVector& vLine,WordInfoVector& vecInfo);
			U32		WordInfoToSyntaxTree(WordInfoVector& vecInfo);

			
		protected:
			std::tr1::unordered_map<std::string,U32>	m_mapWordType;
			Node*										m_pSyntaxTree;
		};
	}
}
#endif // AirCppScriptCompiler_h__
