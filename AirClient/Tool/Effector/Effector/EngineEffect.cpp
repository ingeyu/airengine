#include "stdafx.h"
#include "EngineEffect.h"
#include "EffectorFile.h"

Effect::Effect( const TCHAR* strName ,TreeObj*	pFile):TreeObj(strName,pFile,pFile->GetTree(),enTOT_Effect)
{
	m_bEnableEdit	=	true;
	//m_bEnableActive	=	true;
}

Effect::~Effect()
{
	Destroy();
}

bool Effect::Create()
{

	return	true;
}

bool Effect::Destroy()
{
	
	return	__super::Destroy();
}

bool Effect::AddPhase( const TCHAR* strName )
{
	if(strName==NULL)
		return	false;
	Phase*	p	=	new Phase(strName,this);
	p->Create();
	AddChild(p);
	return	true;
}

void Effect::Draw()
{
	std::vector<TreeObj*>	vecObj	=	GetChildByType(enTOT_Phase);
	unsigned long			uiSize	=	vecObj.size();
	for(unsigned long i=0;i<uiSize;i++){
		TreeObj*	p	=	vecObj[i];
		if(p!=NULL){
			Phase*	pPhase	=	(Phase*)p;
			pPhase->Draw();
		}
	}


}


