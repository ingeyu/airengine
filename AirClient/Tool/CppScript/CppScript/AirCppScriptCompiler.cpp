#include "AirCppScriptCompiler.h"

namespace	Air{
	namespace	CppScript{


		Compiler::Compiler()
		{
			m_pWordBuffer	=	NULL;
			m_pWordInfo		=	NULL;
			m_uiWordCount	=	0;
		}

		Compiler::~Compiler()
		{

		}

		bool Compiler::Initialization()
		{
			m_mapWordType["#"]			=	MakeType(enWT_PreDeclare,0,0,0);
			m_mapWordType["include"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Include,		0,0);
			m_mapWordType["define"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Define,		0,0);
			m_mapWordType["pragma"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Typedef,		0,0);
			m_mapWordType["typedef"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Program,		0,0);
			m_mapWordType["warning"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Warning,		0,0);
			m_mapWordType["error"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Error,		0,0);
			m_mapWordType["if"]			=	MakeType(enWT_CppKeyWord,	enCKWT_If,			0,0);
			m_mapWordType["else"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Else,		0,0);
			m_mapWordType["elif"]		=	MakeType(enWT_CppKeyWord,	enCKWT_ElseIf,		0,0);
			m_mapWordType["endif"]		=	MakeType(enWT_CppKeyWord,	enCKWT_EndIf,		0,0);
			m_mapWordType["ifdef"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Ifdef,		0,0);
			m_mapWordType["ifndef"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Ifndef,		0,0);
			m_mapWordType["namespace"]	=	MakeType(enWT_CppKeyWord,	enCKWT_NameSpace,	0,0);
			m_mapWordType["switch"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Switch,		0,0);
			m_mapWordType["case"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Case,		0,0);
			m_mapWordType["break"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Break,		0,0);
			m_mapWordType["default"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Default,		0,0);
			m_mapWordType["continue"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Continue,	0,0);
			m_mapWordType["return"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Return,		0,0);
			m_mapWordType["for"]		=	MakeType(enWT_CppKeyWord,	enCKWT_For,			0,0);
			m_mapWordType["while"]		=	MakeType(enWT_CppKeyWord,	enCKWT_While,		0,0);
			m_mapWordType["do"]			=	MakeType(enWT_CppKeyWord,	enCKWT_Do,			0,0);
			m_mapWordType["goto"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Goto,		0,0);
			m_mapWordType["const"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Const,		0,0);
			m_mapWordType["static"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Static,		0,0);
			m_mapWordType["register"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Register,	0,0);
			m_mapWordType["struct"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Struct,		0,0);
			m_mapWordType["class"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Class,		0,0);
			m_mapWordType["interface"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Interface,	0,0);
			m_mapWordType["virtual"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Virtual,		0,0);
			m_mapWordType["void"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Void,		0,0);
			m_mapWordType["bool"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Bool,		0,0);
			m_mapWordType["char"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Char,		0,0);
			m_mapWordType["short"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Short,		0,0);
			m_mapWordType["int"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Int,			0,0);
			m_mapWordType["long"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Long,		0,0);
			m_mapWordType["__int64"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Int64,		0,0);
			m_mapWordType["unsigned"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Unsigned,	0,0);
			m_mapWordType["true"]		=	MakeType(enWT_CppKeyWord,	enCKWT_True,		0,0);
			m_mapWordType["false"]		=	MakeType(enWT_CppKeyWord,	enCKWT_False,		0,0);
			m_mapWordType["NULL"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Null,		0,0);
			m_mapWordType["public"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Public,		0,0);
			m_mapWordType["protected"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Protected,	0,0);
			m_mapWordType["private"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Private,		0,0);



			return true;
		}

		bool Compiler::Release()
		{
			return true;
		}

		bool Compiler::Compile( const void* pBuffer,unsigned int uiSize )
		{

			return true;
		}

		bool Compiler::Compile( const char* pName )
		{
			return true;
		}

		Air::CppScript::U32 WordToType( const char* str )
		{

		}

		Air::CppScript::U32 MakeType( enumWordType w,U32 main,U32 sub,U32 flag )
		{
			WorldType	type;
			type.wordtype	=	w;
			type.main		=	main;
			type.sub		=	sub;
			type.flag		=	flag;
		}

	}
}