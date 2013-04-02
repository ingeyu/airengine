#ifndef INTERFACEGAMEDATASYSTEM_HEAD_FILE
#define INTERFACEGAMEDATASYSTEM_HEAD_FILE

#include "AirGameHeader.h"
#include "AirInterfaceGameDataInfo.h"

namespace Air{
	
	namespace Engine{
	
	
		namespace	Game{
			namespace	Data{
				/**	\brief	数据指针类
				*
				*	数据指针类
				*
				***/
				class	ISystem	:
					public	IPlugin{
				public:
					virtual	void*	Get(AString	strName)				=	NULL;
					virtual	void	Set(AString	strName,void*	pData)	=	NULL;
	
					virtual	Infomation::Player*	GetPlayerInfo(UInt uiID)	=	NULL;
					virtual	Infomation::Room*	GetRoomInfo(AString	strName)		=	NULL;
				};
			}
		}
	
	};
};
#endif // INTERFACEGAMEDATASYSTEM_HEAD_FILE