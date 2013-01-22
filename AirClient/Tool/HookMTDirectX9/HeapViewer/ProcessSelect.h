#pragma once


// ProcessSelect 对话框

class ProcessSelect : public CDialog
{
	DECLARE_DYNAMIC(ProcessSelect)

public:
	ProcessSelect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProcessSelect();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_PROCESSSELECT };

	int GetPID(){
		return iPID;
	};

	void	Refresh(CListCtrl*	pCtrl);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	int iPID;
};
