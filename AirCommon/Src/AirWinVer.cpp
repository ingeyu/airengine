// XWinVer.cpp  Version 1.2
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// Description:
//     XWinVer implements CXWinVersion, a singleton class to retrieve
//     the Windows OS version.  Please see article at 
//     www.codeproject.com.
//
// History
//     Version 1.1 - 2005 March 14
//     - Initial public release
//
//     Version 1.2 - 2007 June 7
//     - Added IsVista(), IsVistaXXXXX()
//     - Added GetVistaProductString()
//     - Added GetVistaProductType()
//     - Added GetPlatformId()
//     - Added IsMediaCenter()
//     - Added IsWin95()
//     - Added IsWin98()
//     - Added IsWinCE()
//
// Public APIs:
//             NAME                             DESCRIPTION
//     ---------------------   -------------------------------------------------
//     GetMajorVersion()       Get major version number
//     GetMinorVersion()       Get minor version number
//     GetBuildNumber()        Get build number (ANDed with 0xFFFF for Win9x)
//     GetServicePackNT()      Get service pack number
//     GetPlatformId()         Get platform id
//     GetServicePackString()  Get service pack string
//     GetVistaProductString() Get Vista product string (e.g., "Business Edition")
//     GetVistaProductType()   Get Vista product type
//     GetWinVersion()         Get windows version (CXWinVersion code)
//     GetWinVersionString()   Get windows version as string
//     IsMediaCenter()         TRUE = Media Center Edition
//     IsWin95()               TRUE = Win95
//     IsWin98()               TRUE = Win98
//     IsWin2KorLater()        TRUE = Win2000 or later
//     IsWin2003()             TRUE = Win2003
//     IsWinCE()               TRUE = WinCE
//     IsXP()                  TRUE = XP
//     IsXPorLater()           TRUE = XP or later
//     IsXPHome()              TRUE = XP Home
//     IsXPPro()               TRUE = XP Pro
//     IsXPSP2()               TRUE = XP SP2
//     IsVista()               TRUE = Vista
//     IsVistaHome()           TRUE = Vista Home
//     IsVistaBusiness()       TRUE = Vista Business
//     IsVistaEnterprise()     TRUE = Vista Enterprise
//     IsVistaUltimate()       TRUE = Vista Ultimate
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////


#define XWINVER_CPP
#include "AirWinVer.h"

// from winbase.h
#ifndef VER_PLATFORM_WIN32_WINDOWS
#define VER_PLATFORM_WIN32_WINDOWS      1
#endif
#ifndef VER_PLATFORM_WIN32_NT
#define VER_PLATFORM_WIN32_NT           2
#endif
#ifndef VER_PLATFORM_WIN32_CE
#define VER_PLATFORM_WIN32_CE           3
#endif
// from winnt.h
#ifndef VER_NT_WORKSTATION
#define VER_NT_WORKSTATION              0x0000001
#endif
#ifndef VER_SUITE_PERSONAL
#define VER_SUITE_PERSONAL              0x00000200
#endif


///////////////////////////////////////////////////////////////////////////////
/*
    This table has been assembled from Usenet postings, personal
    observations, and reading other people's code.  Please feel
    free to add to it or correct it.


         dwPlatFormID  dwMajorVersion  dwMinorVersion  dwBuildNumber
95             1              4               0             950
95 SP1         1              4               0        >950 && <=1080
95 OSR2        1              4             <10           >1080
98             1              4              10            1998
98 SP1         1              4              10       >1998 && <2183
98 SE          1              4              10          >=2183
ME             1              4              90            3000

NT 3.51        2              3              51            1057
NT 4           2              4               0            1381
2000           2              5               0            2195
XP             2              5               1            2600
2003           2              5               2            3790
Vista          2              6               0

CE 1.0         3              1               0
CE 2.0         3              2               0
CE 2.1         3              2               1
CE 3.0         3              3               0
*/

///////////////////////////////////////////////////////////////////////////////
//  per process data
BOOL CXWinVersion::m_bInitialized = FALSE;
CXWinVersion::OSVERSIONINFOEXX CXWinVersion::m_osinfo = { 0 };
DWORD CXWinVersion::m_dwVistaProductType = 0;

///////////////////////////////////////////////////////////////////////////////
// Init
void CXWinVersion::Init()
{


	m_dwVistaProductType = 0;

	ZeroMemory(&m_osinfo, sizeof(m_osinfo));

	m_osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if (GetVersionEx((LPOSVERSIONINFO) &m_osinfo))
	{
		m_bInitialized = TRUE;

		if ((m_osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
			(m_osinfo.dwMajorVersion >= 5))
		{
			// get extended version info for 2000 and later

			ZeroMemory(&m_osinfo, sizeof(m_osinfo));

			m_osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

			GetVersionEx((LPOSVERSIONINFO) &m_osinfo);

// 			TRACE(_T("dwMajorVersion =%u\n"), m_osinfo.dwMajorVersion );
// 			TRACE(_T("dwMinorVersion =%u\n"), m_osinfo.dwMinorVersion );
// 			TRACE(_T("dwBuildNumber=%u\n"), m_osinfo.dwBuildNumber);
// 			TRACE(_T("suite mask=%u\n"), m_osinfo.wSuiteMask);
// 			TRACE(_T("product type=%u\n"), m_osinfo.wProductType);
// 			TRACE(_T("sp major=%u\n"), m_osinfo.wServicePackMajor);
// 			TRACE(_T("sp minor=%u\n"), m_osinfo.wServicePackMinor);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// GetWinVersionString
Air::AString CXWinVersion::GetWinVersionString()
{
	Air::AString strVersion = WUNKNOWNSTR;

	int nVersion = GetWinVersion();

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
	if(IsX64()){
		strVersion	+=	"	64bit";
	}else{
		strVersion	+=	"	32bit";
	}
	switch(m_dwVistaProductType){
	case PRODUCT_ULTIMATE                           : {strVersion+=" ULTIMATE						   ";}break;
	case PRODUCT_HOME_BASIC                         : {strVersion+=" HOME_BASIC						   ";}break;
	case PRODUCT_HOME_PREMIUM                       : {strVersion+=" HOME_PREMIUM					   ";}break;
	case PRODUCT_ENTERPRISE                         : {strVersion+=" ENTERPRISE						   ";}break;
	case PRODUCT_HOME_BASIC_N                       : {strVersion+=" HOME_BASIC_N					   ";}break;
	case PRODUCT_BUSINESS                           : {strVersion+=" BUSINESS						   ";}break;
	case PRODUCT_STANDARD_SERVER                    : {strVersion+=" STANDARD_SERVER				   ";}break;
	case PRODUCT_DATACENTER_SERVER                  : {strVersion+=" DATACENTER_SERVER				   ";}break;
	case PRODUCT_SMALLBUSINESS_SERVER               : {strVersion+=" SMALLBUSINESS_SERVER              ";}break;
	case PRODUCT_ENTERPRISE_SERVER                  : {strVersion+=" ENTERPRISE_SERVER                 ";}break;
	case PRODUCT_STARTER                            : {strVersion+=" STARTER                           ";}break;
	case PRODUCT_DATACENTER_SERVER_CORE             : {strVersion+=" DATACENTER_SERVER_CORE            ";}break;
	case PRODUCT_STANDARD_SERVER_CORE               : {strVersion+=" STANDARD_SERVER_CORE              ";}break;
	case PRODUCT_ENTERPRISE_SERVER_CORE             : {strVersion+=" ENTERPRISE_SERVER_CORE            ";}break;
	case PRODUCT_ENTERPRISE_SERVER_IA64             : {strVersion+=" ENTERPRISE_SERVER_IA64            ";}break;
	case PRODUCT_BUSINESS_N                         : {strVersion+=" BUSINESS_N                        ";}break;
	case PRODUCT_WEB_SERVER                         : {strVersion+=" WEB_SERVER                        ";}break;
	case PRODUCT_CLUSTER_SERVER                     : {strVersion+=" CLUSTER_SERVER                    ";}break;
	case PRODUCT_HOME_SERVER                        : {strVersion+=" HOME_SERVER                       ";}break;
	case PRODUCT_STORAGE_EXPRESS_SERVER             : {strVersion+=" STORAGE_EXPRESS_SERVER            ";}break;
	case PRODUCT_STORAGE_STANDARD_SERVER            : {strVersion+=" STORAGE_STANDARD_SERVER           ";}break;
	case PRODUCT_STORAGE_WORKGROUP_SERVER           : {strVersion+=" STORAGE_WORKGROUP_SERVER          ";}break;
	case PRODUCT_STORAGE_ENTERPRISE_SERVER          : {strVersion+=" STORAGE_ENTERPRISE_SERVER         ";}break;
	case PRODUCT_SERVER_FOR_SMALLBUSINESS           : {strVersion+=" SERVER_FOR_SMALLBUSINESS          ";}break;
	case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM       : {strVersion+=" SMALLBUSINESS_SERVER_PREMIUM      ";}break;
	case PRODUCT_HOME_PREMIUM_N                     : {strVersion+=" HOME_PREMIUM_N                    ";}break;
	case PRODUCT_ENTERPRISE_N                       : {strVersion+=" ENTERPRISE_N                      ";}break;
	case PRODUCT_ULTIMATE_N                         : {strVersion+=" ULTIMATE_N                        ";}break;
	case PRODUCT_WEB_SERVER_CORE                    : {strVersion+=" WEB_SERVER_CORE                   ";}break;
	case PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT   : {strVersion+=" MEDIUMBUSINESS_SERVER_MANAGEMENT  ";}break;
	case PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY     : {strVersion+=" MEDIUMBUSINESS_SERVER_SECURITY    ";}break;
	case PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING    : {strVersion+=" MEDIUMBUSINESS_SERVER_MESSAGING   ";}break;
	case PRODUCT_SERVER_FOUNDATION                  : {strVersion+=" SERVER_FOUNDATION                 ";}break;
	case PRODUCT_HOME_PREMIUM_SERVER                : {strVersion+=" HOME_PREMIUM_SERVER               ";}break;
	case PRODUCT_SERVER_FOR_SMALLBUSINESS_V         : {strVersion+=" SERVER_FOR_SMALLBUSINESS_V        ";}break;
	case PRODUCT_STANDARD_SERVER_V                  : {strVersion+=" STANDARD_SERVER_V                 ";}break;
	case PRODUCT_DATACENTER_SERVER_V                : {strVersion+=" DATACENTER_SERVER_V               ";}break;
	case PRODUCT_ENTERPRISE_SERVER_V                : {strVersion+=" ENTERPRISE_SERVER_V               ";}break;
	case PRODUCT_DATACENTER_SERVER_CORE_V           : {strVersion+=" DATACENTER_SERVER_CORE_V          ";}break;
	case PRODUCT_STANDARD_SERVER_CORE_V             : {strVersion+=" STANDARD_SERVER_CORE_V            ";}break;
	case PRODUCT_ENTERPRISE_SERVER_CORE_V           : {strVersion+=" ENTERPRISE_SERVER_CORE_V          ";}break;
	case PRODUCT_HYPERV                             : {strVersion+=" HYPERV                            ";}break;
	case PRODUCT_STORAGE_EXPRESS_SERVER_CORE        : {strVersion+=" STORAGE_EXPRESS_SERVER_CORE       ";}break;
	case PRODUCT_STORAGE_STANDARD_SERVER_CORE       : {strVersion+=" STORAGE_STANDARD_SERVER_CORE      ";}break;
	case PRODUCT_STORAGE_WORKGROUP_SERVER_CORE      : {strVersion+=" STORAGE_WORKGROUP_SERVER_CORE     ";}break;
	case PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE     : {strVersion+=" STORAGE_ENTERPRISE_SERVER_CORE    ";}break;
	case PRODUCT_STARTER_N                          : {strVersion+=" STARTER_N                         ";}break;
	case PRODUCT_PROFESSIONAL                       : {strVersion+=" PROFESSIONAL                      ";}break;
	case PRODUCT_PROFESSIONAL_N                     : {strVersion+=" PROFESSIONAL_N                    ";}break;
	case PRODUCT_SB_SOLUTION_SERVER                 : {strVersion+=" SB_SOLUTION_SERVER                ";}break;
	case PRODUCT_SERVER_FOR_SB_SOLUTIONS            : {strVersion+=" SERVER_FOR_SB_SOLUTIONS           ";}break;
	case PRODUCT_STANDARD_SERVER_SOLUTIONS          : {strVersion+=" STANDARD_SERVER_SOLUTIONS         ";}break;
	case PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE     : {strVersion+=" STANDARD_SERVER_SOLUTIONS_CORE    ";}break;
	case PRODUCT_SB_SOLUTION_SERVER_EM              : {strVersion+=" SB_SOLUTION_SERVER_EM             ";}break;
	case PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM         : {strVersion+=" SERVER_FOR_SB_SOLUTIONS_EM        ";}break;
	case PRODUCT_SOLUTION_EMBEDDEDSERVER            : {strVersion+=" SOLUTION_EMBEDDEDSERVER           ";}break;
	case PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE       : {strVersion+=" SOLUTION_EMBEDDEDSERVER_CORE      ";}break;
	case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE  : {strVersion+=" SMALLBUSINESS_SERVER_PREMIUM_CORE ";}break;
	case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT      : {strVersion+=" ESSENTIALBUSINESS_SERVER_MGMT     ";}break;
	case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL      : {strVersion+=" ESSENTIALBUSINESS_SERVER_ADDL     ";}break;
	case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC   : {strVersion+=" ESSENTIALBUSINESS_SERVER_MGMTSVC  ";}break;
	case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC   : {strVersion+=" ESSENTIALBUSINESS_SERVER_ADDLSVC  ";}break;
	case PRODUCT_CLUSTER_SERVER_V                   : {strVersion+=" CLUSTER_SERVER_V                  ";}break;
	case PRODUCT_EMBEDDED                           : {strVersion+=" EMBEDDED                          ";}break;
	case PRODUCT_STARTER_E                          : {strVersion+=" STARTER_E                         ";}break;
	case PRODUCT_HOME_BASIC_E                       : {strVersion+=" HOME_BASIC_E                      ";}break;
	case PRODUCT_HOME_PREMIUM_E                     : {strVersion+=" HOME_PREMIUM_E                    ";}break;
	case PRODUCT_PROFESSIONAL_E                     : {strVersion+=" PROFESSIONAL_E                    ";}break;
	case PRODUCT_ENTERPRISE_E                       : {strVersion+=" ENTERPRISE_E                      ";}break;
	case PRODUCT_ULTIMATE_E                         : {strVersion+=" ULTIMATE_E                        ";}break;
	}
	return strVersion;
}

///////////////////////////////////////////////////////////////////////////////
// GetWinVersion
int CXWinVersion::GetWinVersion()
{
	int nVersion = WUNKNOWN;

	DWORD dwPlatformId   = m_osinfo.dwPlatformId;
	DWORD dwMinorVersion = m_osinfo.dwMinorVersion;
	DWORD dwMajorVersion = m_osinfo.dwMajorVersion;
	DWORD dwBuildNumber  = m_osinfo.dwBuildNumber & 0xFFFF;	// Win 9x needs this

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
			GetProductInfo(dwMajorVersion,dwMinorVersion,m_osinfo.wServicePackMajor,m_osinfo.wServicePackMinor,&m_dwVistaProductType);
		}
		else if ((dwMajorVersion == 6) && (dwMinorVersion == 1))
		{
			nVersion = WIN7;
			GetProductInfo(dwMajorVersion,dwMinorVersion,m_osinfo.wServicePackMajor,m_osinfo.wServicePackMinor,&m_dwVistaProductType);
		}
		else if ((dwMajorVersion == 6) && (dwMinorVersion == 2))
		{
			nVersion = WIN8;
			GetProductInfo(dwMajorVersion,dwMinorVersion,m_osinfo.wServicePackMajor,m_osinfo.wServicePackMinor,&m_dwVistaProductType);
		}
	}
	else if (dwPlatformId == VER_PLATFORM_WIN32_CE)
	{
		nVersion = WCE;
	}

	return nVersion;
}

///////////////////////////////////////////////////////////////////////////////
// GetServicePackNT - returns a valid service pack number only for NT platform
int CXWinVersion::GetServicePackNT()
{
	int nServicePack = 0;

	for (int i = 0;
		 (m_osinfo.szCSDVersion[i] != _T('\0')) &&
			 (i < (sizeof(m_osinfo.szCSDVersion)/sizeof(TCHAR)));
		 i++)
	{
		if (_istdigit(m_osinfo.szCSDVersion[i]))
		{
			nServicePack = _ttoi(&m_osinfo.szCSDVersion[i]);
			break;
		}
	}

	return nServicePack;
}

///////////////////////////////////////////////////////////////////////////////
// IsXP
BOOL CXWinVersion::IsXP()
{
	if (GetWinVersion() == WXP)
	{
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsXPHome
BOOL CXWinVersion::IsXPHome()
{
	if (GetWinVersion() == WXP)
	{
		if (m_osinfo.wSuiteMask & VER_SUITE_PERSONAL)
			return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsXPPro
BOOL CXWinVersion::IsXPPro()
{
	if (GetWinVersion() == WXP)
	{
		if ((m_osinfo.wProductType == VER_NT_WORKSTATION) && !IsXPHome())
			return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsXPSP2
BOOL CXWinVersion::IsXPSP2()
{
	if (GetWinVersion() == WXP)
	{
		if (GetServicePackNT() == 2)
			return TRUE;
	}

	return FALSE;
}

#ifndef SM_MEDIACENTER
#define SM_MEDIACENTER          87
#endif

///////////////////////////////////////////////////////////////////////////////
// IsMediaCenter
BOOL CXWinVersion::IsMediaCenter()
{
	if (GetSystemMetrics(SM_MEDIACENTER))
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsWin2003
BOOL CXWinVersion::IsWin2003()
{
	if ((m_osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) && 
		(m_osinfo.dwMajorVersion == 5) &&
		(m_osinfo.dwMinorVersion == 2))
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// GetVistaProductType
DWORD CXWinVersion::GetVistaProductType()
{
	if (m_dwVistaProductType == 0)
	{
		typedef BOOL (FAR PASCAL * lpfnGetProductInfo) (DWORD, DWORD, DWORD, DWORD, PDWORD);

		HMODULE hKernel32 = GetModuleHandle(_T("KERNEL32.DLL"));
		if (hKernel32)
		{
			lpfnGetProductInfo pGetProductInfo = (lpfnGetProductInfo) GetProcAddress(hKernel32, "GetProductInfo"); 

			if (pGetProductInfo)
				pGetProductInfo(6, 0, 0, 0, &m_dwVistaProductType);
		}  
	}

	return m_dwVistaProductType;
}

///////////////////////////////////////////////////////////////////////////////
// GetVistaProductString
Air::AString CXWinVersion::GetVistaProductString()
{
	Air::AString strProductType;// = _T("");

	switch (m_dwVistaProductType)
		{
		case PRODUCT_BUSINESS:						 strProductType = _T("Business Edition"); break;
		case PRODUCT_BUSINESS_N:					 strProductType = _T("Business Edition"); break;
		case PRODUCT_CLUSTER_SERVER:				 strProductType = _T("Cluster Server Edition"); break;
		case PRODUCT_DATACENTER_SERVER:				 strProductType = _T("Server Datacenter Edition (full installation)"); break;
		case PRODUCT_DATACENTER_SERVER_CORE:		 strProductType = _T("Server Datacenter Edition (core installation)"); break;
		case PRODUCT_ENTERPRISE:					 strProductType = _T("Enterprise Edition"); break;
		case PRODUCT_ENTERPRISE_N:					 strProductType = _T("Enterprise Edition"); break;
		case PRODUCT_ENTERPRISE_SERVER:				 strProductType = _T("Server Enterprise Edition (full installation)"); break;
		case PRODUCT_ENTERPRISE_SERVER_CORE:		 strProductType = _T("Server Enterprise Edition (core installation)"); break;
		case PRODUCT_ENTERPRISE_SERVER_IA64:		 strProductType = _T("Server Enterprise Edition for Itanium-based Systems"); break;
		case PRODUCT_HOME_BASIC:					 strProductType = _T("Home Basic Edition"); break;
		case PRODUCT_HOME_BASIC_N:					 strProductType = _T("Home Basic Edition"); break;
		case PRODUCT_HOME_PREMIUM:					 strProductType = _T("Home Premium Edition"); break;
		case PRODUCT_HOME_PREMIUM_N:				 strProductType = _T("Home Premium Edition"); break;
		case PRODUCT_HOME_SERVER:					 strProductType = _T("Home Server Edition"); break;
		case PRODUCT_SERVER_FOR_SMALLBUSINESS:		 strProductType = _T("Server for Small Business Edition"); break;
		case PRODUCT_SMALLBUSINESS_SERVER:			 strProductType = _T("Small Business Server"); break;
		case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:	 strProductType = _T("Small Business Server Premium Edition"); break;
		case PRODUCT_STANDARD_SERVER:				 strProductType = _T("Server Standard Edition (full installation)"); break;
		case PRODUCT_STANDARD_SERVER_CORE:			 strProductType = _T("Server Standard Edition (core installation)"); break;
		case PRODUCT_STARTER:						 strProductType = _T("Starter Edition"); break;
		case PRODUCT_STORAGE_ENTERPRISE_SERVER:		 strProductType = _T("Storage Server Enterprise Edition"); break;
		case PRODUCT_STORAGE_EXPRESS_SERVER:		 strProductType = _T("Storage Server Express Edition"); break;
		case PRODUCT_STORAGE_STANDARD_SERVER:		 strProductType = _T("Storage Server Standard Edition"); break;
		case PRODUCT_STORAGE_WORKGROUP_SERVER:		 strProductType = _T("Storage Server Workgroup Edition"); break;
		case PRODUCT_UNDEFINED:						 strProductType = _T("An unknown product"); break;
		case PRODUCT_ULTIMATE:						 strProductType = _T("Ultimate Edition"); break;
		case PRODUCT_ULTIMATE_N:					 strProductType = _T("Ultimate Edition"); break;
		case PRODUCT_WEB_SERVER:					 strProductType = _T("Web Server Edition"); break;

		default: break;
	}

	return strProductType;
}

///////////////////////////////////////////////////////////////////////////////
// IsVista
BOOL CXWinVersion::IsVista()
{
	if (GetWinVersion() == WVISTA)
	{
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsVistaHome
BOOL CXWinVersion::IsVistaHome()
{
	if (GetWinVersion() == WVISTA)
	{
		switch (m_dwVistaProductType)
		{
			case PRODUCT_HOME_BASIC:	
			case PRODUCT_HOME_BASIC_N:	
			case PRODUCT_HOME_PREMIUM:	
			case PRODUCT_HOME_PREMIUM_N:
			case PRODUCT_HOME_SERVER:	
				return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsVistaBusiness
BOOL CXWinVersion::IsVistaBusiness()
{
	if (GetWinVersion() == WVISTA)
	{
		switch (m_dwVistaProductType)
		{
			case PRODUCT_BUSINESS:	
			case PRODUCT_BUSINESS_N:
				return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsVistaEnterprise
BOOL CXWinVersion::IsVistaEnterprise()
{
	if (GetWinVersion() == WVISTA)
	{
		switch (m_dwVistaProductType)
		{
			case PRODUCT_ENTERPRISE:			
			case PRODUCT_ENTERPRISE_N:			
			case PRODUCT_ENTERPRISE_SERVER:		
			case PRODUCT_ENTERPRISE_SERVER_CORE:
			case PRODUCT_ENTERPRISE_SERVER_IA64:
				return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsVistaUltimate
BOOL CXWinVersion::IsVistaUltimate()
{
	if (GetWinVersion() == WVISTA)
	{
		switch (m_dwVistaProductType)
		{
			case PRODUCT_ULTIMATE:	
			case PRODUCT_ULTIMATE_N:
				return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsWin2KorLater
BOOL CXWinVersion::IsWin2KorLater()
{
	if ((m_osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) && 
		(m_osinfo.dwMajorVersion >= 5))
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsXPorLater
BOOL CXWinVersion::IsXPorLater()
{
	if ((m_osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) && 
		(((m_osinfo.dwMajorVersion == 5) && (m_osinfo.dwMinorVersion > 0)) || 
		(m_osinfo.dwMajorVersion > 5)))
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsWin95
BOOL CXWinVersion::IsWin95()
{
	if ((m_osinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && 
		(m_osinfo.dwMajorVersion == 4) && 
		(m_osinfo.dwMinorVersion < 10))
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsWin98
BOOL CXWinVersion::IsWin98()
{
	if ((m_osinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && 
		(m_osinfo.dwMajorVersion == 4) && 
		(m_osinfo.dwMinorVersion >= 10))
		return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IsWinCE
BOOL CXWinVersion::IsWinCE()
{
	return (GetWinVersion() == WCE);
}

BOOL CXWinVersion::IsX64()
{
#ifdef _WIN32
	BOOL	b		=	FALSE;
	BOOL	bRet	=	IsWow64Process(GetCurrentProcess(),&b);
	return	bRet&&b;
#else
	return TRUE;
#endif
}

