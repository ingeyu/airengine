#include "stdafx.h"
#include "DumpFile.h"
#include "DumpSymbol.h"

//#define PRINT_DUMPINFO

std::string WideByte2Acsi(const std::wstring& wstrcode){
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)	{
		return "";
	}
	if (asciisize == 0)	{
		return "";
	}
	std::vector<char> resultstring(asciisize);
	int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);

	if (convresult != asciisize)	{
		return "";
	}

	return &resultstring[0];
}

std::wstring Acsi2WideByte(const std::string& strascii){
	int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)	{
		return L"";
	}
	if (widesize == 0)	{
		return L"";
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);

	if (convresult != widesize)	{
		return L"";
	}

	return &resultstring[0];
}

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
std::wstring GetWinVersionString(
	DWORD dwPlatformId  ,
	DWORD dwMinorVersion,
	DWORD dwMajorVersion,
	DWORD dwBuildNumber
	)
{
	std::wstring strVersion = WUNKNOWNSTR;

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
	case WVISTA:	strVersion = _T("Windows Vista/Windows Server 2008");	break;
	case WIN7:		strVersion = _T("Windows7/Windows Server 2008 R2");		break;
	case WIN8:		strVersion = _T("Windows8/Windows Server 2012");			break;
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

#define NONAMELESSUNION
#define NONAMELESSSTRUCT

enum FileSig {
	SIG_UNKNOWN, 
	SIG_DOS, 
	SIG_PE, 
	SIG_DBG, 
	SIG_PDB, 
	SIG_NE, 
	SIG_LE, 
	SIG_MDMP, 
	SIG_COFFLIB, 
	SIG_LNK,
	SIG_EMF, 
	SIG_FNT, 
	SIG_MSFT};

DumpFile::DumpFile()
{
	m_pBuffer	=	NULL;
	m_uiSize	=	0;
	m_State		=	enFS_Close;
	m_Type		=	enOT_File;

	m_pSystemInfo		 =	NULL;
	m_pMiseInfo			 =	NULL;
	m_pExceptionStream	 =	NULL;
	m_pMemoryList		=	NULL;
	m_pModuleList		=	NULL;
	m_pThreadList		=	NULL;

	m_pExceptionThreadContext	=	NULL;
}

DumpFile::~DumpFile()
{
	Close();
}

bool DumpFile::Open( const wchar_t* strName )
{
	if(strName==NULL)
		return false;
	
	if(m_State==enFS_Open){
		Close();
	}
	m_strDumpName	=	strName;
	m_Type		=	enOT_File;
	HANDLE	hFile	=	CreateFile(strName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(hFile!=INVALID_HANDLE_VALUE){
		m_uiSize	=	GetFileSize(hFile,0);
		m_pBuffer		=	malloc(m_uiSize);
		DWORD uiReadSize=0;
		if(m_pBuffer!=NULL){	
			ReadFile(hFile,m_pBuffer,m_uiSize,&uiReadSize,NULL);
		}
		CloseHandle(hFile);
		bool bRet	=	false;
		if(m_pBuffer!=NULL){
			bRet	=	Open(m_pBuffer,m_uiSize);
		}
		if(bRet){
			
			return BuildCallstack();
		}
		return bRet;
	}
	return	false;
}

bool DumpFile::Open( const void* pData,unsigned int uiSize )
{
	if(m_State==enFS_Open){
		Close();
	}
	if(m_pBuffer==NULL){
		m_pBuffer	=	malloc(uiSize);
		if(m_pBuffer==NULL){
			return false;
		}
		memcpy(m_pBuffer,pData,uiSize);
		m_Type		=	enOT_Memory;
	}
	mdmp_dump(m_pBuffer,uiSize);
	m_State	=	enFS_Open;

	LoadSymbol();
	return true;
}


char* DumpFile::dump_want_n(unsigned sz)
{
    static char         buffer[4 * 1024];
    static unsigned     idx;
    char*               ret;

   // assert(sz < sizeof(buffer));
    if (idx + sz >= sizeof(buffer)) idx = 0;
    ret = &buffer[idx];
    idx += sz;
    return ret;
}

const char *DumpFile::get_time_str(unsigned long _t)
{
	const time_t    t = (const time_t)_t;
	const char      *str = ctime(&t);
	size_t          len;
	char*           buf;

	if (!str) return "not valid time";

	len = strlen(str);
	/* FIXME: I don't get the same values from MS' pedump running under Wine...
	* I wonder if Wine isn't broken wrt to GMT settings...
	*/
	if (len && str[len-1] == '\n') len--;
	buf = dump_want_n(len + 1);
	if (buf)
	{
		memcpy( buf, str, len );
		buf[len] = 0;
	}
	return buf;
 }

void DumpFile::dump_unicode_str( const wchar_t *str, int len )
{
	if (len == -1) len = wcslen( str );
	printf( "L\"");
	while (len-- > 0 && *str)
	{
		WCHAR c = *str++;
		switch (c)
		{
		case '\n': printf( "\\n" ); break;
		case '\r': printf( "\\r" ); break;
		case '\t': printf( "\\t" ); break;
		case '"':  printf( "\\\"" ); break;
		case '\\': printf( "\\\\" ); break;
		default:
			if (c >= ' ' && c <= 126) putchar(c);
			else printf( "\\u%04x",c);
		}
	}
	printf( "\"" );
}

const void*    DumpFile::PRD(unsigned long prd, unsigned long len)
{
    return (prd + len > m_uiSize) ? NULL : (const char*)m_pBuffer + prd;
}

void DumpFile::dump_data( const unsigned char *ptr, unsigned int size, const char *prefix )
{
}


void DumpFile::dump_mdmp_data(const MINIDUMP_LOCATION_DESCRIPTOR* md, const char* pfx)
{
	if (md->DataSize)
		dump_data((unsigned char*)PRD(md->Rva, md->DataSize), md->DataSize, pfx);
}

void DumpFile::dump_mdmp_string(DWORD rva)
{
	const MINIDUMP_STRING*      ms = (MINIDUMP_STRING*)PRD(rva, sizeof(MINIDUMP_STRING));
	if (ms)
		dump_unicode_str( ms->Buffer, ms->Length / sizeof(WCHAR) );
	else
		printf("<<?>>");
}

const MINIDUMP_DIRECTORY* DumpFile::get_mdmp_dir(const MINIDUMP_HEADER* hdr, unsigned int str_idx)
{
	const MINIDUMP_DIRECTORY*   dir;
	unsigned int                i;

	for (i = 0; i < hdr->NumberOfStreams; i++)
	{
		dir = (MINIDUMP_DIRECTORY*)PRD(hdr->StreamDirectoryRva + i * sizeof(MINIDUMP_DIRECTORY), 
			sizeof(MINIDUMP_DIRECTORY));
		if (!dir) continue;
		if (dir->StreamType == str_idx) return dir;
	}
	return NULL;
}

enum FileSig DumpFile::get_kind_mdmp(void)
{
	const DWORD*        pdw;

	pdw = (DWORD*)PRD(0, sizeof(DWORD));
	if (!pdw) {printf("Can't get main signature, aborting\n"); return SIG_UNKNOWN;}

	if (*pdw == 0x504D444D /* "MDMP" */) return SIG_MDMP;
	return SIG_UNKNOWN;
}

void DumpFile::mdmp_dump(void* pBase,unsigned int uiSize)
{
	const MINIDUMP_HEADER*      hdr = (MINIDUMP_HEADER*)PRD(0, sizeof(MINIDUMP_HEADER));
	ULONG                       idx, ndir = 0;
	const MINIDUMP_DIRECTORY*   dir;
	const void*                 stream;

	if (!hdr)
	{
		printf("Cannot get Minidump header\n");
		return;
	}
#ifdef PRINT_DUMPINFO
	printf("Signature: %u (%.4s)\n", hdr->Signature, (const char*)&hdr->Signature);
	printf("Version: %x\n", hdr->Version);
	printf("NumberOfStreams: %u\n", hdr->NumberOfStreams);
	printf("StreamDirectoryRva: %u\n", hdr->StreamDirectoryRva);
	printf("CheckSum: %u\n", hdr->CheckSum);
	printf("TimeDateStamp: %s\n", get_time_str(hdr->TimeDateStamp));
	printf("Flags: %x%08x\n", (DWORD)(hdr->Flags >> 32), (DWORD)hdr->Flags);
#endif
	for (idx = 0; idx < hdr->NumberOfStreams; idx++)
	{
		//if (!(dir = get_mdmp_dir(hdr, idx))) continue;

		dir = (MINIDUMP_DIRECTORY*)PRD(hdr->StreamDirectoryRva + idx * sizeof(MINIDUMP_DIRECTORY), 
			sizeof(MINIDUMP_DIRECTORY));

		stream = PRD(dir->Location.Rva, dir->Location.DataSize);
#ifdef PRINT_DUMPINFO
		printf("Directory [%u]: ", idx);
#endif
		switch (dir->StreamType)
		{
		case ThreadListStream:
			{
				const MINIDUMP_THREAD_LIST* mtl = (const MINIDUMP_THREAD_LIST*)stream;
				m_pThreadList					=	(MINIDUMP_THREAD_LIST*) mtl;
				const MINIDUMP_THREAD*      mt = mtl->Threads;
				unsigned int                i;

				m_vecThread.resize(mtl->NumberOfThreads);
				for (i = 0; i < mtl->NumberOfThreads; i++, mt++){
					DumpThread& thread = m_vecThread[i];
					thread.ThreadId		=	mt->ThreadId;
					thread.SuspendCount	=	mt->SuspendCount;
					thread.PriorityClass	=	mt->PriorityClass;
					thread.Priority	=	mt->Priority;
					thread.Teb	=	mt->Teb;
					thread.StartOfMemoryRange	=	mt->Stack.StartOfMemoryRange;
					thread.MemorySize	=	mt->Stack.Memory.DataSize;
					thread.StackMemory	=	(unsigned char*)m_pBuffer	+	mt->Stack.Memory.Rva;
					thread.pContext		=	(CONTEXT*)((unsigned char*)m_pBuffer	+	mt->ThreadContext.Rva);
				}
#ifdef PRINT_DUMPINFO
				mt = mtl->Threads;
				printf("Threads: %u\n", mtl->NumberOfThreads);
				for (i = 0; i < mtl->NumberOfThreads; i++, mt++)
				{
					printf("  Thread: #%d\n", i);
					printf("    ThreadId: %u\n", mt->ThreadId);
					printf("    SuspendCount: %u\n", mt->SuspendCount);
					printf("    PriorityClass: %u\n", mt->PriorityClass);
					printf("    Priority: %u\n", mt->Priority);
					printf("    Teb: 0x%x%08x\n", (DWORD)(mt->Teb >> 32), (DWORD)mt->Teb);
					printf("    Stack: 0x%x%08x-0x%x%08x\n",
						(DWORD)(mt->Stack.StartOfMemoryRange >> 32),
						(DWORD)mt->Stack.StartOfMemoryRange,
						(DWORD)((mt->Stack.StartOfMemoryRange + mt->Stack.Memory.DataSize) >> 32),
						(DWORD)(mt->Stack.StartOfMemoryRange + mt->Stack.Memory.DataSize));
					dump_mdmp_data(&mt->Stack.Memory, "    ");
					printf("    ThreadContext:\n");
					dump_mdmp_data(&mt->ThreadContext, "    ");
				}
#endif
			}
			break;
		case ModuleListStream:
		case 0xFFF0:
			{
				const MINIDUMP_MODULE_LIST* mml = (const MINIDUMP_MODULE_LIST*)stream;
				m_pModuleList					=	(MINIDUMP_MODULE_LIST* )mml;
				const MINIDUMP_MODULE*      mm = mml->Modules;
				unsigned int                i;
				const char*                 p1;
				const char*                 p2;

				m_vecModule.resize(mml->NumberOfModules);
				for (i = 0; i < mml->NumberOfModules; i++, mm++)
				{
					DumpModule& module		=	m_vecModule[i];
					module.BaseOfImage		=	mm->BaseOfImage;
					module.SizeOfImage		=	mm->SizeOfImage;
					module.TimeDateStamp	=	mm->TimeDateStamp;
					module.Name				=	(wchar_t*)((unsigned char*)m_pBuffer +mm->ModuleNameRva+4);
					memcpy(&module.RSDS,(unsigned char*)m_pBuffer +mm->CvRecord.Rva,mm->CvRecord.DataSize);
					module.pBinary			=	NULL;
					module.pPDB				=	NULL;
				}
#ifdef PRINT_DUMPINFO
				printf("Modules (%s): %u\n",
					dir->StreamType == ModuleListStream ? "PE" : "ELF",
					mml->NumberOfModules);
				mm = mml->Modules;
				for (i = 0; i < mml->NumberOfModules; i++, mm++)
				{
					printf("  Module #%d:\n", i);
					printf("    BaseOfImage: 0x%x%08x\n",
						(DWORD)(mm->BaseOfImage >> 32), (DWORD) mm->BaseOfImage);
					printf("    SizeOfImage: %u\n", mm->SizeOfImage);
					printf("    CheckSum: %u\n", mm->CheckSum);
					printf("    TimeDateStamp: %s\n", get_time_str(mm->TimeDateStamp));
					printf("    ModuleName: ");
					dump_mdmp_string(mm->ModuleNameRva);
					printf("\n");
					printf("    VersionInfo:\n");
					printf("      dwSignature: %x\n", mm->VersionInfo.dwSignature);
					printf("      dwStrucVersion: %x\n",
						mm->VersionInfo.dwStrucVersion);
					printf("      dwFileVersion: %d,%d,%d,%d\n", 
						HIWORD(mm->VersionInfo.dwFileVersionMS),
						LOWORD(mm->VersionInfo.dwFileVersionMS),
						HIWORD(mm->VersionInfo.dwFileVersionLS),
						LOWORD(mm->VersionInfo.dwFileVersionLS));
					printf("      dwProductVersion %d,%d,%d,%d\n",
						HIWORD(mm->VersionInfo.dwProductVersionMS),
						LOWORD(mm->VersionInfo.dwProductVersionMS),
						HIWORD(mm->VersionInfo.dwProductVersionLS),
						LOWORD(mm->VersionInfo.dwProductVersionLS));
					printf("      dwFileFlagsMask: %u\n",
						mm->VersionInfo.dwFileFlagsMask);
					printf("      dwFileFlags: %s%s%s%s%s%s\n", 
						mm->VersionInfo.dwFileFlags & VS_FF_DEBUG ? "Debug " : "",
						mm->VersionInfo.dwFileFlags & VS_FF_INFOINFERRED ? "Inferred " : "",
						mm->VersionInfo.dwFileFlags & VS_FF_PATCHED ? "Patched " : "",
						mm->VersionInfo.dwFileFlags & VS_FF_PRERELEASE ? "PreRelease " : "",
						mm->VersionInfo.dwFileFlags & VS_FF_PRIVATEBUILD ? "PrivateBuild " : "",
						mm->VersionInfo.dwFileFlags & VS_FF_SPECIALBUILD ? "SpecialBuild " : "");
					if (mm->VersionInfo.dwFileOS)
					{
						switch (mm->VersionInfo.dwFileOS & 0x000F)
						{
						case VOS__BASE:     p1 = "_base"; break;
						case VOS__WINDOWS16:p1 = "16 bit Windows"; break;
						case VOS__PM16:     p1 = "16 bit Presentation Manager"; break;
						case VOS__PM32:     p1 = "32 bit Presentation Manager"; break;
						case VOS__WINDOWS32:p1 = "32 bit Windows"; break;
						default:            p1 = "---"; break;
						}
						switch (mm->VersionInfo.dwFileOS & 0xF0000)
						{
						case VOS_UNKNOWN:   p2 = "unknown"; break;
						case VOS_DOS:       p2 = "DOS"; break;
						case VOS_OS216:     p2 = "16 bit OS/2"; break;
						case VOS_OS232:     p2 = "32 bit OS/2"; break;
						case VOS_NT:        p2 = "Windows NT"; break;
						default:            p2 = "---"; break;
						}
						printf("      dwFileOS: %s running on %s\n", p1, p2);
					}
					else printf("      dwFileOS: 0\n");
					switch (mm->VersionInfo.dwFileType)
					{
					case VFT_UNKNOWN:       p1 = "Unknown"; break;
					case VFT_APP:           p1 = "Application"; break;
					case VFT_DLL:           p1 = "DLL"; break;
					case VFT_DRV:           p1 = "Driver"; break;
					case VFT_FONT:          p1 = "Font"; break;
					case VFT_VXD:           p1 = "VxD"; break;
					case VFT_STATIC_LIB:    p1 = "Static Library"; break;
					default:                p1 = "---"; break;
					}
					printf("      dwFileType: %s\n", p1);
					printf("      dwFileSubtype: %u\n",
						mm->VersionInfo.dwFileSubtype);
					printf("      dwFileDate: %x%08x\n",
						mm->VersionInfo.dwFileDateMS, mm->VersionInfo.dwFileDateLS);
					printf("    CvRecord: <%u>\n", mm->CvRecord.DataSize);
					dump_mdmp_data(&mm->CvRecord, "    ");
					printf("    MiscRecord: <%u>\n", mm->MiscRecord.DataSize);
					dump_mdmp_data(&mm->MiscRecord, "    ");
					printf("    Reserved0: 0x%x%08x\n",
						(DWORD)(mm->Reserved0 >> 32), (DWORD)mm->Reserved0);
					printf("    Reserved1: 0x%x%08x\n",
						(DWORD)(mm->Reserved1 >> 32), (DWORD)mm->Reserved1);
				}
#endif
			}       
			break;
		case MemoryListStream:
			{
				const MINIDUMP_MEMORY_LIST*         mml = (const MINIDUMP_MEMORY_LIST*)stream;
				m_pMemoryList							=	(MINIDUMP_MEMORY_LIST*)mml;
				const MINIDUMP_MEMORY_DESCRIPTOR*   mmd = mml->MemoryRanges;
				unsigned int                        i;
#ifdef PRINT_DUMPINFO
				printf("Memory Ranges: %u\n", mml->NumberOfMemoryRanges);
				for (i = 0; i < mml->NumberOfMemoryRanges; i++, mmd++)
				{
					printf("  Memory Range #%d:\n", i);
					printf("    Range: 0x%x%08x-0x%x%08x\n",
						(DWORD)(mmd->StartOfMemoryRange >> 32),
						(DWORD)mmd->StartOfMemoryRange,
						(DWORD)((mmd->StartOfMemoryRange + mmd->Memory.DataSize) >> 32),
						(DWORD)(mmd->StartOfMemoryRange + mmd->Memory.DataSize));
					dump_mdmp_data(&mmd->Memory, "    ");
				} 
#endif
			}
			break;
		case SystemInfoStream:
			{
				const MINIDUMP_SYSTEM_INFO* msi = (const MINIDUMP_SYSTEM_INFO*)stream;
				m_pSystemInfo					=	(MINIDUMP_SYSTEM_INFO*)msi;
				const char*                 str;
				char                        tmp[128];
#ifdef PRINT_DUMPINFO
				printf("System Information:\n");
				switch (msi->ProcessorArchitecture)
				{
				case PROCESSOR_ARCHITECTURE_UNKNOWN:
					str = "Unknown";
					break;
				case PROCESSOR_ARCHITECTURE_INTEL:
					strcpy(tmp, "Intel ");
					switch (msi->ProcessorLevel)
					{
					case  3: str = "80386"; break;
					case  4: str = "80486"; break;
					case  5: str = "Pentium"; break;
					case  6: str = "Pentium Pro/II or AMD Athlon"; break;
					case 15: str = "Pentium 4 or AMD Athlon64"; break;
					default: str = "???"; break;
					}
					strcat(tmp, str);
					strcat(tmp, " (");
					if (msi->ProcessorLevel == 3 || msi->ProcessorLevel == 4)
					{
						if (HIBYTE(msi->ProcessorRevision) == 0xFF)
							sprintf(tmp + strlen(tmp), "%c%d", 'A' + ((msi->ProcessorRevision>>4)&0xf)-0x0a, msi->ProcessorRevision&0xf);
						else
							sprintf(tmp + strlen(tmp), "%c%d", 'A' + HIBYTE(msi->ProcessorRevision), LOBYTE(msi->ProcessorRevision));
					}
					else sprintf(tmp + strlen(tmp), "%d.%d", HIBYTE(msi->ProcessorRevision), LOBYTE(msi->ProcessorRevision));
					str = tmp;
					break;
				case PROCESSOR_ARCHITECTURE_MIPS:
					str = "Mips";
					break;
				case PROCESSOR_ARCHITECTURE_ALPHA:
					str = "Alpha";
					break;
				case PROCESSOR_ARCHITECTURE_PPC:
					str = "PowerPC";
					break;
				case PROCESSOR_ARCHITECTURE_ARM:
					str = "ARM";
					break;
				case PROCESSOR_ARCHITECTURE_AMD64:
					str = "X86_64";
					break;
				default:
					str = "???";
					break;
				}
				printf("  Processor: %s (#%d CPUs)\n", str, msi->NumberOfProcessors);
				/*				
				switch (msi->MajorVersion)
				{
				case 3:
				switch (msi->MinorVersion)
				{
				case 51: str = "NT 3.51"; break;
				default: str = "3-????"; break;
				}
				break;
				case 4:
				switch (msi->MinorVersion)
				{
				case 0: str = (msi->PlatformId == VER_PLATFORM_WIN32_NT) ? "NT 4.0" : "95"; break;
				case 10: str = "98"; break;
				case 90: str = "ME"; break;
				default: str = "5-????"; break;
				}
				break;
				case 5:
				switch (msi->MinorVersion)
				{
				case 0: str = "2000"; break;
				case 1: str = "XP"; break;
				case 2: str = "Server 2003"; break;
				default: str = "5-????"; break;
				}
				break;
				default: str = "???"; break;
				}
				*/
				printf("  Version: Windows %s (%u)\n", GetWinVersionString(msi->PlatformId,msi->MinorVersion,msi->MajorVersion,msi->BuildNumber).c_str(), msi->BuildNumber);
				printf("  PlatformId: %u\n", msi->PlatformId);
				printf("  CSD: ");
				dump_mdmp_string(msi->CSDVersionRva);
				printf("\n");
				printf("  Reserved1: %u\n", msi->Reserved1);
				if (msi->ProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
				{
					printf("  x86.VendorId: %.12s\n",
						(const char*)msi->Cpu.X86CpuInfo.VendorId);
					printf("  x86.VersionInformation: %x\n",
						msi->Cpu.X86CpuInfo.VersionInformation);
					printf("  x86.FeatureInformation: %x\n",
						msi->Cpu.X86CpuInfo.FeatureInformation);
					printf("  x86.AMDExtendedCpuFeatures: %x\n",
						msi->Cpu.X86CpuInfo.AMDExtendedCpuFeatures);
				}
				if (sizeof(MINIDUMP_SYSTEM_INFO) + 4 > dir->Location.DataSize &&
					msi->CSDVersionRva >= dir->Location.Rva + 4)
				{
					const char*  code = (char*)PRD(dir->Location.Rva + sizeof(MINIDUMP_SYSTEM_INFO), 4);
					const DWORD* wes;
					if (code && code[0] == 'W' && code[1] == 'I' && code[2] == 'N' && code[3] == 'E' &&
						*(wes = (const DWORD*)(code += 4)) >= 3)
					{
						/* assume we have wine extensions */
						printf("  Wine details:\n");
						printf("    build-id: %s\n", code + wes[1]);
						printf("    system: %s\n", code + wes[2]);
						printf("    release: %s\n", code + wes[3]);
					}
				}
#endif
			}
			break;
		case MiscInfoStream:
			{
				const MINIDUMP_MISC_INFO* mmi = (const MINIDUMP_MISC_INFO*)stream;
				m_pMiseInfo					=	(MINIDUMP_MISC_INFO*)mmi;
#ifdef PRINT_DUMPINFO
				printf("Misc Information\n");
				printf("  Size: %u\n", mmi->SizeOfInfo);
				printf("  Flags: %s%s\n", 
					mmi->Flags1 & MINIDUMP_MISC1_PROCESS_ID ? "ProcessId " : "",
					mmi->Flags1 & MINIDUMP_MISC1_PROCESS_TIMES ? "ProcessTimes " : "");
				if (mmi->Flags1 & MINIDUMP_MISC1_PROCESS_ID)
					printf("  ProcessId: %u\n", mmi->ProcessId);
				if (mmi->Flags1 & MINIDUMP_MISC1_PROCESS_TIMES)
				{
					printf("  ProcessCreateTime: %u\n", mmi->ProcessCreateTime);
					printf("  ProcessUserTime: %u\n", mmi->ProcessUserTime);
					printf("  ProcessKernelTime: %u\n", mmi->ProcessKernelTime);
				}
#endif
			}
			break;
		case ExceptionStream:
			{
				const MINIDUMP_EXCEPTION_STREAM*    mes = (const MINIDUMP_EXCEPTION_STREAM*)stream;
				m_pExceptionStream					=	(MINIDUMP_EXCEPTION_STREAM*)mes;
				unsigned int                        i;
#ifdef PRINT_DUMPINFO
				printf("Exception:\n");
				printf("  ThreadId: %08x\n", mes->ThreadId);
				printf("  ExceptionRecord:\n");
				printf("  ExceptionCode: %u\n", mes->ExceptionRecord.ExceptionCode);
				printf("  ExceptionFlags: %u\n", mes->ExceptionRecord.ExceptionFlags);
				printf("  ExceptionRecord: 0x%x%08x\n",
					(DWORD)(mes->ExceptionRecord.ExceptionRecord  >> 32),
					(DWORD)mes->ExceptionRecord.ExceptionRecord);
				printf("  ExceptionAddress: 0x%x%08x\n",
					(DWORD)(mes->ExceptionRecord.ExceptionAddress >> 32),
					(DWORD)(mes->ExceptionRecord.ExceptionAddress));
				printf("  ExceptionNumberParameters: %u\n",
					mes->ExceptionRecord.NumberParameters);
				for (i = 0; i < mes->ExceptionRecord.NumberParameters; i++)
				{
					printf("    [%d]: 0x%x%08x\n", i,
						(DWORD)(mes->ExceptionRecord.ExceptionInformation[i] >> 32),
						(DWORD)mes->ExceptionRecord.ExceptionInformation[i]);
				}
				printf("  ThreadContext:\n");
				dump_mdmp_data(&mes->ThreadContext, "    ");
#endif
				m_pExceptionThreadContext	=	(CONTEXT*)((unsigned char*)m_pBuffer + mes->ThreadContext.Rva);
			}
			break;

		default:
#ifdef PRINT_DUMPINFO
			printf("NIY %d\n", dir->StreamType);
			printf("  RVA: %u\n", dir->Location.Rva);
			printf("  Size: %u\n", dir->Location.DataSize);
			dump_mdmp_data(&dir->Location, "    ");
#endif
			break;
		}
	}
}

bool DumpFile::Close()
{

	if(m_pBuffer!=NULL){
		free(m_pBuffer);
		m_pBuffer=NULL;
	}
	m_uiSize	=	0;
	m_State		=	enFS_Close;
	m_pSystemInfo		 =	NULL;
	m_pMiseInfo			 =	NULL;
	m_pExceptionStream	 =	NULL;
	m_pMemoryList		=	NULL;
	m_pModuleList		=	NULL;
	m_pThreadList		=	NULL;

	m_vecModule.clear();
	m_vecThread.clear();
	m_strDumpName.clear();
	return true;
}

bool DumpFile::BuildCallstack()
{
	DWORD esp		=	m_pExceptionThreadContext->Esp;
	DWORD threadid	=	m_pExceptionStream->ThreadId;

	DWORD	uiStackAddress	=	0;
	U8*	pStack					=	NULL;
	U8*	pStackEnd				=	NULL;
	for(DWORD i=0;i<m_vecThread.size();i++){
		DumpThread& thread = m_vecThread[i];
		if(thread.ThreadId==threadid){
			pStack				=	(U8*)thread.StackMemory;
			uiStackAddress		=	thread.StartOfMemoryRange&0x00000000ffffffff;
			pStackEnd			=	pStack+thread.MemorySize;
			break;
		}
	}
	if(pStack==NULL){
		return	false;
	}

	std::wstring	str;
	str.reserve(1024*10);
	wchar_t tempstring[1024];

	swprintf_s(tempstring,L"==[threadid=%d][Callstack]==\n",threadid);
	str+=tempstring;
	DWORD* pStart = (DWORD*)(pStack+(esp-uiStackAddress));
	for(DWORD* p=pStart;p!=(DWORD*)pStackEnd;p++){
		ULONG64 address = *p;
		for(U32 i=0;i<m_vecModule.size();i++){
			DumpModule& module = m_vecModule[i];
			ULONG64 offset = (address - module.BaseOfImage);
			if(offset < module.SizeOfImage	&&	offset > 0){

				if(module.pBinary!=NULL){
					Dump::BinaryFile* pBinary	=	(Dump::BinaryFile*)module.pBinary;
					void* pCode = pBinary->GetOffset(address);
					if(pCode==NULL){
						continue;
					}
					if(!IsCall(pCode)){
						continue;
					}
				}
				
				swprintf_s(tempstring,L"[%08x]",address);
				str+=tempstring;
				str+=module.Name;
				str+=L"\n";
			}
		}
	}
	swprintf_s(tempstring,L"==[threadid=%d][End]==\n");
	str+=tempstring;
	std::string strANSI = WideByte2Acsi(str);
	//OutputDebugString(str.c_str());
	std::wstring strCallstackName = m_strDumpName+L".txt";
	std::string	strANSIName		=	WideByte2Acsi(strCallstackName);
	//HANDLE	hFile	=	CreateFile(strCallstackName.c_str(),GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_NEW,FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	//if(hFile!=INVALID_HANDLE_VALUE){
	//	DWORD dWriteSize = NULL;
	//	WriteFile(hFile,strANSI.c_str(),strANSI.size()+1,&dWriteSize,NULL);
	//	CloseHandle(hFile);
	//}
	//FILE* pFile = fopen(strANSIName.c_str(),"w");
	//if(pFile!=NULL){
	//	fprintf(pFile,strANSI.c_str());
	//	fclose(pFile);
	//}
	printf(strANSI.c_str());
	//MessageBox(NULL,str.c_str(),L"CallStack!",NULL);
	return true;
}

U1 DumpFile::IsCall( const void* p )
{
	U8* pCode = (U8*)p;
	U16* pCode2	=	(U16*)(pCode-2);
	U16 c2 = *pCode2;
	c2 = c2&0xf0ff;
	if(c2 == 0x10FF || c2==0xD0FF || c2 == 0x50FF){
		return true;
	}
	U16* pCode3	=	(U16*)(pCode-3);
	U16 c3_1	=	*pCode3;
	U16 c3		=	*pCode3;
	c3=c3&0xf0ff;
	if(c2 == 0x50FF ||c3_1==0x14ff){
		return true;
	}
	U16* pCode4	=	(U16*)(pCode-4);
	U16 c4		=	*pCode4;
	if(c4 == 0x54ff){
		return true;
	}

	U8 c5	=	*(pCode-5);
	if(c5==0xe8){
		return true;
	}

	U16* pCode6	=	(U16*)(pCode-6);
	U16 c6 = *pCode6;
	if(c6==0x15FF){
		return true;
	}

	return false;
}

void DumpFile::LoadSymbol()
{
	wprintf(L"[Load Module/Symbol File]\n");
	for(U32 i=0;i<m_vecModule.size();i++){
		DumpModule& module = m_vecModule[i];
		module.pBinary	=	Dump::FileManager::GetSingleton()->AddModuleFile(module.Name,module.TimeDateStamp);
		
		if(module.pBinary!=NULL){
			Dump::BinaryFile* pB	=	(Dump::BinaryFile*)module.pBinary;
			pB->SetBase(module.BaseOfImage);

			printf(WideByte2Acsi(module.Name).c_str());
			wprintf(L"\n");
		}
	}
}


