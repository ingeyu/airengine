#ifndef AirParticleElement_h__
#define AirParticleElement_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	ENGINE_EXPORT	ParticleElement	:	public	MemoryObject
		{
		public:
			ParticleElement(){
				fBornTime	=	0.0f;
				fSize		=	1.0f;
			}; 
			ParticleElement(float fTime){
				fBornTime	=	fTime;
				fSize		=	1.0f;
			}; 
			Float3	vPos;
			Float3	vVelocity;
			float	fBornTime;
			float	fSize;
		};
		typedef	STD_LIST<ParticleElement*>	PElementList;
	}
}
#endif // AirParticleElement_h__