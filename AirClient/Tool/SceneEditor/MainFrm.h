// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__C5D27100_EA55_4DC1_9F25_A3913E16E73D__INCLUDED_)
#define AFX_MAINFRM_H__C5D27100_EA55_4DC1_9F25_A3913E16E73D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CXTPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;


	BOOL CreateRibbonBar();
	BOOL CreateStatusBar();
	BOOL CreatePane();



// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnEnableButton(CCmdUI* pCmdUI);

	afx_msg void OnCheckbox(UINT nID);
	afx_msg void OnRadioButton(UINT nID);
	afx_msg void OnUpdateCheckbox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRadioButton(CCmdUI* pCmdUI);
	afx_msg void OnToggleButton();
	afx_msg void OnUpdateToggleButton(CCmdUI* pCmdUI);

	//Edit
	afx_msg void OnSelectButton();
	afx_msg void OnUpdateSelectButton(CCmdUI* pCmdUI);
	afx_msg void OnSelectListButton();
	afx_msg void OnUpdateSelectListButton(CCmdUI* pCmdUI);
	afx_msg void OnMoveButton();
	afx_msg void OnUpdateMoveButton(CCmdUI* pCmdUI);
	afx_msg void OnRotateButton();
	afx_msg void OnUpdateRotateButton(CCmdUI* pCmdUI);
	afx_msg void OnScaleButton();
	afx_msg void OnUpdateScaleButton(CCmdUI* pCmdUI);
	//Create
	afx_msg void OnButtonCreate_Object();		
	afx_msg void OnButtonCreate_Actor();				
	afx_msg void OnButtonCreate_Building();			
	afx_msg void OnButtonCreate_Point_light();	
	afx_msg void OnButtonCreate_Spot_light();	
	afx_msg void OnButtonCreate_Sun_light();		
	afx_msg void OnButtonCreate_Water();		
	afx_msg void OnButtonCreate_Cloud();			
	afx_msg void OnButtonCreate_Tree();			
	afx_msg void OnButtonCreate_Grass();			

	afx_msg void OnUpdate_Object(CCmdUI* pCmdUI);		
	afx_msg void OnUpdate_Actor(CCmdUI* pCmdUI);				
	afx_msg void OnUpdate_Building(CCmdUI* pCmdUI);			
	afx_msg void OnUpdate_Point_light(CCmdUI* pCmdUI);	
	afx_msg void OnUpdate_Spot_light(CCmdUI* pCmdUI);	
	afx_msg void OnUpdate_Sun_light(CCmdUI* pCmdUI);		
	afx_msg void OnUpdate_Water(CCmdUI* pCmdUI);		
	afx_msg void OnUpdate_Cloud(CCmdUI* pCmdUI);			
	afx_msg void OnUpdate_Tree(CCmdUI* pCmdUI);			
	afx_msg void OnUpdate_Grass(CCmdUI* pCmdUI);

	afx_msg void OnButtonSVOBuild();		
	afx_msg void OnButtonSVOShow();
	afx_msg void OnUpdateSVOBuild(CCmdUI* pCmdUI);		
	afx_msg void OnUpdateSVOShow(CCmdUI* pCmdUI);

	afx_msg void OnOptionsRighttoleft();
	afx_msg void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	UINT m_nRibbonStyle;

	CXTPControlGalleryItems* m_pItemsFontFace;
	CXTPControlGalleryItems* m_pItemsStyles;
	CXTPControlGalleryItems* m_pItemsTable;
	CXTPControlGalleryItems* m_pItemsFontTextColor;
	CXTPControlGalleryItems* m_pItemsUndo;

	void OnUpdateEditUndo(CCmdUI* pCmd);
	void OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult);
	void OnSelectorText(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateSelectorText(CCmdUI* pCmdUI);
	
	BOOL m_bCheckbox[3];
	int m_nRadioButton;
	COLORREF m_clr;
	BOOL m_bToggleButton;

	enumEditMode	m_EditMode;
	CString m_csStylesPath;
	// Attributes
public:
	CXTPDockingPaneManager m_paneManager;

	// Operations
public:
	CXTPDockingPaneManager* GetDockingPaneManager() {
		return &m_paneManager;
	}

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C5D27100_EA55_4DC1_9F25_A3913E16E73D__INCLUDED_)
