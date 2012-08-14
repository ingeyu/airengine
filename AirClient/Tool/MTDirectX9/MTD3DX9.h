#ifndef	D3DX9_HEAD_FILE 
#define	D3DX9_HEAD_FILE

#include "MTHeader.h"


HRESULT WINAPI
    D3DXCheckTextureRequirements(
        MT_LPDIRECT3DDEVICE9      pDevice,
        UINT*                     pWidth,
        UINT*                     pHeight,
        UINT*                     pNumMipLevels,
        DWORD                     Usage,
        D3DFORMAT*                pFormat,
        D3DPOOL                   Pool);

HRESULT WINAPI
    D3DXCheckCubeTextureRequirements(
        MT_LPDIRECT3DDEVICE9      pDevice,
        UINT*                     pSize,
        UINT*                     pNumMipLevels,
        DWORD                     Usage,
        D3DFORMAT*                pFormat,
        D3DPOOL                   Pool);

HRESULT WINAPI
    D3DXCheckVolumeTextureRequirements(
        MT_LPDIRECT3DDEVICE9      pDevice,
        UINT*                     pWidth,
        UINT*                     pHeight,
        UINT*                     pDepth,
        UINT*                     pNumMipLevels,
        DWORD                     Usage,
        D3DFORMAT*                pFormat,
        D3DPOOL                   Pool);

HRESULT WINAPI	D3DXComputeNormalMap ();
HRESULT WINAPI	D3DXCreateCubeTexture ();
HRESULT WINAPI	D3DXCreateCubeTextureFromFile ();
HRESULT WINAPI	D3DXCreateCubeTextureFromFileEx ();
HRESULT WINAPI	D3DXCreateCubeTextureFromFileInMemory ();
HRESULT WINAPI	D3DXCreateCubeTextureFromFileInMemoryEx ();
HRESULT WINAPI	D3DXCreateCubeTextureFromResource ();
HRESULT WINAPI	D3DXCreateCubeTextureFromResourceEx ();
HRESULT WINAPI	D3DXCreateTexture ();
HRESULT WINAPI	D3DXCreateTextureFromFile ();
HRESULT WINAPI	D3DXCreateTextureFromFileEx ();
HRESULT WINAPI	D3DXCreateTextureFromFileInMemory ();
HRESULT WINAPI	D3DXCreateTextureFromFileInMemoryEx ();
HRESULT WINAPI	D3DXCreateTextureFromResource ();
HRESULT WINAPI	D3DXCreateTextureFromResourceEx ();
HRESULT WINAPI	D3DXCreateVolumeTexture ();
HRESULT WINAPI	D3DXCreateVolumeTextureFromFile ();
HRESULT WINAPI	D3DXCreateVolumeTextureFromFileEx ();
HRESULT WINAPI	D3DXCreateVolumeTextureFromFileInMemory ();
HRESULT WINAPI	D3DXCreateVolumeTextureFromFileInMemoryEx ();
HRESULT WINAPI	D3DXCreateVolumeTextureFromResource ();
HRESULT WINAPI	D3DXCreateVolumeTextureFromResourceEx ();
HRESULT WINAPI	D3DXFillCubeTexture ();
HRESULT WINAPI	D3DXFillCubeTextureTX ();
HRESULT WINAPI	D3DXFillTexture ();
HRESULT WINAPI	D3DXFillTextureTX ();
HRESULT WINAPI	D3DXFillVolumeTexture ();
HRESULT WINAPI	D3DXFillVolumeTextureTX ();
HRESULT WINAPI	D3DXFilterTexture ();
HRESULT WINAPI	D3DXGetImageInfoFromFile ();
HRESULT WINAPI	D3DXGetImageInfoFromFileInMemory ();
HRESULT WINAPI	D3DXGetImageInfoFromResource ();
HRESULT WINAPI	D3DXLoadSurfaceFromFileA (
	    MT_LPDIRECT3DSURFACE9     pDestSurface,
        CONST PALETTEENTRY*       pDestPalette,
        CONST RECT*               pDestRect,
        LPCSTR                    pSrcFile,
        CONST RECT*               pSrcRect,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo
	);
HRESULT WINAPI	D3DXLoadSurfaceFromFileW (
        MT_LPDIRECT3DSURFACE9     pDestSurface,
        CONST PALETTEENTRY*       pDestPalette,
        CONST RECT*               pDestRect,
        LPCWSTR                   pSrcFile,
        CONST RECT*               pSrcRect,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo
	);
HRESULT WINAPI	D3DXLoadSurfaceFromFileInMemory ();
HRESULT WINAPI	D3DXLoadSurfaceFromMemory ();
HRESULT WINAPI	D3DXLoadSurfaceFromResource ();
HRESULT WINAPI	D3DXLoadSurfaceFromSurface ();
HRESULT WINAPI	D3DXLoadVolumeFromFile ();
HRESULT WINAPI	D3DXLoadVolumeFromFileInMemory ();
HRESULT WINAPI	D3DXLoadVolumeFromMemory ();
HRESULT WINAPI	D3DXLoadVolumeFromResource ();
HRESULT WINAPI	D3DXLoadVolumeFromVolume ();
HRESULT WINAPI	D3DXSaveSurfaceToFile ();
HRESULT WINAPI	D3DXSaveSurfaceToFileInMemory ();
HRESULT WINAPI	D3DXSaveTextureToFile ();
HRESULT WINAPI	D3DXSaveTextureToFileInMemory ();
HRESULT WINAPI	D3DXSaveVolumeToFile ();
HRESULT WINAPI	D3DXSaveVolumeToFileInMemory ();


#endif