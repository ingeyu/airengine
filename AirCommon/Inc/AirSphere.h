#ifndef AirSphere_h__
#define AirSphere_h__

#include "AirCommonHeader.h"
#include "AirCommonVector3.h"

namespace	Air{
	
	class	Sphere{
	public:
		Sphere():m_fRadius(0.0f){
		};
		Sphere(const Float3&	vCenter,Real fRadius)
			:	m_vCenter(vCenter),
				m_fRadius(fRadius)
		{

		};
		Sphere(const Float4&	vVec4){
			m_vCenter	=	vVec4;
			m_fRadius	=	vVec4.w;
		};
		Float3	m_vCenter;
		Real	m_fRadius;
	};

}
#endif // AirSphere_h__