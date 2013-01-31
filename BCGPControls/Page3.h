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
#if !defined(AFX_PAGE3_H__E10BE142_6635_4C5B_93B9_9588F3CB944D__INCLUDED_)
#define AFX_PAGE3_H__E10BE142_6635_4C5B_93B9_9588F3CB944D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page3.h : header file
//

class CCustomEditListBox : public CBCGPEditListBox
{
	virtual void OnBrowse ()
	{
		int nSel = GetSelItem ();

		MessageBox (_T("Browse item..."));

		if (nSel == GetCount ())	// New item
		{
			int nSel = AddItem (_T("New text"));
			SelectItem (nSel);
		}
		else
		{
			SetItemText (nSel, _T("Updated text"));
		}
	}
};

class CMyBrowseEdit : public CBCGPEdit
{
	virtual void OnBrowse ()
	{
		MessageBox (_T("Browse item..."));
		SetWindowText (_T("New value!"));
	}
};

/////////////////////////////////////////////////////////////////////////////
// CPage3 dialog

class CPage3 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPage3)

// Construction
public:
	CPage3();
	~CPage3();

// Dialog Data
	//{{AFX_DATA(CPage3)
	enum { IDD = IDD_PAGE3 };
	CMyBrowseEdit	m_wndCustomEdit;
	CBCGPEdit	m_wndFolderEdit;
	CBCGPEdit	m_wndFileEdit;
	CBCGPFontComboBox	m_wndFont;
	CStatic	m_wndImageArea;
	CBCGPButton	m_btnImageEdit;
	CSliderCtrl	m_wndFrameRate;
	CBCGPButton	m_wndStopAnimation;
	CBCGPButton	m_wndStartAnimation;
	CBCGPAnimCtrl	m_wndAnimation;
	CBCGPURLLinkButton	m_btnLink;
	CCustomEditListBox	m_wndEditListBox;
	int		m_iFrameRate;
	BOOL	m_bTrueType;
	BOOL	m_bRaster;
	BOOL	m_bDeviceFont;
	BOOL	m_bDrawUsingFont;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage3)
	afx_msg void OnStartAnimation();
	afx_msg void OnStopAnimation();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEditImage();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnFontType();
	afx_msg void OnDrawUsingFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CRect		m_rectImage;
	CBitmap		m_bmpImage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE3_H__E10BE142_6635_4C5B_93B9_9588F3CB944D__INCLUDED_)
