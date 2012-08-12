#include "AirCompress.h"
#include "minilzo.h"

namespace Air{
	
	namespace	Common{
	
	
	#define HEAP_ALLOC(var,size) \
		lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]
	
		static HEAP_ALLOC(wrkmem,LZO1X_1_MEM_COMPRESS);
	
	
	
	
		bool Compress::Init(){
			if (lzo_init() != LZO_E_OK){
				return false;
			}
			return true;
		};
	
		bool Compress::Release(){
			return true;
		}
	
		bool Compress::ToLZO(	U8*		pSrcData,
								UInt	uiSrcSize,
								U8*		pDstData,
								U32*	uiDstSize){
				int r = lzo1x_1_compress(pSrcData,uiSrcSize,pDstData,uiDstSize,wrkmem);
				if (r == LZO_E_OK){
					if (*uiDstSize >= uiSrcSize){
						return false;
					}
				}else{
					return false;
				}
	
				return true;
		}
	
		bool Compress::FromLZO(	U8*		pSrcData,
								UInt	uiSrcSize,
								U8*		pDstData,
								U32*	uiDstSize){
				int r = lzo1x_decompress(pSrcData,uiSrcSize,pDstData,uiDstSize,NULL);
				if (r == LZO_E_OK && uiSrcSize == *uiDstSize){
					return true;
				}else{
					return false;
				}
				return true;
		}
	
	}
};