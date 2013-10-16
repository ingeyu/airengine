#ifndef MNetData_h__
#define MNetData_h__

#include	"MCommon.h"

#define		NET_VERSION	0X10000001

enum enNetType{
	enNT_Unknown,
	enNT_Return,

	enNT_CF_Hello,
	enNT_CF_LoadFile,
	enNT_CF_UnloadFile,


	enNT_FS_Hello,
	enNT_FS_LoadFile,
	enNT_SF_FileData,

};
struct	NetHeader{
	enNetType	t;	
};

struct	NT_Return		:	public	NetHeader{
	U32			ret;
	enNetType	lastType;		
};

template<typename T>
struct	NT_ReturnT		:	public	NT_Return{
	T	last;
};
struct	NT_CF_Hello		:	public	NetHeader{
	U32	PID;
	U32	BufferSize;
	U32	Version;
};

struct	NT_CF_LoadFile	:	public	NetHeader{
	U64	id;
	U32	val;
};
typedef NT_CF_LoadFile	NT_CF_UnLoadFile;

typedef NetHeader		NT_FS_Hello;
typedef	NT_CF_LoadFile	NT_FS_LoadFile;
struct NT_FS_FileData	:public	NetHeader{
	U32	uiOffset;
	U32	uiSize;
	U32	uiComplated;
	U8	data[512];

};


#endif // MNetData_h__
