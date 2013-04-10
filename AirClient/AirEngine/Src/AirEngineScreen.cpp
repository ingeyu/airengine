#include "AirEngineScreen.h"
#include "AirEnginePipeline.h"
#include "AirEngineSystem.h"

namespace	Air{
	namespace	Engine{

		AString Screen::ProductTypeName	=	"Screen";
		Screen::Screen( CAString& strName,Info* pInfo ):IProduct(strName)
		{
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}
			m_pPipeline=NULL;
		}

		Air::U1 Screen::Create()
		{
			m_pPipeline	=	OnCreatePipeline(m_Info.strPipelineName);
			if(m_pPipeline==NULL){
				return false;
			}
			return true;
		}

		Air::U1 Screen::Destroy()
		{
			SAFE_RELEASE_REF(m_pPipeline);

			return true;
		}

		Pipeline* Screen::GetPipeline()
		{
			if(m_pPipeline!=NULL){
				m_pPipeline->AddRef();
			}
			return m_pPipeline;
		}

		Pipeline* Screen::OnCreatePipeline( CAString& strPipelineName )
		{
			return	EngineSystem::GetSingleton()->CreateProduct<Pipeline>(m_strProductName+"_Pipeline",strPipelineName);
		}

		Air::U1 Screen::RenderOneFrame( const FrameTime& frameTime )
		{
			if(m_pPipeline!=NULL){
				m_pPipeline->Update(frameTime);

				m_pPipeline->RenderOneFrame(frameTime);
			}
			return true;
		}

		void Screen::SetCurrentScene( Scene* pScene )
		{
			if(m_pPipeline){
				m_pPipeline->SetCurrentScene(pScene);
			}
		}

		Scene* Screen::GetCurrentScene()
		{
			if(m_pPipeline){
				return	m_pPipeline->GetCurrentScene();
			}
			return NULL;
		}

	}
}