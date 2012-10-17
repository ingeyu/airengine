#ifndef MTDOUBLEBUFFER_HEAD_FILE
#define	MTDOUBLEBUFFER_HEAD_FILE

#include "MTHeader.h"


typedef	std::vector<U8>	Buffer;

class MT_DoubleBuffer{
public:
	MT_DoubleBuffer();
	virtual	~MT_DoubleBuffer();
	virtual	void*	Request(U32 dwSize);
	virtual	void*	Read(U32 dwSize);
	virtual	void	Sync();

	void	EmptyWriteBufer();
	void	Request(enumCommandFunc	func){
		enumCommandFunc*	pFunc	=	(enumCommandFunc*)Request(sizeof(enumCommandFunc));
		*pFunc	=	func;
	}
	template<typename T>
	T*	Request(enumCommandFunc	func){
		U8*	pStart					=	(U8*)Request(sizeof(T)+sizeof(enumCommandFunc));
		enumCommandFunc*	pFunc	=	(enumCommandFunc*)pStart;
		*pFunc	=	func;
		return	(T*)(pStart+sizeof(enumCommandFunc));
	};
	template<typename T>
	T*	Request(enumCommandFunc	func,U32 uiBufferSize,void*&	pOutBuffer){
		U8*	pStart					=	(U8*)Request(sizeof(T)+sizeof(enumCommandFunc) + uiBufferSize);
		enumCommandFunc*	pFunc	=	(enumCommandFunc*)pStart;
		*pFunc	=	func;
		pStart+=sizeof(enumCommandFunc);
		T*	pRet	=	(T*)pStart;
		pStart+=sizeof(T);
		pOutBuffer	=	pStart;
		return	pRet;
	};

	void				PushReleaseObj(const ReleaseObj&	pObj);
	ReleaseObjVector&	GetWriteReleaseObjVector();
	ReleaseObjVector&	GetReadReleaseObjVector();
protected:
	void			ReAlloc(U32 uiSize);

public:
	Buffer				m_Buffer[2];
	U32					m_BufferOffset[2];
	U32					m_BufferSize[2];
	U32					m_uiWriteIndex;

	ReleaseObjVector	m_vecReleaseObj[2];
};

#endif