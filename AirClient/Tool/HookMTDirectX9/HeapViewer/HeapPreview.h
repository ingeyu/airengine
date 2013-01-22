#pragma once


// CHeapPreview 对话框

class CHeapPreview : public CDialog
{
	DECLARE_DYNAMIC(CHeapPreview)

public:
	CHeapPreview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHeapPreview();

// 对话框数据
	enum { IDD = IDD_DIALOG_HEAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTRBNThumbPosChangingSliderView(NMHDR *pNMHDR, LRESULT *pResult);
};
