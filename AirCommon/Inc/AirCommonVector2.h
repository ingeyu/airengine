/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/07
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonVector2.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>        ; <desc>
******************************************************/
#ifndef COMMONVECTOR2_HEAD_FILE
#define COMMONVECTOR2_HEAD_FILE

#include "xnamath.h"

namespace	Air{
	namespace Common{
	
		class	Vector2{
		public:
			inline	Vector2():x(0.0f),y(0.0f){};
	
			inline	Vector2(float fx,float fy):x(fx),y(fy){

			};
			inline	Vector2(const Vector2&	v):x(v.x),y(v.y){

			};
			inline	Vector2(CXMVECTOR v):x(v.m128_f32[0]),y(v.m128_f32[1]){

			};
			template<typename T_Vector2>
			Vector2(const T_Vector2& v){
				U32	uiSize	=	min(sizeof(T_Vector2),sizeof(Vector2));
				memcpy(&x,&v,uiSize);
			};
			template<typename T_Vector2>
			Vector2	operator	=	(const T_Vector2& v){
				U32	uiSize	=	min(sizeof(T_Vector2),sizeof(Vector2));
				memcpy(&x,&v,uiSize);
				return	*this;
			};
			inline	Vector2	operator	=	(const	Vector2&	v){
				x	=	v.x;
				y	=	v.y;
				return	*this;
			};
			inline	Vector2	operator	=	(CXMVECTOR	v){
				x	=	v.m128_f32[0];
				y	=	v.m128_f32[1];
				return	*this;
			};
			inline	bool		operator	==	(const	Vector2&	v){
				return	(	x	==	v.x	&&
							y	==	v.y);
			};
			inline	bool		operator	!=	(const	Vector2&	v){
				return	(	x	!=	v.x	&&
							y	!=	v.y);
			};
			inline	bool		operator	==	(CXMVECTOR	v){
				return	(	x	==	v.m128_f32[0]	&&
							y	==	v.m128_f32[1]);
			};
			inline	bool		operator	!=	(CXMVECTOR	v){
				return	(	x	!=	v.m128_f32[0]	&&
							y	!=	v.m128_f32[1]);
			};

			inline	Vector2		operator	*	(const	Vector2&	v){
				return	Vector2(x*v.x,y*v.y);
			};
			inline	Vector2		operator	*	(float	f){
				return	Vector2(x*f,y*f);
			};
			inline	Vector2		operator	/	(const	Vector2&	v){
				return	Vector2(x/v.x,y/v.y);
			};
			inline	Vector2		operator	/	(float	f){
				float	f0	=	1.0f/f;
				return	Vector2(x*f0,y*f0);
			};
			inline	Vector2		operator	+	(const	Vector2&	v){
				return	Vector2(x+v.x,y+v.y);
			};
			inline	Vector2		operator	-	(const	Vector2&	v){
				return	Vector2(x-v.y,y-v.y);
			};
			inline	Vector2		operator	-	(){
				return	Vector2(-x,-y);
			}
			inline	Vector2&	operator	+=	(const	Vector2&	v){
				x	+=	v.x;
				y	+=	v.y;
				return	*this;
			};
			inline	Vector2&	operator	-=	(const	Vector2&	v){
				x	-=	v.x;
				y	-=	v.y;
				return	*this;
			};
			inline	Vector2&	operator	*=	(const	Vector2&	v){
				x	*=	v.x;
				y	*=	v.y;
				return	*this;
			};
			inline	Vector2&	operator	/=	(const	Vector2&	v){
				x	/=	v.x;
				y	/=	v.y;
				return	*this;
			};
			inline	XMVECTOR	ToXM(){
				return	XMLoadFloat2((XMFLOAT2*)this);
			};
			float	x,y;
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONVECTOR2_HEAD_FILE