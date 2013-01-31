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
// ReportDemoView.h : interface of the CMailView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILVIEW_H__AC23BEA5_8CE3_4B70_B0C3_2D73D6683483__INCLUDED_)
#define AFX_MAILVIEW_H__AC23BEA5_8CE3_4B70_B0C3_2D73D6683483__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Mail/MailReportCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFlagItem class

class CFlagItem: public CBCGPGridItem
{
public:
	CFlagItem(
		CBCGPToolBarImages& icons,
		int nSelectedIcon,
		DWORD dwData = 0
	);

public:
	virtual BOOL OnClickValue (UINT uiMsg, CPoint point);
	
protected:
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual void OnPrintValue (CDC* /*pDC*/, CRect /*rect*/) {}
	CBCGPToolBarImages&	m_Icons;
};

/////////////////////////////////////////////////////////////////////////////
// CMailView

class CMailView : public CBCGPReportView
{
protected: // create from serialization only
	CMailView();
	DECLARE_DYNCREATE(CMailView)

// Attributes
public:
	CBCGPOrganizerDoc* GetDocument();

protected:
	CImageList			m_ImagesHeader;
	CImageList			m_Images;
	CBCGPToolBarImages	m_Flags;

	enum IMPORTANCE
	{
		IMPORTANCE_NORMAL,
		IMPORTANCE_HIGH,
		IMPORTANCE_LOW
	};
	
// Operations
public:

// Overrides
	CBCGPGridCtrl* CreateGrid ()
	{
		return new CMailReportCtrl;
	}

	void CreateDemo (BOOL bRedraw = TRUE);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailView)
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
	virtual ~CMailView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CMailView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnExpandAll();
	afx_msg void OnCollapseAll();
	afx_msg void OnViewFieldchooser();
	afx_msg void OnUpdateViewFieldchooser(CCmdUI* pCmdUI);
	afx_msg void OnViewGroupbox();
	afx_msg void OnUpdateViewGroupbox(CCmdUI* pCmdUI);
	afx_msg void OnViewColumnAutoResize();
	afx_msg void OnUpdateViewColumnAutoResize(CCmdUI* pCmdUI);
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg LRESULT OnOpen (WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()

	BOOL AddMail (int nIcon, LPCTSTR strFrom, LPCTSTR strTo,
		 LPCTSTR strSubject, COleDateTime dateCreated, 
		 COleDateTime dateReceived, long lSize, 
		 IMPORTANCE importance = IMPORTANCE_NORMAL,
		 BOOL bHasAttachment = FALSE,
		 int nFlag = 0);

private:
	void UpdateCaptionText ();

private:
	BOOL	m_bFirstTime;
};

#ifndef _DEBUG  // debug version in MailView.cpp
inline CBCGPOrganizerDoc* CMailView::GetDocument()
   { return (CBCGPOrganizerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILVIEW_H__AC23BEA5_8CE3_4B70_B0C3_2D73D6683483__INCLUDED_)
