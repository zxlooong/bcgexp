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
#if !defined(AFX_RIBBONLISTBUTTON_H__46553F75_B494_4B85_A707_701639C71BD7__INCLUDED_)
#define AFX_RIBBONLISTBUTTON_H__46553F75_B494_4B85_A707_701639C71BD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RibbonListButton.h : header file
//

class CRibbonListButton : public CBCGPRibbonPaletteButton  
{
	DECLARE_DYNCREATE(CRibbonListButton)

// Construction:
public:
	CRibbonListButton ();

	CRibbonListButton (
		UINT	nID,
		LPCTSTR	lpszText,
		int		nSmallImageIndex,
		int		nLargeImageIndex,
		BOOL    bRightAlignedText = TRUE);

	CRibbonListButton (
		UINT	nID,
		LPCTSTR	lpszText,
		int		nSmallImageIndex,
		int		nLargeImageIndex,
		UINT	uiImagesPaletteResID,
		int		cxPaletteImage,
		const CStringArray& arLabels,
		BOOL    bRightAlignedText = TRUE);

	virtual ~CRibbonListButton();

public:
	void AddGroup (
			LPCTSTR				lpszGroupName,
			UINT				uiImagesPaletteResID,
			int					cxPaletteImage,
			const CStringArray& arLabels);

	virtual void Clear ();

	void SetRightAlignedText (BOOL bSet = TRUE);

protected:
	virtual CSize GetIconSize () const;
	virtual void OnDrawPaletteIcon (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* pIcon, COLORREF clrText);
	virtual void CopyFrom (const CBCGPBaseRibbonElement& src);
	virtual void OnShowPopupMenu ();

	virtual BOOL IsItemMenuLook () const
	{
		return m_bRightAlignedText;
	}

	void RecalcTextSizes (CDC* pDC);

protected:
	CBCGPToolBarImages	m_listImages;
	CStringArray		m_arLabels;
	CSize				m_sizeMargins;
	BOOL				m_bRightAlignedText;
	CSize				m_sizeMaxText;
};


class CRibbonListFontButton : public CBCGPRibbonPaletteButton  
{
	DECLARE_DYNCREATE(CRibbonListFontButton)

public:
	struct XItem
	{
		CString m_Caption;
		LOGFONT m_Font[2];
		int     m_Height;

		XItem ()
		{
			ZeroMemory (&m_Font[0], sizeof (LOGFONT));
			ZeroMemory (&m_Font[1], sizeof (LOGFONT));

			m_Font[0].lfHeight         = -14;
			m_Font[0].lfWeight         = FW_BOLD;
			m_Font[0].lfCharSet        = DEFAULT_CHARSET;
			m_Font[0].lfOutPrecision   = OUT_DEFAULT_PRECIS;
			m_Font[0].lfClipPrecision  = CLIP_DEFAULT_PRECIS;
			m_Font[0].lfQuality        = DEFAULT_QUALITY;
			m_Font[0].lfPitchAndFamily = DEFAULT_PITCH;

			m_Font[1].lfHeight         = -12;
			m_Font[1].lfWeight         = FW_NORMAL;
			m_Font[1].lfCharSet        = DEFAULT_CHARSET;
			m_Font[1].lfOutPrecision   = OUT_DEFAULT_PRECIS;
			m_Font[1].lfClipPrecision  = CLIP_DEFAULT_PRECIS;
			m_Font[1].lfQuality        = DEFAULT_QUALITY;
			m_Font[1].lfPitchAndFamily = DEFAULT_PITCH;

			m_Height = 0;
		}

		XItem& operator = (const XItem& rItem)
		{
			m_Caption = rItem.m_Caption;
			memcpy (&m_Font[0], &rItem.m_Font[0], sizeof (LOGFONT));
			memcpy (&m_Font[1], &rItem.m_Font[1], sizeof (LOGFONT));
			m_Height = rItem.m_Height;

			return *this;
		}
	};

	typedef CArray<XItem, XItem&> XItems;

// Construction:
public:
	CRibbonListFontButton ();

	CRibbonListFontButton (
		UINT	nID,
		LPCTSTR	lpszText,
		int		nSmallImageIndex,
		int		nLargeImageIndex);

	CRibbonListFontButton (
		UINT	nID,
		LPCTSTR	lpszText,
		int		nSmallImageIndex,
		int		nLargeImageIndex,
		UINT	uiImagesPaletteResID,
		int		cxPaletteImage,
		const XItems& arItems);

	virtual ~CRibbonListFontButton();

public:
	void AddGroup (
			LPCTSTR		  lpszGroupName,
			UINT		  uiImagesPaletteResID,
			int			  cxPaletteImage,
			const XItems& arItems);

	virtual void Clear ();

protected:
	virtual CSize GetIconSize () const;
	virtual void OnDrawPaletteIcon (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* pIcon, COLORREF clrText);
	virtual void CopyFrom (const CBCGPBaseRibbonElement& src);
	virtual void OnShowPopupMenu ();

	void RecalcTextSizes (CDC* pDC);

protected:
	CBCGPToolBarImages	m_listImages;
	XItems				m_arItems;
	CSize				m_sizeMargins;
	CSize				m_sizeMaxText;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONLISTBUTTON_H__46553F75_B494_4B85_A707_701639C71BD7__INCLUDED_)
