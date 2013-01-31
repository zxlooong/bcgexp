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
#if !defined(AFX_STARTVIEW_H__0F796E3D_FC8E_45AB_AB20_728DE5077CCF__INCLUDED_)
#define AFX_STARTVIEW_H__0F796E3D_FC8E_45AB_AB20_728DE5077CCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartView html view

class CStartView : public CView
{
protected:
	CStartView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStartView)

// html Data
public:
	//{{AFX_DATA(CStartView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CBCGPHotSpotImageCtrl	m_Image;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CStartView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDisableUpdate(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	afx_msg void OnCaretPos(CCmdUI* pCmdUI);
	afx_msg void OnClickHotSpot();
	DECLARE_MESSAGE_MAP()

	void SetBitmap ();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTVIEW_H__0F796E3D_FC8E_45AB_AB20_728DE5077CCF__INCLUDED_)
