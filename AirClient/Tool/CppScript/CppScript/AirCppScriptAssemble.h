#ifndef AirCppScriptAssemble_h__
#define AirCppScriptAssemble_h__

#include <string>

namespace	Air{
	namespace	CppScript{
		enum	AssembleOperator{
			eAO_Push,
			eAO_Pop,
			eAO_Add,
			eAO_Sub,
			eAO_Imul,
			eAO_Div,
			eAO_Mov,
			eAO_Inc,
			eAO_And,
			eAO_Or,
			eAO_Cmp,
			eAO_Test,
			eAO_Jmp,
			eAO_Jz,
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

			eAR_AX=eAR_EAX,
			eAR_CX=eAR_ECX,
			eAR_DX=eAR_EDX,
			eAR_BX=eAR_EBX,
			eAR_SP=eAR_ESP,
			eAR_BP=eAR_EBP,
			eAR_SI=eAR_ESI,
			eAR_DI=eAR_EDI,

			eAR_AL=eAR_EAX,
			eAR_CL=eAR_ECX,
			eAR_DL=eAR_EDX,
			eAR_BL=eAR_EBX,
			eAR_AH=eAR_ESP,
			eAR_CH=eAR_EBP,
			eAR_DH=eAR_ESI,
			eAR_BH=eAR_EDI,
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

		class	Assemble{
		public:
			//U32		Add();

			
		};

		bool	Disassemble(const void* p,unsigned int uiSize,std::string&	strCode);
	}
}
#endif // AirCppScriptAssemble_h__
