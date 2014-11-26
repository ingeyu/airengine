// FolderCompare.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <windows.h>
#include <list>
#include <vector>
#include <string>
#include <map>

typedef std::map<std::wstring,int> StringList;

void	FindAllFile(const std::wstring& strRoot,std::wstring currentPath,StringList& lst){
	WIN32_FIND_DATA FindFileData;  
	currentPath+=L"\\";
	std::wstring	findfile = strRoot+currentPath+L"*";

	std::wstring strtemp;
	HANDLE hFile;

	DWORD errorcode = 0;


	{
		hFile=FindFirstFile(findfile.c_str(),&FindFileData);
		while(hFile!=INVALID_HANDLE_VALUE)
		{
			if(	wcscmp(FindFileData.cFileName,L".")!=0	&&
				wcscmp(FindFileData.cFileName,L"..")!=0)
			{
				strtemp=currentPath+FindFileData.cFileName;
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					FindAllFile(strRoot,strtemp,lst);
				}
				else	if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
				{
					std::wstring strfile = FindFileData.cFileName;
					lst[strtemp]=1;
				}
			}
			if(!FindNextFile(hFile,&FindFileData))
				break;
		}

		FindClose(hFile);
	}

}

typedef std::vector<unsigned char>	FileData;

bool ReadFile(const std::wstring& file,FileData& data)
{
	HANDLE f = CreateFile(file.c_str(),GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		OPEN_EXISTING,0,NULL);
	if(f!=INVALID_HANDLE_VALUE)
	{
		DWORD high	=	0;
		DWORD size	=	GetFileSize(f,&high);
		
		if(size>0)
		{
			data.resize(size);
			DWORD dwRead	=	0;
			ReadFile(f,&data[0],size,&dwRead,NULL);
		}
		else
		{
			data.clear();
		}
		CloseHandle(f);
		return true;
	}
	return false;
}

bool Compare(FileData& src,FileData& dst)
{
	if(src.size()!=dst.size())
	{
		return false;
	}
	if(src.size()!=0)
	{
		if(memcmp(&src[0],&dst[0],src.size())!=0)
		{
			return false;
		}
	}
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc>2)
	{
		for(int i=1;i<argc;i++)
		{
			wprintf(argv[i]);
			wprintf(L"\n");
		}

		std::wstring left = argv[1];

		StringList leftFile;
		FindAllFile(left,L"",leftFile);

		std::wstring right = argv[2];

		StringList rightFile;
		FindAllFile(right,L"",rightFile);

		FileData leftData,rightData;

		for(StringList::iterator i = leftFile.begin();i!=leftFile.end();i++)
		{
			std::wstring file0 = i->first;
			if(rightFile.find(file0)!=rightFile.end())
			{
				ReadFile(left+file0,leftData);
				ReadFile(right+file0,rightData);
				if(!Compare(leftData,rightData))
				{
					std::wstring sOutput	=	left + file0 + L",-2\n";
					wprintf(sOutput.c_str());
				}

				rightFile[file0]	=	0;
			}
			else
			{
				std::wstring sOutput	=	left + file0 + L",-1\n";
				wprintf(sOutput.c_str());
			}
		}

		for (StringList::iterator i = rightFile.begin();i!=rightFile.end();i++)
		{
			if(i->second==1)
			{
				std::wstring sOutput	=	left + i->first + L",-3\n";
				wprintf(sOutput.c_str());
			}
		}

		wprintf(L"Compare Complated!");
	}
	else
	{
		printf("FolderCompare leftPath rightPath\n");
		
	}
	getchar();
	return 0;
}

