#include "Airslkreader.h"
#include <MMSystem.h>



void (*g_pfnSlkLoadingCallBack)( const char* pszString ) = NULL;
void OutputSlkLoadingMessage( char* pszString, ... )
{

	if( g_pfnSlkLoadingCallBack )
	{
		char TmpBuf[1024];
		va_list vl;

		//转换参数
		va_start(vl, pszString);
		vsnprintf_s(TmpBuf,1024,sizeof(TmpBuf)-1, pszString, vl);
		va_end(vl);

		g_pfnSlkLoadingCallBack(TmpBuf);
	}
	
}

//
#define Safe_Delete(x) {if(x){delete x;x=0;}}

//#ifdef _DEBUG
//	#pragma comment(lib, "..\\FileIO\\FileIOD.lib")
//#else
//	#pragma comment(lib, "..\\FileIO\\FileIO.lib")
//#endif;

using namespace std;

char g_szValueTemp[ 64000 ];
char g_szStringValueTemp[257];


CSlkReader::CSlkReader()
{
	m_iMaxLineNo = 0;
	m_pLastFindLine = 0;
	
}

CSlkReader::~CSlkReader()
{
	FreeAll();
	
}

void CSlkReader::FreeLine(SLine*pLine)
{	
	;
	//CSALocker locker(this->m_csAccess);
	SField *pField;
	for( unsigned int i = 0 ; i < pLine->vector.size(); i ++ )
	{	
		pField = (pLine->vector[i]);
		if( !pField )
			continue;
		if( field_string == pField->iFieldType )
		{
			delete[] pField->data.szValue;
		}
		delete pField;
	}
	pLine->vector.clear();
	
}

void CSlkReader::FreeAll(void)
{
	;
	//CSALocker locker(this->m_csAccess);
	listLine::iterator it;
	for ( it = m_list.begin(); it != m_list.end(); it++ )
	{
		FreeLine( (*it) );
		delete( *it );
	}
	m_list.clear();
	//while( it != m_list.end() )
	//{
	//	FreeLine( (*it) );
	//	delete( *it );
	//	m_list.pop_front();
	//	
	//	it = m_list.begin();
	//}	
	m_iMaxLineNo = 0;
	m_mapIndex.clear();
	m_mapFiledNameToId.clear();
	m_pLastFindLine = NULL;
	
}



char *CSlkReader::GetFieldValue( char *szString,CSlkReader::SField &field )
{
	;
	//CSALocker locker(this->m_csAccess);
	char *pcFind;
	int iSize;
	char *pcRead,*pcWrite;;
	bool bIsString = false;
	if( '"' == szString[0] )
		bIsString = true;
	pcFind = strchr( szString,'\r');
	if( pcFind )
	{
		iSize = (int)(pcFind - szString);
		g_szValueTemp[ iSize ] = 0;
		if( bIsString )
		{
			field.iFieldType = field_string;
			bool bFinish = false;
			memcpy(g_szValueTemp,szString, min(iSize, sizeof(g_szValueTemp)));
			pcRead = g_szValueTemp;

			//skip "
			pcRead ++;

			pcWrite = g_szStringValueTemp;
			while( !bFinish )
			{
				switch( *pcRead ) 
				{
				case 0:
					bFinish = true;
					break;
				case '\x1b':
					if( pcRead[1] == '\x20' 
						&& pcRead[2] == '\x3a' )
					{
						pcRead += 3;
						pcWrite[0] = '\r';
						pcWrite[1] = '\n';
						pcWrite += 2;
					}
					else
					{
						pcWrite[0] = pcRead[0];
						pcWrite++;
						pcRead ++;
					}
					break;
				case ';':
					if( pcRead[1] == ';' )
					{
						pcRead += 2;
						pcWrite[0] = ';';
						pcWrite ++;
					}
					else
					{
						pcWrite[0] = pcRead[0];
						pcWrite++;
						pcRead ++;
					}
					break;				
				default:
					pcWrite[0] = pcRead[0];
					pcWrite++;
					pcRead ++;
					break;
				}
			}
			//skip "
			if( pcWrite[-1] == '"' )
				pcWrite[-1] = 0;
			//*(pcWrite - 1) = 0;
			Safe_Delete(field.data.szValue);
			//if( field.data.szValue )
			//	delete[] field.data.szValue;
			unsigned int uiSize	=	strlen(g_szStringValueTemp ) + 1;
			field.data.szValue = new char[uiSize ];
			strcpy_s( field.data.szValue,uiSize,g_szStringValueTemp );

		}
		else
		{
			memcpy(g_szValueTemp, szString, min((pcFind-szString), sizeof(g_szValueTemp)));
			if( strchr( g_szValueTemp,'.') )
			{
				field.iFieldType = field_float;
				field.data.fValue = (float)atof( g_szValueTemp );
			}
			else
			{
				field.iFieldType = field_int;
				field.data.iValue = atoi( g_szValueTemp );
			}
		}

	}
	return pcFind + 1;
	
}

char* CSlkReader::GetRowOrLineNO(char *szString,int &iValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	char *pcFind;
	int iRet  = (int)strcspn( szString,";\r\n");
	if( iRet == 0 )
		return 0;
	pcFind = szString;
	pcFind += iRet;

	if( pcFind )
	{
		g_szValueTemp[ (pcFind - szString) ] = 0;
		memcpy(g_szValueTemp, szString, min((pcFind-szString), sizeof(g_szValueTemp)) );
		iValue = atoi( g_szValueTemp );
		return pcFind;
	}
	
	return 0;
	
}

CSlkReader::SLine *CSlkReader::FindLine( int iLine,bool bAddIfNotFound )
{
	;
	//CSALocker locker(this->m_csAccess);
	/*listLine::iterator it;
	for( it = m_list.begin() ; it != m_list.end() ; it ++ )
	{
		if( (*it)->iLineNo == iLine )
		{
			return &( *it );
		}
		if( (*it)->iLineNo > iLine )
			break;
	}*/

	if( m_pLastFindLine )
	{
		if( m_pLastFindLine->iLineNo == iLine )
			return m_pLastFindLine;
	}

	mapLine::iterator itFind;
	itFind = m_mapIndex.find( iLine );
	if( itFind != m_mapIndex.end() )
	{
		m_pLastFindLine = (*itFind).second;
		return m_pLastFindLine;
	}
	if( !bAddIfNotFound )
		return 0;
	SLine* pLine = new SLine;
	if( !pLine )
		return 0;
	pLine->iLineNo = iLine;
	//m_list.insert( it,pLine );
	m_list.push_back( pLine );
	if( iLine > m_iMaxLineNo )
		m_iMaxLineNo = iLine;
	m_mapIndex.insert( mapLine::value_type( iLine,pLine ) );
	m_pLastFindLine = pLine;
	return m_pLastFindLine;
	
}

int	 CSlkReader::FindFirstLineByIntField( int iFieldNo,int iValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	for (int i=0; i<m_iMaxLineNo; i++)
	{
		if (ret_succ == GotoNextLine(i))
		{
			int val = 0;
			if (GetIntField(iFieldNo, val))
			{
				if (iValue == val)
				{
					return i;
				}
			}
		}
	}
	return -1;
	

}

int	 CSlkReader::FindLineByIntField( int iFieldNo,int iValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	listLine::iterator it;
	
	SField *pFieldLocal;
	for( it = m_list.begin() ; it != m_list.end() ; it ++ )
	{
		m_pCurGetLine = (*it);
		pFieldLocal = GetFieldOfLine( iFieldNo );
		if( !pFieldLocal )
			continue;
		if( field_int != pFieldLocal->iFieldType )
			continue;
		if( pFieldLocal->data.iValue != iValue )
			continue;
		return m_pCurGetLine->iLineNo;
	}
	return -1;
	
}

void CSlkReader::SetValue( CSlkReader::SLine *pLine,int iX,SField &field  )
{
	;
	//CSALocker locker(this->m_csAccess);
	if( !pLine )
		return;
	SField *pField = 0;

	int iSize =  (int)pLine->vector.size();	

	if( iSize < iX + 1 )
	{
		for( int i = iSize ; i <= iX ; i ++ )
		{
			pLine->vector.push_back( NULL );
		}
	}
	pField = new SField;
	*pField = field;

	Safe_Delete(pLine->vector[ iX ]);
	

	pLine->vector[ iX ] = pField;
	
}

bool CSlkReader::ReadFromFile( const char *szFile )
{
	//CSALocker locker(this->m_csAccess);

// 	if( g_SlkVFS.IsOpen() )
// 	{
// 		DWORD dwBuffer = 0;
// 	
// 		size_t size = 0;
// 		if (!g_SlkVFS.GetUnitLength(szFile, size))
// 		{
// 			return FALSE;
// 		}
// 		unsigned char *pbyMemory = new unsigned char[size];
// 		if (!g_SlkVFS.GetUnit(szFile, pbyMemory, size))
// 		{
// 			delete[] pbyMemory;
// 			pbyMemory = NULL;
// 			return FALSE;
// 		}
// 	//	dwSize = size;
// 
// 		ReadFromString( (char*)pbyMemory, size );
// 		InitFiledName();
// 
// 		delete []pbyMemory;
// 		pbyMemory =NULL;
// 
// 		return TRUE;
// 	}

	FILE *fp=NULL;
	fopen_s(&fp, szFile,"rb" );
	if( !fp )
		return false;
	DWORD dwSize;
	char *szBuf;
	fseek( fp,0,SEEK_END );
	dwSize = ftell(fp);
	fseek( fp,0,SEEK_SET );
	szBuf = new char[ dwSize + 1 ];

	if( !szBuf )
	{
		fclose( fp );
		return false;
	}
	szBuf[ dwSize ] = 0;
	bool bRet = false;
	if( 1 ==fread( szBuf,dwSize,1,fp ) )
	{
		bRet = ReadFromString( szBuf,dwSize );
	}	

	delete[] szBuf;
	fclose(fp);

	//if( stricmp( szFile, "slk\\weapon.slk" ) == 0 )
	//{
	//	int k = 0;
	//}
	InitFiledName();

	return bRet;
	

}

bool CSlkReader::ReadFromString( char *szString,int iSize )
{
	;
	//CSALocker locker(this->m_csAccess);
	bool bIsInString = false;
	FreeAll();
	int iYValue = 0;
	int iXValue = 0;

	char *pcChar = szString;
	char *pcNext = 0;
	SLine *pCurLine = 0;	
	bool bNewLine = true;
	bool bValueLine = false;
	
	//int nTimes = 0;
	DWORD dwTime = timeGetTime();
	int d = 0;
	while( 0 != pcChar && 0 != *pcChar)
	{
		if( timeGetTime()-dwTime > 200 )
		{
			dwTime = timeGetTime();
			switch( d++%4 )
			{
			case 0:
				OutputSlkLoadingMessage("/L分析");
				break;
			case 1:
				OutputSlkLoadingMessage("/L分析.");
				break;
			case 2:
				OutputSlkLoadingMessage("/L分析..");
				break;
			case 3:
				OutputSlkLoadingMessage("/L分析...");
				break;
			}
		}
		if( pcChar - szString >= iSize )
			break;		
		if( bNewLine )
		{
			if( ( 'c' == pcChar[0] || 'C' == pcChar[0] )
				&& ( ';' == pcChar[1]  ) )
			{
				bValueLine = true;
			}
			else
				bValueLine = false;
		}
		bNewLine = false;

		switch( *pcChar ) 
		{
		case ';':	
			pcChar ++;
			switch( *pcChar )
			{
			case 'X':
				{
					pcNext = GetRowOrLineNO( pcChar + 1,iXValue );

					pcChar = pcNext;
				}
				break;
			case 'Y':
				{
					pcNext = GetRowOrLineNO( pcChar + 1,iYValue );
					if( pcNext )
					{
						pCurLine = FindLine( iYValue );
					}
					pcChar = pcNext;
				}
				break;
			case 'K':
				{
					//查看
					if( !bValueLine )
					{
						pcChar ++;
						break;
					}
					//数值
					SField field;
					pcNext = GetFieldValue( pcChar + 1,field );
					if( pcNext )
					{
						SetValue( pCurLine,iXValue,field );
					}
					pcChar = pcNext;
				}
				break;
			case ';':
				pcChar ++;
				break;
			default:
				break;
			}
			break;		
		case '\n':
			bNewLine = true;
			pcChar ++;
			break;
		default:
			pcChar ++;
			break;
		}
	}
	
	ClearBlankRow();

	m_pCurGetLine = FindLine( 0,false );
	
	return true;
	
}

int		CSlkReader::GetFieldNumOfLine(void)
{
	;
	//CSALocker locker(this->m_csAccess);
	if( !m_pCurGetLine )	
		return 0;
	return (int)m_pCurGetLine->vector.size();
	
}

CSlkReader::SField *CSlkReader::GetFieldOfLine( int iFieldNo )
{
	;
	//CSALocker locker(this->m_csAccess);
	if( !m_pCurGetLine )	
		return 0;
	if( iFieldNo >= (int)m_pCurGetLine->vector.size() )
		return 0;
	SField *pField = m_pCurGetLine->vector[ iFieldNo ];
	if( !pField )
		return 0;
	return pField;
	
}

int CSlkReader::GotoNextLine( int iLine )
{
	;
	//CSALocker locker(this->m_csAccess);
	if( iLine > m_iMaxLineNo )
		return ret_readover;
	m_pCurGetLine = FindLine( iLine,false );
	if(m_pCurGetLine != 0)
		return ret_succ;	
	return ret_nothisline;
	
}

void CSlkReader::OutDebugLine(SLine*pLine,FILE *fp)
{
	;
	//CSALocker locker(this->m_csAccess);
	SField *pField = NULL;
	for( int i = 0 ; i < (int)pLine->vector.size(); i ++ )
	{	
		pField = (pLine->vector[i]);
		if( !pField )
			continue;
		fprintf( fp,"(%d,%d)  :",i,pLine->iLineNo);
		switch( pField->iFieldType ) 
		{
		case field_string:
			fprintf( fp,"%s",pField->data.szValue );
			break;
		case field_int:
			fprintf( fp,"%d",pField->data.iValue );
			break;
		case field_float:
			fprintf( fp,"%f",pField->data.fValue );
			break;		
		}
		fprintf( fp,"\r\n");
	}

	
}

void CSlkReader::OutDebugInfo(void)
{
	;
	listLine::iterator it = m_list.begin();
	FILE *fp	=	NULL;
	fopen_s(&fp, "slkinfo.txt","ab" );
	fprintf( fp,"\r\n\r\nbegin info log:\r\n" );
	while( it != m_list.end() )
	{
		OutDebugLine( (*it),fp );	

		it ++;
	}	
	fclose( fp );
	
}

bool CSlkReader::GetIntField( int iCol,int &iValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	//
	SField *pField;
	//
	//
	pField = GetFieldOfLine( iCol );
	if( !pField )
		return false;
	switch( pField->iFieldType )
	{
	case CSlkReader::field_int: 
		iValue = pField->data.iValue;
		break;
	case CSlkReader::field_float: 
		return false;
		break;
	case CSlkReader::field_string:
		return false;		
	}	
	return true;
	
}

bool CSlkReader::GetFloatField( int iCol, float &fValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	SField *pField;
	pField = GetFieldOfLine( iCol );
	if(!pField)
		return false;
	switch( pField->iFieldType )
	{
	case CSlkReader::field_int:
		fValue = (float)(pField->data.iValue);
		break;
	case CSlkReader::field_float:
		fValue = pField->data.fValue;
		break;
	case CSlkReader::field_string:
		return false;
	}
	return true;
	
}

bool CSlkReader::GetStringField( int iCol,string& strRetValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	CSlkReader::SField *pField;
	pField = GetFieldOfLine( iCol );
	if( !pField )
		return false;
	if( CSlkReader::field_string != pField->iFieldType )
		return false;
	if( !pField->data.szValue )
		return false;
	strRetValue = pField->data.szValue;
	return true;
	
}

bool CSlkReader::GetStringField( int iCol,char **pstrRetValue,CFlyMemAllocer*pAllocer )
{
	;
	//CSALocker locker(this->m_csAccess);
	int iStringSize;
	CSlkReader::SField *pField;
	pField = GetFieldOfLine( iCol );
	if( !pField )
		return false;
	if( CSlkReader::field_string != pField->iFieldType )
		return false;
	if( !pField->data.szValue )
		return false;
	iStringSize = strlen( pField->data.szValue );	
// 	if(!(*pstrRetValue))
// 		(*pstrRetValue) = (char*)pAllocer->Malloc( iStringSize + 1 );
	if( !(*pstrRetValue) )
		return false;
	strcpy_s( (*pstrRetValue),iStringSize,pField->data.szValue );
	return true;
	
}

//////////////////////////////////////////////////////////////////////////
int CSlkReader::ConvHeaderToId( const char* pszCol )
{
	;
	//CSALocker locker(this->m_csAccess);
	if( !pszCol )
	{
		assert( false && "slk reader conv header to id error, col is null" );
		return -1;
	}
	char c = pszCol[0];
	if( c >= 'a' && c <= 'z' ) 
		return c-'a'+1;
	if( c >= 'A' && c <= 'Z')
		return c-'A'+1;
	assert( false && "slk reader conv header to id error, invalid col" );
	return -1;

	
}
bool CSlkReader::GetIntField( const char* pszCol,int &iValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetIntField( nCol, iValue );
	
}
//读取string
bool CSlkReader::GetStringField( const char* pszCol,std::string& pstrRetValue)
{
	;
	//CSALocker locker(this->m_csAccess);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetStringField( nCol, pstrRetValue );
	
}
//读取string
bool CSlkReader::GetStringField( const char* pszCol,char **pstrRetValue,CFlyMemAllocer*pAllocer )
{
	;
	//CSALocker locker(this->m_csAccess);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetStringField( nCol, pstrRetValue, pAllocer );
	
}
//读取浮点
bool CSlkReader::GetFloatField( const char* pszCol, float &fValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetFloatField( nCol, fValue );
	
}

//////////////////////////////////////////////////////////////////////////


void CSlkReader::ClearBlankRow(void)
{
	;
	//CSALocker locker(this->m_csAccess);
	listLine::iterator it,itNext;

	SLine *pLine;
	//SField *pFieldLocal;
	for( it = m_list.begin() ; it != m_list.end() ; )
	{	

		itNext = it;
		itNext ++;
		pLine = (*it);
		if( 0 == pLine->vector.size() )
		{
			if( m_pLastFindLine == pLine )
				m_pLastFindLine = 0;
			m_list.erase( it );
			//清除索引
			mapLine::iterator itFind = m_mapIndex.find( pLine->iLineNo );
			m_mapIndex.erase( itFind );
			delete pLine;
		}

		it = itNext;
	}
	
}

void CSlkReader::InitFiledName()
{
	;
	//CSALocker locker(this->m_csAccess);
    GotoNextLine( 1 );

    for( int i=0; i<=256; i++ )
    {
        std::string tempName;
        if( !GetStringField( i, tempName ) )
            continue;
        m_mapFiledNameToId.insert( std::map<std::string,int>::value_type( tempName, i ) );
		OutputSlkLoadingMessage( "    字段[%s]", tempName.c_str() );
	}
	
}

int CSlkReader::GetFiledNameID( const char * strName )
{
	;
	//CSALocker locker(this->m_csAccess);
    std::string strFiledName = strName;
    std::map<std::string,int>::iterator itr = m_mapFiledNameToId.find( strFiledName );
    if( itr != m_mapFiledNameToId.end() )
        return itr->second;
	return -1;
	
}

bool CSlkReader::GetIntFieldByName( const char* pszColName,int &iValue )
{
	;
	//CSALocker locker(this->m_csAccess);
	iValue = 0;
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
	{
		//assert(false);
        return false;
	}
    
	return GetIntField( iCol, iValue );
	
}
//bool CSlkReader::GetIntFieldByName( const char* pszColName,short &shValue )
//{
//	int nValue = 0;
//	if( GetIntFieldByName( pszColName, nValue ) )
//	{
//		shValue = nValue;
//		return true;
//	}
//	return false;
//}
//读取string
bool CSlkReader::GetStringFieldByName( const char* pszColName,std::string& pstrRetValue)
{
	;
	//CSALocker locker(this->m_csAccess);
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
        return false;
	return GetStringField( iCol, pstrRetValue );
	
}
//读取string
bool CSlkReader::GetStringFieldByName( const char* pszColName,char **pstrRetValue,CFlyMemAllocer*pAllocer )
{
	;
	//CSALocker locker(this->m_csAccess);
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
        return false;
	return GetStringField( iCol, pstrRetValue, pAllocer );
	
}
//读取浮点
bool CSlkReader::GetFloatFieldByName( const char* pszColName, float &fValue )
{
	;
	//CSALocker locker(this->m_csAccess);
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
        return false;
	return GetFloatField( iCol, fValue );
	
}