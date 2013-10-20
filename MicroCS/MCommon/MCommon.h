#ifndef MCommon_h__
#define MCommon_h__

#ifndef MCOMMON_EXPORT
#ifdef MCOMMON_IMPORT
#define MCOMMON_EXPORT __declspec(dllexport)
#else
#define MCOMMON_EXPORT __declspec(dllimport)
#endif
#endif

#include <Windows.h>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <hash_map>
#include <hash_set>
#include <queue>
#include <tchar.h>


#include "AirSingleton.h"

typedef bool				U1;
typedef	char				S8;
typedef	short				S16;
typedef	int					S32;
typedef	__int64				S64;
typedef unsigned char		U8;
typedef unsigned short		U16;
typedef unsigned int		U32;
typedef unsigned __int64	U64;
typedef std::string			AString;
typedef const AString		CAString;
typedef char				AChar;
typedef wchar_t				WChar;
//删除指针
#ifndef		SAFE_DELETE
#define		SAFE_DELETE(p)					if(p!=0){delete p;p=0;}
#endif
#define		SAF_D							SAFE_DELETE
//删除指针数组
#ifndef		SAFE_DELETE_ARRAY
#define		SAFE_DELETE_ARRAY(p)			if(p!=0){delete[] p;p=0;}
#endif
#define		SAF_DA							SAFE_DELETE_ARRAY

#ifndef		SAFE_RELEASE_REF
#define		SAFE_RELEASE_REF(p)				if(p!=NULL){p->ReleaseRef();p=NULL;}
#endif

#define		STD_LIST						std::list
#define		STD_VECTOR						std::vector
#define		STD_MAP							std::map
#define		STD_SET							std::set
#define		STD_HASHMAP						stdext::hash_map
#define		STD_QUEUE						std::queue


extern "C"	MCOMMON_EXPORT	void*	__Alloc(unsigned int	uiSize);
extern "C"	MCOMMON_EXPORT	void	__Free(void*	p);
extern "C"	MCOMMON_EXPORT	S32		MCompress(const void* pSrc,U32 iSize,void* pDest,U32& uiDestSize);
extern "C"	MCOMMON_EXPORT	S32		MDescompress(const void* pSrc,U32 iSize,void* pDest,U32& uiDestSize);
extern "C"	MCOMMON_EXPORT	S64		StringHash(const S8*	pName);
class MCOMMON_EXPORT	MemoryObject{
public:
	static	void*	operator new(size_t uiSize);
	static	void*	operator new[](size_t uiSize);
	static	void	operator delete(void* p);
	static	void	operator delete[](void* p);
	//replacement new
	static	void*	operator new(size_t uiSize,void* p){return p;};
	static	void*	operator new[](size_t uiSize,void* p){return p;};
	static	void	operator delete(void* ,void*){};
	static	void	operator delete[](void* ,void*){};
};
struct FileInfo{
	U64		fileid;
	U32		offset;
	U32		size;
	U32		idx;
	U32		compressize;
	
};
struct CSInfo 
{
	U32	FileSystemPID;
	U32	mark;
	U32	ret;
	U64	FileID;
	U32	uiSize;
};

struct	FileDataInfo{
	U32	idx;
	U32	uiOffset;
	U32	uiSize;
	U64	uiSocket;
};

typedef STD_VECTOR<FileInfo>		FileInfoVector;
typedef STD_HASHMAP<U64,FileInfo*>	FileInfoMap;
#define FILEDATA_COUNT	16
#define MAX_DATA_SIZE	3500*1048576
#endif // MCommon_h__
