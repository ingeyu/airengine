#include "AirCommonPlane.h"

namespace	Air{
	namespace	Common{


		Plane::Plane( const Vector3 &v1, const Vector3 &v2, const Vector3 &v3 ){
			SetVertex(v1,v2,v3);
		}

		Plane::Plane(){
			m_vNormal	=	Vector3(0,1,0);
			m_fDistance	=	0.0f;
		}

		void Plane::SetVertex( const Vector3 &v1, const Vector3 &v2, const Vector3 &v3 ){
			Vector3 aux1, aux2;

			aux1 = v1 - v2;
			aux2 = v3 - v2;

			m_vNormal = aux2.Cross(aux1);

			m_vNormal.Normalize();

			m_fDistance = -(m_vNormal.Dot(v2));
		}

		void Plane::SetNormal_Point( const Vector3 &normal, const Vector3 &point ){
			m_vNormal	=	normal;
			m_vNormal.Normalize();
			m_fDistance = -(m_vNormal.Dot(point));
		}

		void Plane::Set( float x, float y, float z, float w ){
			m_vNormal			=	Vector3(x,y,z);
			float l				=	m_vNormal.Length();
			float	invLength	=	1.0f/l;
			m_vNormal			=	Vector3(x*invLength,y*invLength,z*invLength);
			m_fDistance			=	w*invLength;
		}

		float Plane::Distance( const Vector3 &p ){
			return (m_fDistance + m_vNormal.Dot(p));
		}

		Air::enumPlaneSide Plane::GetSide( const Vector3& p ){
			return	(m_vNormal.Dot(p)+m_fDistance)>0?enPS_Position:enPS_Negative;
		}

		Air::enumPlaneSide Plane::GetSide( const Vector3& center,float fRadius ){
			float	f	=	Distance(center);
			if(f	>	fRadius){
				return	enPS_Position;
			}else	if(f	<	-fRadius){
				return	enPS_Negative;
			}else{
				return	enPS_Intersect;
			}
		}

		Air::enumPlaneSide Plane::GetSide( const Vector3& p0, const Vector3& p1, const Vector3& p2 ){
			unsigned long	i	=	0;
			i+=	GetSide(p0);
			i+=	GetSide(p1);
			i+=	GetSide(p2);
			switch(i){
				case	0:	return	enPS_Position;
				case	3:	return	enPS_Negative;
				default:	return	enPS_Intersect;
			}
			return	enPS_Negative;
		}

		Air::enumPlaneSide Plane::GetSide( Vector3* p,unsigned long uiSize ){
			unsigned long	iCount	=	0;
			for(unsigned long i=0;i<uiSize;i++){
				iCount	+=	GetSide(p[i]);
			}
			if(iCount==0){
				return	enPS_Position;
			}else	if(iCount==8){
				return	enPS_Negative;
			}else
				return	enPS_Intersect;
		}
	}
}