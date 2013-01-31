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
#if !defined(AFX_FRAMEDIALOG_H__60575F73_88A2_48C0_8A05_0A490F42D0D8__INCLUDED_)
#define AFX_FRAMEDIALOG_H__60575F73_88A2_48C0_8A05_0A490F42D0D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameDialog.h : header file
//

class CBCGPRibbonBarEx: public CBCGPRibbonBar
{
	DECLARE_DYNAMIC(CBCGPRibbonBarEx)

public:

	CBCGPRibbonBarEx (BOOL bReplaceFrameCaption = TRUE)
		: CBCGPRibbonBar (bReplaceFrameCaption)
	{

	}
	virtual ~CBCGPRibbonBarEx ()
	{

	}

	virtual void OnUpdateCmdUI (CBCGPFrameWnd* pTarget, BOOL bDisableIfNoHndler);

protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CFrameDialog frame

class CFrameDialog : public CBCGPFrameWnd
{
	DECLARE_DYNCREATE(CFrameDialog)
protected:
	CFrameDialog();           // protected constructor used by dynamic creation

// Attributes
public:
	CBCGPRibbonBar* GetRibbonBar ()
	{
		return &m_wndRibbonBar;
	}

	virtual UINT_PTR DoModal ();
	void EndDialog(int nResult);

	CFrameDialog(UINT nIDResource, CWnd* pParentWnd = NULL);
	virtual ~CFrameDialog();

protected:
	virtual void OnOK();
	virtual void OnCancel();

	virtual BOOL CreateRibbonBar ();
	virtual BOOL CreateStatusBar ();

	virtual BOOL CreateOtherBars ();

	virtual BOOL LoadPanelImages ();

	virtual void AddMainCategory ();
	virtual void AddTabs ();
	virtual void AddQAT ();

	virtual void SetKeys ();

	virtual void ShowOptions (int nPage);

	void CompleteCategories (CBCGPRibbonButton& btn);

protected:
	HWND PreModal();
	void PostModal();

	BOOL InitPrintPreview ();
	BOOL ClosePrintPreview ();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameDialog)
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFrameDialog)
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd (CDC*);
	afx_msg void OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI);
	afx_msg void OnToolsOptions ();
	//}}AFX_MSG
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPRibbonBarEx		m_wndRibbonBar;	// Ribbon control bar
	CBCGPRibbonMainButton	m_MainButton;	// Ribbon main button
	CBCGPRibbonStatusBar	m_wndStatusBar;

	CBCGPToolBarImages		m_PanelImages;	// Ribbon panel images

	CWnd*					m_pParentWnd;
	HWND					m_hWndTop;      // top level parent window (may be disabled)

	UINT                    m_nIDResource;
	
	CWnd*					m_pMainWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEDIALOG_H__60575F73_88A2_48C0_8A05_0A490F42D0D8__INCLUDED_)
