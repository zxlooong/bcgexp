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
// CustomCells.h: interface for the CColorGridItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMCELLS_H__2E159741_6592_4EA9_BBB1_B18CEE7D0BD5__INCLUDED_)
#define AFX_CUSTOMCELLS_H__2E159741_6592_4EA9_BBB1_B18CEE7D0BD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// CPasswordItem Class

class CPasswordItem : public CBCGPGridItem
{
public:
	CPasswordItem (const CString& strPassword);

protected:
	virtual CString FormatItem ();
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
};

/////////////////////////////////////////////////////////////////////////////
// CSliderItem object

class CItemSliderCtrl;

class CSliderItem : public CBCGPGridItem
{
public:
	CSliderItem (long lValue);

	void SetValue (const _variant_t& varValue);

protected:

	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual BOOL OnSetCursor () const	
	{
		return FALSE; /* Use default */	
	}

	virtual BOOL OnUpdateValue ();
};

/////////////////////////////////////////////////////////////////////////////
// CItemSliderCtrl window

class CItemSliderCtrl : public CSliderCtrl
{
	DECLARE_DYNAMIC(CItemSliderCtrl)

// Construction
public:
	CItemSliderCtrl(CSliderItem* pItem, COLORREF clrBack);

// Attributes
protected:
	CBrush			m_brBackground;
	COLORREF		m_clrBack;
	CSliderItem*	m_pItem;

// Operations
public:
	void Redraw ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropSliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CItemSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CItemSliderCtrl)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////
// CFileItem Class

class  CFileItem : public CBCGPGridItem
{
// Construction
public:
	CFileItem(const CString& strFileName);

// Overrides
	virtual void OnClickButton (CPoint point);
};

//////////////////////////////////////////////////////////////////////
// CFolderItem Class

class  CFolderItem : public CBCGPGridItem
{
// Construction
public:
	CFolderItem(const CString& strFolderName);

// Overrides
	virtual void OnClickButton (CPoint point);
};

//////////////////////////////////////////////////////////////////////
// CFontItem Class

class CFontItem : public CBCGPGridItem
{
// Construction
public:
	CFontItem(LOGFONT& lf);
	
// Overrides
public:
	virtual void OnClickButton (CPoint point);
	virtual CString FormatProperty ();

// Attributes
protected:
	LOGFONT		m_lf;
	LOGFONT		m_lfOrig;
	DWORD		m_dwFontDialogFlags;
	COLORREF	m_Color;

	virtual BOOL IsValueChanged () const
	{
		return memcmp (&m_lf, &m_lfOrig, sizeof (LOGFONT) != 0) ||
			lstrcmp (m_lf.lfFaceName, m_lfOrig.lfFaceName) != 0;
	}
};

//////////////////////////////////////////////////////////////////////
// CIconGridItem Class

class CIconGridItem : public CBCGPGridItem
{
public:
	CIconGridItem(
		const CImageList& imageListIcons, int nItem);

protected:
	
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	
	CBCGPToolBarImages	m_imageListIcons;
	int					m_nItem;
};

////////////////////////////////////////////////////////////////////////////////
// CIconListItem Class

class CIconListItem : public CBCGPGridItem
{
public:
	CIconListItem(const _variant_t varValue, const CImageList& imageListIcons,
							CStringList* plstIconNames = NULL);

protected:
	

	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
	virtual void OnDrawValue (CDC* pDC, CRect rect);

	CBCGPToolBarImages	m_imageListIcons;
	CStringList			m_lstIconNames;
	int					m_nSelectedIcon;
	CString				m_strVal;
};

/////////////////////////////////////////////////////////////////////////////
// CIconCombo window

class CIconCombo : public CComboBox
{
// Construction
public:
	CIconCombo(CBCGPToolBarImages& imageListIcons, CStringList& lstIconNames);
	CIconListItem* GetIconListItem()
	{
		return m_pIconListItem;
	}
	void SetIconListItem(CIconListItem* pIconListItem)
	{
		m_pIconListItem=pIconListItem;
	}
	
// Attributes
protected:
	CBCGPToolBarImages&	m_imageListIcons;
	CStringList&		m_lstIconNames;
	CIconListItem* m_pIconListItem;

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
	afx_msg void OnCbnSelchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////
// CProgressItem Class

class CProgressItem : public CBCGPGridItem
{
public:
	CProgressItem (long lValue, long lTotal);

	long GetTotal () const
	{
		return m_lTotal;
	}

protected:
	virtual CWnd* CreateInPlaceEdit (CRect /*rectEdit*/, BOOL& /*bDefaultFormat*/)
	{
		return NULL;
	}

	virtual void OnDrawValue (CDC* pDC, CRect rect);

	long m_lTotal;
};

////////////////////////////////////////////////////////////////////////////////
// CButtonItem Class

class CButtonItem : public CBCGPGridItem
{
public:
	CButtonItem (LPCTSTR lpszText, UINT id);

protected:
	virtual CWnd* CreateInPlaceEdit (CRect /*rectEdit*/, BOOL& /*bDefaultFormat*/)
	{
		return NULL;
	}

	virtual BOOL OnSetCursor () const
	{
		return FALSE; /* Use default */	
	}

	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual BOOL OnClickValue (UINT uiMsg, CPoint point);

	UINT	m_id;
};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_CUSTOMCELLS_H__2E159741_6592_4EA9_BBB1_B18CEE7D0BD5__INCLUDED_)
