#ifndef AirSmallObjectAllocator_h__
#define AirSmallObjectAllocator_h__

#include "AirCommonHeader.h"

namespace	Air{
	class	COMMON_EXPORT	SmallObjectAllocator{
	public:
		SmallObjectAllocator(U32 uiMaxSize	=	512,U32 uiMaxCount	=	32768);
		~SmallObjectAllocator();

		void*	Alloc(U32 uiSize);
		void	Free(void* p);

	protected:
		U8*		m_pBuffer;
		U8*		m_pAllocBase;
		void**	m_pFreeBase;
		U32		m_uiMaxSize;
		U32		m_uiMaxCount;
		U32		m_uiFreeBegin;
		U32		m_uiFreeEnd;
		U32		m_uiMask;
	};
}
#endif // AirSmallObjectAllocator_h__
