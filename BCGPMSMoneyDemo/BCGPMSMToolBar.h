//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
#if !defined(AFX_BCGPMSMToolBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
#define AFX_BCGPMSMToolBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMToolBar window

class CBCGPMSMToolBar : public CBCGPToolBar
{
	DECLARE_DYNCREATE(CBCGPMSMToolBar)

// Construction
public:
	CBCGPMSMToolBar();

	virtual ~CBCGPMSMToolBar ();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSMToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual BOOL LoadToolBar (UINT uiResID, UINT uiColdResID = 0, 
					UINT uiMenuResID = 0, BOOL bLocked = FALSE,
					UINT uiDisabledResID = 0, UINT uiMenuDisabledResID = 0,
  				    UINT uiHotResID = 0, UINT uiPressedResID = 0);

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMSMToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	virtual BOOL DrawButton (CDC* pDC, CBCGPToolbarButton* pButton, 
		CBCGPToolBarImages* pImages, BOOL bHighlighted,
		BOOL bDrawDisabledImages);

protected:

	static CBCGPToolBarImages m_PressedImages; // Shared pressed images
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMToolBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
