// DumpReader.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "dbghelp.h"

#include <string>

#define WUNKNOWNSTR	_T("unknown Windows version")

#define W95STR		_T("Windows 95")
#define W95SP1STR	_T("Windows 95 SP1")
#define W95OSR2STR	_T("Windows 95 OSR2")
#define W98STR		_T("Windows 98")
#define W98SP1STR	_T("Windows 98 SP1")
#define W98SESTR	_T("Windows 98 SE")
#define WMESTR		_T("Windows ME")

#define WNT351STR	_T("Windows NT 3.51")
#define WNT4STR		_T("Windows NT 4")
#define W2KSTR		_T("Windows 2000")
#define WXPSTR		_T("Windows XP")
#define WVISTASTR	_T("Windows Vista")
#define W2003STR	_T("Windows Server 2003")

#define WCESTR		_T("Windows CE")

int GetWinVersion(
	DWORD dwPlatformId  ,
	DWORD dwMinorVersion,
	DWORD dwMajorVersion,
	DWORD dwBuildNumber
	)
{
	int nVersion = WUNKNOWN;

	//DWORD dwPlatformId   = m_osinfo.dwPlatformId;
	//DWORD dwMinorVersion = m_osinfo.dwMinorVersion;
	//DWORD dwMajorVersion = m_osinfo.dwMajorVersion;
	//DWORD dwBuildNumber  = m_osinfo.dwBuildNumber & 0xFFFF;	// Win 9x needs this

	if ((dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && (dwMajorVersion == 4))
	{
		if ((dwMinorVersion < 10) && (dwBuildNumber == 950))
		{
			nVersion = W95;
		}
		else if ((dwMinorVersion < 10) &&
			((dwBuildNumber > 950) && (dwBuildNumber <= 1080)))
		{
			nVersion = W95SP1;
		}
		else if ((dwMinorVersion < 10) && (dwBuildNumber > 1080))
		{
			nVersion = W95OSR2;
		}
		else if ((dwMinorVersion == 10) && (dwBuildNumber == 1998))
		{
			nVersion = W98;
		}
		else if ((dwMinorVersion == 10) &&
			((dwBuildNumber > 1998) && (dwBuildNumber < 2183)))
		{
			nVersion = W98SP1;
		}
		else if ((dwMinorVersion == 10) && (dwBuildNumber >= 2183))
		{
			nVersion = W98SE;
		}
		else if (dwMinorVersion == 90)
		{
			nVersion = WME;
		}
	}
	else if (dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if ((dwMajorVersion == 3) && (dwMinorVersion == 51))
		{
			nVersion = WNT351;
		}
		else if ((dwMajorVersion == 4) && (dwMinorVersion == 0))
		{
			nVersion = WNT4;
		}
		else if ((dwMajorVersion == 5) && (dwMinorVersion == 0))
		{
			nVersion = W2K;
		}
		else if ((dwMajorVersion == 5) && (dwMinorVersion == 1))
		{
			nVersion = WXP;
		}
		else if ((dwMajorVersion == 5) && (dwMinorVersion == 2))
		{
			nVersion = W2003;
		}
		else if ((dwMajorVersion == 6) && (dwMinorVersion == 0))
		{
			nVersion = WVISTA;
			//GetVistaProductType();
			//GetProductInfo(dwMajorVersion,dwMinorVersion,m_osinfo.wServicePackMajor,m_osinfo.wServicePackMinor,&m_dwVistaProductType);
		}
		else if ((dwMajorVersion == 6) && (dwMinorVersion == 1))
		{
			nVersion = WIN7;
			//GetProductInfo(dwMajorVersion,dwMinorVersion,m_osinfo.wServicePackMajor,m_osinfo.wServicePackMinor,&m_dwVistaProductType);
		}
		else if ((dwMajorVersion == 6) && (dwMinorVersion == 2))
		{
			nVersion = WIN8;
			//GetProductInfo(dwMajorVersion,dwMinorVersion,m_osinfo.wServicePackMajor,m_osinfo.wServicePackMinor,&m_dwVistaProductType);
		}
	}
	else// if (dwPlatformId == VER_PLATFORM_WIN32_CE)
	{
		nVersion = WCE;
	}

	return nVersion;
}
std::string GetWinVersionString(
	DWORD dwPlatformId  ,
	DWORD dwMinorVersion,
	DWORD dwMajorVersion,
	DWORD dwBuildNumber
	)
{
	std::string strVersion = WUNKNOWNSTR;

	int nVersion = GetWinVersion(dwPlatformId,dwMinorVersion,dwMajorVersion,dwBuildNumber);

	switch (nVersion)
	{
	default:
	case WUNKNOWN:								break;
	case W95:		strVersion = W95STR;		break;
	case W95SP1:	strVersion = W95SP1STR;		break;
	case W95OSR2:	strVersion = W95OSR2STR;	break;
	case W98:		strVersion = W98STR;		break;
	case W98SP1:	strVersion = W98SP1STR;		break;
	case W98SE:		strVersion = W98SESTR;		break;
	case WME:		strVersion = WMESTR;		break;
	case WNT351:	strVersion = WNT351STR;		break;
	case WNT4:		strVersion = WNT4STR;		break;
	case W2K:		strVersion = W2KSTR;		break;
	case WXP:		strVersion = WXPSTR;		break;
	case W2003:		strVersion = W2003STR;		break;
	case WVISTA:	strVersion = "Windows Vista/Windows Server 2008";	break;
	case WIN7:		strVersion = "Windows7/Windows Server 2008 R2";		break;
	case WIN8:		strVersion = "Windows8/Windows Server 2012";			break;
	case WCE:		strVersion = WCESTR;		break;
	}
	//SYSTEM_INFO	sysinfo;
	//GetNativeSystemInfo(&sysinfo);
	//switch(sysinfo.wProcessorArchitecture){
	//case PROCESSOR_ARCHITECTURE_INTEL        :{}break;
	//case PROCESSOR_ARCHITECTURE_MIPS         :{}break;
	//case PROCESSOR_ARCHITECTURE_ALPHA        :{}break;
	//case PROCESSOR_ARCHITECTURE_PPC          :{}break;
	//case PROCESSOR_ARCHITECTURE_SHX          :{}break;
	//case PROCESSOR_ARCHITECTURE_ARM          :{}break;
	//case PROCESSOR_ARCHITECTURE_IA64         :{}break;
	//case PROCESSOR_ARCHITECTURE_ALPHA64      :{}break;
	//case PROCESSOR_ARCHITECTURE_MSIL         :{}break;
	//case PROCESSOR_ARCHITECTURE_AMD64        :{}break;
	//}
	//if(IsX64()){
	//	strVersion	+=	"	64bit";
	//}else{
	//	strVersion	+=	"	32bit";
	//}
	return strVersion;
}

void mdmp_dump(void* pBase,unsigned int uiSize);

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc<2)
	{
		printf("Usage:DumpReader [*.dmp]\n");
		getchar();
		return -1;
	}
	printf("dump file name=[");
	printf(argv[1]);
	printf("]\n");
	//getchar();

	
	FILE* pFile =	fopen(argv[1],"rb");
	if(pFile==NULL){
		printf("open dump file failed!\n");
		getchar();
		return -2;
	}
	//MINIDUMP_HEADER header;
	//fread(&header,sizeof(header),1,pFile);
	fseek(pFile,0,SEEK_END);
	unsigned int uiSize	 = ftell(pFile);
	fseek(pFile,0,SEEK_SET);
	void* pBuffer = malloc(uiSize);
	fread(pBuffer,uiSize,1,pFile);
	fclose(pFile);

	mdmp_dump(pBuffer,uiSize);
	free(pBuffer);
	printf("------------------Finished!--------------\n");
	//getchar();
	return 0;
}

