#include "AirGameSection.h"
#include "AirEngineSystem.h"
#include "AirEnginePipeline.h"

namespace	Air{
	namespace	Game{


		AString	Section::ProductTypeName	=	"Section";
		Section::Section( CAString& strName ):Common::IProduct(strName)
		{
			m_pPipeline	=	NULL;
			m_pScene	=	NULL;
		}

		Air::U1 Section::Create()
		{

			m_pPipeline	=	EngineSystem::GetSingleton()->CreateProduct<Engine::DefaultPipeline>(m_strProductName+"_Pipeline");
			if(m_pPipeline==NULL)
				return false;
			m_pScene	=	EngineSystem::GetSingleton()->CreateProduct<Engine::Scene>(m_strProductName+"_Scene");
			if(m_pScene==NULL)
				return false;
			m_pPipeline->SetCurrentScene(m_pScene);
			return true;
		}

		Air::U1 Section::Destroy()
		{
			SAFE_RELEASE_REF(m_pPipeline);
			SAFE_RELEASE_REF(m_pScene);
			return true;
		}

		Engine::Pipeline* Section::GetPipeline()
		{
			return m_pPipeline;
		}

		void Section::Update( const FrameTime& fFrameTime )
		{
			m_pScene->Update(fFrameTime);
		}

		Engine::Scene* Section::GetScene()
		{
			return m_pScene;
		}

		void Section::RenderOneFrame( const FrameTime& fFrameTime )
		{
			if(m_pPipeline!=NULL){
				m_pPipeline->Update(fFrameTime);

				m_pPipeline->RenderOneFrame(fFrameTime);
			}
		}

	}
}