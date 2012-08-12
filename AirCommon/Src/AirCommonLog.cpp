#include "AirCommonLog.h"
#include "AirCommonLock.h"
namespace Air{
	
	WORD	wMonthArray[]={
		0,
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};
	
	namespace	Common{
	
	
		Log::Log(){
			//m_uiLockCount	=	0;
			m_uiBuffSize	=	0;
			memset(m_pBuff,0,LOG_BUFF_SIZE);
			m_strProductName	=	"System.log";
			Create();
		}
	
		U1 Log::Create(){
			//追加方式打开文件
			FILE*	p	=	NULL;
			fopen_s(&p,m_strProductName.c_str(),"a+");
			if(p==NULL){
				SetFileAttributesA(m_strProductName.c_str(),FILE_ATTRIBUTE_NORMAL);
				fopen_s(&p,m_strProductName.c_str(),"a+");
				if(p==NULL){
					return	false;
				}
				
			}
			
			fclose(p);
			return true;
		}
	
		void Log::Write( CAString& strName ){
			if(strName.empty())
				return;
			AChar strTime[MAX_NAME];
			SYSTEMTIME	sysTime;
			//获取本地时间
			GetLocalTime(&sysTime);
			
			WORD	y	=	sysTime.wYear;
			WORD	m	=	sysTime.wMonth;
			WORD	d	=	sysTime.wDay;
			WORD	h	=	sysTime.wHour;
	
			//进入临界区
			m_CS.Enter();
	
	
		
			sprintf_s(strTime,MAX_NAME,"[%d-%d-%d %d:%d:%d]",
				y,
				m,
				d,
				h,
				sysTime.wMinute,
				sysTime.wSecond);
			AString	str	=	AString(strTime)	+	strName;
	
			
			UInt	uiSize	=	str.size()+1;
			memcpy(&m_pBuff[m_uiBuffSize],str.c_str(),uiSize-1);
			m_pBuff[m_uiBuffSize+uiSize-1]	=	'\n';
			m_uiBuffSize+=uiSize;
			//离开临界区
			m_CS.Leave();
			//if(m_uiBuffSize>=LOG_BUFF_SIZE/2){
				Write2File();
			//}
	
		}
	
		void Log::Write2File(){
			if(strlen(m_pBuff)==0)
				return;
	
			m_CS.Enter();
			//追加方式打开文件
			FILE*	p	=	NULL;
			fopen_s(&p,m_strProductName.c_str(),"a+");
			if(p==NULL){
				return;
			}
			fputs(m_pBuff,p);
			memset(m_pBuff,0,LOG_BUFF_SIZE);
			m_uiBuffSize=0;
	
			fclose(p);
			m_CS.Leave();
		}
	
		void Log::SetFileName(AString&	strFileName){
			m_CS.Enter();
			m_strProductName	=	strFileName;
			m_CS.Leave();
		}
	
		Log::~Log(){
			Write2File();
		}
	}
};