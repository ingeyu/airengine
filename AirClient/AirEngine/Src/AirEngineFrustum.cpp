#include "AirEngineFrustum.h"
#include "AirCommonPlane.h"
#include "AirEngineSceneNode.h"

namespace	Air{
	namespace	Engine{
#define ANG2RAD 3.14159265358979323846/180.0

		Frustum::Frustum(){
			m_vPosition		=	Float3(0,0,0);
			m_vUp			=	Float3(0,1,0);
			m_vDirection	=	Float3(0,0,-1);

			m_fAngle		=	XM_PI*0.25;
			m_fAspect		=	1280.0f/720.0f;

			m_fNear	=	1.0f;
			m_fFar	=	1000.0f;

			m_bOrtho		=	false;

			m_matView.ViewTL(m_vPosition,m_vDirection,m_vUp);
			m_matProj.ProjectFL(m_fAngle,m_fAspect,m_fNear,m_fFar);

			m_bDirty		=	true;

		}

		void Frustum::SetPosition( const Float3& position ){
			m_vPosition	=	position;
			m_bDirty	=	true;
		}

		void Frustum::SetPosition( Real x,Real y,Real z ){
			m_vPosition.x	=	x;
			m_vPosition.y	=	y;
			m_vPosition.z	=	z;
			m_bDirty	=	true;
		}

		Air::Float3 Frustum::GetPosition(){
			return	m_vPosition;
		}

		void Frustum::SetUpDir( const Float3& up ){
			m_vUp	=	up;
			m_bDirty	=	true;
		}

		void Frustum::SetUpDir( Real x,Real y,Real z ){
			m_vUp.x	=	x;
			m_vUp.y	=	y;
			m_vUp.z	=	z;
			m_bDirty	=	true;
		}

		Air::Float3 Frustum::GetUpDir(){
			return	m_vUp;
		}

		void Frustum::SetDir( const Float3& dir ){
			m_vDirection	=	dir.NormalizeCopy();
			m_bDirty	=	true;
		}

		void Frustum::SetDir( Real x,Real y,Real z ){
			m_vDirection.x	=	x;
			m_vDirection.y	=	y;
			m_vDirection.z	=	z;
			m_bDirty	=	true;
		}

		Air::Float3 Frustum::GetDir(){
			return	m_vDirection;
		}

		void Frustum::SetNear( Real fNear ){
			m_fNear	=	fNear;
			m_bDirty	=	true;
		}

		Air::Real Frustum::GetNear(){
			return	m_fNear;
		}		

		void Frustum::SetFar( Real fFar ){
			m_fFar	=	fFar;
			m_bDirty	=	true;
		}

		Air::Real Frustum::GetFar(){
			return	m_fFar;
		}

		void Frustum::SetNearFar( Real fNear,Real fFar ){
			m_fNear	=	fNear;
			m_fFar	=	fFar;
			m_bDirty	=	true;
		}

		void Frustum::SetAngle( Real fAngle ){
			m_fAngle	=	fAngle;
			m_bDirty	=	true;
		}

		void Frustum::SetAspect( Real fAspect ){
			m_fAspect	=	fAspect;
			m_bDirty	=	true;
		}

		const	Matrix& Frustum::GetViewMatrix(){
			if(m_bDirty){
				ReBuild();
			}
			return	m_matView;
		}

		void Frustum::GetViewMatrix( Matrix& mat ){
			if(m_bDirty){
				ReBuild();
			}
			mat	=	m_matView;
		}
		const	Matrix& Frustum::GetProjMatrix(){
			if(m_bDirty){
				ReBuild();
			}
			return	m_matProj;
		}

		void Frustum::GetProjMatrix( Matrix& mat ){
			if(m_bDirty){
				ReBuild();
			}
			mat	=	m_matProj;
		}
		const	Matrix& Frustum::GetViewProjMatrix(){
			if(m_bDirty){
				ReBuild();
			}
			return	m_matViewProj;
		}

		void Frustum::GetViewProjMatrix( Matrix& matVP ){
			if(m_bDirty){
				ReBuild();
			}
			matVP	=	m_matViewProj;
		}

		void Frustum::GetViewProjMatrix( Matrix& matView,Matrix& matProj ){
			if(m_bDirty){
				ReBuild();
			}
			matView	=	m_matView;
			matProj	=	m_matProj;
		}

		Air::U1 Frustum::IsVisiable( const Float3& point ){
			if(m_vecPlane[enFS_Near].GetSide(point)		==	enPS_Negative)
				return	false;	
			if(m_vecPlane[enFS_Left].GetSide(point)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Right].GetSide(point)	==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Top].GetSide(point)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Bottom].GetSide(point)	==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Far].GetSide(point)		==	enPS_Negative)
				return	false;
			return	true;
		}

		Air::U1 Frustum::IsVisiable( const Float3& point0,const Float3& point1,const Float3& point2 ){
			if(m_vecPlane[enFS_Near].GetSide(point0,point1,point2)		==	enPS_Negative)
				return	false;	
			if(m_vecPlane[enFS_Left].GetSide(point0,point1,point2)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Right].GetSide(point0,point1,point2)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Top].GetSide(point0,point1,point2)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Bottom].GetSide(point0,point1,point2)	==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Far].GetSide(point0,point1,point2)		==	enPS_Negative)
				return	false;
			return	true;
		}

		Air::U1 Frustum::IsVisiable( const Sphere& sphere ){
			if(m_vecPlane[enFS_Near].GetSide((const Float3)sphere.Center,sphere.Radius)		==	enPS_Negative)
				return	false;	
			if(m_vecPlane[enFS_Left].GetSide((const Float3)sphere.Center,sphere.Radius)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Right].GetSide((const Float3)sphere.Center,sphere.Radius)	==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Top].GetSide((const Float3)sphere.Center,sphere.Radius)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Bottom].GetSide((const Float3)sphere.Center,sphere.Radius)	==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Far].GetSide((const Float3)sphere.Center,sphere.Radius)		==	enPS_Negative)
				return	false;
			return	true;
		}

		Air::U1 Frustum::IsVisiable( const AxisAlignedBox& box ){
			Float3	v[8];
			Float3	vCenter(box.Center);
			Float3	vExtents(box.Extents);
			v[0]	=	vCenter	+	Float3(-1,-1,1)*vExtents;
			v[1]	=	vCenter	+	Float3(1,-1,-1)*vExtents;
			v[2]	=	vCenter	+	Float3(1,-1,1)*vExtents;
			v[3]	=	vCenter	+	Float3(-1,-1,-1)*vExtents;

			v[4]	=	vCenter	+	Float3(-1,1,1)*vExtents;
			v[5]	=	vCenter	+	Float3(1,1,-1)*vExtents;
			v[6]	=	vCenter	+	Float3(1,1,1)*vExtents;
			v[7]	=	vCenter	+	Float3(-1,1,-1)*vExtents;

			if(m_vecPlane[enFS_Near].GetSide(v,8)		==	enPS_Negative)
				return	false;	
			if(m_vecPlane[enFS_Left].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Right].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Top].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Bottom].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Far].GetSide(v,8)		==	enPS_Negative)
				return	false;
			return	true;
		};

		Air::U1 Frustum::IsVisiable( const OrientedBox& box ){
			Float3	v[8];
			Float3	vCenter(box.Center);
			Float3	vExtents(box.Extents);
			v[0]	=	vCenter	+	Float3(-1,-1,1)*vExtents;
			v[1]	=	vCenter	+	Float3(1,-1,-1)*vExtents;
			v[2]	=	vCenter	+	Float3(1,-1,1)*vExtents;
			v[3]	=	vCenter	+	Float3(-1,-1,-1)*vExtents;

			v[4]	=	vCenter	+	Float3(-1,1,1)*vExtents;
			v[5]	=	vCenter	+	Float3(1,1,-1)*vExtents;
			v[6]	=	vCenter	+	Float3(1,1,1)*vExtents;
			v[7]	=	vCenter	+	Float3(-1,1,-1)*vExtents;

			//旋转8个顶点
			Float4	q(box.Orientation);
			for(U32	i=0;i<8;i++){
				v[i]	=	q*v[i];
			}
			if(m_vecPlane[enFS_Near].GetSide(v,8)		==	enPS_Negative)
				return	false;	
			if(m_vecPlane[enFS_Left].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Right].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Top].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Bottom].GetSide(v,8)		==	enPS_Negative)
				return	false;
			if(m_vecPlane[enFS_Far].GetSide(v,8)		==	enPS_Negative)
				return	false;
			return	true;
		}

		Air::U1 Frustum::IsVisiable( const BoundingBox& box )
		{
			Float3	vCenter	=	(box.vMin	+	box.vMax)*0.5f;
			Float3	vSize	=	(box.vMax	-	box.vMin)*0.5f;
			AxisAlignedBox	b;
			memcpy(&b.Center,&vCenter,sizeof(Float3));
			memcpy(&b.Extents,&vSize,sizeof(Float3));
			return	IsVisiable(b);
		}

		void Frustum::BuildPlane(){


			Float3 dir,nc,fc,X,Y,Z;

			Z = Float3(-m_vDirection.x,-m_vDirection.y,-m_vDirection.z);
			Z.Normalize();

			X = m_vUp.Cross(Z);
			X.Normalize();

			Y = Z.Cross(X);

			nc = m_vPosition - Z * m_fNear;
			fc = m_vPosition - Z * m_fFar;

			Float3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
			float nw,nh,fw,fh;

			float	tang = (float)tan(m_fAngle * 0.5f) ;
			nh = m_fNear * tang;
			nw = nh * m_fAspect; 
			fh = m_fFar  * tang;
			fw = fh * m_fAspect;

			ntl = nc + Y * nh - X * nw;
			ntr = nc + Y * nh + X * nw;
			nbl = nc - Y * nh - X * nw;
			nbr = nc - Y * nh + X * nw;

			ftl = fc + Y * fh - X * fw;
			ftr = fc + Y * fh + X * fw;
			fbl = fc - Y * fh - X * fw;
			fbr = fc - Y * fh + X * fw;

			m_vecPlane[enFS_Top].SetVertex(ntr,ntl,ftl);
			m_vecPlane[enFS_Bottom].SetVertex(nbl,nbr,fbr);
			m_vecPlane[enFS_Left].SetVertex(ntl,nbl,fbl);
			m_vecPlane[enFS_Right].SetVertex(nbr,ntr,fbr);
			m_vecPlane[enFS_Near].SetVertex(ntl,ntr,nbr);
			m_vecPlane[enFS_Far].SetVertex(ftr,ftl,fbl);
		}

		void Frustum::Update(	const	Float44&	ParentGlobalWorldMatrix,
								const	Float4&		ParentGlobalWorldQuat,
								const	Float3&		ParentGlobalWorldScale,
								U1					bParentDirty )
		{
			__super::Update(ParentGlobalWorldMatrix,ParentGlobalWorldQuat,ParentGlobalWorldScale,bParentDirty);
			if(bParentDirty)
				m_bDirty	=	true;
			ReBuild();

		}

		void Frustum::BuildPlaneFromViewProj(){
			Matrix& combo = m_matViewProj;
			m_matViewProj	=	m_matView *	m_matProj;

			m_vecPlane[enFS_Left].m_vNormal.x = combo[3][0] + combo[0][0];
			m_vecPlane[enFS_Left].m_vNormal.y = combo[3][1] + combo[0][1];
			m_vecPlane[enFS_Left].m_vNormal.z = combo[3][2] + combo[0][2];
			m_vecPlane[enFS_Left].m_fDistance = combo[3][3] + combo[0][3];

			m_vecPlane[enFS_Right].m_vNormal.x = combo[3][0] - combo[0][0];
			m_vecPlane[enFS_Right].m_vNormal.y = combo[3][1] - combo[0][1];
			m_vecPlane[enFS_Right].m_vNormal.z = combo[3][2] - combo[0][2];
			m_vecPlane[enFS_Right].m_fDistance = combo[3][3] - combo[0][3];

			m_vecPlane[enFS_Top].m_vNormal.x = combo[3][0] - combo[1][0];
			m_vecPlane[enFS_Top].m_vNormal.y = combo[3][1] - combo[1][1];
			m_vecPlane[enFS_Top].m_vNormal.z = combo[3][2] - combo[1][2];
			m_vecPlane[enFS_Top].m_fDistance = combo[3][3] - combo[1][3];

			m_vecPlane[enFS_Bottom].m_vNormal.x = combo[3][0] + combo[1][0];
			m_vecPlane[enFS_Bottom].m_vNormal.y = combo[3][1] + combo[1][1];
			m_vecPlane[enFS_Bottom].m_vNormal.z = combo[3][2] + combo[1][2];
			m_vecPlane[enFS_Bottom].m_fDistance = combo[3][3] + combo[1][3];

			
			m_vecPlane[enFS_Far].m_vNormal.x = combo[3][0] - combo[2][0];
			m_vecPlane[enFS_Far].m_vNormal.y = combo[3][1] - combo[2][1];
			m_vecPlane[enFS_Far].m_vNormal.z = combo[3][2] - combo[2][2];
			m_vecPlane[enFS_Far].m_fDistance = combo[3][3] - combo[2][3];
		

		
			m_vecPlane[enFS_Near].m_vNormal.x = combo[3][0] + combo[2][0];
			m_vecPlane[enFS_Near].m_vNormal.y = combo[3][1] + combo[2][1];
			m_vecPlane[enFS_Near].m_vNormal.z = combo[3][2] + combo[2][2];
			m_vecPlane[enFS_Near].m_fDistance = combo[3][3] + combo[2][3];
			



			// Renormalise any normals which were not unit length
			for(U32 i=0; i<6; i++ ) 
			{
				//mFrustumPlanes[i].normal	=	-mFrustumPlanes[i].normal;
				Real length = m_vecPlane[i].m_vNormal.Length();
				m_vecPlane[i].m_vNormal.Normalize();
				m_vecPlane[i].m_fDistance /= length;
			}
		}

		void Frustum::ReBuild(){

			Float3	vPos	=	GetRealPosition();
			Float3	vDir	=	GetRealDirection().Normalize();
			Float3	vUpDir	=	GetRealUpDirection().Normalize();

			m_matView.ViewTL(vPos,vDir,vUpDir);
			if(!m_bOrtho)
				m_matProj.ProjectFL(m_fAngle,m_fAspect,m_fNear,m_fFar);
			else
				m_matProj.OrthographicL(m_fWidth,m_fWidth/m_fAspect,m_fNear,m_fFar);

			m_matViewProj	=	m_matView*m_matProj;
			
			BuildPlaneFromViewProj();

			m_bDirty	=	false;
		}

		Air::Ray Frustum::BuildRay( Real x,Real y )
		{
#if 0
			POINT point;

			point.x	=	x;
			point.y	=	y;


			Common::Matrix mInverseView	=	m_matView;
			mInverseView.Inverse();

			// Compute the vector of the pick ray in screen space
			Float3 v;
			v.x = ( ( ( 2.0f * point.x ) / m_iScreenWidth ) - 1 ) /m_matProj.m00;
			v.y = -( ( ( 2.0f * point.y ) / m_iScreenHeight ) - 1 ) /m_matProj.m11;
			//如果是右手坐标系 Z必须为-1 左手坐标系为1 切需注意
			v.z = 1;//-m_ShaderParam.m_matProj[3][2];

			Ray ray;

			// Transform the screen space pick ray into 3D space
			ray.m_vDirection.x = v.x * mInverseView.m00 + v.y * mInverseView.m10 + v.z * mInverseView.m20;
			ray.m_vDirection.y = v.x * mInverseView.m01 + v.y * mInverseView.m11 + v.z * mInverseView.m21;
			ray.m_vDirection.z = v.x * mInverseView.m02 + v.y * mInverseView.m12 + v.z * mInverseView.m22;
			// 	 		//origin	=	m_vCurrentPosition;
			ray.m_vStart	=	Float3(mInverseView.m30,mInverseView.m31,mInverseView.m32);
			//Ray ray;
			ray.m_vDirection.Normalize();

			return	ray;
#else
			Matrix inverseVP = m_matViewProj;
			inverseVP.Inverse();

			Real nx = (2.0f * x) - 1.0f;
			Real ny = 1.0f - (2.0f * y);
			// Use midPoint rather than far point to avoid issues with infinite projection
			Float3 midPoint (nx, ny,  0.0f);

			// Get ray origin and ray target on near plane in world space
			Float3 rayTarget;


			rayTarget = inverseVP * midPoint;

			Float3 rayDirection = rayTarget - GetPosition();
			rayDirection.Normalize();

			return	Ray(GetPosition(),rayDirection);
#endif
			
		}

		void Frustum::SetWidth( Real fWidth )
		{
			m_fWidth	=	fWidth;
			m_bDirty	=	true;
		}

		void Frustum::SetHeight( Real fHeight )
		{
			m_fHeight	=	fHeight;
			m_bDirty	=	true;
		}

		void Frustum::SetOrtho( U1 bOrtho )
		{
			m_bOrtho	=	bOrtho;
			m_bDirty	=	true;
		}

		Float3 Frustum::GetRealDirection(){
			if(m_pParentNode!=NULL){
				Float3& vPos	=	m_WorldMatrix.GetPosition();
				return	(m_WorldMatrix*(vPos+m_vDirection)	-	vPos).Normalize();
			}
			else
			{
				return	m_vDirection;
			}
		}

		Float3 Frustum::GetRealPosition(){
			if(m_pParentNode!=NULL){
				return	m_WorldMatrix.GetPosition();
			}
			else
			{
				return	m_vPosition;
			}
		}

		Float3 Frustum::GetRealRightDirection(){
			if(m_pParentNode!=NULL){
				Float3& vPos	=	m_WorldMatrix.GetPosition();
				Float3& vRealUp	=	(m_WorldMatrix*(vPos+m_vUp)	-	vPos).Normalize();
				return	vRealUp.Cross(GetRealDirection());
			}
			else
			{
				return	m_vUp.Cross(GetRealDirection());
			}
		}

		Float3 Frustum::GetRealUpDirection(){
			return	GetRealDirection().Cross(GetRealRightDirection());
		};

		Air::Real Frustum::GetWidth()const
		{
			return m_fWidth;
		}


	}
}