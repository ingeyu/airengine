// RibbonControls.h : main header file for the RIBBONCONTROLS application
//

#if !defined(AFX_RIBBONCONTROLS_H__4CC61172_E866_4AE1_8719_87BCC1B8759F__INCLUDED_)
#define AFX_RIBBONCONTROLS_H__4CC61172_E866_4AE1_8719_87BCC1B8759F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsApp:
// See RibbonControls.cpp for the implementation of this class
//

class CRibbonControlsApp : public CWinApp
{
public:
	CRibbonControlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonControlsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	virtual BOOL OnIdle(LONG lCount);
// Implementation
	//{{AFX_MSG(CRibbonControlsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONCONTROLS_H__4CC61172_E866_4AE1_8719_87BCC1B8759F__INCLUDED_)