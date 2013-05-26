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
		
		struct	Shape	:	
			public	MemoryObject{
			Shape(){
				m_UserData	=	0;
				m_Type		=	enPST_Point;
			};
			void		SetBox(const Float3& vCenter,const Float3& halfSize){
				m_Type		=	enPST_Box;
				m_vPosition	=	vCenter;
				m_vHalfSize	=	halfSize;
			};
			void		SetSphere(const Float3& vCenter,float fRadius){
				m_Type		=	enPST_Sphere;
				m_vPosition		=	vCenter;
				m_vHalfSize.x	=	fRadius;
			};
			void		SetCylinder(const Float3& vCenter,float fRadius,float fHeight){
				m_Type			=	enPST_Cylinder;
				m_vPosition		=	vCenter;
				m_vHalfSize.x	=	fRadius;
				m_vHalfSize.y	=	fHeight;
			};
			void*					m_UserData;
			enumPhysicsShapeType	m_Type;
			Float3					m_vPosition;
			Float3					m_vHalfSize;//Sphere x=Radius Cylinder x=Radius y=Height Plane x=Normal
		};
		
	}
}
#endif // AirPhysicsShape_h__
