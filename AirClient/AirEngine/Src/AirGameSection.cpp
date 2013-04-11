#include "AirGameSection.h"
#include "AirEngineSystem.h"
#include "AirEngineScreen.h"

namespace	Air{
	namespace	Game{


		AString	Section::ProductTypeName	=	"Section";
		Section::Section( CAString& strName ):Common::IProduct(strName)
		{
			m_pScreen	=	NULL;
			m_pScene	=	NULL;
		}

		Air::U1 Section::Create()
		{
			Engine::Screen::Info info;
			info.strPipelineName	=	"DefaultPipeline";
			m_pScreen	=	EngineSystem::GetSingleton()->CreateProduct<Engine::Screen>(m_strProductName+"_Screen",&info);
			if(m_pScreen==NULL)
				return false;
			m_pScene	=	EngineSystem::GetSingleton()->CreateProduct<Engine::Scene>(m_strProductName+"_Scene");
			if(m_pScene==NULL)
				return false;
			m_pScreen->SetCurrentScene(m_pScene);
			return true;
		}

		Air::U1 Section::Destroy()
		{
			SAFE_RELEASE_REF(m_pScreen);
			SAFE_RELEASE_REF(m_pScene);
			return true;
		}

		Engine::Screen* Section::GetScreen()
		{
			return m_pScreen;
		}

		void Section::Update( const FrameTime& fFrameTime )
		{
			m_pScene->Update(fFrameTime);
		}

		Engine::Scene* Section::GetScene()
		{
			return m_pScene;
		}

	}
}