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
// MenuBar.h : header file
//

#if !defined(AFX_MENUBAR_H__62AB342E_1B46_4D69_B671_50EB5867611D__INCLUDED_)
#define AFX_MENUBAR_H__62AB342E_1B46_4D69_B671_50EB5867611D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMenuBar window

class CMenuBar : public CBCGPMenuBar
{
// Construction
public:
	CMenuBar();

// Attributes
public:

// Operations
public:

	inline BOOL IsTempVisible () const
	{
		return m_bTempVisible;
	}
	void SetTempVisible (BOOL bTemp)
	{
		m_bTempVisible = bTemp;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMenuBar();

	virtual BOOL IsVisible () const;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMenuBar)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void CloseTemp ();

	virtual BOOL SaveState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);

protected:
	BOOL	m_bTempVisible;
	BOOL	m_bSaveState;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUBAR_H__62AB342E_1B46_4D69_B671_50EB5867611D__INCLUDED_)
