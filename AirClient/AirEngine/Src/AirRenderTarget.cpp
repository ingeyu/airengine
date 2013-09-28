#include "AirRenderTarget.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirEngineCamera.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{


			Target::Info::Info(){
				extraDepth	=	NULL;
				depthFormat	=	enTFMT_D24_UNORM_S8_UINT;
				bUseDepth	=	false;
				clearColor	=	Float4(0,0,0,0);

				extraWnd	=	NULL;
				parentWnd	=	NULL;
				bFullScreen	=	false;
			}

			void Target::Info::SetSingleTarget( UInt uiWidth, UInt uiHeight, TFormat fmt, U1 bDepth /*= false*/, Target* pExtraTarget /*= NULL*/ ){
				vecTextureInfo.resize(1);
				vecTextureInfo[0].SetRenderToTexture(uiWidth,uiHeight,fmt);
				bUseDepth	=	bDepth;
				extraDepth	=	pExtraTarget;
				vecTextureInfo[0].SetViewFlag(enVF_SRV|enVF_RTV);
			}

			void Target::Info::SetSingleTargetScreen( TFormat fmt, float		fScale,U1 bDepth /*= false*/, Target* pExtraTarget /*= NULL*/ ){
				vecTextureInfo.resize(1);
				vecTextureInfo[0].SetRenderToTexture(fScale,fmt);
				bUseDepth	=	bDepth;
				extraDepth	=	pExtraTarget;
				vecTextureInfo[0].SetViewFlag(enVF_SRV|enVF_RTV);
			}

			void Target::Info::SetMutilTarget( UInt uiWidth, UInt uiHeight, UInt uiNumTarget, TFormat* pFmtArray, U1 bDepth /*= false*/, Target* pExtraTarget /*= NULL*/ ){
				if(pFmtArray==NULL)
					return;
				if(uiNumTarget==0)
					return;

				vecTextureInfo.resize(uiNumTarget);
				for(UInt i=0;i<uiNumTarget;i++){
					vecTextureInfo[i].SetRenderToTexture(uiWidth,uiHeight,pFmtArray[i]);
					vecTextureInfo[i].SetViewFlag(enVF_SRV|enVF_RTV);
				}
				bUseDepth	=	bDepth;
				extraDepth	=	pExtraTarget;
			}

			void Target::Info::SetMutilTargetScreen( UInt uiNumTarget, TFormat* pFmtArray,float fScale,U1 bDepth /*= false*/, Target* pExtraTarget /*= NULL*/ ){
				if(pFmtArray==NULL)
					return;

				vecTextureInfo.resize(uiNumTarget);
				for(UInt i=0;i<uiNumTarget;i++){
					vecTextureInfo[i].SetRenderToTexture(fScale,pFmtArray[i]);
					vecTextureInfo[i].SetViewFlag(enVF_SRV|enVF_RTV);
				}
				bUseDepth	=	bDepth;
				extraDepth	=	pExtraTarget;
			}

			void Target::Info::SetRenderWindow( U32 uiWidth, U32 uiHeight, U1 bWindow /*= true*/, HWND parentWindow /*= NULL*/, HWND extraWindow /*= NULL*/ )
			{
				bFullScreen	=	!bWindow;
				vecTextureInfo.resize(1);
				vecTextureInfo[0].SetRenderToTexture(uiWidth,uiHeight);
				parentWnd	=	parentWindow;
				extraWnd	=	extraWindow;

			}
			AString Target::ProductTypeName="RenderTarget";
			Target::Target( CAString& strName, Info* pInfo ):IProduct(strName)
			{
				if(pInfo!=NULL){
					m_Info	=	*pInfo;
				}
				m_ClearFlag	=	0;
				m_bActive	=	true;
			}

			void Target::AddPhaseFlag( enumPhaseIndex uiPhaseIndex ){
				m_PhaseOpt.AddIndex(uiPhaseIndex);
			}

			void Target::RemovePhaseFlag( enumPhaseIndex uiPhaseIndex ){
				m_PhaseOpt.RemoveIndex(uiPhaseIndex);
			}

			Air::U32 Target::GetPhaseFlag(){
				return	m_PhaseOpt.flag;
			}

			void Target::ClearPhaseFlag(){
				m_PhaseOpt.Clear();
			}

			Air::U1 Target::Create(){

				if(m_Info.vecTextureInfo.empty())
					return	false;

				System*	pSys	=	Render::System::GetSingleton();

				U32	uTargetCount	=	m_Info.vecTextureInfo.size();
				if(uTargetCount>0)
					m_vecTexture.resize(uTargetCount);
				for(U32	i=0;i<uTargetCount;i++){

					AString	strTargetName	=	m_strProductName;
					if(uTargetCount	>	1){
						strTargetName	=	m_strProductName+Converter::ToString(i);
					}
					m_vecTexture[i]	=	pSys->CreateProduct<Texture>(strTargetName,&m_Info.vecTextureInfo[i]);
				}
				if(m_Info.extraDepth!=NULL	&&	m_Info.bUseDepth){
					m_Info.extraDepth->AddRef();
				}
				return	true;
			}

			Air::U1 Target::Destroy(){
				if(m_Info.extraDepth!=NULL	&&	m_Info.bUseDepth){
					m_Info.extraDepth->ReleaseRef();
				}
				System*	pSys	=	Render::System::GetSingleton();

				U32	uTargetCount	=	m_vecTexture.size();
				for(U32	i=0;i<uTargetCount;i++){
					m_vecTexture[i]->ReleaseRef();
				}
				m_vecTexture.clear();

				RemoveAllViewport();
				return	true;
			}

			Air::U32 Target::GetWidth(){
				return	m_vecTexture[0]->GetWidth();
			}	

			Air::U32 Target::GetHeight(){
				return	m_vecTexture[0]->GetHeight();
			}

			Air::U32 Target::GetDepth(){
				return	m_vecTexture[0]->GetDepth();
			}

			void Target::SetActive( U1 bActive ){
				m_bActive	=	bActive;
			}

			Air::U1 Target::IsAvtive(){
				return	m_bActive;
			}

			Air::U1 Target::Update(){
				Render::System*	pSys	=	Render::System::GetSingleton();

				if(BeforeUpdate()){

					Viewport*	pVP	=	NULL;
					ViewportMap::iterator	i	=	m_mapViewport.begin();
					for(;i!=m_mapViewport.end();i++){
						pVP	=	i->second;
						pSys->GetDevice()->SetVP(pVP->GetAbsX(),pVP->GetAbsY(),pVP->GetAbsWidth(),pVP->GetAbsHeight());
						pVP->Update();
						pSys->RenderPhase(m_PhaseOpt);
					}
					AfterUpdate();
				}

				return	true;
			}

			Air::U1 Target::BeforeUpdate(U32	uiFace){
				Render::System*	pSys	=	Render::System::GetSingleton();

				pSys->ClearPhaseFlag();
				pSys->SetPhaseOption(m_PhaseOpt);

				return	true;
			}

			Air::U1 Target::AfterUpdate(U1 bSwapBuffer){

				return	true;
			}

			Viewport* Target::AddCamera( Camera* pCamera, U32 uiZOrder /*= 0*/, Real x /*= 0.0f*/, Real y /*= 0.0f*/, Real w /*= 0.0f*/, Real h /*= 0.0f*/ ){
				if(pCamera	==	NULL)
					return	NULL;

				pCamera->AddPhaseFlag(m_PhaseOpt.flag);

				ViewportMap::iterator	i	=	m_mapViewport.find(uiZOrder);
				if(i!=m_mapViewport.end()){
					SAF_D(i->second);
				}
				Viewport*	pVP	=	new	Viewport(w,h,x,y);
				pVP->SetTarget(this);
				pVP->SetCamera(pCamera);
				m_mapViewport[uiZOrder]	=	pVP;
				return	pVP;
				
			}

			void Target::RemoveViewport( U32 uiZOrder ){
				ViewportMap::iterator	i	=	m_mapViewport.find(uiZOrder);
				if(i!=m_mapViewport.end()){
					SAF_D(i->second);
					m_mapViewport.erase(i);
				}
			}

			void Target::AddViewport( Viewport* pVP, U32 uiZOrder /*= 0*/ ){
				if(pVP==NULL)
					return;

				ViewportMap::iterator	i	=	m_mapViewport.find(uiZOrder);
				if(i!=m_mapViewport.end()){
					SAF_D(i->second);
				}
				//pVP->m_pCamera	=	NULL;
				m_mapViewport[uiZOrder]	=	pVP;
			}

			void Target::RemoveAllViewport(){
				ViewportMap::iterator	i	=	m_mapViewport.begin();
				for(;i!=m_mapViewport.end();i++){
					SAF_D(i->second);
				}
				m_mapViewport.clear();
			}

			void Target::SetUseExtraDepth( Target* pTarget ){
				if(m_Info.extraDepth!=NULL)
					m_Info.extraDepth->ReleaseRef();
				m_Info.extraDepth	=	pTarget;
				if(m_Info.extraDepth!=NULL){
					m_Info.extraDepth->AddRef();
					m_Info.bUseDepth	=	true;
				}else{
					m_Info.bUseDepth	=	false;
				}
			}

			void Target::AddClearFlag( enumTargetClearFlag flag ){
				m_ClearFlag	|=	flag;
			}

			void Target::RemoveClearFlag( enumTargetClearFlag flag ){
				m_ClearFlag	^=	flag;
			}

			void Target::SetClearFlag( U32 flag ){
				m_ClearFlag	=	flag;
			}

			void Target::SetClearFlag( U1 bClearStencil,U1 bClearTarget,U1 bClearZBuffer ){
				m_ClearFlag	=	0;
				if(bClearStencil)
					m_ClearFlag	|=	enTCF_STENCIL;
				if(bClearTarget)
					m_ClearFlag	|=	enTCF_TARGET;
				if(bClearZBuffer)
					m_ClearFlag	|=	enTCF_ZBUFFER;
			}

			Air::U32 Target::GetClearFlag(){
				return	m_ClearFlag;
			}

			void Target::FindActiveCamera( CameraSet& setCamera )
			{
				Viewport*	pVP	=	NULL;
				ViewportMap::iterator	i	=	m_mapViewport.begin();
				for(;i!=m_mapViewport.end();i++){
					Camera*	pCamera	=	i->second->GetCamera();
					if(pCamera!=NULL){
						setCamera.insert(pCamera);
					}
				}
			}

			void* Target::GetRTV( U32 uiIdx /*= 0*/ )
			{
				return	m_vecTexture[uiIdx]->GetRTV();
			}

			void* Target::GetSRV( U32 uiIdx /*= 0*/ )
			{
				return	m_vecTexture[uiIdx]->GetSRV();
			}

			void* Target::GetBackBuffer( U32 uiIdx /*= 0*/ )
			{
				return	m_vecTexture[uiIdx]->GetBuffer();
			}

			void Target::ReSize( U32 width,U32 height )
			{
				U32	uiWidth		=	GetWidth();
				U32	uiHeight	=	GetHeight();
				if(	uiWidth		!=	width	||
					uiHeight	!=	height)
				{
					Destroy();
					U32	uiTexCount	=	m_Info.vecTextureInfo.size();
					for(U32 i=0;i<uiTexCount;i++){
						m_Info.vecTextureInfo[i].width	=	width;
						m_Info.vecTextureInfo[i].height	=	height;
					}
					Create();
				}
			}

			void Target::OnMainWindowSize( Window* pMainWindow )
			{
				if(m_Info.vecTextureInfo[0].fScreenScale	>	0.0f){
					U32	uTargetCount	=	m_Info.vecTextureInfo.size();

					for(U32	i=0;i<uTargetCount;i++){
						if(m_vecTexture[i]!=NULL){
							m_vecTexture[i]->Destroy();
							m_vecTexture[i]->Create();
						}
					}
				}
			}

			void* Target::GetUAV( U32 uiIdx /*= 0*/ )
			{
				return m_vecTexture[uiIdx]->GetUAV();
			}

		}
	}
}