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
#if !defined(AFX_PAGE5_H__66377156_5E09_4BE8_86BD_5271D9F7F60A__INCLUDED_)
#define AFX_PAGE5_H__66377156_5E09_4BE8_86BD_5271D9F7F60A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page5.h : header file
//

class CMyListCtrl : public CBCGPListCtrl
{
	virtual COLORREF OnGetCellTextColor (int nRow, int nColum);
	virtual COLORREF OnGetCellBkColor (int nRow, int nColum);
	virtual HFONT OnGetCellFont (int nRow, int nColum, DWORD dwData = 0);

public:
	BOOL	m_bColor;
	BOOL	m_bModifyFont;
};

/////////////////////////////////////////////////////////////////////////////
// CPage5 dialog

class CPage5 : public CBCGPPropertyPage
{
	friend class CMyListCtrl;

	DECLARE_DYNCREATE(CPage5)

// Construction
public:
	CPage5();
	~CPage5();

// Dialog Data
	//{{AFX_DATA(CPage5)
	enum { IDD = IDD_PAGE5 };
	CButton	m_btnExpandAll;
	CStatic	m_wndPropListLocation;
	CMyListCtrl	m_wndList;
	BOOL	m_bDescrArea;
	BOOL	m_bDotNetLook;
	BOOL	m_bHeader;
	BOOL	m_bMarkSortedColumn;
	BOOL	m_bColor;
	BOOL	m_bModifyFont;
	BOOL	m_bPropListCustomColors;
	BOOL	m_bPropListCategorized;
	BOOL	m_bShowDragContext;
	BOOL	m_bMarkChanged;
	BOOL	m_bHideFontProps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage5)
	virtual BOOL OnInitDialog();
	afx_msg void OnHeader();
	afx_msg void OnDotNetLook();
	afx_msg void OnDescriptionArea();
	afx_msg void OnMarkSortedColumn();
	afx_msg void OnColorRows();
	afx_msg void OnModifyFont();
	afx_msg void OnPropListCustomColors();
	afx_msg void OnProplistExpandAll();
	afx_msg void OnProplistCategorized();
	afx_msg void OnProplistCategorized2();
	afx_msg void OnResetValues();
	afx_msg void OnMarkChanged();
	afx_msg void OnHideFontProps();
	afx_msg void OnCommitChanges();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGPPropList	m_wndPropList;
	CImageList		m_imageList;

	CBCGPProp* pGroupFont;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE5_H__66377156_5E09_4BE8_86BD_5271D9F7F60A__INCLUDED_)
