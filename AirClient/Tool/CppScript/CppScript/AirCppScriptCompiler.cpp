#include "AirCppScriptCompiler.h"
#include <Windows.h>
#include "AirCppScriptParse.h"
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
			m_mapWordType["#"]			=	MakeType(enWT_PreDeclare,	0,					0,0);
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
			m_mapWordType["void"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Void,		enBOT_Void,0);
			m_mapWordType["bool"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Bool,		enBOT_Bool,0);
			m_mapWordType["char"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Char,		enBOT_S8,0);
			m_mapWordType["short"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Short,		enBOT_S16,0);
			m_mapWordType["int"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Int,			enBOT_S32,0);
			m_mapWordType["long"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Long,		enBOT_S32,0);
			m_mapWordType["__int64"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Int64,		enBOT_S64,0);
			m_mapWordType["unsigned"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Unsigned,	0,0);
			m_mapWordType["true"]		=	MakeType(enWT_CppKeyWord,	enCKWT_True,		0,0);
			m_mapWordType["false"]		=	MakeType(enWT_CppKeyWord,	enCKWT_False,		0,0);
			m_mapWordType["NULL"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Null,		0,0);
			m_mapWordType["public"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Public,		0,0);
			m_mapWordType["protected"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Protected,	0,0);
			m_mapWordType["private"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Private,		0,0);
			m_mapWordType["comment"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Comment,		0,0);
			m_mapWordType["lib"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Lib,			0,0);
			m_mapWordType["push"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Push,		0,0);
			m_mapWordType["pop"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Pop,			0,0);
			m_mapWordType["message"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Message,		0,0);


			m_mapWordType["+"]	=	MakeType(enWT_Operator,	enOT_Add,				0,0);
			m_mapWordType["-"]	=	MakeType(enWT_Operator,	enOT_Sub,				0,0);
			m_mapWordType["*"]	=	MakeType(enWT_Operator,	enOT_Mul,				0,0);
			m_mapWordType["/"]	=	MakeType(enWT_Operator,	enOT_Div,				0,0);
			m_mapWordType["%"]	=	MakeType(enWT_Operator,	enOT_Remain,			0,0);
			m_mapWordType["="]	=	MakeType(enWT_Operator,	enOT_Mov,				0,0);
			m_mapWordType["&"]	=	MakeType(enWT_Operator,	enOT_And,				0,0);
			m_mapWordType["|"]	=	MakeType(enWT_Operator,	enOT_Or,				0,0);
			m_mapWordType["^"]	=	MakeType(enWT_Operator,	enOT_Xor,				0,0);
			m_mapWordType["~"]	=	MakeType(enWT_Operator,	enOT_Not,				0,0);
			m_mapWordType["=="]	=	MakeType(enWT_Operator,	enOT_Equal,				0,0);
			m_mapWordType["!="]	=	MakeType(enWT_Operator,	enOT_NotEqual,			0,0);
			m_mapWordType[">"]	=	MakeType(enWT_Operator,	enOT_Greater,			0,0);
			m_mapWordType["<"]	=	MakeType(enWT_Operator,	enOT_Less,				0,0);
			m_mapWordType[">="]	=	MakeType(enWT_Operator,	enOT_GreaterEqual,		0,0);
			m_mapWordType["<="]	=	MakeType(enWT_Operator,	enOT_LessEqual,			0,0);
			m_mapWordType["++"]	=	MakeType(enWT_Operator,	enOT_Increment,			0,0);
			m_mapWordType["--"]	=	MakeType(enWT_Operator,	enOT_Decrement,			0,0);
			m_mapWordType["+="]	=	MakeType(enWT_Operator,	enOT_AddEqual,			0,0);
			m_mapWordType["-+"]	=	MakeType(enWT_Operator,	enOT_SubEqual,			0,0);
			m_mapWordType["*="]	=	MakeType(enWT_Operator,	enOT_MulEqual,			0,0);
			m_mapWordType["/="]	=	MakeType(enWT_Operator,	enOT_DivEqual,			0,0);
			m_mapWordType["%="]	=	MakeType(enWT_Operator,	enOT_RemainEqual,		0,0);
			m_mapWordType["&="]	=	MakeType(enWT_Operator,	enOT_AndEqual,			0,0);
			m_mapWordType["!="]	=	MakeType(enWT_Operator,	enOT_OrEqual,			0,0);
			m_mapWordType["<<"]	=	MakeType(enWT_Operator,	enOT_LeftShift,			0,0);
			m_mapWordType[">>"]	=	MakeType(enWT_Operator,	enOT_RightShift,		0,0);
			m_mapWordType["["]	=	MakeType(enWT_Operator,	enOT_IndexBegin,		0,0);
			m_mapWordType["]"]	=	MakeType(enWT_Operator,	enOT_IndexEnd,			0,0);
			m_mapWordType[":"]	=	MakeType(enWT_Operator,	enOT_IfElse,			0,0);
			m_mapWordType["?"]	=	MakeType(enWT_Operator,	enOT_Question,			0,0);
			m_mapWordType["&&"]	=	MakeType(enWT_Operator,	enOT_LogicAnd,			0,0);
			m_mapWordType["||"]	=	MakeType(enWT_Operator,	enOT_LogicNot,			0,0);
			m_mapWordType["!"]	=	MakeType(enWT_Operator,	enOT_LogicOr,			0,0);

			m_mapWordType[","]	=	MakeType(enWT_Delimiter,	enWDT_Parameter,		0,0);//	,
			m_mapWordType[";"]	=	MakeType(enWT_Delimiter,	enWDT_Statement,		0,0);//	;
			m_mapWordType["{"]	=	MakeType(enWT_Delimiter,	enWDT_BlockBegin,		0,0);//	{
			m_mapWordType["}"]	=	MakeType(enWT_Delimiter,	enWDT_BlockEnd,			0,0);//	}
			m_mapWordType["("]	=	MakeType(enWT_Delimiter,	enWDT_PrePriority,		0,0);//	(
			m_mapWordType[")"]	=	MakeType(enWT_Delimiter,	enWDT_PostPriority,		0,0);//	)
			m_mapWordType["\\"]	=	MakeType(enWT_Delimiter,	enWDT_Connector,		0,0);//	"\"
			return true;
		}

		bool Compiler::Release()
		{
			return true;
		}

		bool Compiler::Compile( const void* pBuffer,unsigned int uiSize )
		{
			StringVector v;
			if(!StringToWord((U8 *)pBuffer,uiSize,v)){
				return false;
			}
			WordInfoVector	vInfo;
			if(WorldToWordInfo(v,vInfo)	!=	0){
				return false;
			}
			return true;
		}

		bool Compiler::Compile( const wchar_t* pName )
		{
			HANDLE hFile	=	CreateFile(pName,GENERIC_READ,FILE_SHARE_READ |FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL );
			if(hFile==INVALID_HANDLE_VALUE){
				CloseHandle(hFile);
				return false;
			}
			U32 uiSize	=	GetFileSize(hFile,0);
			if(uiSize==0){
				CloseHandle(hFile);
				return	true;
			}
			void* pBuffer =	__Alloc(uiSize);
			if(pBuffer==NULL){
				CloseHandle(hFile);
				return false;
			}
			DWORD	dwReadSize	=	0;
			if(!ReadFile(hFile,pBuffer,uiSize,&dwReadSize,NULL)){
				__Free(pBuffer);
				CloseHandle(hFile);
				return	false;
			}
			CloseHandle(hFile);
			hFile=NULL;

			bool bRet	=	Compile(pBuffer,uiSize);
			__Free(pBuffer);
			return bRet;
		}
		U32	CharArrayToU32(char* p,U32 uiSize){
			if(uiSize>4){
				return 0;
			}
			U32 val=0;
			for(U32 i=0;i<uiSize;i++){
				val|=(p[i])<<(8*i);
			}
			return val;
		}
		Air::U32 Compiler::WorldToWordInfo( StringVector& vecWord,WordInfoVector& vecInfo )
		{
			U32 uiSize	=	vecWord.size();
			vecInfo.reserve(uiSize);
			for(U32 i=0;i<uiSize;i++){
				std::tr1::unordered_map<std::string,U32>::iterator	itr = m_mapWordType.find(vecWord[i]);
				if(itr!=m_mapWordType.end()){
					WordInfo info;
					info.uiType	=	itr->second;
					info.str	=	vecWord[i];
					vecInfo.push_back(info);
				}else{
					WordInfo info;
					info.str	=	vecWord[i];
					if(!info.str.empty()){
						if(info.str[0]=='\''){
							info.uiType	=	MakeType(enWT_Variable,enVT_IntNumber,0,0);
							info.iVal	=	CharArrayToU32(&info.str[1],info.str.size()-2);
							vecInfo.push_back(info);
						}else if(info.str[0]=='\"'){
							info.uiType	=	MakeType(enWT_Variable,enVT_String,0,0);
							AString s;
							s.resize(info.str.size()-2);
							memcpy(&s[0],&info.str[1],info.str.size()-2);
							info.str	=	s;
							vecInfo.push_back(info);
						}else if(IsNumber(info.str)){
							if(i+1 < uiSize){
								if(vecWord[i+1]=="."){
									//info.str+=vecWord[i++];
									if(i+2 < uiSize){
										if(IsFloatEnd(vecWord[i+2])){
											info.str+=vecWord[i+1]+vecWord[i+2];
											i+=2;
											info.uiType	=	MakeType(enWT_Variable,enVT_FloatNumber,0,0);
											info.iVal	=	ToFloat(info.str);
											vecInfo.push_back(info);
											continue;
										}
									}
								}
							}
							info.uiType	=	MakeType(enWT_Variable,enVT_IntNumber,0,0);
							info.iVal	=	ToS32(info.str);
							vecInfo.push_back(info);
						}else if(IsHexNumber(info.str)){
							info.uiType	=	MakeType(enWT_Variable,enVT_IntNumber,0,0);
							info.iVal	=	ToHex(info.str);
							vecInfo.push_back(info);
						}else{
							info.uiType	=	MakeType(enWT_Unknown,0,0,0);
							vecInfo.push_back(info);
						}
					}
				}
			}
			return 0;
		}

		Air::U32 Compiler::WordInfoToSyntaxTree( WordInfoVector& vecInfo )
		{

		}

		Air::U32 WordToType( const char* str )
		{
			return 0;
		}

		Air::U32 MakeType( enumWordType w,U32 main,U32 sub,U32 flag )
		{
			WorldType	type;
			type.eWordtype		=	w;
			type.eKeyword		=	(enumCppKeyWordType)main;
			type.eBaseObj		=	(enumBaseObjectType)sub;
			type.Flag			=	flag;
			return type.uiType;
		}

	}
}