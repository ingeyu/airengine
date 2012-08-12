#include "stdafx.h"
#include "EnginePhase.h"
#include "EnginePass.h"

Phase::Phase( const TCHAR* strName,TreeObj* pParent ):TreeObj(strName,pParent,pParent->GetTree(),enTOT_Phase)
{
	m_bEnableEdit	=	true;
	m_bEnableBind	=	true;
}

bool Phase::Create()
{

	return	true;
}

bool Phase::Destroy()
{

	return	__super::Destroy();
}

void Phase::Draw()
{
	if(m_pBindObj==NULL)
		return;
	if(m_pBindObj->GetType()==enTOT_RenderTarget){
		//m_pBindObj
	}
	std::vector<TreeObj*>	vecObj	=	GetChildByType(enTOT_Pass);
	unsigned long			uiSize	=	vecObj.size();
	for(unsigned long i=0;i<uiSize;i++){
		TreeObj*	p	=	vecObj[i];
		if(p!=NULL){
			EPass*	pPhase	=	(EPass*)p;
			pPhase->Draw();
		}
	}
}
