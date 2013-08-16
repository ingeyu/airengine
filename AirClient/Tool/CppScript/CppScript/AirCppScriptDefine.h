#ifndef AirCppScriptDefine_h__
#define AirCppScriptDefine_h__

#include <string>
#include <vector>
#include <list>

namespace	Air{
	typedef	char				AChar;
	typedef	wchar_t				WChar;
	typedef	bool				U1;
	typedef	unsigned char		U8;
	typedef	unsigned short		U16;
	typedef	unsigned long		U32;
	typedef	unsigned __int64	U64;
	typedef	unsigned int		UInt;
#if 1
	//(FLOAT_BIT == 32)
	typedef	float				Real;
#else
	typedef	double				Real;
#endif

	typedef	float				FLOAT;
	typedef	float				F32;
	typedef	double				F64;
	typedef	char				S8;
	typedef	short				S16;
	typedef	long				S32;
	typedef	__int64				S64;
	typedef	int					SInt;
	typedef std::string			AString;
	typedef const AString			CAString;
	typedef std::vector<AString>	StringVector;
	typedef std::list<AString>		StringList;
	namespace	CppScript{
		
		enum	enumWordType{
			enWT_Unknown,
			enWT_PreDeclare,		//	#
			enWT_Constant,			//	 123 1.000f 
			enWT_CppKeyWord,		//	class struct virtual int public
			enWT_Operator,			//	+	-	*	/
			enWT_Delimiter,			//	{ } ( ) , ; 
			enWT_Connector,			//	"\"
			
		};
		enum	enumCppKeyWordType{
			enCKWT_Unknown,		///<	未知
			enCKWT_Include,		///<	#include
			enCKWT_Define,		///<	#define
			enCKWT_Typedef,		///<	#typedef
			enCKWT_Program,		///<	#pragma
			enCKWT_Warning,		///<	#warning
			enCKWT_Error,		///<	#error
			enCKWT_If,			///<	#if
			enCKWT_Else,		///<	#else
			enCKWT_ElseIf,		///<	#elif
			enCKWT_EndIf,		///<	#endif
			enCKWT_Ifdef,		///<	#ifdef
			enCKWT_Ifndef,		///<	#ifndef
			enCKWT_NameSpace,	///<	namespace
			enCKWT_Switch,		///<	switch
			enCKWT_Case,		///<	case
			enCKWT_Break,		///<	break
			enCKWT_Default,		///<	default
			enCKWT_Continue,	///<	continue
			enCKWT_Return,		///<	return
			enCKWT_For,			///<	for
			enCKWT_While,		///<	while
			enCKWT_Do,			///<	do
			enCKWT_Goto,		///<	goto
			enCKWT_Const,		///<	const
			enCKWT_Static,		///<	static
			enCKWT_Register,	///<	register
			enCKWT_Struct,		///<	struct
			enCKWT_Class,		///<	class
			enCKWT_Interface,	///<	interface
			enCKWT_Virtual,		///<	virtual
			enCKWT_Void,		///<	void
			enCKWT_Bool,		///<	bool
			enCKWT_Char,		///<	char
			enCKWT_Short,		///<	short
			enCKWT_Int,			///<	int
			enCKWT_Long,		///<	long
			enCKWT_Int64,		///<	_int64
			enCKWT_Float,		///<	float
			enCKWT_Double,		///<	double
			enCKWT_Unsigned,	///<	unsigned
			enCKWT_True,		///<	true
			enCKWT_False,		///<	false
			enCKWT_Null,		///<	NULL
			enCKWT_Public,		///<	public
			enCKWT_Protected,	///<	protected
			enCKWT_Private,		///<	private
			enCKWT_Comment,		///<	comment
			enCKWT_Lib,			///<	private
			enCKWT_Push,		///<	push
			enCKWT_Pop,			///<	pop
			enCKWT_Message,		///<	message
			enCKWT_Operator,	///<	operator
			enCKWT_New,			///<	new
			enCKWT_Delete,		///<	delete
			enCKWT___declspec,	///<	__declspec
			enCKWT_dllexport,	///<	dllexport
			enCKWT_dllimport,	///<	dllimport
			enCKWT___cdecl,		///<	__cdecl		调用者恢复堆栈
			enCKWT___fastcall,	///<	__fastcall
			enCKWT___stdcall,	///<	__stdcall	this	指针在esp+4
			enCKWT___thiscall,	///<	__thiscall	this	指针在ECX
			enOT_Add,					///<	+
			enOT_Sub,					///<	-
			enOT_Mul,					///<	*
			enOT_Div,					///<	/
			enOT_Remain,				///<	%
			enOT_Mov,					///<	=
			enOT_And,					///<	&
			enOT_Or,					///<	|
			enOT_Xor,					///<	^
			enOT_Not,					///<	~
			enOT_Equal,					///<	==
			enOT_NotEqual,				///<	!=
			enOT_Greater,				///<	>
			enOT_Less,					///<	<
			enOT_GreaterEqual,			///<	>=
			enOT_LessEqual,				///<	<=
			enOT_Increment,				///<	++
			enOT_Decrement,				///<	--
			enOT_AddEqual,				///<	+=
			enOT_SubEqual,				///<	-=
			enOT_MulEqual,				///<	*/
			enOT_DivEqual,				///<	/=
			enOT_RemainEqual,			///<	%=
			enOT_AndEqual,				///<	&=
			enOT_OrEqual,				///<	|=
			enOT_LeftShift,				///<	<<
			enOT_RightShift,			///<	>>
			enOT_SquareBracketBegin,	///<	[
			enOT_SquareBracketEnd,		///<	]
			enOT_Colon,					///<	:
			enOT_Question,				///<	?
			enOT_LogicAnd,				///<	&&
			enOT_LogicOr,				///<	||
			enOT_LogicNot,				///<	!
			enOT_PointorMember,			///<	->
			enOT_Domain,				///<	::
			enWDT_Comma,			///<	,	逗号
			enWDT_Semicolon,		///<	;	分号
			enWDT_PreBrace,			///<	{	大括号 前缀
			enWDT_PostBrace,		///<	}	大括号	后缀
			enWDT_PreBracket,		///<	(	括号 前缀
			enWDT_PostBracket,		///<	)	后缀
			enWDT_Back_Slant ,		///<	"\"反斜杠
			enWDT_Period,			///<	.	句号
			enVT_IntNumber,			///<	整数
			enVT_FloatNumber,		///<	浮点数
			enVT_String,			///<	字符串
			enVT_Static,
			enVT_VariableName,	
		};
		enum	enumBaseObjectType{
			enBOT_Unknown,
			enBOT_Void,
			enBOT_Bool,
			enBOT_S8,
			enBOT_S16,
			enBOT_S32,
			enBOT_S64,
			enBOT_U8,
			enBOT_U16,
			enBOT_U32,
			enBOT_U64,
			enBOT_F32,
			enBOT_F64,
			enBOT_Obj,
			enBOT_VirtualObj,
			enBOT_Pointor
		};

	}
}
#endif // AirCppScriptDefine_h__
