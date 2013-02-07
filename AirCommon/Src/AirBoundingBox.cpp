#include "AirBoundingBox.h"
namespace	Air{

	BoundingBox::BoundingBox( const Float3& vmin,const Float3& vmax )
	{
		vMin	=	vmin;
		vMax	=	vmax;
	}

// 	BoundingBox::BoundingBox( const Float3& vcenter,const Float3& vhalfsize )
// 	{
// 		vMin	=	vcenter	-	vhalfsize;
// 		vMax	=	vcenter	+	vhalfsize;
// 	}

	BoundingBox::BoundingBox( float minx,float miny,float minz,float maxx,float maxy,float maxz )
	{
		vMin	=	Float3(minx,miny,minz);
		vMax	=	Float3(maxx,maxy,maxz);
	}

	Air::U1 BoundingBox::IsInclude( const Float3& v ) const
	{
		if(	v.x	<	vMin.x	||
			v.y	<	vMin.y	||
			v.z	<	vMin.z	||
			v.x	>	vMax.x	||
			v.y	>	vMax.y	||
			v.z	>	vMax.z)
		{
			return	false;
		}
		return	true;
	}

	Air::U1 BoundingBox::IsInclude( const BoundingBox& b ) const
	{
		if(	b.vMin.x	<	vMin.x	||
			b.vMin.y	<	vMin.y	||
			b.vMin.z	<	vMin.z	||
			b.vMax.x	>	vMax.x	||
			b.vMax.y	>	vMax.y	||
			b.vMax.z	>	vMax.z)
		{
			return	false;
		}
		return	true;
	}

	BoundingBox& BoundingBox::Add( const Float3& v )
	{
		if(	v.x	<	vMin.x)vMin.x	=	v.x;
		if( v.y	< 	vMin.y)vMin.y	=	v.y;
		if( v.z	<	vMin.z)vMin.z	=	v.z;
		if( v.x	>	vMax.x)vMax.x	=	v.x;
		if( v.y	>	vMax.y)vMax.y	=	v.y;
		if( v.z	>	vMax.z)vMax.z	=	v.z;
		return	*this;
	}

	BoundingBox& BoundingBox::Add( const BoundingBox& b )
	{
		if(	b.vMin.x	<	vMin.x)vMin.x	=	b.vMin.x;
		if( b.vMin.y	< 	vMin.y)vMin.y	=	b.vMin.y;
		if( b.vMin.z	<	vMin.z)vMin.z	=	b.vMin.z;
		if( b.vMax.x	>	vMax.x)vMax.x	=	b.vMax.x;
		if( b.vMax.y	>	vMax.y)vMax.y	=	b.vMax.y;
		if( b.vMax.z	>	vMax.z)vMax.z	=	b.vMax.z;
		return	*this;
	}

	BoundingBox& BoundingBox::Intersect( const BoundingBox& b )
	{
		if(	b.vMin.x	>	vMin.x)vMin.x	=	b.vMin.x;
		if( b.vMin.y	> 	vMin.y)vMin.y	=	b.vMin.y;
		if( b.vMin.z	>	vMin.z)vMin.z	=	b.vMin.z;
		if( b.vMax.x	<	vMax.x)vMax.x	=	b.vMax.x;
		if( b.vMax.y	<	vMax.y)vMax.y	=	b.vMax.y;
		if( b.vMax.z	<	vMax.z)vMax.z	=	b.vMax.z;
		return	*this;
	}

	Float3 BoundingBox::GetHalfSize()const
	{
		return	(vMax-vMin)*0.5f;
	}

	void BoundingBox::GetHalfSize( Float3& vOut )const
	{
		vOut	=	(vMax-vMin)*0.5f;
	}

	Float3 BoundingBox::GetCenter()const
	{
		return	(vMax+vMin)*0.5f;
	}

	void BoundingBox::GetCenter( Float3& vOut )const
	{
		vOut	=	(vMax+vMin)*0.5f;
	}

	Air::U1 BoundingBox::RayCast( const	Float3& vStart,const	Float3& vDir,float* pNearDistance,float* pFarDistance )const
	{
		Float3	fmin		=	vMin	-	vStart;
		Float3	fmax		=	vMax	-	vStart;
		Float3	invMinDir	=	fmin	/	vDir;
		Float3	invMaxDir	=	fmax	/	vDir;


		Float3	fNear		=	Float3(	min(invMinDir.x,invMaxDir.x),
										min(invMinDir.y,invMaxDir.y),
										min(invMinDir.z,invMaxDir.z));
		Float3	fFar		=	Float3(	max(invMinDir.x,invMaxDir.x),
										max(invMinDir.y,invMaxDir.y),
										max(invMinDir.z,invMaxDir.z));

		float	maxNear		=	max(fNear.x,fNear.y);
		maxNear				=	max(maxNear,fNear.z);
		float	minFar		=	min(fFar.x,fFar.y);
		minFar				=	min(minFar,fFar.z);
		if(	maxNear	>	minFar	||
			minFar	<	0.0f)
		{
			return	false;
		}
		if(maxNear	<	0.0f)
			maxNear	=	0.0f;
		if(pNearDistance!=NULL)
			*pNearDistance	=	maxNear;
		if(pFarDistance!=NULL)
			*pFarDistance	=	minFar;
		return	true;
	}

	Air::S32 BoundingBox::GetSide( float fPlane,enumPlaneType	pt )const
	{
		if(vMin[pt]	>=	fPlane)
			return	1;
		if(vMax[pt]	<=	fPlane)
			return	-1;
		return	0;
	}

	void BoundingBox::BuildFrom3Point( const Float3& v0,const Float3& v1,const Float3& v2 )
	{
		vMin	=	v0;
		vMax	=	v0;
		Add(v1);
		Add(v2);
	}

	Air::BoundingBox BoundingBox::Transform( const Common::Matrix& matrix )
	{
		BoundingBox	b;
		Float3	point[8]	=	{
			vMin,
			Float3(vMin.x,vMin.y,vMax.z),
			Float3(vMax.x,vMin.y,vMin.z),
			Float3(vMax.x,vMin.y,vMax.z),

			vMax,
			Float3(vMin.x,vMax.y,vMax.z),
			Float3(vMax.x,vMax.y,vMin.z),
			Float3(vMax.x,vMax.y,vMax.z),
		};
		for(int i=0;i<8;i++){
			point[i]	=	matrix*point[i];
		}
		b.vMin	=	point[0];
		b.vMax	=	point[1];
		for(int i=1;i<8;i++){
			b.Add(point[i]);
		}
		return	b;

	}

#define FLOAT_OFFSET	0.00001f
	Air::U1 BoundingBox::IsIncludeH( const Float3& v ) const
	{
		Float3	vTempMin	=	vMin	-	Float3(FLOAT_OFFSET,FLOAT_OFFSET,FLOAT_OFFSET);
		Float3	vTempMax	=	vMax	+	Float3(FLOAT_OFFSET,FLOAT_OFFSET,FLOAT_OFFSET);
		if(	v.x	<	vTempMin.x	||
			v.y	<	vTempMin.y	||
			v.z	<	vTempMin.z	||
			v.x	>	vTempMax.x	||
			v.y	>	vTempMax.y	||
			v.z	>	vTempMax.z)
		{
			return	false;
		}
		return	true;
	}

}