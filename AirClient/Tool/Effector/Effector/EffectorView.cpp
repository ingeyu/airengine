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

// EffectorView.cpp : CEffectorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Effector.h"
#endif

#include "EffectorDoc.h"
#include "EffectorView.h"
#include "EngineManager.h"
#include "EffectorFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEffectorView

IMPLEMENT_DYNCREATE(CEffectorView, CView)

BEGIN_MESSAGE_MAP(CEffectorView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEffectorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_COMMAND(ID_ADD_EFFECT, &CEffectorView::OnAddEffect)
	ON_COMMAND(ID_ADD_PHASE, &CEffectorView::OnAddPhase)
	ON_COMMAND(ID_RENDERSTATE_RS, &CEffectorView::OnRenderstateRs)
	ON_COMMAND(ID_RENDERSTATE_DS, &CEffectorView::OnRenderstateDs)
	ON_COMMAND(ID_RENDERSTATE_BS, &CEffectorView::OnRenderstateBs)
END_MESSAGE_MAP()

// CEffectorView 构造/析构

CEffectorView::CEffectorView()
{
	// TODO: 在此处添加构造代码

}

CEffectorView::~CEffectorView()
{
}

BOOL CEffectorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	
	return CView::PreCreateWindow(cs);
}

// CEffectorView 绘制

void CEffectorView::OnDraw(CDC* /*pDC*/)
{
	CEffectorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//  	EngineManager::GetSingleton()->Init(GetSafeHwnd());
//  	HWND	hWnd	=	GetSafeHwnd();
//  	RECT r;
//  	GetClientRect(&r);
//  	EngineManager::GetSingleton()->ResizeWindow(r.right	-	r.left,r.bottom-r.top);
	// TODO: 在此处为本机数据添加绘制代码

	//EngineManager::GetSingleton()->RenderOneFrame();
}


// CEffectorView 打印


void CEffectorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEffectorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEffectorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEffectorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CEffectorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEffectorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEffectorView 诊断

#ifdef _DEBUG
void CEffectorView::AssertValid() const
{
	CView::AssertValid();
}

void CEffectorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEffectorDoc* CEffectorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEffectorDoc)));
	return (CEffectorDoc*)m_pDocument;
}
int CEffectorView::OnCreate(LPCREATESTRUCT lpcs)
{
	//EngineManager::GetSingleton()->Init(GetSafeHwnd());
	OutputDebugString(_T("OnCreate\n"));
	return	CView::OnCreate(lpcs);
}

#endif //_DEBUG


void CEffectorView::OnAddEffect()
{
	CEffectorDoc*	pDoc	=	GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				pFile->AddEffect(_T("Effect"));
			}
		}
	}
}


void CEffectorView::OnAddPhase()
{
	// TODO: Add your command handler code here
	CEffectorDoc*	pDoc	=	GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				if(pObj->GetType()	==	enTOT_Effect){
					Effect*	pEffect	=	(Effect*)pObj;
					pEffect->AddPhase(_T("Phase"));
				}
			}
		}
	}
}


void CEffectorView::OnRenderstateRs()
{
	// TODO: Add your command handler code here
}


void CEffectorView::OnRenderstateDs()
{
	// TODO: Add your command handler code here
}


void CEffectorView::OnRenderstateBs()
{
	// TODO: Add your command handler code here
}

// CEffectorView 消息处理程序
