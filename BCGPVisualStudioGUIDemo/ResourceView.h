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
// ResourceView.h: interface for the CResourceViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEVIEW_H__F9C28949_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
#define AFX_RESOURCEVIEW_H__F9C28949_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClassTreeWnd.h"

class CResourceViewBar : public CBCGPDockingControlBar  
{
// Construction
public:
	CResourceViewBar();

// Attributes
protected:

	CClassTreeWnd	m_wndResourceView;
	CImageList		m_ResourceViewImages;

public:
	void OnChangeVisualStyle ();

protected:
	void FillResourceView ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceViewBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResourceViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_RESOURCEVIEW_H__F9C28949_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
