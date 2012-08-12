#include "stdafx.h"
#include "EngineTexture.h"


ETexture::ETexture( const TCHAR* strName,TreeObj* pObj ):TreeObj(strName,pObj,pObj->GetTree(),enTOT_Texture)
{
	m_bEnableEdit	=	true;
	//m_bEnableBind	=	true;
	m_bIsResource	=	true;
	m_pTexture		=	NULL;
}

bool ETexture::Create()
{
	if(m_pTexture==NULL	&&	!m_strResourceName.empty()){
		Air::AString	strName	=	Air::Common::Converter::WideByte2Acsi(m_strResourceName);
		m_pTexture	=	Air::Client::Render::System::GetSingleton()->CreateProduct<AirTexture*>(strName,"Texture");
	}
	return	true;
}

bool ETexture::Destroy()
{
	if(m_pTexture!=NULL){
		m_pTexture->ReleaseRef();
		m_pTexture=NULL;
	}
	return	true;
}

bool ETexture::ReLoad()
{
	Destroy();

	return	Create();
}

void ETexture::OnShowProperty( CMFCPropertyGridProperty* pGroup )
{
	__super::OnShowProperty(pGroup);

	if(pGroup!=NULL){
		if(m_pTexture!=NULL){
			AddMember(pGroup,_T("TextureType"),GetNameString(m_pTexture->GetType()).c_str(),_T("Texture Type !"),FALSE);
			AddMember(pGroup,_T("TextureFormat"),GetNameString(m_pTexture->GetFormat()).c_str(),_T("Texture Format Like DirectX 11. See DXGI_FORMAT!"),FALSE);
			AddMember(pGroup,_T("Width"),m_pTexture->GetWidth(),_T("Texture Width "),FALSE);
			AddMember(pGroup,_T("Height"),m_pTexture->GetHeight(),_T("Texture Height "),FALSE);
			AddMember(pGroup,_T("Depth"),m_pTexture->GetDepth(),_T("Texture Depth "),FALSE);
			AddMember(pGroup,_T("MipMap"),m_pTexture->GetMipmapCount(),_T("Texture MipMap Level Count!"),FALSE);
		}
	}
}

void ETexture::OnPropertyChanged( CMFCPropertyGridProperty* pProperty )
{
	if(wcscmp(pProperty->GetName(),_T("ResourceName"))==0){
		m_strResourceName	=	pProperty->GetValue().bstrVal;
	}
}


ETextureRef::ETextureRef( const TCHAR* strName,TreeObj* pObj ):TreeObj(strName,pObj,pObj->GetTree(),enTOT_TextureRef)
{
	m_bEnableEdit	=	true;
	m_bEnableBind	=	true;
}
