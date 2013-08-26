#ifndef AirCppScriptAssemble_h__
#define AirCppScriptAssemble_h__
#include "AirCppScriptDefine.h"
#include <string>

namespace	Air{
	namespace	CppScript{
		enum	AssembleOperator{
			//Main Instructions 
			eO_AAA 			,
			eO_AAD 			,
			eO_AAM 			,
			eO_AAS 			,
			eO_ADC 			,
			eO_ADD 			,
			eO_AND 			,
			eO_ARPL 			,
			eO_BOUND 			,
			eO_BSF 			,
			eO_BSR 			,
			eO_BSWAP 			,
			eO_BT 			,
			eO_BTC 			,
			eO_BTR 			,
			eO_BTS 			,
			eO_CBW 			,
			eO_CDQ 			,
			eO_CLC 			,
			eO_CLD 			,
			eO_CLI 			,
			eO_CLTS 			,
			eO_CMC 			,
			eO_CMOVcc 		,
			eO_CMP 			,
			eO_CMPSB 			,
			eO_CMPSW 			,
			eO_CMPSD 			,
			eO_CMPXCHG 		,
			eO_CMPXCHG8B 		,
			eO_CPUID 			,
			eO_CWD 			,
			eO_CWDE 			,
			eO_DAA 			,
			eO_DAS 			,
			eO_DEC 			,
			eO_DIV 			,
			eO_ENTER 			,
			eO_HLT 			,
			eO_IDIV 			,
			eO_IMUL 			,
			eO_IN 			,
			eO_INC 			,
			eO_INSB 			,
			eO_INSW 			,
			eO_INSD 			,
			eO_INT 			,
			eO_INTO 			,
			eO_INVD 			,
			eO_INVLPG 		,
			eO_IRET 			,
			eO_IRETD 			,
			eO_LAHF 			,
			eO_LAR 			,
			eO_LDS 			,
			eO_LES 			,
			eO_LFS 			,
			eO_LGS 			,
			eO_LSS 			,
			eO_LEA 			,
			eO_LEAVE 			,
			eO_LGDT 			,
			eO_LIDT 			,
			eO_LLDT 			,
			eO_LMSW 			,
			eO_LODSB 			,
			eO_LODSW 			,
			eO_LODSD 			,
			eO_LSL 			,
			eO_LTR 			,
			eO_MOV 			,
			eO_MOVSB 			,
			eO_MOVSW 			,
			eO_MOVSD 			,
			eO_MOVSX 			,
			eO_MOVZX 			,
			eO_MUL 			,
			eO_NEG 			,
			eO_NOP 			,
			eO_NOT 			,
			eO_OR 			,
			eO_OUT 			,
			eO_OUTSB 			,
			eO_OUTSW 			,
			eO_OUTSD 			,
			eO_POP 			,
			eO_POPA 			,
			eO_POPAD 			,
			eO_POPF 			,
			eO_POPFD 			,
			eO_PUSH 			,
			eO_PUSHW 			,
			eO_PUSHD 			,
			eO_PUSHA 			,
			eO_PUSHAD 		,
			eO_PUSHF 			,
			eO_PUSHFD 		,
			eO_RCL 			,
			eO_RCR 			,
			eO_RDMSR 			,
			eO_RET 			,
			
			eO_RDPMC 			=104,
			eO_ROL 			,
			eO_ROR 			,
			eO_RSM 			,
			eO_SALC 			,
			eO_SAHF 			,
			eO_SAL 			,
			eO_SAR 			,
			eO_SETcc 			,
			eO_SHL 			,
			eO_SHR 			,
			eO_SBB 			,
			eO_SCASB 			,
			eO_SCASW 			,
			eO_SCASD 			,
			eO_SGDT 			,
			eO_SHLD 			,
			eO_SHRD 			,
			eO_SIDT 			,
			eO_SLDT			,
			eO_SMSW 			,
			eO_STC 			,
			eO_STD 			,
			eO_STI 			,
			eO_STOSB 			,
			eO_STOSW 			,
			eO_STOSD 			,
			eO_STR 			,
			eO_SUB 			,
			eO_TEST 			,
			eO_VERR 			,
			eO_VERW 			,
			eO_WAIT 			,
			eO_WBINVD 		,
			eO_WRMSR 			,
			eO_XADD 			,
			eO_XCHG 			,
			eO_XLAT 			,
			eO_XOR 			,
			eO_CALL 			,
			eO_Jcc 			,
			eO_JCXZ 			,
			eO_JCXE 			,
			eO_JECXZ 			,
			eO_JECXE 			,
			eO_JMP 			,
			eO_LOOP 			,
			eO_LOOPZ 			,
			eO_LOOPE 			,
			eO_LOOPNZ 		,
			eO_LOOPNE 		,
			eO_LOCK 			,
			eO_REP 			,
			eO_REPE 			,
			eO_REPZ 			,
			eO_REPNE 			,
			eO_REPNZ 			,
			eO_CS				,
			eO_DS				,
			eO_ES				,
			eO_FS				,
			eO_GS				,
			eO_SS				,
			//Co-processor instructions : 
			eO_F2XM1 			,
			eO_FABS 			,
			eO_FADD 			,
			eO_FADDP 			,
			eO_FIADD 			,
			eO_FCMOVcc 		,
			eO_FCHS 			,
			eO_FCLEX 			,
			eO_FNCLEX 		,
			eO_FCOM 			,
			eO_FCOMP 			,
			eO_FICOM 			,
			eO_FICOMP 		,
			eO_FCOMI 			,
			eO_FCOMIP 		,
			eO_FUCOMI 		,
			eO_FUCOMIP 		,
			eO_FUCOMPP 		,
			eO_FCOS 			,
			eO_FDECSTP 		,
			eO_FDISI 			,
			eO_FNDISI 		,
			eO_FDIV 			,
			eO_FDIVP 			,
			eO_FIDIV 			,
			eO_FDIVR 			,
			eO_FDIVRP 		,
			eO_FIDIVR 		,
			eO_FENI 			,
			eO_FNENI 			,
			eO_FFREE 			,
			eO_FINCSTP 		,
			eO_FINIT 			,
			eO_FNINIT 		,
			eO_FLD 			,
			eO_FILD 			,
			eO_FBLD 			,
			eO_FLD1 			,
			eO_FLDZ 			,
			eO_FLDPI 			,
			eO_FLDL2E 		,
			eO_FLDL2T 		,
			eO_FLDLG2 		,
			eO_FLDLN2 		,
			eO_FLDCW 			,
			eO_FLDENV 		,
			eO_FMUL 			,
			eO_FMULP 			,
			eO_FIMUL 			,
			eO_FNOP 			,
			eO_FPATAN 		,
			eO_FPREM 			,
			eO_FPREM1 		,
			eO_FPTAN 			,
			eO_FRNDINT 		,
			eO_FRSTOR 		,
			eO_FSAVE 			,
			eO_FNSAVE 		,
			eO_FSCALE 		,
			eO_FSETPM 		,
			eO_FSIN 			,
			eO_FSINCOS 		,
			eO_FSQRT 			,
			eO_FST 			,
			eO_FSTP 			,
			eO_FIST 			,
			eO_FISTP 			,
			eO_FBSTP 			,
			eO_FSTCW 			,
			eO_FNSTCW 		,
			eO_FSTENV 		,
			eO_FNSTENV 		,
			eO_FSTSW 			,
			eO_FNSTSW 		,
			eO_FSUB 			,
			eO_FSUBP 			,
			eO_FISUB 			,
			eO_FSUBR 			,
			eO_FSUBRP 		,
			eO_FISUBR 		,
			eO_FTST 			,
			eO_FUCOM 			,
			eO_FUCOMP 		,
			//eO_FUCOMPP 		,
			eO_FWAIT 			,
			eO_FXAM 			,
			eO_FXCH 			,
			eO_FXTRACT 		,
			eO_FYL2X 			,
			eO_FYL2XP1		,
			
			eUnknownOperator,

		};
		enum	ConditionCode{
			eCC_O 			,													///<	overflow 
			eCC_NO 			,													///<	Not overflow 
			eCC_C			,eCC_B		=	eCC_C		,eCC_NAE	=	eCC_C,	///<	Carry, below, not above nor equal
			eCC_NC			,eCC_AE		=	eCC_NC		,eCC_NB		=	eCC_NC,	///<	Not carry, above or equal, not below 
			eCC_E			,eCC_Z		=	eCC_E		,						///<	Equal, zero 
			eCC_NE			,eCC_NZ		=	eCC_NE		,						///<	Not equal, not zero 
			eCC_BE			,eCC_NA		=	eCC_BE		,						///<	Below or equal, not above 
			eCC_A			,eCC_NBE	= 	eCC_A		,						///<	Above, not below nor equal 
			eCC_S 			,													///<	Sign (negative) 
			eCC_NS 			,													///<	Not sign 
			eCC_P			,eCC_PE		=	eCC_P		,						///<	Parity, parity even 
			eCC_NP			,eCC_PO		=	eCC_NP		,						///<	Not parity, parity odd 
			eCC_L			,eCC_NGE	=	eCC_L		,						///<	Less, not greater nor equal 
			eCC_GE			,eCC_NL		=	eCC_GE 		,						///<	Greater or egual, not less 
			eCC_LE			,eCC_NG		=	eCC_LE		,						///<	Less or equal, not greater 
			eCC_G			,eCC_NLE	=	eCC_G		,						///<	Greater, not less nor equal 

		};
		enum	FCMOVccConditionCode{
			eFCC_C,eFCC_B=eFCC_C,eFCC_NAE=eFCC_C,
			eFCC_NC,eFCC_AE=eFCC_NC,eFCC_NB =eFCC_NC,
			eFCC_E,eFCC_Z =eFCC_E,
			eFCC_NE,eFCC_NZ =eFCC_NE,
			eFCC_BE,eFCC_NA =eFCC_BE,
			eFCC_A,eFCC_NBE =eFCC_A,
			eFCC_U ,
			eFCC_NU, 
		};

		enum	AssembleRegister{
			eAR_EAX,
			eAR_ECX,
			eAR_EDX,
			eAR_EBX,
			eAR_ESP,
			eAR_EBP,
			eAR_ESI,
			eAR_EDI,
		};
		enum	AssembleRegister16{
			eAR_AX,
			eAR_CX,
			eAR_DX,
			eAR_BX,
			eAR_SP,
			eAR_BP,
			eAR_SI,
			eAR_DI,
		};
		enum	AssembleRegister8{
			eAR_AL,
			eAR_CL,
			eAR_DL,
			eAR_BL,
			eAR_AH,
			eAR_CH,
			eAR_DH,
			eAR_BH,
		};
		enum	AssembleSegmentRegister{
			eASR_ES,
			eASR_CS,
			eASR_SS,
			eASR_DS,
			eASR_FS,//(Only 386+) 
			eASR_GS,//(Only 386+) 
		};
		enum	AssembleIndexRegister{
			eAIR_EAX,
			eAIR_ECX,
			eAIR_EDX,
			eAIR_EBX,
			eAIR_NoIndex,
			eAIR_EBP,
			eAIR_ESI,
			eAIR_EDI,
		};


		enum Code1{
			eC_ADD_RM8_R8, // 0x00
			eC_ADD_RM32_R32,
			eC_ADD_R8_RM8,
			eC_ADD_R32_RM32,
			eC_ADD_AL_IMM8,
			eC_ADD_EAX_IMM32,
			eC_PUSH_ES,
			eC_POP_ES,
			eC_OR_RM8_R8, // 0x08
			eC_OR_RM32_R32,
			eC_OR_R8_RM8,
			eC_OR_R32_RM32,
			eC_OR_AL_IMM8,
			eC_OR_EAX_IMM32,
			eC_PUSH_CS,
			eC_IMM8_NONE_NONE_NONE_opcodex,
			eC_ADC_RM8_R8, // 0x10
			eC_ADC_RM32_R32,
			eC_ADC_R8_RM8,
			eC_ADC_R32_RM32,
			eC_ADC_AL_IMM8,
			eC_ADC_EAX_IMM32,
			eC_PUSH_SS,
			eC_POP_SS,
			eC_SBB_RM8_R8, // 0x18
			eC_SBB_RM32_R32,
			eC_SBB_R8_RM8,
			eC_SBB_R32_RM32,
			eC_SBB_AL_IMM8,
			eC_SBB_EAX_IMM32,
			eC_PUSH_DS,
			eC_POP_DS,
			eC_AND_RM8_R8, // 0x20
			eC_AND_RM32_R32,
			eC_AND_R8_RM8,
			eC_AND_R32_RM32,
			eC_AND_AL_IMM8,
			eC_AND_EAX_IMM32,
			eC_SEG_ES,
			eC_DAA,
			eC_SUB_RM8_R8, // 0x28
			eC_SUB_RM32_R32,
			eC_SUB_R8_RM8,
			eC_SUB_R32_RM32,
			eC_SUB_AL_IMM8,
			eC_SUB_EAX_IMM32,
			eC_SEG_CS_PREFIX,
			eC_DAS,
			eC_XOR_RM8_R8, // 0x30
			eC_XOR_RM32_R32,
			eC_XOR_R8_RM8,
			eC_XOR_R32_RM32,
			eC_XOR_AL_IMM8,
			eC_XOR_EAX_IMM32,
			eC_SEG_SS_PREFIX,
			eC_AAA,
			eC_CMP_RM8_R8, // 0x38
			eC_CMP_RM32_R32,
			eC_CMP_R8_RM8,
			eC_CMP_R32_RM32,
			eC_CMP_AL_IMM8,
			eC_CMP_EAX_IMM32,
			eC_SEG_DS_PREFIX,
			eC_AAS,
			eC_INC_EAX, // 0x40
			eC_INC_ECX,
			eC_INC_EDX,
			eC_INC_EBX,
			eC_INC_ESP,
			eC_INC_EBP,
			eC_INC_ESI,
			eC_INC_EDI,
			eC_DEC_EAX, // 0x48
			eC_DEC_ECX,
			eC_DEC_EDX,
			eC_DEC_EBX,
			eC_DEC_ESP,
			eC_DEC_EBP,
			eC_DEC_ESI,
			eC_DEC_EDI,
			eC_PUSH_EAX, // 0x50
			eC_PUSH_ECX,
			eC_PUSH_EDX,
			eC_PUSH_EBX,
			eC_PUSH_ESP,
			eC_PUSH_EBP,
			eC_PUSH_ESI,
			eC_PUSH_EDI,
			eC_POP_EAX, // 0x58
			eC_POP_ECX,
			eC_POP_EDX,
			eC_POP_EBX,
			eC_POP_ESP,
			eC_POP_EBP,
			eC_POP_ESI,
			eC_POP_EDI,
			eC_PUSHAD, // 0x60
			eC_POPAD,
			eC_BOUND_IMM16_IMM32,
			eC_ARPL_RM32_R32,
			eC_SEG_FS_PREFIX,
			eC_SEG_GS_PREFIX,
			eC_PREFIX_NONE_NONE,
			
			eC_PUSH_IMM32=104, // 0x68
			eC_IMUL_R32_RM32_IMM32,
			eC_PUSH_IMM8,
			eC_IMUL_R32_RM32_IMM8,
			eC_INSB,
			eC_INSD,
			eC_OUTSB,
			eC_OUTSD,
			eC_JO_REL8, // 0x70
			eC_JNO_REL8,
			eC_JB_REL8,
			eC_JAE_REL8,
			eC_JZ_REL8,
			eC_JNZ_REL8,
			eC_JBE_REL8,
			eC_JA_REL8,
			eC_JS_REL8, // 0x78
			eC_JNS_REL8,
			eC_JP_REL8,
			eC_JNP_REL8,
			eC_JL_REL8,
			eC_JGE_REL8,
			eC_JLE_REL8,
			eC_JG_REL8,
			eC_R8_RM8_IMM8_NONE_group1, // 0x80
			eC_R8_RM32_IMM32_NONE_group1,
			eC_R8_RM8_IMM8_NONE_group1_,
			eC_R8_RM32_IMM8_NONE_group1_,
			eC_TEST_RM8_R8,
			eC_TEST_RM32_R32,
			eC_XCHG_RM8_R8,
			eC_XCHG_RM32_R32,
			eC_MOV_RM8_R8, // 0x88
			eC_MOV_RM32_R32,
			eC_MOV_R8_RM8,
			eC_MOV_R32_RM32,
			eC_MOV_R32_SEG,
			eC_LEA_R32_RM32,
			eC_MOV_SEG_R32,
			eC_POP_RM32,
			eC_NOP, // 0x90
			eC_XCHG_EAX_ECX,
			eC_XCHG_EAX_EDX,
			eC_XCHG_EAX_EBX,
			eC_XCHG_EAX_ESP,
			eC_XCHG_EAX_EBP,
			eC_XCHG_EAX_ESI,
			eC_XCHG_EAX_EDI,
			eC_CWD, // 0x98
			eC_CDQ,
			eC_CALL_ADDR,
			eC_WAIT,
			eC_PUSHFD,
			eC_POPFD,
			eC_SAHF,
			eC_LAHF,
			eC_MOV_AL_MEM, // 0xA0
			eC_MOV_EAX_MEM,
			eC_MOV_MEM_AL,
			eC_MOV_MEM_EAX,
			eC_MOVSB,
			eC_MOVSD,
			eC_CMPSB,
			eC_CMPSD,
			eC_TEST_AL_IMM8, // 0xA8
			eC_TEST_EAX_IMM32,
			eC_STOSB,
			eC_STOSD,
			eC_LODSB,
			eC_LODSD,
			eC_SCASB,
			eC_SCASD,
			eC_MOV_AL_IMM8, // 0xB0
			eC_MOV_CL_IMM8,
			eC_MOV_DL_IMM8,
			eC_MOV_BL_IMM8,
			eC_MOV_AH_IMM8,
			eC_MOV_CH_IMM8,
			eC_MOV_DH_IMM8,
			eC_MOV_BH_IMM8,
			eC_MOV_EAX_IMM32, // 0xB8
			eC_MOV_ECX_IMM32,
			eC_MOV_EDX_IMM32,
			eC_MOV_EBX_IMM32,
			eC_MOV_ESP_IMM32,
			eC_MOV_EBP_IMM32,
			eC_MOV_ESI_IMM32,
			eC_MOV_EDI_IMM32,
			eC_R8_RM8_IMM8_NONE_group2, // 0xC0
			eC_R8_RM32_IMM32_NONE_group2,
			eC_RET_IMM16,
			eC_RET,
			eC_LES_R8_RM8,
			eC_LDS_R32_RM32,
			eC_MOV_RM8_IMM8,
			eC_MOV_RM32_IMM32,
			eC_ENTER_IMM16_IMM8, // 0xC8
			eC_LEAVE,
			eC_RETF_IMM16,
			eC_RETF,
			eC_INT_C3,
			eC_INT_IMM8,
			eC_INTO,
			eC_IRET,
			eC_R8_RM8_C1_NONE_group2, // 0xD0
			eC_R8_RM32_C1_NONE_group2,
			eC_R8_RM8_CL_NONE_group2,
			eC_R8_RM32_CL_NONE_group2,
			eC_AMX_IMM8,
			eC_ADX_IMM8,
			eC_SALC,
			eC_XLAT,
			eC_NONE, // 0xD8

			eC_LOOPNZ_REL8=224, // 0xE0
			eC_LOOPZ_REL8,
			eC_LOOP_REL8,
			eC_JCXZ_REL8,
			eC_IN_AL_IMM8,
			eC_IN_EAX_IMM8,
			eC_OUT_AL_IMM8,
			eC_OUT_EAX_IMM8,
			eC_CALL_REL32, // 0xE8
			eC_JMP_REL32,
			eC_JMPF_REL32,
			eC_JMP_REL8,
			eC_IN_AL_DX,
			eC_IN_EAX_DX,
			eC_OUT_AL_DX,
			eC_OUT_EAX_DX,
			eC_LOCK_NONE_PREFIX, // 0xF0
			eC_INT_C1,
			eC_REPNZ_NONE_PREFIX,
			eC_REPZ_NONE_PREFIX,
			eC_HLT,
			eC_CMC,
			eC_R8_RM8_NONE_NONE_group3,
			eC_R8_RM32_NONE_NONE_group3,
			eC_CLC, // 0xF8
			eC_STC,
			eC_CLI,
			eC_STI,
			eC_CLD,
			eC_STD,
			eC_R8_RM8_NONE_NONE_group4,
			eC_R8_RM32_NONE_NONE_group4,
		};
		enum Code1top00{
			eCT00_SLDT_RM32_LDTR,
			eCT00_STR_RM32_TR,
			eCT00_LLDT_LDTR_RM32,
			eCT00_LTR_TR_RM32,
			eCT00_VERR_RM32,
			eCT00_VERW_RM32,
		};
		enum Code1top01{
			eCT01_SLDT_RM32_LDTR,
			eCT01_STR_RM32_TR,
			eCT01_LLDT_LDTR_RM32,
			eCT01_LTR_TR_RM32,
			eCT01_VERR_RM32,
			eCT01_VERW_RM32,
		};
		enum Code1Ex{
			eCEx_R16_NONE_NONE_NONE_top00, // 0x00
			eCEx_R16_NONE_NONE_NONE_top01,
			eCEx_LAR_r32_rm32,           //Load Access Rights Byte     

			eCEx_JO_REL32	=	0x80, // 0x80
			eCEx_JNO_REL32,
			eCEx_JB_REL32,
			eCEx_JAE_REL32,
			eCEx_JZ_REL32,
			eCEx_JNZ_REL32,
			eCEx_JBE_REL32,
			eCEx_JA_REL32,
			eCEx_JS_REL32, // 0x88
			eCEx_JNS_REL32,
			eCEx_JP_REL32,
			eCEx_JNP_REL32,
			eCEx_JL_REL32,
			eCEx_JGE_REL32,
			eCEx_JLE_REL32,
			eCEx_JG_REL32,
			eCEx_SETO_rm8               ,//Set byte if overflow 
			eCEx_SETNO_rm8              ,//Set byte if not overflow 
			eCEx_SETB_rm8               ,//Set byte if below 
			eCEx_SETAE_rm8              ,//Set byte if above or equal
			eCEx_SETE_rm8               ,//Set byte if equal 
			eCEx_SETNE_rm8              ,//Set byte if not equal 
			eCEx_SETBE_rm8              ,//Set byte if below or equal 
			eCEx_SETA_rm8               ,//Set byte if above 
			eCEx_SETS_rm8               ,//Set byte if sign 
			eCEx_SETNS_rm8              ,//Set byte if not sign 
			eCEx_SETPE_rm8              ,//Set byte if parity even 
			eCEx_SETPO_rm8              ,//Set byte if parity odd 
			eCEx_SETL_rm8               ,//Set byte if less 
			eCEx_SETGE_rm8              ,//Set byte if greater or equal
			eCEx_SETLE_rm8              ,//Set byte if less or equal 
			eCEx_SETG_rm8               ,//Set byte if greater 
			eCEx_PUSH_FS                 ,//Push FS
			eCEx_POP_FS                  ,//Pop FS
		};
		enum Code1Group1{
			enCG1_ADD,
			enCG1_OR,
			enCG1_ADC,
			enCG1_SBB,
			enCG1_AND,
			enCG1_SUB,
			enCG1_XOR,
			enCG1_CMP,
		};
		enum Code1Group2{
			enCG2_ROL,
			enCG2_ROR,
			enCG2_RCL,
			enCG2_RCR,
			enCG2_SHL,
			enCG2_SHR,
			enCG2_SAL,
			enCG2_SAR,
		};
		enum Code1Group3{
			enCG3_TEST,

			enCG3_NOT=2,
			enCG3_NEG,
			enCG3_MUL,
			enCG3_IMUL,
			enCG3_DIV,
			enCG3_IDIV,
		};
		enum Code1Group4{
			enCG4_INC,
			enCG4_DEC,
			enCG4_CALL,
			enCG4_CALLF,
			enCG4_JMP,
			enCG4_JMPF,
			enCG4_PUSH,
			enCG4_NONE,
		};
		struct Instruction{
			//Instruction(){
			//	op		=	eUnknownOperator;
			//	size	=	1;
			//	prefix	=	0;
			//	code
			//};
			AssembleOperator	eOp;
			U8	size;
			U8	bSwitch;
			U8	prefix;
			U8	op;
			U8	code[16];
		};

		struct InstCode{
			U8	InstructionPrefixes;
			U8	s			:1;
			U8	d			:1;
			U8  Opcode		:6;
			U8	R_M			:3;
			U8	Reg_OpCode	:3;
			U8	Mod			:2;
			U8	Base		:3;
			U8	Index		:3;
			U8	Scale		:2;
			U32	Address;
			U32	Imm;
		};

		Code1Ex	InserveJumpCondition(Code1Ex codeex);

		class	Assemble{
		public:
			Assemble();

			void	Optimize();

			U32		Code(Code1 op);
			U32		Code(Code1 op,U8 Imm8);
			U32		Code(Code1 op,U32 Imm32);
			U32		Code(AssembleOperator op,AssembleRegister rDst,AssembleRegister rSrc);
			U32		Code(AssembleOperator op,AssembleRegister rDst,U32 mSrc);
			U32		Code(AssembleOperator op,AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc);
			U32		Code(AssembleOperator op,AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset);

			U8		OperatorToByteCode(AssembleOperator op);

			U32		Push(AssembleRegister r);
			U32		Push(U32 m);
			U32		Pop(AssembleRegister r);

			U32		Operator(Code1 op,AssembleRegister rDst,AssembleRegister rSrc);
			U32		Operator(Code1 op,AssembleRegister rDst,U32 mSrc);
			U32		Operator(Code1 op,AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc);
			U32		Operator(Code1 op,AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset);

			U32		Call(AssembleRegister r);
			U32		Call(U32 uiOffset,U32* pRelocal	=	NULL);
			U32		Test(AssembleRegister r);
			U32		Cmp(AssembleRegister rLeft,AssembleRegister rRight);
			U32		CmpEaxImm(U32 Imm32);
			U32		CmpR32Imm(AssembleRegister r,U32 imm);
			U32		Jmp(U32 mOffset);
			U32		JmpAbs(U32 mAddr);
			U32		JumpZero(U32* pOffset=NULL);
			U32		JumpNotEqual(U32* pOffset=NULL);
			U32		JumpLess(U32 mOffset);
			U32		JumpCondition(Code1Ex codeex,U32* pOffset=NULL);
			
			U32		Ret(U16 uiEspOffset	=	0);
			U32		Int3();
			U32		Nop();
			void	WriteAddress_JumpHere(U32 uiJump);

			U32		AddR32Imm(AssembleRegister r,U32 imm);
			U32		SubR32Imm(AssembleRegister r,U32 imm);
			U32		AndR32Imm(AssembleRegister r,U32 imm);
			U32		OrR32Imm(AssembleRegister r,U32 imm);
			U32		XorR32Imm(AssembleRegister r,U32 imm);

			U32		IMulR32Imm(AssembleRegister r,U32 imm32);
			U32		IMulR32R32(AssembleRegister rDst,AssembleRegister rSrc);
			U32		IDivR32Imm(AssembleRegister r,U32 imm32);
			U32		IDiv();
			U32		Mov_Imm(AssembleRegister r,U32 imm32);
			U32		Mov_R32R32(AssembleRegister rDst,AssembleRegister rSrc);
			U32		Mov_RM32R32(AssembleRegister rDst,U32 uiOffset,AssembleRegister rSrc);
			U32		Mov_R32RM32(AssembleRegister rDst,AssembleRegister rSrc,U32 uiOffset);
			U32		MovAbsEax(U32 uiOffset);
			U32		MovEaxAbs(U32 uiOffset);
			// ~
			U32		Not(AssembleRegister r);
			// !
			U32		LogicNot(AssembleRegister r);
			U32		XorEaxImm(U32 Imm);
			U32		XorR32R32(AssembleRegister rDst,AssembleRegister rSrc);
			U32		AndR32R32(AssembleRegister rDst,AssembleRegister rSrc);
			U32		OrR32R32(AssembleRegister rDst,AssembleRegister rSrc);
			U32		SetEqual(AssembleRegister r);

			U32		LeftShift(AssembleRegister r,U8 imm);
			U32		RightShift(AssembleRegister r,U8 imm);
		public:
			U32		GetCurrentOffset();
			U32		AddOffset(U32 uiOffset);
			U8*		GetCurrentPtr();
			void*	GetBuffer(U32 uiOffset=0);

			U32		PushBuffer(const void* pBuffer,U32 uiSize);
			template<typename T>
			U32		PushBuffer(const T& t){
				return PushBuffer(&t,sizeof(t));
			};	
			template<int iCount>
			U32		PushBuffer(const U8(&t)[iCount]){
				return PushBuffer(t,iCount);
			};
		protected:
			U32		Group1(Code1Group1 g1Code,AssembleRegister r,U32 imm);
			U32		Group2(Code1Group2 g2Code,AssembleRegister r,U8 imm);

			U32		CodeEx(Code1Ex codeex,U32 uiVal);
		protected:
			
			U8*		Buffer(U32 uiSize);

			
		protected:
			U32		m_uiSize;
			U32		m_uiOffset;
			U8*		m_pBuffer;
		};

		bool	Disassemble(const void* p,unsigned int uiSize,std::string&	strCode);
	}
}
#endif // AirCppScriptAssemble_h__
