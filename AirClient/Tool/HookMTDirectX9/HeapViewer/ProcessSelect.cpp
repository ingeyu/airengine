// ProcessSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "HeapViewer.h"
#include "ProcessSelect.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <TlHelp32.h>


// ProcessSelect 对话框

IMPLEMENT_DYNAMIC(ProcessSelect, CDialog)

ProcessSelect::ProcessSelect(CWnd* pParent /*=NULL*/)
	: CDialog(ProcessSelect::IDD, pParent)
{
	iPID	=	0;
}

ProcessSelect::~ProcessSelect()
{
}

void ProcessSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ProcessSelect, CDialog)
	ON_BN_CLICKED(IDOK, &ProcessSelect::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ProcessSelect::OnBnClickedCancel)
END_MESSAGE_MAP()


// ProcessSelect 消息处理程序


void ProcessSelect::OnBnClickedOk()
{
	CListCtrl*	pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_PROCESS_SELECT);

	POSITION pos = pCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL){
		//TRACE0("No items were selected!\n");
		MessageBoxW(L"No Process Selected!");
	}
	else
	{
		int nItem = pCtrl->GetNextSelectedItem(pos);
		iPID	=	(int)pCtrl->GetItemData(nItem);
		// TODO: 在此添加控件通知处理程序代码
		CDialog::OnOK();
	}
	
}


void ProcessSelect::OnBnClickedCancel()
{
	iPID	=	0;
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void ProcessSelect::Refresh(CListCtrl*	pCtrl)
{
	pCtrl->DeleteAllItems();

	PROCESSENTRY32 pe32;    //实例化一个快照结构 
	DWORD ExplorerID = 0;     //存放ExplorerPID 
	pe32.dwSize = sizeof(pe32);  //设置这个结构的大小 
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	if(hProcessSnap == INVALID_HANDLE_VALUE) 
	{  
		return ; 
	} 

	int iProcessCount	=	0;

	wchar_t strModuleName[512];
	GetModuleFileNameW(NULL,strModuleName,512);

	BOOL bMore = ::Process32First(hProcessSnap,&pe32); 
	while(bMore) 
	{  
		wchar_t* pStr	=	wcsstr(strModuleName,pe32.szExeFile);
		if(	pStr!=NULL ||
			wcscmp(L"System",pe32.szExeFile)==0	||
			wcscmp(L"[System Process]",pe32.szExeFile)==0	)  
		{   

		}else{
			wchar_t strPID[256];
			wsprintf(strPID,L"%d",pe32.th32ProcessID);
			int iItem = pCtrl->InsertItem(iProcessCount++,pe32.szExeFile);
			pCtrl->SetItemText(iItem,1,strPID);
			pCtrl->SetItemData(iItem,(DWORD_PTR)pe32.th32ProcessID);
		}

		bMore=::Process32Next(hProcessSnap,&pe32); 
		if(!bMore){
			break;
		}
	} 
	::CloseHandle(hProcessSnap);

	//pCtrl->SetItemText()
}

BOOL ProcessSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	CListCtrl*	pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_PROCESS_SELECT);
	//pCtrl->sET

	DWORD dwStyle = pCtrl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	pCtrl->SetExtendedStyle(dwStyle); //设置扩展风格

	pCtrl->InsertColumn(0,L"Name",0,150);
	pCtrl->InsertColumn(1,L"PID",0,50);
	
	

	Refresh(pCtrl);

	return TRUE;
}
