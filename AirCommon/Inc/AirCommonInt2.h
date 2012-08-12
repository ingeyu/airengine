/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonInt2.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONINT2_HEAD_FILE
#define COMMONINT2_HEAD_FILE
namespace	Air{
	namespace Common{
	
		/**	\brief	3D整数模板向量
		*
		*	3D整数模板向量
		*
		***/
		template<typename	T>
		class	TVector2{
		public:
			inline	TVector2():x(0),y(0){

			};
			inline	TVector2(T ix,T iy):x(ix),y(iy){

			};
			inline	TVector2(const	TVector2&	v):x(v.x),y(v.y){

			};
			inline	TVector2&	operator	=	(const	TVector2&	v){
				x	=	v.x;
				y	=	v.y;
				return	*this;
			};
			inline	bool		operator	==	(const	TVector2&	v){
				return	(	x	==	v.x	&&
					y	==	v.y);
			};
			inline	bool		operator	!=	(const	TVector2&	v){
				return	(	x	!=	v.x	&&
					y	!=	v.y);
			};
			inline	TVector2	operator	+	(const	TVector2&	v){
				return	TVector2(	x	+	v.x,
					y	+	v.y);
			};
			inline	TVector2	operator	-	(const	TVector2&	v){
				return	TVector2(	x	-	v.x,
					y	-	v.y);
			};
			inline	TVector2	operator	*	(const	TVector2&	v){
				return	TVector2(	x	*	v.x,
					y	*	v.y);
			};
			inline	TVector2	operator	/	(const	TVector2&	v){
				return	TVector2(	x	/	v.x,
					y	/	v.y);
			};
			inline	TVector2	operator	*	(T t){
				return	TVector2(	x	*	t,
					y	*	t);
			};
			inline	TVector2	operator	/	(T t){
				return	TVector2(	x	/	t,
					y	/	t);
			};
			inline	TVector2&	operator	+=	(const	TVector2&	v){
				x	+=	v.x;
				y	+=	v.y;
				return	*this;
			};
			inline	TVector2&	operator	-=	(const	TVector2&	v){
				x	-=	v.x;
				y	-=	v.y;
				return	*this;
			};
			inline	TVector2&	operator	*=	(const	TVector2&	v){
				x	*=	v.x;
				y	*=	v.y;
				return	*this;
			};
			inline	TVector2&	operator	/=	(const	TVector2&	v){
				x	/=	v.x;
				y	/=	v.y;
				return	*this;
			};

			inline	TVector2&	operator	*=	(T t){
				x	*=	t;
				y	*=	t;
				return	*this;
			};
			inline	TVector2&	operator	/=	(T t){
				x	/=	t;
				y	/=	t;
				return	*this;
			};

			T	x,y;
		};

		typedef	TVector2<int>				IntVec2;
		typedef	TVector2<unsigned int>		UIntVec2;
		typedef	TVector2<short>				ShortVec2;
		typedef	TVector2<unsigned short>	UShortVec2;
		typedef	TVector2<char>				CharVec2;
		typedef	TVector2<unsigned char>		UCharVec2;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONINT2_HEAD_FILE