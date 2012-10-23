#include "AirRay.h"

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

	bool Ray::Intersect( const BoundingBox& obj ) const
	{
		if(obj.IsInclude(m_vStart))
			return	true;
		const Float3& min		= obj.vMin;
		const Float3& max		= obj.vMax;

		Real lowt = 0.0f;
		Real t;
		bool hit = false;
		Float3 hitpoint;
		// Check each face in turn, only check closest 3
		// Min x
		if (m_vStart.x <= min.x && m_vDirection.x > 0)
		{
			t = (min.x - m_vStart.x) / m_vDirection.x;
			if (t >= 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = m_vStart + m_vDirection * t;
				if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Max x
		if (m_vStart.x >= max.x && m_vDirection.x < 0)
		{
			t = (max.x - m_vStart.x) / m_vDirection.x;
			if (t >= 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = m_vStart + m_vDirection * t;
				if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Min y
		if (m_vStart.y <= min.y && m_vDirection.y > 0)
		{
			t = (min.y - m_vStart.y) / m_vDirection.y;
			if (t >= 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = m_vStart + m_vDirection * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Max y
		if (m_vStart.y >= max.y && m_vDirection.y < 0)
		{
			t = (max.y - m_vStart.y) / m_vDirection.y;
			if (t >= 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = m_vStart + m_vDirection * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Min z
		if (m_vStart.z <= min.z && m_vDirection.z > 0)
		{
			t = (min.z - m_vStart.z) / m_vDirection.z;
			if (t >= 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = m_vStart + m_vDirection * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.y >= min.y && hitpoint.y <= max.y &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Max z
		if (m_vStart.z >= max.z && m_vDirection.z < 0)
		{
			t = (max.z - m_vStart.z) / m_vDirection.z;
			if (t >= 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = m_vStart + m_vDirection * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.y >= min.y && hitpoint.y <= max.y &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}

		return	hit;
	}

	bool Ray::Intersect( const Float3& v0,const Float3& v1,const Float3& v2 ) const
	{
		return	false;
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