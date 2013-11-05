#pragma once


// CSetupFinshed 对话框

class CSetupFinshed : public CDialog
{
	DECLARE_DYNAMIC(CSetupFinshed)

public:
	CSetupFinshed(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetupFinshed();

// 对话框数据
	enum { IDD = IDD_DIALOG_FINISHED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	wchar_t strGamePath[1024];
};
