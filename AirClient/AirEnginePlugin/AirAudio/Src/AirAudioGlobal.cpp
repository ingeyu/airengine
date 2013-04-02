#include "AirAudioGlobal.h"
namespace Air{
	
	namespace	Engine{
		namespace	Audio{
	
	
			Global::Global(){
				m_pContext	=	NULL;
				m_pDevice	=	NULL;
			}
			static	Global	g_Global;
			Global& GetGlobal(){
				return	g_Global;
			}
		}
	
	}
};