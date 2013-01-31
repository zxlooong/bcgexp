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
#if !defined(AFX_COLORCOMBOBOX_H__BDBB5AE4_2769_4A9B_8D64_CC03F7785A6F__INCLUDED_)
#define AFX_COLORCOMBOBOX_H__BDBB5AE4_2769_4A9B_8D64_CC03F7785A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox window

class CColorComboBox : public CBCGPComboBox
{
// Construction
public:
	CColorComboBox();

// Attributes
public:

// Operations
public:
	int AddColor (COLORREF color, CString strLabel);
	
	COLORREF GetColor (int nIndex) const
	{
		COLORREF color = RGB (255, 255, 255);
		m_Colors.Lookup (nIndex, color);

		return color;
	}

	int FindColor (COLORREF color) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorComboBox)
	public:
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	CMap<int, int&, COLORREF, COLORREF&>	m_Colors;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCOMBOBOX_H__BDBB5AE4_2769_4A9B_8D64_CC03F7785A6F__INCLUDED_)
