#include "AirPipelineOIT.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"

namespace	Air{
	namespace	Engine{
		struct Pixel{
			struct{
				U32		uiColor;
				float	fDepth;
			}Fragment;
			U32	uiNext;
		};


		OIT::OIT()
		{
			m_pPixelBuffer_Counter		=	NULL;
			m_pPerPixelLinkedList	=	NULL;
			m_pScreenMask	=	NULL;
			m_pSortRender			=	NULL;
		}

		OIT::~OIT()
		{

		}

		Air::U1 OIT::Initialize( Render::Window* pMainWindow )
		{
			if(pMainWindow==NULL){
				return false;
			}
			U32	uiCount	=	pMainWindow->GetWidth()*pMainWindow->GetHeight();

			Render::Buffer::Info info;
			info.SetStructureBuffer(uiCount*4,sizeof(Pixel));
			info.SetViewFlag(enVF_SRV|enVF_UAV|enVF_Counter);
			m_pPixelBuffer_Counter	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer*>("OIT_PixelBuffer_Counter","Buffer",&info);
			info.SetByteAddressBuffer(uiCount,sizeof(S32));
			info.SetViewFlag(enVF_SRV|enVF_UAV);
			m_pScreenMask	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer*>("OIT_ScreenMask","Buffer",&info);

			m_pSortRender	=	EngineSystem::GetSingleton()->CreateProduct<Material*>("OIT_SortRender","Material");

			return true;
		}

		Air::U1 OIT::Release()
		{
			SAFE_RELEASE_REF(m_pPixelBuffer_Counter);
			SAFE_RELEASE_REF(m_pScreenMask);
			SAFE_RELEASE_REF(m_pPerPixelLinkedList);
			SAFE_RELEASE_REF(m_pSortRender);
			return true;
		}

		void OIT::Update(Renderable* pRenderable)
		{
			Render::Device*	pDevice	=	RenderSystem::GetSingleton()->GetDevice();


			Render::Window* pWindow	=	RenderSystem::GetSingleton()->GetMainWindow();

			
			{
				void*	pRTV	=	pWindow->GetRTV();
				void*	pDSV	=	pWindow->GetDepthRTV();
				void* pUAVArray[]={
					m_pPixelBuffer_Counter->GetUAV(),
					m_pScreenMask->GetUAV()
				};
				U32 uiClear=0xffffffff;
				pDevice->ClearUAV(pUAVArray[1],&uiClear);
				pDevice->SetRTV_DSV_UAV(1,&pRTV,pDSV,0,2,pUAVArray,0);


				PhaseOption opt;
				opt.AddIndex(enPI_Alpha);
				RenderSystem::GetSingleton()->RenderPhase(opt);

				pUAVArray[0]	=	NULL;
				pUAVArray[1]	=	NULL;
				pDevice->SetRTV_DSV(1,&pRTV,pDSV);
				
				void* pSRV[]={
					m_pPixelBuffer_Counter->GetSRV(),
					m_pScreenMask->GetSRV()
				};
				pDevice->SetSRV(enPS,0,pSRV[0]);
				pDevice->SetSRV(enPS,1,pSRV[1]);
				m_pSortRender->RenderOneObject(pRenderable);
				pDevice->SetSRV(enPS,0,NULL);
				pDevice->SetSRV(enPS,1,NULL);

			}





		}

	}
}