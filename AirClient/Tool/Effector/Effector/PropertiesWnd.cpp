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

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Effector.h"
#include "PropertiesStruct.h"
#include "EngineCommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_pSelectObj	=	NULL;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,CPropertiesWnd::OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建组合:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}

	m_wndObjectCombo.AddString(_T("应用程序"));
	m_wndObjectCombo.AddString(_T("属性窗口"));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	// 测试调用
// 	ViewProperties( &sRasterizer );
// 	ViewProperties( &sRenderTarget );
// 	ViewProperties( &sBlend );
// 	ViewProperties( &sDepthStencil );
// 	ViewProperties( &sDepthStencilop );
// 	ViewProperties( &sSampler );

//	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("外观"));

// 	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("三维外观"), (_variant_t) false, _T("指定窗口的字体不使用粗体，并且控件将使用三维边框")));
// 
// 	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("边框"), _T("对话框外框"), _T("其中之一:“无”、“细”、“可调整大小”或“对话框外框”"));
// 	pProp->AddOption(_T("无"));
// 	pProp->AddOption(_T("细"));
// 	pProp->AddOption(_T("可调整大小"));
// 	pProp->AddOption(_T("对话框外框"));
// 	pProp->AllowEdit(FALSE);
// 
// 	pGroup1->AddSubItem(pProp);
// 	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("标题"), (_variant_t) _T("关于"), _T("指定窗口标题栏中显示的文本")));

// 	m_wndPropList.AddProperty(pGroup1);
// 
// 	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( _T( "FileModel" ), strFillMode[sParForView.FillMode], _T( "E_VALUE_LIST" ) );
// 	pProp->AddOption( strFillMode[0] );
// 	pProp->AddOption( strFillMode[1] );
// 	pProp->AddOption( strFillMode[2] );
// 	pProp->AddOption( strFillMode[3] );
// 	pProp->AllowEdit( FALSE );
// 	pGroup1->AddSubItem( pProp );

// 	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("窗口大小"), 0, TRUE);
// 
// 	pProp = new CMFCPropertyGridProperty(_T("高度"), (_variant_t) 250l, _T("指定窗口的高度"));
// 	pProp->EnableSpinControl(TRUE, 50, 300);
// 	pSize->AddSubItem(pProp);
// 
// 	pProp = new CMFCPropertyGridProperty( _T("宽度"), (_variant_t) 150l, _T("指定窗口的宽度"));
// 	pProp->EnableSpinControl(TRUE, 50, 200);
// 	pSize->AddSubItem(pProp);
// 
// 	m_wndPropList.AddProperty(pSize);
// 
// 	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("字体"));
// 
// 	LOGFONT lf;
// 	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
// 	font->GetLogFont(&lf);
// 
// 	lstrcpy(lf.lfFaceName, _T("宋体, Arial"));
// 
// 	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("字体"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("指定窗口的默认字体")));
// 	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("使用系统字体"), (_variant_t) true, _T("指定窗口使用“MS Shell Dlg”字体")));
// 
// 	m_wndPropList.AddProperty(pGroup2);
// 
// 	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("杂项"));
// 	pProp = new CMFCPropertyGridProperty(_T("(名称)"), _T("应用程序"));
// 	pProp->Enable(FALSE);
// 	pGroup3->AddSubItem(pProp);
// 
// 	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("窗口颜色"), RGB(210, 192, 254), NULL, _T("指定默认的窗口颜色"));
// 	pColorProp->EnableOtherButton(_T("其他..."));
// 	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
// 	pGroup3->AddSubItem(pColorProp);
// 
// 	static const TCHAR szFilter[] = _T("图标文件(*.ico)|*.ico|所有文件(*.*)|*.*||");
// 	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("图标"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("指定窗口图标")));
// 
// 	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("文件夹"), _T("c:\\")));
// 
// 	m_wndPropList.AddProperty(pGroup3);
// 
// 	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("层次结构"));
// 
// 	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("第一个子级"));
// 	pGroup4->AddSubItem(pGroup41);
// 
// 	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("第二个子级"));
// 	pGroup41->AddSubItem(pGroup411);
// 
// 	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 1"), (_variant_t) _T("值 1"), _T("此为说明")));
// 	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 2"), (_variant_t) _T("值 2"), _T("此为说明")));
// 	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 3"), (_variant_t) _T("值 3"), _T("此为说明")));
// 
// 	pGroup4->Expand(FALSE);
// 	m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

void CPropertiesWnd::ViewProperties( const  Air::Client::Render::RASTERIZER_DESC* pRasterizer )
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("光栅化状态"));
	m_wndPropList.AddProperty(pGroup);

// 	AddCombo( pGroup, _T("enumFillMode"), strenumFillMode,nenumFillModeCount,pRasterizer->FillMode, _T("Note"),FALSE );
// 	AddCombo( pGroup, _T("enumCullMode"),strenumCullMode,nenumCullModeCount, pRasterizer->CullMode, _T("Note"),FALSE );
// 	AddMember( pGroup, _T("FrontCounterClockwise"), pRasterizer->FrontCounterClockwise, _T("Note"), TRUE );
// 	AddMember( pGroup, _T("DepthBias"), pRasterizer->DepthBias, _T("Note"), TRUE );
// 	AddMember( pGroup, _T("DepthBiasClamp"), pRasterizer->DepthBiasClamp, _T("Note"), TRUE );
// 	AddMember( pGroup, _T("SlopeScaledDepthBias"), pRasterizer->SlopeScaledDepthBias, _T("Note"), TRUE );
// 	AddMember( pGroup, _T("DepthClipEnable"), pRasterizer->DepthClipEnable, _T("Note"), TRUE );
// 	AddMember( pGroup, _T("ScissorEnable"), pRasterizer->ScissorEnable, _T("Note"), TRUE );
// 	AddMember( pGroup, _T("MultisampleEnable"), pRasterizer->MultisampleEnable, _T("Note"), TRUE );
// 	AddMember( pGroup, _T("AntialiasedLineEnable"), pRasterizer->AntialiasedLineEnable, _T("Note"), TRUE );
// 
// 	memcpy( &m_Rasterizer, pRasterizer, sizeof( Air::Client::Render::RASTERIZER_DESC ) );
}

void CPropertiesWnd::ViewProperties( const Air::Client::Render::RENDER_TARGET_BLEND* pRenderTarget )
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("渲染目标混合"));
	m_wndPropList.AddProperty(pGroup);

	memcpy( &m_RenderTarget, pRenderTarget, sizeof( Air::Client::Render::RENDER_TARGET_BLEND ) );
}

void CPropertiesWnd::ViewProperties( const Air::Client::Render::BLEND_DESC* pBlend )
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("混合状态"));
	m_wndPropList.AddProperty(pGroup);

	memcpy( &m_Blend, pBlend, sizeof( Air::Client::Render::BLEND_DESC ) );
}

void CPropertiesWnd::ViewProperties( const Air::Client::Render::DEPTH_STENCILOP* pDepthStencilop )
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("深度模板操作"));
	m_wndPropList.AddProperty(pGroup);

	memcpy( &m_DepthStencilop, pDepthStencilop, sizeof( Air::Client::Render::DEPTH_STENCILOP ) );
}

void CPropertiesWnd::ViewProperties( const Air::Client::Render::DEPTH_STENCIL_DESC* pDepthStencil )
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("深度状态"));
	m_wndPropList.AddProperty(pGroup);

	memcpy( &m_DepthStencil, pDepthStencil, sizeof( Air::Client::Render::DEPTH_STENCIL_DESC ) );
}

void CPropertiesWnd::ViewProperties( const Air::Client::Render::SAMPLER_DESC* pSampler )
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("采样状态"));
	m_wndPropList.AddProperty(pGroup);

	memcpy( &m_Sampler, pSampler, sizeof( Air::Client::Render::SAMPLER_DESC ) );
}

void CPropertiesWnd::addListener( Listener* pListener )
{
	if ( NULL == pListener )
	{
		return;
	}
	ConstIterListener cIter = m_vListener.begin();
	for ( ; cIter != m_vListener.end(); ++cIter )
	{
		if ( *cIter == pListener )
		{
			return;
		}
	}
	m_vListener.push_back( pListener );
}

void CPropertiesWnd::delListener( Listener* pListener )
{
	if ( NULL == pListener )
	{
		return;
	}
	IterListener Iter = m_vListenerDel.begin();
	for ( ; Iter != m_vListenerDel.end(); ++Iter )
	{
		if ( *Iter == pListener )
		{
			return;
		}
	}
	m_vListenerDel.push_back( pListener );
}

void CPropertiesWnd::_changeRenderTarget( const Air::Client::Render::RENDER_TARGET_BLEND* pRenderTarget )
{
	ConstIterListener cIter = m_vListener.begin();
	for ( ; cIter != m_vListener.end(); ++cIter )
	{
		(*cIter)->_changeRenderTarget( &m_RenderTarget );
	}
}

void CPropertiesWnd::_changeBlend( const Air::Client::Render::BLEND_DESC* pBlend )
{
	ConstIterListener cIter = m_vListener.begin();
	for ( ; cIter != m_vListener.end(); ++cIter )
	{
		(*cIter)->_changeBlend( &m_Blend );
	}
}

void CPropertiesWnd::_changeDepthStencilop( const Air::Client::Render::DEPTH_STENCILOP* pDepthStencilop )
{
	ConstIterListener cIter = m_vListener.begin();
	for ( ; cIter != m_vListener.end(); ++cIter )
	{
		(*cIter)->_changeDepthStencilop( &m_DepthStencilop );
	}
}

void CPropertiesWnd::_changeDepthStencil( const Air::Client::Render::DEPTH_STENCIL_DESC* pDepthStencil )
{
	ConstIterListener cIter = m_vListener.begin();
	for ( ; cIter != m_vListener.end(); ++cIter )
	{
		(*cIter)->_changeDepthStencil( &m_DepthStencil );
	}
}

void CPropertiesWnd::_changeRasterizer( const Air::Client::Render::RASTERIZER_DESC* pRasterizer )
{
	ConstIterListener cIter = m_vListener.begin();
	for ( ; cIter != m_vListener.end(); ++cIter )
	{
		(*cIter)->_changeRasterizer( &m_Rasterizer );
	}
}

void CPropertiesWnd::_changeSampler( const Air::Client::Render::SAMPLER_DESC* pSampler )
{
	ConstIterListener cIter = m_vListener.begin();
	for ( ; cIter != m_vListener.end(); ++cIter )
	{
		(*cIter)->_changeSampler( &m_Sampler );
	}
}

LRESULT CPropertiesWnd::OnPropertyChanged( WPARAM w,LPARAM l )
{
	CMFCPropertyGridProperty*	pProperty	=	(CMFCPropertyGridProperty*)l;
	if(pProperty!=NULL){
		if(m_pSelectObj!=NULL){
			m_pSelectObj->OnPropertyChanged(pProperty);
			m_pSelectObj->ReLoad();
		}
// 		int	iVal			=	pProperty->GetData();
// 		CString	strName		=	pProperty->GetName();
// 		if ( (strName.Compare( _T("enumFillMode"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 			//m_Rasterizer.FillMode = 0;
// 		}
// 		else if ( (strName.Compare( _T("enumCullMode"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 			//m_Rasterizer.CullMode = 0;
// 		}
// 		else if ( (strName.Compare( _T("FrontCounterClockwise"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
// 		else if ( (strName.Compare( _T("DepthBias"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
// 		else if ( (strName.Compare( _T("DepthBiasClamp"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
// 		else if ( (strName.Compare( _T("SlopeScaledDepthBias"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
// 		else if ( (strName.Compare( _T("DepthClipEnable"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
// 		else if ( (strName.Compare( _T("ScissorEnable"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
// 		else if ( (strName.Compare( _T("MultisampleEnable"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
// 		else if ( (strName.Compare( _T("AntialiasedLineEnable"))) == 0 )
// 		{
// 			CString	strValue	=	pProperty->GetValue();
// 		}
	}
	return	S_OK;
}

void CPropertiesWnd::ShowProperty( TreeObj* pObj )
{
	m_wndPropList.RemoveAll();
	m_pSelectObj	=	pObj;
	if(m_pSelectObj==NULL){
		return;
	}
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(m_pSelectObj->GetName().c_str());
	m_wndPropList.AddProperty(pGroup);

	m_pSelectObj->OnShowProperty(pGroup);

	m_wndPropList.ExpandAll();
}


