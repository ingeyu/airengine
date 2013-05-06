// Sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "D3D11.H"
#include "xnamath.h"
#include "d3dx9.h"
#include "D3DX11.h"
#pragma comment(lib,"d3dx9")
#pragma comment(lib,"d3d11")
#pragma comment(lib,"d3dx11")
typedef unsigned int uint;
struct float3{
	float3(float fx,float fy,float fz){
		x=	fx;
		y=fy;
		z=fz;
	};

	float x,y,z;
};
float dot(const D3DXVECTOR3& v0,const D3DXVECTOR3& v1){
	return v0.x*v1.x+v0.y*v1.y+v0.z*v1.z;
};
uint   CalcOrder(D3DXVECTOR3 vDir){
	float aData[8];
	uint  anIndex[8]={0,1,2,3,4,5,6,7};
	uint  uiOrder=0;
	for(uint i=0;i<8;i++){
		aData[i]=dot(D3DXVECTOR3(i>>2,1&(i>>1),1&i),vDir);   
	}
	uint N2=8;
	// Bitonic sort
	for( uint k = 2; k <= N2; k = 2*k )
	{
		for( uint j = k>>1; j > 0 ; j = j>>1 ) 
		{
			for( uint i = 0; i < N2; i++ ) 
			{
				float di = aData[ anIndex[ i ] ];
				uint ixj = i^j;
				if ( ( ixj ) > i )
				{
					float dixj = aData[ anIndex[ ixj ] ];
					if ( ( i&k ) == 0 && di > dixj )
					{ 
						int temp = anIndex[ i ];
						anIndex[ i ] = anIndex[ ixj ];
						anIndex[ ixj ] = temp;
					}
					if ( ( i&k ) != 0 && di < dixj )
					{
						int temp = anIndex[ i ];
						anIndex[ i ] = anIndex[ ixj ];
						anIndex[ ixj ] = temp;
					}
				}
			}
		}
	}
	for(uint n=0;n<8;n++){
		uiOrder|=(anIndex[n])<<3*n;   
	}
	return uiOrder;
}
D3DXMATRIX WINAPI DXUTGetCubeMapViewMatrix( DWORD dwFace )
{
	D3DXVECTOR3 vEyePt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vLookDir;
	D3DXVECTOR3 vUpDir;

	switch( dwFace )
	{
	case D3DCUBEMAP_FACE_POSITIVE_X:
		vLookDir = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
		vUpDir = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_X:
		vLookDir = D3DXVECTOR3( -1.0f, 0.0f, 0.0f );
		vUpDir = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		break;
	case D3DCUBEMAP_FACE_POSITIVE_Y:
		vLookDir = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		vUpDir = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_Y:
		vLookDir = D3DXVECTOR3( 0.0f, -1.0f, 0.0f );
		vUpDir = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
		break;
	case D3DCUBEMAP_FACE_POSITIVE_Z:
		vLookDir = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
		vUpDir = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_Z:
		vLookDir = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		vUpDir = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		break;
	}

	// Set the view transform for this cubemap surface
	D3DXMATRIXA16 mView;
	D3DXMatrixLookAtLH( &mView, &vEyePt, &vLookDir, &vUpDir );
	return mView;
}
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}
HWND g_hWnd=NULL;
HRESULT InitWindow( HINSTANCE hInstance )
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;//LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	wcex.hCursor =0;// LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm =0;// LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	if( !RegisterClassEx( &wcex ) )
		return E_FAIL;

	// Create window
	//g_hInst = hInstance;
	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	g_hWnd = CreateWindow( L"TutorialWindowClass", L"Direct3D 11 Tutorial 2: Rendering a Triangle",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );
	if( !g_hWnd )
		return E_FAIL;

	ShowWindow( g_hWnd, true );

	return S_OK;
}
D3D_FEATURE_LEVEL	g_featureLevel;
ID3D11Device*		g_pd3dDevice=0;
ID3D11DeviceContext* g_pImmediateContext;
HRESULT	InitDevice(){
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect( g_hWnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	//for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		//g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice( 
			NULL, 
			D3D_DRIVER_TYPE_HARDWARE, 
			NULL,
			createDeviceFlags,
			featureLevels, 
			numFeatureLevels,
			D3D11_SDK_VERSION, 
			&g_pd3dDevice,
			&g_featureLevel, 
			&g_pImmediateContext );

	}
	return true;
}
int _tmain(int argc, _TCHAR* argv[])
{
	//XMMatrixLookToLH()

	if( FAILED( InitWindow( (HINSTANCE)GetModuleHandleA(NULL) ) ) )
		return 0;

	if( FAILED( InitDevice() ) )
	{
		//CleanupDevice();
		return 0;
	}

	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH( &mProj, D3DX_PI * 0.5f, 1.0f, 0.01f, 100.0f );


	 D3D11_SUBRESOURCE_DATA* pInitData	=	new D3D11_SUBRESOURCE_DATA[6];


	for(uint uiFace=0;uiFace<6;uiFace++){
		pInitData[uiFace].pSysMem		=	new uint[512*512];
		pInitData[uiFace].SysMemPitch	=	2048;
		pInitData[uiFace].SysMemSlicePitch	=	0;
		D3DXMATRIX mView	=	DXUTGetCubeMapViewMatrix(uiFace);
		D3DXMATRIX mViewProj;
		D3DXMATRIX mViewProjInv;
		D3DXMatrixMultiply(&mViewProj,&mView,&mProj);
		D3DXMatrixInverse(&mViewProjInv,NULL,&mViewProj);



		uint* data = (uint*)pInitData[uiFace].pSysMem;
		
		for(uint i=0;i<512;i++){
			for(uint j=0;j<512;j++){
				uint index = j*512+i;

				D3DXVECTOR3	vPos((i+0.5f)/512.0f,(j+0.5f)/512.0f,1);
				vPos.x	=	vPos.x*2-1;
				vPos.y	=	1-vPos.y*2;
				D3DXVECTOR3 vWorldPos;
				D3DXVec3TransformCoord(&vWorldPos,&vPos,&mViewProjInv);
				D3DXVECTOR3 vNormal;
				D3DXVec3Normalize(&vNormal,&vWorldPos);

				data[index]	=	CalcOrder(vNormal);
			}
		}

	}
	ID3D11Texture2D* pTex=0;
	D3D11_TEXTURE2D_DESC dstex;
	dstex.Width = 512;
	dstex.Height = 512;
	dstex.MipLevels = 1;
	dstex.ArraySize = 6;
	dstex.SampleDesc.Count = 1;
	dstex.SampleDesc.Quality = 0;
	dstex.Format = DXGI_FORMAT_R32_UINT;
	dstex.Usage = D3D11_USAGE_STAGING;
	dstex.BindFlags = 0;//D3D11_BIND_DEPTH_STENCIL;
	dstex.CPUAccessFlags = D3D11_CPU_ACCESS_READ|D3D11_CPU_ACCESS_WRITE;
	dstex.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	g_pd3dDevice->CreateTexture2D(&dstex,pInitData,&pTex);
	D3DX11SaveTextureToFile(g_pImmediateContext,pTex,D3DX11_IFF_DDS,L"DIR2ORDER.dds");
	ID3D11ShaderResourceView* pSRV=NULL;
	D3DX11CreateShaderResourceViewFromFile(g_pd3dDevice,L"DIR2ORDER.dds",NULL,NULL,&pSRV,0);
	return 0;
}

