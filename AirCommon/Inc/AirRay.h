#ifndef AirRay_h__
#define AirRay_h__

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonVector3.h"
#include "AirBoundingBox.h"
#include "AirCommonMatrix.h"
#include "AirSphere.h"
#include "AirCommonPlane.h"


namespace	Air{

		class	COMMON_EXPORT	Ray{
		public:
			Ray();
			Ray(const Float3& vStart,const Float3& vDir);

			const Float3&	GetOrigin()const;
			const Float3&	GetDirection()const;

			Ray				Transform(const Common::Matrix&	mat)const;

			bool			Intersect(const Sphere&	obj)const;
			bool			Intersect(const BoundingBox&	obj,float*	pNear	=	NULL)const;
			bool			Intersect(const Float3&	v0,const Float3&	v1,const Float3&	v2,float* pDistance =NULL)const;
			bool			Intersect(const Common::Plane&	obj)const;
		
			Float3	m_vStart;
			Float3	m_vDirection;
		};

}
#endif // AirRay_h__