#include "AirParticleAffector.h"
#include "AirParticle.h"
#include "AirPhysicsSystem.h"
#include "AirCommonParse.h"
namespace	Air{
	namespace	Engine{
		/*
		extern STD_VECTOR<U32> vecTree;
#define	MAX_DEPTH	10
#define VOXEL_BOUND_SIZE	pow(2.0f,MAX_DEPTH-1);
#define SCALE				8


		U1 CollisionDetection(const Float3& vPos,Float3& vVelocity){
			if(vecTree.empty())
				return false;

			U32 uiMaxDepth	=	MAX_DEPTH;
			float	uiMaxVoxelBoundSize	=	VOXEL_BOUND_SIZE;
			BoundingBox	bound;
			bound.vMin=Float3(-uiMaxVoxelBoundSize,-uiMaxVoxelBoundSize,-uiMaxVoxelBoundSize);
			bound.vMax=Float3(uiMaxVoxelBoundSize,uiMaxVoxelBoundSize,uiMaxVoxelBoundSize);

			if(!bound.IsInclude(vPos)){
				return false;
			}

			Float3 VoxelIndex = vPos-bound.vMin;
			Common::IntVec3 vIndex(VoxelIndex.x,VoxelIndex.y,VoxelIndex.z);
			U32 offset	=	0;
			for(int i=0;i<MAX_DEPTH;i++){
				U32 uiSHR	=	(MAX_DEPTH-1-i);
				Common::IntVec3	maskValue(vIndex.x>>uiSHR,vIndex.y>>uiSHR,vIndex.z>>uiSHR);//mask;
				maskValue	=	Common::IntVec3(maskValue.x&1,maskValue.y&1,maskValue.z&1);

				U32 idx	=	(maskValue.x<<2)+(maskValue.y<<1)+maskValue.z;

				U32	address			=	(offset+idx);

				U32& uiValue	=	vecTree[address];
				if(uiValue==0){
					return false;
				}else if(i==(MAX_DEPTH-1)){
					Float3 vNormal = Float3(((uiValue&0x00ff0000)>>16)/255.0f,
											((uiValue&0x0000ff00)>>8)/255.0f,
											((uiValue&0x000000ff))/255.0f);
					vNormal	=	vNormal*2-1;
					Float3 vDir	=	vVelocity;
					vDir.Normalize();
					if(vNormal.Dot(vDir)>0){
						vNormal	*=-1;
					}
					Float3 vReflect	=	vNormal*2*vNormal.Dot(-vDir)+vDir;
					vVelocity	=	vReflect*vVelocity.Length();
					return true;
				}else{
					offset	=	uiValue;
				}
			}

			return false;
		}
		*/
		AString ParticleAffector::ProductTypeName	="DefaultAffector";
		ParticleAffector::ParticleAffector( CAString& strName,Info* pInfo ):IProduct(strName)
		{
			m_pInfo	=	pInfo;
		}

		void ParticleAffector::Update( const FrameTime& frameTime,Particle* pParticle )
		{
			const	ParticleCB&	cb	=	pParticle->GetCallback();
			U32		uiMask			=	pParticle->GetCollisionMask();
			
			ForceField forcefield[4];
			if(m_pInfo->uiCount	>	0){
				memcpy(forcefield,m_pInfo->forceField,sizeof(ForceField)*m_pInfo->uiCount);
				UpdateForceField(forcefield,pParticle);
			}

			PhysicsSystem* pPhysicsSys	=	PhysicsSystem::GetSingleton();
			PElementList& lst = pParticle->GetElementList();
			Float3 p;
			for(PElementList::iterator i = lst.begin();i!=lst.end();i++){
				ParticleElement* e = (*i);
				p = e->vPos;
				UpdateVelocityPosition(frameTime,e,forcefield);

				if(m_pInfo->bEnableCollision==0)
					continue;
				if(pPhysicsSys->CollisionDetect(e->vPos,e->vVelocity,uiMask)){
					if(cb.pCB!=NULL){
						(*cb.pCB)(cb.pObject,*e,pParticle,enEHT_DynamicObject,NULL);
					}					
					p+=e->vVelocity*frameTime.fTimeDelta;
					e->vPos=p;
				}
			}
		}

		Air::U1 ParticleAffector::Create()
		{
			return true;
		}

		Air::U1 ParticleAffector::Destroy()
		{
			return true;
		}

		void* ParticleAffector::ScriptParser( StringVector& vecWord,U32& i )
		{
			ParticleAffector::Info* pEInfo	=	(ParticleAffector::Info*)ParticleSystem::GetSingleton()->PTAlloc(sizeof(ParticleAffector::Info));
			pEInfo->bEnableCollision		=	false;
			pEInfo->uiCount					=	0;
			while(true){
				AString& strTemp2	=	vecWord[i++];
				if(strTemp2=="}"){
					break;
				}else if(strTemp2	==	"CollisionDetect"){
					pEInfo->bEnableCollision	=	Common::Converter::ToU1(vecWord[i++]);
				}else if(strTemp2	==	"PointForce"){
					ForceField& field		=	pEInfo->forceField[pEInfo->uiCount];
					pEInfo->uiCount++;
					field.type				=	enFFT_PointForce;
					field.vPosition.x	=	Common::Parse::ParseFloat(vecWord,i);
					field.vPosition.y	=	Common::Parse::ParseFloat(vecWord,i);
					field.vPosition.z	=	Common::Parse::ParseFloat(vecWord,i);
					field.vForce_Velocity.x	=	Common::Parse::ParseFloat(vecWord,i);



				}
				else if(strTemp2	==	"DirectionForce"){
					ForceField& field		=	pEInfo->forceField[pEInfo->uiCount];
					pEInfo->uiCount++;
					field.type				=	enFFT_DirectionForce;
					field.vForce_Velocity.x	=	Common::Parse::ParseFloat(vecWord,i);
					field.vForce_Velocity.y	=	Common::Parse::ParseFloat(vecWord,i);
					field.vForce_Velocity.z	=	Common::Parse::ParseFloat(vecWord,i);
				}
				else if(strTemp2	==	"DirectionVelocity"){
					ForceField& field		=	pEInfo->forceField[pEInfo->uiCount];
					pEInfo->uiCount++;
					field.type				=	enFFT_DirectionVelocity;
					field.vForce_Velocity.x	=	Common::Parse::ParseFloat(vecWord,i);
					field.vForce_Velocity.y	=	Common::Parse::ParseFloat(vecWord,i);
					field.vForce_Velocity.z	=	Common::Parse::ParseFloat(vecWord,i);
				}
				else if(strTemp2	==	"RotateForce"){
					ForceField& field		=	pEInfo->forceField[pEInfo->uiCount];
					pEInfo->uiCount++;
					field.type				=	enFFT_RotateForce;
					field.vPosition.x	=	Common::Parse::ParseFloat(vecWord,i);
					field.vPosition.y	=	Common::Parse::ParseFloat(vecWord,i);
					field.vPosition.z	=	Common::Parse::ParseFloat(vecWord,i);
					field.vAxis.x	=	Common::Parse::ParseFloat(vecWord,i);
					field.vAxis.y	=	Common::Parse::ParseFloat(vecWord,i);
					field.vAxis.z	=	Common::Parse::ParseFloat(vecWord,i);
					//field.vAxis.Normalize();
					field.vForce_Velocity.x	=	Common::Parse::ParseFloat(vecWord,i);

				}
				else if(strTemp2	==	"RotateVelocity"){
					ForceField& field		=	pEInfo->forceField[pEInfo->uiCount];
					pEInfo->uiCount++;
					field.type				=	enFFT_RotateVelocity;
					field.vPosition.x	=	Common::Parse::ParseFloat(vecWord,i);
					field.vPosition.y	=	Common::Parse::ParseFloat(vecWord,i);
					field.vPosition.z	=	Common::Parse::ParseFloat(vecWord,i);
					field.vAxis.x	=	Common::Parse::ParseFloat(vecWord,i);
					field.vAxis.y	=	Common::Parse::ParseFloat(vecWord,i);
					field.vAxis.z	=	Common::Parse::ParseFloat(vecWord,i);
					//field.vAxis.Normalize();
					field.vForce_Velocity.x	=	Common::Parse::ParseFloat(vecWord,i);

				}
				
			}
			return pEInfo;
		}

		void ParticleAffector::UpdateVelocityPosition( const FrameTime& frameTime,ParticleElement* pElement,ForceField* pForceField )
		{
			Float3 vTempVelocity;
			U32 uiForceFieldCount	=	m_pInfo->uiCount;
			for(U32 i=0;i<uiForceFieldCount&&i<4;i++){
				ForceField& p	=	pForceField[i];
				switch(p.type){
					case	enFFT_PointForce		 :{
						Float3 v	=	p.vPosition	-	pElement->vPos;
						float fLength	=	v.Length();
						if(fLength>0.00001f){
							v.Normalize();
							Float3 vForce	=	(v*p.vForce_Velocity.x/fLength);
							pElement->vVelocity	+=	vForce*frameTime.fTimeDelta;
						}
						;
													  }break;
					case	enFFT_DirectionForce	 :{
						pElement->vVelocity	+=	p.vForce_Velocity*frameTime.fTimeDelta;
						
													  }break;
					case	enFFT_DirectionVelocity	 :{
						vTempVelocity+=p.vForce_Velocity;
													  }break;
					case	enFFT_RotateForce		 :{
						Float3 v = pElement->vPos	-	p.vPosition;
						Float3 vPos		=	p.vAxis*v.Dot(p.vAxis)+p.vPosition;
						Float3 vDir	=	(vPos-pElement->vPos);
						float fLength	=	vDir.Length();
						if(fLength	>0.00001f){
							vDir.Normalize();
						
							Float3 vForce	=	(vDir*p.vForce_Velocity.x/fLength);
							pElement->vVelocity	+=	vForce*frameTime.fTimeDelta;
						}
						
													  }break;
					case	enFFT_RotateVelocity	 :{
						Float3 v = pElement->vPos	-	p.vPosition;
						Float3 vPos		=	p.vAxis*v.Dot(p.vAxis)+p.vPosition;
						Float3 vDir	=	vPos	-	pElement->vPos;
						if(vDir.Length()	>0.00001f){
							vDir.Normalize();
							Float3 vVelocity	=	p.vAxis.Cross(vDir)*p.vForce_Velocity.x;
							vTempVelocity+=	vVelocity;
						}
													  }break;
				}

				
			}
			pElement->vPos	+= (pElement->vVelocity+vTempVelocity)*frameTime.fTimeDelta;
		}

		void ParticleAffector::UpdateForceField( ForceField* pForceField,Particle* pParticle )
		{
			Float44& matWorld	=	*pParticle->GetWorldMatrix();

			U32 uiForceFieldCount	=	m_pInfo->uiCount;
			for(U32 i=0;i<uiForceFieldCount&&i<4;i++){
				ForceField& p	=	pForceField[i];
				switch(p.type){
				case	enFFT_PointForce		 :{
					p.vPosition	=	matWorld*(p.vPosition);
												  }break;
				case	enFFT_DirectionForce	 :
				case	enFFT_DirectionVelocity	 :{
					float fLength	=	p.vForce_Velocity.Length();
					Float3 v0	=	matWorld*p.vForce_Velocity;
					v0-=matWorld.GetPosition();
					v0.Normalize();
					p.vForce_Velocity	=	v0*fLength;
												  }break;
				case	enFFT_RotateForce		 :
				case	enFFT_RotateVelocity	 :{
					p.vPosition	=	matWorld*p.vPosition;
					Float3 v		=	matWorld*p.vAxis	-	matWorld.GetPosition();
					p.vAxis	=	v.Normalize();
												  }break;
				}


			}
		}

	}
}