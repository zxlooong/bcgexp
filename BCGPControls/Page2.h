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
#if !defined(AFX_PAGE2_H__5917C59B_76F1_41CE_9F59_2CB96304B3F5__INCLUDED_)
#define AFX_PAGE2_H__5917C59B_76F1_41CE_9F59_2CB96304B3F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage2 dialog

class CPage2 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPage2)

// Construction
public:
	CPage2();
	~CPage2();

// Dialog Data
	//{{AFX_DATA(CPage2)
	enum { IDD = IDD_PAGE2 };
	CBCGPColorPickerCtrl	m_wndColorHue;
	CBCGPColorPickerCtrl	m_wndLum;
	CBCGPColorPickerCtrl	m_wndColorPalette;
	CStatic	m_wndColorBarFrame2;
	CStatic	m_wndColorBarFrame;
	CBCGPColorButton	m_ColorPicker;
	CString	m_strRGB;
	CString	m_strRGBColorBar;
	CString	m_strRGBColorBar2;
	CString	m_strRGBColorDialog;
	CString	m_strRGBColorPalette;
	CString	m_strRGBColorHue;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage2)
	afx_msg void OnColorDlg();
	afx_msg void OnColorPicker();
	virtual BOOL OnInitDialog();
	afx_msg void OnColorPalette();
	afx_msg void OnLum();
	afx_msg void OnHue();
	//}}AFX_MSG
	afx_msg void OnColorBar();
	afx_msg void OnColorBar2();
	DECLARE_MESSAGE_MAP()

	COLORREF		m_Color;
	CBCGPColorBar	m_wndColorBar;
	CBCGPColorBar	m_wndColorBar2;

	CPalette		m_palColorPicker;
	CPalette		m_palSys;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE2_H__5917C59B_76F1_41CE_9F59_2CB96304B3F5__INCLUDED_)
