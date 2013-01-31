//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPControlsDlg.h : header file
//

#if !defined(AFX_BCGPControlsDLG_H__49B6759C_C3E1_11D3_A722_009027900694__INCLUDED_)
#define AFX_BCGPControlsDLG_H__49B6759C_C3E1_11D3_A722_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBCGPControlsDlg dialog

class CBCGPControlsDlg : public CBCGPDialog
{
// Construction
public:
	CBCGPControlsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBCGPControlsDlg)
	enum { IDD = IDD_BCGPCONTROLS_DIALOG };
	CButton	m_wndXPButtons;
	CBCGPColorButton	m_ColorPicker;
	CStatic	m_wndImageArea;
	CBCGPButton	m_btnImageEdit;
	CSliderCtrl	m_wndFrameRate;
	CBCGPButton	m_wndStopAnimation;
	CBCGPButton	m_wndStartAnimation;
	CBCGPAnimCtrl	m_wndAnimation;
	CBCGPURLLinkButton	m_btnLink;
	CBCGPEditListBox	m_wndEditListBox;
	CBCGPMenuButton	m_btnMenu;
	CBCGPButton	m_Button;
	BOOL	m_bIsRightImage;
	CString	m_strToolTip;
	BOOL	m_bRightArrow;
	int		m_iFrameRate;
	int		m_iImage;
	int		m_iBorderStyle;
	int		m_iCursor;
	CString	m_strRGB;
	BOOL	m_bMenuStayPressed;
	BOOL	m_bBackImage;
	BOOL	m_bXPButtons;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPControlsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBCGPControlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetTooltip();
	afx_msg void OnResetButton();
	afx_msg void OnSetCursor();
	afx_msg void OnRightArrow();
	afx_msg void OnButtonMenu();
	afx_msg void OnButton();
	afx_msg void OnStartAnimation();
	afx_msg void OnStopAnimation();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEditImage();
	afx_msg void OnColorDlg();
	afx_msg void OnColorPicker();
	afx_msg void OnPressedOnMenu();
	afx_msg void OnBackground();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnItem1();
	afx_msg void OnItem2();
	afx_msg void OnDialogAbout();
	afx_msg void OnUpdateItem2(CCmdUI* pCmdUI);
	afx_msg void OnXpButtons();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CMenu		m_menu;
	CRect		m_rectImage;
	CBitmap		m_bmpImage;
	COLORREF	m_Color;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPControlsDLG_H__49B6759C_C3E1_11D3_A722_009027900694__INCLUDED_)
