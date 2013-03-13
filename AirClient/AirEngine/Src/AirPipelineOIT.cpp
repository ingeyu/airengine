#include "AirPipelineOIT.h"
#include "AirEngineMaterial.h"

namespace	Air{
	namespace	Client{
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

		void OIT::UpdateOIT()
		{
			Render::Device*	pDevice	=	RenderSystem::GetSingleton()->GetDevice();
			void* pUAVArray[]={
				m_pPixelBuffer_Counter->GetUAV(),
				m_pScreenMask->GetUAV()
			};
			pDevice->SetUAV(2,pUAVArray);




			pUAVArray[0]	=	NULL;
			pUAVArray[1]	=	NULL;
			pDevice->SetUAV(2,pUAVArray);
		}

	}
}