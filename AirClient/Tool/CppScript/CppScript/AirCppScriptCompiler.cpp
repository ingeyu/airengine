#include "AirCppScriptCompiler.h"
#include <Windows.h>
#include "AirCppScriptParse.h"
#include "AirCppScriptSyntax.h"
#include "AirCppScriptAssemble.h"
#include "AirCppScriptFunction.h"
#include "AirCppScriptSyntaxFunction.h"
namespace	Air{
	namespace	CppScript{


		Compiler::Compiler()
		{
			m_pSyntaxTree	=	NULL;
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
			m_mapWordType["float"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Float,		enBOT_F32,0);
			m_mapWordType["double"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Double,		enBOT_F64,0);
			m_mapWordType["unsigned"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Unsigned,	0,0);
			m_mapWordType["true"]		=	MakeType(enWT_CppKeyWord,	enCKWT_True,		0,0);
			m_mapWordType["false"]		=	MakeType(enWT_CppKeyWord,	enCKWT_False,		0,0);
			m_mapWordType["NULL"]		=	MakeType(enWT_Constant,		enCKWT_Null,		0,0);
			m_mapWordType["public"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Public,		0,0);
			m_mapWordType["protected"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Protected,	0,0);
			m_mapWordType["private"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Private,		0,0);
			m_mapWordType["comment"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Comment,		0,0);
			m_mapWordType["lib"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Lib,			0,0);
			m_mapWordType["push"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Push,		0,0);
			m_mapWordType["pop"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Pop,			0,0);
			m_mapWordType["message"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Message,		0,0);
			m_mapWordType["operator"]	=	MakeType(enWT_CppKeyWord,	enCKWT_Operator,	0,0);
			m_mapWordType["new"]		=	MakeType(enWT_CppKeyWord,	enCKWT_New,			0,0);
			m_mapWordType["delete"]		=	MakeType(enWT_CppKeyWord,	enCKWT_Delete,		0,0);
			m_mapWordType["__declspec"]	=	MakeType(enWT_CppKeyWord,	enCKWT___declspec,	0,0);
			m_mapWordType["dllexport"]	=	MakeType(enWT_CppKeyWord,	enCKWT_dllexport,	0,0);
			m_mapWordType["dllimport"]	=	MakeType(enWT_CppKeyWord,	enCKWT_dllimport,	0,0);
			m_mapWordType["__cdecl"]	=	MakeType(enWT_CppKeyWord,	enCKWT___cdecl,		0,0);
			m_mapWordType["__fastcall"]	=	MakeType(enWT_CppKeyWord,	enCKWT___fastcall,	0,0);
			m_mapWordType["__stdcall"]	=	MakeType(enWT_CppKeyWord,	enCKWT___stdcall,	0,0);
			m_mapWordType["__thiscall"]	=	MakeType(enWT_CppKeyWord,	enCKWT___thiscall,	0,0);

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
			m_mapWordType["-="]	=	MakeType(enWT_Operator,	enOT_SubEqual,			0,0);
			m_mapWordType["*="]	=	MakeType(enWT_Operator,	enOT_MulEqual,			0,0);
			m_mapWordType["/="]	=	MakeType(enWT_Operator,	enOT_DivEqual,			0,0);
			m_mapWordType["%="]	=	MakeType(enWT_Operator,	enOT_RemainEqual,		0,0);
			m_mapWordType["&="]	=	MakeType(enWT_Operator,	enOT_AndEqual,			0,0);
			m_mapWordType["!="]	=	MakeType(enWT_Operator,	enOT_OrEqual,			0,0);
			m_mapWordType["<<"]	=	MakeType(enWT_Operator,	enOT_LeftShift,			0,0);
			m_mapWordType[">>"]	=	MakeType(enWT_Operator,	enOT_RightShift,		0,0);
			m_mapWordType["["]	=	MakeType(enWT_Operator,	enOT_SquareBracketBegin,		0,0);
			m_mapWordType["]"]	=	MakeType(enWT_Operator,	enOT_SquareBracketEnd,			0,0);
			m_mapWordType[":"]	=	MakeType(enWT_Operator,	enOT_Colon,				0,0);
			m_mapWordType["?"]	=	MakeType(enWT_Operator,	enOT_Question,			0,0);
			m_mapWordType["&&"]	=	MakeType(enWT_Operator,	enOT_LogicAnd,			0,0);
			m_mapWordType["||"]	=	MakeType(enWT_Operator,	enOT_LogicNot,			0,0);
			m_mapWordType["!"]	=	MakeType(enWT_Operator,	enOT_LogicOr,			0,0);
			m_mapWordType["->"]	=	MakeType(enWT_Operator,	enOT_PointorMember,		0,0);

			m_mapWordType[","]	=	MakeType(enWT_Delimiter,	enWDT_Comma,			0,0);//	,
			m_mapWordType[";"]	=	MakeType(enWT_Delimiter,	enWDT_Semicolon,		0,0);//	;
			m_mapWordType["{"]	=	MakeType(enWT_Delimiter,	enWDT_PreBrace,			0,0);//	{
			m_mapWordType["}"]	=	MakeType(enWT_Delimiter,	enWDT_PostBrace,		0,0);//	}
			m_mapWordType["("]	=	MakeType(enWT_Delimiter,	enWDT_PreBracket,		0,0);//	(
			m_mapWordType[")"]	=	MakeType(enWT_Delimiter,	enWDT_PostBracket,		0,0);//	)
			m_mapWordType["\\"]	=	MakeType(enWT_Delimiter,	enWDT_Back_Slant ,		0,0);//	"\"
			m_mapWordType["."]	=	MakeType(enWT_Delimiter,	enWDT_Period,			0,0);//	)
			return true;
		}

		bool Compiler::Release()
		{
			return true;
		}

		bool Compiler::Compile( const void* pBuffer,unsigned int uiSize )
		{
			StringVector v;
			PosVector	vLine;
			if(!ParseWord((U8 *)pBuffer,uiSize,v,vLine)){
				return false;
			}
			WordInfoVector	vInfo;
			if(WordToWordInfo(v,vLine,vInfo)	!=	0){
				return false;
			}
			if(m_pSyntaxTree==NULL)
				m_pSyntaxTree = new Node();
			U32 idx =0;
			enumSyntaxError	e	= m_pSyntaxTree->Parse(vInfo,idx);
			if(e!=enSE_OK){
				Pos pos;
				if(idx<vInfo.size()){
					pos	=	vInfo[idx].pos;
				}
				printf("error(%d) file_pos(%d,%d)\n",e,pos.uiLine,pos.uiColumn);
				return false;
			}
#ifdef _DEBUG
			m_pSyntaxTree->Print("|-|");
#endif
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
			wprintf(L"Compile %s\n",pName);
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
		Air::U32 Compiler::WordToWordInfo( StringVector& vecWord,PosVector& vLine,WordInfoVector& vecInfo )
		{
			U32 uiSize	=	vecWord.size();
			vecInfo.reserve(uiSize);
			for(U32 i=0;i<uiSize;i++){
				std::tr1::unordered_map<std::string,U32>::iterator	itr = m_mapWordType.find(vecWord[i]);
				if(itr!=m_mapWordType.end()){
					WordInfo info;
					info.eType.uiType	=	itr->second;
					info.str	=	vecWord[i];
					info.pos	=	vLine[i];
					vecInfo.push_back(info);
				}else{
					WordInfo info;
					info.str	=	vecWord[i];
					info.pos	=	vLine[i];
					if(!info.str.empty()){
						if(info.str[0]=='\''){
							info.eType.uiType	=	MakeType(enWT_Constant,enVT_IntNumber,0,0);
							info.iVal	=	CharArrayToU32(&info.str[1],info.str.size()-2);
							vecInfo.push_back(info);
						}else if(info.str[0]=='\"'){
							info.eType.uiType	=	MakeType(enWT_Constant,enVT_String,0,0);
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
											info.eType.uiType	=	MakeType(enWT_Constant,enVT_FloatNumber,0,0);
											info.fVal	=	ToFloat(info.str);
											vecInfo.push_back(info);
											continue;
										}
									}
								}
							}
							info.eType.uiType	=	MakeType(enWT_Constant,enVT_IntNumber,0,0);
							info.iVal	=	ToS32(info.str);
							vecInfo.push_back(info);
						}else if(IsHexNumber(info.str)){
							info.eType.uiType	=	MakeType(enWT_Constant,enVT_IntNumber,0,0);
							info.iVal	=	ToHex(info.str);
							vecInfo.push_back(info);
						}else{
							info.eType.uiType	=	MakeType(enWT_Unknown,0,0,0);
							vecInfo.push_back(info);
						}
					}
				}
			}
			return 0;
		}

		Air::U32 Compiler::WordInfoToSyntaxTree( WordInfoVector& vecInfo )
		{
			return 0;
		}

		bool Compiler::CompileProject( const WStringVector& vCppArray,U32 uiCompileFlag/*=0*/ )
		{
			U32 uiSize	=	vCppArray.size();
			for(U32 i=0;i<uiSize;i++){
				if(!Compile(vCppArray[i].c_str())){
					return false;
				};
			}
			return true;
		}

		bool Compiler::Link( const wchar_t* pName,U32 uiLinkFlag /*= 0*/ )
		{
			if(m_pSyntaxTree==NULL)
				return false;
			Assemble asmGen;
			m_pSyntaxTree->GenerateFunctionCode(asmGen);

			AString	strName;
			Disassemble(asmGen.GetBuffer(),asmGen.GetCurrentOffset(),strName);
			printf(strName.c_str());

			FunctionNode* pNode = (FunctionNode*)m_pSyntaxTree->FindNode("main",enNT_Function);

			Function f;
			f.SetFunctionEntry(asmGen.GetBuffer(pNode->pEntry));

			U32 ret=0;
			U32 uiParam[]={101,0};
			f.Call(&ret,(void**)uiParam,2);

			if(m_pSyntaxTree!=NULL){
				delete m_pSyntaxTree;
				m_pSyntaxTree=NULL;
			}
			return true;
		}

		Air::U32 WordToType( const char* str )
		{
			return 0;
		}

		Air::U32 MakeType( enumWordType w,U32 main,U32 sub,U32 flag )
		{
			WordType	type;
			type.eWordtype		=	w;
			type.eKeyword		=	(enumCppKeyWordType)main;
			type.eBaseObj		=	(enumBaseObjectType)sub;
			type.Flag			=	flag;
			return type.uiType;
		}

	}
}