#include "AirEditorSystem.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceInputSystem.h"
namespace	Air{
	namespace	Engine{


		EditorSystem::EditorSystem()
		{

		}

		Air::U1 EditorSystem::Initialization()
		{
			OIS::KeyListener*	pKey	=	this;
			OIS::MouseListener*	pMouse	=	this;
			GetGlobalSetting().m_pInputSystem->Add(pKey);
			GetGlobalSetting().m_pInputSystem->Add(pMouse);

			return true;
		}

		Air::U1 EditorSystem::Release()
		{
			OIS::KeyListener*	pKey	=	this;
			OIS::MouseListener*	pMouse	=	this;
			GetGlobalSetting().m_pInputSystem->Remove(pKey);
			GetGlobalSetting().m_pInputSystem->Remove(pMouse);
			return true;
		}

		bool EditorSystem::mouseMoved( const OIS::MouseEvent &arg )
		{

			return true;
		}

		bool EditorSystem::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			return true;
		}

		bool EditorSystem::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			return true;
		}

		bool EditorSystem::keyPressed( const OIS::KeyEvent &arg )
		{
			return true;
		}

		bool EditorSystem::keyReleased( const OIS::KeyEvent &arg )
		{
			return true;
		}

	}
}