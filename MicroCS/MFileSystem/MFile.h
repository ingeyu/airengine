#ifndef MFile_h__
#define MFile_h__

#include "MFileSystemCommon.h"
class MClient;
struct NotifyInfo{
	MClient*	pClient;
	U32			uiOffset;
};

class MFile	:	public	Air::Common::IProduct{
public:
	static AString	ProductTypeName;
	typedef FileInfo	Info;

public:
	MFile(CAString& strName,Info* pInfo);

	virtual	U1	Create();
	virtual	U1	Destroy();
	U1			IsDownloading(){
		return m_bDownloading;
	}
	void		OnDownloading(U32 uiOffset,const void* p,U32 uiSize);
	void		OnDownloadComplated(U1	bOK);
	U64			GetFileID(){
		return m_pInfo->fileid;
	};
	U32			GetDataSize();
	FileInfo&	GetFileInfo();
	void		AddNotify(const NotifyInfo& info);
	void*		GetData();
	U32			GetFileIndexRA();
protected:
	Info*			m_pInfo;
	STD_VECTOR<U8>	m_Data;
	U1				m_bDownloading;

	STD_LIST<NotifyInfo>			m_lstNotify;
	Air::Common::CriticalSection	m_NotifyCS;
};
#endif // MFilePool_h__
