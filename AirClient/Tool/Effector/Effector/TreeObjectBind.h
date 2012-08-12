#pragma once

#include "EngineCommon.h"
// TreeObjectBind dialog

class TreeObjectBind : public CDialog
{
	DECLARE_DYNAMIC(TreeObjectBind)

public:
	TreeObjectBind(const std::vector<TreeObj*>&	vec,CWnd* pParent = NULL);   // standard constructor
	virtual ~TreeObjectBind();

// Dialog Data
	enum { IDD = IDD_DIALOG_BIND };

	TreeObj*	GetSelectObj();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	std::vector<TreeObj*>	vecObject;
	TreeObj*				pSelectObj;
public:
	afx_msg void OnBnClickedOk();
};
