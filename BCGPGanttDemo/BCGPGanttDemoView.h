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
// BCGPGanttDemoView.h : interface of the CBCGPGanttDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPCHARTEXAMPLEVIEW_H__D40CD046_CB25_4C83_85B2_C94EFBA012ED__INCLUDED_)
#define AFX_BCGPCHARTEXAMPLEVIEW_H__D40CD046_CB25_4C83_85B2_C94EFBA012ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPGanttView.h"

class CBCGPGanttDemoView : public CBCGPGanttView
{
protected: // create from serialization only
	CBCGPGanttDemoView();
	DECLARE_DYNCREATE(CBCGPGanttDemoView)

// Attributes
public:
	CBCGPGanttDemoDoc* GetDocument();

	void CreateDemo (BOOL bRedraw = TRUE);

// Operations
public:

	void OnChangeType ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPGanttDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

protected:
    virtual BOOL OnChartDoubleClickItem (UINT nFlags, CBCGPGanttItem* pItem);

// Implementation
public:
	virtual ~CBCGPGanttDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    void GetSelectedItems (CArray <CBCGPGanttItem*, CBCGPGanttItem*>& arrSelected) const;

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPGanttDemoView)
    afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnGanttLinkItems();
	afx_msg void OnUpdateGanttLinkItems(CCmdUI* pCmdUI);
    afx_msg void OnGanttUnlinkItems();
    afx_msg void OnUpdateGanttUnlinkItems(CCmdUI* pCmdUI);
    afx_msg void OnGanttZoomIn();
    afx_msg void OnUpdateGanttZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnGanttZoomOut();
	afx_msg void OnUpdateGanttZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnGanttNewTask();
	afx_msg void OnUpdateGanttNew(CCmdUI* pCmdUI);
	afx_msg void OnGanttNewMilestone();
	afx_msg void OnGanttOpenItem();
	afx_msg void OnUpdateGanttOpenItem(CCmdUI* pCmdUI);
	afx_msg void OnGanttRemoveItem();
	afx_msg void OnUpdateGanttRemoveItem(CCmdUI* pCmdUI);
	afx_msg void OnMarkComplete();
	afx_msg void OnUpdateMarkComplete(CCmdUI* pCmdUI);
	afx_msg void OnGotoToday();
	afx_msg void OnGotoDay();
    afx_msg void OnDestroy();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void AddEditTask (CBCGPGanttItem* pItem, BOOL bMilestone = FALSE);

protected:
	BOOL	m_bFirstTime;
};

#ifndef _DEBUG  // debug version in BCGPGanttDemoView.cpp
inline CBCGPGanttDemoDoc* CBCGPGanttDemoView::GetDocument()
   { return (CBCGPGanttDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCHARTEXAMPLEVIEW_H__D40CD046_CB25_4C83_85B2_C94EFBA012ED__INCLUDED_)
