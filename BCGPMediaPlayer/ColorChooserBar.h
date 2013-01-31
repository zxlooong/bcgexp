//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// ColorChooserBar.h : header file
//

#if !defined(AFX_COLORCHOOSERBAR_H__8E19868F_14F7_4F08_B024_1434ADD93539__INCLUDED_)
#define AFX_COLORCHOOSERBAR_H__8E19868F_14F7_4F08_B024_1434ADD93539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColorChooserButton: public CBCGPButton
{
	DECLARE_DYNCREATE(CColorChooserButton)

public:
	CColorChooserButton ()
	{
	}
	CColorChooserButton (const CSize& sizeImage, const CString& strImage);

protected:
	virtual void OnFillBackground (CDC* pDC, const CRect& rectClient)
	{
		if (!m_Image.IsValid ())
		{
			CBCGPButton::OnFillBackground (pDC, rectClient);
		}
	}
	virtual void OnDrawBorder (CDC* pDC, CRect& rectClient, UINT uiState)
	{
		if (!m_Image.IsValid ())
		{
			CBCGPButton::OnDrawBorder (pDC, rectClient, uiState);
		}
	}
	virtual void OnDrawFocusRect (CDC* pDC, const CRect& rectClient)
	{
		if (!m_Image.IsValid ())
		{
			CBCGPButton::OnDrawFocusRect (pDC, rectClient);
		}
	}
	virtual void OnDraw (CDC* pDC, const CRect& rect, UINT uiState);

private:
	CBCGPToolBarImages	m_Image;
};

/////////////////////////////////////////////////////////////////////////////
// CColorChooserBar dialog

class CColorChooserBar : public CBCGPDialogBar
{
	DECLARE_SERIAL(CColorChooserBar)

// Construction
public:
	CColorChooserBar();   // standard constructor

	void Reset ();
	void Preset (BOOL bNext);

// Dialog Data
	//{{AFX_DATA(CColorChooserBar)
	enum { IDD = IDD_COLOR_CHOOSER_BAR };
	CColorChooserButton	m_btnPresetPrev;
	CColorChooserButton	m_btnPresetNext;
	CBCGPURLLinkButton	m_btnReset;
	CBCGPSliderCtrl	m_wndSliderS;
	CBCGPSliderCtrl	m_wndSliderH;
	int		m_nHue;
	int		m_nSaturation;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorChooserBar)
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorChooserBar)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	void UpdateHS ();

private:
	long	m_Preset;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCHOOSERBAR_H__8E19868F_14F7_4F08_B024_1434ADD93539__INCLUDED_)
