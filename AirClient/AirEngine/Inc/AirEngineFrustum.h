/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/18
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  AirEngineFrustum.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRENGINEFRUSTUM_HEAD_FILE
#define AIRENGINEFRUSTUM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"

namespace	Air{
	namespace Engine{
		enum enumFrustumSide
		{
			enFS_Left,
			enFS_Right,
			enFS_Top,
			enFS_Bottom,
			enFS_Far,
			enFS_Near
		};
		class	ENGINE_EXPORT	Frustum	:	
			public	MovableObject{
		public:
			Frustum();

			void	SetPosition(const	Float3&	position);
			void	SetPosition(Real	x,Real	y,Real	z);
			Float3	GetPosition();
			void	SetUpDir(const		Float3&	up);
			void	SetUpDir(Real	x,Real	y,Real	z);
			Float3	GetUpDir();
			void	SetDir(const		Float3&	dir);
			void	SetDir(Real	x,Real	y,Real	z);
			Float3	GetDir();

			void	SetNear(Real	fNear);
			Real	GetNear();
			void	SetFar(Real		fFar);
			Real	GetFar();
			void	SetNearFar(Real	fNear,Real	fFar);
			void	SetAngle(Real	fAngle);
			void	SetAspect(Real	fAspect);
			void	SetWidth(Real	fWidth);
			void	SetHeight(Real	fHeight);
			void	SetOrtho(U1		bOrtho);

			const	Matrix&	GetViewMatrix();
			void	GetViewMatrix(Matrix&	mat);
			const	Matrix&	GetProjMatrix();
			void	GetProjMatrix(Matrix&	mat);
			const	Matrix&	GetViewProjMatrix();
			void	GetViewProjMatrix(Matrix&	matVP);
			void	GetViewProjMatrix(Matrix&	matView,Matrix&	matProj);


			U1	IsVisiable(const	Float3&	point);
			U1	IsVisiable(const	Float3&	point0,const	Float3&	point1,const	Float3&	point2);
			U1	IsVisiable(const	Sphere&	sphere);
			U1	IsVisiable(const	AxisAlignedBox&	box);
			U1	IsVisiable(const	OrientedBox&	box);
			U1	IsVisiable(const	BoundingBox&	box);

			virtual	void	Update(	const	Float44&	ParentGlobalWorldMatrix,
									const	Float4&		ParentGlobalWorldQuat,
									const	Float3&		ParentGlobalWorldScale,
									U1					bParentDirty);

			Ray		BuildRay(Real	x,Real	y);
		protected:
			void	BuildPlane();
			void	BuildPlaneFromViewProj();
			void	ReBuild();
		protected:
			Plane			m_vecPlane[6];
			Matrix			m_matView;
			Matrix			m_matProj;
			Matrix			m_matViewProj;
			Float3			m_vPosition;
			Float3			m_vDirection;
			Float3			m_vUp;
			union{
			Real			m_fAngle;
			Real			m_fWidth;
			};
			union{
			Real			m_fAspect;
			Real			m_fHeight;
			};
			Real			m_fNear;
			Real			m_fFar;

			U1				m_bDirty;
			U1				m_bOrtho;			///<	是否为正交
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRENGINEFRUSTUM_HEAD_FILE