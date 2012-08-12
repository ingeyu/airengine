/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonInt4.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONINT4_HEAD_FILE
#define COMMONINT4_HEAD_FILE
namespace	Air{
	namespace Common{
		/**	\brief	4D整数模板向量
		*
		*	4D整数模板向量
		*
		***/
		template<typename	T>
		class	TVector4{
		public:
			inline	TVector4():x(0),y(0),z(0),w(0){

			};
			inline	TVector4(T ix,T iy,T iz,T iw):x(ix),y(iy),z(iz),w(iw){

			};
			inline	TVector4(const	TVector4&	v):x(v.x),y(v.y),z(v.z),w(v.w){

			};
			inline	TVector4&	operator	=	(const	TVector4&	v){
				x	=	v.x;
				y	=	v.y;
				z	=	v.z;
				w	=	v.w;
				return	*this;
			};
			inline	bool		operator	==	(const	TVector4&	v){
				return	(	x	==	v.x	&&
							y	==	v.y	&&
							z	==	v.z	&&
							w	==	v.w);
			};
			inline	bool		operator	!=	(const	TVector4&	v){
				return	(	x	!=	v.x	&&
							y	!=	v.y	&&
							z	!=	v.z	&&
							w	!=	v.w);
			};
			inline	TVector4	operator	+	(const	TVector4&	v){
				return	TVector4(	x	+	v.x,
									y	+	v.y,
									z	+	v.z,
									w	+	v.w);
			};
			inline	TVector4	operator	-	(const	TVector4&	v){
				return	TVector4(	x	-	v.x,
									y	-	v.y,
									z	-	v.z,
									w	-	v.w);
			};
			inline	TVector4	operator	*	(const	TVector4&	v){
				return	TVector4(	x	*	v.x,
									y	*	v.y,
									z	*	v.z,
									w	*	v.w);
			};
			inline	TVector4	operator	/	(const	TVector4&	v){
				return	TVector4(	x	/	v.x,
									y	/	v.y,
									z	/	v.z,
									w	/	v.w);
			};
			inline	TVector4	operator	*	(T t){
				return	TVector4(	x	*	t,
									y	*	t,
									z	*	t,
									w	*	t);
			};
			inline	TVector4	operator	/	(T t){
				return	TVector4(	x	/	t,
									y	/	t,
									z	/	t,
									w	/	t);
			};
			inline	TVector4&	operator	+=	(const	TVector4&	v){
				x	+=	v.x;
				y	+=	v.y;
				z	+=	v.z;
				w	+=	v.w;
				return	*this;
			};
			inline	TVector4&	operator	-=	(const	TVector4&	v){
				x	-=	v.x;
				y	-=	v.y;
				z	-=	v.z;
				w	-=	v.w;
				return	*this;
			};
			inline	TVector4&	operator	*=	(const	TVector4&	v){
				x	*=	v.x;
				y	*=	v.y;
				z	*=	v.z;
				w	*=	v.w;
				return	*this;
			};
			inline	TVector4&	operator	/=	(const	TVector4&	v){
				x	/=	v.x;
				y	/=	v.y;
				z	/=	v.z;
				w	/=	v.w;
				return	*this;
			};

			inline	TVector4&	operator	*=	(T t){
				x	*=	t;
				y	*=	t;
				z	*=	t;
				w	*=	t;
				return	*this;
			};
			inline	TVector4&	operator	/=	(T t){
				x	/=	t;
				y	/=	t;
				z	/=	t;
				w	/=	t;
				return	*this;
			};

			T	x,y,z,w;
		};
		
		typedef	TVector4<int>				IntVec4;
		typedef	TVector4<unsigned int>		UIntVec4;
		typedef	TVector4<short>				ShortVec4;
		typedef	TVector4<unsigned short>	UShortVec4;
		typedef	TVector4<char>				CharVec4;
		typedef	TVector4<unsigned char>		UCharVec4;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONINT4_HEAD_FILE