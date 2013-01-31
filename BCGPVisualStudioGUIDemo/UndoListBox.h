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
#if !defined(AFX_UNDOLISTBOX_H__3CB08857_F7B9_4B5E_B019_D2E748A2CCD4__INCLUDED_)
#define AFX_UNDOLISTBOX_H__3CB08857_F7B9_4B5E_B019_D2E748A2CCD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UndoListBox.h : header file
//

class CUndoBar;

/////////////////////////////////////////////////////////////////////////////
// CUndoListBox window

class CUndoListBox : public CListBox
{
// Construction
public:
	CUndoListBox(CUndoBar& bar);

// Attributes
protected:
	CUndoBar&	m_Bar;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUndoListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUndoListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUndoListBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNDOLISTBOX_H__3CB08857_F7B9_4B5E_B019_D2E748A2CCD4__INCLUDED_)
