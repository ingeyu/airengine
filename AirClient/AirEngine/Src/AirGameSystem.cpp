#include "AirGameSystem.h"
#include "AirGameSection.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"
#include "AirGameFPSControl.h"
#include "AirGameThirdControl.h"
#include "AirGameFreeControl.h"
#include "AirGameActor.h"

namespace	Air{
	namespace	Game{


		System::System()
		{
			m_pSection	=	NULL;
		}

		Air::U1 System::Initialization()
		{
			AddFactory(new ParamFactory<Actor>());
			AddFactory(new ParamFactory<FPSControl>());
			AddFactory(new ParamFactory<ThirdControl>());
			AddFactory(new ParamFactory<FreeControl>());
			AddFactory(new NoParamFactory<Section>());


			EngineSystem::GetSingleton()->CreateProduct<Engine::Material>("NoMaterial");

			return true;
		}

		Air::U1 System::Release()
		{
			DestroyAllProduct();
			DestroyAllFactory();
			return true;
		}

		Section* System::GetCurrentSection()
		{
			return m_pSection;
		}

		void System::Update( const FrameTime& fFrameTime )
		{
			if(m_pSection!=NULL)
				m_pSection->Update(fFrameTime);
		}

		void System::RenderOneFrame( const FrameTime& fFrameTime )
		{
			if(m_pSection!=NULL)
			{
				m_pSection->RenderOneFrame(fFrameTime);
			}
		}

		void System::SetCurrentSection( Section* pSection )
		{
			m_pSection	=	pSection;
			if(m_pSection!=NULL){
				EngineSystem::GetSingleton()->SetCurrentPipeline(m_pSection->GetPipeline());
			}else{
				EngineSystem::GetSingleton()->SetCurrentPipeline(NULL);
			}
		}

	}
}