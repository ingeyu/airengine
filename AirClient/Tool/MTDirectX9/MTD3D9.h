#ifndef MTD3D9_HEAD_FILE
#define	MTD3D9_HEAD_FILE

#include "MTResource9.h"
#include "MTVolume9.h"
#include "MTIndexBuffer9.h"
#include "MTVertexBuffer9.h"
#include "MTBaseTexture9.h"
#include "MTTexture9.h"
#include "MTCubeTexture9.h"
#include "MTVolumeTexture9.h"
#include "MTVertexDeclaration9.h"
#include "MTSwapChain9.h"
#include "MTQuery9.h"
#include "MTVertexShader9.h"
#include "MTPixelShader9.h"
#include "MTStateBlock9.h"
#include "MTDevice9.h"

MT_IDirect3D9*		MT_Direct3DCreate9(UINT	SDKVersion);
MT_IDirect3D9Ex*	MT_Direct3DCreate9Ex(UINT	SDKVersion);


#endif