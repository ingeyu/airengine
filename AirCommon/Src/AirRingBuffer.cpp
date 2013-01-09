#include "AirRingBuffer.h"
#include "AirCommonMemory.h"

namespace	Air{
	RingBuffer::RingBuffer(int iBufferSize){
		m_iBufferSize	=	iBufferSize;
		if(m_iBufferSize	>	0){
			m_pData	=	(unsigned char*)__Alloc(m_iBufferSize);
			memset(m_pData,0,sizeof(int));
		}else{
			m_pData	=	0;
		}
		m_iRead		=	0;
		m_iWrite	=	0;
	};
	RingBuffer::~RingBuffer(){
		if(m_pData!=0){
			__Free(m_pData);
			m_pData=0;
		}
		m_iBufferSize	=	0;
		m_iRead		=	0;
		m_iWrite	=	0;
	}

	int		RingBuffer::Write(const void* pData,unsigned int uiSize){
		if(uiSize	>	m_iBufferSize)
			return -1;
		const int iEndFlag		=	0;
		const int iInverseFlag	=	-1;
		if(m_iWrite+uiSize	>	m_iBufferSize){
			memcpy(&m_pData[0],&iEndFlag,sizeof(int));
			memcpy(&m_pData[m_iWrite],&iInverseFlag,sizeof(int));
			m_iWrite=0;
		}
		memcpy(&m_pData[m_iWrite+4],pData,uiSize);
		memcpy(&m_pData[m_iWrite],&iEndFlag,uiSize);
		m_iWrite+=sizeof(int)+uiSize;
		return 0;
	};
	int		RingBuffer::Read(DataProcess pProcessFunc){
		if(m_iRead	==	m_iWrite)
			return 0;
		int	iCount	=	0;
		while(true){
			int iSize =	*(int*)&m_pData[m_iRead];
			switch(iSize){
				case -1:{
					m_iRead	=	0;
					}break;
				case 0:{
					return iCount;
					}break;
				default:{
					if(iSize<0)
						return iCount;
					iCount++;
					m_iRead+=sizeof(int);
					if(pProcessFunc!=0){
						(*pProcessFunc)(&m_pData[m_iRead],iSize);
					}
					m_iRead+=iSize;
					}break;
			}
		}
		return iCount;
	};

	int RingBuffer::Read( void* pData,int iMaxSize /*= 1024*/ )
	{
		if(m_iRead	==	m_iWrite)
			return 0;
		int	iCount	=	0;
		unsigned char* pBase = (unsigned char*)pData;
		while(true){
			int iSize =	*(int*)&m_pData[m_iRead];
			switch(iSize){
			case -1:{
				m_iRead	=	0;
					}break;
			case 0:{
				return iCount;
				   }break;
			default:{
				if(iSize<0)
					return iCount;
				int iDataSize = iSize+sizeof(int);
				if(iCount+iSize+4 <	iMaxSize){
					memcpy(pBase,&m_pData[m_iRead],iDataSize);
					iCount+=iDataSize;
					m_iRead+=iDataSize;
				}else{
					return iCount;
				}
					}break;
			}
		}
		return iCount;
	}


}