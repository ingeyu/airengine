#include "stdafx.h"
#include "EngineCamera.h"


ECamera::ECamera( const TCHAR* strName,TreeObj* pParent ):TreeObj(strName,pParent,pParent->GetTree(),enTOT_Camera)
{
	m_pCamera	=	new Air::Client::Camera("Camera");
	m_bEnableEdit	=	true;
	m_bEnableActive	=	true;
}

bool ECamera::Create()
{

	return	true;
}

bool ECamera::Destroy()
{

	return	true;
}

ECamera::~ECamera()
{
	delete m_pCamera;
}
