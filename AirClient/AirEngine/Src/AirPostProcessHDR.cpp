#include "AirPostProcessHDR.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"
namespace	Air{
	namespace	Engine{
		namespace	PostProcess{


			HDR::HDR()
			{
				for(int i=0;i<6;i++){
					m_pRT_Luminance[i]	=	NULL;
				}
				for(int i=0;i<2;i++){
					m_pRT_Brightness[i]=0;
				}
				m_matColorToLuminance		=	NULL;
				m_matDownScaleLuminance		=	NULL;
				m_matBrightness				=	NULL;
				m_matBrightBlur				=	NULL;
				m_matBloom					=	NULL;
				m_matFinal					=	NULL;
			}

			HDR::~HDR()
			{

			}

			void HDR::Init()
			{
				RenderSystem*	pRenderSys	=	RenderSystem::GetSingleton();

				RenderTarget::Info rtinfo;
				rtinfo.SetSingleTargetScreen(enTFMT_R16G16B16A16_FLOAT,0.5f);
				m_pRT_Luminance[0]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_LuminanceHalf","Target",&rtinfo);
				rtinfo.SetSingleTarget(81,81,enTFMT_R16G16B16A16_FLOAT);
				m_pRT_Luminance[1]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_Luminance81x81","Target",&rtinfo);
				rtinfo.SetSingleTarget(27,27,enTFMT_R16G16B16A16_FLOAT);
				m_pRT_Luminance[2]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_Luminance27x27","Target",&rtinfo);
				rtinfo.SetSingleTarget(9,9,enTFMT_R16G16B16A16_FLOAT);
				m_pRT_Luminance[3]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_Luminance9x9","Target",&rtinfo);
				rtinfo.SetSingleTarget(3,3,enTFMT_R16G16B16A16_FLOAT);
				m_pRT_Luminance[4]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_Luminance3x3","Target",&rtinfo);
				rtinfo.SetSingleTarget(1,1,enTFMT_R16G16B16A16_FLOAT);
				m_pRT_Luminance[5]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_Luminance1","Target",&rtinfo);

				rtinfo.SetSingleTargetScreen(enTFMT_R16G16B16A16_FLOAT,0.125);
				
				m_pRT_Brightness[0]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_Brightness_0","Target",&rtinfo);
				m_pRT_Brightness[1]	=	pRenderSys->CreateProduct<RenderTarget*>("HDR_Brightness_1","Target",&rtinfo);
				

				EngineSystem* pEngineSys	=	EngineSystem::GetSingleton();
				m_matColorToLuminance		=	pEngineSys->CreateProduct<Material*>("PostProcess_HDR_ColorToLuminance","Material");
				m_matDownScaleLuminance		=	pEngineSys->CreateProduct<Material*>("PostProcess_HDR_DownScaleLuminance","Material");
				m_matBrightness				=	pEngineSys->CreateProduct<Material*>("PostProcess_HDR_Brightness","Material");
				m_matBrightBlur				=	pEngineSys->CreateProduct<Material*>("PostProcess_HDR_BrightBlur","Material");
				m_matBloom					=	pEngineSys->CreateProduct<Material*>("PostProcess_HDR_Bloom","Material");
				m_matFinal					=	pEngineSys->CreateProduct<Material*>("PostProcess_HDR_Final","Material");	
			}

			void HDR::Release()
			{
				for(int i=0;i<6;i++){
					SAFE_RELEASE_REF(m_pRT_Luminance[i]);
				}
				for(int i=0;i<2;i++){
					SAFE_RELEASE_REF(m_pRT_Brightness[i]);
				}
				SAFE_RELEASE_REF(m_matColorToLuminance		);
				SAFE_RELEASE_REF(m_matDownScaleLuminance	);
				SAFE_RELEASE_REF(m_matBrightness			);
				SAFE_RELEASE_REF(m_matBrightBlur			);
				SAFE_RELEASE_REF(m_matBloom					);
				SAFE_RELEASE_REF(m_matFinal					);
			}

			void HDR::UpdateTarget()
			{

			}

		}
	}
}