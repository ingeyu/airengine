#include "AirRenderTexture9.h"
#include "AirRenderGlobal9.h"
#include "AirRenderSystem9.h"


namespace Air{
	
	namespace	Client{
		namespace	Render{
	
	
			Texture9::Texture9(CAString&	strTextureName,Info*	pInfo)
				:	ITexture(strTextureName,pInfo),
				m_pTexture2D(NULL),
				m_pTextureCube(NULL),
				m_pTexture3D(NULL),
				m_pTextureData(NULL){

					m_pStream	=	NULL;
					m_pSurface	=	NULL;
			}
			U1 Texture9::Create(){

				if(m_Info.format	==	enTFMT_UNKNOWN){
					U32	uiSize	=	GetGlobalSetting().m_pResourceSystem->Find(m_strProductName);
					if(uiSize==0)
						return	false;
					m_pStream	=	GetGlobalSetting().m_pResourceSystem->CreateProduct<Resource::IStream*>(m_strProductName,"Stream");
				}
				return	true;
			}
	
			U1 Texture9::Destroy( ){
				
				SAFE_RELEASE(m_pTexture2D);
				SAFE_RELEASE(m_pTexture3D);
				SAFE_RELEASE(m_pTextureCube);
				SAFE_RELEASE(m_pSurface);

				return	true;
			}
	
			U1 Texture9::SaveToFile( AString strName ){
				
				if(m_pObject!=NULL){
					DxResult	hr	=	S_OK;
					AString	strTextureName	=	strName	+	".dds";
	
					hr	=	D3DXSaveTextureToFileA(	strTextureName.c_str(),
													D3DXIFF_DDS,(DxBaseTexture*)m_pObject,NULL);
	
					if(FAILED(hr)){
						
						return false;
					}
				}
	
				return true;
			}
	
			U1 Texture9::SaveToMemery( MemoryData** ppData ){
	
				
					DxResult	hr		=	S_OK;
					DxBuffer*	pBuff	=	NULL;
					hr	=	D3DXSaveTextureToFileInMemory(&pBuff,D3DXIFF_DDS,(DxBaseTexture*)m_pObject,NULL);
					if(FAILED(hr)){
						return false;
					}
					*ppData	=	new	MemoryData(	(U8*)pBuff->GetBufferPointer(),
												(U32)pBuff->GetBufferSize());
					SAFE_RELEASE(pBuff);
				
	
				return true;
			}
	
			U1 Texture9::Lock( LockRectOption* p,DWORD flag /*= LOCK_DISCARD */ ){
				
// 				if(m_Pool	==	POOL_DEFAULT	&&	m_Info.usage	!=	USAGE_DYNAMIC)
// 					return	false;
// 	
// 				DxTexture*	pTexture	=	GetObjectT<DxTexture*>();
// 				if(pTexture!=NULL){
// 				HRESULT	hr	=	pTexture->LockRect(0,(D3DLOCKED_RECT*)p,NULL,flag);
// 					if(FAILED(hr)){
// 						return	false;
// 					}
// 				}
				return	true;
			}
	
			void Texture9::UnLock(){
	
// 				if(m_Pool	==	POOL_DEFAULT	&&	m_Info.usage	!=	USAGE_DYNAMIC)
// 					return;
// 				DxTexture*	pTexture	=	GetObjectT<DxTexture*>();
// 				if(pTexture!=NULL)
// 					pTexture->UnlockRect(0);
			}
	
			void Texture9::ReCreate( Info& info ){
				
				Destroy();
	
				m_Info	=	info;
	
				Create();
			}
			HDC	Texture9::GetHDC(){
				if(m_pObject==NULL){
					return NULL;
				}
// 				DxTexture*	pTex	=	(DxTexture*)m_pObject;
// 				DxSurface*	pSurface	=	NULL;
// 	
// 				pTex->GetSurfaceLevel(0,&pSurface);
// 	
// 				if(pSurface==NULL){
// 					return;
// 				}
// 				HDC dc;
// 	
// 				pSurface->GetDC(&dc);
// 				pCallback->OnDraw(&dc);
// 				pSurface->ReleaseDC(dc);
// 				SAF_R(pSurface);
				return 0;
			}

			void* Texture9::GetTexture(){

				IDirect3DBaseTexture9*	pOutTexture	=	NULL;

				//如果是从文件加载
				if(m_pStream!=NULL){
					if(m_pStream->GetState()==Resource::enSS_Loaded){
						U32		uiSize	=	m_pStream->GetSize();
						void*	pData	=	m_pStream->GetData();

						D3DXIMAGE_INFO	info;
						D3DXGetImageInfoFromFileInMemory(pData,uiSize,&info);


						m_Info.format	=	(ITexture::enumFormat)info.Format;
						m_Info.width	=	info.Width;
						m_Info.height	=	info.Height;
						m_Info.depth	=	info.Depth;
						m_Info.mipmap	=	info.MipLevels;

						DxDevice*	pDevice	=	GetGlobal().m_pDevice;

						switch(info.ResourceType){
							case	D3DRTYPE_TEXTURE:{
								D3DXCreateTextureFromFileInMemory(pDevice,pData,uiSize,&m_pTexture2D);
								m_pTexture2D->GetSurfaceLevel(0,&m_pSurface);
								pOutTexture	=	m_pTexture2D;
								break;}
							case	D3DRTYPE_CUBETEXTURE:{
								D3DXCreateCubeTextureFromFileInMemory(pDevice,pData,uiSize,&m_pTextureCube);
								pOutTexture	=	m_pTextureCube;
								m_pTextureCube->GetCubeMapSurface((D3DCUBEMAP_FACES)0,0,&m_pSurface);
								break;}
							case	D3DRTYPE_VOLUMETEXTURE:{
								D3DXCreateVolumeTextureFromFileInMemory(pDevice,pData,uiSize,&m_pTexture3D);
								pOutTexture	=	m_pTexture3D;
								//m_pTexture3D->GetVolumeLevel()
								break;}
						}

						m_pStream->PushRecycle();
						m_pStream	=	NULL;

						return	pOutTexture;

					}
					
				}else{
					if(			m_pTexture2D	!=	NULL	){
						pOutTexture	=	m_pTexture2D;
					}else if(	m_pTextureCube	!=	NULL	){
						pOutTexture	=	m_pTextureCube;
					}else if(	m_pTexture3D	!=	NULL	){
						pOutTexture	=	m_pTexture3D;
					}

// 					if(pOutTexture==NULL){
// 						GetSurface();
// 					}
				}
				return	pOutTexture;
			}

			void* Texture9::GetSurface(enumCubeFaceType	uiFaceType){
				if(m_pSurface!=NULL){
					return	m_pSurface;
				}

				System*	pSys				=	static_cast<System*>(m_pFactoryMgr);
				IDirect3DDevice9*	pDevice	=	pSys->GetDevice();

				const static
					DWORD	usage[]	=	{	0,
					D3DUSAGE_RENDERTARGET,
					D3DUSAGE_DYNAMIC,
					0,
					0};
				const static
					D3DPOOL	pool[]	=	{	D3DPOOL_DEFAULT,
					D3DPOOL_DEFAULT,
					D3DPOOL_DEFAULT,
					D3DPOOL_MANAGED,
					D3DPOOL_SYSTEMMEM};

				DWORD		dwUsage		=	usage[m_Info.usage];
				D3DPOOL		dwPool		=	pool[m_Info.usage];
				D3DFORMAT	format		=	D3DFMT_A8R8G8B8;

				U32&	uiWidth		=	m_Info.width;
				U32&	uiHeight	=	m_Info.height;
				U32&	uiDepth		=	m_Info.depth;
				if(m_Info.fScreenScale	>	0.0f){
					uiWidth		=	m_Info.fScreenScale*pSys->m_uiMainWindowWidth;
					uiHeight	=	m_Info.fScreenScale*pSys->m_uiMainWindowHeight;
				}


				//从内存创建
				DxResult	hr	=	S_OK;
				switch(m_Info.type){
				case	enTexture1D:
				case	enTexture2D:{
					if(m_pTexture2D==NULL){
						hr	=	D3DXCreateTexture(	pDevice,
							uiWidth,
							uiHeight,
							m_Info.mipmap,
							dwUsage,
							format,
							dwPool,
							&m_pTexture2D);
					}
					m_pTexture2D->GetSurfaceLevel(0,&m_pSurface);

					break;}
				case	enTexture3D:{
					if(m_pTexture3D==NULL){
						hr	=	D3DXCreateVolumeTexture(	pDevice,
							uiWidth,
							uiHeight,
							uiDepth,
							m_Info.mipmap,
							dwUsage,
							format,
							dwPool,
							&m_pTexture3D);
					}

					break;}
				case	enTextureCUBE:{
					if(m_pTextureCube==NULL){

						hr	=	D3DXCreateCubeTexture(	pDevice,
							uiWidth,
							m_Info.mipmap,
							dwUsage,
							format,
							dwPool,
							&m_pTextureCube);
					}
					break;}		
				}
				return	m_pSurface;
			}
			void Texture9::OnLostDevice()
			{
				if(	m_Info.usage	==	enUSAGE_RENDERTARGET	||
					m_Info.usage	==	enUSAGE_DEFAULT)
				{
					Destroy();
				}
				
			}

			void Texture9::OnResetDevice()
			{

			}

			Texture9Factory::Texture9Factory(){
				m_strTypeName	=	"Texture";
			}
	
			IProduct* Texture9Factory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){

				if(lstParam==NULL)
					return	NULL;
				Texture::Info*	pInfo	=	(Texture::Info*)lstParam;
				Texture9*	pTexture	=	new	Texture9(strName,pInfo);
	
				return pTexture;
			}
		}
	}
};