#include "stdafx.h"
#include "EngineRenderTexture.h"

RenderTexture::RenderTexture( const TCHAR* strName,TreeObj* pParent ):ETexture(strName,pParent)
{
	m_Type			=	enTOT_RenderTexture;
	m_bEnableEdit	=	true;
}

bool RenderTexture::Create()
{

	return	true;
}

bool RenderTexture::Destroy()
{
	return	true;
}
