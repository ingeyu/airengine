//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Compress.h
 \note     
       
 \attention:
			压缩解压缩
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMPRESS_HEAD_FILE
#define COMPRESS_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
namespace Air{
	
	namespace Common{
		/**	\brief	高速压缩
		*
		*	高速压缩
		*
		***/
		class Compress{
		public:
			/**	\brief	初始化压缩
			*   
			*	@remarks 	初始化
			*	@see		Compress
			*	@return   	bool
			*	@note
			*
			**/
			static bool Init();
			/**	\brief	释放
			*   
			*	@remarks 	释放
			*	@see		Compress
			*	@return   	bool
			*	@note
			*
			**/
			static bool Release();
	
			
			/**	\brief	压缩
			*   
			*	@remarks 	压缩
			*	@see		Compress
			*	@return   	bool
			*	@param		U8 * pSrcData
			*	@param		UInt uiSrcSize
			*	@param		U8 * pDstData
			*	@param		U32 * uiDstSize
			*	@note
			*
			**/
			static bool ToLZO(	U8*		pSrcData,
								UInt	uiSrcSize,
								U8*		pDstData,
								U32*	uiDstSize);
			/**	\brief	解压缩
			*   
			*	@remarks 	解压缩
			*	@see		Compress
			*	@return   	bool
			*	@param		U8 * pSrcData
			*	@param		UInt uiSrcSize
			*	@param		U8 * pDstData
			*	@param		U32 * uiDstSize
			*	@note
			*
			**/
			static bool FromLZO(U8*		pSrcData,
								UInt	uiSrcSize,
								U8*		pDstData,
								U32*	uiDstSize);
		};
		
	
	};
};
#endif // COMPRESS_HEAD_FILE