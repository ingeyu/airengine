/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/20
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  AirCommonPlane.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRCOMMONPLANE_HEAD_FILE
#define AIRCOMMONPLANE_HEAD_FILE

#include "AirCommonHeader.h"
#include "AirCommonVector3.h"

namespace	Air{
	enum enumPlaneSide{
		enPS_Position,	///<	正面
		enPS_Negative,	///<	反面
		enPS_Intersect	///<	相交
	};
	namespace Common{
		class COMMON_EXPORT Vector3;
		/**	\brief	平面
		*
		*	平面	方程 Ax+By+Cz+D=0
		*
		***/
		class COMMON_EXPORT	Plane{
		public:
			Vector3	m_vNormal;
			float	m_fDistance;

			Plane(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3);
			Plane();
			void			SetVertex( const Vector3  &v1,  const Vector3  &v2,  const Vector3  &v3);
			void			SetNormal_Point(const Vector3 &normal, const Vector3 &point);
			void			Set(float x, float y, float z, float w);
			float			Distance(const	Vector3 &p);
			enumPlaneSide	GetSide(const	Vector3&	p);
			enumPlaneSide	GetSide(const	Vector3&	center,float	fRadius);
			enumPlaneSide	GetSide(const	Vector3&	p0,
									const	Vector3&	p1,
									const	Vector3&	p2);
			enumPlaneSide	GetSide(Vector3*	p,unsigned long	uiSize);
		};
		
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRCOMMONPLANE_HEAD_FILE