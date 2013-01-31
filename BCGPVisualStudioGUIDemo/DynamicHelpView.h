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
#if !defined(AFX_DYNAMICHELPVIEBAR_H__E15D7C82_B803_11D4_95C8_00A0C9289F1B__INCLUDED_)
#define AFX_DYNAMICHELPVIEBAR_H__E15D7C82_B803_11D4_95C8_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExplorerBar.h : header file
//

class CHelpToolBar : public CBCGPToolBar
{
public:	
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)	
	{		
		CBCGPToolBar::OnUpdateCmdUI ((CFrameWnd*) GetOwner (), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList () const		{	return FALSE;	}
};

/////////////////////////////////////////////////////////////////////////////
// CDynamicHelpVieBar window

class CDynamicHelpViewBar : public CBCGPDockingControlBar
{
// Construction
public:
	CDynamicHelpViewBar();

	void AdjustLayout ();

// Attributes
protected:
	CHelpToolBar	m_wndToolBar;
	CTreeCtrl		m_wndArticles;
	CImageList		m_DynamicHelpImages;


// Operations
public:
	void OnChangeVisualStyle ();

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynamicHelpViewBar)
	//}}AFX_VIRTUAL

protected:
	virtual void OnEraseWorkArea (CDC* pDC, CRect rectWorkArea);
	void FillHelp ();

// Implementation
public:
	virtual ~CDynamicHelpViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDynamicHelpViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDhelp1();
	afx_msg void OnUpdateDhelp1(CCmdUI* pCmdUI);
	afx_msg void OnDhelp2();
	afx_msg void OnUpdateDhelp2(CCmdUI* pCmdUI);
	afx_msg void OnDhelp3();
	afx_msg void OnUpdateDhelp3(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg void OnSelectTree(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNAMICHELPVIEBAR_H__E15D7C82_B803_11D4_95C8_00A0C9289F1B__INCLUDED_)
