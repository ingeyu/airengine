#include "AirAISystem.h"

namespace	Air{
	namespace	AI{


		System::System()
		{
			m_SVO		=	NULL;
			m_uiDepth	=	0;
			m_fSVOScale	=	1.0f;
		}

		Air::U1 System::Create()
		{
			return true;
		}

		Air::U1 System::Destroy()
		{

			return true;
		}

		void System::SVOUpdate( U32* svoData,U32 uiDepth,float fScale )
		{
			m_SVO		=	svoData;
			m_uiDepth	=	uiDepth;
			m_fSVOScale	=	fScale;
		}

		STD_VECTOR<Float3> System::SVOFindPath( const Float3& vStart,const Float3& vTarget )
		{
			STD_VECTOR<Float3> vecPathPoint;

			return vecPathPoint;
		}

	}
}