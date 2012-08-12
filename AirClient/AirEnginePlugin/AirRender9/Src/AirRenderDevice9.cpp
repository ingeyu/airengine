#include "AirRenderDevice9.h"
#include "AirRenderGlobal9.h"
#include "AirInterfaceGameSystem.h"
#include "AirInterfaceUISystem.h"
//#include "AirInterfaceEngine.h"
#include "AirInterfaceNetSystem.h"
//#include "AirRenderBuffPool9.h"


namespace Air{
	
	namespace	Client{
		namespace	Render{
	
	
			LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ){
				switch(msg){
					case WM_SIZE:{
						Render::ISystem*	pRenderSys	=	GetGlobalSetting().m_pRenderSystem;
	
						if(wParam	==	SIZE_MINIMIZED){
	// 						if(pRenderSys!=NULL){
	// 							pRenderSys->PauseThread();
	// 						}
						}else	if(	wParam	==	SIZE_RESTORED){
							DisplayParam&	dParam	=	GetGlobalSetting().m_DisplayParam;
							RECT rect;
							GetWindowRect(hwnd,&rect);
							SInt	iWidth	=	rect.right	-	rect.left;
							SInt	iHeight	=	rect.bottom	-	rect.top;
	
							dParam.iWidth	=	iWidth;
							dParam.iHeight	=	iHeight;
							GetGlobal().m_bReseting	=	true;
							GetGlobal().m_pRenderDevice->ChangeSize();
							GetGlobal().m_bReseting	=	false;
	
						}else	if(	wParam	==	SIZE_MAXIMIZED){
								DisplayParam&	dParam	=	GetGlobalSetting().m_DisplayParam;
								RECT rect;
								GetClientRect(hwnd,&rect);
								SInt	iWidth	=	rect.right	-	rect.left;
								SInt	iHeight	=	rect.bottom	-	rect.top;
	
								dParam.iWidth	=	iWidth;
								dParam.iHeight	=	iHeight;
								GetGlobal().m_bReseting	=	true;
								GetGlobal().m_pRenderDevice->ChangeSize();
								GetGlobal().m_bReseting	=	false;
						}
						break;}
					case WM_GETMINMAXINFO:{
						((MINMAXINFO*)lParam)->ptMinTrackSize.x	=	200;
						((MINMAXINFO*)lParam)->ptMinTrackSize.x	=	200;
						break;}
					case WM_CLOSE:{
						HMENU hMenu;
						hMenu = GetMenu( hwnd );
						if( hMenu != NULL )
							DestroyMenu( hMenu );
						DestroyWindow( hwnd );
						GetGlobalSetting().m_EngineParam.hWnd	=	NULL;
						return 0;
						break;}
					case WM_DESTROY:{
						::PostQuitMessage(0);
						break;}
				}
	
				//渲染界面
				UI::ISystem*	pUISystem		=	GetGlobalSetting().m_pUISystem;
				if(pUISystem!=NULL){
					pUISystem->MsgProc(hwnd,msg,wParam,lParam,NULL,NULL);
				}
	
	
				if(	(	msg	== WM_SYSKEYDOWN	||	msg	== WM_SYSKEYUP ) && 
					(	wParam	== VK_F10			||	wParam	== VK_MENU)){
						return 0;
				}
	
				if(WM_SETCURSOR	==	msg)
					return 0;
				return ::DefWindowProc(hwnd, msg, wParam, lParam);
			}
	
			Device9::Device9( Info* pInfo ){
				m_Info		=	*pInfo;
				m_bPause	=	false;
				m_pDevice	=	NULL;
				m_bNeedFullScreen	=	false;
				m_pDefaultState		=	NULL;
			}
	
			U1 Device9::CreateWin(){
				EngineParam&	eParam	=	GetGlobalSetting().m_EngineParam;
				//如果已经创建窗口  则直接返回
				if(eParam.hWnd!=NULL)
					return	true;
				DisplayParam&	dParam	=	GetGlobalSetting().m_DisplayParam;
	
	
				HINSTANCE	hInstance = ( HINSTANCE )GetModuleHandle( NULL );
	
				WNDCLASSW wc;
	
				//AString	strName	=	;
				WString		wStr	=	L"ZuEngine";//	=	Common::::Acsi2WideByte(strName);
	
	
	
				wc.style         = CS_DBLCLKS;
				wc.lpfnWndProc   = (WNDPROC)WndProc; 
				wc.cbClsExtra    = 0;
				wc.cbWndExtra    = 0;
				wc.hInstance     = hInstance;
				wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
				wc.hCursor       = LoadCursor(0, IDC_ARROW);
				wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
				wc.lpszMenuName  = 0;
				wc.lpszClassName = L"DirectXWindow";
	
				if( !RegisterClassW(&wc) ){
					::MessageBoxA(0, "RegisterClass() - FAILED", 0, 0);
					return false;
				}
				eParam.hWnd =	::CreateWindowW(	L"DirectXWindow",
													wStr.c_str(),
													WS_OVERLAPPEDWINDOW, 
													0,
													0, 
													dParam.iWidth, 
													dParam.iHeight,
													eParam.hParentWnd /*parent hwnd*/, 
													0 /* menu */, 
													hInstance, 
													0 /*extra*/);
				//SetWindowTextA(eParam.hWnd,m_strWindowName.c_str());
	
				::ShowWindow(eParam.hWnd, SW_SHOW);
				::UpdateWindow(eParam.hWnd);
				return	true;
			}
	
			U1 Device9::DestroyWin(){
				EngineParam&	eParam	=	GetGlobalSetting().m_EngineParam;
				if(eParam.hWnd!=NULL){
					DestroyWindow(eParam.hWnd);
					eParam.hWnd	=	NULL;
				}
				return	true;
			}
	
			U1 Device9::Create(){
				//创建窗口
				CreateWin();
				//创建D3D
				CreateD3D();
				//创建设备
				CreateDevice(D3DADAPTER_DEFAULT);
				//初始化设备
				InitDeviceState();
	
				//申请缓冲池
				//BufferPoolManager::GetSingleton();
	
				return	true;
			}
	
			U1 Device9::Destroy(){
				//释放缓冲池
				//BufferPoolManager::ReleaseSingleton();//->ReleaseSingleton();
	
				DestroyDevice();
				DestroyWin();
	
				SAF_R(m_pD3D);
	
				return	true;
			}
	
			U1 Device9::CreateDevice(UInt uiAdapter){
				HRESULT hr = 0;
	
				//判断是否支持抗锯齿
				if(m_Info.bWindow){
					if(m_Info.iMSAAType	>	D3DMULTISAMPLE_NONE	&&	m_Info.iMSAAType	<	m_vecAdapter[uiAdapter].vecMSAAWindow.size()){
						DWORD dQuality	=	m_vecAdapter[uiAdapter].vecMSAAWindow[m_Info.iMSAAType];
						if(m_Info.iMSAAQuality	>=	dQuality){
							m_Info.iMSAAQuality	=	dQuality	-	1;	
						}
					}else{
						m_Info.iMSAAType	=	D3DMULTISAMPLE_NONE;
						m_Info.iMSAAQuality	=	0;
					}
				}else{
					if(m_Info.iMSAAType	>	D3DMULTISAMPLE_NONE	&&	m_Info.iMSAAType	<	m_vecAdapter[uiAdapter].vecMSAAFull.size()){
						DWORD dQuality	=	m_vecAdapter[uiAdapter].vecMSAAFull[m_Info.iMSAAType];
						if(m_Info.iMSAAQuality	>=	dQuality){
							m_Info.iMSAAQuality	=	dQuality	-	1;	
						}
					}else{
						m_Info.iMSAAType	=	D3DMULTISAMPLE_NONE;
						m_Info.iMSAAQuality	=	0;
					}
				}
	
				UINT AdapterToUse		=	D3DADAPTER_DEFAULT;
				D3DDEVTYPE DeviceType	=	D3DDEVTYPE_HAL;
	#ifdef SHIPPING_VERSION
				// When building a shipping version, disable PerfHUD (opt-out)
	#else
				// Look for 'NVIDIA PerfHUD' adapter
				// If it is present, override default settings
				for (UINT Adapter=0;Adapter<m_pD3D->GetAdapterCount();Adapter++)
				{
					D3DADAPTER_IDENTIFIER9 Identifier;
					HRESULT Res;
					Res = m_pD3D->GetAdapterIdentifier(Adapter,0,&Identifier);
					if (strstr(Identifier.Description,"PerfHUD") != 0)
					{
						AdapterToUse=Adapter;
						DeviceType=D3DDEVTYPE_REF;
						break;
					}
				}
	#endif
	
	
				EngineParam&	eParam	=	GetGlobalSetting().m_EngineParam;
	
				//D3DPRESENT_PARAMETERS& d3dpp	=	m_DeviceParam;
				m_DeviceParam.BackBufferWidth            = m_Info.iWidth;
				m_DeviceParam.BackBufferHeight           = m_Info.iHeight;
	 			m_DeviceParam.BackBufferFormat           = D3DFMT_X8R8G8B8;
	 			m_DeviceParam.BackBufferCount            = 2;
	 			m_DeviceParam.MultiSampleType            = (D3DMULTISAMPLE_TYPE)m_Info.iMSAAType;
	 			m_DeviceParam.MultiSampleQuality         = m_Info.iMSAAQuality;
	 			m_DeviceParam.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	 			m_DeviceParam.hDeviceWindow              = eParam.hWnd;
	 			m_DeviceParam.Windowed                   = m_Info.bWindow;
	 			m_DeviceParam.EnableAutoDepthStencil     = true; 
	 			m_DeviceParam.AutoDepthStencilFormat     = D3DFMT_D24X8;
	 			m_DeviceParam.Flags                      = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	 			m_DeviceParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	 			m_DeviceParam.PresentationInterval       = D3DPRESENT_INTERVAL_ONE	|	D3DPRESENT_DONOTWAIT;
	
				hr	=	m_pD3D->CreateDevice(	AdapterToUse,
												DeviceType,
												eParam.hWnd,
	#ifdef	_DEBUG
												D3DCREATE_FPU_PRESERVE	|	D3DCREATE_HARDWARE_VERTEXPROCESSING	|	D3DCREATE_MULTITHREADED,
	#else
												D3DCREATE_PUREDEVICE	|	D3DCREATE_FPU_PRESERVE	|	D3DCREATE_HARDWARE_VERTEXPROCESSING	|	D3DCREATE_MULTITHREADED,
	#endif
												&m_DeviceParam,
												&m_pDevice);
				if(m_pDevice!=NULL){
					IDirect3DSurface9*	pBackSurface	=	NULL;
					m_pDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pBackSurface);
					D3DSURFACE_DESC	sDesc;
					pBackSurface->GetDesc(&sDesc);
					SAF_R(pBackSurface);
				}
				if(FAILED(hr)){
					RenderLogWarnning("创建设备失败","设备参数无效",hr);
				}
				SAF_R(m_pD3D);
	
				GetGlobal().m_pDevice	=	m_pDevice;
				return	true;
			}
	
			U1 Device9::DestroyDevice(){
				SAF_R(m_pDevice);
	
				GetGlobal().m_pDevice	=	NULL;
				return	true;
			}
	
			U1 Device9::CreateD3D(){
				// Step 1: Create the IDirect3D9 object.
				IDirect3D9* pD3D	=	Direct3DCreate9(D3D_SDK_VERSION);
	
				if( pD3D	==	NULL ){
					::MessageBoxA(0, "Direct3DCreate9() - FAILED", 0, 0);
					return false;
				}
				//获取显示设备数量
				UInt	uiAdapterCount	=	pD3D->GetAdapterCount();
				m_vecAdapter.resize(uiAdapterCount);
	
				//遍历显卡
				for(UInt i=0;i<uiAdapterCount;i++){
					//获取设备信息
					pD3D->GetAdapterIdentifier(i,0,&m_vecAdapter[i].identifier);
					//获取设备显示器
					m_vecAdapter[i].monitor	=	pD3D->GetAdapterMonitor(i);
					//获取设备显示模式
					pD3D->GetAdapterDisplayMode(i,&m_vecAdapter[i].displayMode);
					//枚举所有支持的显示模式
					UInt uiModeCount	=	pD3D->GetAdapterModeCount(i,D3DFMT_X8R8G8B8);
					m_vecAdapter[i].vecDisplayMode.resize(uiModeCount);
					for(UInt j=0;j<uiModeCount;j++){
						pD3D->EnumAdapterModes(i,D3DFMT_X8R8G8B8,j,&m_vecAdapter[i].vecDisplayMode[j]);
					}
					//获取设备能力
					pD3D->GetDeviceCaps(i,D3DDEVTYPE_HAL,&m_vecAdapter[i].caps);
	
					//m_vecAdapter[i].caps.MaxVertexShaderConst
					//检测抗锯齿能力
					m_vecAdapter[i].vecMSAAWindow.resize(D3DMULTISAMPLE_16_SAMPLES+1);
					m_vecAdapter[i].vecMSAAFull.resize(D3DMULTISAMPLE_16_SAMPLES+1);
					for(UInt j=0;j<=D3DMULTISAMPLE_16_SAMPLES;j++){
						DWORD	uiQuality	=	0;
						//获取窗口模式下抗锯齿能力
						pD3D->CheckDeviceMultiSampleType(i,D3DDEVTYPE_HAL,D3DFMT_X8R8G8B8,true,(D3DMULTISAMPLE_TYPE)j,&uiQuality);
						m_vecAdapter[i].vecMSAAWindow[j]	=	uiQuality;
	// 					AChar str[128];
	// 					sprintf_s(str,128,"Windowd %d - %d \n",j,uiQuality);
	// 					OutputDebugStringA(str);
						//获取全屏模式下抗锯齿能力
						pD3D->CheckDeviceMultiSampleType(i,D3DDEVTYPE_HAL,D3DFMT_X8R8G8B8,false,(D3DMULTISAMPLE_TYPE)j,&uiQuality);
						m_vecAdapter[i].vecMSAAFull[j]		=	uiQuality;
	// 					sprintf_s(str,128,"FullScreen %d - %d \n",j,uiQuality);
	// 					OutputDebugStringA(str);
					}
				}
	
				m_pD3D	=	pD3D;
				return	true;
			}
	
			U1 Device9::ChangeSize(){
				if(m_pDevice==NULL)
					return	true;
				DisplayParam&	dParam	=	GetGlobalSetting().m_DisplayParam;
	
				m_Info.iWidth	=	dParam.iWidth;
				m_Info.iHeight	=	dParam.iHeight;
	
				Lost();
				m_DeviceParam.BackBufferWidth	=	m_Info.iWidth;
				m_DeviceParam.BackBufferHeight	=	m_Info.iHeight;
	
				return	Reset();
			}
	
			U1 Device9::FullScreen(){
				
				DisplayParam&	dParam	=	GetGlobalSetting().m_DisplayParam;
				U1&	bWindowd			=	dParam.bWindow;
				bWindowd				=	!bWindowd;
				m_DeviceParam.Windowed	=	bWindowd;
	
				Lost();
				static	SInt	w	=	dParam.iWidth;
				static	SInt	h	=	dParam.iHeight;
	//			if(bWindowd){
	// 				dParam.iWidth					=	w;
	// 				dParam.iHeight					=	h;
					m_DeviceParam.BackBufferWidth	=	dParam.iWidth;
					m_DeviceParam.BackBufferHeight	=	dParam.iHeight;
					//ShowWindow(GetGlobalSetting().m_EngineParam.hWnd,SW_SHOW);
	// 				AChar str[128];
	// 				sprintf_s(str,128,"窗口大小 %d %d\n",dParam.iWidth,dParam.iHeight);
	// 				OutputDebugStringA(str);
	// 				OutputDebugStringA("窗口化\n");
	// 				
	// 			}else{
	// 				w	=	dParam.iWidth;
	// 				h	=	dParam.iHeight;
	// 				AChar str[128];
	// 				sprintf_s(str,128,"窗口大小 %d %d\n",dParam.iWidth,dParam.iHeight);
	// 				OutputDebugStringA(str);
	// 
	// 				OutputDebugStringA("全屏\n");
	// 			}
				Reset();
				//if(bWindowd){
				//	MoveWindow(GetGlobalSetting().m_EngineParam.hWnd,0,0,w,h,true);
				//}
				return	true;
			}
	
			U1 Device9::Lost(){
				GetGlobalSetting().m_pRenderSystem->OnD3DLostDevice();
				return	true;
			}
	
			U1 Device9::Reset(){
				//当DX9使用多线程模式时 重置设备只能够 使用创建windows窗口的那条线程来调用
				//否则会出现无效调用 
				//可以参考http://www.codeguru.com/forum/archive/index.php/t-298417.html
				HRESULT	hr	=	m_pDevice->Reset(&m_DeviceParam);
				OutputDebugStringA(DXGetErrorDescriptionA(hr));
	
				if(hr	==	D3D_OK){
					GetGlobalSetting().m_pRenderSystem->OnD3DResetDevice();
					if(GetGlobalSetting().m_pUISystem!=NULL){
						GetGlobalSetting().m_pUISystem->OnResetDevice();
					}
				}else if( hr == D3DERR_DEVICELOST ){
					//Lost();
					return	true;
				}else	if(hr	==	D3DERR_DEVICENOTRESET){
					hr	=	m_pDevice->Reset(&m_DeviceParam);
					return	false;
				}else{
					MessageBoxA(NULL,"设备重置失败",NULL,NULL);
					PostMessage(GetGlobalSetting().m_EngineParam.hWnd,WM_DESTROY,NULL,NULL);
					return	false;
				}
	
				return	true;
			}
	
			U1 Device9::RenderOneFrame(){
				if(!CheckChange())
					return	false;
	
	
				//计算与上一帧渲染的时间间隔 以及从程序启动到现在的总时间
				static	Real	fLastTime			=	timeGetTime()*0.001f;
				static	ShaderShareParam&	sParam	=	GetGlobalSetting().m_ShaderParam;
	
				Real	fCurrentTime				=	timeGetTime()*0.001f;
				sParam.m_fTimeDelta					=	fCurrentTime	-	fLastTime;
				sParam.m_fTotalTime					+=	sParam.m_fTimeDelta;
	
				fLastTime							=	fCurrentTime;
	
				
	//   			if(sParam.m_fTimeDelta	<	0.016f){
	//   				Sleep(16 - sParam.m_fTimeDelta*1000.0f);
	//   			}
	 			static	UInt	uiFrameCount	=	0;
	 			uiFrameCount++;
	 			static	Real	fTime			=	0;
	 			fTime+=	sParam.m_fTimeDelta;
	 
	 			if(fTime	>	2.0f){
	 				Real	fps	=	uiFrameCount/fTime;
	 				AChar	str[128];
	 				sprintf_s(str,128,"[Render]FPS=%f\n",fps);
	 				OutputDebugStringA(str);
	 				uiFrameCount=0;
	 				fps	=	0;fTime=0;
	 			}
	
				HRESULT	hr	=	m_pDevice->TestCooperativeLevel();
				// Test the cooperative level to see if it's okay to render.
				if(D3D_OK	==	hr){
	
				}else if( D3DERR_DEVICELOST == hr ){
					// The device has been lost but cannot be reset at this time.
					// So wait until it can be reset.
					::OutputDebugStringA("设备丢失\n");
					return	true;
				}else if(D3DERR_DEVICENOTRESET	==	hr){
					//设备已恢复 需要重置
	// 				Lost();
	 				Reset();
					return	true;
				}else{
					::OutputDebugStringA("设备出现未知错误\n");
					return	false;
				}
	
				//渲染目标
				RenderTarget();
				//最终渲染
				RenderFinal();
				//提交渲染结果
				hr = m_pDevice->Present( NULL, NULL, NULL, NULL );
				//判断是否设备丢失
				if( D3DERR_DEVICELOST == hr ){
					//Lost();
					::OutputDebugStringA("提交之后设备丢失\n");
				}else if( D3DERR_DRIVERINTERNALERROR == hr ){
					// When D3DERR_DRIVERINTERNALERROR is returned from Present(),
					// the application can do one of the following:
					// 
					// - End, with the pop-up window saying that the application cannot continue 
					//   because of problems in the display adapter and that the user should 
					//   contact the adapter manufacturer.
					//
					// - Attempt to restart by calling IDirect3DDevice9::Reset, which is essentially the same 
					//   path as recovering from a lost device. If IDirect3DDevice9::Reset fails with 
					//   D3DERR_DRIVERINTERNALERROR, the application should end immediately with the message 
					//   that the user should contact the adapter manufacturer.
					// 
					// The framework attempts the path of resetting the device
					// 
					//GetDXUTState().SetDeviceLost( true );
					Lost();
				}
				return	true;
			}
	
			U1 Device9::RenderTarget(){

	
				static	UI::ISystem*&	pUISystem	=	GetGlobalSetting().m_pUISystem;
				if(pUISystem!=NULL){
					pUISystem->RenderTarget();
				}
				return	true;
			}
	
			U1 Device9::RenderFinal(){
				HRESULT	hr	=	S_OK;
	
				hr	=	m_pDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0x55555555,1.0f,0);
				hr	=	m_pDevice->BeginScene();
	
	
				if(FAILED(hr))
					return	false;
	

	
				static	UI::ISystem*&	pUISystem	=	GetGlobalSetting().m_pUISystem;
				if(pUISystem!=NULL){
					pUISystem->Render();
				}
	
				m_pDevice->EndScene();
	
				
				return	true;
			}
	
			U1 Device9::SaveScreen( ){
	
				IDirect3DSurface9*	pSurface	=	NULL;
				m_pDevice->GetRenderTarget(0,&pSurface);
				AString	strSaveName	=	m_strSaveScreenFileName	+	".dds";
				D3DXSaveSurfaceToFileA(strSaveName.c_str(),D3DXIFF_DDS,pSurface,NULL,NULL);
				SAF_R(pSurface);
	
				return	true;
			}
	
			U1 Device9::SetNeedSaveScreen( CAString& strName ){
				m_strSaveScreenFileName	=	strName;
	
				return	true;
			}
	
			U1 Device9::CheckChange(){
				if(!m_strSaveScreenFileName.empty()){
					SaveScreen();
					m_strSaveScreenFileName.clear();
				}
				//检查是否需要切换全屏
				if(m_bNeedFullScreen){
					FullScreen();
					m_bNeedFullScreen	=	false;
				}
	
				return	true;
			}
	
			U1 Device9::SetNeedFullScreen(){
				m_bNeedFullScreen	=	true;
				return	true;
			}
	
			void Device9::InitDeviceState(){
	
				//m_pDevice->SetRenderState()
	
				for(UInt i=0;i<16;i++){
					m_pDevice->SetSamplerState(i,	D3DSAMP_MAGFILTER,	D3DTEXF_POINT);
					m_pDevice->SetSamplerState(i,	D3DSAMP_MINFILTER,	D3DTEXF_POINT);
					m_pDevice->SetSamplerState(i,	D3DSAMP_MIPFILTER,	D3DTEXF_POINT);
					m_pDevice->SetSamplerState(i,	D3DSAMP_ADDRESSU,	D3DTADDRESS_WRAP);
					m_pDevice->SetSamplerState(i,	D3DSAMP_ADDRESSV,	D3DTADDRESS_WRAP);
					m_pDevice->SetSamplerState(i,	D3DSAMP_ADDRESSW,	D3DTADDRESS_WRAP);
				}
	
				for(UInt i=1;i<=4;i++){
					m_pDevice->SetSamplerState(D3DDMAPSAMPLER+i,	D3DSAMP_MAGFILTER,	D3DTEXF_POINT);
					m_pDevice->SetSamplerState(D3DDMAPSAMPLER+i,	D3DSAMP_MINFILTER,	D3DTEXF_POINT);
					m_pDevice->SetSamplerState(D3DDMAPSAMPLER+i,	D3DSAMP_MIPFILTER,	D3DTEXF_POINT);
					m_pDevice->SetSamplerState(D3DDMAPSAMPLER+i,	D3DSAMP_ADDRESSU,	D3DTADDRESS_WRAP);
					m_pDevice->SetSamplerState(D3DDMAPSAMPLER+i,	D3DSAMP_ADDRESSV,	D3DTADDRESS_WRAP);
					m_pDevice->SetSamplerState(D3DDMAPSAMPLER+i,	D3DSAMP_ADDRESSW,	D3DTADDRESS_WRAP);
				}
	
				//	创建状态
				//m_pDevice->CreateStateBlock(D3DSBT_ALL,&m_pDefaultState);
				//	捕获当前状态
				//m_pDefaultState->Capture();
			}
		}
	}
};