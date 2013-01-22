// HeapPreview.cpp : 实现文件
//

#include "stdafx.h"
#include "HeapViewer.h"
#include "HeapPreview.h"
#include "afxdialogex.h"


// CHeapPreview 对话框

IMPLEMENT_DYNAMIC(CHeapPreview, CDialog)

CHeapPreview::CHeapPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CHeapPreview::IDD, pParent)
{

}

CHeapPreview::~CHeapPreview()
{
}

void CHeapPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHeapPreview, CDialog)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_VIEW, &CHeapPreview::OnTRBNThumbPosChangingSliderView)
END_MESSAGE_MAP()


// CHeapPreview 消息处理程序


void CHeapPreview::OnTRBNThumbPosChangingSliderView(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
