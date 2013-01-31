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
// RibbonTableButton.h: interface for the CRibbonTableButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIBBONTABLEBUTTON_H__49EF9705_17D2_4DC2_A911_629F8F8807FF__INCLUDED_)
#define AFX_RIBBONTABLEBUTTON_H__49EF9705_17D2_4DC2_A911_629F8F8807FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRibbonTableButton : public CBCGPRibbonPaletteButton  
{
	DECLARE_DYNCREATE(CRibbonTableButton)

// Construction:
public:
	CRibbonTableButton ()
	{
	}

	CRibbonTableButton (
		UINT	nID,
		LPCTSTR	lpszText,
		int		nSmallImageIndex,
		int		nLargeImageIndex);

	virtual ~CRibbonTableButton();

// Attributes:
public:
	static int GetRows ()
	{
		return m_nRows;
	}

	static int GetColumns ()
	{
		return m_nColumns;
	}

protected:
	static int	m_nRows;
	static int	m_nColumns;

// Overrides:
protected:
	virtual void OnDrawPaletteIcon (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* pIcon, COLORREF clrText);
	virtual void NotifyHighlightListItem (int nIndex);
	virtual void OnShowPopupMenu ();

// Operations:
protected:
};

#endif // !defined(AFX_RIBBONTABLEBUTTON_H__49EF9705_17D2_4DC2_A911_629F8F8807FF__INCLUDED_)
