#ifndef AirCppScriptAssemble_h__
#define AirCppScriptAssemble_h__
#include "AirCppScriptDefine.h"
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
			Assemble();


			U32		Push(AssembleRegister r);
			U32		Pop(AssembleRegister r);
			U32		Mov(AssembleRegister rDst,AssembleRegister rSrc);
			U32		Mov(AssembleRegister rDst,U32 mSrc);
			U32		Mov(AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc);
			U32		Mov(AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset);
			U32		Call(AssembleRegister r);
			U32		Call(U32 uiOffset,U32* pRelocal	=	NULL);
			U32		Add(AssembleRegister rDst,AssembleRegister rSrc);
			U32		Add(AssembleRegister rDst,U32 mSrc);
			U32		Add(AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc);
			U32		Add(AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset);
			U32		Sub(AssembleRegister rDst,AssembleRegister rSrc);
			U32		Sub(AssembleRegister rDst,U32 mSrc);
			U32		Sub(AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc);
			U32		Sub(AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset);
			U32		IMul(AssembleRegister rDst,AssembleRegister rSrc);
			U32		IMul(AssembleRegister rDst,U32 mSrc);
			U32		IMul(AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc);
			U32		IMul(AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset);
			U32		Div(AssembleRegister rDst,AssembleRegister rSrc);
			U32		Div(AssembleRegister rDst,U32 mSrc);
			U32		Div(AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc);
			U32		Div(AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset);
			U32		Test(AssembleRegister r);
			U32		Cmp(AssembleRegister rLeft,AssembleRegister rRight);
			U32		Jmp(U32 mOffset);
			U32		JmpAbs(U32 mAddr);
			U32		JumpZero(U32 mOffset);
			U32		JumpLess(U32 mOffset);
			U32		JumpGreater(U32 mOffset);
			U32		JumpEqual(U32 mOffset);
			U32		Ret(U16 uiEspOffset	=	0);
			U32		Int3();


		public:
			U32		GetCurrentOffset();
		protected:
			U32		PushBuffer(const U8* pBuffer,U32 uiSize);
			U8*		Buffer(U32 uiSize);
			template<typename T>
			U32		PushBuffer(const T& t){
				return PushBuffer(&t,sizeof(t));
			};
			template<int iCount>
			U32		PushBuffer(const U8(&t)[iCount]){
				return PushBuffer(t,iCount);
			};
		protected:
			U32		m_uiSize;
			U32		m_uiOffset;
			U8*		m_pBuffer;
		};

		bool	Disassemble(const void* p,unsigned int uiSize,std::string&	strCode);
	}
}
#endif // AirCppScriptAssemble_h__
