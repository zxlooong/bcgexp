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
#if !defined(AFX_PAGE1_H__42746B5E_E6CC_48E5_BA21_103576DE34BE__INCLUDED_)
#define AFX_PAGE1_H__42746B5E_E6CC_48E5_BA21_103576DE34BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage1 dialog

class CPage1 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPage1)

// Construction
public:
	CPage1();
	~CPage1();

// Dialog Data
	//{{AFX_DATA(CPage1)
	enum { IDD = IDD_PAGE1 };
	CBCGPButton	m_btnMultiLine;
	CComboBox	m_wndBorder;
	CStatic	m_wndBorderLabel;
	CBCGPButton	m_btnCheck;
	CButton	m_wndXPButtons;
	BOOL	m_bXPButtons;
	BOOL	m_bCheck;
	CBCGPButton	m_Button;
	CString	m_strToolTip;
	int		m_iFrameRate;
	int		m_iImage;
	int		m_iBorderStyle;
	int		m_iCursor;
	CBCGPMenuButton	m_btnMenu;
	BOOL	m_bMenuStayPressed;
	BOOL	m_bRightArrow;
	int		m_nImageLocation;
	BOOL	m_bMenuDefaultClick;
	//}}AFX_DATA
	CBCGPButton	m_btnRadio1;
	CBCGPButton	m_btnRadio2;
	CBCGPButton	m_btnRadio3;
	CBCGPButton	m_btnRadio4;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage1)
	afx_msg void OnXpButtons();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetTooltip();
	afx_msg void OnSetCursor();
	afx_msg void OnButton();
	afx_msg void OnRightArrow();
	afx_msg void OnButtonMenu();
	afx_msg void OnPressedOnMenu();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnItem1();
	afx_msg void OnItem2();
	afx_msg void OnDialogAbout();
	afx_msg void OnUpdateItem2(CCmdUI* pCmdUI);
	afx_msg void OnResetButton();
	afx_msg void OnMenuDefaultClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CMenu		m_menu;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1_H__42746B5E_E6CC_48E5_BA21_103576DE34BE__INCLUDED_)
