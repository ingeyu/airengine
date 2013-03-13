#include "AirRenderDevice.h"
#include "AirEngineRenderable.h"

namespace	Air{
	namespace	Client{
		namespace	Render{


			void Device::SetVD( VertexDeclare* pDeclare )
			{

			}

			void Device::SetVB( U32 uiIndex,Buffer* pBuffer )
			{

			}

			void Device::SetIB( Buffer* pBuffer )
			{

			}

			void Device::SetCB( U32 uiIndex,Buffer* pBuffer )
			{

			}

			void Device::SetCB( enumShaderType type,U32 uiIndex,Buffer* pBuffer )
			{

			}

			void Device::SetShader( enumShaderType type,Shader* pShader )
			{

			}

			void Device::SetSS( enumShaderType type,U32 uiRegister,State* pState )
			{

			}

			void Device::SetRS( State* pState )
			{

			}

			void Device::SetDSS( State* pState )
			{

			}

			void Device::SetBS( State* pState )
			{

			}


			void Device::DrawOpt( const DrawOption& opt )
			{
				m_uiDrawBatch++;
				m_uiDrawTriangleCount	+=	opt.m_uiIndexCount/3;
			}

			void	Device::SetVP( Viewport* pVP )
			{

			}

			void	Device::SetSRV( enumShaderType type,U32 uiIndex,void* pSRV )
			{

			}

			void	Device::SetUAV( U32 uiCount,void** pUAV )
			{

			}
			void	Device::ClearUAV(void* pUAV,U32* uiClear)
			{

			};
			void	Device::ClearUAV(void* pUAV,float* fClear)
			{

			};
			void	Device::SetRTV_DSV( U32 uiCount,void** pRTV,void* pDSV )
			{

			}
			void	Device::SetRTV_DSV_UAV(U32	uiCount,void**	pRTV,void*	pDSV,U32 uiUAVCount,void** pUAV)
			{

			}

			Air::Client::enumSystemVersion Device::GetHWVersion()
			{
				return	m_HWVersion;
			}

			Device::Device():IProduct("Device")
			{
				m_HWVersion	=	enRSV_11;

				m_uiDrawBatch			=	0;
				m_uiDrawTriangleCount	=	0;
			}

		}
	}
}