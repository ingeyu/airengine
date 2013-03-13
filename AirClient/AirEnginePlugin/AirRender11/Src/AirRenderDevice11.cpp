#include "AirRenderDevice11.h"
#include "AirRenderGlobal11.h"
#include "AirInterfaceGameSystem.h"
#include "AirInterfaceUISystem.h"
#include "AirInterfaceNetSystem.h"
#include "AirCommonWindow.h"
#include "AirRenderBuffer11.h"
#include "AirRenderWindow11.h"
#include "AirRenderShader11.h"
#include "AirRenderVertexDeclare11.h"
#include "AirRenderTexture11.h"
#include "AirRenderState11.h"
#include "AirRenderTarget11.h"
#include "AirCommonFactory.h"

#define HARDWARE_DEVICE			0
#define WARP_DEVICE				1
#define REFERENCE_DEVICE		2
#define DX_DEVICE_TYPE			REFERENCE_DEVICE


namespace Air{
	
	namespace	Client{
		namespace	Render{
	
	

			
	
			Device11::Device11( ){

				m_pDevice			=	NULL;
				m_pContext			=	NULL;
				m_pFactory1			=	NULL;
				m_pFactory			=	NULL;
				m_uiAdapterCount	=	0;
				m_uiCurrentAdapter	=	0;

				HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&m_pFactory1) );

				if(m_pFactory1!=NULL){
					IDXGIAdapter1*	pAdapter	=	NULL;
					
					for(;;){
						HRESULT	hr	=	m_pFactory1->EnumAdapters1(m_uiAdapterCount,&pAdapter);
						if(pAdapter==NULL)
							break;
						m_uiAdapterCount++;
						pAdapter->Release();
					}
				}
				else
				{
					hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pFactory) );
					if(m_pFactory!=NULL){
						IDXGIAdapter*	pAdapter	=	NULL;

						for(;;){
							HRESULT	hr	=	m_pFactory->EnumAdapters(m_uiAdapterCount,&pAdapter);
							
							if(pAdapter==NULL)
								break;
							m_uiAdapterCount++;
							pAdapter->Release();
						}
					}
				}

				for(U32	i=0;i<6;i++){
					m_pShaderArray[i]	=	NULL;
				}

				// 					U32	uiAdapterCount	=	vecAdapter.size();
				// 					for(U32	i=0;i<uiAdapterCount;i++){
				// 						pAdapter	=	vecAdapter[i];
				// 						DXGI_ADAPTER_DESC1	desc1;
				// 						pAdapter->GetDesc1(&desc1);
				// 						
				// 						std::vector<IDXGIOutput*>	vecOutput;
				// 						for(U32	j=0;;j++){
				// 							IDXGIOutput*	pOutput=NULL;
				// 							pAdapter->EnumOutputs(j,&pOutput);
				// 							if(pOutput==NULL)
				// 								break;
				// 							vecOutput.push_back(pOutput);
				// 							DXGI_OUTPUT_DESC	oDesc;
				// 							pOutput->GetDesc(&oDesc);
				// // 							UINT	uiModeCount		=	0;
				// // 							UINT	flags         = DXGI_ENUM_MODES_INTERLACED;
				// // 							DXGI_MODE_DESC	mDesc;
				// // 							pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_TYPELESS,flags,&uiModeCount,&mDesc);
				// // 							pOutput->GetDisplayModeList(DXGI_FORMAT_R10G10B10A2_TYPELESS,flags,&uiModeCount,&mDesc);
				// 						}
				// 					}

			}
			Device11::~Device11(){
				SAFE_RELEASE(m_pFactory);
				SAFE_RELEASE(m_pFactory1);
			}
			Air::U1 Device11::Create()
			{
				HRESULT	hr	=	S_OK;
				IDXGIAdapter*	pAdapter	=	NULL;
				if(m_pFactory1!=NULL){
					IDXGIAdapter1*	pAdapter1	=	NULL;
					m_pFactory1->EnumAdapters1(m_uiCurrentAdapter,&pAdapter1);
					pAdapter	=	pAdapter1;
				}else	if(m_pFactory!=NULL){
					m_pFactory->EnumAdapters(m_uiCurrentAdapter,&pAdapter);
				}

				if(pAdapter==NULL)
					return	false;


				UINT createDeviceFlags = 0;
#ifdef _DEBUG
				//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

				D3D_FEATURE_LEVEL featureLevels[] =
				{
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
				};
				HMODULE	h	=	GetModuleHandle(NULL);

				D3D_FEATURE_LEVEL	outLevel	=	D3D_FEATURE_LEVEL_11_0;
#if		(DX_DEVICE_TYPE	==	WARP_DEVICE)
				hr	=	D3D11CreateDevice(	0,
											D3D_DRIVER_TYPE_WARP,
											NULL,
											createDeviceFlags,
											featureLevels,
											3,
											D3D11_SDK_VERSION,
											&m_pDevice,
											&outLevel,
											&m_pContext);
#elif	(DX_DEVICE_TYPE	==	REFERENCE_DEVICE)
				hr	=	D3D11CreateDevice(	0,
					D3D_DRIVER_TYPE_REFERENCE ,
					NULL,
					createDeviceFlags,
					featureLevels,
					3,
					D3D11_SDK_VERSION,
					&m_pDevice,
					&outLevel,
					&m_pContext);
				SAFE_RELEASE(m_pFactory);
				SAFE_RELEASE(m_pFactory1);
				if(m_pDevice!=NULL){
					IDXGIDevice * pDXGIDevice;
					hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

					IDXGIAdapter * pDXGIAdapter;
					hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);
					SAFE_RELEASE(pDXGIDevice);

					pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pFactory);
					SAFE_RELEASE(pDXGIAdapter);
					m_pFactory->QueryInterface(__uuidof(IDXGIFactory1), (void **)&m_pFactory1);
				}

#elif	(DX_DEVICE_TYPE	==	HARDWARE_DEVICE)
				hr	=	D3D11CreateDevice(	pAdapter,
											D3D_DRIVER_TYPE_UNKNOWN ,
											NULL,
											createDeviceFlags,
											featureLevels,
											3,
											D3D11_SDK_VERSION,
											&m_pDevice,
											&outLevel,
											&m_pContext);
#endif

				if(FAILED(hr)){
					return	false;
				}else{
					switch(outLevel){
						case D3D_FEATURE_LEVEL_11_0:{
							m_HWVersion	=	enRSV_11;
						}break;
						case D3D_FEATURE_LEVEL_10_1:{
							m_HWVersion	=	enRSV_10_1;
						}break;
						case D3D_FEATURE_LEVEL_10_0:{
							m_HWVersion	=	enRSV_10;
						}break;
						case D3D_FEATURE_LEVEL_9_3:
						case D3D_FEATURE_LEVEL_9_2:
						case D3D_FEATURE_LEVEL_9_1:{
							m_HWVersion	=	enRSV_9;
						}break;
					}

				}



				
				SAFE_RELEASE(pAdapter);
#ifdef ENABLE_WARP_DEVICE
				IDXGIDevice1 * pDXGIDevice1=NULL;
				hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void **)&pDXGIDevice1);
				if(pDXGIDevice1!=NULL){
					pDXGIDevice1->GetAdapter(&pAdapter);
					SAFE_RELEASE(pDXGIDevice1);
				}else{
					IDXGIDevice*	pDXGIDevice=NULL;
					hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
					if(pDXGIDevice!=NULL){
						pDXGIDevice->GetAdapter(&pAdapter);
					}
					SAFE_RELEASE(pDXGIDevice);
				}
				SAFE_RELEASE(m_pFactory);
				SAFE_RELEASE(m_pFactory1);

				//GetParent
				/**********************
									NULL
									|
								IDXGIFactory
								|			|
					IDXGISwapChain		IDXGIAdapter
						|				|			|
					IDXGISurface	IDXGIOutput	IDXGIDevice
										|			|
								IDXGIResource	IDXGISurface
													|
												IDXGISurface
				**********************/

				pAdapter->GetParent(__uuidof(IDXGIFactory1),(void**)&m_pFactory1);
				if(m_pFactory1==NULL){
					pAdapter->GetParent(__uuidof(IDXGIFactory),(void**)&m_pFactory);
				}
				SAFE_RELEASE(pAdapter);
#endif



				Render::System::GetSingleton()->AddFactory(new ExtraOptionParamFactory<State11,PassStateInfo*>("State"));
				Render::System::GetSingleton()->AddFactory(new ParamFactory<Buffer11>("Buffer"));
				Render::System::GetSingleton()->AddFactory(new NoParamFactory<Shader11>("Shader"));
				Render::System::GetSingleton()->AddFactory(new ParamFactory<VertexDeclare11>("Declare"));
				Render::System::GetSingleton()->AddFactory(new OptionParamFactory<Texture11>("Texture"));
				Render::System::GetSingleton()->AddFactory(new ParamFactory<Window11>("Window"));
				Render::System::GetSingleton()->AddFactory(new ParamFactory<Target11>("Target"));
				
				

				return	true;
			}

			Air::U1 Device11::Destroy()
			{
				Render::System::GetSingleton()->RemoveFactory("Target");
				Render::System::GetSingleton()->RemoveFactory("Window");
				Render::System::GetSingleton()->RemoveFactory("Texture");
				Render::System::GetSingleton()->RemoveFactory("Declare");
				Render::System::GetSingleton()->RemoveFactory("Shader");
				Render::System::GetSingleton()->RemoveFactory("Buffer");
				Render::System::GetSingleton()->RemoveFactory("State");
				if(m_pContext!=NULL){
					
					ID3D11ShaderResourceView*	pSRV[]		={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
					ID3D11Buffer*				pBuffer[]	={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
					ID3D11SamplerState*			pSS[]		={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
					m_pContext->VSSetShader(NULL,NULL,NULL);
					m_pContext->VSSetSamplers(0,8,pSS);
					m_pContext->VSSetShaderResources(0,8,pSRV);
					m_pContext->VSSetConstantBuffers(0,8,pBuffer);
					m_pContext->GSSetShader(NULL,NULL,NULL);
					m_pContext->GSSetSamplers(0,8,pSS);
					m_pContext->GSSetShaderResources(0,8,pSRV);
					m_pContext->GSSetConstantBuffers(0,8,pBuffer);
					m_pContext->PSSetShader(NULL,NULL,NULL);
					m_pContext->PSSetSamplers(0,8,pSS);
					m_pContext->PSSetShaderResources(0,8,pSRV);
					m_pContext->PSSetConstantBuffers(0,8,pBuffer);
					
				}

				SAFE_RELEASE(m_pContext);
				SAFE_RELEASE(m_pDevice);
				
				return	true;

			}

			void* Device11::GetDevice()
			{
				return	m_pDevice;
			}

			void* Device11::GetContext()
			{
				return	m_pContext;
			}

			Air::U32 Device11::GetAdapterCount()
			{
				return	m_uiAdapterCount;
			}

			Air::AString Device11::GetAdapterName( U32 uiAdapterIndex )
			{
				if(m_pFactory1!=NULL){
					DxAdapter1*	pAdapter	=	NULL;
					m_pFactory1->EnumAdapters1(uiAdapterIndex,&pAdapter);
					if(pAdapter!=NULL)
					{
						DXGI_ADAPTER_DESC1	desc1;
						pAdapter->GetDesc1(&desc1);
						pAdapter->Release();
						return	Common::Converter::WideByte2Acsi(desc1.Description);
					}
				}else	if(m_pFactory!=NULL){
					DxAdapter*	pAdapter	=	NULL;
					m_pFactory->EnumAdapters(uiAdapterIndex,&pAdapter);
					if(pAdapter!=NULL)
					{
						DXGI_ADAPTER_DESC	desc;
						pAdapter->GetDesc(&desc);
						pAdapter->Release();
						return	Common::Converter::WideByte2Acsi(desc.Description);
					}
				}
				return	"";
				
			}

			DxFactory1* Device11::GetFactory1()
			{
				return	m_pFactory1;
			}

			DxFactory* Device11::GetFactory()
			{
				return	m_pFactory;
			}

			void Device11::SelectAdapter( U32 uiSelectIndex )
			{
				m_uiCurrentAdapter	=	uiSelectIndex;
			}

			void Device11::SetShader(enumShaderType	type, Shader* pShader )
			{
				void*	pDxShader	=	NULL;
				if(pShader!=NULL)
					pDxShader	=	pShader->GetShader();
				m_pShaderArray[type]	=	pShader;
				switch(type){
					case enVS:{
						if(pDxShader!=NULL)
							m_pContext->VSSetShader((DxVertexShader*)pDxShader,NULL,NULL);
					break;}
					case enGS:{
						m_pContext->GSSetShader((ID3D11GeometryShader*)pDxShader,NULL,NULL);
						break;}
					case enPS:{
						if(pShader!=NULL)
							m_pContext->PSSetShader((DxPixelShader*)pDxShader,NULL,NULL);
						break;}
					case enCS:{
						m_pContext->CSSetShader((ID3D11ComputeShader*)pDxShader,NULL,NULL);
						break;}
					case enHS:{
						m_pContext->HSSetShader((ID3D11HullShader*)pDxShader,NULL,NULL);
						break;}
					case enDS:{
						m_pContext->DSSetShader((ID3D11DomainShader*)pDxShader,NULL,NULL);
						break;}
				}
			}

			Shader* Device11::GetShader( enumShaderType type )
			{
				return	m_pShaderArray[type];
			}

			void Device11::SetVB( U32 uiIndex,Buffer* pBuffer )
			{
				UINT			uiVertexSize	=	pBuffer->GetElementSize();
				UINT			uiOffset		=	0;
				ID3D11Buffer*	pVB				=	(ID3D11Buffer*)pBuffer->GetBuffer();
				m_pContext->IASetVertexBuffers(uiIndex,1,&pVB,&uiVertexSize,&uiOffset);
			}

			void Device11::SetIB( Buffer* pBuffer )
			{
				U32	uiElementSize	=	pBuffer->GetElementSize();
				DXGI_FORMAT	fmt		=	uiElementSize	==	4?DXGI_FORMAT_R32_UINT:DXGI_FORMAT_R16_UINT;
				m_pContext->IASetIndexBuffer((ID3D11Buffer*)pBuffer->GetBuffer(),fmt,0);
			}

			void Device11::SetVD( Vertex::IDeclare* pDeclare )
			{
				ID3D11InputLayout*	pLayout	=	(ID3D11InputLayout*)pDeclare->GetDeclare();
				m_pContext->IASetInputLayout(pLayout);
			}

			void Device11::SetCB( U32 uiIndex,Buffer* pBuffer )
			{
				ID3D11Buffer*	pCB	=	(ID3D11Buffer*)pBuffer->GetBuffer();
				m_pContext->VSSetConstantBuffers(uiIndex,1,&pCB);
				m_pContext->GSSetConstantBuffers(uiIndex,1,&pCB);
				m_pContext->PSSetConstantBuffers(uiIndex,1,&pCB);
			}

			void Device11::SetCB( enumShaderType type,U32 uiIndex,Buffer* pBuffer )
			{
				ID3D11Buffer*	pCB	=	(ID3D11Buffer*)pBuffer->GetBuffer();
				switch(type){
					case enVS:{
						m_pContext->VSSetConstantBuffers(uiIndex,1,&pCB);
						break;}
					case enGS:{
						m_pContext->GSSetConstantBuffers(uiIndex,1,&pCB);
						break;}
					case enPS:{
						m_pContext->PSSetConstantBuffers(uiIndex,1,&pCB);
						break;}
					case enCS:{
						m_pContext->CSSetConstantBuffers(uiIndex,1,&pCB);
						break;}
					case enHS:{
						m_pContext->HSSetConstantBuffers(uiIndex,1,&pCB);
						break;}
					case enDS:{
						m_pContext->DSSetConstantBuffers(uiIndex,1,&pCB);
						break;}

				}
				
				
			}

			void Device11::DrawOpt( const DrawOption& opt )
			{
				__super::DrawOpt(opt);

				m_pContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)opt.m_DrawType);

				switch(opt.m_DrawFuncType){
					case	Draw::FUNC_TYPE_DP		:{
						m_pContext->Draw(opt.m_uiVertexCount,opt.m_uiBaseVertexIndex);
						break;}
					case	Draw::FUNC_TYPE_DIP		:{
						m_pContext->DrawIndexed(opt.m_uiIndexCount,opt.m_uiStartIndex,opt.m_uiBaseVertexIndex);
						break;}
					case	Draw::FUNC_TYPE_DA		:{
						m_pContext->DrawAuto();
						break;}
					case	Draw::FUNC_TYPE_DIP_I	:{
						m_pContext->DrawIndexedInstanced(opt.m_uiIndexCount,opt.m_uiInstanceCount,opt.m_uiStartIndex,opt.m_uiBaseVertexIndex,0);
						break;}
					case	Draw::FUNC_TYPE_DP_I	:{
						m_pContext->DrawInstanced(opt.m_uiVertexCount,opt.m_uiInstanceCount,opt.m_uiBaseVertexIndex,0);
						break;}
				}
			}

			void Device11::SetVP( Viewport* pVP )
			{
				D3D11_VIEWPORT	vp;
				vp.TopLeftX	=	pVP->GetAbsX();
				vp.TopLeftY	=	pVP->GetAbsY();
				vp.Width	=	pVP->GetAbsWidth();
				vp.Height	=	pVP->GetAbsHeight();
				vp.MinDepth	=	0.0f;
				vp.MaxDepth	=	1.0f;
				m_pContext->RSSetViewports(1,&vp);
			}

			void Device11::SetSS( enumShaderType type,U32 uiRegister,State* pState )
			{
				ID3D11SamplerState*	pSS	=		NULL;
				if(pState!=NULL)
					pSS	=		(ID3D11SamplerState*)pState->GetState();
				switch(type){
				case enVS:{
					m_pContext->VSSetSamplers(uiRegister,1,&pSS);
					break;}
				case enGS:{
					m_pContext->GSSetSamplers(uiRegister,1,&pSS);
					break;}
				case enPS:{
					m_pContext->PSSetSamplers(uiRegister,1,&pSS);
					break;}
				case enCS:{
					m_pContext->CSSetSamplers(uiRegister,1,&pSS);
					break;}
				case enHS:{
					m_pContext->HSSetSamplers(uiRegister,1,&pSS);
					break;}
				case enDS:{
					m_pContext->DSSetSamplers(uiRegister,1,&pSS);
					break;}

				}
			}

			void Device11::SetRS( State* pState )
			{
				ID3D11RasterizerState*	pRS	=		NULL;
				if(pState!=NULL)
					pRS	=	(ID3D11RasterizerState*)pState->GetState();
				m_pContext->RSSetState(pRS);
			}

			void Device11::SetDSS( State* pState )
			{
				ID3D11DepthStencilState*	pDSS	=		NULL;
				U32 uiStencilRef	=	0xFFFFFFFF;
				if(pState!=NULL){
					pDSS			=	(ID3D11DepthStencilState*)pState->GetState();
					uiStencilRef	=	pState->m_Info.ds.StencilRef;
				}
				
				m_pContext->OMSetDepthStencilState(pDSS,uiStencilRef);
			}

			void Device11::SetBS( State* pState )
			{
				ID3D11BlendState*	pBS	=	NULL;
				if(pState!=NULL)
					pBS	=	(ID3D11BlendState*)pState->GetState();
				static	Float4	f;
				m_pContext->OMSetBlendState(pBS,(float*)&f,0xFFFFFFFF);
			}

			void Device11::SetSRV( enumShaderType type,U32 uiIndex,void* pSRV )
			{
				ID3D11ShaderResourceView*	pSRV11	=	(ID3D11ShaderResourceView*)pSRV;
				switch(type){
				case enVS:{
					m_pContext->VSSetShaderResources(uiIndex,1,&pSRV11);
					break;}
				case enGS:{
					m_pContext->GSSetShaderResources(uiIndex,1,&pSRV11);
					break;}
				case enPS:{
					m_pContext->PSSetShaderResources(uiIndex,1,&pSRV11);
					break;}
				case enCS:{
					m_pContext->CSSetShaderResources(uiIndex,1,&pSRV11);
					break;}
				case enHS:{
					m_pContext->HSSetShaderResources(uiIndex,1,&pSRV11);
					break;}
				case enDS:{
					m_pContext->DSSetShaderResources(uiIndex,1,&pSRV11);
					break;}

				}
			}

			void Device11::SetUAV( U32 uiCount,void** pUAV )
			{
				ID3D11UnorderedAccessView**	pUAV11	=	(ID3D11UnorderedAccessView**)pUAV;
				m_pContext->CSSetUnorderedAccessViews(0,uiCount,pUAV11,NULL);
			}

			void Device11::SetRTV_DSV( U32 uiCount,void** pRTV,void* pDSV )
			{
				ID3D11RenderTargetView**	pRTV11	=	(ID3D11RenderTargetView**)pRTV;
				m_pContext->OMSetRenderTargets(uiCount,pRTV11,(ID3D11DepthStencilView*)pDSV);
			}

		}
	}
};