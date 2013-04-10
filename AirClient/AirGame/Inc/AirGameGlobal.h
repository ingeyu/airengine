#ifndef GAMEGLOBAL_HEAD_FILE
#define GAMEGLOBAL_HEAD_FILE

#include "AirGame.h"
#include "AirGameHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Game{
			namespace	Data{
				class	ISystem;
			}
			/**	\brief	游戏系统全局变量
			*
			*	游戏系统全局变量
			*
			***/
			class	Global{
			public:
				Global();
	
				//Data::ISystem*	m_pDataSystem;
				//System*		m_pSystem;
				//Section*		m_pSection;
				//Section*		m_pLoadingSection;
				//UI::Flash::IISystem*	m_pUIFlashSys;
			};
	
			GAME_EXPORT	Global&	GetGlobal();
		}
	
	};
};
#endif // GAMEGLOBAL_HEAD_FILE