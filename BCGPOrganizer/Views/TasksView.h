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
#if !defined(AFX_TASKSVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
#define AFX_TASKSVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TasksView.h : header file
//

#include "../BCGPOrganizerDoc.h"

class CADOGridCtrl : public CBCGPADOGridCtrl
{
public:
	CADOGridCtrl()
	{
		m_nFilter = 0;
		SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
	}

	virtual ~CADOGridCtrl()
	{
	}

	int	m_nFilter;

protected:
	virtual BOOL OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow);
	virtual BOOL OnBeforeAddRow (CBCGPGridRow* pRow, int nRow);
};

/////////////////////////////////////////////////////////////////////////////
// CTasksView view

class CTasksView : public CBCGPGridView
{
protected: // create from serialization only
	CTasksView();
	DECLARE_DYNCREATE(CTasksView)

// Attributes
public:
	CBCGPOrganizerDoc* GetDocument();
	
	CImageList			m_ImagesHeader;
	static CImageList	m_Images;

// Operations
public:
	virtual CBCGPGridCtrl* CreateGrid ()
	{
		return new CADOGridCtrl;
	}

	BOOL Refresh ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTasksView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTasksView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTasksView)
	afx_msg void OnDestroy();
	afx_msg void OnExpandAll();
	afx_msg void OnCollapseAll();
	afx_msg void OnViewFieldchooser();
	afx_msg void OnUpdateViewFieldchooser(CCmdUI* pCmdUI);
	afx_msg void OnViewGroupbox();
	afx_msg void OnUpdateViewGroupbox(CCmdUI* pCmdUI);
	afx_msg void OnViewColumnAutoResize();
	afx_msg void OnUpdateViewColumnAutoResize(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnShowAll();
	afx_msg void OnShowTasks();
	afx_msg void OnShowToDo();
	afx_msg void OnDummy();
	DECLARE_MESSAGE_MAP()

private:
	void UpdateCaptionText ();

private:
	BOOL		m_bFirstTime;
	int			m_nFilter;
	CString		m_strSQL;
};

#ifndef _DEBUG  // debug version in TasksView.cpp
inline CBCGPOrganizerDoc* CTasksView::GetDocument()
   { return (CBCGPOrganizerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKSView_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
