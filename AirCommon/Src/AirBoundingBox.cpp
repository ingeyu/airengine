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
		Float3	subMin	=	vMin	-	vStart;
		Float3	subMax	=	vMax	-	vStart;

		Float3	invMin	=	subMin/vDir;
		Float3	invMax	=	subMax/vDir;

		float	fNear	=	99999999.0f;
		float	fFar	=	0.0f;
		bool	bResult	=	false;

		if(invMin.x	>	0){
			Float3	v	=	vDir*invMin.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				if(invMin.x	<	fNear)
					fNear	=	invMin.x;
				if(invMin.x	>	fFar)
					fFar	=	invMin.x;
				bResult	=	true;
			}
		}
		if(invMin.y	>	0){
			Float3	v	=	vDir*invMin.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				if(invMin.y	<	fNear)
					fNear	=	invMin.y;
				if(invMin.y	>	fFar)
					fFar	=	invMin.y;
				bResult	=	true;
			}
		}
		if(invMin.z	>	0){
			Float3	v	=	vDir*invMin.z;
			if(	v.x	>=	subMin.x	&&	v.x	>=	subMin.x	&&
				v.x	<=	subMax.x	&&	v.x	<=	subMax.x)
			{
				if(invMin.z	<	fNear)
					fNear	=	invMin.z;
				if(invMin.z	>	fFar)
					fFar	=	invMin.z;
				bResult	=	true;
			}
		}
		if(invMax.x	>	0){
			Float3	v	=	vDir*invMax.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				if(invMax.x	<	fNear)
					fNear	=	invMax.x;
				if(invMax.x	>	fFar)
					fFar	=	invMax.x;
				bResult	=	true;
			}
		}
		if(invMax.y	>	0){
			Float3	v	=	vDir*invMax.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				if(invMax.y	<	fNear)
					fNear	=	invMax.y;
				if(invMax.y	>	fFar)
					fFar	=	invMax.y;
				bResult	=	true;
			}
		}
		if(invMax.z	>	0){
			Float3	v	=	vDir*invMax.z;
			if(	v.x	>=	subMin.x	&&	v.x	>=	subMin.x	&&
				v.x	<=	subMax.x	&&	v.x	<=	subMax.x)
			{
				if(invMax.z	<	fNear)
					fNear	=	invMax.z;
				if(invMax.z	>	fFar)
					fFar	=	invMax.z;
				bResult	=	true;
			}
		}

		if(bResult){
			if(pNearDistance!=NULL){
				*pNearDistance	=	fNear;
			}
			if(pFarDistance!=NULL){
				*pFarDistance	=	fFar;
			}
		}

		return	bResult;

		return	true;
	}

	Air::U1 BoundingBox::RayCast( const	Float3& vStart,const	Float3& vDir )const
	{
		Float3	subMin	=	vMin	-	vStart;
		Float3	subMax	=	vMax	-	vStart;

		Float3	invMin	=	subMin/vDir;
		Float3	invMax	=	subMax/vDir;

		if(invMin.x	>	0){
			Float3	v	=	vDir*invMin.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMin.y	>	0){
			Float3	v	=	vDir*invMin.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMin.z	>	0){
			Float3	v	=	vDir*invMin.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				return	true;
			}
		}
		if(invMax.x	>	0){
			Float3	v	=	vDir*invMax.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMax.y	>	0){
			Float3	v	=	vDir*invMax.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMax.z	>	0){
			Float3	v	=	vDir*invMax.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				return	true;
			}
		}

		return	false;
	}

	Air::U1 BoundingBox::RayCast( const Float3& vStart,const Float3& vDir,float fMaxDistance )const
	{
		Float3	subMin	=	vMin	-	vStart;
		Float3	subMax	=	vMax	-	vStart;

		Float3	invMin	=	subMin/vDir;
		Float3	invMax	=	subMax/vDir;

		if(invMin.x	>	0	&&	invMin.x	<	fMaxDistance){
			Float3	v	=	vDir*invMin.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMin.y	>	0	&&	invMin.y	<	fMaxDistance){
			Float3	v	=	vDir*invMin.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMin.z	>	0	&&	invMin.z	<	fMaxDistance){
			Float3	v	=	vDir*invMin.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				return	true;
			}
		}
		if(invMax.x	>	0	&&	invMax.x	<	fMaxDistance){
			Float3	v	=	vDir*invMax.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMax.y	>	0	&&	invMax.y	<	fMaxDistance){
			Float3	v	=	vDir*invMax.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				return	true;
			}
		}
		if(invMax.z	>	0	&&	invMax.z	<	fMaxDistance){
			Float3	v	=	vDir*invMax.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				return	true;
			}
		}

		return	false;
	}

	Air::U1 BoundingBox::RayCastNear( const Float3& vStart,const Float3& vDir,float* pNearDistance )const
	{
		Float3	subMin	=	vMin	-	vStart;
		Float3	subMax	=	vMax	-	vStart;

		Float3	invMin	=	subMin/vDir;
		Float3	invMax	=	subMax/vDir;

		float	fNear	=	99999999.0f;
		bool	bResult	=	false;

		if(invMin.x	>	0	&&	invMin.x	<	fNear){
			Float3	v	=	vDir*invMin.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				fNear	=	invMin.x;
				bResult	=	true;
			}
		}
		if(invMin.y	>	0	&&	invMin.y	<	fNear){
			Float3	v	=	vDir*invMin.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				fNear	=	invMin.y;
				bResult	=	true;
			}
		}
		if(invMin.z	>	0	&&	invMin.z	<	fNear){
			Float3	v	=	vDir*invMin.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				fNear	=	invMin.z;
				bResult	=	true;
			}
		}
		if(invMax.x	>	0	&&	invMax.x	<	fNear){
			Float3	v	=	vDir*invMax.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				fNear	=	invMax.x;
				bResult	=	true;
			}
		}
		if(invMax.y	>	0	&&	invMax.y	<	fNear){
			Float3	v	=	vDir*invMax.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				fNear	=	invMax.y;

				bResult	=	true;
			}
		}
		if(invMax.z	>	0	&&	invMax.z	<	fNear){
			Float3	v	=	vDir*invMax.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				fNear	=	invMax.z;
				bResult	=	true;
			}
		}

		return	false;
	}
	Air::U1 BoundingBox::RayCastFar( const Float3& vStart,const Float3& vDir,float* pFarDistance )const
	{
		Float3	subMin	=	vMin	-	vStart;
		Float3	subMax	=	vMax	-	vStart;

		Float3	invMin	=	subMin/vDir;
		Float3	invMax	=	subMax/vDir;

		float	fFar	=	0.0f;
		bool	bResult	=	false;

		if(invMin.x	>	0	&&	invMin.x	>	fFar){
			Float3	v	=	vDir*invMin.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				fFar	=	invMin.x;
				bResult	=	true;
			}
		}
		if(invMin.y	>	0	&&	invMin.y	>	fFar){
			Float3	v	=	vDir*invMin.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				fFar	=	invMin.y;
				bResult	=	true;
			}
		}
		if(invMin.z	>	0	&&	invMin.z	>	fFar){
			Float3	v	=	vDir*invMin.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				fFar	=	invMin.z;
				bResult	=	true;
			}
		}
		if(invMax.x	>	0	&&	invMax.x	>	fFar){
			Float3	v	=	vDir*invMax.x;
			if(	v.y	>=	subMin.y	&&	v.z	>=	subMin.z	&&
				v.y	<=	subMax.y	&&	v.z	<=	subMax.z)
			{
				fFar	=	invMax.x;
				bResult	=	true;
			}
		}
		if(invMax.y	>	0	&&	invMax.y	>	fFar){
			Float3	v	=	vDir*invMax.y;
			if(	v.x	>=	subMin.x	&&	v.z	>=	subMin.z	&&
				v.x	<=	subMax.x	&&	v.z	<=	subMax.z)
			{
				fFar	=	invMax.y;

				bResult	=	true;
			}
		}
		if(invMax.z	>	0	&&	invMax.z	>	fFar){
			Float3	v	=	vDir*invMax.z;
			if(	v.x	>=	subMin.x	&&	v.y	>=	subMin.y	&&
				v.x	<=	subMax.x	&&	v.y	<=	subMax.y)
			{
				fFar	=	invMax.z;
				bResult	=	true;
			}
		}

		return	false;
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

}