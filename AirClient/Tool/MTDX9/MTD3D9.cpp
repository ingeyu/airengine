#include "MTD3D9.h"
#include "MTDevice9.h"

#pragma comment(lib,"detours")
//#pragma comment(lib,"d3d9")

typedef	IDirect3D9* (STDMETHODCALLTYPE	*	T_Direct3DCreate9		)(UINT );
typedef	HRESULT		(STDMETHODCALLTYPE	*	T_Direct3DCreate9Ex	)(UINT ,IDirect3D9Ex**);

T_Direct3DCreate9	ST_Direct3DCreate9		=	NULL;//Direct3DCreate9;
T_Direct3DCreate9Ex	ST_Direct3DCreate9Ex	=	NULL;//Direct3DCreate9Ex;

HRESULT	(STDMETHODCALLTYPE *ST_IDirect3D9_CreateDevice)(IDirect3D9 * This,UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) =	NULL;
HRESULT	STDMETHODCALLTYPE MT_IDirect3D9_CreateDevice(IDirect3D9 * This,UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	BehaviorFlags	|=	D3DCREATE_MULTITHREADED;
	pPresentationParameters->PresentationInterval	=	D3DPRESENT_INTERVAL_IMMEDIATE;
	HRESULT	hr	=	ST_IDirect3D9_CreateDevice(This,Adapter,DeviceType,hFocusWindow,BehaviorFlags,pPresentationParameters,ppReturnedDeviceInterface);
	if(SUCCEEDED(hr)){
		Hook_IDirect3DDevice9(*ppReturnedDeviceInterface);
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


IDirect3D9* WINAPI	MT_Direct3DCreate9( UINT SDKVersion )
{
	IDirect3D9*	pD3D9	=	ST_Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D9!=NULL){
		ST_IDirect3D9_CreateDevice	=	pD3D9->lpVtbl->CreateDevice;

		DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)ST_IDirect3D9_CreateDevice, MT_IDirect3D9_CreateDevice);
        DetourTransactionCommit();
	}
	return	pD3D9;
}

HRESULT		WINAPI	MT_Direct3DCreate9Ex( UINT SDKVersion ,IDirect3D9Ex**	ppD3D9)
{
	HRESULT	hr	=	ST_Direct3DCreate9Ex(D3D_SDK_VERSION,ppD3D9);
	if((*ppD3D9)!=NULL){
		ST_IDirect3D9_CreateDeviceEx	=	(*ppD3D9)->lpVtbl->CreateDeviceEx;

		DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)ST_IDirect3D9_CreateDeviceEx, MT_IDirect3D9_CreateDeviceEx);
        DetourTransactionCommit();
	}

	return	hr;
}


extern T_D3DPERF_BeginEvent							ST_D3DPERF_BeginEvent	;
extern T_D3DPERF_EndEvent							ST_D3DPERF_EndEvent		;
extern T_D3DPERF_SetMarker							ST_D3DPERF_SetMarker	;

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    //if (DetourIsHelperProcess()) {
    //    return TRUE;
    //}
    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();

		HMODULE	hD3D9			=	GetModuleHandleW(L"d3d9.dll");
		ST_Direct3DCreate9		=	(T_Direct3DCreate9)GetProcAddress(hD3D9,"Direct3DCreate9");
		ST_Direct3DCreate9Ex	=	(T_Direct3DCreate9Ex)GetProcAddress(hD3D9,"Direct3DCreate9Ex");
		ST_D3DPERF_BeginEvent	=	(T_D3DPERF_BeginEvent)GetProcAddress(hD3D9,"D3DPERF_BeginEvent");
		ST_D3DPERF_EndEvent		=	(T_D3DPERF_EndEvent)GetProcAddress(hD3D9,"D3DPERF_EndEvent");
		ST_D3DPERF_SetMarker	=	(T_D3DPERF_SetMarker)GetProcAddress(hD3D9,"D3DPERF_SetMarker");
		
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)ST_Direct3DCreate9,		MT_Direct3DCreate9);
		DetourAttach(&(PVOID&)ST_Direct3DCreate9Ex,		MT_Direct3DCreate9Ex);
		DetourAttach(&(PVOID&)ST_D3DPERF_BeginEvent,	MT_PIX_D3DPERF_BeginEvent);
		DetourAttach(&(PVOID&)ST_D3DPERF_EndEvent,		MT_PIX_D3DPERF_EndEvent);
		DetourAttach(&(PVOID&)ST_D3DPERF_SetMarker,		MT_PIX_D3DPERF_SetMarker);
        DetourTransactionCommit();

// 		if(FALSE==D3DXCheckVersion(D3D_SDK_VERSION,D3DX_SDK_VERSION)){
// 			OutputDebugStringA("D3DX_SDK_VERSION ERROR!\n");
// 		}
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)ST_Direct3DCreate9, MT_Direct3DCreate9);
		DetourDetach(&(PVOID&)ST_Direct3DCreate9Ex, MT_Direct3DCreate9Ex);
        DetourTransactionCommit();
    }
    return TRUE;
}
