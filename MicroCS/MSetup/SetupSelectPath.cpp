// SetupSelectPath.cpp : 实现文件
//

#include "stdafx.h"
#include "MSetup.h"
#include "SetupSelectPath.h"
#include "afxdialogex.h"


// CSetupSelectPath 对话框

IMPLEMENT_DYNAMIC(CSetupSelectPath, CDialog)

CSetupSelectPath::CSetupSelectPath(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupSelectPath::IDD, pParent)
{
	memset(m_strSetupPath,0,sizeof(wchar_t)*1024);
	m_dwLength=0;
}

CSetupSelectPath::~CSetupSelectPath()
{
}

void CSetupSelectPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetupSelectPath, CDialog)
	ON_BN_CLICKED(IDOK, &CSetupSelectPath::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_HD, &CSetupSelectPath::OnLvnItemchangedListHd)
END_MESSAGE_MAP()


// CSetupSelectPath 消息处理程序


void CSetupSelectPath::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCEditBrowseCtrl* pBrowser	=	(CMFCEditBrowseCtrl*)GetDlgItem(IDC_MFCEDITBROWSE_PATH);
	if(pBrowser!=NULL){

		pBrowser->GetWindowTextW(m_strSetupPath,1024);
		m_dwLength	=	wcslen(m_strSetupPath);
		for(DWORD i=0;i<m_dwLength;i++){
			if(m_strSetupPath[i]==L'/'){
				m_strSetupPath[i]=L'\\';
			}else{
				m_strSetupPath[i]	=	tolower(m_strSetupPath[i]);
			}
			
		}
		//路径末尾加上反斜杠
		if(m_strSetupPath[m_dwLength-1]!=L'\\'){
			m_strSetupPath[m_dwLength]	=	L'\\';
			m_dwLength++;
			m_strSetupPath[m_dwLength]=	0;
		}
		wchar_t strFixPath[1024]={0};
		DWORD realLength=0;
		for(DWORD i=0;i<m_dwLength;i++){
			if(m_strSetupPath[i]==L'\\'	&&	strFixPath[realLength-1]==L'\\'){
				continue;
			}

			strFixPath[realLength]=m_strSetupPath[i];
			realLength++;
			
		}
		memcpy(m_strSetupPath,strFixPath,sizeof(wchar_t)*1024);
		m_dwLength	=	realLength;

		bool bAbsPath	=	true;
		//判断是不是绝对路径
		if(m_dwLength<2){
			bAbsPath=false;
			GetCurrentDirectoryW(1024,strFixPath);
		}else{
			memcpy(strFixPath,m_strSetupPath,sizeof(wchar_t)*2);
		}
		if(strFixPath[0]>=L'a' && strFixPath[0]<=L'z' && strFixPath[1]==':'){
			bAbsPath	=	true;	
		}else{
			GetCurrentDirectoryW(32,strFixPath);
		}
		strFixPath[3]=0;

		DWORD serialNumber, maxComponentLength, fsFlags;
		TCHAR szFileSystem[12];
		TCHAR szVolumeName[100];
		if (GetVolumeInformation(strFixPath,szVolumeName,sizeof(szVolumeName),&serialNumber,&maxComponentLength,&fsFlags,szFileSystem,sizeof(szFileSystem))) 
		{
			_ULARGE_INTEGER lpFreeBytesAvailableToCaller, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes;
			GetDiskFreeSpaceEx(strFixPath, &lpFreeBytesAvailableToCaller, &lpTotalNumberOfBytes, &lpTotalNumberOfFreeBytes);
			float fFree	= (double)(lpTotalNumberOfFreeBytes.QuadPart) / (1024 *1024);
			fFree/=1024.0f;
			if(fFree<15){
				wchar_t strError[1024];
				swprintf_s(strError,L"磁盘(%s)剩余空间不足，无法安装游戏",strFixPath);
				AfxMessageBox(strError);
				return;
			}
		}else{
			wchar_t strError[1024];
			swprintf_s(strError,L"磁盘(%s)不存在，无法安装游戏",strFixPath);
			AfxMessageBox(strError);
			return;
		}
		
		if(m_dwLength==0){
			AfxMessageBox(L"安装路径不能为空");
			return;
		}
		//检查路径有效性
		wchar_t strTemp[1024];
		for(DWORD i=0;i<m_dwLength;i++){
			if(m_strSetupPath[i]==L'\\'){
				memset(strTemp,0,sizeof(wchar_t)*1024);
				memcpy(strTemp,m_strSetupPath,sizeof(wchar_t)*i);
				DWORD dwAttr	=	GetFileAttributesW(strTemp);
				if(dwAttr==INVALID_FILE_ATTRIBUTES){
					wchar_t strError[1024];
					swprintf_s(strError,L"文件夹(%s)不存在，需要创建文件夹才能够安装游戏",strTemp);
					if(IDOK	==	AfxMessageBox(strError,IDOK)){
						if(!CreateDirectoryW(strTemp,NULL)){

							swprintf_s(strError,L"创建文件夹(%s)失败,游戏无法安装到该目录下",strTemp);
							AfxMessageBox(strError);
							return;
						}
					}else{

						return;
					}
				}else if((FILE_ATTRIBUTE_DIRECTORY|dwAttr)==0){
					wchar_t strError[1024];
					swprintf_s(strError,L"(%s)不是一个文件夹,游戏无法安装到该目录下",strTemp);
					AfxMessageBox(strError);
					return;
				}
			}
		}

	}
	CDialog::OnOK();
}


BOOL CSetupSelectPath::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	GetCurrentDirectoryW(1024,m_strSetupPath);
	m_dwLength	=	wcslen(m_strSetupPath);
	for(DWORD i=0;i<m_dwLength;i++){
		if(m_strSetupPath[i]==L'/'){
			m_strSetupPath[i]=L'\\';
		}
	}
	if(m_strSetupPath[m_dwLength-1]!=L'\\'){
		m_strSetupPath[m_dwLength]	=	L'\\';
		m_dwLength++;
		m_strSetupPath[m_dwLength]=	0;
	}

	CMFCEditBrowseCtrl* pBrowser	=	(CMFCEditBrowseCtrl*)GetDlgItem(IDC_MFCEDITBROWSE_PATH);
	if(pBrowser!=NULL){
		pBrowser->SetWindowTextW(m_strSetupPath);
	}

	CListCtrl* pList	=	(CListCtrl*)GetDlgItem(IDC_LIST_HD);

	pList->SetExtendedStyle(LVS_EX_FULLROWSELECT );

	pList->InsertColumn(0,L"分区",0,50);
	pList->InsertColumn(1,L"分区名",0,150);
	pList->InsertColumn(2,L"分区格式",0,75);
	pList->InsertColumn(3,L"总空间",0,75);
	pList->InsertColumn(4,L"剩余空间",0,75);

	if(pList!=NULL){
		wchar_t	strHD[4]=L"c:\\";
		int iItem=0;
		for(;strHD[0]!=L'z';strHD[0]++)
		{
			DWORD serialNumber, maxComponentLength, fsFlags;
			TCHAR szFileSystem[12];
			TCHAR szVolumeName[100];
			if (GetVolumeInformation(strHD,szVolumeName,sizeof(szVolumeName),&serialNumber,&maxComponentLength,&fsFlags,szFileSystem,sizeof(szFileSystem))) 
			{
				_ULARGE_INTEGER lpFreeBytesAvailableToCaller, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes;
				GetDiskFreeSpaceEx(strHD, &lpFreeBytesAvailableToCaller, &lpTotalNumberOfBytes, &lpTotalNumberOfFreeBytes);
				wchar_t str[1024];

			
				iItem	=	pList->InsertItem(iItem,strHD);
				pList->SetItemText(iItem,1,szVolumeName);
				pList->SetItemText(iItem,2,szFileSystem);
				float fTotal	=	lpTotalNumberOfBytes.QuadPart / (1024 *1024);
				swprintf_s(str,L"%.2fG",fTotal/1024.0f);
				pList->SetItemText(iItem,3,str);
				float fFree	=	lpTotalNumberOfFreeBytes.QuadPart / (1024 *1024);
				swprintf_s(str,L"%.2fG",fFree/1024.0f);
				pList->SetItemText(iItem,4,str);
				iItem++;
			}
		}
	}

	GetDlgItem(IDC_IPADDRESS1)->SetWindowText(L"10.240.38.103");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetupSelectPath::OnLvnItemchangedListHd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pList	=	(CListCtrl*)GetDlgItem(IDC_LIST_HD);
	wchar_t str[512];
	pList->GetItemText(pNMLV->iItem,0,str,512);

	swprintf_s(m_strSetupPath,L"%sSNDA\\WorldZero\\",str);
	m_dwLength	=	wcslen(m_strSetupPath);
	CMFCEditBrowseCtrl* pBrowser	=	(CMFCEditBrowseCtrl*)GetDlgItem(IDC_MFCEDITBROWSE_PATH);
	if(pBrowser!=NULL){
		pBrowser->SetWindowTextW(m_strSetupPath);
	}
	*pResult = 0;
}
