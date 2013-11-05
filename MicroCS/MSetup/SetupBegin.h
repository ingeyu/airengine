#pragma once


// CSetupBegin 对话框

class CSetupBegin : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupBegin)

public:
	CSetupBegin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetupBegin();

// 对话框数据
	enum { IDD = IDD_DIALOG_BEGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
