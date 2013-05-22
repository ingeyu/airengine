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
			BoxShape shape;
			
			shape.m_vHalfSize		=	Float3(1,2,1)*fRadius;
			Float3 vDir = v+m_vGravity*fTimeDelta*5;
			Float3 vPos = p+vDir*fTimeDelta;
			shape.m_vPosition	=	vPos;
			Float3 vNormal;
			if(m_pSVO->CollisionDetect(&shape,&vNormal)){
				
				p+=(v+vNormal).Normalize()*fTimeDelta;
				//p+=	vDir*fTimeDelta;
				return true;
			}else{
				p+=	vDir*fTimeDelta;
				return false;
			}
		}

	}
}