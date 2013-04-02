#include "AirRenderState11.h"
#include "AirRenderDevice11.h"
namespace	Air{
	namespace	Engine{
		extern	Render::Device11*	pDevice;
		namespace	Render{
#define CREATE_STATE(StateType)	ID3D11##StateType*	p		=	NULL;pDxDevice->Create##StateType(desc,&p);m_pDxState	=	p;


			State11::State11( CAString& strName,PassStateInfo* pInfo ):State(strName,pInfo)
			{
				m_pDxState	=	NULL;
			}

			Air::U1 State11::Create()
			{

				DxDevice*	pDxDevice	=	(DxDevice*)pDevice->GetDevice();
				switch(m_Info.type){
				case enRST_RS:{
					D3D11_RASTERIZER_DESC*	desc	=	(D3D11_RASTERIZER_DESC*)&m_Info.rs;

					CREATE_STATE(RasterizerState);
					break;}
				case enRST_DS:{
					D3D11_DEPTH_STENCIL_DESC*	desc	=	(D3D11_DEPTH_STENCIL_DESC*)&m_Info.ds;
					CREATE_STATE(DepthStencilState);
					break;}
				case enRST_BS:{
					D3D11_BLEND_DESC*	desc	=	(D3D11_BLEND_DESC*)&m_Info.bs;
					CREATE_STATE(BlendState);
					break;}
				case enRST_SS:{
					D3D11_SAMPLER_DESC*	desc	=	(D3D11_SAMPLER_DESC*)&m_Info.ss;
					CREATE_STATE(SamplerState);
					break;}
				}
				return	true;
			}

			Air::U1 State11::Destroy()
			{
				if(m_pDxState!=NULL){
					switch(m_Info.type){
						case enRST_RS:{
							TRelease<ID3D11RasterizerState>(m_pDxState);
							break;}
						case enRST_DS:{
							TRelease<ID3D11DepthStencilState>(m_pDxState);
							break;}
						case enRST_BS:{
							TRelease<ID3D11BlendState>(m_pDxState);
							break;}
						case enRST_SS:{
							TRelease<ID3D11SamplerState>(m_pDxState);
							break;}
					}
				}
				return	true;
			}

			void* State11::GetState()
			{
				return	m_pDxState;
			}

		}
	}
}