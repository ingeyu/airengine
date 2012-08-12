#include "AirRenderGlobal11.h"
#include "AirRenderHeader11.h"
//#include "asm_math.h"
//#include "AirRenderMaterial.h"
namespace Air{
	
	namespace	Client{
		namespace	Render{
			static	Global	g_Global;
	
			Global::Global(){
				m_pDevice			=	NULL;
				pGlobalSetting		=	&GetGlobalSetting();
				m_pRenderDevice		=	NULL;
				m_bReseting			=	false;
	
	
			}
	
			Global::~Global(){
	
			}
	
			Global& GetGlobal(){
				return g_Global;
			}
		}
	}
};