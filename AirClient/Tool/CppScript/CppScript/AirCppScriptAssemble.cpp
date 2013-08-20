#include "AirCppScriptAssemble.h"
#include "Disassemable/udis86.h"
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

	}
}