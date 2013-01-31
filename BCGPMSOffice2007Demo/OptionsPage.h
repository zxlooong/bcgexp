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
#if !defined(AFX_OPTIONSPAGE_H__31F01121_D253_4175_9CD9_69615717107E__INCLUDED_)
#define AFX_OPTIONSPAGE_H__31F01121_D253_4175_9CD9_69615717107E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPage.h : header file
//

#include "DlgBanner.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsPage dialog

class COptionsPage : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(COptionsPage)

// Construction
public:
	COptionsPage();
	~COptionsPage();

// Dialog Data
	//{{AFX_DATA(COptionsPage)
	enum { IDD = IDD_POPULAR_PAGE };
	CBCGPColorButton	m_wndColor;
	CDlgBanner	m_wndBanner;
	CComboBox	m_wndColorScheme;
	int		m_nColorScheme;
	int		m_nTooltipStyle;
	BOOL	m_bShowDevTab;
	BOOL	m_bShowFloaty;
	BOOL	m_bShowKeyTips;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeColorScheme();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

class COptionsPropSheet : public CBCGPPropertySheet
{
public:
	COptionsPropSheet (CWnd* pWndParent, UINT nSelectedPage = 0);

protected:
	virtual BOOL OnInitDialog();
	virtual void OnDrawPageHeader (CDC* pDC, int nPage, CRect rectHeader);

	CBCGPToolBarImages	m_Icons;
	CBCGPControlRenderer m_Pat[4];
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSPAGE_H__31F01121_D253_4175_9CD9_69615717107E__INCLUDED_)
