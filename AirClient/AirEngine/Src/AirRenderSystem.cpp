#include "AirRenderSystem.h"
#include "AirEngineRenderable.h"
#include "AirGlobalSetting.h"

namespace Air{
	
	namespace	Client{
		namespace	Render{
	
	
			System::System(){		


				m_bDeviceLost	=	false;



// 				m_CBFrame.vAmbient		=	Float4(0.5f,0.5f,0.5f,0);
// 				m_CBFrame.vFog			=	Float4(0.5f,0.5f,0.5f,0);
// 				m_CBFrame.vSunDiffuse	=	Float4(1,1,1,1);
// 				m_CBFrame.vSunDir		=	Float4(-1,-1,-1,0).Normalize();
// 				m_CBFrame.vSunSpec		=	Float4(1,1,1,64);
// 				m_CBFrame.vTime			=	Float4(0,0,0,0);
// 
// 				m_CBCamera.vCameraDir	=	Float4(0,0,-1,0);
// 				m_CBCamera.vCameraPosition	=	Float4(0,0,0,0);
// 				m_CBCamera.vCameraRight	=	Float4(1,0,0,0);
// 				m_CBCamera.vCameraUp	=	Float4(0,1,0,0);
// 				m_CBCamera.vVP_NearFar	=	Float4(1.0f/1024.0f,1.0f/768.0f,1,1000);
// 
// 				memset(&m_CBBone,0,sizeof(m_CBBone));
				m_pDevice				=	NULL;
				m_pMainWindow			=	NULL;

				m_pWorldMatrixBuffer	=	NULL;
				m_pBoneMatrixBuffer		=	NULL;

			}
	
			System::~System(){
	
			}


			void System::FindActiveCamera( CameraSet& setCamera )
			{
				IFactory*	pFactory	=	GetFactory("Target");
				if(pFactory!=NULL)
				{
					const	IFactory::ProductMap&	lstTarget	=	pFactory->GetProductList();
					IFactory::ProductMap::const_iterator	i	=	lstTarget.begin();
					for(;i!=lstTarget.end();i++){
						RenderTarget*	pTarget	=	static_cast<RenderTarget*>(i->second);
						if(pTarget!=NULL){
							if(pTarget->IsAvtive())
							{
								pTarget->FindActiveCamera(setCamera);
							}
						}
					}
				}


				pFactory				=	GetFactory("Window");
				if(pFactory!=NULL)
				{
					const	IFactory::ProductMap&	lstWindow	=	pFactory->GetProductList();
					IFactory::ProductMap::const_iterator	i	=	lstWindow.begin();
					for(;i!=lstWindow.end();i++){
						RenderWindow*	pTarget	=	static_cast<RenderWindow*>(i->second);
						if(pTarget!=NULL){
							if(pTarget->IsAvtive())
							{
								pTarget->FindActiveCamera(setCamera);
							}
						}
					}
				}
			}

			Device* System::GetDevice()
			{
				return	m_pDevice;
			}

			Air::U1 System::Initialization()
			{
				if(m_pDevice!=NULL){
					m_pDevice->Create();
				}
				if(m_pMainWindow	==	NULL){
					Window::Info info;
					U32	uiWidth		=	GetGlobalSetting().m_DisplayParam.iWidth;
					U32	uiHeight	=	GetGlobalSetting().m_DisplayParam.iHeight;
					U1	bWindow		=	GetGlobalSetting().m_DisplayParam.bWindow;
					HWND	hWnd	=	GetGlobalSetting().m_EngineParam.hWnd;
					HWND	hParentWnd	=	GetGlobalSetting().m_EngineParam.hParentWnd;
					info.SetRenderWindow(uiWidth,uiHeight,bWindow,hParentWnd,hWnd);
					info.bUseDepth		=	true;
					m_pMainWindow	=	CreateProduct<Window*>("MainWindow","Window",&info);
					m_pMainWindow->SetClearFlag(1,1,1);
				}

				if(m_pWorldMatrixBuffer	==	NULL){

					Buffer::Info	info;
					info.SetConstantBuffer(sizeof(Float44));
					info.cbType		=	enCBT_Object;
					info.usage		=	enUSAGE_DYNAMIC;
					m_pWorldMatrixBuffer	=	CreateProduct<Buffer*>("WorldMatrix","Buffer",&info);
					m_pDevice->SetCB(enVS,2,m_pWorldMatrixBuffer);
				};
				if(m_pBoneMatrixBuffer		==	NULL){

					Buffer::Info	info;
					info.SetConstantBuffer(256*sizeof(Float44));
					info.cbType		=	enCBT_Bone;
					info.usage		=	enUSAGE_DYNAMIC;
					m_pBoneMatrixBuffer	=	CreateProduct<Buffer*>("BoneMatrix","Buffer",&info);
					m_pDevice->SetCB(enVS,4,m_pBoneMatrixBuffer);
				};
				return	true;
			}

			Air::U1 System::Release()
			{
				SAFE_RELEASE_REF(m_pBoneMatrixBuffer);
				SAFE_RELEASE_REF(m_pWorldMatrixBuffer);
				SAFE_RELEASE_REF(m_pMainWindow);
				if(m_pDevice!=NULL){
					m_pDevice->Destroy();
				}
				
				return	true;
			}

			Air::U1 System::Start()
			{
				return	true;
			}

			Air::U1 System::Stop()
			{
				return	true;
			}

			void System::AddDevice( Device* pDevice )
			{
				if(pDevice!=NULL){
					m_vecDevice.push_back(pDevice);
				}
				if(m_pDevice==NULL	&&	!m_vecDevice.empty()){
					m_pDevice	=	m_vecDevice[0];
				}

			}

			Air::U32 System::GetDeviceCount()
			{
				return	m_vecDevice.size();
			}

			Air::AString System::GetDeviceName()
			{
				return	m_vecDevice[0]->GetProductName();
			}

			void System::SelectDevice( U32 uiIndex )
			{
				if(uiIndex	>=	m_vecDevice.size())
					m_pDevice	=	m_vecDevice[uiIndex];
				else
					m_pDevice	=	m_vecDevice[0];
			}

			Window* System::GetMainWindow()
			{
				return	m_pMainWindow;
			}

			void System::OnWindowChange( Window* pWindow )
			{
				if(pWindow==NULL)
					return;
				if(m_pMainWindow==pWindow){
					IFactory*	pFactory	=	GetFactory("Target");
					const IFactory::ProductMap& mapProduct	=	pFactory->GetProductList();
					IFactory::ProductMap::const_iterator	i	=	mapProduct.begin();
					for(;i!=mapProduct.end();i++){
						Target*	pTarget	=	static_cast<Target*>(i->second);
						pTarget->OnMainWindowSize(pWindow);
					}

				}

			}

			void System::SetWorldMatrix( const Float44& matWorld )
			{
				if(m_pWorldMatrixBuffer!=NULL){
					m_pWorldMatrixBuffer->Write(0,sizeof(Float44),(void*)&matWorld);
				}
			}

			void System::SetBoneMatrix( Float44* pBone,U32 uiBoneCount )
			{
				if(	pBone				!=NULL	&&
					uiBoneCount			!=0		&&
					m_pBoneMatrixBuffer	!=NULL)
				{
					m_pWorldMatrixBuffer->Write(0,uiBoneCount*sizeof(Float44),(void*)&pBone);
				}
			}

			void System::DrawObject( Renderable* pObject ,bool	bUseSkin)
			{
				if(pObject->NeedWorldMatrix()){
					SetWorldMatrix(*pObject->GetWorldMatrix());
				}
				U32	uiBoneCount	=	pObject->GetBoneCount();
				if(bUseSkin	&&	uiBoneCount!=0){
					SetBoneMatrix(pObject->GetBoneMatrix(),uiBoneCount);
				}
				//äÖÈ¾
				m_pDevice->DrawObject(pObject);
			}

		}
	}
};