#ifndef AirParticleElement_h__
#define AirParticleElement_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	ENGINE_EXPORT	ParticleElement	:	public	MemoryObject
		{
		public:
			ParticleElement(){
				m_fBornTime	=	0.0f;
				m_fSize		=	1.0f;
			}; 
			ParticleElement(float fTime){
				m_fBornTime	=	fTime;
				m_fSize		=	1.0f;
			}; 
			Float3	vPos;
			Float3	vVelocity;
			float	m_fBornTime;
			float	m_fSize;
		};
		typedef	STD_LIST<ParticleElement*>	PElementList;
	}
}
#endif // AirParticleElement_h__