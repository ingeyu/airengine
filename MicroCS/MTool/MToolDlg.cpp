
// MToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MTool.h"
#include "MToolDlg.h"
#include "afxdialogex.h"
#include <list>
#include <string>
#include <vector>
#include "MCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMToolDlg 对话框




CMToolDlg::CMToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

		pBrow		=	NULL;
		pProgress	=	NULL;
		pList		=	NULL;
		pTest		=	NULL;
		pMaxBlock	=	NULL;
}

void CMToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMToolDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMToolDlg 消息处理程序

BOOL CMToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	pBrow		=	(CMFCEditBrowseCtrl*)GetDlgItem(IDC_MFCEDITBROWSE1);
	pBrow->EnableFolderBrowseButton();
	pProgress	=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	pProgress->SetRange(0,100);
	pProgress->SetPos(0);
	pList		=	(CListBox*)GetDlgItem(IDC_LIST2);
	//pList->InsertString()
	pTest		=	(CStatic*)GetDlgItem(IDC_STATIC);
	pTest->SetWindowTextW(L"0/0");
	pMaxBlock	=	(CEdit*)GetDlgItem(IDC_EDIT1);

	wchar_t str[MAX_PATH];
	swprintf_s(str,L"%d",3500);

	pMaxBlock->SetWindowTextW(L"3500");;
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
typedef std::list<std::wstring>	FileList;
void	ScanFolder(std::wstring strFloder,FileList& lstFile){
	std::wstring	s = strFloder+std::wstring(L"*.*");
	WIN32_FIND_DATA	data;
	HANDLE	h	=	FindFirstFile(s.c_str(),&data);
	while(h!=INVALID_HANDLE_VALUE){
		if(	wcscmp(data.cFileName,L".")!=0	&&
			wcscmp(data.cFileName,L"..")!=0)
		{
			
			if(data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
				std::wstring newPath	=	strFloder+data.cFileName+std::wstring(L"\\");
				ScanFolder(newPath,lstFile);
			}else{
				lstFile.push_back(strFloder+data.cFileName);
			}
		}

		if(!FindNextFile(h,&data)){
			break;
		}
	}
}
std::string WideByte2Acsi(const std::wstring& wstrcode){
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)	{
		return "";
	}
	if (asciisize == 0)	{
		return "";
	}
	std::string resultstring;
	resultstring.resize(asciisize);
	int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);

	if (convresult != asciisize)	{
		return "";
	}

	return resultstring;
}
void	ThreadFunc(void* p){
	CMToolDlg* pDlg	=	(CMToolDlg*)p;
	CoInitialize(NULL);
		ITaskbarList3 *pitl;   
		HRESULT hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pitl));   
		if (SUCCEEDED(hr)){   
			hr = pitl->HrInit();   
			if (FAILED(hr)){   
				pitl->Release();   
				pitl = NULL;   
			}
			pitl->SetProgressState(pDlg->GetSafeHwnd(),TBPF_INDETERMINATE );
			pDlg->Build(pitl);

			//if (nProgress > 100) nProgress = 10;

			pitl->SetProgressState(pDlg->GetSafeHwnd(),TBPF_NORMAL  );
			pitl->Release();   
		}else{
			
			pDlg->Build(NULL);
		}


	

}

void CMToolDlg::OnBnClickedOk()
{
	_beginthread(ThreadFunc,1048576,this);
}

void CMToolDlg::Build(ITaskbarList3 *p){
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	U32	uiBlockSize	=	3500;
	wchar_t strBlockSize[MAX_PATH];
	pMaxBlock->GetWindowTextW(strBlockSize,MAX_PATH);
	if(wcslen(strBlockSize)>0){
		swscanf_s(strBlockSize,L"%d",&uiBlockSize);
	}
	if(uiBlockSize==0){
		uiBlockSize	=	3500;
	}
	uiBlockSize*=1048576;

	pList->ResetContent();

	wchar_t strPath[MAX_PATH]={0};
	pBrow->GetWindowTextW(strPath,MAX_PATH);
	int iLen	=	wcslen(strPath);
	if(iLen==0){
		pList->AddString(L"路径不能为空!");
		return;
	}
	if(strPath[iLen-1]!=L'/'&&strPath[iLen-1]!=L'\\'){
		strPath[iLen]=L'\\';
	}
	FileList lstFile;
	ScanFolder(strPath,lstFile);



	FileInfoVector	vecFileInfo;
	vecFileInfo.reserve(lstFile.size());


	std::vector<unsigned char>	vecTempData,vecCompressData;
	std::vector<std::wstring>	vecString;
	vecString.reserve(10000);
	FILE* pFileData[FILEDATA_COUNT];
	for(U32	i=0;i<FILEDATA_COUNT;i++){
		//TCHAR strTemp[MAX_PATH];
		//swprintf_s(strTemp,_T("Data%d"),i);
		pFileData[i]	=	NULL;//_wfopen(strTemp,L"wb");
	}
	FILE* pFileIndex	=	_wfopen(L"Index",L"wb");
	
	U32 maxSize	=	0;
	U32	maxCompressSize	=0;

	U32	uiCurrentData	=	0;
	U32 iOffset=0;

	int f = 0;
	FileList::iterator	i	=	lstFile.begin();
	for(;i!=lstFile.end();i++){
		f++;
		float pos = (float)f/(float)lstFile.size();
		pProgress->SetPos(pos*100);
		p->SetProgressValue(GetSafeHwnd(),pos*100,100);
		wchar_t str[MAX_PATH];
		swprintf_s(str,L"%d/%d",f,lstFile.size());
		pTest->SetWindowTextW(str);
		//pList->InsertString(0,(*i).c_str());
		//if(f&0xf==0){
		//	pTest->RedrawWindow();
		//	pProgress->RedrawWindow();
		//	pList->RedrawWindow();
		//}
		vecString.push_back((*i));
		std::wstring	s = *i;
		FileInfo info;
		HANDLE h = CreateFile(s.c_str(),GENERIC_READ ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING ,0,0 );
		if(h!=INVALID_HANDLE_VALUE){
			info.size	=	GetFileSize(h,0);
			if(info.size==0)
				continue;
			vecTempData.resize(info.size);
			vecCompressData.resize(info.size+4096);
			DWORD	dwRead=0;
			ReadFile(h,&vecTempData[0],info.size,&dwRead,NULL);
			CloseHandle(h);
			info.compressize	=	vecCompressData.size();

			S32	err = MCompress(&vecTempData[0],info.size,&vecCompressData[0],info.compressize);//info.compressize);
			if(err!=0){
				wchar_t str[256];
				swprintf_s(str,L"err = %d",err);
				pList->InsertString(0,str);
				info.compressize	=	info.size;
				//AfxMessageBox(s.c_str());
				continue;
			}
			
			if(iOffset+info.compressize	>	uiBlockSize){
				uiCurrentData++;
				iOffset=0;
			}
			FILE*&	hFile	=		pFileData[uiCurrentData];
			if(hFile==NULL){
				TCHAR strTemp[MAX_PATH];
				swprintf_s(strTemp,_T("Data%d"),uiCurrentData);
				hFile	=	_wfopen(strTemp,L"wb");
			}

			fwrite(&vecCompressData[0],info.compressize,1,hFile);
			info.idx	=	uiCurrentData;
			info.offset	=	iOffset;
			info.crc32	=	CRC32(&vecTempData[0],info.size);
			iOffset+=info.compressize;

			std::string s1	=	WideByte2Acsi(s);
			for(int i=0;i<s1.size();i++){
				s1[i]	=	toupper(s1[i]);
			}
			info.fileid	=	StringHash(s1.c_str());
			vecFileInfo.push_back(info);
			if(info.size>maxSize){
				maxSize	=	info.size;
			}
			if(info.compressize>maxCompressSize){
				maxCompressSize	=	info.compressize;
			}
		}else{
			continue;
		}
	}
	for(U32	i=0;i<FILEDATA_COUNT;i++){
		if(pFileData[i]!=NULL){
			fclose(pFileData[i]);
		}
	}

	fwrite(&vecFileInfo[0],vecFileInfo.size()*sizeof(FileInfo),1,pFileIndex);
	fclose(pFileIndex);

	for(U32	i=0;i<FILEDATA_COUNT;i++){
		TCHAR strTemp[MAX_PATH];
		swprintf_s(strTemp,_T("Data%d"),uiCurrentData);
		pFileData[i]	=	_wfopen(strTemp,L"rb");
	}
	for(U32	i=0;i<vecFileInfo.size();i++){
		FileInfo& info = vecFileInfo[i];
		FILE* pFile = pFileData[info.idx];
		vecCompressData.resize(info.compressize);
		vecTempData.resize(info.size);
		_fseeki64(pFile,info.offset,SEEK_SET);
		fread(&vecCompressData[0],info.compressize,1,pFile);
		
		U32	dwDest=info.size;
		MDescompress(&vecCompressData[0],info.compressize,&vecTempData[0],dwDest);
		U32	crc=CRC32(&vecTempData[0],info.size);
		if(crc!=info.crc32){
			wchar_t str[MAX_PATH];
			swprintf_s(str,L"%s c=%d size=%d offset=%d crc32=%d",vecString[i].c_str(),i,info.compressize,info.size,info.offset,info.crc32);
			pList->InsertString(0,str);
			continue;
		};
	}

	AfxMessageBox(_T("Finished!"));
}
