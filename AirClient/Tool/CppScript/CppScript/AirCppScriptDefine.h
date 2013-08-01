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
			enWT_Variable,			//	 123 1.000f 
			enWT_CppKeyWord,		//	class struct virtual int public
			enWDT_Operator,			//	+	-	*	/
			enWT_Delimiter,			//	{ } ( ) , ; 
			enWT_Connector,			//	"\"
			
		};
		enum	enumCppKeyWordType{
			enCKWT_Include,		//	#include
			enCKWT_Define,		//	#define
			enCKWT_Typedef,		//	#typedef
			enCKWT_Program,		//	#pragma
			enCKWT_Warning,		//	#warning
			enCKWT_Error,		//	#error
			enCKWT_If,			//	#if
			enCKWT_Else,		//	#else
			enCKWT_ElseIf,		//	#elif
			enCKWT_EndIf,		//	#endif
			enCKWT_Ifdef,		//	#ifdef
			enCKWT_Ifndef,		//	#ifndef
			enCKWT_NameSpace,	//	namespace
			enCKWT_Switch,		//	switch
			enCKWT_Case,		//	case
			enCKWT_Break,		//	break
			enCKWT_Default,		//	default
			enCKWT_Continue,	//	continue
			enCKWT_Return,		//	return
			enCKWT_For,			//	for
			enCKWT_While,		//	while
			enCKWT_Do,			//	do
			enCKWT_Goto,		//	goto
			enCKWT_Const,		//	const
			enCKWT_Static,		//	static
			enCKWT_Register,	//	register
			enCKWT_Struct,		//	struct
			enCKWT_Class,		//	class
			enCKWT_Interface,	//	interface
			enCKWT_Virtual,		//	virtual
			enCKWT_Void,		//	void
			enCKWT_Bool,		//	bool
			enCKWT_Char,		//	char
			enCKWT_Short,		//	short
			enCKWT_Int,			//	int
			enCKWT_Long,		//	long
			enCKWT_Int64,		//	_int64
			enCKWT_Unsigned,	//	unsigned
			enCKWT_True,		//	true
			enCKWT_False,		//	false
			enCKWT_Null,		//	NULL
			enCKWT_Public,		//	public
			enCKWT_Protected,	//	protected
			enCKWT_Private,		//	private
			enCKWT_Comment,		//	comment
			enCKWT_Lib,			//	private
			enCKWT_Push,		//	push
			enCKWT_Pop,			//	pop
			enCKWT_Message,		//	message
		};

		enum	enumWordNameType{
			enWNT_ObjTypeDecl,			///<	"struct" "class" "interface"
			enWNT_ObjTypeName,			///<	class "TestClass"
			enWNT_ObjType,				///<	"int"
			enWNT_ObjName,				///<	int "iCount"
			enWNT_PreDecorate,
			enWNT_PostDecorate,
			enWNT_MemberPropertyType,	///<	"public"
			enWNT_PreOperator,			///<	"+	-	*	/	=	!	."
			enWNT_PostOperator,			///<	same with above
			enWNT_StatementEnd,			///<	";"
		};
		enum	enumOperatorType{
			enOT_Add,
			enOT_Sub,
			enOT_Mul,
			enOT_Div,
			enOT_Remain,
			enOT_Mov,
			enOT_And,
			enOT_Or,
			enOT_Xor,
			enOT_Not,
			enOT_Equal,
			enOT_NotEqual,
			enOT_Greater,
			enOT_Less,
			enOT_GreaterEqual,
			enOT_LessEqual,
			enOT_Increment,
			enOT_Decrement,
			enOT_AddEqual,
			enOT_SubEqual,
			enOT_MulEqual,
			enOT_DivEqual,
			enOT_RemainEqual,
			enOT_AndEqual,
			enOT_OrEqual,
			enOT_LeftShift,		//	<<
			enOT_RightShift,	//	>>
			enOT_IndexBegin,	//	[
			enOT_IndexEnd,		//	]
			enOT_IfElse,		//	:
			enOT_Question,		//	?

		};
		enum	enumObjectType{
			enCOT_Void,
			enCOT_Bool,
			enCOT_S8,
			enCOT_S16,
			enCOT_S32,
			enCOT_S64,
			enCOT_U8,
			enCOT_U16,
			enCOT_U32,
			enCOT_U64,
			enCOT_F32,
			enCOT_F64,
			enCOT_Obj,
			enCOT_VirtualObj,
			enCOT_Pointor
		};
		enum	enumUnknownType{
			enUT_Unknown,
			enUT_IntNumber,
			enUT_FloatNumber,
			enUT_String
		};
		enum	enumWordDelamiterType{
			enWDT_Unknown,
			enWDT_Parameter,		//	,
			enWDT_Statement,		//	;
			enWDT_BlockBegin,		//	{
			enWDT_BlockEnd,			//	}
			enWDT_PrePriority,		//	(
			enWDT_PostPriority,		//	)
			enWDT_Connector,		//	"\"
		};
		enum	enumVariableType{
			enVT_Unknown,
			enVT_Constant,
			enVT_Static,
			enVT_VariableName,
		};


	}
}
#endif // AirCppScriptDefine_h__
