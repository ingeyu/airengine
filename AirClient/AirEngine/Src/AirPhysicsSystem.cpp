#include "AirPhysicsSystem.h"
#include "AirPhysicsSVO.h"
namespace	Air{
	namespace	Physics{


		System::System()
		{
			m_pSVO	=	NULL;
			m_vGravity	=	Float3(0,-9.8,0);
		}

		Air::U1 System::Initialization()
		{
			m_pSVO	=	new SVO("SVO");
			m_pSVO->AddRef();
			return true;
		}

		Air::U1 System::Release()
		{
			SAFE_RELEASE_REF(m_pSVO);
			return true;
		}

		void System::Update( const FrameTime& frameTime )
		{

		}

		Air::U1 System::CollisionDetect( const Float3& p,Float3& v )
		{
			return m_pSVO->CollisionDetect(p,&v);
		}

		void System::UpdateSVO( const STD_VECTOR<U32>& svoData,U32 uiDepth,float fScale )
		{
			m_pSVO->Update(svoData,uiDepth,fScale);
		}

		Air::U1 System::Simulation( Float3& p,Float3& v,U1 bGravity /*= false*/ )
		{
			if(!bGravity){
				return CollisionDetect(p,v);
			}else{
				//static 
			}
			return false;
		}

		Air::U1 System::Silumation( Float3& p,float fRadius,float fHeight,Float3& v,U1 bGravity /*= false*/ )
		{
			static float& fTimeDelta	=	GetTimer().m_FrameTime.fTimeDelta;

			Float3 vOffset	=	v*fTimeDelta;
			Float3 vTestPos	=	p+vOffset;

			Float3 vHalfSize	=	Float3(0.5,1,0.5)*fRadius;
			Float3 vCenter		=	vTestPos+Float3(0,0.5,0);
			BoundingBox bound(vCenter-vHalfSize,vCenter+vHalfSize);



			BoxShape	moveShape;
			moveShape.m_vHalfSize			=	bound.GetHalfSize()*Float3(1,0.5,1);
			moveShape.m_vPosition			=	bound.GetCenter();
			BoxShape	gravityShape;
			gravityShape.m_vHalfSize		=	bound.GetHalfSize()*Float3(0.5,1,0.5);
			gravityShape.m_vPosition		=	bound.GetCenter();
			
			Float3 vNormal;
			Float3 vCorrectOffset;
			if(m_pSVO->CollisionDetect(&moveShape,&gravityShape,&vNormal,&vCorrectOffset)){
				//if(vCorrectOffset.y	>	0){
					v.y = 0;
				//}
				
				Float3 vCorrect	=	v	+	vNormal*v.Dot(-vNormal);
				p	+=(vCorrect+vNormal)*fTimeDelta;
				p.y = vCorrectOffset.y;
				
				v.y += m_vGravity.y*fTimeDelta;
				return true;
			}else{
				p=vTestPos;
				v.y+=m_vGravity.y*fTimeDelta;
				return false;
			}


			
		}

	}
}