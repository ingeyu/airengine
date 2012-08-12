/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonInt3.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONINT3_HEAD_FILE
#define COMMONINT3_HEAD_FILE
namespace	Air{
	namespace Common{
		/**	\brief	3D整数模板向量
		*
		*	3D整数模板向量
		*
		***/
		template<typename	T>
		class	TVector3{
		public:
			inline	TVector3():x(0),y(0),z(0){

			};
			inline	TVector3(T ix,T iy,T iz):x(ix),y(iy),z(iz){

			};
			inline	TVector3(const	TVector3&	v):x(v.x),y(v.y),z(v.z){

			};
			inline	TVector3&	operator	=	(const	TVector3&	v){
				x	=	v.x;
				y	=	v.y;
				z	=	v.z;
				return	*this;
			};
			inline	bool		operator	==	(const	TVector3&	v){
				return	(	x	==	v.x	&&
							y	==	v.y	&&
							z	==	v.z);
			};
			inline	bool		operator	!=	(const	TVector3&	v){
				return	(	x	!=	v.x	&&
							y	!=	v.y	&&
							z	!=	v.z);
			};
			inline	TVector3	operator	+	(const	TVector3&	v){
				return	TVector3(	x	+	v.x,
					y	+	v.y,
					z	+	v.z);
			};
			inline	TVector3	operator	-	(const	TVector3&	v){
				return	TVector3(	x	-	v.x,
					y	-	v.y,
					z	-	v.z);
			};
			inline	TVector3	operator	*	(const	TVector3&	v){
				return	TVector3(	x	*	v.x,
					y	*	v.y,
					z	*	v.z);
			};
			inline	TVector3	operator	/	(const	TVector3&	v){
				return	TVector3(	x	/	v.x,
					y	/	v.y,
					z	/	v.z);
			};
			inline	TVector3	operator	*	(T t){
				return	TVector3(	x	*	t,
					y	*	t,
					z	*	t);
			};
			inline	TVector3	operator	/	(T t){
				return	TVector3(	x	/	t,
					y	/	t,
					z	/	t);
			};
			inline	TVector3&	operator	+=	(const	TVector3&	v){
				x	+=	v.x;
				y	+=	v.y;
				z	+=	v.z;
				return	*this;
			};
			inline	TVector3&	operator	-=	(const	TVector3&	v){
				x	-=	v.x;
				y	-=	v.y;
				z	-=	v.z;
				return	*this;
			};
			inline	TVector3&	operator	*=	(const	TVector3&	v){
				x	*=	v.x;
				y	*=	v.y;
				z	*=	v.z;
				return	*this;
			};
			inline	TVector3&	operator	/=	(const	TVector3&	v){
				x	/=	v.x;
				y	/=	v.y;
				z	/=	v.z;
				return	*this;
			};

			inline	TVector3&	operator	*=	(T t){
				x	*=	t;
				y	*=	t;
				z	*=	t;
				return	*this;
			};
			inline	TVector3&	operator	/=	(T t){
				x	/=	t;
				y	/=	t;
				z	/=	t;
				return	*this;
			};

			T	x,y,z;
		};
		typedef	TVector3<int>				IntVec3;
		typedef	TVector3<unsigned int>		UIntVec3;
		typedef	TVector3<short>				ShortVec3;
		typedef	TVector3<unsigned short>	UShortVec3;
		typedef	TVector3<char>				CharVec3;
		typedef	TVector3<unsigned char>		UCharVec3;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONINT3_HEAD_FILE