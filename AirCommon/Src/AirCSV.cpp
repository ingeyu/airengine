#include "AirCSV.h"
#include "AirCommonFile.h"
namespace	Air{


	CSV::CSV()
	{
		m_uiLineCount	=	0;
		m_uiRowCount	=	0;
	}

	CSV::~CSV()
	{

	}

	Air::U1 CSV::Load( CAString& strName )
	{
		
		if(Common::File::Load(strName,m_Data)){
			return Load(m_Data.buff,m_Data.size);
		}
		return false;
	}

	Air::U1 CSV::Load( void* pData,U32 uiSize )
	{
		STD_VECTOR<AChar*>	vecString;
		vecString.reserve(1024);

		U32 uiLastItem=0;
		AChar*	pString	=	(AChar*)pData;
		for(U32 i=0;i<uiSize;i++){
			if(pString[i] == ','){
				pString[i]=0;
				CSVItem item;
				item.pStr	=	&pString[uiLastItem];
				m_vecItem.push_back(item);
				uiLastItem=i+1;
			}
			
			if(pString[i]==0x0d && pString[i+1]==0x0a){
				pString[i]=0;
				pString[i+1]=0;
				CSVItem item;
				item.pStr	=	&pString[uiLastItem];
				m_vecItem.push_back(item);
				uiLastItem=i+2;

				m_uiLineCount++;
			}
		}
		m_uiRowCount	=	m_vecItem.size()/m_uiLineCount;

		return true;
	}

	CSVItem CSV::GetItem( U32 X,U32 Y )
	{
		return m_vecItem[m_uiRowCount*Y+X];
	}

	Air::U32 CSV::GetLineCount()
	{
		return m_uiLineCount;
	}

	Air::U32 CSV::GetRowCount()
	{
		return m_uiRowCount;
	}

	void CSV::Clear()
	{
		m_vecItem.clear();
		m_Data.Clear();
		m_uiRowCount=0;
		m_uiLineCount=0;
	}

}