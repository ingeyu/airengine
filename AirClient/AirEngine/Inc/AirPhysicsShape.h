#ifndef AirPhysicsShape_h__
#define AirPhysicsShape_h__

#include "AirEngineHeader.h"

namespace	Air{
	enum	enumPhysicsShapeType{
		enPST_Point,
		enPST_Triangle,
		enPST_Box,
		enPST_Sphere,
		enPST_Cylinder,
		enPST_Plane
	};
	namespace	Physics{
		
		struct	PointShape	:	
			public	MemoryObject{
			PointShape(){
				m_UserData	=	0;
				m_Type		=	enPST_Point;
			};
			void*					m_UserData;
			enumPhysicsShapeType	m_Type;
			Float3					m_vPosition;
		};
		struct SphereShape	:	public	PointShape{
			SphereShape(){
				m_Type	=	enPST_Sphere;
			};
			float	fRadius;
		};
		struct BoxShape	:	public	PointShape{
			BoxShape(){
				m_Type	=	enPST_Box;
			};
			Float3 m_vHalfSize;
		};
		
		struct CylinderShape	:	public	PointShape{
			CylinderShape(){
				m_Type	=	enPST_Cylinder;
			};
			float	fRadius;
			float	fHeight;
		};
		struct PlaneShape	:	public	PointShape{
			PlaneShape(){
				m_Type	=	enPST_Plane;
			};
			Float3 vNormal;
		};
	}
}
#endif // AirPhysicsShape_h__
