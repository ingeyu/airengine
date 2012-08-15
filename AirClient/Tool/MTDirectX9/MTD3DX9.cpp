#include "MTD3DX9.h"
#include "MTD3D9.h"

HRESULT WINAPI D3DXCheckTextureRequirements( MT_LPDIRECT3DDEVICE9 pDevice, UINT* pWidth, UINT* pHeight, UINT* pNumMipLevels, DWORD Usage, D3DFORMAT* pFormat, D3DPOOL Pool )
{
	return	D3DXCheckTextureRequirements(pDevice->m_pIDirect3DDevice9,pWidth,pHeight,pNumMipLevels,Usage,pFormat,Pool);
}

HRESULT WINAPI D3DXCheckCubeTextureRequirements( MT_LPDIRECT3DDEVICE9 pDevice, UINT* pSize, UINT* pNumMipLevels, DWORD Usage, D3DFORMAT* pFormat, D3DPOOL Pool )
{
	return	D3DXCheckCubeTextureRequirements(pDevice->m_pIDirect3DDevice9,pSize,pNumMipLevels,Usage,pFormat,Pool);
}

HRESULT WINAPI D3DXCheckVolumeTextureRequirements( MT_LPDIRECT3DDEVICE9 pDevice, UINT* pWidth, UINT* pHeight, UINT* pDepth, UINT* pNumMipLevels, DWORD Usage, D3DFORMAT* pFormat, D3DPOOL Pool )
{
	return	D3DXCheckVolumeTextureRequirements(pDevice->m_pIDirect3DDevice9,pWidth,pHeight,pDepth,pNumMipLevels,Usage,pFormat,Pool);
}

HRESULT WINAPI D3DXComputeNormalMap( MT_LPDIRECT3DTEXTURE9 pTexture, MT_LPDIRECT3DTEXTURE9 pSrcTexture, CONST PALETTEENTRY* pSrcPalette, DWORD Flags, DWORD Channel, FLOAT Amplitude )
{
	return	D3DXComputeNormalMap(pTexture->m_pIDirect3DTexture9,pSrcTexture->m_pIDirect3DTexture9,pSrcPalette,Flags,Channel,Amplitude);
}
HRESULT WINAPI
    D3DXCreateTexture(
        MT_LPDIRECT3DDEVICE9      pDevice,
        UINT                      Width,
        UINT                      Height,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        MT_LPDIRECT3DTEXTURE9*       ppTexture)
{
	LPDIRECT3DTEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateTexture(pDevice->m_pIDirect3DDevice9,Width,Height,MipLevels,Usage,Format,Pool,&pTex);

	if(SUCCEEDED(hr)){
		(*ppTexture)	=	new	MT_IDirect3DTexture9(pDevice,pTex);
		(*ppTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateCubeTexture(
        MT_LPDIRECT3DDEVICE9		pDevice,
        UINT						Size,
        UINT						MipLevels,
        DWORD						Usage,
        D3DFORMAT					Format,
        D3DPOOL						Pool,
        MT_LPDIRECT3DCUBETEXTURE9*	ppCubeTexture)
{
	LPDIRECT3DCUBETEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateCubeTexture(pDevice->m_pIDirect3DDevice9,Size,MipLevels,Usage,Format,Pool,&pTex);

	if(SUCCEEDED(hr)){
		(*ppCubeTexture)	=	new	MT_IDirect3DCubeTexture9(pDevice,pTex);
		(*ppCubeTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateVolumeTexture(
        MT_LPDIRECT3DDEVICE9			pDevice,
        UINT							Width,
        UINT							Height,
        UINT							Depth,
        UINT							MipLevels,
        DWORD							Usage,
        D3DFORMAT						Format,
        D3DPOOL							Pool,
		MT_LPDIRECT3DVOLUMETEXTURE9*	ppVolumeTexture)
{
	LPDIRECT3DVOLUMETEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateVolumeTexture(pDevice->m_pIDirect3DDevice9,Width,Height,Depth,MipLevels,Usage,Format,Pool,&pTex);

	if(SUCCEEDED(hr)){
		(*ppVolumeTexture)	=	new	MT_IDirect3DVolumeTexture9(pDevice,pTex);
		(*ppVolumeTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
};
HRESULT WINAPI
    D3DXCreateTextureFromFileA(
        MT_LPDIRECT3DDEVICE9		pDevice,
        LPCSTR						pSrcFile,
        MT_LPDIRECT3DTEXTURE9*		ppTexture)
{
	LPDIRECT3DTEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateTextureFromFileA(pDevice->m_pIDirect3DDevice9,pSrcFile,&pTex);
	if(SUCCEEDED(hr)){
		(*ppTexture)	=	new	MT_IDirect3DTexture9(pDevice,pTex);
		(*ppTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateTextureFromFileW(
        MT_LPDIRECT3DDEVICE9		pDevice,
        LPCWSTR						pSrcFile,
		MT_LPDIRECT3DTEXTURE9*		ppTexture)
{
	LPDIRECT3DTEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateTextureFromFileW(pDevice->m_pIDirect3DDevice9,pSrcFile,&pTex);
	if(SUCCEEDED(hr)){
		(*ppTexture)	=	new	MT_IDirect3DTexture9(pDevice,pTex);
		(*ppTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateTextureFromFileInMemory(
        MT_LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        MT_LPDIRECT3DTEXTURE9*       ppTexture)
{
	LPDIRECT3DTEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateTextureFromFileInMemory(pDevice->m_pIDirect3DDevice9,pSrcData,SrcDataSize,&pTex);
	if(SUCCEEDED(hr)){
		(*ppTexture)	=	new	MT_IDirect3DTexture9(pDevice,pTex);
		(*ppTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileInMemory(
        MT_LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        MT_LPDIRECT3DCUBETEXTURE9*   ppCubeTexture)
{
	LPDIRECT3DCUBETEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateCubeTextureFromFileInMemory(pDevice->m_pIDirect3DDevice9,pSrcData,SrcDataSize,&pTex);
	if(SUCCEEDED(hr)){
		(*ppCubeTexture)	=	new	MT_IDirect3DCubeTexture9(pDevice,pTex);
		(*ppCubeTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileInMemory(
        MT_LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        MT_LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture)
{
	LPDIRECT3DVOLUMETEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateVolumeTextureFromFileInMemory(pDevice->m_pIDirect3DDevice9,pSrcData,SrcDataSize,&pTex);
	if(SUCCEEDED(hr)){
		(*ppVolumeTexture)	=	new	MT_IDirect3DVolumeTexture9(pDevice,pTex);
		(*ppVolumeTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}



HRESULT WINAPI
    D3DXCreateTextureFromFileInMemoryEx(
        MT_LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        UINT                      Width,
        UINT                      Height,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        MT_LPDIRECT3DTEXTURE9*       ppTexture)
{
	LPDIRECT3DTEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateTextureFromFileInMemoryEx(
		pDevice->m_pIDirect3DDevice9,
		pSrcData,
		SrcDataSize,
		Width,
		Height,
		MipLevels,
		Usage,
		Format,
		Pool,
		Filter,
		MipFilter,
		ColorKey,
		pSrcInfo,
		pPalette,
		&pTex);

	if(SUCCEEDED(hr)){
		(*ppTexture)	=	new	MT_IDirect3DTexture9(pDevice,pTex);
		(*ppTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileInMemoryEx(
        MT_LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        UINT                      Size,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
		MT_LPDIRECT3DCUBETEXTURE9*   ppCubeTexture)
{
	LPDIRECT3DCUBETEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateCubeTextureFromFileInMemoryEx(
		pDevice->m_pIDirect3DDevice9,
		pSrcData,
		SrcDataSize,
		Size,
		MipLevels,
		Usage,
		Format,
		Pool,
		Filter,
		MipFilter,
		ColorKey,
		pSrcInfo,
		pPalette,
		&pTex);

	if(SUCCEEDED(hr)){
		(*ppCubeTexture)	=	new	MT_IDirect3DCubeTexture9(pDevice,pTex);
		(*ppCubeTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileInMemoryEx(
        MT_LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        UINT                      Width,
        UINT                      Height,
        UINT                      Depth,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        MT_LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture)
{
	LPDIRECT3DVOLUMETEXTURE9	pTex	=	NULL;
	HRESULT	hr	=	D3DXCreateVolumeTextureFromFileInMemoryEx(
		pDevice->m_pIDirect3DDevice9,
		pSrcData,
		SrcDataSize,
		Width,
		Height,
		Depth,
		MipLevels,
		Usage,
		Format,
		Pool,
		Filter,
		MipFilter,
		ColorKey,
		pSrcInfo,
		pPalette,
		&pTex);

	if(SUCCEEDED(hr)){
		(*ppVolumeTexture)	=	new	MT_IDirect3DVolumeTexture9(pDevice,pTex);
		(*ppVolumeTexture)->AddRef();
		pTex->Release();
	}
	return	hr;
}


HRESULT WINAPI
    D3DXLoadSurfaceFromMemory(
        MT_LPDIRECT3DSURFACE9     pDestSurface,
        CONST PALETTEENTRY*       pDestPalette,
        CONST RECT*               pDestRect,
        LPCVOID                   pSrcMemory,
        D3DFORMAT                 SrcFormat,
        UINT                      SrcPitch,
        CONST PALETTEENTRY*       pSrcPalette,
        CONST RECT*               pSrcRect,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey)
{
	return	D3DXLoadSurfaceFromMemory(
										pDestSurface->m_pIDirect3DSurface9,
										pDestPalette,
										pDestRect,
										pSrcMemory,
										SrcFormat,
										SrcPitch,
										pSrcPalette,
										pSrcRect,
										Filter,
										ColorKey);
}

HRESULT WINAPI
    D3DXLoadSurfaceFromSurface(
        MT_LPDIRECT3DSURFACE9     pDestSurface,
        CONST PALETTEENTRY*       pDestPalette,
        CONST RECT*               pDestRect,
        MT_LPDIRECT3DSURFACE9     pSrcSurface,
        CONST PALETTEENTRY*       pSrcPalette,
        CONST RECT*               pSrcRect,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey)
{
	return	D3DXLoadSurfaceFromSurface(
										pDestSurface->m_pIDirect3DSurface9,
										pDestPalette,
										pDestRect,
										pSrcSurface->m_pIDirect3DSurface9,
										pSrcPalette,
										pSrcRect,
										Filter,
										ColorKey);

}

HRESULT WINAPI
    D3DXSaveSurfaceToFileA(
        LPCSTR                    pDestFile,
        D3DXIMAGE_FILEFORMAT      DestFormat,
        MT_LPDIRECT3DSURFACE9     pSrcSurface,
        CONST PALETTEENTRY*       pSrcPalette,
		CONST RECT*               pSrcRect)
{
	return	D3DXSaveSurfaceToFileA(
									pDestFile,
									DestFormat,
									pSrcSurface->m_pIDirect3DSurface9,
									pSrcPalette,
									pSrcRect);

}

HRESULT WINAPI
    D3DXSaveSurfaceToFileW(
        LPCWSTR                   pDestFile,
        D3DXIMAGE_FILEFORMAT      DestFormat,
        MT_LPDIRECT3DSURFACE9        pSrcSurface,
        CONST PALETTEENTRY*       pSrcPalette,
        CONST RECT*               pSrcRect)
{
	return	D3DXSaveSurfaceToFileW(
									pDestFile,
									DestFormat,
									pSrcSurface->m_pIDirect3DSurface9,
									pSrcPalette,
									pSrcRect);
}

HRESULT WINAPI
    D3DXSaveTextureToFileA(
        LPCSTR						pDestFile,
        D3DXIMAGE_FILEFORMAT		DestFormat,
        MT_LPDIRECT3DBASETEXTURE9    pSrcTexture,
        CONST PALETTEENTRY*			pSrcPalette)
{
	return	D3DXSaveTextureToFileA(
									pDestFile,
									DestFormat,
									pSrcTexture->m_pIDirect3DBaseTexture9,
									pSrcPalette);

}

HRESULT WINAPI
    D3DXSaveTextureToFileW(
        LPCWSTR                   pDestFile,
        D3DXIMAGE_FILEFORMAT      DestFormat,
        MT_LPDIRECT3DBASETEXTURE9    pSrcTexture,
        CONST PALETTEENTRY*       pSrcPalette)
{
	return	D3DXSaveTextureToFileW(
									pDestFile,
									DestFormat,
									pSrcTexture->m_pIDirect3DBaseTexture9,
									pSrcPalette);
}