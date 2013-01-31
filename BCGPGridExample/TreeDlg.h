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
#if !defined(AFX_TREEDLG_H__8AA0F68E_6117_4B66_8C12_42155CA23060__INCLUDED_)
#define AFX_TREEDLG_H__8AA0F68E_6117_4B66_8C12_42155CA23060__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeDlg dialog

class CTreeDlg : public CDialog
{
// Construction
public:
	CTreeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTreeDlg)
	enum { IDD = IDD_TREE };
	CStatic	m_wndTreeLocation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTreeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGPGridCtrl		m_wndGridTree;
	CImageList			m_Images;

	void FillImagesFoder (CBCGPGridRow* pFolder);
	void FillMusicFoder (CBCGPGridRow* pFolder);
	void FillProjectFoder (CBCGPGridRow* pFolder);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEDLG_H__8AA0F68E_6117_4B66_8C12_42155CA23060__INCLUDED_)
