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
// BCGPGridExampleView.h : interface of the CBCGPGridExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPGRIDEXAMPLEVIEW_H__F77E2428_8CF3_4411_945C_5B0D3CF831FB__INCLUDED_)
#define AFX_BCGPGRIDEXAMPLEVIEW_H__F77E2428_8CF3_4411_945C_5B0D3CF831FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPGridExampleView : public CBCGPGridView
{
protected: // create from serialization only
	CBCGPGridExampleView();
	DECLARE_DYNCREATE(CBCGPGridExampleView)

// Attributes
public:
	CBCGPGridExampleDoc* GetDocument();

protected:
	CBCGPGridCtrl*							m_pCurrGrid;
	CArray<CBCGPGridCtrl*, CBCGPGridCtrl*>	m_arGrids;
	int										m_nCurrType;

	CArray<int,int>							m_arNavigationHistory;
	int										m_nNavHistoryIndex;

// Operations
public:
	void SetViewType (int nType, BOOL bByNavigationButtons = FALSE);
	void UpdateGrid ();
	void AdjustLayout ();
	void OnUpdateVisualManager ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPGridExampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPGridExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPGridExampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	afx_msg void OnFieldChooser();
	afx_msg void OnUpdateFieldChooser(CCmdUI* pCmdUI);
	afx_msg void OnGroupByBox();
	afx_msg void OnUpdateGroupByBox(CCmdUI* pCmdUI);
	afx_msg void OnReportPreview();
	afx_msg void OnUpdateReportPreview(CCmdUI* pCmdUI);
	afx_msg void OnColorThemeCombo();
	afx_msg void OnEditSelectAll();
	afx_msg void OnViewBack();
	afx_msg void OnUpdateViewBack(CCmdUI* pCmdUI);
	afx_msg void OnViewForward();
	afx_msg void OnUpdateViewForward(CCmdUI* pCmdUI);
	afx_msg void OnGridMerge();
	afx_msg void OnGridUnmerge();
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT OnHideColumnChooser (WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BCGPGridExampleView.cpp
inline CBCGPGridExampleDoc* CBCGPGridExampleView::GetDocument()
   { return (CBCGPGridExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPGRIDEXAMPLEVIEW_H__F77E2428_8CF3_4411_945C_5B0D3CF831FB__INCLUDED_)
