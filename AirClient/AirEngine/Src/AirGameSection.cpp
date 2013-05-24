#include "AirGameSection.h"
#include "AirEngineSystem.h"
#include "AirEnginePipeline.h"
#include "AirGameThirdControl.h"
#include "AirGameSystem.h"
#include "AirGlobalSetting.h"
namespace	Air{
	namespace	Game{


		AString	Section::ProductTypeName	=	"Section";
		Section::Section( CAString& strName ):Common::IProduct(strName)
		{
			m_pPipeline	=	NULL;
			m_pScene	=	NULL;
			m_pControl	=	NULL;
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
			m_pControl	=	OnCreateControl();
			if(m_pControl!=NULL)
			{
				OIS::KeyListener*	pKey	=	m_pControl;
				OIS::MouseListener*	pMouse	=	m_pControl;
				Engine::GetGlobalSetting().m_pInputSystem->Add(pKey);
				Engine::GetGlobalSetting().m_pInputSystem->Add(pMouse);

				m_pControl->SetCallback(this);

			}
			return true;
		}

		Air::U1 Section::Destroy()
		{
			if(m_pControl!=NULL)
			{
				OIS::KeyListener*	pKey	=	m_pControl;
				OIS::MouseListener*	pMouse	=	m_pControl;
				Engine::GetGlobalSetting().m_pInputSystem->Remove(pKey);
				Engine::GetGlobalSetting().m_pInputSystem->Remove(pMouse);

			}
			SAFE_RELEASE_REF(m_pControl);
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
			m_pControl->Update(fFrameTime);
			m_pScene->UpdateNode(fFrameTime);
			m_pPipeline->Update(fFrameTime);
			m_pScene->UpdateMovableObject(fFrameTime);
		}

		Engine::Scene* Section::GetScene()
		{
			return m_pScene;
		}

		void Section::RenderOneFrame( const FrameTime& fFrameTime )
		{
			if(m_pPipeline!=NULL){
				m_pPipeline->RenderOneFrame(fFrameTime);
			}
		}

		void Section::LoadScene( CAString& strName )
		{
			m_pScene->GetLoader().Load(strName);
			m_pPipeline->BuildSVO();
		}

		void Section::SaveScene( CAString& strName )
		{
			m_pScene->GetLoader().Save(strName);
		}

		Control* Section::OnCreateControl()
		{
			ThirdControl::Info info;
			info.bAllowRotate	=	false;
			info.pSection		=	this;
			info.pCamera		=	m_pPipeline->GetMainCamera();
			return GameSystem::GetSingleton()->CreateProduct<ThirdControl>(m_strProductName+"_Control",&info);
		}

		Control* Section::GetControl()
		{
			return m_pControl;
		}

		Engine::SceneNode* Section::GetActorNode()
		{
			return m_pScene->GetDynamicSceneNode();
		}



	}
}