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
// formatba.h : header file
//

#ifndef __FORMATBA_H__
#define __FORMATBA_H__

/////////////////////////////////////////////////////////////////////////////
// CFormatBar dialog
class CFormatBar : public CBCGPToolBar
{
	DECLARE_SERIAL(CFormatBar)

// Construction
public:
	CFormatBar();

// Operations
public:
	virtual void CFormatBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

	CBCGPColorMenuButton* CreateColorButton ();
	CBCGPToolbarFontCombo* CreateFontComboButton ();
	CBCGPToolbarMenuButton* CreateBorderTypeButton ();

// Attributes
public:
	CSize m_szBaseUnits;

protected:
	CPalette	m_palColorPicker;	// Palette for color picker
	int			m_nNumColours;

// Implementation
protected:
	virtual void OnReset ();

	// Generated message map functions
	//{{AFX_MSG(CFormatBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

/////////////////////////////////////////////////////////////////////////////
