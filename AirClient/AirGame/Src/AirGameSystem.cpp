#include "AirGameSystem.h"
//#include "DecorationShowSystem.h"
#include "AirGameSection.h"
#include "AirGameGlobal.h"
#include "AirGameFPSControl.h"
#include "AirGameThirdControl.h"
#include "AirEngineSystem.h"

namespace Air{
	
	
	namespace	Engine{
		Terrain::World*	g_World	=	NULL;
		Terrain::IPage*	g_pPage	=	NULL;
		SubEntity*		g_pEntity	=	NULL;
		SceneNode*		g_pNode		=	NULL;
	
		Common::NetClient*	g_Client	=	NULL;
		Common::NetServer*	g_Server	=	NULL;
	
		Render::IText*	g_pText		=	NULL;
	
	
	
		
	
	
		
		//Terrain::Info	g_Info;
		namespace	Game{
			//插件名字
			static	UInt		g_uiNumPlugin		=	3;	
			static	AString		g_strPluginArray[]	=	{
				"Loading",
				"Data",
				"Custom"
			};
			//DecorationShowSystem*		pShowSystem	=	NULL;
	
			System::System():Common::ISystem("GameSystem"){
				
				GetGlobal().m_pSystem				=	this;
				m_pRootNode							=	new	SceneNode();
				m_ppSection							=	&GetGlobal().m_pSection;
				m_ppLoadingSection					=	&GetGlobal().m_pLoadingSection;
				m_pPluginMgr						=	NULL;
	
				m_pCurrentSection					=	NULL;
				m_pTempSection						=	NULL;
	
				m_pCurrentPlugin					=	NULL;
	
				m_strPluginNameArray.resize(3);
			}
	
			System::~System(){
				GetGlobal().m_pSystem				=	NULL;
	//			GetGlobalSetting().m_pGameSystem	=	NULL;
				SAF_D(m_pRootNode);
			}
	
			void System::OnFrameMove( Real fTotalTime,Real fDeltaTime ){
	// 			if(g_World!=NULL)
	// 				g_World->Updata();
				if(g_pNode!=NULL)
					g_pNode->SetQuat(Common::Quaternion(Common::Vector3(0,1,0),fTotalTime/5.0f));
				if(g_pPage!=NULL)
					g_pPage->Updata();
	
				if(m_pCurrentSection!=NULL){
					m_pCurrentSection->OnUpdata();
				}
				//判断是否需要切换场景
				if(!m_strNextSectionName.empty()){
					m_CS.Enter();
					AString	str	=	m_strNextSectionName;
					m_strNextSectionName.clear();
					m_CS.Leave();
					//Render::System::GetSingleton()->PauseThreadSync();
					SwitchSection(str);
				}
			}
	
			void System::OnBeforeRender(){
				m_pTempSection	=	m_pCurrentSection;
				if(m_pTempSection!=NULL){
					m_pTempSection->OnRenderTarget();
				}
	
			}
	
			void System::OnRender(){
// 				if(g_World!=NULL)
// 					g_World->Render();
// 				if(g_pPage!=NULL)
// 					g_pPage->Render();
// 				if(g_pEntity!=NULL)
// 					g_pEntity->Render();
	
	
	// 			if(pShowSystem!=NULL)
	// 				pShowSystem->Render();
	
				if(m_pTempSection!=NULL){
					m_pTempSection->OnRender();
				}
// 				if(g_pText!=NULL)
// 					g_pText->Render();
			}
	
			void System::OnAfterRender(){
	
			}
	
			U1 System::Initialization(){
	
				AddFactory(new	Common::PluginFactory());
	//			AddFactory(new	DecorationShowSystemFactory(),this);
				AddFactory(new	SectionFactory());
				AddFactory(new	FPSControlFactory());
				AddFactory(new	ThirdControlFactory());
	
				//Log::GetSingleton()->Write("Game	Init\n");
	
				//纹理字体测试
	
// 				Common::Data*	p	=	GetGlobalSetting().m_pResourceSystem->Find("Material\\TestState.State");
// 				MaterialParse*	pMP	=	MaterialParse::GetSingleton();
// 				pMP->CompileState(p);
// 				p	=	GetGlobalSetting().m_pResourceSystem->Find(AString("Material\\TestMaterial.MaterialTemplate"));
// 				pMP->CompileMaterialTemplate(p);
	
	
	
	// 			g_World	=	new	Terrain::World();
	// 			g_World->Load("..\\Data\\Map\\Test\\");
	
	//   			Terrain::IPage::Info info;
	//   			info.strMapPath	=	"..\\Data\\Map\\Test1\\";
	//   			g_pPage	=	GetGlobalSetting().m_pEngine->Create<Terrain::IPage*>(info.GetPageName(),"TerrainPage",&info);
	//   			m_pRootNode->attachObject(g_pPage);
	//   
	   			//g_pNode	=	m_pRootNode->CreateChildSceneNode();
	//  #if 0
					//AString	strMaterial	=	"Material\\NoTexture.Material";
	     			//g_pEntity	=	GetGlobalSetting().m_pEngine->Create<SubEntity*>("Model\\Sphere.x","SubEntity",&strMaterial);
	     			//g_pNode->attachObject(g_pEntity);
	//   			//g_pNode->SetScale(Common::Vector3(0.5,0.5,0.5));
	//  #else
	//  			DecorationShowSystem::Info info;
	//  			info.pParentNode	=	m_pRootNode;
	//  			pShowSystem	=	Create<DecorationShowSystem*>("..\\Data\\Model\\final.txt","DecorationShowSystem",&info);
	//  #endif
	
	//  			m_pSection	=	Create<Section*>("TestSection","Section");
	//  			if(m_pSection!=NULL){
	//  				m_pSection->Load("");
	//  			}
	 			if(!LoadPlugin())
					return false;
				//Log::GetSingleton()->Write("Game	Load	Plugin");
	
// 				Render::IText::Info	tInfo;
// 				tInfo.Width		=	8;
// 				tInfo.Height	=	16;
// 	
// 				g_pText	=	Render::System::GetSingleton()->CreateProduct<Render::IText*>("Test","Text",&tInfo);
	//  			C3DS m3DS;
	//  			Common::File file("..\\Data\\Model\\Teapot.3ds");
	//  			file.Open();
	//  			Common::File::Data*	pData	=	file.GetData();
	//  			m3DS.LoadFromMemery(pData->GetBuff(),pData->GetSize());
	// 
	// 			m3DS.ComputeNormal();
	
				//Render::IXObject*	pObject	=	GetGlobalSetting().
	
				//m3DS.m_Model.vObject[0].
	
				//m3DS.Init("..\\Data\\Model\\Teapot.3ds");
				Input::ISystem*	pSys	=	GetGlobalSetting().m_pInputSystem;
				if(pSys!=NULL){
					pSys->Add((OIS::KeyListener*)this);
					pSys->Add((OIS::MouseListener*)this);
					pSys->Add((OIS::JoyStickListener*)this);
				}
	
	// 			Common::Vector3	U	=	Common::Vector3::UNIT_Y;
	// 			Common::Vector3	D	=	Common::Vector3::UNIT_Z;
	// 			Common::Vector3	R	=	U.crossProduct(D);
	// 			Common::Vector3 left	=	D.crossProduct(U);
				
				return true;
			}
	
			U1 System::Start(){
				m_pCurrentSection	=	GetGlobal().m_pLoadingSection;
				//Log::GetSingleton()->Write("Game	LoadSection");
				//载入所有关卡	但是不加载
				LoadSection();
				//Log::GetSingleton()->Write("Game	SwitchSection");
				//切换场景
				SwitchSection(m_strFirstSectionName);
	
				m_strFirstSectionName.clear();
	
				return true;
			}
	
			U1 System::Release(){
// 				if(g_pText!=NULL){
// 					Render::System::GetSingleton()->DestroyProduct(g_pText);
// 					g_pText=NULL;
// 				}
				if(g_Client!=NULL){
					GetGlobalSetting().m_pNetSystem->DestroyProduct(g_Client);
					g_Client	=	NULL;
				}
	
				if(g_Server!=NULL){
					GetGlobalSetting().m_pNetSystem->DestroyProduct(g_Server);
					g_Server	=	NULL;
				}
	
				if(g_pPage!=NULL){
					m_pRootNode->detachObject(g_pPage);
					EngineSystem::GetSingleton()->DestroyProduct(g_pPage);
					g_pPage=NULL;
				}
				if(g_pEntity!=NULL){
					g_pNode->detachObject(g_pEntity);
					EngineSystem::GetSingleton()->DestroyProduct(g_pEntity);
					g_pEntity=NULL;
				}
				if(g_pNode!=NULL){
					m_pRootNode->RemoveChild(g_pNode,true);
					g_pNode	=	NULL;
				}
	
	// 			if(pShowSystem!=NULL){
	// 				DestroyProduct(pShowSystem);
	// 				pShowSystem	=	NULL;
	// 			}
				//g_World->UnLoad();
				SAF_D(g_World);
	
				m_pCurrentSection	=	NULL;
				m_pTempSection		=	NULL;
	
				UnLoadSection();
	
				DestroyAllProduct();
				//卸载插件
				UnLoadPlugin();
	
				Input::ISystem*	pSys	=	GetGlobalSetting().m_pInputSystem;
				if(pSys!=NULL){
					pSys->Remove((OIS::KeyListener*)this);
					pSys->Remove((OIS::MouseListener*)this);
					pSys->Remove((OIS::JoyStickListener*)this);
				}
	
				//MaterialParse::ReleaseSingleton();
				return true;
			}
	
			void System::OnGUIEvent( UINT nEvent, int nControlID, void* pControl, void* pUserContext ){
			}
	
			bool System::keyPressed( const OIS::KeyEvent &arg ){
				//::OutputDebugStringA("Key Down\n");
				SAF_I((m_pTempSection),keyPressed(arg));
	// 			switch(arg.key){
	// 				case	OIS::KC_1:{
	// 					if(g_Client==NULL){
	// // 						Net::IClient::Info	info;
	// // 						info.strIP	=	"127.0.0.1";
	// // 						info.usPort	=	8001;
	// 						//g_Client	=	GetGlobalSetting().m_pNetSystem->Create<Net::IClient*>("测试服务器","Client",&info);
	// 						if(g_Server!=NULL)
	// 							break;
	// 						Net::IServer::Info	info;
	// 						info.usPort	=	8001;
	// 						g_Server	=	GetGlobalSetting().m_pNetSystem->Create<Net::IServer*>("测试服务器","Server",&info);
	// 					}
	// 					break;}
	// 				case	OIS::KC_2:{
	// 					if(g_Client!=NULL){
	// 						g_Client->Connect();
	// 					}
	// 					break;}
	// 				case	OIS::KC_3:{
	// 					AChar buff[100];
	// 					sprintf_s(buff,100,"测试发送文字");
	// // 					if(g_Client!=NULL)
	// // 						g_Client->Send((Net::IPackage*)buff);
	// 						if(g_Server!=NULL)
	// 							g_Server->Send((Net::IPackage*)buff);
	// 					break;}
	// 				case	OIS::KC_4:{
	// // 					if(g_Client!=NULL)
	// // 						g_Client->DisConnect();
	// 					if(g_Server!=NULL){
	// 						GetGlobalSetting().m_pNetSystem->DestroyProduct(g_Server);
	// 						g_Server	=	NULL;
	// 					}
	//					break;}
	//			}
				return	true;
			}
	
			bool System::keyReleased( const OIS::KeyEvent &arg ){
				SAF_I((m_pTempSection),keyReleased(arg));
				if(arg.key	==	OIS::KC_F){
					//Render::System::GetSingleton()->SetFullScreen();
				}
				return	true;
			}
	
			bool System::mouseMoved( const OIS::MouseEvent &arg ){
				SAF_I((m_pTempSection),mouseMoved(arg));
				return	true;
			}
	
			bool System::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
				SAF_I((m_pTempSection),mousePressed(arg,id));
				//::OutputDebugStringA("Mouse Down\n");
				return	true;
			}
	
			bool System::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
				SAF_I((m_pTempSection),mouseReleased(arg,id));
				return	true;
			}
	
			bool System::buttonPressed( const OIS::JoyStickEvent &arg, int button ){
				SAF_I((m_pTempSection),buttonPressed(arg,button));
				return	true;
			}
	
			bool System::buttonReleased( const OIS::JoyStickEvent &arg, int button ){
				SAF_I((m_pTempSection),buttonReleased(arg,button));
				return	true;
			}
	
			bool System::axisMoved( const OIS::JoyStickEvent &arg, int axis ){
				SAF_I((m_pTempSection),axisMoved(arg,axis));
				return	true;
			}
	
			U1 System::LoadPlugin(){
	
				AString	strGamePluginName	=	GetGlobalSetting().m_EngineParam.strGamePlugin;
	 			Common::Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(strGamePluginName);
				
	 			IniFile	cfgFile;
	 			if(!cfgFile.LoadFileFromMemory(pData->buff,pData->size))
	 				return false;
	 
	 			m_pPluginMgr	=	new	Common::PluginFactory();
	
				StringArray	strPluginArray;
				strPluginArray.resize(g_uiNumPlugin);
				strPluginArray[0]	=	"Loading";
				strPluginArray[1]	=	"Data";
				//strPluginArray[2]	=	"Custom";
	 
	 			for(UInt	i=0;i<g_uiNumPlugin;i++){
	 				//获取插件名
	 				m_strPluginNameArray[i]	=	cfgFile.Get("Plugin",(AChar*)strPluginArray[i].c_str());
	 				if(!m_strPluginNameArray[i].empty()){
						
	 					//加载插件	并初始化
						Plugin*		p		=	dynamic_cast<Plugin*>(m_pPluginMgr->NewProduct(m_strPluginNameArray[i],"Plugin"));
						
						if(!p->AddRef()){
							m_pPluginMgr->Destroy(p);
							p=NULL;
							continue;
						}
						p->SetFactory(m_pPluginMgr);
	 					m_pPluginMgr->Insert(p);
	
						p->Excute(Plugin::enInit);
				
	 				}
	 			}
	
				//m_pSection	=	dynamic_cast<Section*>(m_pPluginMgr->GetProduct(m_strPluginNameArray[0]));
				return true;
			}
	
			U1 System::UnLoadPlugin(){
				if(m_pPluginMgr==NULL)
					return true;
				//获取插件工厂
				IFactory*	pPluginFactory	=	m_pPluginMgr;//GetFactory("Plugin");
	
				if(pPluginFactory==NULL)
					return false;
				for(SInt	i=g_uiNumPlugin	-	1;i>=0;i--){
					if(m_strPluginNameArray[i].empty())
						continue;
					//卸载插件
					Plugin*	p	=	dynamic_cast<Plugin*>(pPluginFactory->GetProduct(m_strPluginNameArray[i]));
					if(p==NULL)
						continue;
					p->Excute(Plugin::enRelease);
				}
				pPluginFactory->DestroyAllProduct();
	
				delete	m_pPluginMgr;
				m_pPluginMgr	=	NULL;
				return	true;
				//return true;
			}
	
			U1 System::Stop(){
	
				return	true;
			}
	
			U1 System::LoadSection(){
				
				AString	strGamePluginName	=	GetGlobalSetting().m_EngineParam.strGamePlugin;
				Common::Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(strGamePluginName);
	
				IniFile	cfgFile;
				if(!cfgFile.LoadFileFromMemory(pData))
					return false;
	
				m_strFirstSectionName	=	cfgFile.Get("Plugin","FirstSection");
	
				StringVector*	lstSectionName	=	cfgFile.GetStringList("Section",cfgFile.GetSort("Section"));
				if(lstSectionName==NULL)
					return	false;
				StringVector&	lst	=	*lstSectionName;
	
				UInt	uiSize	=	lst.size();
				for(UInt i=0;i<uiSize;i++){
					if(lst[i].empty())
						continue;
					Plugin*	pPlugin	=	new	Plugin(lst[i]+".dll",NULL);
					if(!pPlugin->AddRef()){
						pPlugin->Destroy();
						SAF_D(pPlugin);
						continue;
					}
					m_mapSection[lst[i].c_str()]	=	pPlugin;
				}
				return	true;
			}
	
			U1 System::UnLoadSection(){
				std::map<AString,Plugin*>::iterator	i	=	m_mapSection.begin();
				for(;i!=m_mapSection.end();i++){
					Plugin*	p	=	i->second;
					if(p==NULL)
						continue;
					p->Excute(Plugin::enStop);
					p->Excute(Plugin::enRelease);
					p->Destroy();
					SAF_D(p);
				}
				m_mapSection.clear();
				return	true;
			}
	
			void System::SwitchSection( AString strName ){
				//开始进入进度条场景
				m_pCurrentSection->OnLeave();
				m_pCurrentSection	=	GetGlobal().m_pLoadingSection;
				m_pCurrentSection->OnEnter();
				
	
				//Render::System::GetSingleton()->StartThread();
				//更新进度条
				m_pCurrentSection->OnLoadingStart();
				m_pCurrentSection->OnLoadingProcess(1.0f);
	
				AString	str	=	strName;
				if(str.empty())
					str	=	"Login";
	
				Plugin*		pLastPlugin	=	m_pCurrentPlugin;
	
				m_pCurrentPlugin		=	m_mapSection[str.c_str()];
	
				//初始化下一个场景
				m_pCurrentPlugin->Excute(Plugin::enInit);
				m_pCurrentPlugin->Excute(Plugin::enStart);
	
				//卸载上一个场景
				if(pLastPlugin!=NULL){
					pLastPlugin->Excute(Plugin::enStop);
					pLastPlugin->Excute(Plugin::enRelease);
				}
	
				//下一场景切换完毕
				m_pCurrentSection->OnLeave();
				m_pCurrentSection	=	*m_ppSection;
				m_pCurrentSection->OnEnter();
			}
	
			void System::SetNextSection( AString strSectionName ){
				m_CS.Enter();
				m_strNextSectionName	=	strSectionName;
				m_CS.Leave();
			}	
	
			void System::SetDebugString( AString strDebugString ){
// 				if(g_pText!=NULL)
// 					g_pText->SetText(strDebugString);
			}
		}
	}
};