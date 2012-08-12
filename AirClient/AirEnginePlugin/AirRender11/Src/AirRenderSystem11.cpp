#include "AirRenderSystem11.h"
#include "AirRenderGlobal11.h"
#include "AirEngineSceneNode.h"
#include "AirCommonMath.h"

//工厂类
#include "AirRenderTexture11.h"
#include "AirRenderVertexBuffer11.h"
#include "AirRenderIndexBuffer11.h"
#include "AirRenderShader11.h"
#include "AirEngineMaterial.h"

#include "AirRenderTarget11.h"
#include "AirRenderWindow11.h"

namespace Air{
	
	namespace	Client{
		namespace	Render{

			D3DCULL	AirCull_To_Cull9(enumCullMode	val){
				switch(val){
					case	enCM_NONE:	return	D3DCULL_NONE;
					case	enCM_CW:	return	D3DCULL_CW;
					case	enCM_CCW:	return	D3DCULL_CCW;
				}
				return	D3DCULL_CCW;
			};
			D3DFILLMODE	AirFillMode_To_Fill9(enumFillMode	val){
				switch(val){
					case	enFM_POINT:		return	D3DFILL_POINT;
					case	enFM_WIREFRAME:	return	D3DFILL_WIREFRAME;
					case	enFM_SOILD:		return	D3DFILL_SOLID;
				}
				return	D3DFILL_SOLID;
			};
			D3DCMPFUNC	AirCmpFunc_To_Cmp9(enumCompare	val){
				switch(val){
					case	enC_ALWAYS_FAIL:	return	D3DCMP_NEVER;
					case	enC_ALWAYS_PASS:	return	D3DCMP_ALWAYS;
					case	enC_LESS:			return	D3DCMP_LESS;
					case	enC_LESS_EQUAL:		return	D3DCMP_LESSEQUAL;
					case	enC_EQUAL:			return	D3DCMP_EQUAL;
					case	enC_NOT_EQUAL:		return	D3DCMP_NOTEQUAL;
					case	enC_GREATER_EQUAL:	return	D3DCMP_GREATEREQUAL;
					case	enC_GREATER:		return	D3DCMP_GREATER;
				}
				return	D3DCMP_ALWAYS;
			};
			D3DSTENCILOP	AirStencilOP_To_Op9(enumStencileOP	val){
				switch(val){
					case	enSOP_KEEP:		return	D3DSTENCILOP_KEEP;
					case	enSOP_ZERO:		return	D3DSTENCILOP_ZERO;
					case	enSOP_REPLACE:	return	D3DSTENCILOP_REPLACE;
					case	enSOP_INCR_SAT:	return	D3DSTENCILOP_INCRSAT;
					case	enSOP_DECR_SAT:	return	D3DSTENCILOP_DECRSAT;
					case	enSOP_INVERT:	return	D3DSTENCILOP_INVERT;
					case	enSOP_INCR:		return	D3DSTENCILOP_INCR;
					case	enSOP_DECR:		return	D3DSTENCILOP_DECR;
				}

				return	D3DSTENCILOP_KEEP;
			};
			D3DBLENDOP		AirBlendOp_To_BlendOp9(enumBlendOP	val){
				switch(val){
					case	enBOP_ADD:			return	D3DBLENDOP_ADD;
					case	enBOP_SUBTRACT:		return	D3DBLENDOP_SUBTRACT;
					case	enBOP_REV_SUBTRACT:	return	D3DBLENDOP_REVSUBTRACT;
					case	enBOP_MIN:			return	D3DBLENDOP_MIN;
					case	enBOP_MAX:			return	D3DBLENDOP_MAX;
				}
				return	D3DBLENDOP_ADD;
			};
			D3DBLEND		AirBlend_To_Blend9(enumBlend	val){
				switch(val){
					case	enB_ZERO:				return	D3DBLEND_ZERO;
					case	enB_ONE:				return	D3DBLEND_ONE;
					case	enB_SRC_COLOR:			return	D3DBLEND_SRCCOLOR;
					case	enB_INV_SRC_COLOR:		return	D3DBLEND_INVSRCCOLOR;
					case	enB_SRC_ALPHA:			return	D3DBLEND_SRCALPHA;
					case	enB_INV_SRC_ALPHA:		return	D3DBLEND_INVSRCALPHA;
					case	enB_DEST_ALPHA:			return	D3DBLEND_DESTALPHA;
					case	enB_INV_DEST_ALPHA:		return	D3DBLEND_INVDESTALPHA;
					case	enB_DEST_COLOR:			return	D3DBLEND_DESTCOLOR;
					case	enB_INV_DEST_COLOR:		return	D3DBLEND_INVDESTCOLOR;
					case	enB_SRC_ALPHA_SAT:		return	D3DBLEND_SRCALPHASAT;
					case	enB_BLEND_FACTOR:		return	D3DBLEND_BLENDFACTOR;
					case	enB_INV_BLEND_FACTOR:	return	D3DBLEND_INVBLENDFACTOR;
					case	enB_SRC1_COLOR:			return	D3DBLEND_SRCCOLOR;
					case	enB_INV_SRC1_COLOR:		return	D3DBLEND_INVSRCCOLOR;
					case	enB_SRC1_ALPHA:			return	D3DBLEND_SRCALPHA;
					case	enB_INV_SRC1_ALPHA:		return	D3DBLEND_INVSRCALPHA;
				}
				return	D3DBLEND_ONE;
			};



	
	
	
			System::System():ISystem("RenderSystem"){

				m_strName		=	"DirectX11 RenderSystem";
				m_bNeedReset	=	false;
				//m_pD3D			=	NULL;
				m_pDevice		=	NULL;
				GetGlobalSetting().m_pRenderSystem	=	this;
			}
	
			System::~System(){

				
			}

	
			void System::OnD3DResetDevice( void* pd3dDevice, const void* pBackBufferSurfaceDesc,void* pUserContext ,void*	pSwapChain){
				//GetGlobal().OnD3DResetDevice(pd3dDevice,pBackBufferSurfaceDesc,pUserContext,pSwapChain);
	
				FactoryMapItr	i	=	m_mapFactory.begin();
				for(;i!=m_mapFactory.end();i++){
					Factory*	pFactory	=	dynamic_cast<Factory*>(i->second);
					if(pFactory!=NULL){
						pFactory->OnResetDevice();
					}
				}
			}
	
			void System::OnD3DLostDevice( void* pUserContext ){
				FactoryMapItr	i	=	m_mapFactory.begin();
				for(;i!=m_mapFactory.end();i++){
					Factory*	pFactory	=	dynamic_cast<Factory*>(i->second);
					if(pFactory!=NULL){
						pFactory->OnLostDevice();
					}
				}
			}
	
			U1 System::Initialization(){
				RENDER_LOG_INFO;
				//添加工厂到工厂管理器
				AddFactory(new	Texture9Factory());
				AddFactory(new	Vertex::Declare9Factory());
				AddFactory(new	ParamFactory<Vertex::Buff9>("VertexBuffer"));
				AddFactory(new	ParamFactory<Index::Buff>("IndexBuffer"));
				AddFactory(new	Shader9Factory());
				//AddFactory(new	EffectFactory(),		this);
				//AddFactory(new	MaterialFactory(),		this);
				AddFactory(new	TextFactory());
				//AddFactory(new	XObjectFactory(),		this);
				AddFactory(new	Target9Factory());
				AddFactory(new	ParamFactory<Window9>("Window"));
				
	
				//StartThread();
				return	true;
			}	
	
			U1 System::Release(){
				RENDER_LOG_INFO;
	
	
				DestroyAllProduct();
	
	
				//StartThread();
				//StopThreadWaitForExit();
				return	true;
			}
	
			bool System::Start(){
				
				return	true;//StartThread();//DXUT::Start();
			}
			Air::U1 System::SetVertexDeclare( VertexDeclare* pDeclare ){
				if(ISystem::SetVertexDeclare(pDeclare)){
					SetVertexDeclaration((DxVertexDeclare*)pDeclare->GetDeclare());
				}
				return	true;
			}

			U1 System::SetVertexBuffer( VertexBuffer* pBuffer ){
				if(ISystem::SetVertexBuffer(pBuffer)){
					if(pBuffer==NULL){
						SetStreamSource(0,NULL,0,12);
					}else{
						U32	uiVertexSize		=	pBuffer->GetElementSize();
						DxVertexBuff*	pVB		=	(DxVertexBuff*)pBuffer->GetBuffer();
						SetStreamSource(0,pVB,0,uiVertexSize);
					}
				}
				return	true;
			}
	
			U1 System::SetIndexBuffer( IndexBuffer* pBuffer ){
				if(ISystem::SetIndexBuffer(pBuffer)){
					if(pBuffer==NULL){
						SetIndices(NULL);
					}else{
						SetIndices((DxIndexBuff*)pBuffer->GetBuffer());
					}
				}
	
				return	true;
			}
	
			U1 System::SaveScreenToFile( CAString& strName ){
				GetGlobal().m_pRenderDevice->SetNeedSaveScreen(strName);
				return	true;
			}
	
			U1 System::SetFullScreen(){
				GetGlobal().m_pRenderDevice->SetNeedFullScreen();
				return	true;
			}
	
			void System::SetVertexInstance(Vertex::IBuff* pBuff,Vertex::IBuff* pInstanceBuff,UInt uiInstanceCount){
	
// 				//获取DX设备指针
// 				DxDevice*	pd3dDevice	=	GetGlobal().m_pDevice;
// 				//如果实体个数为0 则设置流为空
// 				if(uiInstanceCount==0){
// 	
// 					( pd3dDevice->SetStreamSourceFreq( 0, 1 ) );
// 					( pd3dDevice->SetStreamSourceFreq( 1, 1 ) );
// 	
// 					return;
// 				}
// 	
// 				//判断缓冲是否为空
// 				if(pBuff	==	NULL	||	pInstanceBuff	==	NULL)
// 					return;
// 	
// 				//获取模型顶点缓冲数据
// 				Vertex::Buff*	p	=	dynamic_cast<Vertex::Buff*>(pBuff);
// 				DxVertexBuff*	pVertexBuff	=	p->GetObjectT<DxVertexBuff*>();
// 	
// 	
// 				//设置模型顶点缓冲
// 				( pd3dDevice->SetStreamSource( 0, pVertexBuff, 0, pBuff->GetVertexSize() ) );
// 				( pd3dDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | uiInstanceCount ) );
// 	
// 				//获取实体顶点缓冲数据
// 				p	=	dynamic_cast<Vertex::Buff*>(pInstanceBuff);
// 				pVertexBuff	=	p->GetObjectT<DxVertexBuff*>();
// 	
// 				//设置实体顶点缓冲
// 				( pd3dDevice->SetStreamSource( 1, pVertexBuff, 0, pInstanceBuff->GetVertexSize() ) );
// 				( pd3dDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1ul ) );
	
			}
	
			U1 System::UpdataSurface( ITexture* pSrcTexture,RECT* rect,ITexture* pDstTexture,POINT& p ){
				if(GetGlobal().m_bReseting)
					return	false;
	
				Texture*	pSrc	=	dynamic_cast<Texture*>(pSrcTexture);
				Texture*	pDst	=	dynamic_cast<Texture*>(pDstTexture);
				if(pSrc==NULL	||	pDst==NULL)
					return	false;
				DxTexture*	pSrcTex	=	pSrc->GetObjectT<DxTexture*>();
				DxTexture*	pDstTex	=	pDst->GetObjectT<DxTexture*>();
				if(pSrcTex==NULL	||	pDstTex==NULL)
					return	false;
	
				DxSurface*	pSrcSurface	=	NULL;
				DxSurface*	pDstSurface	=	NULL;
	
				pSrcTex->GetSurfaceLevel(0,&pSrcSurface);
				pDstTex->GetSurfaceLevel(0,&pDstSurface);
	
				if(pSrcSurface==NULL	||	pDstSurface==NULL)
					return	false;
	
				GetGlobal().m_pDevice->UpdateSurface(pSrcSurface,rect,pDstSurface,&p);
				
	
				SAF_R(pSrcSurface);
				SAF_R(pDstSurface);
	
				return	true;
			}
	
			bool System::Stop(){
				return	true;
			}
	
			bool System::RepetitionRun(){
				Device9::Info	info	=	GetGlobalSetting().m_DisplayParam;
				Device9*&	pDevice	=	GetGlobal().m_pRenderDevice;
				pDevice	=	new	Device9(&info);
				pDevice->Create();
	
				MSG msg;
				::ZeroMemory(&msg, sizeof(MSG));
	
				SetCursor(LoadCursor(0, IDC_ARROW));
	
				while(!m_bExit){
					while(!m_bPause){
	
						if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
							::TranslateMessage(&msg);
							::DispatchMessage(&msg);
						}else{	
							pDevice->RenderOneFrame();
						}
						m_bHasPause	=	false;
						if(msg.message	==	WM_QUIT){
							GetGlobalSetting().m_bQuit	=	true;
							m_bPause	=	true;
						}
					}
					m_bHasPause	=	true;
					Sleep(10);
				}
	
				pDevice->Destroy();
				SAF_D(pDevice);
	
				return	true;
			}
	
			U1 System::ChangeSize(){
				//StopThreadWaitForExit();
				//GetGlobal().m_pRenderDevice->ChangeSize();
				//StartThread();
				return	true;
			}
	
			U1 System::IsNeedReset(){
				return	m_bNeedReset;
			}
	
			U1 System::Reset(){
				//GetGlobal().m_pRenderDevice->ChangeSize();
				//m_bNeedReset	=	false;
				//StartThread();
				return	true;
			}
	
			void System::SetNeedReset(){
				m_bNeedReset	=	true;
			}

			IDirect3D9* System::GetD3D(){
				if(m_pD3D==NULL){
					m_pD3D	=	Direct3DCreate9(D3D_SDK_VERSION);
				}
				return	m_pD3D;
			}

			Air::U1 System::SetTexture( enumShaderType type,U32 uiRegister,ITexture* pTexture ){
				DxBaseTexture*	pTex	=	NULL;
				if(pTexture!=NULL){
					pTex	=	(DxBaseTexture*)pTexture->GetShaderResourceView();
				}
				switch(type){
					case	enVS:{
						StateManager::SetTexture(D3DVERTEXTEXTURESAMPLER0+uiRegister,pTex);
						break;}
					case	enPS:{
						StateManager::SetTexture(uiRegister,pTex);
						break;}
				}
				return	true;
			}

			Air::U1 System::SetShader( Render::enumShaderType type,IShader* pShader ){
				IDirect3DVertexShader9*	pVS	=	NULL;
				IDirect3DPixelShader9*	pPS	=	NULL;
				if(type	==	enVS){
					if(pShader!=NULL){
						pVS	=	(DxVertexShader*)pShader->GetShader();
					}
					SetVertexShader(pVS);
				}else{
					if(pShader!=NULL){
						pPS	=	(DxPixelShader*)pShader->GetShader();
					}
					SetPixelShader(pPS);
				}
				return	true;
			}

			Air::U1 System::SetRasterizerState( IRasterizerState* pState ){
				if(ISystem::SetRasterizerState(pState)){
					RASTERIZER_DESC&	desc	=	m_pRS->m_pInfo->rs;
					SetRenderState(D3DRS_CULLMODE,				AirCull_To_Cull9(desc.CullMode));
					SetRenderState(D3DRS_FILLMODE,				AirFillMode_To_Fill9(desc.FillMode));
					SetRenderState(D3DRS_DEPTHBIAS,				desc.DepthBias);
					SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS,	desc.SlopeScaledDepthBias);
					SetRenderState(D3DRS_ANTIALIASEDLINEENABLE,	desc.AntialiasedLineEnable);
					SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,	desc.MultisampleEnable);
					SetRenderState(D3DRS_SCISSORTESTENABLE,		desc.ScissorEnable);
				}
				return	true;
			}

			Air::U1 System::SetDepthStencilState( IDepthStencilState* pState ){
				if(ISystem::SetDepthStencilState(pState)){
					DEPTH_STENCIL_DESC&	desc	=	m_pDS->m_pInfo->ds;
					SetRenderState(D3DRS_ZENABLE,				desc.DepthEnable);
					SetRenderState(D3DRS_ZWRITEENABLE,			desc.DepthWriteMask!=0);
					if(desc.DepthEnable)
						SetRenderState(D3DRS_ZFUNC,				AirCmpFunc_To_Cmp9(desc.DepthFunc));
					SetRenderState(D3DRS_STENCILENABLE,			desc.StencilEnable);
					if(desc.StencilEnable>0){
						SetRenderState(D3DRS_STENCILFAIL,		AirStencilOP_To_Op9(desc.FrontFace.StencilFailOp));
						SetRenderState(D3DRS_STENCILPASS,		AirStencilOP_To_Op9(desc.FrontFace.StencilPassOp));
						SetRenderState(D3DRS_STENCILFUNC,		AirCmpFunc_To_Cmp9(desc.FrontFace.StencilFunc));
						SetRenderState(D3DRS_STENCILZFAIL,		AirStencilOP_To_Op9(desc.FrontFace.StencilDepthFailOp));
						SetRenderState(D3DRS_STENCILMASK,		desc.StencilReadMask);
						SetRenderState(D3DRS_STENCILWRITEMASK,	desc.StencilWriteMask);	
					}
					
					if(desc.StencilEnable	==2){
						SetRenderState(D3DRS_TWOSIDEDSTENCILMODE,	TRUE);
						SetRenderState(D3DRS_CCW_STENCILFAIL,		AirStencilOP_To_Op9(desc.BackFace.StencilFailOp));
						SetRenderState(D3DRS_CCW_STENCILZFAIL,		AirStencilOP_To_Op9(desc.BackFace.StencilDepthFailOp));
						SetRenderState(D3DRS_CCW_STENCILPASS,		AirStencilOP_To_Op9(desc.BackFace.StencilPassOp));
						SetRenderState(D3DRS_CCW_STENCILFUNC,		AirCmpFunc_To_Cmp9(desc.BackFace.StencilFunc));
					}else{
						SetRenderState(D3DRS_TWOSIDEDSTENCILMODE,	FALSE);
					}
				}
				return	true;
			}

			Air::U1 System::SetBlendState( IBlendState* pState ){
				if(ISystem::SetBlendState(pState)){
					BLEND_DESC&	desc			=	m_pBS->m_pInfo->bs;
					RENDER_TARGET_BLEND&	b	=	desc.Blend[0];
					SetRenderState(D3DRS_ALPHATESTENABLE,	desc.AlphaToCoverageEnable);
					SetRenderState(D3DRS_ALPHABLENDENABLE,	b.BlendEnable);
					if(b.BlendEnable){
						SetRenderState(D3DRS_BLENDOP,		AirBlendOp_To_BlendOp9(b.BlendOp));
						SetRenderState(D3DRS_SRCBLEND,		AirBlend_To_Blend9(b.SrcBlend));
						SetRenderState(D3DRS_DESTBLEND,		AirBlend_To_Blend9(b.DestBlend));
						SetRenderState(D3DRS_SRCBLENDALPHA,	AirBlend_To_Blend9(b.SrcBlendAlpha));
						SetRenderState(D3DRS_DESTBLENDALPHA,AirBlend_To_Blend9(b.DestBlendAlpha));
						SetRenderState(D3DRS_BLENDOPALPHA,	AirBlendOp_To_BlendOp9(b.BlendOpAlpha));
					}
					SetRenderState(D3DRS_COLORWRITEENABLE,	b.RenderTargetWriteMask);
				}
				return	true;
			}

			Air::U1 System::DrawOpt( const DrawOption& opt )
			{
				IDirect3DDevice9*	pDev		=	GetGlobal().m_pDevice;
				D3DPRIMITIVETYPE	drawType	=	(D3DPRIMITIVETYPE)opt.m_DrawType;

				if(opt.m_uiInstanceCount!=0){
					SetStreamSourceFreq(	0,	D3DSTREAMSOURCE_INDEXEDDATA		| opt.m_uiInstanceCount);
					SetStreamSourceFreq(	1,	D3DSTREAMSOURCE_INSTANCEDATA	| 1ul );
				}

				switch(opt.m_DrawFuncType){
					case	Draw::FUNC_TYPE_DP:{
						pDev->DrawPrimitive(drawType,
											opt.m_uiBaseVertexIndex,
											opt.m_uiFaceCount);
						break;}
					case	Draw::FUNC_TYPE_DIP:{
						pDev->DrawIndexedPrimitive(drawType,
													opt.m_uiBaseVertexIndex,
													0,
													opt.m_uiVertexCount,
													opt.m_uiStartIndex,
													opt.m_uiFaceCount);
						break;}
				}
				if(opt.m_uiInstanceCount!=0){
					SetStreamSourceFreq(0,1);
					SetStreamSourceFreq(1,1);
				}
				return	true;
			}

			Air::U1 System::SetConstantBuffer( enumShaderType type,IConstantBuffer* pBuffer )
			{
				if(pBuffer==NULL)
					return	false;

				enumConstantBufferType	cbType	=	pBuffer->GetType();

				const static	U32	uiRegister[6]	=	{
					0,
					6,
					15,
					19,
					30,
					19
				};

				U32	uiRegisterStart	=	uiRegister[cbType];

				if(type	==	enVS){
					SetVertexShaderConstantF(uiRegisterStart,(float*)pBuffer->GetBuffer(),pBuffer->GetSize());
				}else{
					SetPixelShaderConstantF(uiRegisterStart,(float*)pBuffer->GetBuffer(),pBuffer->GetSize());
				}
				return	true;
			}

			Air::U1 System::SetConstantBuffer( IConstantBuffer* pBuffer )
			{
				if(pBuffer==NULL)
					return	false;

				enumConstantBufferType	cbType	=	pBuffer->GetType();

				const static	U32	uiRegister[6]	=	{
					0,
					6,
					15,
					19,
					30,
					19
				};

				U32	uiRegisterStart	=	uiRegister[cbType];

				SetVertexShaderConstantF(uiRegisterStart,(float*)pBuffer->GetBuffer(),pBuffer->GetSize());
				SetPixelShaderConstantF(uiRegisterStart,(float*)pBuffer->GetBuffer(),pBuffer->GetSize());

				return	true;
			}

		}
	}
};