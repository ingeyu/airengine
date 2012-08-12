// TreeObjectBind.cpp : implementation file
//

#include "stdafx.h"
#include "Effector.h"
#include "TreeObjectBind.h"
#include "afxdialogex.h"


// TreeObjectBind dialog

IMPLEMENT_DYNAMIC(TreeObjectBind, CDialog)

TreeObjectBind::TreeObjectBind(const std::vector<TreeObj*>&	vec,CWnd* pParent /*=NULL*/)
	: CDialog(TreeObjectBind::IDD, pParent),vecObject(vec)
{
	pSelectObj	=	vec[0];
}

TreeObjectBind::~TreeObjectBind()
{
}

void TreeObjectBind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	CComboBox*	pBox	=	(CComboBox*)GetDlgItem(IDC_COMBO_BIND);
	unsigned long uiSize	=	vecObject.size();
	for(unsigned long i=0;i<uiSize;i++){
		pBox->AddString(vecObject[i]->GetName().c_str());
	}
	pBox->SetCurSel(0);
}


BEGIN_MESSAGE_MAP(TreeObjectBind, CDialog)
	ON_BN_CLICKED(IDOK, &TreeObjectBind::OnBnClickedOk)
END_MESSAGE_MAP()


// TreeObjectBind message handlers


void TreeObjectBind::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CComboBox*	pBox	=	(CComboBox*)GetDlgItem(IDC_COMBO_BIND);
	pSelectObj	=	vecObject[pBox->GetCurSel()];
	CDialog::OnOK();
}

TreeObj* TreeObjectBind::GetSelectObj()
{
	return	pSelectObj;
}
