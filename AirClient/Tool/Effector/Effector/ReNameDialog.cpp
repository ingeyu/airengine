// ReNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Effector.h"
#include "ReNameDialog.h"
#include "afxdialogex.h"


// ReNameDialog dialog

IMPLEMENT_DYNAMIC(ReNameDialog, CDialog)

ReNameDialog::ReNameDialog(const CString&	strName,CWnd* pParent /*=NULL*/)
	: CDialog(ReNameDialog::IDD, pParent)
{
	strInitName	=	strName;
}

ReNameDialog::~ReNameDialog()
{
}

void ReNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	SetDlgItemTextW(IDC_EDIT_RENAME,strInitName.GetBuffer());
	GetDlgItem(IDC_EDIT_RENAME)->SetActiveWindow();
}


BEGIN_MESSAGE_MAP(ReNameDialog, CDialog)
	ON_BN_CLICKED(IDOK, &ReNameDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ReNameDialog message handlers


void ReNameDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	GetDlgItemTextW(IDC_EDIT_RENAME,strInitName);
	CDialog::OnOK();
}
