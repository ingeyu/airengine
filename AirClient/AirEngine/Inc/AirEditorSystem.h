#ifndef AirEditorSystem_h__
#define AirEditorSystem_h__

#include "AirEngineHeader.h"
#include "OIS.h"

namespace	Air{
	namespace	Engine{
		class	EditorSystem	:
			public	IFactoryManager,
			public	Singleton<EditorSystem>,
			public	OIS::MouseListener,
			public	OIS::KeyListener
		{
		public:
			EditorSystem();

			virtual	U1	Initialization();
			virtual	U1	Release();
			virtual bool mouseMoved( const OIS::MouseEvent &arg );
			virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			virtual bool keyPressed( const OIS::KeyEvent &arg );
			virtual bool keyReleased( const OIS::KeyEvent &arg );		
		protected:

		};
	}
}
#endif // AirEditorSystem_h__
