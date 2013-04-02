#ifndef INTERFACEAUDIOSYSTEM_HEAD_FILE
#define INTERFACEAUDIOSYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceAudioScene.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	ISystem	:
				public	Common::ISystem{
			public:
				ISystem(CAString&	strType):Common::ISystem(strType){

				};
	
				virtual	IScene*	CreateScene(AString	strName)	=	NULL;
				virtual	void	DestroyScene(IScene*	pScene)	=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEAUDIOSYSTEM_HEAD_FILE