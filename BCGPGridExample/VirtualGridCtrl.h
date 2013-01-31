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
#if !defined(AFX_VIRTUALGRIDCTRL_H__4ACA55A9_2297_4484_A5FD_4227754ABE8D__INCLUDED_)
#define AFX_VIRTUALGRIDCTRL_H__4ACA55A9_2297_4484_A5FD_4227754ABE8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VirtualGridCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVirtualGridCtrl window

class CVirtualGridCtrl : public CBCGPGridCtrl
{
// Construction
public:
	CVirtualGridCtrl();

// Attributes
protected:
	CMapStringToString m_mapChangedItems;

// Operations
public:
	CString GetItemValue (int nRow, int nColumn) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVirtualGridCtrl)
	//}}AFX_VIRTUAL

	virtual void OnItemChanged (CBCGPGridItem* pItem, int nRow, int nColumn);

// Implementation
public:
	virtual ~CVirtualGridCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVirtualGridCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRTUALGRIDCTRL_H__4ACA55A9_2297_4484_A5FD_4227754ABE8D__INCLUDED_)
