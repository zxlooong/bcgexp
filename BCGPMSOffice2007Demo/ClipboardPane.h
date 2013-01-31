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
// ClipboardPane.h : header file
//

#if !defined(AFX_CLIPBOARDPANE_H__C521A238_3386_4850_BCBA_1D4CA007E535__INCLUDED_)
#define AFX_CLIPBOARDPANE_H__C521A238_3386_4850_BCBA_1D4CA007E535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClipboardPane window

class CClipboardPane : public CBCGPDialogBar
{
	DECLARE_DYNAMIC(CClipboardPane)

// Construction
public:
	CClipboardPane();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClipboardPane)
	enum { IDD = IDD_CLIPBOARD };
	CBCGPStatic	m_wndLabel;
	CBCGPListBox m_wndItems;
	CBCGPButton	m_btnOption1;
	CBCGPButton	m_btnOption2;
	CBCGPButton	m_btnPasteAll;
	CBCGPButton	m_btnClearAll;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void AdjustControls ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipboardPane)
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

	virtual BCGP_DOCK_TYPE GetDockMode () const 
	{
		return BCGP_DT_IMMEDIATE;
	}

// Implementation
public:
	virtual ~CClipboardPane();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClipboardPane)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()


	int	m_mButtonsFullWidth;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPBOARDPANE_H__C521A238_3386_4850_BCBA_1D4CA007E535__INCLUDED_)
