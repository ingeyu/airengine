#ifndef MNetData_h__
#define MNetData_h__

#include	"MCommon.h"

#define		NET_VERSION	0X10000001

enum enNetType{
	enNT_Unknown,
	enNT_Return,

	enNT_FS_Hello,
	enNT_FS_LoadFile,
	enNT_SF_FileData,

};
#pragma pack(push)
#pragma pack(4)
struct NtBase
{
	U32			uiSize;
	enNetType	t;	
};
template<typename T>
struct NtPack	:	public	NtBase
{
	NtPack(enNetType	nType){
		t		=	nType;
		uiSize	=	sizeof(NtPack<T>)-4;
	};
	T	data;
};

struct NtReturnPack	:	public	NtBase{
	NtReturnPack(enNetType nLast,U32	val	=	1)
	{
		uiSize		=	sizeof(*this)-4;
		t			=	enNT_Return;
		lastType	=	nLast;
		retValue	=	val;
	};
	U32			retValue;
	enNetType	lastType;
};

template<typename T>
struct NtReturnPackT	:	public	NtReturnPack{
	NtReturnPackT(enNetType nLast,U32	val	=	1):NtReturnPack(nLast,val)
	{
		uiSize		=	sizeof(*this)-4;
	}
	T	data;
};

struct	NetHeader{
	enNetType	t;	
};

template<typename T>
struct	NT_Data	:	public	NetHeader{
	NT_Data(enNetType	nType){
		t		=	nType;
	};
	T	data;
};

struct	NT_Return	:public	NetHeader{
	NT_Return(enNetType nLast,U32	val	=	1)
	{
		t			=	enNT_Return;
		lastType	=	nLast;
		retValue	=	val;
	};
	U32			retValue;
	enNetType	lastType;		
};

template<typename T>
struct	NT_ReturnT	:public	NT_Return{
	NT_ReturnT(enNetType nLast,U32	val	=	1):NT_Return(nLast,val)
	{
	};
	T	data;	
};

struct NT_SF_Hello{
	U32	uiClient;
	U32	uiTaskCount;
};
struct NT_FS_LoadFile
{
	U64	fileid;
	
};
struct NT_FS_FileData{
	U32	idx;
	U32	uiOffset;
	U32	uiSize;
	U32	uiComplated;
	U8	data[4096];

};
#pragma pack(pop)

#endif // MNetData_h__
