#pragma once


// CSetupSelectPath 对话框

class CSetupSelectPath : public CDialog
{
	DECLARE_DYNAMIC(CSetupSelectPath)

public:
	CSetupSelectPath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetupSelectPath();

// 对话框数据
	enum { IDD = IDD_DIALOG_SELECT_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	wchar_t			m_strSetupPath[1024];
	DWORD			m_dwLength;
	afx_msg void OnLvnItemchangedListHd(NMHDR *pNMHDR, LRESULT *pResult);
};
