
// TextureCompareDlg.h : 头文件
//

#pragma once


// CTextureCompareDlg 对话框
class CTextureCompareDlg : public CDialogEx
{
// 构造
public:
	CTextureCompareDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEXTURECOMPARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemActivateListTextureName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListTextureName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListTextureCompare(NMHDR *pNMHDR, LRESULT *pResult);
	bool bLoad;

	bool bUpdateCompare;

	HBITMAP m_BMP;
	HBITMAP m_BMPCOMPARE;
	afx_msg void OnLvnColumnclickListTextureName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListTextureCompare(NMHDR *pNMHDR, LRESULT *pResult);
};
