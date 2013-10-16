#pragma once

#include "MCommon.h"
#include "AirCommonProduct.h"
namespace	Air{
	class MCOMMON_EXPORT	FileMapping	:	public	Common::IProduct
	{
	public:
		static AString	ProductTypeName;
		enum	enumFileMappingType{
			enFMT_Create,
			enFMT_Open,
		};
		struct Info{
			Info(){
				type		=		enFMT_Open;
				uiFileSize	=		16*1024*1024;
			};
			enumFileMappingType	type;
			U32					uiFileSize;
		};
	public:
		FileMapping(CAString& strFileName,Info* pInfo);
		virtual	~FileMapping(void);

		virtual	U1	Create();
		virtual	U1	Destroy();


		void*	GetLockedBuffer(){
			return m_pLockBuffer;
		};
	protected:
		U1		CreateFile();
		U1		OpenFile();
		U1		CloseFile();

		void*	Lock(	U32 uiOffset,U32	uiSize);
		void	UnLock();
	protected:
		HANDLE	m_hFile;
		void*	m_pLockBuffer;
		Info	m_Info;
	};
}

