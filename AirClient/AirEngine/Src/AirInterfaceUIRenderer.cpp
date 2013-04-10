#include "AirInterfaceUIRenderer.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirEngineSystem.h"
#include "AirInterfaceUIWindowControl.h"
#include "AirEngineScreenEntity.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	
	namespace	Engine{
		namespace	UI{
	
			typedef	Render::Vertex::IDeclare	VertexDeclare;
			typedef	Render::Buffer				VertexBuffer;
			typedef	Render::Buffer				IndexBuffer;
			typedef	Render::Draw::Buff			DrawBuff;
			typedef	Render::LockOption			LockOpt;
	
	
			Renderer::Renderer(){
				m_uiSize	=	0;
				m_vPositionSizeArray.resize(MAX_WINDOW);
				m_vUVPositionSizeArray.resize(MAX_WINDOW);
				m_vColorArray.resize(MAX_WINDOW);
				m_vCustomArray.resize(MAX_WINDOW);
				m_vTextureSize	=	Float4(0,0,0,0);
			
				m_pScreenEnt	=	NULL;
			}
	
			U1 Renderer::InitEffect(){
				GlobalSetting&	setting		=	GetGlobalSetting();
				//创建材质
				SetMaterialName("UI");
				//创建声明
				VertexDeclare::Info	vdeclareInfo;
				//vdeclareInfo.m_FVF	=	VertexBuff::PT::fvf;
				m_DrawBuff.m_pVertexDeclare	=	setting.m_pRenderSystem->CreateProduct<VertexDeclare>("XYZ",&vdeclareInfo);
				//创建顶点缓冲区
				VertexBuffer::Info		vbuffinfo;
				vbuffinfo.SetVertexBuffer(MAX_WINDOW*6,12);
				m_DrawBuff.m_pVertexBuffer[0]	=	setting.m_pRenderSystem->CreateProduct<VertexBuffer>("UI",&vbuffinfo);
				//VertexBuff::PT*	pVertex	=	NULL;
// 				m_DrawBuff.m_pVertexBuff->Lock(LockOpt(0,0,(void**)&pVertex));
// 				for(UInt	i	=0;i<MAX_WINDOW;i++){
// 					pVertex[i*6]	= VertexBuff::PT(-1.0f, -1.0f, 1.0f, i, i);
// 					pVertex[i*6+1]	= VertexBuff::PT(-1.0f,  1.0f, 1.0f, i, i);
// 					pVertex[i*6+2]	= VertexBuff::PT( 1.0f,  1.0f, 1.0f, i, i);
// 	
// 					pVertex[i*6+3]	= VertexBuff::PT(-1.0f, -1.0f, 1.0f, i, i);
// 					pVertex[i*6+4]	= VertexBuff::PT( 1.0f,  1.0f, 1.0f, i, i);
// 					pVertex[i*6+5]	= VertexBuff::PT( 1.0f, -1.0f, 1.0f, i, i);
// 				}
// 				m_DrawBuff.m_pVertexBuff->Unlock();
	
				m_DrawBuff.m_DrawOption.m_uiVertexCount		=	MAX_WINDOW*6;
				m_DrawBuff.m_DrawOption.m_DrawFuncType		=	Render::Draw::FUNC_TYPE_DP;
	
				//创建第二个缓冲区
				m_pScreenEnt	=	EngineSystem::GetSingleton()->CreateProduct<ScreenEntity>("UIScreen");
	
				return true;
	
			}
	
			void Renderer::ReleaseEffect(){
				GlobalSetting&	setting		=	GetGlobalSetting();
				if(m_pImageSet!=NULL){
					m_pImageSet->Destroy();
					delete	m_pImageSet;
					m_pImageSet	=	NULL;
				}
// 				if(m_pMaterial!=NULL){
// 					//这个时候 材质工厂已经释放掉了
// 					setting.m_pRenderSystem->DestroyProduct(m_pMaterial);
// 					m_pMaterial	=	NULL;
// 				}
	
				if(m_DrawBuff.m_pVertexDeclare!=NULL){
					setting.m_pRenderSystem->DestroyProduct(m_DrawBuff.m_pVertexDeclare);
					m_DrawBuff.m_pVertexDeclare	=	NULL;
				}
	
				SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
	
				if(m_pScreenEnt!=NULL){
					//setting.m_pEngine->DestroyProduct(m_pScreenEnt);
					m_pScreenEnt	=	NULL;
				}
			}
	
			void Renderer::Push( IElement*	pElement ){
				if(m_uiSize>=MAX_WINDOW){
					StartRender();
				}
				
				m_vPositionSizeArray[m_uiSize]		=	pElement->m_vPositionSize;
				m_vUVPositionSizeArray[m_uiSize]	=	pElement->m_vUV;
				m_vColorArray[m_uiSize]				=	pElement->m_vColor;
				m_vCustomArray[m_uiSize]			=	pElement->m_vCustom;
	
				//标记位置
				//pElement->m_uiMark					=	m_uiSize;
				m_uiSize++;
			}
	
			void Renderer::StartRender(){
				m_DrawBuff.m_DrawOption.m_uiIndexCount	=	m_uiSize;
				//Render::IMaterial::Technique*	pTechnique	=	m_pMaterial->GetCurrentTechnique();
				//pTechnique->m_mapParam.
// 				pTechnique->SetParam("PositionSize",	&m_vPositionSizeArray,		0);
// 				pTechnique->SetParam("UVPositionSize",	&m_vUVPositionSizeArray,	0);
// 				pTechnique->SetParam("Color",			&m_vColorArray,				0);
// 				pTechnique->SetParam("Custom",			&m_vCustomArray,			0);
				//pTechnique
				//Render::IRenderable::Render();
				m_uiSize	=	0;
			}
	
			void Renderer::SetMaterialName( AString strMaterialName ){
				AString	strMaterial	=	AString("..\\Data\\UI\\")	+	strMaterialName	+	AString(".Material");
				AString	strImageSet	=	AString("..\\Data\\UI\\")	+	strMaterialName	+	AString(".ImageSet.Xml");
	
// 				Render::IMaterial*	pMaterial	=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(strMaterial,AString("Material"));
// 				if(pMaterial==NULL){
// 					EngineLogWarnning((AChar*)strMaterialName.c_str(),"UI材质更换失败！");
// 					return;
// 				}
// 				if(m_pMaterial!=NULL){
// 					EngineSystem::GetSingleton()->DestroyProduct(m_pMaterial);
// 					m_pMaterial	=	NULL;
// 				}
// 				m_pMaterial	=	pMaterial;
// 	
// 				if(pMaterial!=NULL){
// 					Render::IMaterial::Technique*	pTechnique	=	m_pMaterial->GetCurrentTechnique();
// 					if(pTechnique!=NULL){
// 						Render::ITexture*	pTex	=	(Render::ITexture*)pTechnique->GetParam("UI");
// 						if(pTex!=NULL){
// 							//Render::ITexture::Info	info	=	pTex->m_Info;
// 	
// 							m_vTextureSize.x	=	pTex->m_Info.width;
// 							m_vTextureSize.y	=	pTex->m_Info.height;
// 						}
// 					}
// 				}
	
				IImageSet::Info	info;
				info.vTextureSize	=	Float2(m_vTextureSize.x,m_vTextureSize.y);
				m_pImageSet	=	new	IImageSet(strImageSet,&info);
				m_pImageSet->Create();
			}
	
			void Renderer::RenderControl( Window::IControl* pControl ){
				if(pControl!=NULL){
// 					Render::IMaterial*	pMaterial	=	pControl->GetMaterial();
// 					if(m_pScreenEnt!=NULL)
// 						m_pScreenEnt->RenderPostComposer(pMaterial);
				}
			}
	
			void Renderer::RenderTarget(){
				Render::TargetListItr	i	=	m_lstTarget.begin();
				for(;i!=m_lstTarget.end();i++){
					Render::Target*	p	=	(Render::Target*)(*i);
					if(p!=NULL){
						//判断材质是否为空
						MovableObject*	pObject	=	p->GetRenderObject();
// 						if(	pObject->GetMaterial()==NULL)
// 							continue;
						//判断是否为一个UI窗口
						Window::IControl*	pControl	=	dynamic_cast<Window::IControl*>(pObject);
						if(pControl==NULL)
							continue;
						//判断是否已经变化
						if(!pControl->IsChanged())
							continue;
						//渲染到缓存
						//p->Render();
						
					}
				}
			}
		}
	}
};