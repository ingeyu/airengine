/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/04
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonQuaternion.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONQUATERNION_HEAD_FILE
#define COMMONQUATERNION_HEAD_FILE


#include "AirCommonVector3.h"

namespace	Air{
	namespace Common{
	

		class	Quaternion{
		public:
			inline	XMVECTOR	ToXM()const{
				return	XMLoadFloat4((XMFLOAT4*)&x);
			};
			inline	Quaternion():x(0.0f),y(0.0f),z(0.0f),w(0.0f){

			};
			inline	Quaternion(float	fx,float fy,float fz,float fw):x(fx),y(fy),z(fz),w(fw){

			};
			inline	Quaternion(const	Quaternion&	q):x(q.x),y(q.y),z(q.z),w(q.w){

			};
			inline	Quaternion(const	XMFLOAT4&	q):x(q.x),y(q.y),z(q.z),w(q.w){

			};
			inline	Quaternion(const	Vector3&	v):x(v.x),y(v.y),z(v.z),w(1.0f){

			}
			inline	Quaternion(CXMVECTOR	q){
				XMStoreFloat4((XMFLOAT4*)&x,q);
			};
			inline	Quaternion(const	Vector3&	v,float	fAngle){
				*this	=	XMQuaternionRotationAxis(v.ToXM(),fAngle);
			};
			inline	Quaternion(CXMMATRIX	m){
				*this	=	XMQuaternionRotationMatrix(m);
			};
			template<typename T_Quaternion>
			Quaternion(const T_Quaternion& v){
				U32	uiSize	=	min(sizeof(T_Quaternion),sizeof(Quaternion));
				memcpy(&x,&v,uiSize);
			};
			template<typename T_Quaternion>
			Quaternion	operator	=	(const T_Quaternion& v){
				U32	uiSize	=	min(sizeof(T_Quaternion),sizeof(Quaternion));
				memcpy(&x,&v,uiSize);
				return	*this;
			};

			inline	const Quaternion&		operator	=	(const	Quaternion&	q){
				x	=	q.x;
				y	=	q.y;
				z	=	q.z;
				w	=	q.w;
				return	*this;
			};
			inline	const Quaternion&		operator	=	(const	Vector3&	v){
				x	=	v.x;
				y	=	v.y;
				z	=	v.z;
				w	=	1.0f;
				return	*this;
			}
			inline	const Quaternion&		operator	=	(CXMVECTOR	q){
				XMStoreFloat4((XMFLOAT4*)&x,q);
				return	*this;
			};
			inline bool operator	== (const Quaternion& q) const
			{
				return	(q.x == x) && 
						(q.y == y) &&
						(q.z == z) && 
						(q.w == w);
			};
			inline bool operator	!= (const Quaternion& q) const
			{
				return	(q.x != x) && 
						(q.y != y) &&
						(q.z != z) && 
						(q.w != w);
			};
			inline	Quaternion		operator	+	(const	Quaternion&	q)const{
				return Quaternion(x+q.x,y+q.y,z+q.z,w+q.w);
			};
			inline	Quaternion		operator	-	(const Quaternion& q)const{
				return Quaternion(x-q.x,y-q.y,z-q.z,w-q.w);
			};
			inline	Quaternion		operator	-	()const{
				return	Quaternion(-x,-y,-z,-w);
			};
			inline	Quaternion		operator	*	(const	Quaternion&	q)const{
				return	XMQuaternionMultiply(ToXM(),q.ToXM());
			};
			inline	Quaternion		operator	*	(Quaternion&	q)const{
				return	XMQuaternionMultiply(ToXM(),q.ToXM());
			};
			inline	const Quaternion&		operator	*=	(const	Quaternion&	q){
				*this	=	XMQuaternionMultiply(ToXM(),q.ToXM());
				return	*this;
			};
			inline	const Quaternion&		operator	*=	(float f){
				x	*=	f;
				y	*=	f;
				z	*=	f;
				w	*=	f;
				return	*this;
			};
			inline	const Quaternion&		operator	/=	(float f){
				x	/=	f;
				y	/=	f;
				z	/=	f;
				w	/=	f;
				return	*this;
			};
			inline	const Quaternion&		operator	+=	(const	Quaternion&	q){
				x	+=	q.x;
				y	+=	q.y;
				z	+=	q.z;
				w	+=	q.w;
				return	*this;
			};
			inline	const Quaternion&		operator	+=	(float f){
				x	+=	f;
				y	+=	f;
				z	+=	f;
				w	+=	f;
				return	*this;
			};
			inline	const Quaternion&		operator	-=	(const	Quaternion&	q){
				x	-=	q.x;
				y	-=	q.y;
				z	-=	q.z;
				w	-=	q.w;
				return	*this;
			};
			inline	const Quaternion&		operator	-=	(float f){
				x	-=	f;
				y	-=	f;
				z	-=	f;
				w	-=	f;
				return	*this;
			};
			inline	XMMATRIX	ToMatrix()const{
				return	XMMatrixRotationQuaternion(XMLoadFloat4((XMFLOAT4*)this));
			};
			inline	Vector3			operator	*	(const	Vector3&	v)const{
				return	XMVector3TransformCoord(XMLoadFloat3((XMFLOAT3*)&v),ToMatrix());
			};
			inline	const Quaternion&	Inverse(){
				*this	=	XMQuaternionInverse(ToXM());
				return	*this;
			};
			inline	const Quaternion&	Normalize(){
				*this	=	XMQuaternionNormalize(ToXM());
				return	*this;
			};

			inline float& operator [] ( const unsigned int i ){
				assert( i < 4 );

				return *(&x+i);
			};
			inline float* ptr(){
				return &x;
			};
			inline const float* ptr() const{
				return &x;
			};




			float	x,y,z,w;

		};

// 		bool	operator	<(XMFLOAT4& xv,const Quaternion&	q){
// 			//XMFLOAT4 xv;
// 			xv.x	=	q.x;
// 			xv.y	=	q.y;
// 			xv.z	=	q.z;
// 			xv.w	=	q.w;
// 			return	true;
// 		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONQUATERNION_HEAD_FILE