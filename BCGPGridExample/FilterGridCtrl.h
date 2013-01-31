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
// FilterGridCtrl.h : header file
//

#if !defined(AFX_FILTERGRIDCTRL_H__FAA3ED71_D929_45A2_BBA5_981D7592E8C6__INCLUDED_)
#define AFX_FILTERGRIDCTRL_H__FAA3ED71_D929_45A2_BBA5_981D7592E8C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// filter parameters

struct FILTER_PARAM	// used by filter callback function
{
// Construction
	FILTER_PARAM () : nCol (-1), bAll (TRUE) {}
	FILTER_PARAM (const FILTER_PARAM& src)
	{
		Copy (src);
	}

	void Clear ();
	void Copy (const FILTER_PARAM& src);

// Attributes
	int				nCol;		// Column index

	CString			strFilter;	// Filter string text

	BOOL			bAll;
	CStringList		lstStrings;	// Allowed values
	CList<int, int>	lstValues;	// Allowed values
};

/////////////////////////////////////////////////////////////////////////////
// CFilterGridCtrl window

class CFilterGridCtrl : public CBCGPGridCtrl
{
	DECLARE_DYNCREATE(CFilterGridCtrl)

// Construction
public:
	CFilterGridCtrl();

// Attributes
public:
	FILTER_PARAM	m_param;
	CBCGPToolBarImages	m_ImagesHeaderBtn;

// Operations
public:
	BOOL AddRec (LPCTSTR strName, LPCTSTR strCompany, LPCTSTR strDepartment,
				 LPCTSTR strSex, int nAge, LPCTSTR strFamily);
	void GetStringList (CStringList& lst, int nColumn);

	void SetDefaultDemoFilter (int nColumn);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterGridCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilterGridCtrl();

protected:
	virtual int GetHeaderMenuButtonImageIndex (int nColumn, BOOL bSortArrow) const;
	virtual void OnHeaderMenuButtonClick (int nColumn, CRect rectMenuButton);

	// Generated message map functions
protected:
	//{{AFX_MSG(CFilterGridCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	static LRESULT CALLBACK pfnFilterCallback (WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERGRIDCTRL_H__FAA3ED71_D929_45A2_BBA5_981D7592E8C6__INCLUDED_)
