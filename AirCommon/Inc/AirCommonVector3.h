/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/02
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonVector3.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONVECTOR3_HEAD_FILE
#define COMMONVECTOR3_HEAD_FILE


//#include "AirCommonHeader.h"
#include "xnamath.h"

namespace	Air{

	namespace Common{
	
		/**	\brief	3D向量
		*
		*	3D向量
		*
		***/
		class	Vector3{
		public:
			inline Vector3():
				x(0.0f),
				y(0.0f),
				z(0.0f){

			};
			inline Vector3(float fx,float fy,float fz):
				x(fx),
				y(fy),
				z(fz){

			};
			inline Vector3(const Vector3& v):
				x(v.x),
				y(v.y),
				z(v.z){

			};
			inline	Vector3(const	XMFLOAT3&	v):
				x(v.x),
				y(v.y),
				z(v.z){

			};
			inline Vector3(CXMVECTOR	v)
			{
				XMStoreFloat3((XMFLOAT3*)this,v);
			};

			template<typename T_Vector3>
			Vector3(const T_Vector3& v){
				U32	uiSize	=	min(sizeof(T_Vector3),sizeof(Vector3));
				memcpy(&x,&v,uiSize);
			};
			template<typename T_Vector3>
			Vector3	operator	=	(const T_Vector3& v){
				U32	uiSize	=	min(sizeof(T_Vector3),sizeof(Vector3));
				memcpy(&x,&v,uiSize);
				return	*this;
			};
			inline Vector3&		operator	=	(CXMVECTOR	v){
				XMStoreFloat3((XMFLOAT3*)this,v);
				return	*this;
			};
			inline	Vector3&	operator	=	(const	Vector3&	v){
				x	=	v.x;
				y	=	v.y;
				z	=	v.z;
				return	*this;
			};
			inline	Vector3		operator	+	(const	Vector3&	v)const{
				return	Vector3(x+v.x,y+v.y,z+v.z);
			};
			inline	Vector3		operator	+	(CXMVECTOR	v)const{
				return	Vector3(x+v.m128_f32[0],y+v.m128_f32[1],z+v.m128_f32[2]);
			};
			inline	Vector3&	operator	+=	(const	Vector3&	v){
				x	+=	v.x;
				y	+=	v.y;
				z	+=	v.z;
				return	*this;
			};
			inline	Vector3		operator	-	(const	Vector3&	v)const{
				return	Vector3(x-v.x,y-v.y,z-v.z);
			};
			inline	Vector3		operator	-	()const{
				return	Vector3(-x,-y,-z);
			};
			inline	Vector3		operator	-	(CXMVECTOR	v)const{
				return	Vector3(x-v.m128_f32[0],y-v.m128_f32[1],z-v.m128_f32[2]);
			};
			inline	Vector3&	operator	-=	(const	Vector3&	v){
				x	-=	v.x;
				y	-=	v.y;
				z	-=	v.z;
				return	*this;
			};
			inline	Vector3		operator	*	(float	f)const{
				return	Vector3(x*f,y*f,z*f);
			};
			inline	Vector3		operator	*	(const	Vector3&	v)const{
				return	Vector3(x*v.x,y*v.y,z*v.z);
			};
			inline	Vector3		operator	*	(CXMVECTOR	v)const{
				return	Vector3(x*v.m128_f32[0],y*v.m128_f32[1],z*v.m128_f32[2]);
			};
			inline	Vector3		operator	/	(float f)const{
				float	f0	=	1.0f/f;
				return	*this * f0;
			};
			inline	Vector3		operator	/	(const	Vector3&	v)const{
				return	Vector3(x/v.x,y/v.y,z/v.z);
			};
			inline	Vector3		operator	/	(CXMVECTOR	v)const{
				return	Vector3(x/v.m128_f32[0],y/v.m128_f32[1],z/v.m128_f32[2]);
			};
			inline	Vector3&	operator	/=	(float	f){
				float	f0	=	1.0f/f;
				*this	*=	f0;
				return	*this;
			};
			inline	Vector3&	operator	/=	(const	Vector3&	v){
				x	/=	v.x;
				y	/=	v.y;
				z	/=	v.z;
				return	*this;
			};
			inline	Vector3&	operator	*=	(float f){
				x	*=	f;
				y	*=	f;
				z	*=	f;
				return	*this;
			};
			inline	Vector3&	operator	*=	(const	Vector3&	v){
				x	*=	v.x;
				y	*=	v.y;
				z	*=	v.z;
				return	*this;
			};
			inline	Vector3&	operator	*=	(CXMVECTOR	v){
				x	*=	v.m128_f32[0];
				y	*=	v.m128_f32[1];
				z	*=	v.m128_f32[2];
				return	*this;
			};
			inline	bool		operator	==	(const	Vector3&	v)const{
				return	(	x	==	v.x	&&	
							y	==	v.y	&&
							z	==	v.z);
			};
			inline	bool		operator	!=	(const	Vector3&	v)const{
				return	(	x	!=	v.x	&&
							y	!=	v.y	&&
							z	!=	v.z);
			};
			inline	bool		operator	==	(CXMVECTOR	v)const{
				return	(	x	==	v.m128_f32[0]	&&	
							y	==	v.m128_f32[1]	&&
							z	==	v.m128_f32[2]);
			};
			inline	bool		operator	!=	(CXMVECTOR	v)const{
				return	(	x	!=	v.m128_f32[0]	&&	
							y	!=	v.m128_f32[1]	&&
							z	!=	v.m128_f32[2]);
			};
			inline	Vector3&	Normalize(){
				*this	=	XMVector3Normalize(ToXM());
				return	*this;
			};
			inline	Vector3		NormalizeCopy()const{
				return	XMVector3Normalize(ToXM());
			};
			inline	float		Length()const{
				return	XMVector3Length(ToXM()).m128_f32[0];
			};
			inline	float		Distance(const	Vector3&	v)const{
				return	(*this	-	v).Length();
			};
			inline	float		Dot(const	Vector3&	v)const{
				return	x*v.x+y*v.y+z*v.z;//XMVector3Dot(	ToXM(),										XMLoadFloat3((XMFLOAT3*)&v)).m128_f32[0];
			};
			inline	Vector3		Cross(const	Vector3&	v)const{
				return	XMVector3Cross(	ToXM(),
										XMLoadFloat3((XMFLOAT3*)&v));
			};
			inline	XMVECTOR	ToXM()const{
				return	XMLoadFloat3((XMFLOAT3*)&x);
			};


			inline float operator [] ( const unsigned int i )const{
				assert( i < 3 );

				return *(&x+i);
			};
			inline float& operator [] ( const unsigned int i ){
				assert( i < 3 );

				return *(&x+i);
			};
			inline float* ptr(){
				return &x;
			};
			inline const float* ptr() const{
				return &x;
			};


			float x,y,z;
			
		};
		/**	\brief	双精度浮点3D向量
		*
		*	针对超大地形而设计
		*
		***/
		class	DVector3{
		public:
			inline	DVector3():x(0.0f),y(0.0f),z(0.0f){

			};
			inline	DVector3(double	fx,double fy,double	fz):x(fx),y(fy),z(fz){

			};
			inline	DVector3(const	DVector3&	v):x(v.x),y(v.y),z(v.z){

			};
			inline	DVector3&	operator	=	(const	DVector3&	v){
				x	=	v.x;
				y	=	v.y;
				z	=	v.z;
				return	*this;
			};
			inline	DVector3&	operator	=	(const	Vector3&	v){
				x	=	v.x;
				y	=	v.y;
				z	=	v.z;
				return	*this;
			};
			inline	DVector3&	operator	=	(CXMVECTOR	v){
				x	=	v.m128_f32[0];
				y	=	v.m128_f32[1];
				z	=	v.m128_f32[2];
				return	*this;
			}; 
			inline	DVector3	operator	+	(const	DVector3&	v){
				return	DVector3(	x+v.x,y+v.y,z+v.z);
			};
			inline	DVector3	operator	-	(const	DVector3&	v){
				return	DVector3(	x-v.x,y-v.y,z-v.z);
			};
			inline	DVector3	operator	*	(const	DVector3&	v){
				return	DVector3(	x*v.x,y*v.y,z*v.z);
			};
			inline	DVector3	operator	/	(const	DVector3&	v){
				return	DVector3(	x/v.x,y/v.y,z/v.z);
			};
			inline	DVector3	operator	*	(double	f){
				return	DVector3(	x*f,y*f,z*f);
			};
			inline	DVector3	operator	/	(double	f){
				double	f0	=	1/f;
				return	DVector3(	x*f0,y*f0,z*f0);
			};
			inline	DVector3	operator	*	(float	f){
				return	DVector3(	x*f,y*f,z*f);
			};
			inline	DVector3	operator	/	(float	f){
				double	f0	=	1/f;
				return	DVector3(	x*f0,y*f0,z*f0);
			};

			inline	DVector3&	operator	+=	(const	DVector3&	v){
				x	+=	v.x;
				y	+=	v.y;
				z	+=	v.z;
				return	*this;
			};
			inline	DVector3&	operator	-=	(const	DVector3&	v){
				x	-=	v.x;
				y	-=	v.y;
				z	-=	v.z;
				return	*this;
			};
			inline	DVector3&	operator	*=	(const	DVector3&	v){
				x	*=	v.x;
				y	*=	v.y;
				z	*=	v.z;
				return	*this;
			};
			inline	DVector3&	operator	/=	(const	DVector3&	v){
				x	/=	v.x;
				y	/=	v.y;
				z	/=	v.z;
				return	*this;
			};
			inline	double		Dot(const	DVector3&	v){
				return	x*v.x+y*v.y+z*v.z;
			};
			inline	DVector3	Cross(const	DVector3&	v){
				return	DVector3(	y * v.z - z * v.y,
									z * v.x - x * v.z,
									x * v.y - y * v.x);
			};
			inline	double		Length(){
				return	sqrt(x*x+y*y+z*z);
			};
			inline	double		Distance(const	DVector3&	v){
				return	(*this	-	v).Length();
			};
			inline	DVector3&	Normalize(){
				double fLength = sqrt(	x * x + y * y + z * z );
				// Will also work for zero-sized vectors, but will change nothing
				if ( fLength > 1e-08 ){
					double fInvLength = 1.0 / fLength;
					x *= fInvLength;
					y *= fInvLength;
					z *= fInvLength;
				}

				return	*this;
			};
			inline	DVector3	NormalizeCopy(){
				DVector3	v	=	*this;
				return	v.Normalize();
			};
			inline	DVector3	MiddlePoint( const DVector3& v )
			{
				return DVector3(
								( x + v.x ) * 0.5,
								( y + v.y ) * 0.5,
								( z + v.z ) * 0.5 );
			};
//warning C4244: “参数”: 从“double”转换到“const Real”，可能丢失数据
#pragma warning(disable:4244)
			inline	Vector3		ToVector3(){
				return	Vector3(x,y,z);
			};
#pragma warning(default:4244)
			double	x,y,z;
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONVECTOR3_HEAD_FILE