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
#if !defined(AFX_PROPERTYBAR_H__2317B75E_543B_4B27_96E8_00D1FCFCE030__INCLUDED_)
#define AFX_PROPERTYBAR_H__2317B75E_543B_4B27_96E8_00D1FCFCE030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyBar window

class CPropertyBar : public CBCGPDockingControlBar
{
// Construction
public:
	CPropertyBar();

// Attributes
protected:
	CBCGPPropList	m_wndPropList;

	enum
	{
		idType,
		idBackground,
		idImages,
		idClockIcons,
		idShowToolTip,
		idFirstDayOfWeek,
		idDayTimeDelta,
		idDayWorkingHourFirst,
		idDayWorkingHourLast,
		idWeekDrawTimeFinish,
		idWeekDrawTimeIcons,
		idMonthDrawTimeFinish,
		idMonthDrawTimeIcons,
		idMonthCompressWeekend,
		idCalendarGradientFill,
		idCalendarWeekNumbers,
		idUseDayInsteadWeek,
	};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertyBar();

	void InitializeColors (BOOL bDark);
	void Update ();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

class CColorListProp : public CBCGPProp
{
public:
	CColorListProp(const CString& strName,
		COLORREF colorSelected,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
	);

	void Initialize (BOOL bDark);
	BOOL IsDark () const
	{
		return m_bDark;
	}

protected:
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);

	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual BOOL OnUpdateValue ();

	CArray<COLORREF,COLORREF>	m_arColors;
	BOOL m_bDark;
};

/////////////////////////////////////////////////////////////////////////////
// CColorPropComboBox window

class CColorPropComboBox : public CBCGPComboBox
{
// Construction
public:
	CColorPropComboBox (CArray<COLORREF,COLORREF>& arColors);

// Attributes
protected:
	CArray<COLORREF,COLORREF>&	m_arColors;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPropComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorPropComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorPropComboBox)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYBAR_H__2317B75E_543B_4B27_96E8_00D1FCFCE030__INCLUDED_)
