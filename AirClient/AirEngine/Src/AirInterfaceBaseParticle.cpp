#include "AirInterfaceBaseParticle.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceParticleSystem.h"
#include "AirEngineSceneNode.h"
namespace Air{
	
	namespace	Client{
		namespace	Particle{
	
	#ifndef SET_PARTICLE_PROPERTY
	#define SET_PARTICLE_PROPERTY(name,p)	
			/*
			\
		if(m_pMaterial!=NULL){\
			Render::IMaterial::Technique*	pTech	=	m_pMaterial->GetCurrentTechnique();\
			if(pTech!=NULL){\
				pTech->SetParam(strName,p);\
			}\
		}
		*/
	#endif
	
	
			void IBaseObject::SetProperty( AString strName,SInt& iParam ){
				SET_PARTICLE_PROPERTY(strName,iParam);
	
			}
	
			void IBaseObject::SetProperty( AString strName,Real& fParam ){
				SET_PARTICLE_PROPERTY(strName,fParam);
			}
	
// 			void IBaseObject::SetProperty( AString strName,Vector2& vParam ){
// // 				Float3 v(vParam.m128_f32[0],vParam.m128_f32[1],1);
// // 				SET_PARTICLE_PROPERTY(strName,v);
// 			}
	
// 			void IBaseObject::SetProperty( AString strName,Float3& vParam ){
// 				SET_PARTICLE_PROPERTY(strName,vParam);
// 			}
	
			void IBaseObject::SetProperty( AString strName,Float4& vParam ){
				//SET_PARTICLE_PROPERTY(strName,vParam);
			}
	
// 			void IBaseObject::SetProperty( AString strName,Float4& qParam ){
// 				Float4	v(qParam.x,qParam.y,qParam.z,qParam.w);
// 				SET_PARTICLE_PROPERTY(strName,v);
// 			}
	
			void IBaseObject::SetProperty( AString strName,Float44& mParam ){
				SET_PARTICLE_PROPERTY(strName,mParam);
			}
	
			void IBaseObject::SetProperty( AString strName,void* pParam ){
	
			}
	
			void IBaseObject::GetProperty( AString strName,SInt& iParam ){
	
			}
	
			void IBaseObject::GetProperty( AString strName,Real& fParam ){
	
			}
	
// 			void IBaseObject::GetProperty( AString strName,Vector2& vParam ){
// 	
// 			}
	
// 			void IBaseObject::GetProperty( AString strName,Float3& vParam ){
// 	
// 			}
	
			void IBaseObject::GetProperty( AString strName,Float4& vParam ){
	
			}
	
// 			void IBaseObject::GetProperty( AString strName,Float4& qParam ){
// 	
// 			}
	
			void IBaseObject::GetProperty( AString strName,Float44& mParam ){
	
			}
	
			void* IBaseObject::GetProperty( AString strName ){
				return	NULL;
			}
	
			U1 IBaseObject::IsDead(){
				return	m_bIsDead;
			}
	
			void IBaseObject::Updata(){
				//¸üÐÂ°üÎ§ºÐ
				MovableObject::Updata();
	
				static	Real&	fCurrentTime	=	GetGlobalSetting().m_ShaderParam.m_fTotalTime;
				if(m_bInfiniteLife){
					return;
				}
				//ÅÐ¶ÏÊÇ·ñËÀÍö
				if(fCurrentTime	-	m_fBornTime	>	m_fLife){
					m_bIsDead	=	true;
					//´ÓäÖÈ¾½ÚµãÒÆ³ý
					if(m_pParentNode!=NULL){
						GetParentSceneNode()->detachObject(this);
					}
	
					GetGlobalSetting().m_pParticleSystem->DestroyParticle(this);
				}
			}
	
			IBaseObject::IBaseObject(CAString&	strName,Info*	pInfo):Common::IProduct(strName){
				m_bIsDead	=	false;
				if(pInfo!=NULL){
					m_Info	=	*pInfo;
				}
				m_bInfiniteLife	=	false;
				m_fLife			=	10000.0f;
				m_fBornTime		=	GetGlobalSetting().m_ShaderParam.m_fTotalTime;
			}
	
				void IBaseObject::SetLife( Real fLife ){
					m_fLife	=	fLife;
				}
	
				void IBaseObject::SetInfiniteLife( U1 bEnable ){
					m_bInfiniteLife	=	bEnable;
				}
		}
	}
};