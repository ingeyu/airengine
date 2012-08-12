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

#pragma once
#include "stdafx.h"

// 测试对象


class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};


class TreeObj;

class CPropertiesWnd : public CDockablePane
{
// 构造
public:
	CPropertiesWnd();

	void AdjustLayout();

// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

// 实现
public:
	virtual ~CPropertiesWnd();

	// 接口
	class Listener{
	public:
		virtual void _changeRenderTarget( const  Air::Client::Render::RENDER_TARGET_BLEND* pRenderTarget ){};
		virtual void _changeBlend( const  Air::Client::Render::BLEND_DESC* pBlend ){};
		virtual void _changeDepthStencilop( const  Air::Client::Render::DEPTH_STENCILOP* pDepthStencilop ){};
		virtual void _changeDepthStencil( const  Air::Client::Render::DEPTH_STENCIL_DESC* pDepthStencil ){};
		virtual void _changeRasterizer( const  Air::Client::Render::RASTERIZER_DESC* pRasterizer ){};
		virtual void _changeSampler( const  Air::Client::Render::SAMPLER_DESC* pSampler ){};
	};
	void addListener( Listener* pListener );
	void delListener( Listener* pListener );

	// 属性显示
	void ViewProperties( const  Air::Client::Render::RENDER_TARGET_BLEND* pRenderTarget );
	void ViewProperties( const  Air::Client::Render::BLEND_DESC* pBlend );
	void ViewProperties( const  Air::Client::Render::DEPTH_STENCILOP* pDepthStencilop );
	void ViewProperties( const  Air::Client::Render::DEPTH_STENCIL_DESC* pDepthStencil );
	void ViewProperties( const  Air::Client::Render::RASTERIZER_DESC* pRasterizer );
	void ViewProperties( const  Air::Client::Render::SAMPLER_DESC* pSampler );

	void	ShowProperty(TreeObj*	pObj);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	afx_msg	LRESULT	OnPropertyChanged(WPARAM w,LPARAM	l);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	void _changeRenderTarget( const  Air::Client::Render::RENDER_TARGET_BLEND* pRenderTarget );
	void _changeBlend( const  Air::Client::Render::BLEND_DESC* pBlend );
	void _changeDepthStencilop( const  Air::Client::Render::DEPTH_STENCILOP* pDepthStencilop );
	void _changeDepthStencil( const  Air::Client::Render::DEPTH_STENCIL_DESC* pDepthStencil );
	void _changeRasterizer( const  Air::Client::Render::RASTERIZER_DESC* pRasterizer );
	void _changeSampler( const  Air::Client::Render::SAMPLER_DESC* pSampler );

private:
	typedef std::vector<Listener*> vListener;
	typedef std::vector<Listener*>::const_iterator ConstIterListener;
	typedef std::vector<Listener*>::iterator IterListener;
	vListener m_vListener;
	vListener m_vListenerDel;

	Air::Client::Render::RENDER_TARGET_BLEND m_RenderTarget;
	Air::Client::Render::BLEND_DESC m_Blend;
	Air::Client::Render::DEPTH_STENCILOP m_DepthStencilop;
	Air::Client::Render::DEPTH_STENCIL_DESC m_DepthStencil;
	Air::Client::Render::RASTERIZER_DESC m_Rasterizer;
	Air::Client::Render::SAMPLER_DESC m_Sampler;

	TreeObj*	m_pSelectObj;
};

