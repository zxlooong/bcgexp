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


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONLISTBUTTON_H__46553F75_B494_4B85_A707_701639C71BD7__INCLUDED_)
