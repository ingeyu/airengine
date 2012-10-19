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

			void Device::DrawObject( Renderable* pObj )
			{

				const DrawBuff&	buff	=	pObj->GetDrawBuff();
				SetVD(buff.m_pVertexDeclare);
				SetVB(0,buff.m_pVertexBuff);
				//如果IB为空 则不设置
				if(buff.m_pIndexBuff!=NULL)
					SetIB(buff.m_pIndexBuff);

				return	DrawOpt(buff.m_DrawOption);
			}

			void Device::DrawOpt( const DrawOption& opt )
			{
				m_uiDrawBatch++;
				m_uiDrawTriangleCount	+=	opt.m_uiFaceCount;
			}

			void Device::SetVP( Viewport* pVP )
			{

			}

			void Device::SetSRV( enumShaderType type,U32 uiIndex,void* pSRV )
			{

			}

			void Device::SetUAV( U32 uiCount,void** pUAV )
			{

			}

			void Device::SetRTV_DSV( U32 uiCount,void** pRTV,void* pDSV )
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