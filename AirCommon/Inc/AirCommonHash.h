/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/28
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonHash.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONHASH_HEAD_FILE
#define COMMONHASH_HEAD_FILE
namespace	Air{
	namespace Common{
		/**	\brief	计算32位hash值
		*   
		*	@remarks 	算法参考Ogre的pass sort
		*	@see		
		*	@return   	Air::U32
		*	@param		U32 * p
		*	@param		U32 uiCount
		*	@note
		*
		**/
		inline	U32	CalcHash32(U32*	p,U32	uiCount){
			U32	h	=	0;
			for(U32 i=0;i<uiCount;i++){
				h	+=	(p[i]% (1 << 14)) << 14;
			}
			return	h;
		};

		/**	\brief	64位的hash值
		*
		*	64位的hash值
		*
		***/
		struct Hash64 
		{
			Hash64(){
				lowHash		=	0;
				highHash	=	0;
			};
			U1	operator	==	(const	Hash64&	h){
				return	(	lowHash		==	h.highHash	&&
							highHash	==	h.highHash);
			};
			U1	operator	<	(const	Hash64&	h){
				if(highHash	==	h.highHash){
					return	lowHash		<	h.lowHash;
				}else{
					return	highHash	<	h.highHash;
				}
			};
			U32	lowHash;
			U32	highHash;
		};

		/**	\brief	128位的hash值
		*
		*	128位的hash值
		*
		***/
		struct	Hash128{
			U1	operator	==	(const	Hash128&	h){
				return	(	l64	==	h.l64	&&
							h64	==	h.h64);
			};
			U1	operator	<	(const	Hash128&	h){
				if(h64	==	h.h64){
					return	l64	<	h.l64;
				}else{
					return	h64	<	h.h64;
				}
			};
			Hash64	l64;
			Hash64	h64;
		};
		
	
	};//end of	namespace	Client

	typedef	Common::Hash128	Hash128;
	typedef	Common::Hash64	Hash64;
};//end of namespace Air
#endif // COMMONHASH_HEAD_FILE