#include "AirRay.h"
#include "AirCommonCollision.h"
namespace	Air{


	Ray::Ray()
	{

	}

	Ray::Ray( const Float3& vStart,const Float3& vDir )
	{
		m_vStart		=	vStart;
		m_vDirection	=	vDir;
	}

	const Float3& Ray::GetOrigin() const
	{
		return	m_vStart;
	}

	const Float3& Ray::GetDirection() const
	{
		return	m_vDirection;
	}

	Air::Ray Ray::Transform( const Common::Matrix& mat ) const
	{
		Float3	vNewStart	=	mat*m_vStart;
		Float3	vNewLook	=	mat*(m_vStart+m_vDirection);
		Float3	vNewDir		=	(vNewLook	-	vNewStart).NormalizeCopy();

		return	Ray(vNewStart,vNewDir);
	}

	bool Ray::Intersect( const Sphere& obj ) const
	{
		float	dis				=	(obj.m_vCenter	-	m_vStart).Length();
		if(dis	<=	obj.m_fRadius)
			return	true;
		float	dotLen			=	(obj.m_vCenter	-	m_vStart).Dot(m_vDirection);
		
		float	center_to_ray	=	sqrt(dis*dis-dotLen*dotLen);
		return	center_to_ray	<	obj.m_fRadius;
	}

	bool Ray::Intersect( const BoundingBox& obj,float*	pNear ) const
	{
		if(obj.IsInclude(m_vStart)){
			if(pNear!=NULL){
				*pNear	=	0.0f;
			}
			return	true;
		}
		return	obj.RayCast(m_vStart,m_vDirection,pNear);
	}

	bool Ray::Intersect( const Float3& v0,const Float3& v1,const Float3& v2,float* pDistance ) const
	{
		return	Common::IntersectRayTriangle(m_vStart.ToXM(),m_vDirection.ToXM(),v0.ToXM(),v1.ToXM(),v2.ToXM(),pDistance);
	}

	bool Ray::Intersect( const Common::Plane& obj ) const
	{
		float	fDot	=	obj.m_vNormal.Dot(m_vDirection);
		if(	fDot	==	0.0f)
		{
			return	false;
		}

		float	fDis	=	obj.m_vNormal.Dot(m_vStart)+obj.m_fDistance;
		float	t		=	fDis/fDot;
		if(t<0)
			return	false;

		Float3	vHitPosition	=	m_vDirection*t+m_vStart;
		return	true;
	}

}