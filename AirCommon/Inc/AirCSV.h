#ifndef AirCSV_h__
#define AirCSV_h__

#include "AirCommonHeader.h"
#include "AirCommonData.h"

namespace	Air{
	union	CSVItem{
		AChar*	pStr;
		S32		iVal;
		U32		uiVal;
		float	fVal;
		
	};
	class	COMMON_EXPORT CSV	:	public	MemoryObject
	{
	public:
		CSV();
		~CSV();
		U1	Load(CAString& strName);
		U1	Load(void*	pData,U32 uiSize);
		void	Clear();
		U32			GetLineCount();
		U32			GetRowCount();
		CSVItem		GetItem(U32	X,U32 Y);
		
		STD_VECTOR<CSVItem>	m_vecItem;
		Common::Data		m_Data;
		U32					m_uiLineCount;
		U32					m_uiRowCount;
	};
}
#endif // AirCSV_h__
