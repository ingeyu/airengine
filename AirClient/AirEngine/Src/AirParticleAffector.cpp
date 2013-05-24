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
			PhysicsSystem* pPhysicsSys	=	PhysicsSystem::GetSingleton();
			PElementList& lst = pParticle->GetElementList();
			Float3 p;
			for(PElementList::iterator i = lst.begin();i!=lst.end();i++){
				p = (*i)->vPos;
				(*i)->vPos	+= (*i)->vVelocity*frameTime.fTimeDelta;
				if(m_pInfo->bEnableCollision==0)
					continue;
				if(pPhysicsSys->CollisionDetect((*i)->vPos,(*i)->vVelocity)){
					p+=(*i)->vVelocity*frameTime.fTimeDelta;
					(*i)->vPos=p;
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
			pEInfo->pForceField				=	NULL;
			while(true){
				AString& strTemp2	=	vecWord[i++];
				if(strTemp2=="}"){
					break;
				}else if(strTemp2	==	"CollisionDetect"){
					pEInfo->bEnableCollision	=	Common::Converter::ToU1(vecWord[i++]);
				}
			}
			return pEInfo;
		}

	}
}