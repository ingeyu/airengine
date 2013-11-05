#include "MCommon.h"

#define	LZO_COMPRESS	0
#define ZIP_COMPRESS	1
#define	LZMA_COMPRESS	2

#define	COMPRESS_TYPE	LZMA_COMPRESS

#if (COMPRESS_TYPE	==	ZIP_COMPRESS)
#include "lzo/zlib.h"
#elif (COMPRESS_TYPE	==	LZMA_COMPRESS)
#include "lzo/zlib.h"
#include "lzma/LzmaLib.h"
#else
#include "lzo/minilzo.h"
#endif


BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call){
	case DLL_PROCESS_ATTACH:{
		//lzo_init();

							}break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:

		break;
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}
void* __Alloc( unsigned int uiSize ){
	if(uiSize==0){
		return	NULL;
	}
	return	malloc(uiSize);
}

void __Free( void* p ){
	free(p);
}
void*	MemoryObject::operator new(size_t uiSize){
	return __Alloc(uiSize);
};
void*	MemoryObject::operator new[](size_t uiSize){
	return __Alloc(uiSize);
};
void	MemoryObject::operator delete(void* p){
	__Free(p);
};
void	MemoryObject::operator delete[](void* p){
	__Free(p);
};

S32 MCompress( const void* pSrc,U32 iSize,void* pDest,U32& uiDestSize )
{
	//U8 workmem[LZO1X_1_MEM_COMPRESS];
	//return lzo1x_1_compress((U8*)pSrc,iSize,(U8*)pDest,(unsigned long*)&uiDestSize,workmem);
#if COMPRESS_TYPE	==	ZIP_COMPRESS
	return compress2((Bytef*)pDest,(uLongf*)&uiDestSize,(const Bytef*)pSrc,iSize,Z_BEST_COMPRESSION);
#elif COMPRESS_TYPE	==	LZMA_COMPRESS
	unsigned char prop[5]={0};
	size_t sizeProp = 5;
	unsigned char* pDest1	=	(unsigned char*)pDest;
	
	int ret	= LzmaCompress(pDest1,&uiDestSize,(const unsigned char*)pSrc,iSize,prop,&sizeProp,9,1<<24,3,0,2,32,2);
	if(ret==7){
		uiDestSize	=	iSize+1;
		OutputDebugString(L"No Compress\n");
		return 0;
	}
	return ret;
#else
	U8 workmem[LZO1X_1_MEM_COMPRESS];
	return lzo1x_1_compress((U8*)pSrc,iSize,(U8*)pDest,(unsigned long*)&uiDestSize,workmem);
#endif
}

S32 MDescompress( const void* pSrc,U32 iSize,void* pDest,U32& uiDestSize )
{
	//U8 workmem[LZO1X_1_MEM_COMPRESS];
	//return lzo1x_decompress((U8*)pSrc,iSize,(U8*)pDest,(unsigned long*)&uiDestSize,workmem);
#if COMPRESS_TYPE	==	ZIP_COMPRESS
	return uncompress((Bytef*)pDest,(uLongf*)&uiDestSize,(const Bytef*)pSrc,(uLongf)iSize);
#elif COMPRESS_TYPE	==	LZMA_COMPRESS
	unsigned char prop[5]	=	{0x5d,0,0,0,1};
	size_t sizeProp = 5;
	return LzmaUncompress((unsigned char*)pDest,&uiDestSize,(unsigned char*)pSrc,&iSize,prop,sizeProp);
#else
	return lzo1x_decompress((U8*)pSrc,iSize,(U8*)pDest,(unsigned long*)&uiDestSize,0);
#endif
}
U32	HashStringID( const S8* pName ,U32 type){
	U32	seed1	=	0x7FED7FED;
	U32	seed2	=	0xEEEEEEEE;
	U32	ch;
	while(*pName!=0){
		ch	=	toupper(*pName++);
		//seed1	=	
	}
	return 0;
}
unsigned int APHash(const char *str)
{
	unsigned int hash = 0;
	int i;

	for (i=0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}

	return (hash & 0x7FFFFFFF);
}
unsigned int BKDRHash(const char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}
S64 StringHash( const S8* pName )
{
	U64	h1	=	(U64)BKDRHash(pName);
	U32	h2	=	APHash(pName);
	return (h1<<32)|(h2);
}

U32 CRC32( void* p,U32 uiSize )
{
#ifdef ZIP_COMPRESS
	return crc32(0x12345678,(const U8*)p,uiSize);//lzo_adler32(0x1234,(const U8*)p,uiSize);
#else
	return lzo_adler32(0x12345678,(const U8*)p,uiSize);
#endif
}
