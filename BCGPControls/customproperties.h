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
// CustomProperties.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMPROPERTIES_H__1EB0FB92_8DCC_4A06_948E_2AB23F319482__INCLUDED_)
#define AFX_CUSTOMPROPERTIES_H__1EB0FB92_8DCC_4A06_948E_2AB23F319482__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDurationProp : public CBCGPProp
{
// Construction
public:
	CDurationProp(const CString& strName, const COleDateTimeSpan& duration, 
		LPCTSTR lpszDescr = NULL, DWORD dwData = 0);

// Overrides
public:
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual void OnPosSizeChanged (CRect rectOld);
	virtual BOOL OnUpdateValue ();
	virtual void AdjustInPlaceEditRect (CRect& rectEdit, CRect& rectSpin);

	virtual void OnSetSelection (CBCGPProp* pOldSel);
	virtual void OnKillSelection (CBCGPProp* pNewSel);

	virtual BOOL PushChar (UINT nChar);

// Attributes
public:
	void SetDuration (COleDateTimeSpan duration);
	COleDateTimeSpan GetDuration () const
	{
		return (COleDateTimeSpan) (double) m_varValue;
	}

protected:
	CBCGPDurationCtrl	m_wndDuration;
};


class CCheckBoxProp : public CBCGPProp
{
public:
	CCheckBoxProp(
		const CString& strName,
		BOOL bCheck,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
	);

protected:
	virtual BOOL OnEdit(LPPOINT /*lptClick*/)						{	return FALSE;	}
	virtual void OnDrawButton (CDC* /*pDC*/, CRect /*rectButton*/)	{}
	virtual void OnDrawValue(CDC* /*pDC*/, CRect /*rect*/)			{}
	virtual BOOL HasButton () const									{	return FALSE;	}

	virtual BOOL PushChar (UINT nChar);
	virtual void OnDrawCheckBox (CDC * pDC, CRect rectCheck, BOOL bChecked);
	virtual void OnDrawName (CDC* pDC, CRect rect);
	virtual void OnClickName (CPoint point);
	virtual BOOL OnDblClick (CPoint point);

protected:
	CRect	m_rectCheck;
};

class CPasswordProp : public CBCGPProp
{
public:
	CPasswordProp(
		const CString& strName,
		const CString& strPassword,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
	);

protected:
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual CString FormatProperty ();
};

class CSliderProp : public CBCGPProp
{
public:
	CSliderProp(
		const CString& strName,
		long nValue,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
	);

	virtual BOOL OnUpdateValue ();

protected:
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual BOOL OnSetCursor () const	{	return FALSE; /* Use default */	}
};

/////////////////////////////////////////////////////////////////////////////
// CPropSliderCtrl window

class CPropSliderCtrl : public CSliderCtrl
{
// Construction
public:
	CPropSliderCtrl(CSliderProp* pProp, COLORREF clrBack);

// Attributes
protected:
	CBrush			m_brBackground;
	COLORREF		m_clrBack;
	CSliderProp*	m_pProp;

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropSliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropSliderCtrl)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg void HScroll (UINT nSBCode, UINT nPos);

	DECLARE_MESSAGE_MAP()
};

class CIconListProp : public CBCGPProp
{
public:
	CIconListProp(
		const CString& strName,
		const CImageList& imageListIcons,
		int nSelectedIcon,
		CStringList* plstIconNames = NULL,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
	);

protected:
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
	virtual void OnDrawValue (CDC* pDC, CRect rect);

	CBCGPToolBarImages	m_imageListIcons;
	CStringList			m_lstIconNames;
};

/////////////////////////////////////////////////////////////////////////////
// CIconCombo window

class CIconCombo : public CComboBox
{
// Construction
public:
	CIconCombo(CBCGPToolBarImages& imageListIcons, CStringList& lstIconNames);

// Attributes
protected:
	CBCGPToolBarImages&	m_imageListIcons;
	CStringList&		m_lstIconNames;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconCombo)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIconCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIconCombo)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CComboBoxExProp : public CBCGPProp
{
public:
	CComboBoxExProp(
		const CString& strName,
		const CString& strValue,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0,
		CImageList* pImageList = NULL
	);

	BOOL AddOption (LPCTSTR lpszOption, int nIcon = -1, int nIndent = 0);

protected:
	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
	virtual BOOL OnEdit (LPPOINT lptClick);

	CImageList*			m_pImageList;
	CArray<int, int>	m_lstIcons;
	CArray<int, int>	m_lstIndents;
};

class COwnerDrawDescrProp : public CBCGPProp
{
public:
	COwnerDrawDescrProp(
		const CString& strName,
		const _variant_t& varValue
	);

protected:
	virtual void OnDrawDescription (CDC* pDC, CRect rect);
};

class CTwoButtonsProp : public CBCGPProp
{
public:
	CTwoButtonsProp(
		const CString& strName,
		const _variant_t& varValue
	);

protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void AdjustButtonRect ();
	virtual void OnClickButton (CPoint point);
	virtual void OnDrawButton (CDC* pDC, CRect rectButton);

	CImageList	m_images;
};

class CCustomDlgProp : public CBCGPProp
{
public:
	CCustomDlgProp(
		const CString& strName,
		const _variant_t& varValue
	);

protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void OnClickButton (CPoint point);
};

#endif // !defined(AFX_CUSTOMPROPERTIES_H__1EB0FB92_8DCC_4A06_948E_2AB23F319482__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
