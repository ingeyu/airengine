#pragma once


// ReNameDialog dialog

class ReNameDialog : public CDialog
{
	DECLARE_DYNAMIC(ReNameDialog)

public:
	ReNameDialog(const CString&	strName,CWnd* pParent = NULL);   // standard constructor
	virtual ~ReNameDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_RENAME };
	CString	strInitName;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedOk();
};
