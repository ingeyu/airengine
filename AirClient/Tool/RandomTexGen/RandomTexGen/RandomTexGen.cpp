// RandomTexGen.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "d3d9.h"
#include "d3dx9.h"
#pragma comment(lib,"d3d9")
#pragma comment(lib,"d3dx9")

LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device

HRESULT InitD3D( HWND hWnd )
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Most parameters are
	// zeroed out. We set Windowed to TRUE, since we want to do D3D in a
	// window, and then set the SwapEffect to "discard", which is the most
	// efficient method of presenting the back buffer to the display.  And 
	// we request a back buffer format that matches the current desktop display 
	// format.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// Create the Direct3D device. Here we are using the default adapter (most
	// systems only have one, unless they have multiple graphics hardware cards
	// installed) and requesting the HAL (which is saying we want the hardware
	// device rather than a software one). Software vertex processing is 
	// specified since we know it will work on all cards. On cards that support 
	// hardware vertex processing, though, we would see a big performance gain 
	// by specifying hardware vertex processing.
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	// Device state would normally be set here

	return S_OK;
}
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		//Cleanup();
		PostQuitMessage( 0 );
		return 0;

	case WM_PAINT:
		//Render();
		ValidateRect( hWnd, NULL );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}


int _tmain(int argc, _TCHAR* argv[])
{

	double dMax	=	0X7FFF;
	double dMin	=	0;

	SYSTEMTIME t;
	GetSystemTime(&t);
	srand(t.wMilliseconds);
	//if(argc < 2)
	//	return -1;
	if(argc!=4){

		getchar();
		return -2;
	}




	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL
	};
	RegisterClassEx( &wc );

	// Create the application's window
	HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 01: CreateDevice",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
		NULL, NULL, wc.hInstance, NULL );

	if( SUCCEEDED( InitD3D( hWnd ) ) )
	{
		int w		=	wcstol(argv[1],0,10);
		int h		=	wcstol(argv[2],0,10);
		//int chanle	=	wcstol(argv[3],0,10);

		IDirect3DTexture9* pTex	=	NULL;
		g_pd3dDevice->CreateTexture(w,h,1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&pTex,NULL);
		D3DLOCKED_RECT	r;
		pTex->LockRect(0,&r,NULL,D3DLOCK_DISCARD);
		unsigned char* pDst	=	(unsigned char*)r.pBits;
		for(unsigned int i=0;i<h;i++){
			DWORD* p	=	(DWORD*)pDst;
			for(int j=0;j<w;j++){
				p[j]	=	(int)(((double)rand()/dMax)*255)<<24	|
							(int)(((double)rand()/dMax)*255)<<16	|
							(int)(((double)rand()/dMax)*255)<<8	|
							(int)(((double)rand()/dMax)*255);
			}

			pDst+=r.Pitch;
		}
		pTex->UnlockRect(0);

		D3DXSaveTextureToFile(argv[3],D3DXIFF_DDS,pTex,0);
		pTex->Release();

		g_pd3dDevice->Release();
		g_pD3D->Release();

	}

	
	return 0;
}

