#include "AirCommonMemory.h"
#include <malloc.h>

#ifndef		NULL
#define		NULL	0
#endif
namespace Air{
	
	namespace	Common{
		
	
		void Memcpy4( void* pDst,const void* pSrc,int iSize ){
			int	iCount	=	iSize>>2;
			int*	pTemp1	=	static_cast<int*>(pDst);
			const int*	pTemp2	=	static_cast<const int*>(pSrc);
			while (iCount--) {
				*pTemp1++	=	*pTemp2++;
			}
		}

		bool Memcmp4( void* p1,const void* p2,int iSize ){
			int	iCount	=	iSize>>2;
			int*	pTemp1	=	static_cast<int*>(p1);
			const int*	pTemp2	=	static_cast<const int*>(p2);
			while (iCount--) {
				if(*pTemp1++!=*pTemp2++){
					return	false;
				}
			}
			return	true;
		}

		void Memcpy2( void* pDst,const void* pSrc,int iSize ){
			int	iCount	=	iSize>>1;
			short*	pTemp1	=	static_cast<short*>(pDst);
			const short*	pTemp2	=	static_cast<const short*>(pSrc);
			while (iCount--) {
				*pTemp1++	=	*pTemp2++;
			}
		}
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
};