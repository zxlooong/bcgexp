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
// splash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBigIcon window

class CBigIcon : public CButton
{
// Attributes
public:
	CBitmap m_bitmap;
	CSize m_sizeBitmap;

// Operations
public:
	void SizeToContent();

// Implementation
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//{{AFX_MSG(CBigIcon)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog

class CSplashWnd : public CDialog
{
// Construction
public:
	BOOL Create(CWnd* pParent);

// Dialog Data
	//{{AFX_DATA(CSplashWnd)
	enum { IDD = IDD_SPLASH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	CBigIcon m_icon; // self-draw button

	// Generated message map functions
	//{{AFX_MSG(CSplashWnd)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
};
