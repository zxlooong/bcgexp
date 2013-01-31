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
// EditFrameView.h : interface of the CEditFrameView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITFRAMEVIEW_H__C6C975F4_635B_4202_B288_F5A93EF3E7B4__INCLUDED_)
#define AFX_EDITFRAMEVIEW_H__C6C975F4_635B_4202_B288_F5A93EF3E7B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxrich.h"

class CEditFrameView : public CRichEditView
{
protected: // create from serialization only
	CEditFrameView();
	DECLARE_DYNCREATE(CEditFrameView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditFrameView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point,
		CPreviewView* pView);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);	
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditFrameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEditFrameView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFontDialog();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCharStrikethrough();
	afx_msg void OnUpdateCharStrikethrough(CCmdUI* pCmdUI);
	afx_msg void OnFontColor();
	afx_msg void OnFontTextHighlight();
	afx_msg void OnFontName();
	afx_msg void OnFontSize();
	afx_msg void OnFontSizeIncrease();
	afx_msg void OnFontSizeDecrease();
	afx_msg void OnFontClear();
	afx_msg void OnEditChange();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL ShowContextMenu (CPoint pt);

protected:
	BOOL m_bIsEndOfPrint;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITFRAMEVIEW_H__C6C975F4_635B_4202_B288_F5A93EF3E7B4__INCLUDED_)
