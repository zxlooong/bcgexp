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
// ipframe.h : interface of the CInPlaceFrame class
//

class CWordPadResizeBar : public COleResizeBar
{
public:
	void SetMinSize(CSize size) {m_tracker.m_sizeMin = size;}
};

class CInPlaceFrame : public CBCGPOleIPFrameWnd
{
	DECLARE_DYNCREATE(CInPlaceFrame)
public:
	CInPlaceFrame();

// Attributes
public:
	CBCGPToolBar m_wndMenuBar;
	CBCGPToolBar m_wndToolBar;
	CFormatBar m_wndFormatBar;
	CRulerBar m_wndRulerBar;
	CWordPadResizeBar m_wndResizeBar;
	COleDropTarget m_dropTarget;

// Operations
public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual void CalcWindowRect(LPRECT lpClientRect,
		UINT nAdjustType = adjustBorder);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceFrame)
	public:
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	virtual void RepositionFrame(LPCRECT lpPosRect, LPCRECT lpClipRect);
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL CreateMenuBar();
	BOOL CreateToolBar(CWnd* pWndFrame);
	BOOL CreateFormatBar(CWnd* pWndFrame);
	BOOL CreateRulerBar(CWnd* pWndFrame);

// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnHelpFinder();
	afx_msg void OnPenToggle();
	//}}AFX_MSG
	LRESULT OnResizeChild(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBarState(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
