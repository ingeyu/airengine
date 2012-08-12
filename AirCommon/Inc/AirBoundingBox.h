#ifndef AirBoundingBox_h__
#define AirBoundingBox_h__

#include "AirCommonHeader.h"


namespace	Air{
	enum enumPlaneType{
		enPT_X,
		enPT_Y,
		enPT_Z
	};
	class	COMMON_EXPORT	BoundingBox{
	public:
		Float3	vMin;
		Float3	vMax;

	public:
		BoundingBox(){};
		BoundingBox(const	Float3&	vmin,const Float3&	vmax);
		//BoundingBox(const	Float3&	vcenter,const Float3&	vhalfsize);
		BoundingBox(float	minx,float miny,float minz,float maxx,float maxy,float maxz);

		void				BuildFrom3Point(const Float3& v0,const Float3& v1,const Float3& v2);

		U1					IsInclude(const Float3&	v)const;
		U1					IsInclude(const BoundingBox&	b)const;
		//U1					IsSphereIn(const )
		BoundingBox&		Add(const Float3&	v);
		BoundingBox&		Add(const BoundingBox&	b);
		BoundingBox&		Intersect(const BoundingBox&	b);
		S32					GetSide(float	fPlane,enumPlaneType	pt	=	enPT_X)const;

		Float3				GetHalfSize()const;
		void				GetHalfSize(Float3& vOut)const;
		Float3				GetCenter()const;
		void				GetCenter(Float3& vOut)const;

		BoundingBox			Transform(const Common::Matrix&	matrix);
		//只判断是否相交
		U1					RayCast(const	Float3&	vStart,const	Float3&	vDir)const;
		//只判断是否相交	有最大相交距离限制
		U1					RayCast(const	Float3&	vStart,const	Float3&	vDir,float fMaxDistance)const;
		//判断相交并且返回 近交点和远交点距离
		U1					RayCast(const	Float3&	vStart,const	Float3&	vDir,float*	pNearDistance,float*	pFarDistance)const;
		//判断相交并且返回	近交点 
		U1					RayCastNear(const	Float3&	vStart,const	Float3&	vDir,float*	pNearDistance)const;
		//判断相交并且返回	远交点 （主要用于 射线起点在包围盒内部）
		U1					RayCastFar(const	Float3&	vStart,const	Float3&	vDir,float*	pFarDistance)const;
		
	};
}
#endif // AirBoundingBox_h__
