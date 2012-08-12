#include "stdafx.h"
#include "EnginePass.h"
#include "EngineRenderState.h"
#include "EngineShader.h"
#include "EngineMesh.h"
#include "EngineModel.h"
#include "EngineTexture.h"


EPass::EPass( const TCHAR* strName,TreeObj* pParent ):TreeObj(strName,pParent,pParent->GetTree(),enTOT_Pass)
{
	m_bEnableEdit	=	true;
	//m_bEnableBind	=	true;
}

bool EPass::Create()
{

	return	__super::Create();
}

bool EPass::Destroy()
{

	return	__super::Destroy();
}

void EPass::Draw()
{
	Air::Client::Render::System*	pSys	=	Air::Client::Render::System::GetSingleton();
	Air::Client::Render::Device*	pDevice	=	pSys->GetDevice();

	RenderState*	pRS	=	(RenderState*)GetChild(enTOT_RState);
	if(pRS!=NULL){
		pDevice->SetRS(pRS->m_pState);
	}else{
		pDevice->SetRS(NULL);
	}
	RenderState*	pDS	=	(RenderState*)GetChild(enTOT_DState);
	if(pDS!=NULL){
		pDevice->SetDSS(pDS->m_pState);
	}else{
		pDevice->SetDSS(NULL);
	}
	RenderState*	pBS	=	(RenderState*)GetChild(enTOT_BState);
	if(pBS!=NULL){
		pDevice->SetBS(pBS->m_pState);
	}else{
		pDevice->SetBS(NULL);
	}
	EShader*	pVShader		=	(EShader*)GetChild(enTOT_VShader);
	EShader*	pGShader		=	(EShader*)GetChild(enTOT_GShader);
	EShader*	pPShader		=	(EShader*)GetChild(enTOT_PShader);
	EShader*	pCShader		=	(EShader*)GetChild(enTOT_CShader);
	EShader*	pHShader		=	(EShader*)GetChild(enTOT_HShader);
	EShader*	pDShader		=	(EShader*)GetChild(enTOT_DShader);
	if(pCShader!=NULL){
		pDevice->SetShader(Air::Client::enCS,pCShader->m_pShader);
		if(pCShader->m_pShader==NULL)
			return;
	}else{
		std::vector<TreeObj*>	vecTextureRef	=	GetChildByType(enTOT_TextureRef);
		std::vector<void*>		vecSRV;
		unsigned long uiSrvCount	=	vecTextureRef.size();
		if(uiSrvCount!=NULL){
			vecSRV.resize(uiSrvCount);
			for(unsigned long i=0;i<uiSrvCount;i++){
				if(vecTextureRef[i]!=NULL){
					ETextureRef*	pTRef	=	(ETextureRef*)vecTextureRef[i];
					ETexture*		pT		=	(ETexture*)pTRef->GetBindObj();
					if(pT==NULL)
						vecSRV[i]	=	NULL;
					else
						vecSRV[i]	=	pT->m_pTexture->GetSRV();
				}
			}
		}

		if(pCShader!=NULL){
			pDevice->SetShader(Air::Client::enVS,pVShader->m_pShader);
			for(unsigned long i=0;i<uiSrvCount;i++){
				pDevice->SetSRV(Air::Client::enVS,i,vecSRV[i]);
			}
		}else
			pDevice->SetShader(Air::Client::enVS,NULL);
		if(pGShader!=NULL){
			pDevice->SetShader(Air::Client::enGS,pGShader->m_pShader);
			for(unsigned long i=0;i<uiSrvCount;i++){
				pDevice->SetSRV(Air::Client::enGS,i,vecSRV[i]);
			}
		}else
			pDevice->SetShader(Air::Client::enGS,NULL);
		if(pPShader!=NULL){
			pDevice->SetShader(Air::Client::enPS,pPShader->m_pShader);
			for(unsigned long i=0;i<uiSrvCount;i++){
				pDevice->SetSRV(Air::Client::enPS,i,vecSRV[i]);
			}
		}else
			pDevice->SetShader(Air::Client::enPS,NULL);
		if(pHShader!=NULL){
			pDevice->SetShader(Air::Client::enHS,pHShader->m_pShader);
			for(unsigned long i=0;i<uiSrvCount;i++){
				pDevice->SetSRV(Air::Client::enHS,i,vecSRV[i]);
			}
		}else
			pDevice->SetShader(Air::Client::enHS,NULL);
		if(pDShader!=NULL){
			pDevice->SetShader(Air::Client::enDS,pDShader->m_pShader);
			for(unsigned long i=0;i<uiSrvCount;i++){
				pDevice->SetSRV(Air::Client::enDS,i,vecSRV[i]);
			}
		}else
			pDevice->SetShader(Air::Client::enDS,NULL);


		std::vector<TreeObj*>	vecModel	=	GetChildByType(enTOT_ModelRef);
		unsigned long	uiModelCount	=	vecModel.size();
		for(unsigned long i=0;i<uiModelCount;i++){
			ModelRef*	pMRef	=	(ModelRef*)vecModel[i];
			if(pMRef!=NULL){
				//pModel->get
				Model*	pModel	=	(Model*)pMRef->GetBindObj();
				if(pModel!=NULL){
					pModel->Draw();

				}
			}
		}
	}

}
