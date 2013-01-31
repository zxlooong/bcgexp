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
#if !defined(AFX_BACKGNDIMAGEDLG_H__903DC013_D442_4922_8A05_52B4586DF486__INCLUDED_)
#define AFX_BACKGNDIMAGEDLG_H__903DC013_D442_4922_8A05_52B4586DF486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackgndImageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackgndImageDlg dialog

class CBackgndImageDlg : public CDialog
{
// Construction
public:
	CBackgndImageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackgndImageDlg)
	enum { IDD = IDD_BACK_IMAGE };
	CBCGPColorButton	m_btnTextColor;
	CStatic	m_wndPictureArea;
	CSliderCtrl	m_wndBright;
	CEdit	m_wndFilePath;
	CButton	m_wndBrowse;
	CString	m_strFilePath;
	int		m_iImageType;
	int		m_iBright;
	CString	m_strBright;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackgndImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBackgndImageDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnImageType();
	afx_msg void OnBrowse();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnChangeFilePath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void UpdateBitmap ();

	CRect	m_rectPreview;
	CBitmap	m_Bitmap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKGNDIMAGEDLG_H__903DC013_D442_4922_8A05_52B4586DF486__INCLUDED_)
