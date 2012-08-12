/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/05
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonMatrix.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONMATRIX_HEAD_FILE
#define COMMONMATRIX_HEAD_FILE

#include "xnamath.h"
#include "AirCommonQuaternion.h"
#include "AirCommonMemory.h"

namespace	Air{
	namespace Common{
		class	Matrix{
		public:
			inline	Matrix(){
				m00	=	1.0f;	m01	=	0.0f;	m02	=	0.0f;	m03	=	0.0f;
				m10	=	0.0f;	m11	=	1.0f;	m12	=	0.0f;	m13	=	0.0f;
				m20	=	0.0f;	m21	=	0.0f;	m22	=	1.0f;	m23	=	0.0f;
				m30	=	0.0f;	m31	=	0.0f;	m32	=	0.0f;	m33	=	1.0f;
			};
			inline	Matrix(	float f00,float f01,float f02,float f03,
							float f10,float f11,float f12,float f13,
							float f20,float f21,float f22,float f23,
							float f30,float f31,float f32,float f33)
			{
				m00	=	f00;	m01	=	f01;	m02	=	f02;	m03	=	f03;
				m10	=	f10;	m11	=	f11;	m12	=	f12;	m13	=	f13;
				m20	=	f20;	m21	=	f21;	m22	=	f22;	m23	=	f23;
				m30	=	f30;	m31	=	f31;	m32	=	f32;	m33	=	f33;
			};
// 			inline	Matrix(	float f11,float f12,float f13,float f14,
// 							float f21,float f22,float f23,float f24,
// 							float f31,float f32,float f33,float f34,
// 							float f41,float f42,float f43,float f44)
// 			{
// 				_11	=	f11;	_12	=	f12;	_13	=	f13;	_14	=	f14;
// 				_21	=	f21;	_22	=	f22;	_23	=	f23;	_24	=	f24;
// 				_31	=	f31;	_32	=	f32;	_33	=	f33;	_34	=	f34;
// 				_41	=	f41;	_42	=	f42;	_43	=	f43;	_44	=	f44;
// 				
// 			};
			inline	Matrix(const	Quaternion&	q){
				*this	=	XMMatrixRotationQuaternion(XMLoadFloat4((XMFLOAT4*)&q));
			};
			inline	Matrix(Vector3&	position){
				*this	=	XMMatrixTranslation(position.x,position.y,position.z);
			};
			inline	Matrix(Vector3&	position,Vector3& scale,Quaternion& q){
				*this	=	XMMatrixAffineTransformation(	scale.ToXM(),
															g_XMZero,
															q.ToXM(),
															position.ToXM());
			};
			inline	Matrix(const Matrix&	mat){
				Memcpy4(_m,&mat,sizeof(Matrix));
			};
			inline	Matrix(CXMMATRIX&	mat){
				Memcpy4(_m,&mat,sizeof(Matrix));
			};
			inline	Matrix&	operator	=	(CXMMATRIX	mat){
				Memcpy4(_m,&mat,sizeof(Matrix));
				return	*this;
			};
			inline	Matrix&	operator	=	(const	Matrix&	mat){
				Memcpy4(_m,&mat,sizeof(Matrix));
				return	*this;
			};
			inline	Matrix	operator	*	(const	Matrix&	mat)const{
				return	XMMatrixMultiply(ToXM(),XMLoadFloat4x4((XMFLOAT4X4*)&mat));
			};
			inline	Matrix&	operator	*=	(const	Matrix&	mat){
				*this	=	XMMatrixMultiply(ToXM(),XMLoadFloat4x4((XMFLOAT4X4*)&mat));
				return	*this;
			};
			inline	Vector3	operator	*	(const	Vector3&	v)const{
				XMVECTOR	vv	=	XMVector3TransformCoord(XMLoadFloat3((XMFLOAT3*)&v),ToXM());
				return	vv;
			};
			inline	bool	operator	==	(const	Matrix&		mat){
				return	Memcmp4(_m,&mat,sizeof(Matrix));
			};
			inline	bool	operator	!=	(const	Matrix&		mat){
				return	!Memcmp4(_m,&mat,sizeof(Matrix));
			};
			inline	Matrix&	Inverse(){
				XMVECTOR	v;
				*this	=	XMMatrixInverse(&v,ToXM());
				return	*this;
			};
			inline	Matrix&	Transpose(){
				*this	=	XMMatrixTranspose(ToXM());
				return	*this;
			};
			inline	void	Decompose(Vector3*	vPosition,Vector3* vScale,Quaternion*	q){
				XMVECTOR	xp,xs,xq;
				XMMatrixDecompose(&xs,&xq,&xp,ToXM());
				if(vPosition!=NULL)
					*vPosition=xp;
				if(vScale!=NULL)
					*vScale=xs;
				if(q!=NULL)
					*q=xq;
			};
			inline	Vector3	GetPosition()const{
				return	Vector3(m30,m31,m32);
			};
			inline	Matrix&	ViewAL(	Vector3&	eyePosition,
									Vector3&	lookPosition,
									Vector3&	upDirection){
				*this	=	XMMatrixLookAtLH(	eyePosition.ToXM(),
												lookPosition.ToXM(),
												upDirection.ToXM());
				return	*this;
			};
			inline	Matrix&	ViewAR(	Vector3&	eyePosition,
									Vector3&	lookPosition,
									Vector3&	upDirection){
				*this	=	XMMatrixLookAtRH(	eyePosition.ToXM(),
												lookPosition.ToXM(),
												upDirection.ToXM());
				return	*this;
			};
			inline	Matrix&	ViewTL(	Vector3&	eyePosition,
									Vector3&	viewDirection,
									Vector3&	upDirection){
				*this	=	XMMatrixLookToLH(	eyePosition.ToXM(),
												viewDirection.ToXM(),
												upDirection.ToXM());
				return	*this;
			};
			inline	Matrix&	ViewTR(	Vector3&	eyePosition,
									Vector3&	viewDirection,
									Vector3&	upDirection){
				*this	=	XMMatrixLookToRH(	eyePosition.ToXM(),
												viewDirection.ToXM(),
												upDirection.ToXM());
				return	*this;
			};	
			inline	Matrix&	ProjectL(	float ViewWidth,
										float ViewHeight,
										float NearZ,
										float FarZ){
				*this	=	XMMatrixPerspectiveLH(	ViewWidth,
												ViewHeight,
												NearZ,
												FarZ);
				return	*this;
			};
			inline	Matrix&	PeojectR(	float ViewWidth,
										float ViewHeight,
										float NearZ,
										float FarZ){
				*this	=	XMMatrixPerspectiveRH(	ViewWidth,
												ViewHeight,
												NearZ,
												FarZ);
				return	*this;
			};
			inline	Matrix&	ProjectFL(	float FovAngleY,
										float AspectRatio,
										float NearZ,
										float FarZ){
				*this	=	XMMatrixPerspectiveFovLH(	FovAngleY,
													AspectRatio,
													NearZ,
													FarZ);
				return	*this;
			};
			inline	Matrix&	ProjectFR(	float FovAngleY,
										float AspectRatio,
										float NearZ,
										float FarZ){
				*this	=	XMMatrixPerspectiveFovRH(	FovAngleY,
													AspectRatio,
													NearZ,
													FarZ);
				return	*this;
			};
			inline	Matrix&	OrthographicL(	float ViewWidth,
											float ViewHeight,
											float NearZ,
											float FarZ){
				*this	=	XMMatrixOrthographicLH(	ViewWidth,
												ViewHeight,
												NearZ,
												FarZ);
				return	*this;
			};
			inline	Matrix&	OrthographicR(	float ViewWidth,
											float ViewHeight,
											float NearZ,
											float FarZ){
				*this	=	XMMatrixOrthographicRH(	ViewWidth,
												ViewHeight,
												NearZ,
												FarZ);
				return	*this;
			};
			inline	static	Matrix	Reflect(Vector3&	normal,float f){
				XMVECTOR	v(normal.ToXM());
				v.m128_f32[3]	=	f;
				return	XMMatrixReflect(v);
			};
			inline	XMMATRIX	ToXM()const{
				return	XMLoadFloat4x4((XMFLOAT4X4*)_m);
			};
	
			inline float* operator[] (unsigned long iRow) const
			{
				return (float*)m[iRow];
			};

			union{
				struct{
					float	m[4][4];
				};
				struct{
					float	_m[16];
				};
				struct{
					float	m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33;
				};
				struct{
					float	_11,_12,_13,_14,_21,_22,_23,_24,_31,_32,_33,_34,_41,_42,_43,_44;
				};
			};
		};
		
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONMATRIX_HEAD_FILE