#include "AirInterfaceShootParticle.h"
#include "AirGlobalSetting.h"
namespace Air{
	
	namespace	Engine{
	
	
		ShootParticle::ShootParticle( CAString& strName,Info* pInfo ):IParticle(strName,pInfo){
	
		}
	
		void ShootParticle::SetParticleParam(){
			//Render::IMaterial::Technique*	pTech	=	m_pMaterial->GetTechnique();
			//pTech->SetParam("fLife",		m_fLife);
			//pTech->SetParam("fCreateTime",	m_fCreateTime);
// 			pTech->SetParam("vSrcPosition",	m_Info.vPosition);
// 			pTech->SetParam("vDstPosition",	m_Info.vVelocity);
		}
	
		void ShootParticle::Updata(){
			if(m_bDeath)
				return;
	
			if(m_fTotalTime>m_fLife+m_fCreateTime){
				//SetVisiable(false);
				m_bDeath	=	true;
			}
		}
	
		void ShootParticle::SetPosition( Float3 vSrcPos,Float3 vDstPos ){
			m_fCreateTime	=	GetGlobalSetting().m_ShaderParam.m_fTotalTime;
			m_fLife		=	2;
			m_bDeath	=	false;
			m_Info.vPosition	=	vSrcPos;
			m_Info.vVelocity	=	vDstPos;
			//SetVisiable(true);
		}
		ShootParticleFactory::ShootParticleFactory(){
			m_strTypeName	=	"ShootParticle";
		}
	
		IProduct* ShootParticleFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /* = NULL */ ){
			if(lstParam==NULL)
				return NULL;
			IParticle::Info*	pInfo	=	(IParticle::Info*)lstParam;
			IParticle*		pBuff	=	new	ShootParticle(strName,pInfo);
			return	pBuff;
		}
	}
};