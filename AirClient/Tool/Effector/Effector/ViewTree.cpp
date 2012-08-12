// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

#include "stdafx.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{

	//this->se
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

BOOL CViewTree::PreTranslateMessage( MSG* pMsg )
{
	// TODO: 在此添加专用代码和/或调用基类
	BOOL bHandledMsg = FALSE;

	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
			case VK_RETURN:   
				if (::GetKeyState(VK_CONTROL) & 0x8000)
				{
					break;
				}
				if (GetEditControl())
				{
					::TranslateMessage(pMsg);
					::DispatchMessage(pMsg);
					bHandledMsg = TRUE;
				}
				break;
			default: break;
			} // switch (pMsg->wParam)
		} // WM_KEYDOWN
		break;
	default: break;
	} // switch (pMsg->message)                  
	// continue normal translation and dispatching             
	return (bHandledMsg ?TRUE : CTreeCtrl::PreTranslateMessage(pMsg));


}
