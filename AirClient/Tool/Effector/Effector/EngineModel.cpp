#include "stdafx.h"
#include "EngineModel.h"
#include "EngineMesh.h"

Model::Model( const TCHAR* strName,TreeObj* pParent ):TreeObj(strName,pParent,pParent->GetTree(),enTOT_Model)
{
	m_bEnableEdit	=	true;
	m_bEnableBind	=	true;

	Position		=	Air::Float3(0,0,0);
	Rotation		=	Air::Float4(0,0,0,1);
	Scale			=	Air::Float3(1,1,1);

	m_pObjBuffer	=	NULL;
}

void Model::OnPropertyChanged( CMFCPropertyGridProperty* pProperty )
{
	__super::OnPropertyChanged(pProperty);
}

void Model::OnShowProperty( CMFCPropertyGridProperty* pGroup )
{
	__super::OnShowProperty(pGroup);

	AddMember(pGroup,_T("Position"),Position,TRUE);
	AddMember(pGroup,_T("Rotation"),Rotation,TRUE);
	AddMember(pGroup,_T("Scale"),Scale,TRUE);
}

void Model::Draw()
{

	Air::Client::Matrix	mWorld(Position,Scale,Rotation);
	m_pObjBuffer->UpdateData(&mWorld);

	Air::Client::Render::System*	pSys	=	Air::Client::Render::System::GetSingleton();
	Air::Client::Render::Device*	pDevice	=	pSys->GetDevice();

	pDevice->SetCB(Air::Client::enVS,2,m_pObjBuffer);
	pDevice->SetCB(Air::Client::enGS,2,m_pObjBuffer);
	pDevice->SetCB(Air::Client::enHS,2,m_pObjBuffer);
	pDevice->SetCB(Air::Client::enDS,2,m_pObjBuffer);

	Mesh*	pMesh	=	(Mesh*)m_pBindObj;
	if(pMesh){
		pMesh->Draw(mWorld);
	}
}

bool Model::Create()
{
	Air::Client::Buffer::Info info;
	info.SetConstantBuffer(sizeof(Air::Client::Matrix));
	m_pObjBuffer	=	Air::Client::Render::System::GetSingleton()->CreateProduct<Air::Client::Buffer*>(Air::Common::Number::Increase(""),"Buffer",&info);
	return	__super::Create();
}

bool Model::Destroy()
{
	if(m_pObjBuffer!=NULL){
		m_pObjBuffer->ReleaseRef();
		m_pObjBuffer=NULL;
	}
	return	__super::Destroy();
}



ModelRef::ModelRef( const TCHAR* strName,TreeObj* pParent ):TreeObj(strName,pParent,pParent->GetTree(),enTOT_ModelRef)
{
	m_bEnableEdit	=	true;
	m_bEnableBind	=	true;
}
