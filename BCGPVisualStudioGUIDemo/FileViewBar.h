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
// FileViewBar.h: interface for the CFileViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEVIEWBAR_H__350F40BF_23FF_4A41_A125_7F18B55AFA1F__INCLUDED_)
#define AFX_FILEVIEWBAR_H__350F40BF_23FF_4A41_A125_7F18B55AFA1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClassTreeWnd.h"

class CFileViewToolBar : public CBCGPToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)	
	{		
		CBCGPToolBar::OnUpdateCmdUI ((CFrameWnd*) GetOwner (), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList () const		{	return FALSE;	}
};

class CFileViewBar : public CBCGPDockingControlBar  
{
// Construction
public:
	CFileViewBar();

	void AdjustLayout ();
	void OnChangeVisualStyle ();

// Attributes
protected:

	CClassTreeWnd		m_wndFileView;
	CImageList			m_FileViewImages;
	CFileViewToolBar	m_wndToolBar;

protected:
	void FillFileView ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileViewBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnSolutionOpen();
	afx_msg void OnSolutionOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_FILEVIEWBAR_H__350F40BF_23FF_4A41_A125_7F18B55AFA1F__INCLUDED_)
