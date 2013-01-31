//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// TabWnd.h : header file
//

#if !defined(AFX_TABWND_H__E566C917_B757_4C1B_B2DE_1D786F96D5E0__INCLUDED_)
#define AFX_TABWND_H__E566C917_B757_4C1B_B2DE_1D786F96D5E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTabButton: public CBCGPButton
{
	DECLARE_DYNCREATE(CTabButton)

public:

	CTabButton();
	virtual ~CTabButton();

protected:
	virtual void OnDrawBorder (CDC* /*pDC*/, CRect& /*rectClient*/, UINT /*uiState*/)
	{

	}
	virtual void OnFillBackground (CDC* pDC, const CRect& rectClient);
	virtual void OnDrawParentBackground (CDC* pDC, CRect rectClient);
	virtual void OnDraw (CDC* pDC, const CRect& rect, UINT uiState);

	DECLARE_MESSAGE_MAP()
};

class CTabMenuButton: public CBCGPMenuButton
{
	DECLARE_DYNCREATE(CTabMenuButton)

public:

	CTabMenuButton();
	virtual ~CTabMenuButton();

protected:
	virtual void OnDrawBorder (CDC* /*pDC*/, CRect& /*rectClient*/, UINT /*uiState*/)
	{

	}
	virtual void OnFillBackground (CDC* pDC, const CRect& rectClient);
	virtual void OnDrawParentBackground (CDC* pDC, CRect rectClient);
	virtual void OnDraw (CDC* pDC, const CRect& rect, UINT uiState);
	virtual void OnShowMenu ();

	afx_msg UINT OnGetDlgCode();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CTabWnd window

class CTabInfo : public CObject
{
	friend class CTabWnd;

	CTabInfo (HWND hWnd = NULL)
		: m_hWnd  (hWnd)
		, m_hIcon (NULL)
		, m_bDestroyIcon (FALSE)
	{
		m_rect.SetRectEmpty ();

		if (m_hWnd != NULL)
		{
			CollectInfo ();
		}
	}

	~CTabInfo()
	{
		if (m_hIcon != NULL && m_bDestroyIcon)
		{
			::DestroyIcon (m_hIcon);
		}
	}

	CString		m_strText;
	HICON		m_hIcon;
	HWND		m_hWnd;
	BOOL		m_bDestroyIcon;
	CRect		m_rect;

protected:
	void CollectInfo ()
	{
		CWnd* pWnd = CWnd::FromHandle (m_hWnd);
		if (pWnd == NULL)
		{
			return;
		}

		if (m_hIcon != NULL && m_bDestroyIcon)
		{
			::DestroyIcon (m_hIcon);
			m_hIcon = NULL;
		}
		
		m_hIcon = globalUtils.GetWndIcon (pWnd, &m_bDestroyIcon);

		CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, pWnd);

		if (pMDIChild != NULL)
		{
			m_strText = pMDIChild->GetFrameText ();
		}
		else
		{
			pWnd->GetWindowText (m_strText);
		}
	}

public:
	CRect GetRect () const		{	return m_rect;	}
	void SetRect (const CRect& rect)	{	m_rect = rect;	} 
};

class CTabWnd : public CWnd
{
	DECLARE_DYNCREATE(CTabWnd)

	friend class CTabButton;
	friend class CTabMenuButton;

// Construction
public:
	CTabWnd();

// Attributes
public:

// Operations
public:

	BOOL Create (const RECT& rect, CWnd* pParentWnd, UINT nID);
	
	void RecalcLayout ();

protected:
	//int GetTabFromPoint (CPoint& pt) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

protected:

	BOOL LoadImages();
	void ChangeStyle();
	void DrawButton(CBCGPButton& btn, CDC* pDC, const CRect& rect, UINT uiState);
	void DrawBackground (CWnd& wnd, CDC* pDC, CRect rectClient);
	BOOL PrepareButtonMenu(CBCGPMenuButton& btn);

// Implementation
public:
	virtual ~CTabWnd();

	void AddTab (HWND hWnd, BOOL bRecalc = TRUE);
	void RemoveTab (HWND hWnd);
	void SetTabText (HWND hWnd);
	void SetTabIcon (HWND hWnd);
	void SetActiveTab (HWND hWnd);
	void UpdateTabs (BOOL bRedraw);

	int GetTabsNum () const;

protected:
	
	void DrawTab(CDC* pDC, CRect rect, int index);
	void ActivateMDI(int index);

	void AdjustTabs ();
	void AdjustScroll ();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnBCGUpdateToolTips(WPARAM, LPARAM);
	afx_msg BOOL OnNeedTipText(UINT id, NMHDR* pNMH, LRESULT* pResult);
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	
	DECLARE_MESSAGE_MAP()

	int GetTabIndexFromPoint (const CPoint& point);
	int FindTabInfoIndex (HWND hWnd);
	CTabInfo* FindTabInfo (HWND hWnd);	

private:
	CTabButton			m_btnNew;
	CTabButton			m_btnScroll[2];
	CTabMenuButton		m_btnMenu;
	CMenu				m_menu;

	CBCGPToolBarImages	m_ImagesDisabled;
	CBCGPToolBarImages	m_ImagesNormal;
	CBCGPToolBarImages	m_ImagesHot;

	CBCGPToolBarImages	m_Sides;
	CBCGPControlRenderer	m_Corners;
	CBCGPControlRenderer	m_Items;

	CBCGPToolBarImages	m_Close;
	BOOL				m_ClosePressed;
	BOOL				m_CloseHighlighted;

	int					m_Active;
	int					m_Highlighted;
	int					m_FirstVisible;
	
	CRect				m_rectTabs;
	CRect				m_rectClose;

	BOOL				m_bInitialized;
	BOOL				m_bTracked;

	CArray<CTabInfo*, CTabInfo*>
						m_Tabs;
	CArray<CRect, CRect>
						m_TabRects;

	CToolTipCtrl*	m_pToolTip;
	CToolTipCtrl*	m_pToolTipClose;	// Tooltip for active tab "close" button
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABWND_H__E566C917_B757_4C1B_B2DE_1D786F96D5E0__INCLUDED_)
