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
#if !defined(AFX_DEFAULTVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
#define AFX_DEFAULTVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefaultView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDefaultView view

class CDefaultView : public CView
{
protected: // create from serialization only
	CDefaultView();
	DECLARE_DYNCREATE(CDefaultView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefaultView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDefaultView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnDrawMemDC (CDC* pDC);

// Generated message map functions
protected:
	//{{AFX_MSG(CDefaultView)
	afx_msg BOOL OnEraseBkgnd(CDC*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	CBCGPControlRenderer	m_Pat[3];
	CDC						m_MemDC;
    CBitmap					m_MemBitmap;
	CBitmap*				m_pOldBitmap;
	UINT					m_nAppLook;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFAULTVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
