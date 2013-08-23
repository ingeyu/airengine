#include "AirCppScriptAssemble.h"
#include "Disassemable/udis86.h"
#include "AirCppScript.h"
#include <Windows.h>
namespace	Air{
	namespace	CppScript{
		Instruction Code[257]={
			{eO_AAA		,1,false,	0,0X37},
			{eO_AAD		,2,true,	0,0XD5,0X00},
			{eO_AAM		,2,true,	0,0XD4,0X00},
			{eO_AAS		,1,false,	0,0X3F},
			{eO_ADC		,2,true,	0,0X12},
			{eO_ADD		,2,true,	0,0},
			{eO_AND		,2,true,	0,0},
			{eO_ARPL 		,2,true,	0,0x63,0}	,
			{eO_BOUND 	,2,true,	0,0x62,0}		,
			{eO_BSF 		,3,true,	0,0x0F,0xBC,0}	,//3~4	0000111110111100oorrrmmm	Bit Scan Forward 
			{eO_BSR 		,3,true,	0,0x0F,0xBD,0}	,//3~4
			{eO_BSWAP 	,2,true,	0,0x0F,0xC8}		,
			{eO_BT 		,4,true,	0,0x0F,0XBA,0X20}	,//0x0F,0XA3,0X00
			{eO_BTC 		,1,true,	0,0x0,0}	,
			{eO_BTR 		,1,true,	0,0x0,0}	,
			{eO_BTS 		,1,true,	0,0x0,0}	,
			{eO_CBW 		,1,true,	0,0x0,0}	,
			{eO_CDQ 		,1,true,	0,0x0,0}	,
			{eO_CLC 		,1,true,	0,0x0,0}	,
			{eO_CLD 		,1,true,	0,0x0,0}	,
			{eO_CLI 		,1,true,	0,0x0,0}	,
			{eO_CLTS 		,1,true,	0,0x0,0}	,
			{eO_CMC 		,1,false,	0,0xF5,0}	,
			{eO_CMOVcc 	,1,true,	0,0x0,0}	,
			{eO_CMP 		,1,true,	0,0x0,0}	,
			{eO_CMPSB 	,1,true,	0,0x0,0}		,
			{eO_CMPSW 	,1,true,	0,0x0,0}		,
			{eO_CMPSD 	,1,true,	0,0x0,0}		,
			{eO_CMPXCHG 	,1,true,	0,0x0,0}	,
			{eO_CMPXCHG8B ,1,true,	0,0x0,0}		,
			{eO_CPUID 	,1,true,	0,0x0,0}		,
			{eO_CWD 		,1,true,	0,0x0,0}	,
			{eO_CWDE 		,1,true,	0,0x0,0}	,
			{eO_DAA 		,1,true,	0,0x0,0}	,
			{eO_DAS 		,1,true,	0,0x0,0}	,
			{eO_DEC 		,1,true,	0,0x0,0}	,
			{eO_DIV 		,1,true,	0,0x0,0}	,
			{eO_ENTER 	,1,true,	0,0x0,0}		,
			{eO_HLT 		,1,true,	0,0x0,0}	,
			{eO_IDIV 		,1,true,	0,0x0,0}	,
			{eO_IMUL 		,1,true,	0,0x0,0}	,
			{eO_IN 		,1,true,	0,0x0,0}	,
			{eO_INC 		,1,true,	0,0x0,0}	,
			{eO_INSB 		,1,true,	0,0x0,0}	,
			{eO_INSW 		,1,true,	0,0x0,0}	,
			{eO_INSD 		,1,true,	0,0x0,0}	,
			{eO_INT 		,1,true,	0,0x0,0}	,
			{eO_INTO 		,1,true,	0,0x0,0}	,
			{eO_INVD 		,1,true,	0,0x0,0}	,
			{eO_INVLPG 	,1,true,	0,0x0,0}	,
			{eO_IRET 		,1,true,	0,0x0,0}	,
			{eO_IRETD 	,1,true,	0,0x0,0}		,
			{eO_LAHF 		,1,true,	0,0x0,0}	,
			{eO_LAR 		,1,true,	0,0x0,0}	,
			{eO_LDS 		,1,true,	0,0x0,0}	,
			{eO_LES 		,1,true,	0,0x0,0}	,
			{eO_LFS 		,1,true,	0,0x0,0}	,
			{eO_LGS 		,1,true,	0,0x0,0}	,
			{eO_LSS 		,1,true,	0,0x0,0}	,
			{eO_LEA 		,1,true,	0,0x0,0}	,
			{eO_LEAVE 	,1,true,	0,0x0,0}		,
			{eO_LGDT 		,1,true,	0,0x0,0}	,
			{eO_LIDT 		,1,true,	0,0x0,0}	,
			{eO_LLDT 		,1,true,	0,0x0,0}	,
			{eO_LMSW 		,1,true,	0,0x0,0}	,
			{eO_LODSB 	,1,true,	0,0x0,0}		,
			{eO_LODSW 	,1,true,	0,0x0,0}		,
			{eO_LODSD 	,1,true,	0,0x0,0}		,
			{eO_LSL 		,1,true,	0,0x0,0}	,
			{eO_LTR 		,1,true,	0,0x0,0}	,
			{eO_MOV 		,1,true,	0,0x0,0}	,
			{eO_MOVSB 	,1,true,	0,0x0,0}		,
			{eO_MOVSW 	,1,true,	0,0x0,0}		,
			{eO_MOVSD 	,1,true,	0,0x0,0}		,
			{eO_MOVSX 	,1,true,	0,0x0,0}		,
			{eO_MOVZX 	,1,true,	0,0x0,0}		,
			{eO_MUL 		,1,true,	0,0x0,0}	,
			{eO_NEG 		,1,true,	0,0x0,0}	,
			{eO_NOP 		,1,true,	0,0x0,0}	,
			{eO_NOT 		,1,true,	0,0x0,0}	,
			{eO_OR 		,1,true,	0,0x0,0}	,
			{eO_OUT 		,1,true,	0,0x0,0}	,
			{eO_OUTSB 	,1,true,	0,0x0,0}		,
			{eO_OUTSW 	,1,true,	0,0x0,0}		,
			{eO_OUTSD 	,1,true,	0,0x0,0}		,
			{eO_POP 		,1,true,	0,0x0,0}	,
			{eO_POPA 		,1,true,	0,0x0,0}	,
			{eO_POPAD 	,1,true,	0,0x0,0}		,
			{eO_POPF 		,1,true,	0,0x0,0}	,
			{eO_POPFD 	,1,true,	0,0x0,0}		,
			{eO_PUSH 		,1,true,	0,0x0,0}	,
			{eO_PUSHW 	,1,true,	0,0x0,0}		,
			{eO_PUSHD 	,1,true,	0,0x0,0}		,
			{eO_PUSHA 	,1,true,	0,0x0,0}		,
			{eO_PUSHAD 	,1,true,	0,0x0,0}	,
			{eO_PUSHF 	,1,true,	0,0x0,0}		,
			{eO_PUSHFD 	,1,true,	0,0x0,0}	,
			{eO_RCL 		,1,true,	0,0x0,0}	,
			{eO_RCR 		,1,true,	0,0x0,0}	,
			{eO_RDMSR 	,1,true,	0,0x0,0}		,
			{eO_RET 		,1,true,	0,0x0,0}	,
			{eO_RET 		,1,true,	0,0x0,0}	,
			{eO_RET 		,1,true,	0,0x0,0}	,
			{eO_RET 		,1,true,	0,0x0,0}	,
			{eO_RDPMC 	,1,true,	0,0x0,0}		,
			{eO_ROL 		,1,true,	0,0x0,0}	,
			{eO_ROR 		,1,true,	0,0x0,0}	,
			{eO_RSM 		,1,true,	0,0x0,0}	,
			{eO_SALC 		,1,true,	0,0x0,0}	,
			{eO_SAHF 		,1,true,	0,0x0,0}	,
			{eO_SAL 		,1,true,	0,0x0,0}	,
			{eO_SAR 		,1,true,	0,0x0,0}	,
			{eO_SETcc 	,1,true,	0,0x0,0}		,
			{eO_SHL 		,1,true,	0,0x0,0}	,
			{eO_SHR 		,1,true,	0,0x0,0}	,
			{eO_SBB 		,1,true,	0,0x0,0}	,
			{eO_SCASB 	,1,true,	0,0x0,0}		,
			{eO_SCASW 	,1,true,	0,0x0,0}		,
			{eO_SCASD 	,1,true,	0,0x0,0}		,
			{eO_SGDT 		,1,true,	0,0x0,0}	,
			{eO_SHLD 		,1,true,	0,0x0,0}	,
			{eO_SHRD 		,1,true,	0,0x0,0}	,
			{eO_SIDT 		,1,true,	0,0x0,0}	,
			{eO_SLDT		,1,true,	0,0x0,0}	,
			{eO_SMSW 		,1,true,	0,0x0,0}	,
			{eO_STC 		,1,true,	0,0x0,0}	,
			{eO_STD 		,1,true,	0,0x0,0}	,
			{eO_STI 		,1,true,	0,0x0,0}	,
			{eO_STOSB 	,1,true,	0,0x0,0}		,
			{eO_STOSW 	,1,true,	0,0x0,0}		,
			{eO_STOSD 	,1,true,	0,0x0,0}		,
			{eO_STR 		,1,true,	0,0x0,0}	,
			{eO_SUB 		,1,true,	0,0x0,0}	,
			{eO_TEST 		,1,true,	0,0x0,0}	,
			{eO_VERR 		,1,true,	0,0x0,0}	,
			{eO_VERW 		,1,true,	0,0x0,0}	,
			{eO_WAIT 		,1,true,	0,0x0,0}	,
			{eO_WBINVD 	,1,true,	0,0x0,0}	,
			{eO_WRMSR 	,1,true,	0,0x0,0}		,
			{eO_XADD 		,1,true,	0,0x0,0}	,
			{eO_XCHG 		,1,true,	0,0x0,0}	,
			{eO_XLAT 		,1,true,	0,0x0,0}	,
			{eO_XOR 		,1,true,	0,0x0,0}	,
			{eO_CALL 		,1,true,	0,0x0,0}	,
			{eO_Jcc 		,1,true,	0,0x0,0}	,
			{eO_JCXZ 		,1,true,	0,0x0,0}	,
			{eO_JCXE 		,1,true,	0,0x0,0}	,
			{eO_JECXZ 	,1,true,	0,0x0,0}		,
			{eO_JECXE 	,1,true,	0,0x0,0}		,
			{eO_JMP 		,1,true,	0,0x0,0}	,
			{eO_LOOP 		,1,true,	0,0x0,0}	,
			{eO_LOOPZ 	,1,true,	0,0x0,0}		,
			{eO_LOOPE 	,1,true,	0,0x0,0}		,
			{eO_LOOPNZ 	,1,true,	0,0x0,0}	,
			{eO_LOOPNE 	,1,true,	0,0x0,0}	,
			{eO_LOCK 		,1,true,	0,0x0,0}	,
			{eO_REP 		,1,true,	0,0x0,0}	,
			{eO_REPE 		,1,true,	0,0x0,0}	,
			{eO_REPZ 		,1,true,	0,0x0,0}	,
			{eO_REPNE 	,1,true,	0,0x0,0}		,
			{eO_REPNZ 	,1,true,	0,0x0,0}		,
			{eO_CS		,1,true,	0,0x0,0}		,
			{eO_DS		,1,true,	0,0x0,0}		,
			{eO_ES		,1,true,	0,0x0,0}		,
			{eO_FS		,1,true,	0,0x0,0}		,
			{eO_GS		,1,true,	0,0x0,0}		,
			{eO_SS		,1,true,	0,0x0,0}		,
			{eO_F2XM1 	,1,true,	0,0x0,0}		,
			{eO_FABS 		,1,true,	0,0x0,0}	,
			{eO_FADD 		,1,true,	0,0x0,0}	,
			{eO_FADDP 	,1,true,	0,0x0,0}		,
			{eO_FIADD 	,1,true,	0,0x0,0}		,
			{eO_FCMOVcc 	,1,true,	0,0x0,0}	,
			{eO_FCHS 		,1,true,	0,0x0,0}	,
			{eO_FCLEX 	,1,true,	0,0x0,0}		,
			{eO_FNCLEX 	,1,true,	0,0x0,0}	,
			{eO_FCOM 		,1,true,	0,0x0,0}	,
			{eO_FCOMP 	,1,true,	0,0x0,0}		,
			{eO_FICOM 	,1,true,	0,0x0,0}		,
			{eO_FICOMP 	,1,true,	0,0x0,0}	,
			{eO_FCOMI 	,1,true,	0,0x0,0}		,
			{eO_FCOMIP 	,1,true,	0,0x0,0}	,
			{eO_FUCOMI 	,1,true,	0,0x0,0}	,
			{eO_FUCOMIP 	,1,true,	0,0x0,0}	,
			{eO_FUCOMPP 	,1,true,	0,0x0,0}	,
			{eO_FCOS 		,1,true,	0,0x0,0}	,
			{eO_FDECSTP 	,1,true,	0,0x0,0}	,
			{eO_FDISI 	,1,true,	0,0x0,0}		,
			{eO_FNDISI 	,1,true,	0,0x0,0}	,
			{eO_FDIV 		,1,true,	0,0x0,0}	,
			{eO_FDIVP 	,1,true,	0,0x0,0}		,
			{eO_FIDIV 	,1,true,	0,0x0,0}		,
			{eO_FDIVR 	,1,true,	0,0x0,0}		,
			{eO_FDIVRP 	,1,true,	0,0x0,0}	,
			{eO_FIDIVR 	,1,true,	0,0x0,0}	,
			{eO_FENI 		,1,true,	0,0x0,0}	,
			{eO_FNENI 	,1,true,	0,0x0,0}		,
			{eO_FFREE 	,1,true,	0,0x0,0}		,
			{eO_FINCSTP 	,1,true,	0,0x0,0}	,
			{eO_FINIT 	,1,true,	0,0x0,0}		,
			{eO_FNINIT 	,1,true,	0,0x0,0}	,
			{eO_FLD 		,1,true,	0,0x0,0}	,
			{eO_FILD 		,1,true,	0,0x0,0}	,
			{eO_FBLD 		,1,true,	0,0x0,0}	,
			{eO_FLD1 		,1,true,	0,0x0,0}	,
			{eO_FLDZ 		,1,true,	0,0x0,0}	,
			{eO_FLDPI 	,1,true,	0,0x0,0}		,
			{eO_FLDL2E 	,1,true,	0,0x0,0}	,
			{eO_FLDL2T 	,1,true,	0,0x0,0}	,
			{eO_FLDLG2 	,1,true,	0,0x0,0}	,
			{eO_FLDLN2 	,1,true,	0,0x0,0}	,
			{eO_FLDCW 	,1,true,	0,0x0,0}		,
			{eO_FLDENV 	,1,true,	0,0x0,0}	,
			{eO_FMUL 		,1,true,	0,0x0,0}	,
			{eO_FMULP 	,1,true,	0,0x0,0}		,
			{eO_FIMUL 	,1,true,	0,0x0,0}		,
			{eO_FNOP 		,1,true,	0,0x0,0}	,
			{eO_FPATAN 	,1,true,	0,0x0,0}	,
			{eO_FPREM 	,1,true,	0,0x0,0}		,
			{eO_FPREM1 	,1,true,	0,0x0,0}	,
			{eO_FPTAN 	,1,true,	0,0x0,0}		,
			{eO_FRNDINT 	,1,true,	0,0x0,0}	,
			{eO_FRSTOR 	,1,true,	0,0x0,0}	,
			{eO_FSAVE 	,1,true,	0,0x0,0}		,
			{eO_FNSAVE 	,1,true,	0,0x0,0}	,
			{eO_FSCALE 	,1,true,	0,0x0,0}	,
			{eO_FSETPM 	,1,true,	0,0x0,0}	,
			{eO_FSIN 		,1,true,	0,0x0,0}	,
			{eO_FSINCOS 	,1,true,	0,0x0,0}	,
			{eO_FSQRT 	,1,true,	0,0x0,0}		,
			{eO_FST 		,1,true,	0,0x0,0}	,
			{eO_FSTP 		,1,true,	0,0x0,0}	,
			{eO_FIST 		,1,true,	0,0x0,0}	,
			{eO_FISTP 	,1,true,	0,0x0,0}		,
			{eO_FBSTP 	,1,true,	0,0x0,0}		,
			{eO_FSTCW 	,1,true,	0,0x0,0}		,
			{eO_FNSTCW 	,1,true,	0,0x0,0}	,
			{eO_FSTENV 	,1,true,	0,0x0,0}	,
			{eO_FNSTENV 	,1,true,	0,0x0,0}	,
			{eO_FSTSW 	,1,true,	0,0x0,0}		,
			{eO_FNSTSW 	,1,true,	0,0x0,0}	,
			{eO_FSUB 		,1,true,	0,0x0,0}	,
			{eO_FSUBP 	,1,true,	0,0x0,0}		,
			{eO_FISUB 	,1,true,	0,0x0,0}		,
			{eO_FSUBR 	,1,true,	0,0x0,0}		,
			{eO_FSUBRP 	,1,true,	0,0x0,0}	,
			{eO_FISUBR 	,1,true,	0,0x0,0}	,
			{eO_FTST 		,1,true,	0,0x0,0}	,
			{eO_FUCOM 	,1,true,	0,0x0,0}		,
			{eO_FUCOMP 	,1,true,	0,0x0,0}	,
			{eO_FUCOMPP 	,1,true,	0,0x0,0}	,
			{eO_FWAIT 	,1,true,	0,0x0,0}		,
			{eO_FXAM 		,1,true,	0,0x0,0}	,
			{eO_FXCH 		,1,true,	0,0x0,0}	,
			{eO_FXTRACT 	,1,true,	0,0x0,0}	,
			{eO_FYL2X 	,1,true,	0,0x0,0}		,
			{eO_FYL2XP1	,1,true,	0,0x0,0}	,
		};

		void	CheckPrefix(AssembleOperator op,InstCode& c){
			switch(op){
				case eO_LOCK:{
					c.InstructionPrefixes	=	0xF0;
						   }break;
				case eO_REPNE:
				case eO_REPNZ:{
					c.InstructionPrefixes	=	0xF2;
						   }break;
				case eO_REP:{
					c.InstructionPrefixes	=	0xF3;
						   }break;
				case eO_REPE:
				case eO_REPZ:{
					c.InstructionPrefixes	=	0xF3;
						   }break;
				case eO_CS:{
					c.InstructionPrefixes	=	0x2E;
						   }break;
				case eO_SS:{
					c.InstructionPrefixes	=	0x36;
						   }break;
				case eO_DS:{
					c.InstructionPrefixes	=	0x3E;
						   }break;
				case eO_ES:{
					c.InstructionPrefixes	=	0x26;
						   }break;
				case eO_FS:{
					c.InstructionPrefixes	=	0x64;
						   }break;
				case eO_GS:{
					c.InstructionPrefixes	=	0x65;
						 }break;
				default:{
					c.InstructionPrefixes	=	0;
						}break;
			}
		}
// 
// 		U32 modrm(int mod, AssembleRegister r1,AssembleRegister r2)
// 		{
// 			unsigned char m = mod<<6|r1|r2<<3;
// 			switch(mod)
// 			{
// 			case 0:
// 				switch(r1)
// 				{
// 				case 4:
// 					sibb(parser,op1,NONE);
// 					break;
// 				case 5:
// 					op1.type	= MEM;
// 					if(parser.pre_addr)
// 						op1.imm	= parser.gword();
// 					else
// 						op1.imm	= parser.gdword();
// 					break;
// 				default:
// 					op1.type	= MEM;
// 					op1.base	= (op_s)(EAX+r1);
// 					break;
// 				}
// 				break;
// 			case 1:
// 				switch(r1)
// 				{
// 				case 4:
// 					sibb(parser,op1,EBP);
// 					op1.imm		= parser.gbyte();
// 					break;
// 				default:
// 					op1.type	= MEM;
// 					op1.base	= (op_s)(EAX+r1);
// 					op1.imm		= parser.gchar();
// 					break;
// 				}
// 				break;
// 			case 2:
// 				switch(r1)
// 				{
// 				case 4:
// 					sibb(parser,op1,EBP);
// 					op1.imm		= parser.gdword();
// 					break;
// 				default:
// 					op1.type	= MEM;
// 					op1.base	= (op_s)(EAX+r1);
// 					op1.imm		= parser.gdword();
// 					break;
// 				}
// 				break;
// 			case 3:
// 				op1.type		= size;
// 				switch(size)
// 				{
// 				case R8:
// 					op1.base	= (op_s)(AL+r1);
// 					break;
// 				default:
// 					if(parser.pre_addr)
// 						op1.base	= (op_s)(AX+r1);
// 					else
// 						op1.base	= (op_s)(EAX+r1);
// 					break;
// 				}
// 				break;
// 			}
// 			return r2;
// 		}


		bool Disassemble( const void* p,unsigned int uiSize,std::string&	strCode)
		{
			ud_t ud_obj;
			ud_init(&ud_obj);

			ud_set_mode(&ud_obj, 32);

			//ud_set_input_buffer(&ud_obj, bin, sizeof(bin));
			ud_set_input_buffer(&ud_obj, (uint8_t*)p,uiSize);//bin, sizeof(bin));
			ud_set_syntax(&ud_obj, UD_SYN_INTEL);

			//printf("==> Without Symbol Resolution\n");
			//dis_loop(&ud_obj);
			char str[64];
			while (ud_disassemble(&ud_obj) != 0) {
				
				sprintf_s(str,"%016llx %-16s %s\n", ud_insn_off(&ud_obj),
					ud_insn_hex(&ud_obj),
					ud_insn_asm(&ud_obj));
				strCode+=str;
			}
			return true;
		}


		Assemble::Assemble()
		{
			m_uiSize	=	1024*1024;
			m_uiOffset	=	0;
			m_pBuffer	=	(U8*)VirtualAlloc(0,m_uiSize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
		}

		U8* Assemble::Buffer( U32 uiSize)
		{
			if(m_uiOffset	+	uiSize	>	m_uiSize){
				U32 uiOldSize	=	m_uiSize;
				m_uiSize*=2;
				U8*	pBuffer	=	(U8*)VirtualAlloc(0,m_uiSize,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
				memcpy(pBuffer,m_pBuffer,uiOldSize);
				VirtualFree(m_pBuffer,0,MEM_FREE);
				m_pBuffer=pBuffer;
			}
			U32 uiOldOffset	=	m_uiOffset;
			m_uiOffset+=uiSize;
			return	&m_pBuffer[uiOldOffset];
		}

		Air::U32 Assemble::PushBuffer( const void* pBuffer,U32 uiSize )
		{
			U32 uiOldOffset	=	m_uiOffset;
			memcpy(Buffer(uiSize),pBuffer,uiSize);
			return uiOldOffset;
		}

		U32		Assemble::Code(Code1 op){
			return PushBuffer((U8)op);
		};

		U32		Assemble::Code(Code1 op,U32 Imm32){
			U8 c[5]={op,0,0,0,0};
			U32* pOffset	=	(U32*)&c[1];
			*pOffset=Imm32;
			return PushBuffer(c);
		};
		U32		Assemble::Code(AssembleOperator op,AssembleRegister rDst,AssembleRegister rSrc){
			return m_uiOffset;
		};
		U32		Assemble::Code(AssembleOperator op,AssembleRegister rDst,U32 mSrc){
			return m_uiOffset;
		};
		U32		Assemble::Code(AssembleOperator op,AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc){
			return m_uiOffset;
		};
		U32		Assemble::Code(AssembleOperator op,AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset){
			return m_uiOffset;
		};

		Air::U32 Assemble::Code( Code1 op,U8 Imm8 )
		{
			U8 c[2]={op,0};
			c[1]=Imm8;
			return PushBuffer(c);
		}

		Air::U32 Assemble::Push( AssembleRegister r )
		{
			U8 c =	eC_PUSH_EAX;
			c|=r;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Push( U32 m )
		{
			U8 c[5];
			U32 size=2;
			if(m<256){
				c[0]=eC_PUSH_IMM8;
				c[1]=(U8)m;
			}else{
				size=5;
				c[0]=eC_PUSH_IMM32;
				U32* pOffset	=	(U32*)&c[1];
				*pOffset=m;
			}
			return PushBuffer(c,size);
		}


		Air::U32 Assemble::Pop( AssembleRegister r )
		{
			U8 c =	eC_POP_EAX;
			c|=r;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Operator( Code1 op,AssembleRegister rDst,AssembleRegister rSrc )
		{
			U8 c[2] =	{op,0xC0};
			c[1]|=rDst<<3|rSrc;
			return	PushBuffer(c);
		}

		U32		Assemble::Operator(Code1 op,AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset)
		{
			if(mOffset==0){
				U8 c[2] =	{op,0x00};
				c[1]|=rDst<<3|rSrc;
				return	PushBuffer(c);
			}
			if(mOffset	> 255){
				U8 c[6] =	{op,0x80,0x00,0x00,0x00,0x00};
				c[1]|=rDst<<3|rSrc;
				U32* pOffset	=	(U32*)&c[2];
				*pOffset=mOffset;
				return	PushBuffer(c);
			}else{
				U8 c[3] =	{op,0x40,0x00};
				c[1]|=rDst<<3|rSrc;
				c[2]=(U8)mOffset;
				return	PushBuffer(c);
			}
		}

		Air::U32 Assemble::Operator( Code1 op,AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc )
		{
			if(mOffset==0){
				if(rDst	==	eAR_ESP){
					U8 c[3] =	{op,0x00,0x24};
					c[1]|=rSrc<<3|rDst;
					return	PushBuffer(c);
				}else if(rDst	==	eAR_EBP){
					U8 c[3] =	{op,0x40,0x00};
					c[1]|=rSrc<<3|rDst;
					return	PushBuffer(c);
				}
				U8 c[2] =	{op,0x00};
				c[1]|=rSrc<<3|rDst;
				return	PushBuffer(c);
			}
			if(rDst	==	eAR_ESP){
				if(mOffset	> 255){
					U8 c[7] =	{op,0x80,0x24,0x00,0x00,0x00,0x00};
					c[1]|=rSrc<<3|rDst;
					U32* pOffset	=	(U32*)&c[3];
					*pOffset=mOffset;
					return	PushBuffer(c);
				}else{
					U8 c[4] =	{op,0x40,0x24,0x00};
					c[1]|=rSrc<<3|rDst;
					c[3]=(U8)mOffset;
					return	PushBuffer(c);
				}
			}
			if(mOffset	> 255){
				U8 c[6] =	{op,0x80,0x00,0x00,0x00,0x00};
				c[1]|=rSrc<<3|rDst;
				U32* pOffset	=	(U32*)&c[2];
				*pOffset=mOffset;
				return	PushBuffer(c);
			}else{
				U8 c[3] =	{op,0x40,0x00};
				c[1]|=rSrc<<3|rDst;
				c[2]=(U8)mOffset;
				return	PushBuffer(c);
			}
		}

		Air::U32 Assemble::Operator( Code1 op,AssembleRegister rDst,U32 mSrc )
		{
			U8 c[5] =	{op,0x00,0x00,0x00,0x00};
			c[0]|=rDst;
			U32* pOffset	=	(U32*)&c[1];
			*pOffset=mSrc;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Call( AssembleRegister r)
		{
			U8 c[2] =	{eC_R8_RM32_NONE_NONE_group4,0xD0};
			c[1]|=	r;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Call( U32 uiOffset,U32* pRelocal /*= NULL*/ )
		{
			U8 c[5]={eC_CALL_REL32,0,0,0,0};
			U32* pOffset	=	(U32*)&c[1];
			*pOffset=uiOffset-m_uiOffset-5;
			if(pRelocal!=NULL){
				*pRelocal	=	m_uiOffset+1;
			}
			return	PushBuffer(c);
		}


		Air::U32 Assemble::Ret( U16 uiEspOffset /*= 0*/ )
		{
			if(uiEspOffset==0){
				U8 c = eC_RET;
				return	PushBuffer(c);
			}else{
				U8 c[3] = {eC_RET_IMM16,0,0};
				
				U16* pOffset	=	(U16*)&c[1];
				*pOffset=uiEspOffset;
				return	PushBuffer(c);
			}
		}

		Air::U32 Assemble::Cmp( AssembleRegister rLeft,AssembleRegister rRight )
		{
			U8 c[2] = {eC_CMP_R32_RM32,0XC0};
			c[1]|=rLeft<<3|rRight;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Test( AssembleRegister r )
		{
			U8 c[2] = {eC_TEST_RM32_R32,0XC0};
			c[1]|=r<<3;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Int3()
		{
			U8 c=eC_INT_C3;
			return	PushBuffer(c);
		}


		Air::U8 Assemble::OperatorToByteCode( AssembleOperator op )
		{

			return 0;
		}

		Air::U32 Assemble::Jmp( U32 mOffset )
		{
			U8 c[5]={eC_JMP_REL32,0,0,0,0};
			U32 ret	=	PushBuffer(c);
			U32 uiRA	=	mOffset-m_uiOffset;
			memcpy(&m_pBuffer[m_uiOffset-4],&uiRA,sizeof(U32));
			return uiRA;
		}

		Air::U32 Assemble::JumpZero( U32* pOffset )
		{
			//if(mOffset<256){
			//	U8 c[2]={eC_JZ_REL8,(U8)mOffset};
			//	return	PushBuffer(c);
			//}

			return JumpCondition(eCEx_JZ_REL32,pOffset);
		}

		Air::U32 Assemble::JumpLess( U32 mOffset )
		{
			//if(mOffset<256){
			//	U8 c[2]={eC_JL_REL8,(U8)mOffset};
			//	return	PushBuffer(c);
			//}

			return JumpCondition(eCEx_JL_REL32,&mOffset);
		}

		U8* Assemble::GetCurrentPtr()
		{
			return &m_pBuffer[m_uiOffset];
		}

		void Assemble::WriteAddress_JumpHere( U32 uiJump )
		{
			U32 uiRA	=	m_uiOffset-uiJump;
			memcpy(&m_pBuffer[uiJump-4],&uiRA,sizeof(U32));
		}

		Air::U32 Assemble::GetCurrentOffset()
		{
			return m_uiOffset;
		}

		Air::U32 Assemble::Nop()
		{
			U8 c=eC_NOP;
			return	PushBuffer(c);
		}

		void* Assemble::GetBuffer(U32 uiOffset)
		{
			return &m_pBuffer[uiOffset];
		}

		Air::U32 Assemble::SubR32Imm( AssembleRegister r,U32 imm )
		{
			return Group1(enCG1_SUB,r,imm);
		}

		Air::U32 Assemble::IMulR32Imm( AssembleRegister r,U32 imm32 )
		{
			if(imm32 < 256){
				U8 c[3]={eC_IMUL_R32_RM32_IMM8,0XC0,(U8)imm32};
				c[1]|=r;
				return PushBuffer(c);
			}else{
				U8 c[6]={eC_IMUL_R32_RM32_IMM32,0XC0,0,0,0,0};
				c[1]|=r;
				U32* pImm32	=	(U32*)&c[2];
				*pImm32	=	imm32;
				return PushBuffer(c);
			}
		}

		Air::U32 Assemble::IMulR32R32( AssembleRegister rDst,AssembleRegister rSrc )
		{
			U8 c[3]={eC_IMM8_NONE_NONE_NONE_opcodex,0xAF,0XC0};
			c[2]|=	rDst<<3|rSrc;
			return PushBuffer(c);
		}

		Air::U32 Assemble::IDivR32Imm( AssembleRegister r,U32 imm32 )
		{
			if(r!=eAR_EAX){
				Mov_R32R32(eAR_EAX,r);
			}
			Mov_Imm(eAR_ECX,imm32);
			U8 cDiv_Eax_Ecx[3]={0X99,eC_R8_RM32_NONE_NONE_group3,0xF9};
			return PushBuffer(cDiv_Eax_Ecx);
		}

		Air::U32 Assemble::Mov_Imm( AssembleRegister r,U32 imm32 )
		{
			return Operator(eC_MOV_EAX_IMM32,r,imm32);
		}

		Air::U32 Assemble::Mov_R32R32( AssembleRegister rDst,AssembleRegister rSrc )
		{
			return Operator(eC_MOV_R32_RM32,rDst,rSrc);
		}

		Air::U32 Assemble::Mov_RM32R32( AssembleRegister rDst,U32 uiOffset,AssembleRegister rSrc )
		{
			return Operator(eC_MOV_RM32_R32,rDst,uiOffset,rSrc);
		}

		Air::U32 Assemble::Mov_R32RM32( AssembleRegister rDst,AssembleRegister rSrc ,U32 uiOffset)
		{
			return Operator(eC_MOV_R32_RM32,rDst,rSrc,uiOffset);
		}

		Air::U32 Assemble::JumpNotEqual( U32* pOffset/*=NULL*/ )
		{
			return JumpCondition(eCEx_JNZ_REL32,pOffset);
		}

		void Assemble::Optimize()
		{

		}

		Air::U32 Assemble::IDiv()
		{
			//0X99			cdq
			//0xF0 0XF9		idiv eax,ecx
			U8 cDiv_Eax_Ecx[3]={eC_CDQ,eC_R8_RM32_NONE_NONE_group3,0xF9};
			return PushBuffer(cDiv_Eax_Ecx);
		}

		Air::U32 Assemble::Not( AssembleRegister r )
		{
			U32 uiOffset	=	GetCurrentOffset();
			if(r!=eAR_EBX){
				Mov_R32R32(eAR_EBX,r);
			}
			XorR32R32(eAR_EAX,eAR_EAX);
			CmpR32Imm(eAR_EBX,0);
			SetEqual(r);
			return uiOffset;
		}

		Air::U32 Assemble::LogicNot( AssembleRegister r )
		{
			U8 cDiv_Eax_Ecx[3]={eC_CDQ,eC_R8_RM32_NONE_NONE_group3,0xF9};
			return PushBuffer(cDiv_Eax_Ecx);
		}

		Air::U32 Assemble::CmpEaxImm(U32 Imm32 )
		{
			U8 c[5]={eC_CMP_EAX_IMM32,0,0,0,0};
			U32* pImm32	=	(U32*)&c[1];
			*pImm32	=	Imm32;
			return PushBuffer(c);
		}

		Air::U32 Assemble::XorEaxImm( U32 Imm )
		{
			U8 c[3]={eC_R8_RM32_IMM8_NONE_group1_,0xF0,0};
			c[2]=(U8)Imm;
			return PushBuffer(c);
		}

		Air::U32 Assemble::XorR32R32( AssembleRegister rDst,AssembleRegister rSrc )
		{
			U8 c[2]={eC_XOR_R32_RM32,0xC0};
			c[1]|=rDst|rSrc<<3;
			return PushBuffer(c);
		}

		Air::U32 Assemble::SetEqual( AssembleRegister r )
		{
			U8 c[3]={eC_IMM8_NONE_NONE_NONE_opcodex,eCEx_SETE_rm8,0xC0};
			c[2]|=r;
			return PushBuffer(c);
		}

		Air::U32 Assemble::CmpR32Imm( AssembleRegister r,U32 imm )
		{
			return Group1(enCG1_CMP,r,imm);
		}

		Air::U32 Assemble::Group1(Code1Group1 g1Code,AssembleRegister r,U32 imm )
		{
			if(imm<256){
				U8 c[3]={eC_R8_RM32_IMM8_NONE_group1_,0xC0|g1Code<<3,(U8)imm};
				c[1]|=r;
				return PushBuffer(c);
			}
			U8 c[6]={eC_R8_RM32_IMM32_NONE_group1,0xC0|g1Code<<3,0,0,0,0};
			c[1]|=r;
			U32* pImm32	=	(U32*)&c[2];
			*pImm32	=	imm;
			return PushBuffer(c);
		}

		Air::U32 Assemble::XorR32Imm( AssembleRegister r,U32 imm )
		{
			return Group1(enCG1_XOR,r,imm);
		}

		Air::U32 Assemble::AddR32Imm( AssembleRegister r,U32 imm )
		{
			return Group1(enCG1_ADD,r,imm);
		}

		Air::U32 Assemble::AndR32Imm( AssembleRegister r,U32 imm )
		{
			return Group1(enCG1_AND,r,imm);
		}

		Air::U32 Assemble::OrR32Imm( AssembleRegister r,U32 imm )
		{
			return Group1(enCG1_OR,r,imm);
		}

		Air::U32 Assemble::JumpCondition( Code1Ex codeex,U32* pOffset )
		{
			U32 uiVal	=	0;
			if(pOffset!=NULL){
				uiVal	=	*pOffset - m_uiOffset - 5;
			}
			return CodeEx(codeex,uiVal);
		}

		Air::U32 Assemble::CodeEx( Code1Ex codeex,U32 uiVal )
		{
			U8 c[6]={eC_IMM8_NONE_NONE_NONE_opcodex,codeex,0,0,0,0};
			U32* pOffset	=	(U32*)&c[2];
			*pOffset=uiVal;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::AndR32R32( AssembleRegister rDst,AssembleRegister rSrc )
		{
			return Operator(eC_AND_R32_RM32,rDst,rSrc);
		}

		Air::U32 Assemble::OrR32R32( AssembleRegister rDst,AssembleRegister rSrc )
		{
			return Operator(eC_OR_R32_RM32,rDst,rSrc);
		}

		Air::U32 Assemble::Group2( Code1Group2 g2Code,AssembleRegister r,U8 imm )
		{
			U8 c[3]={eC_R8_RM8_IMM8_NONE_group2,0xC0|g2Code<<3,(U8)imm};
			c[1]|=r;
			return PushBuffer(c);
		}

		Air::U32 Assemble::LeftShift(AssembleRegister r, U8 imm )
		{
			return Group2(enCG2_SHL,r,imm);
		}

		Air::U32 Assemble::RightShift( AssembleRegister r,U8 imm )
		{
			return Group2(enCG2_SHR,r,imm);
		}

		Air::CppScript::Code1Ex InserveJumpCondition( Code1Ex codeex )
		{
			switch(codeex){
				case	eCEx_JO_REL32	: {return eCEx_JNO_REL32;}break;
				case 	eCEx_JNO_REL32	: {return eCEx_JO_REL32;}break;
				case 	eCEx_JB_REL32	: {return eCEx_JAE_REL32;}break;
				case 	eCEx_JAE_REL32	: {return eCEx_JB_REL32;}break;
				case 	eCEx_JZ_REL32	: {return eCEx_JNZ_REL32;}break;
				case 	eCEx_JNZ_REL32	: {return eCEx_JZ_REL32;}break;
				case 	eCEx_JBE_REL32	: {return eCEx_JA_REL32;}break;
				case 	eCEx_JA_REL32	: {return eCEx_JBE_REL32;}break;
				case 	eCEx_JS_REL32	: {return eCEx_JNS_REL32;}break;
				case 	eCEx_JNS_REL32	: {return eCEx_JS_REL32;}break;
				case 	eCEx_JP_REL32	: {return eCEx_JNP_REL32;}break;
				case 	eCEx_JNP_REL32	: {return eCEx_JP_REL32;}break;
				case 	eCEx_JL_REL32	: {return eCEx_JGE_REL32;}break;
				case 	eCEx_JGE_REL32	: {return eCEx_JL_REL32;}break;
				case 	eCEx_JLE_REL32	: {return eCEx_JG_REL32;}break;
				case 	eCEx_JG_REL32	: {return eCEx_JLE_REL32;}break;
			}
			return codeex;
		}

	}
}