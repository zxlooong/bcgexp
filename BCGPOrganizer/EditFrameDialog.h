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
#if !defined(AFX_EDITFRAMEDIALOG_H__3186A04E_496E_4D95_8954_F08A5951D560__INCLUDED_)
#define AFX_EDITFRAMEDIALOG_H__3186A04E_496E_4D95_8954_F08A5951D560__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditFrameDialog.h : header file
//

#include "FrameDialog.h"

class CEditFrameView;

/////////////////////////////////////////////////////////////////////////////
// CEditFrameDialog frame

class CEditFrameDialog : public CFrameDialog
{
	friend class CEditFrameView;
	DECLARE_DYNCREATE(CEditFrameDialog)
protected:
	CEditFrameDialog();           // protected constructor used by dynamic creation

public:
	CEditFrameDialog(UINT nIDResource, CWnd* pParentWnd = NULL);
	virtual ~CEditFrameDialog();

// Attributes
public:

// Operations
public:

	void SetText (const CString& rText);
	void GetText (CString& rText) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditFrameDialog)
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL CreateRibbonBar ();

	virtual void CreateDocumentColors ();

	virtual void AddTabs ();
	virtual void AddQAT ();

	virtual void SetKeys ();

	void AddTab_Format ();

	// Generated message map functions
	//{{AFX_MSG(CEditFrameDialog)
	afx_msg void OnFilePrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPRibbonMainButton	m_MainButton;	// Ribbon main button
	CEditFrameView* m_EditView;

	// Document colors:
	CList<COLORREF,COLORREF> m_lstMainColors;
	CList<COLORREF,COLORREF> m_lstAdditionalColors;
	CList<COLORREF,COLORREF> m_lstStandardColors;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITFRAMEDIALOG_H__3186A04E_496E_4D95_8954_F08A5951D560__INCLUDED_)
