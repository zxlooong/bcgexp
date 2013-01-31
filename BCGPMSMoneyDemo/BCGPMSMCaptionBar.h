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
#if !defined(AFX_BCGPMSMCAPTIONBAR_H__4B2621B3_9ADD_4F3B_9A2C_27E1188E2613__INCLUDED_)
#define AFX_BCGPMSMCAPTIONBAR_H__4B2621B3_9ADD_4F3B_9A2C_27E1188E2613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMCaptionBar.h : header file
//

#include "BCGPMSMCaptionBarButton.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCaptionBar window

static const UINT uiCaprionBarID = AFX_IDW_DIALOGBAR + 1;

class CBCGPMSMCaptionBar : public CBCGPControlBar
{
	DECLARE_DYNCREATE(CBCGPMSMCaptionBar)

// Construction
public:
	CBCGPMSMCaptionBar ();

	virtual ~CBCGPMSMCaptionBar ();
	
	virtual void SetIcon (HICON hIcon);

	void SetCaptionHeight (int nHeight);

	int GetCaptionHeight () const;

	void SetCaptionFont (const LOGFONT& lf);

	HFONT GetCaptionFont () const;

	virtual COLORREF GetCaptionTextColor () const;

	void SetParentActive (BOOL bParentActive = true);

	BOOL IsParentActive () const;

	void SetParentMaximize (BOOL bParentMaximize = true);

	BOOL IsParentMaximize () const;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSMCaptionBar)
	public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nID = uiCaprionBarID);
	virtual BOOL CreateEx(CWnd* pParentWnd, UINT nID = uiCaprionBarID);
	virtual CSize CalcFixedLayout(BOOL, BOOL);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPaint(CDC* pDCPaint);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:

	//{{AFX_MSG(CBCGPMSMCaptionBar)
	afx_msg LRESULT OnSetText(WPARAM, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	virtual UINT HitTest (const CPoint& pt) const;
	virtual void ShowSysMenu (const CPoint& point);

public:
	CString 				 m_strCaption;

	HICON					 m_hIcon;
	CSize					 m_szIcon;

	BOOL					 m_bParentActive;
	BOOL					 m_bParentMaximize;

	int						 m_SystemHeight;
	int						 m_CaptionHeight;
	CFont					 m_CaptionFont;

	CBCGPMSMCaptionBarButton m_BtnMinimize;
	CBCGPMSMCaptionBarButton m_BtnMaximize;
	CBCGPMSMCaptionBarButton m_BtnClose;
};


inline
int CBCGPMSMCaptionBar::GetCaptionHeight () const
{
	return m_CaptionHeight;
}


inline
HFONT CBCGPMSMCaptionBar::GetCaptionFont () const
{
	return (HFONT)m_CaptionFont.GetSafeHandle ();
}


inline
BOOL CBCGPMSMCaptionBar::IsParentActive () const
{
	return m_bParentActive;
}


inline
BOOL CBCGPMSMCaptionBar::IsParentMaximize () const
{
	return m_bParentMaximize;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMCAPTIONBAR_H__4B2621B3_9ADD_4F3B_9A2C_27E1188E2613__INCLUDED_)
