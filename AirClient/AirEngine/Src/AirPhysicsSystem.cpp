#include "AirPhysicsSystem.h"
#include "AirPhysicsSVO.h"
namespace	Air{
	namespace	Physics{


		System::System()
		{
			m_pSVO	=	NULL;
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
			PointShape shape;
			shape.m_vPosition	=	p;
			
			return m_pSVO->CollisionDetect(&shape,&v);
		}

		void System::UpdateSVO( const STD_VECTOR<U32>& svoData,U32 uiDepth,float fScale )
		{
			m_pSVO->Updata(svoData,uiDepth,fScale);
		}

	}
}