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
#if !defined(AFX_GANTTVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
#define AFX_GANTTVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GanttView.h : header file
//

#include "BCGPGanttView.h"

class CBCGPOrganizerDoc;

/////////////////////////////////////////////////////////////////////////////
// CGanttView view

class CGanttView : public CBCGPGanttView
{
protected: // create from serialization only
	CGanttView();
	DECLARE_DYNCREATE(CGanttView)

// Attributes
public:
	CBCGPOrganizerDoc* GetDocument();

// Operations
public:
	void CreateDemo (BOOL bRedraw = TRUE);
	void UpdateGantt (const CGanttOptions& options, BOOL bRedraw = TRUE);
	void UpdateZoom (int index = -1);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGanttView)
	public:
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

protected:
	virtual BOOL OnChartScaleChanging (BOOL bIncrease);
	virtual void OnChartScaleChanged ();
	virtual BOOL OnChartDoubleClickItem (UINT nFlags, CBCGPGanttItem* pItem);

// Implementation
public:
	virtual ~CGanttView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGanttView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnDrawBackground();
	afx_msg void OnUpdateDrawBackground(CCmdUI* pCmdUI);
	afx_msg void OnGanttLinkItems();
	afx_msg void OnUpdateGanttLinkItems(CCmdUI* pCmdUI);
    afx_msg void OnGanttUnlinkItems();
    afx_msg void OnUpdateGanttUnlinkItems(CCmdUI* pCmdUI);
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
	afx_msg void OnUpdateGotoToday(CCmdUI* pCmdUI);
	afx_msg void OnGotoDay();
	afx_msg void OnUpdateGotoDay(CCmdUI* pCmdUI);	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg LRESULT OnHighlightRibbonListItem (WPARAM wp, LPARAM lp);

protected:
	void AddEditTask (CBCGPGanttItem* pItem, BOOL bMilestone = FALSE);

private:
	void UpdateCaptionText ();

protected:
	BOOL	m_bFirstTime;
};

#ifndef _DEBUG  // debug version in GanttView.cpp
inline CBCGPOrganizerDoc* CGanttView::GetDocument()
   { return (CBCGPOrganizerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GANTTVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
