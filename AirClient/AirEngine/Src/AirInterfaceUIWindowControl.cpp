#include "AirInterfaceUIWindowControl.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceUISystem.h"
#include "AirInterfaceInputSystem.h"
#include "AirRenderSystem.h"
#include "AirEngineCamera.h"
namespace Air{
	
	namespace	Engine{
		namespace	UI{
			namespace	Window{
				Float2	IControl::TopLeft			=	Float2(0,0);
				Float2	IControl::TopMiddle			=	Float2(0.5f,0.0f);
				Float2	IControl::TopRight			=	Float2(1.0f,0.0f);
				Float2	IControl::MiddleLeft		=	Float2(0.0f,0.5f);
				Float2	IControl::Middle			=	Float2(0.5f,0.5f);
				Float2	IControl::MiddleRight		=	Float2(1.0f,0.5f);
				Float2	IControl::BottomLeft		=	Float2(0.0f,1.0f);
				Float2	IControl::BottomMiddle		=	Float2(0.5f,1.0f);
				Float2	IControl::BottomRight		=	Float2(1.0f,1.0f);
	
				inline	AString	GetCacheMaterialString(AString	str){
					AString	s	=	"[Material]\n"
									"FX=..\\Data\\UI\\UIControl.fx\n"
									"VeryHigh=UIControl\n"
									"[VeryHigh]\n"
									"PositionSize=1,1,1,1:Vector\n"
									"Color=1,1,1,1:Vector\n"
									"Center=1,1,1,1:Vector\n"
									"CacheTex="+str+":Texture\n"
									"Width=ScreenWidth\n"
									"Height=ScreenHeight\n";
					return	s;
				};
				inline	AString	GetUIMaterialString(AString		str);
	
				IControl::IControl(CAString&	strName,StateArray*	pArray,Info*	pInfo)	:
					State(strName,pArray,pInfo){
					m_strProductName	=	strName;
					//m_bChanged				=	true;
					m_vAbsolutelyPosition	=	Float4(0,0,0,0);
	
					m_pParent				=	NULL;
	
					m_piOrginScreenWidth	=	&GetGlobalSetting().m_DisplayParam.iWidth;
					m_piOrginScreenHeight	=	&GetGlobalSetting().m_DisplayParam.iHeight;
	
					m_pTarget				=	NULL;
	
					m_Message.m_pControl	=	this;
				}
	
				void IControl::Update(){
					if(!IsVisiable()	||	!IsEnable())
						return;
	
					
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	pWindow	=	(IControl*)(*i);
						if(pWindow!=NULL){
							pWindow->Update();
						}
					}
				}
	
				void IControl::AddChild( IControl* pWindow ){
					if(pWindow!=NULL){
						pWindow->SetParent(this);
					}
					m_lstWindow.push_back(pWindow);
				}
	
				void IControl::RemoveChild( IControl* pWindow ){
					if(pWindow!=NULL)
						pWindow->SetParent(NULL);
					m_lstWindow.remove(pWindow);
				}
	
				void IControl::SetParent( IControl* pParent ){
					m_pParent	=	pParent;
				}
				void IControl::RefreshSize(){
	
	
					//材质为空 直接返回
// 					if(m_pMaterial!=NULL){
// 						//获取技术
// 						Render::IMaterial::Technique*	pTechnique	=	m_pMaterial->GetCurrentTechnique();
// 						if(pTechnique!=NULL){
// 							pTechnique->SetParam("PositionSize",GetPositionSize());
// 						}
// 					}
	
					//刷新子节点的尺寸
	 				WindowListItr	i	=	m_lstWindow.begin();
	 				for(;i!=m_lstWindow.end();i++){
	 					IControl*	pWindow	=	(IControl*)(*i);
	 					if(pWindow!=NULL){
	 						//if(pWindow->IsRelativelySize())
	 							pWindow->RefreshSize();
	 					}
	 				}
				}
	
				void IControl::RefreshPosition(){
					//材质为空 直接返回
// 					if(m_pMaterial!=NULL){
// 						//获取技术
// 						Render::IMaterial::Technique*	pTechnique	=	m_pMaterial->GetCurrentTechnique();
// 						if(pTechnique!=NULL){
// 							pTechnique->SetParam("PositionSize",GetPositionSize());
// 						}
// 					}
					//刷新子节点的位置
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	pWindow	=	(IControl*)(*i);
						if(pWindow!=NULL){
							pWindow->RefreshPosition();
						}
					}
				}
	
				void IControl::RemoveAllChild(){
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	p	=	(IControl*)(*i);
						if(p!=NULL){
							p->SetParent(NULL);
							p	=	NULL;
						}
					}
					m_lstWindow.clear();
				}
	
				void IControl::DestroyChild(IControl*	pWindow){
					if(pWindow!=NULL){
						RemoveChild(pWindow);
						GetGlobalSetting().m_pUISystem->DestroyIWindow(pWindow);
					}
				}
	
				void IControl::DestroyAllChild(){
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	p	=	(IControl*)(*i);
						if(p!=NULL){
							p->SetParent(NULL);
							GetGlobalSetting().m_pUISystem->DestroyIWindow(p);
							p	=	NULL;
						}
					}
					m_lstWindow.clear();
				}
	
				IControl* IControl::IsMouseInWindow(){
					if(!IsEnable()	||	!IsVisiable())
						return	NULL;
					//static	Float4&	v	=	GetGlobalSetting().m_vCursorPosition;
					static	SInt&	x	=	GetGlobalSetting().m_pInputSystem->m_iX;
					static	SInt&	y	=	GetGlobalSetting().m_pInputSystem->m_iY;
					static	U32&	w	=	GetGlobalSetting().m_DisplayParam.iWidth;
					static	U32&	h	=	GetGlobalSetting().m_DisplayParam.iHeight;
	
					//鼠标位置 测试代码
	// 				AChar	str[128];
	// 				sprintf_s(str,128,"%d,%d\n",x,y);
	// 				OutputDebugStringA(str);
	
					Float4	vPositionSize	=	GetPositionSize();
					Float2	vCenter			=	GetCenter();
					//获取窗口的边界
					Real	left	=	vCenter.x*w	+	vPositionSize.z;
					Real	top		=	vCenter.y*h	+	vPositionSize.w;
					Real	right	=	vCenter.x*w	+	vPositionSize.z	+	vPositionSize.x;
					Real	buttom	=	vCenter.y*h	+	vPositionSize.w	+	vPositionSize.y;
					//判断边界
					if(	x	>	left	&&
						y	>	top		&&
						x	<	right	&&
						y	<	buttom)
					{
						IControl*	pActiveWin	=	NULL;
						WindowList::reverse_iterator	i	=	m_lstWindow.rbegin();
						for(;i!=m_lstWindow.rend();i++){
							IControl*	pWindow	=	(IControl*)(*i);
							if(pWindow!=NULL){
								pActiveWin	=	pWindow->IsMouseInWindow();
								if(pActiveWin!=NULL){
									return	pActiveWin;
								}
							}
						}
						return this;
					}else{
						return NULL;
					}
				}
				void IControl::Render(){
					//如果不可见 直接返回不渲染
	 				if(!IsVisiable())
	 					return;
					RenderCache();
				}
	
				U1 IControl::Create(){
					GlobalSetting&	setting	=	GetGlobalSetting();
					//注册窗口快捷键
					setting.m_pUISystem->AddKey(m_Info.key.Value,this);
					//创建渲染目标
					Render::Target::Info	info;
					//info.SetSingleTarget(m_Info.vPositionSize.x,m_Info.vPositionSize.y,Render::F).SetRenderToTexture(m_Info.vPositionSize.x,m_Info.vPositionSize.y);
					m_pTarget	=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>(m_strProductName,&info);
					//设置当前UI空间为渲染对象
					m_pTarget->SetRenderObject(this);
					//设置背景颜色为黑色
					m_pTarget->SetBKColor(Float4(0,0,0,0));
					//static	Camera	cam("UICamera");
					//m_pTarget->SetCamera(&cam);
					//添加渲染目标到 链表中
					setting.m_pUISystem->AddTarget(m_pTarget);
					//创建材质
					AString	strCache	=	GetCacheMaterialString(m_strProductName);
					//m_pMaterial	=	RenderSystem::GetSingleton()->CreateProduct<Render::IMaterial*>(m_strProductName,AString("Material"),&strCache);
	
// 					if(m_pMaterial!=NULL){
// 						Render::IMaterial::Technique*	pTechnique	=	m_pMaterial->GetCurrentTechnique();
// 						if(pTechnique!=NULL){
// 							pTechnique->SetParam("PositionSize",GetPositionSize());
// 							Float2	vCenter	=	GetCenter();
// 							pTechnique->SetParam("Center",Float4(vCenter.x,vCenter.y,0,0));
// 							pTechnique->SetParam("Color",GetColorAlpha());
// 							//pTechnique->SetParam("Custom",m_Info.vCustom);
// 						}
// 					}
					return true;
				}
	
				U1 IControl::Destroy(){
					GlobalSetting&	setting	=	GetGlobalSetting();
					//移除快捷键
					setting.m_pUISystem->RemoveKey(m_Info.key.Value,this);
					//摧毁渲染目标
					if(m_pTarget!=NULL){
						setting.m_pUISystem->RemoveTarget(m_pTarget);
						m_pTarget->ReleaseRef();
						m_pTarget	=	NULL;
					}
					//摧毁材质
// 					if(m_pMaterial!=NULL){
// 						RenderSystem::GetSingleton()->DestroyProduct(m_pMaterial);
// 						m_pMaterial	=	NULL;
// 					}
					//设置父窗口为空
					SetParent(NULL);
					//摧毁所有子窗口
					DestroyAllChild();
					return true;
				}
	
				void IControl::SetCenter( Float2 vCenter /*= TopLeft*/ ){
					m_Info.vCenter	=	vCenter;
					//材质为空 直接返回
// 					if(m_pMaterial!=NULL){
// 						//获取技术
// 						Render::IMaterial::Technique*	pTechnique	=	m_pMaterial->GetCurrentTechnique();
// 						if(pTechnique!=NULL){
// 							Float2	vCenter	=	GetCenter();
// 							pTechnique->SetParam("Center",Float4(vCenter.x,vCenter.y,0,0));
// 						}
// 					}
					RefreshPosition();
				}
	
				Float2 IControl::GetCenter(){
					if(m_pParent!=NULL)
						return	Float2(m_pParent->GetCenter().x+m_Info.vCenter.x,m_pParent->GetCenter().y+m_Info.vCenter.y);//*m_pParent->GetSize()/Float2(GetGlobalSetting().m_iOrginWidth,GetGlobalSetting().m_iOrginHeight);
					return	m_Info.vCenter;
				}
	
				void IControl::SetPosition( Float2& vPosition ){
					m_Info.vPositionSize.z	=	vPosition.x;
					m_Info.vPositionSize.w	=	vPosition.y;
					RefreshPosition();
				}
	
				Float2 IControl::GetPosition(){
					return	Float2(m_Info.vPositionSize.z,m_Info.vPositionSize.w);
				}
	
				void IControl::SetWindowSize( Float2& vSize ){
					m_Info.vPositionSize.x	=	vSize.x;
					m_Info.vPositionSize.y	=	vSize.y;
					RefreshSize();
	
					m_bChanged	=	true;
// 					Render::Target::Info&	texInfo;//	=	m_pTarget->GetTexture()->m_Info;
// 					texInfo.width	=	m_Info.vPositionSize.x;
// 					texInfo.height	=	m_Info.vPositionSize.y;
// 					m_pTarget->ReCreate(texInfo);
				}
	
				Float2 IControl::GetWindowSize(){
					return	Float2(m_Info.vPositionSize.x,m_Info.vPositionSize.y);
				}
	
				Float2 IControl::GetAbsolutelyPosition(){
					return Float2(m_vAbsolutelyPosition.z,m_vAbsolutelyPosition.w);
				}
	
				void IControl::Refresh(){
					RefreshPosition();
					RefreshSize();
				}
	
				IControl* IControl::GetFirstChildWindow(){
					if(m_lstWindow.empty())
						return	NULL;
					WindowListItr	i	=	m_lstWindow.begin();
					IControl*	pWindow	=	(IControl*)(*i);
					return	pWindow;
				}
	
				IControl* IControl::GetChildWindow( AString strName ){
					if(m_lstWindow.empty())
						return	NULL;
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	pWindow	=	(IControl*)(*i);
						if(pWindow!=NULL){
							if(pWindow->GetProductName()	==	strName){
								return	pWindow;
							}
						}
					}
					return	NULL;
				}
	
	 			void IControl::BeforeRenderElement( ElementArray& eArray ){
	 				for(UInt i=0;i<eArray.size();i++){
	 					IElement&	ele	=	eArray[i];
	 					//ele.m_vPositionSize.z		=	m_Info.vPosition.z;
	  					ele.m_vPositionSize.z	+=	m_vAbsolutelyPosition.z;
	  					ele.m_vPositionSize.w	+=	m_vAbsolutelyPosition.w;
	 				}	
	 			}
	
				U1 IControl::IsChanged(){
					return	(m_bChanged);
				}
	
				bool IControl::keyPressed( const OIS::KeyEvent &arg ){
	
					return	true;
				}
	
				bool IControl::keyReleased( const OIS::KeyEvent &arg ){
	
					return	true;
				}
	
				bool IControl::mouseMoved( const OIS::MouseEvent &arg ){
	
					return	true;
				}
	
				bool IControl::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	
					return	true;
				}
	
				bool IControl::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	
					return	true;
				}
	
				void IControl::RenderCache(){
					if(m_bChanged){
		 				//渲染当前窗口
		 				State::RenderElement();
						m_bChanged	=	false;
					}
				}
	
				void IControl::RenderUI(){
					//不可见 直接返回
					if(!IsVisiable())
						return;
					//材质为空 直接返回
// 					if(m_pMaterial!=NULL){
// 						//渲染
// 						GetGlobalSetting().m_pUISystem->RenderControl(this);
// 					}
					//渲染子窗口
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	pWindow	=	(IControl*)(*i);
						if(pWindow!=NULL){
							pWindow->RenderUI();
						}
					}
				}
	
				Float4 IControl::GetPositionSize(){
					Float2	p(0,0);//	=	Float2::ZERO;
// 					if(m_pParent!=NULL){
// 						p	=	m_pParent->GetPosition()	+	Float2(m_Info.vPositionSize.z,m_Info.vPositionSize.w);
// 					}else{
// 						p	=	Float2(m_Info.vPositionSize.z,m_Info.vPositionSize.w);
// 					}
					Float4	v	=	m_Info.vPositionSize;
					v.z	=	p.x;
					v.w	=	p.y;
					return	v;
				}
	
				void IControl::RefreshColor(){
					//材质为空 直接返回
// 					if(m_pMaterial!=NULL){
// 						//获取技术
// 						Render::IMaterial::Technique*	pTechnique	=	m_pMaterial->GetCurrentTechnique();
// 						if(pTechnique!=NULL){
// 							pTechnique->SetParam("Color",GetColorAlpha());
// 						}
// 					}
					//刷新子节点的位置
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	pWindow	=	(IControl*)(*i);
						if(pWindow!=NULL){
							pWindow->RefreshColor();
						}
					}
				}
	
				void IControl::SetColor( Float3 vColor ){
					m_Info.vColor	=	Float4(vColor.x,vColor.z,vColor.z,m_Info.vColor.w);
					ExecuteEvent(Message::enColorChange,&Message(this,&m_Info.vColor));
					RefreshColor();
				}
	
				void IControl::SetAlpha( Real fAlpha ){
					if(m_Info.vColor.w==fAlpha)
						return;
					m_Info.vColor.w	=	fAlpha;	
					ExecuteEvent(Message::enAlphaChange,&Message(this,fAlpha));
					RefreshColor();
				}
	
				void IControl::SetColorAlpha( Float4 v ){
					SetColor(Float3(v.x,v.y,v.z));
					SetAlpha(v.w);
					//RefreshColor();
				}
	
				Float3 IControl::GetColor(){
					Float4&	v	=	m_Info.vColor;
					return	Float3(v.x,v.y,v.z);
				}
	
				Real IControl::GetAlpha(){
					return	m_Info.vColor.w;
				}
	
				Float4 IControl::GetColorAlpha(){
// 					if(m_pParent!=NULL){
// 						return	m_pParent->GetColorAlpha()*m_Info.vColor;
// 					}else
						return	m_Info.vColor;
				}
	
				void IControl::SetNeedReRender(){
					m_bChanged	=	true;
					//刷新子节点的位置
					WindowListItr	i	=	m_lstWindow.begin();
					for(;i!=m_lstWindow.end();i++){
						IControl*	pWindow	=	(IControl*)(*i);
						if(pWindow!=NULL){
							pWindow->SetNeedReRender();
						}
					}
				}
			}
		}
	}
};