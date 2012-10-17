#include "MTD3D9.h"
#include "MTDevice9.h"

//#pragma comment(lib,"detours")
#pragma comment(lib,"d3d9")

typedef	IDirect3D9* (STDMETHODCALLTYPE	*	T_Direct3DCreate9		)(UINT );
typedef	HRESULT		(STDMETHODCALLTYPE	*	T_Direct3DCreate9Ex	)(UINT ,IDirect3D9Ex**);

T_Direct3DCreate9	ST_Direct3DCreate9		=	NULL;//Direct3DCreate9;
T_Direct3DCreate9Ex	ST_Direct3DCreate9Ex	=	NULL;//Direct3DCreate9Ex;




HRESULT	(STDMETHODCALLTYPE *ST_IDirect3D9_CreateDevice)(IDirect3D9 * This,UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) =	NULL;
HRESULT	STDMETHODCALLTYPE MT_IDirect3D9_CreateDevice(IDirect3D9 * This,UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	bool	bHook	=	true;

	if(DeviceType==D3DDEVTYPE_HAL){
		BehaviorFlags	|=	D3DCREATE_MULTITHREADED;//|D3DCREATE_PUREDEVICE;
		//pPresentationParameters->PresentationInterval	=	D3DPRESENT_INTERVAL_IMMEDIATE;
		bHook	=	true;
		//Adapter	=	1;
		//DeviceType	=	D3DDEVTYPE_REF;
	}else{
		bHook	=	false;
	}
	HRESULT	hr	=	ST_IDirect3D9_CreateDevice(This,Adapter,DeviceType,hFocusWindow,BehaviorFlags,pPresentationParameters,ppReturnedDeviceInterface);
	if(SUCCEEDED(hr)){
		if(bHook){
			Hook_IDirect3DDevice9(*ppReturnedDeviceInterface);
		}
		OutputDebugStringA("MTDiectX9.dll  CreateDevice!\n");
	}
	return	hr;
};

HRESULT	(STDMETHODCALLTYPE *ST_IDirect3D9_CreateDeviceEx)(IDirect3D9Ex * This,UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface) =	NULL;
HRESULT	STDMETHODCALLTYPE MT_IDirect3D9_CreateDeviceEx(IDirect3D9Ex * This,UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface) \
{
	BehaviorFlags	|=	D3DCREATE_MULTITHREADED;
	pPresentationParameters->PresentationInterval	=	D3DPRESENT_INTERVAL_IMMEDIATE;
	return	ST_IDirect3D9_CreateDeviceEx(This,Adapter,DeviceType,hFocusWindow,BehaviorFlags,pPresentationParameters,pFullscreenDisplayMode,ppReturnedDeviceInterface);
};
bool	bHasHookDevice	=	false;

IDirect3D9* WINAPI	MT_Direct3DCreate9( UINT SDKVersion )
{
	OutputDebugStringA("MTDiectX9.dll  Direct3DCreate9	!\n");

	IDirect3D9*	pD3D9	=	ST_Direct3DCreate9(SDKVersion);
	if(pD3D9!=NULL){
		
		if(!bHasHookDevice){
			ST_IDirect3D9_CreateDevice	=	pD3D9->lpVtbl->CreateDevice;
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&(PVOID&)ST_IDirect3D9_CreateDevice, MT_IDirect3D9_CreateDevice);
			DetourTransactionCommit();
			bHasHookDevice	=	true;
		}
	}
	return	pD3D9;
}

HRESULT		WINAPI	MT_Direct3DCreate9Ex( UINT SDKVersion ,IDirect3D9Ex**	ppD3D9)
{
	HRESULT	hr	=	ST_Direct3DCreate9Ex(D3D_SDK_VERSION,ppD3D9);
	if((*ppD3D9)!=NULL){
		
		if(!bHasHookDevice){
			ST_IDirect3D9_CreateDeviceEx	=	(*ppD3D9)->lpVtbl->CreateDeviceEx;
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&(PVOID&)ST_IDirect3D9_CreateDeviceEx, MT_IDirect3D9_CreateDeviceEx);
			DetourTransactionCommit();
			bHasHookDevice	=	true;
		}
	}

	return	hr;
}


extern T_D3DPERF_BeginEvent							ST_D3DPERF_BeginEvent	;
extern T_D3DPERF_EndEvent							ST_D3DPERF_EndEvent		;
extern T_D3DPERF_SetMarker							ST_D3DPERF_SetMarker	;

//__declspec(dllexport)	VOID CALLBACK DetourFinishHelperProcess(HWND, HINSTANCE, LPSTR, INT){
//
//
//};

typedef	HMODULE	(WINAPI	*T_LoadLibraryW)( LPCWSTR lpLibFileName);
T_LoadLibraryW	ST_LoadLibraryW;
HMODULE	WINAPI	MT_LoadLibraryW( LPCWSTR lpLibFileName);

bool	bHasHookKernel	=	false;
void Hook_LoadLibrary(){

	if(bHasHookKernel)
		return;
	HMODULE	hLibrary			=	GetModuleHandle(L"kernel32.dll");

	ST_LoadLibraryW			=	(T_LoadLibraryW)GetProcAddress(hLibrary,"LoadLibraryW");
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)ST_LoadLibraryW,		MT_LoadLibraryW);
	DetourTransactionCommit();

	bHasHookKernel	=	true;
}

void	UnHook_LoadLibrary(){
	if(!bHasHookKernel)
		return;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)ST_LoadLibraryW,		MT_LoadLibraryW);
	DetourTransactionCommit();

	bHasHookKernel	=	false;
}

T_Direct3DCreate9	FindDirect3DCreate9(){
	T_Direct3DCreate9 pIAT	=	Direct3DCreate9;
	U8*	p	=	(U8*)pIAT;

	if(p[0]==0xE9){
		DWORD	offset	=	*(DWORD*)(p+1);

		DWORD*	pJumpAddr	=	(DWORD*)( p+5+offset);
		U8*		pJumpAddrCode	=	(U8*)pJumpAddr;
		if(	pJumpAddrCode[0]	==	0xFF && 
			pJumpAddrCode[1]	==	0x25)
		{
			DWORD offset1		=	*(DWORD*)(pJumpAddrCode+2);
			DWORD*	pJumpAddr1	=	(DWORD*)(*(DWORD*)( offset1));
			U8*	pJumpAddrCode1	=	(U8*)pJumpAddr1;
			if(	pJumpAddrCode1[0]	==	0x8B	&&
				pJumpAddrCode1[1]	==	0xFF	&&
				pJumpAddrCode1[2]	==	0x55	&&
				pJumpAddrCode1[3]	==	0x8B	&&
				pJumpAddrCode1[4]	==	0xEC)
			{
				return	(T_Direct3DCreate9)pJumpAddr1;
			}
		}
	}

	return NULL;
};

bool	bHasHookD3D9	=	false;
void	Hook_D3D9(HMODULE	hLibrary){
	if(hLibrary==NULL)
		return;
	if(bHasHookD3D9)
		return;
	//T_Direct3DCreate9 tTest	=	FindDirect3DCreate9();
	//void* p	=	Direct3DCreate9(D3D_SDK_VERSION);

	ST_Direct3DCreate9		=	(T_Direct3DCreate9)GetProcAddress(hLibrary,"Direct3DCreate9");
	ST_Direct3DCreate9Ex	=	(T_Direct3DCreate9Ex)GetProcAddress(hLibrary,"Direct3DCreate9Ex");
	ST_D3DPERF_BeginEvent	=	(T_D3DPERF_BeginEvent)GetProcAddress(hLibrary,"D3DPERF_BeginEvent");
	ST_D3DPERF_EndEvent		=	(T_D3DPERF_EndEvent)GetProcAddress(hLibrary,"D3DPERF_EndEvent");
	ST_D3DPERF_SetMarker	=	(T_D3DPERF_SetMarker)GetProcAddress(hLibrary,"D3DPERF_SetMarker");

	//void* p	=	tTest(D3D_SDK_VERSION);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)ST_Direct3DCreate9,		MT_Direct3DCreate9);
	if(ST_Direct3DCreate9Ex!=NULL)
		DetourAttach(&(PVOID&)ST_Direct3DCreate9Ex,		MT_Direct3DCreate9Ex);
	DetourAttach(&(PVOID&)ST_D3DPERF_BeginEvent,	MT_PIX_D3DPERF_BeginEvent);
	DetourAttach(&(PVOID&)ST_D3DPERF_EndEvent,		MT_PIX_D3DPERF_EndEvent);
	DetourAttach(&(PVOID&)ST_D3DPERF_SetMarker,		MT_PIX_D3DPERF_SetMarker);
    DetourTransactionCommit();

	bHasHookD3D9	=	true;

	UnHook_LoadLibrary();
};

void	UnHook_D3D9(){
	if(!bHasHookD3D9)
		return;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)ST_Direct3DCreate9,		MT_Direct3DCreate9);
	if(ST_Direct3DCreate9Ex!=NULL)
		DetourDetach(&(PVOID&)ST_Direct3DCreate9Ex,		MT_Direct3DCreate9Ex);
	DetourDetach(&(PVOID&)ST_D3DPERF_BeginEvent,	MT_PIX_D3DPERF_BeginEvent);
	DetourDetach(&(PVOID&)ST_D3DPERF_EndEvent,		MT_PIX_D3DPERF_EndEvent);
	DetourDetach(&(PVOID&)ST_D3DPERF_SetMarker,		MT_PIX_D3DPERF_SetMarker);
    DetourTransactionCommit();
	bHasHookD3D9	=	false;
};





HMODULE	WINAPI	MT_LoadLibraryW( LPCWSTR lpLibFileName){
	HMODULE	hLibrary	=	ST_LoadLibraryW(lpLibFileName);
	if(hLibrary!=NULL){
		if(wcscmp(lpLibFileName,L"d3d9.dll")==0){
			Hook_D3D9(hLibrary);
		}
	}
	return	hLibrary;	
};


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
#if DETOURS_VERSION	==	30000
     if (DetourIsHelperProcess()) {
		 OutputDebugStringA("MTDiectX9.dll  DetourIsHelperProcess!\n");
         return TRUE;
     }
#endif
    if (dwReason == DLL_PROCESS_ATTACH) {
		OutputDebugStringA("MTDiectX9.dll  DLL_PROCESS_ATTACH!\n");

		//static int i=0;
		//while(i++<10)
		//	Sleep(1000);

        DetourRestoreAfterWith();
		
		
		HMODULE	hD3D9			=	GetModuleHandle(L"d3d9.dll");
		//d3d9.dll 还没有加载
		if(hD3D9==NULL){
			Hook_LoadLibrary();
		}else{
			Hook_D3D9(hD3D9);
		}

// 		if(FALSE==D3DXCheckVersion(D3D_SDK_VERSION,D3DX_SDK_VERSION)){
// 			OutputDebugStringA("D3DX_SDK_VERSION ERROR!\n");
// 		}
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
		ReleaseAllResource();
		UnHook_LoadLibrary();
		UnHook_D3D9();
		UnHook_IDirect3DDevice9();
    }
    return TRUE;
}
