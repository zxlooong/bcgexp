//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// WorkspaceBar.h : interface of the CExplorerBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACEBAR_H__142ECAE6_015C_4273_AAF0_5F65FD62DDA8__INCLUDED_)
#define AFX_WORKSPACEBAR_H__142ECAE6_015C_4273_AAF0_5F65FD62DDA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExplorerToolBar : public CBCGPToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)	
	{		
		CBCGPToolBar::OnUpdateCmdUI ((CFrameWnd*) GetOwner (), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList () const		{	return FALSE;	}
};

class CExplorerTreeCtrl: public CTreeCtrl
{
	DECLARE_DYNAMIC(CExplorerTreeCtrl)
		
public:
	CExplorerTreeCtrl();
	virtual ~CExplorerTreeCtrl();

	void SetFavorites (BOOL bFavorites)
	{
		m_bFavorites = bFavorites;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExplorerTreeCtrl)
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CExplorerTreeCtrl)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CToolTipCtrl*	m_pToolTip;
	HTREEITEM		m_hToolItem;
	BOOL			m_bFavorites;
};

class CExplorerBar : public CBCGPDockingControlBar
{
public:
	CExplorerBar();

	void AdjustLayout ();
	void OnChangeVisualStyle ();

	BOOL IsFavorites () const
	{
		return m_bFavorites;
	}

// Attributes
protected:
	CExplorerTreeCtrl	m_wndTree;
	CImageList			m_ilTree;
	CExplorerToolBar	m_wndToolBar;
	BOOL				m_bFavorites;

	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	void FillFavorites ();
	void FillHistory ();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExplorerBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExplorerBar();

// Generated message map functions
protected:
	//{{AFX_MSG(CExplorerBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnFavorites();
	afx_msg void OnUpdateFavorites(CCmdUI* pCmdUI);
	afx_msg void OnHistory();
	afx_msg void OnUpdateHistory(CCmdUI* pCmdUI);
	afx_msg void OnSelectTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEBAR_H__142ECAE6_015C_4273_AAF0_5F65FD62DDA8__INCLUDED_)
