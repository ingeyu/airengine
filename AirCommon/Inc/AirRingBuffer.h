#pragma once

#include "AirCommon.h"

namespace	Air{
	typedef void	(*DataProcess)(const void*,int );
	class	COMMON_EXPORT	RingBuffer{
	public:
		RingBuffer(int uiBufferSize	=	1024);
		~RingBuffer();

		int		Write(const void* pData,unsigned int uiSize);
		int		Read(DataProcess pProcessFunc);
		unsigned char*		m_pData;
		int					m_iBufferSize;
		int					m_iRead;
		int					m_iWrite;
	};
}