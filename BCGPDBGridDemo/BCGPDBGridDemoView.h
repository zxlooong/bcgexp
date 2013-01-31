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
// BCGPDBGridDemoView.h : interface of the CBCGPDBGridDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPDBGRIDDEMOVIEW_H__763FA4A4_159C_4191_9B9C_B7EF7D2B53FE__INCLUDED_)
#define AFX_BCGPDBGRIDDEMOVIEW_H__763FA4A4_159C_4191_9B9C_B7EF7D2B53FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPDBGridDemoDoc.h"

class CMyODBCGridCtrl : public CBCGPODBCGridCtrl
{
	virtual BOOL OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow);

	virtual BOOL OnGetPageHeaderRect (CDC* /*pDC*/, CPrintInfo* pInfo, CRect& rect);
	virtual BOOL OnGetPageFooterRect (CDC* pDC, CPrintInfo* pInfo, CRect& rect);
	
	virtual void OnPrintPageHeader(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrintPageFooter(CDC* pDC, CPrintInfo* pInfo);
};

class CMyADOGridCtrl : public CBCGPADOGridCtrl
{
	virtual BOOL OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow);
};

#ifndef _WIN64
class CMyDAOGridCtrl : public CBCGPDAOGridCtrl
{
	virtual BOOL OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow);
};
#endif // !_WIN64

class CBCGPDBGridDemoView : public CBCGPGridView
{
protected: // create from serialization only
	CBCGPDBGridDemoView();
	DECLARE_DYNCREATE(CBCGPDBGridDemoView)

// Attributes
public:
	CBCGPDBGridDemoDoc* GetDocument();

// Operations
public:
	virtual CBCGPGridCtrl* CreateGrid ()
	{
		return m_nSourceType == 1 ? // Example database
			new CMyODBCGridCtrl : new CBCGPODBCGridCtrl;
	}

	CBCGPDBGridCtrl* GetNewGrid ()
	{
		return m_pNewGrid;
	}

	int	m_nDataType;
	int m_nSourceType;
	BOOL m_bAllowEdit; 
	CString m_strDBPath;
	CString m_strTable;
	CBCGPDBGridCtrl* m_pNewGrid;

	CString m_strDSNString;
	CString m_strDefaultDBPath;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPDBGridDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPDBGridDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPDBGridDemoView)
	afx_msg void OnViewFieldchooser();
	afx_msg void OnUpdateViewFieldchooser(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()

public:
	void ReplaceGrid (CBCGPDBGridCtrl* pNewGrid);
};

#ifndef _DEBUG  // debug version in BCGPDBGridDemoView.cpp
inline CBCGPDBGridDemoDoc* CBCGPDBGridDemoView::GetDocument()
   { return (CBCGPDBGridDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPDBGRIDDEMOVIEW_H__763FA4A4_159C_4191_9B9C_B7EF7D2B53FE__INCLUDED_)
