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
// splitfrm.h : header file

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#define CMDIChildWnd	CBCGPMDIChildWnd

class CDrawSplitterWnd : public CBCGPSplitterWnd
{
	virtual BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID)
	{
		ASSERT_VALID(this);
		ASSERT(m_hWnd != NULL);

		CBCGPScrollBar* pScrollBar = new CBCGPScrollBar;
		ASSERT_VALID (pScrollBar);

		pScrollBar->m_bAutoDestoyWindow = TRUE;

		if (!pScrollBar->Create (dwStyle | WS_VISIBLE | WS_CHILD, CRect (0, 0, 1, 1), this, nID))
		{
		#ifdef _DEBUG
			TRACE1("Warning: Window creation failed: GetLastError returns 0x%8.8X\n",
				GetLastError());
			return FALSE;
		#endif
		}

		return TRUE;
	}
};

class CSplitFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CSplitFrame)
protected:
	CSplitFrame();          // protected constructor used by dynamic creation

// Attributes
protected:
	CDrawSplitterWnd    m_wndSplitter;
public:

// Operations
public:

// Implementation
public:
	virtual ~CSplitFrame();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// Generated message map functions
	//{{AFX_MSG(CSplitFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
