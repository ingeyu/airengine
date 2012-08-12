#include "stdafx.h"
#include "EngineMesh.h"
#include "AirStaticMesh.h"

Mesh::Mesh( const TCHAR* strName,TreeObj* pParent ):TreeObj(strName,pParent,pParent->GetTree(),enTOT_Mesh)
{
	m_bEnableEdit	=	true;
	m_bIsResource	=	true;
	m_pMeshFile		=	NULL;
}
bool Mesh::Create()
{
	if(!m_strResourceName.empty()){
		Air::AString	strName	=	Air::Common::Converter::WideByte2Acsi(m_strResourceName);
		m_pMeshFile	=	new Air::Client::StaticMesh(strName);
		if(!m_pMeshFile->Create()){
			m_pMeshFile->Destroy();
			delete m_pMeshFile;
			m_pMeshFile	=	NULL;
		}
		//m_pMeshFile->SetNeedWorldMatrix(false);
	}
	return	true;
}

bool Mesh::Destroy()
{
	if(m_pMeshFile!=NULL){
		m_pMeshFile->Destroy();
		delete m_pMeshFile;
		m_pMeshFile	=	NULL;
	}
	return	true;
}

void Mesh::OnPropertyChanged( CMFCPropertyGridProperty* pProperty )
{
	if(wcscmp(pProperty->GetName(),_T("ResourceName"))	==	0){
		m_strResourceName	=	pProperty->GetValue().bstrVal;
	}
}

void Mesh::OnShowProperty( CMFCPropertyGridProperty* pGroup )
{
	__super::OnShowProperty(pGroup);
	if(m_pMeshFile!=NULL){
		//m_pMeshFile->
		AddMember(pGroup,_T("VertexCount"),m_pMeshFile->GetVertexCount(),_T("Total Vertex Count!"),FALSE);
		AddMember(pGroup,_T("FaceCount"),m_pMeshFile->GetFaceCount(),_T("Total Vertex Count!"),FALSE);
		//AddMember(pGroup,_T("BoundingBox"),m_pMeshFile->GetOrginBoundingBox(),FALSE);
		
	}
}

bool Mesh::ReLoad()
{
	Destroy();
	return	Create();
}

void Mesh::Draw(const Air::Client::Matrix& matWorld)
{
	if(m_pMeshFile!=NULL){

		Air::Client::Render::System*	pSys	=	Air::Client::Render::System::GetSingleton();
		Air::Client::Render::Device*	pDevice	=	pSys->GetDevice();

		//pDevice->DrawObject(m_pMeshFile);
	}
}
