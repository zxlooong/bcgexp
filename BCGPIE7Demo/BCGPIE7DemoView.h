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
// BCGPIEDemoView.h : interface of the CBCGPIE7DemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPIE7DEMOVIEW_H__F83C8E13_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_BCGPIE7DEMOVIEW_H__F83C8E13_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPIE7DemoView : public CHtmlView
{
protected: // create from serialization only
	CBCGPIE7DemoView();
	DECLARE_DYNCREATE(CBCGPIE7DemoView)

// Attributes
public:
	CBCGPIE7DemoDoc* GetDocument();

	void NavigateB (LPCTSTR lpszURL, DWORD dwFlags = 0,
		LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeaders = NULL,
		LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0);

	static BOOL	m_bWorkOffline;
	static BOOL	m_bGoAddress;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPIE7DemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnInitialUpdate();
	virtual void OnProgressChange(long nProgress, long nProgressMax);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPIE7DemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPIE7DemoView)
	afx_msg void OnGoBack();
	afx_msg void OnUpdateGoBack(CCmdUI* pCmdUI);
	afx_msg void OnGoForward();
	afx_msg void OnUpdateGoForward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGoHistory(CCmdUI* pCmdUI);
	afx_msg void OnGoSearch();
	afx_msg void OnUpdateGoSearchMenu(CCmdUI* pCmdUI);
	afx_msg void OnGoHomePage();
	afx_msg void OnViewStop();
	afx_msg void OnViewRefresh();
	afx_msg void OnViewFontSizeLargest();
	afx_msg void OnUpdateViewFontSizeLargest(CCmdUI* pCmdUI);
	afx_msg void OnViewFontSizeLarger();
	afx_msg void OnUpdateViewFontSizeLarger(CCmdUI* pCmdUI);
	afx_msg void OnViewFontSizeMedium();
	afx_msg void OnUpdateViewFontSizeMedium(CCmdUI* pCmdUI);
	afx_msg void OnViewFontSizeSmaller();
	afx_msg void OnUpdateViewFontSizeSmaller(CCmdUI* pCmdUI);
	afx_msg void OnViewFontSizeSmallest();
	afx_msg void OnUpdateViewFontSizeSmallest(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFilePageSetup();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileProperties();
	afx_msg void OnEditFind();
	afx_msg void OnEditSelectAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bTitleUpdated;
	LONG m_nFontSize;
};

#ifndef _DEBUG  // debug version in BCGPIEDemoView.cpp
inline CBCGPIE7DemoDoc* CBCGPIE7DemoView::GetDocument()
   { return (CBCGPIE7DemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPIE7DEMOVIEW_H__F83C8E13_F33E_11D2_A713_0090274409AC__INCLUDED_)
