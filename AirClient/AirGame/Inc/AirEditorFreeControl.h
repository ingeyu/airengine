#ifndef AirEditorFreeControl_h__
#define AirEditorFreeControl_h__

#include "AirEditorHeader.h"

namespace	Air{
	namespace	Editor{
		class	GAME_EXPORT	FreeControl	:	public	Game::FPSControl
		{
		public:
			static AString ProductTypeName;
			FreeControl(CAString& strName,Info* pInfo);

			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual bool	mouseMoved( const OIS::MouseEvent &arg );

			virtual	U1		Update(const FrameTime& frameTime);

			virtual	U1		keyReleased( const OIS::KeyEvent &arg );

		};
	}
}
#endif // AirEditorFreeControl_h__
