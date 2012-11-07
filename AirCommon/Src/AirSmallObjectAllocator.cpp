#include "AirSmallObjectAllocator.h"

namespace	Air{


	SmallObjectAllocator::SmallObjectAllocator( U32 uiMaxSize,U32 uiMaxCount )
	{
		U32 uiCount	=	1;
		for(U32 i=0;i<32;i++){
			uiCount	=	uiCount<<1;
			if(uiCount > uiMaxCount){
				break;
			}
		}

		m_uiMaxSize		=	uiMaxSize;
		m_uiMaxCount	=	uiCount;
		m_uiMask		=	m_uiMaxCount-1;
		U32	uiFreeSize	=	sizeof(void*)*m_uiMaxCount;
		U32	uiTotalSize	=	uiFreeSize+m_uiMaxCount*uiMaxSize;

		m_pBuffer		=	(U8*)__Alloc(uiTotalSize);

		m_pAllocBase	=	m_pBuffer+uiFreeSize;
		m_pFreeBase		=	(void**)m_pBuffer;
		m_uiFreeBegin	=	0;
		m_uiFreeEnd		=	m_uiMaxCount;
		void**	p		=	(void**)m_pFreeBase;
		for(U32 i=0;i<m_uiMaxCount;i++){
			p[i]	=	m_pAllocBase+i*sizeof(void*);
		}
	}

	SmallObjectAllocator::~SmallObjectAllocator()
	{
		if(m_pBuffer!=NULL){
			__Free(m_pBuffer);
			m_pBuffer=NULL;
		}
	}

	void* SmallObjectAllocator::Alloc( U32 uiSize )
	{
		if(uiSize>m_uiMaxSize){
			return NULL;
		}
		if(m_uiFreeEnd - m_uiFreeBegin==0)
			return NULL;
		U32	uiCurrent	=	InterlockedIncrement(&m_uiFreeBegin)-1;
		uiCurrent	&=m_uiMask;
#ifdef _DEBUG
		void*	pRet	=	 m_pFreeBase[uiCurrent];
		m_pFreeBase[uiCurrent]	=	0x00000000;
		return pRet;
#else
		return m_pFreeBase[uiCurrent];
#endif
	}

	void SmallObjectAllocator::Free( void* p )
	{
		U32 uiCurrent	=	InterlockedIncrement(&m_uiFreeEnd)-1;
		uiCurrent	&=m_uiMask;
		m_pFreeBase[uiCurrent]	=	p;
	}

}