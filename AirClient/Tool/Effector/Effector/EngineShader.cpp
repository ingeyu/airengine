#include "stdafx.h"
#include "EngineShader.h"
#include "AirRenderShader.h"

EShader::EShader( const TCHAR* strName,TreeObj* pParent,enumTreeObjType t ):TreeObj(strName,pParent,pParent->GetTree(),t)
{
	m_pShader		=	NULL;
	m_bIsResource	=	true;
	m_bEnableEdit	=	false;
}

bool EShader::Create()
{
	if(!m_strResourceName.empty()){
		Air::AString	strName	=	Air::Common::Converter::WideByte2Acsi(m_strResourceName);
		m_pShader	=	Air::Client::Render::System::GetSingleton()->CreateProduct<Air::Client::Shader*>(strName,"Shader");
	}
	return	true;
}

bool EShader::Destroy()
{
	if(m_pShader!=NULL){
		m_pShader->ReleaseRef();
		m_pShader=NULL;
	}
	return	true;
}

void EShader::OnPropertyChanged( CMFCPropertyGridProperty* pProperty )
{
	__super::OnPropertyChanged(pProperty);
	if(wcscmp(pProperty->GetName(),_T("ResourceName"))	==	0){
		m_strResourceName	=	pProperty->GetValue().bstrVal;
	}
}

void EShader::OnShowProperty( CMFCPropertyGridProperty* pGroup )
{
	__super::OnShowProperty(pGroup);
}

bool EShader::ReLoad()
{
	Destroy();
	return	Create();
}
