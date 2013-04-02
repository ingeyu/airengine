#include "AirGameGlobal.h"
namespace Air{
	
	namespace	Engine{
		namespace	Game{
			
	
			Global::Global(){
				m_pSystem	=	NULL;
				m_pSection	=	NULL;
				m_pDataSystem	=	NULL;
				m_pLoadingSection	=	NULL;
				//m_pUIFlashSys	=	dynamic_cast<UI::Flash::IISystem*>(GetGlobalSetting().m_pUISystem);
			}
	
			Global& GetGlobal(){
				static	Global	g_Global;
				return g_Global;
			}
		}
	}
	
};
