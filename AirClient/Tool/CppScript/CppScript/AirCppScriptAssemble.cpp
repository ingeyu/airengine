#include "AirCppScriptAssemble.h"
#include "Disassemable/udis86.h"
#include "AirCppScript.h"
namespace	Air{
	namespace	CppScript{


		bool Disassemble( const void* p,unsigned int uiSize,std::string&	strCode)
		{
			ud_t ud_obj;
			ud_init(&ud_obj);
#ifdef _X86_
			ud_set_mode(&ud_obj, 32);
#else
			ud_set_mode(&ud_obj, 64);
#endif
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
			m_pBuffer	=	(U8*)__Alloc(m_uiSize);
		}

		U8* Assemble::Buffer( U32 uiSize)
		{
			if(m_uiOffset	+	uiSize	>	m_uiSize){
				U32 uiOldSize	=	m_uiSize;
				m_uiSize*=2;
				U8*	pBuffer	=	(U8*)__Alloc(m_uiSize);
				memcpy(pBuffer,m_pBuffer,uiOldSize);
				__Free(m_pBuffer);
				m_pBuffer=pBuffer;
			}
			U32 uiOldOffset	=	m_uiOffset;
			m_uiOffset+=uiSize;
			return	&m_pBuffer[uiOldOffset];
		}

		Air::U32 Assemble::PushBuffer( const U8* pBuffer,U32 uiSize )
		{
			U32 uiOldOffset	=	m_uiOffset;
			memcpy(Buffer(uiSize),pBuffer,uiSize);
			return uiOldOffset;
		}
		Air::U32 Assemble::Push( AssembleRegister r )
		{
			U8 c =	0x50;
			c|=r;
			return	PushBuffer(c);
		}


		Air::U32 Assemble::Pop( AssembleRegister r )
		{
			U8 c =	0x58;
			c|=r;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Mov( AssembleRegister rDst,AssembleRegister rSrc )
		{
			U8 c[2] =	{0x8B,0xC0};
			c[1]|=rDst<<3|rSrc;
			return	PushBuffer(c);
		}

		U32		Assemble::Mov(AssembleRegister rDst,AssembleRegister rSrc,U32 mOffset)
		{
			if(mOffset==0){
				U8 c[2] =	{0x8B,0x00};
				c[1]|=rDst<<3|rSrc;
				return	PushBuffer(c);
			}
			if(mOffset	> 255){
				U8 c[6] =	{0x8B,0x80,0x00,0x00,0x00,0x00};
				c[1]|=rDst<<3|rSrc;
				U32* pOffset	=	(U32*)&c[2];
				*pOffset=mOffset;
				return	PushBuffer(c);
			}else{
				U8 c[3] =	{0x8B,0x40,0x00};
				c[1]|=rDst<<3|rSrc;
				c[2]=(U8)mOffset;
				return	PushBuffer(c);
			}
		}

		Air::U32 Assemble::Mov( AssembleRegister rDst, U32 mOffset,AssembleRegister rSrc )
		{
			if(mOffset==0){
				if(rDst	==	eAR_ESP){
					U8 c[3] =	{0x89,0x00,0x24};
					c[1]|=rSrc<<3|rDst;
					return	PushBuffer(c);
				}else if(rDst	==	eAR_EBP){
					U8 c[3] =	{0x89,0x40,0x00};
					c[1]|=rSrc<<3|rDst;
					return	PushBuffer(c);
				}
				U8 c[2] =	{0x89,0x00};
				c[1]|=rSrc<<3|rDst;
				return	PushBuffer(c);
			}
			if(rDst	==	eAR_ESP){
				if(mOffset	> 255){
					U8 c[7] =	{0x89,0x80,0x24,0x00,0x00,0x00,0x00};
					c[1]|=rSrc<<3|rDst;
					U32* pOffset	=	(U32*)&c[3];
					*pOffset=mOffset;
					return	PushBuffer(c);
				}else{
					U8 c[4] =	{0x89,0x40,0x24,0x00};
					c[1]|=rSrc<<3|rDst;
					c[3]=(U8)mOffset;
					return	PushBuffer(c);
				}
			}
			if(mOffset	> 255){
				U8 c[6] =	{0x89,0x80,0x00,0x00,0x00,0x00};
				c[1]|=rSrc<<3|rDst;
				U32* pOffset	=	(U32*)&c[2];
				*pOffset=mOffset;
				return	PushBuffer(c);
			}else{
				U8 c[3] =	{0x89,0x40,0x00};
				c[1]|=rSrc<<3|rDst;
				c[2]=(U8)mOffset;
				return	PushBuffer(c);
			}
		}

		Air::U32 Assemble::Mov( AssembleRegister rDst,U32 mSrc )
		{
			U8 c[5] =	{0xB8,0x00,0x00,0x00,0x00};
			c[0]|=rDst;
			U32* pOffset	=	(U32*)&c[1];
			*pOffset=mSrc;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Call( AssembleRegister r)
		{
			U8 c[2] =	{0xFF,0xD0};
			c[1]|=	r;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Call( U32 uiOffset,U32* pRelocal /*= NULL*/ )
		{
			U8 c[5]={0xE8,0,0,0,0};
			U32* pOffset	=	(U32*)&c[1];
			*pOffset=uiOffset;
			if(pRelocal!=NULL){
				*pRelocal	=	m_uiOffset+1;
			}
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Add( AssembleRegister rDst,AssembleRegister rSrc )
		{
			U8 c[2] =	{0x03,0xC0};
			c[1]|=rDst<<3|rSrc;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Add( AssembleRegister rDst,U32 mSrc )
		{
			if(mSrc<256){
				U8 c[3] =	{0x83,0xC0,0};
				c[1]|=rDst;
				c[2]	=	(U8)mSrc;
				return	PushBuffer(c);
			}else{
				U8 c[6] =	{0x81,0xC0,0,0,0,0};
				c[1]|=rDst;
				U32* pOffset	=	(U32*)&c[2];
				*pOffset=mSrc;
				return	PushBuffer(c);
			}
		}

		Air::U32 Assemble::Ret( U16 uiEspOffset /*= 0*/ )
		{
			if(uiEspOffset==0){
				U8 c = 0xC3;
				return	PushBuffer(c);
			}else{
				U8 c[3] = {0xC2,0,0};
				
				U16* pOffset	=	(U16*)&c[1];
				*pOffset=uiEspOffset;
				return	PushBuffer(c);
			}
		}

		Air::U32 Assemble::Cmp( AssembleRegister rLeft,AssembleRegister rRight )
		{
			U8 c[2] = {0x3B,0XC0};
			c[1]|=rLeft<<3|rRight;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Test( AssembleRegister r )
		{
			U8 c[2] = {0x85,0XC0};
			c[1]|=r<<3;
			return	PushBuffer(c);
		}

		Air::U32 Assemble::Int3()
		{
			U8 c=0xCC;
			return	PushBuffer(c);
		}

	}
}