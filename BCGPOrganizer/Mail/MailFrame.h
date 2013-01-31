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

#if !defined(AFX_MAILFRAME_H__7FD48EC5_63C2_4374_89FE_7029E3726360__INCLUDED_)
#define AFX_MAILFRAME_H__7FD48EC5_63C2_4374_89FE_7029E3726360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailFrame.h : header file
//

#include "../EditDialogBar.h"
#include "../EditFrameDialog.h"

#include "../RibbonListButton.h"

class CMailDialogBar1: public CEditDialogBar
{
	friend class CMailFrame;
	DECLARE_SERIAL(CMailDialogBar1)

public:
	CMailDialogBar1 ();
	virtual ~CMailDialogBar1 ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL LoadState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}
	virtual BOOL SaveState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}

	virtual BOOL OnInitDialogBar();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CString	m_strFrom;
	CString	m_strTo;
	CString	m_strCc;
	CString	m_strSubject;
};

class CMailDialogBar2: public CEditDialogBar
{
	friend class CMailFrame;
	DECLARE_SERIAL(CMailDialogBar2)

public:
	CMailDialogBar2 ();
	virtual ~CMailDialogBar2 ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL LoadState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}
	virtual BOOL SaveState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}

	virtual BOOL OnInitDialogBar();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CString	m_strTo;
	CString	m_strCc;
	CString	m_strSubject;

	CBCGPButton m_Send;
};

class CMailFrame : public CEditFrameDialog
{
	DECLARE_DYNAMIC(CMailFrame)

public:
	enum XFormat
	{
		e_FormatPlain,
		e_FormatHTML,
		e_FormatRTF
	};

	enum XImportance
	{
		e_ImportanceNormal,
		e_ImportanceHigh,
		e_ImportanceLow
	};

// Attributes
public:
	CMailFrame(CBCGPGridRow& mail, 
				BOOL bReadOnly = FALSE,
				CWnd* pParent = NULL);

	virtual ~CMailFrame();

	BOOL IsDeleted () const
	{
		return m_bDeleted;
	}

// Operations
protected:
	virtual void OnOK();

	virtual BOOL CreateStatusBar ();

	virtual BOOL CreateOtherBars ();

	virtual BOOL LoadPanelImages ();

	virtual void AddMainCategory ();	
	virtual void AddTabs ();

	void AddTab_Home ();
	void AddTab_Options ();

	void CreateThemeList ();
	void CreateFontsList ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailFrame)
	public:
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMailFrame)
	afx_msg void OnFileClose();
	afx_msg void OnSaveClose ();
	afx_msg void OnDelete ();
	afx_msg void OnPrivate ();
	afx_msg void OnUpdatePrivate (CCmdUI* pCmdUI);
	afx_msg void OnImportanceLow ();
	afx_msg void OnUpdateImportanceLow (CCmdUI* pCmdUI);
	afx_msg void OnImportanceHigh ();
	afx_msg void OnUpdateImportanceHigh (CCmdUI* pCmdUI);
	afx_msg void OnFormatPlain ();
	afx_msg void OnUpdateFormatPlain (CCmdUI* pCmdUI);
	afx_msg void OnFormatHTML ();
	afx_msg void OnUpdateFormatHTML (CCmdUI* pCmdUI);
	afx_msg void OnFormatRTF ();
	afx_msg void OnUpdateFormatRTF (CCmdUI* pCmdUI);
	afx_msg void OnUpdateDummy (CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CMailDialogBar1	m_wndDialogBar1;
	CMailDialogBar2	m_wndDialogBar2;

	BOOL	m_bAttachment;
	BOOL	m_bPrivate;
	XImportance m_Importance;

	CBCGPGridRow& m_Mail;

	BOOL	m_bReadOnly;
	BOOL	m_bDeleted;
	XFormat m_Format;

	CStringArray	m_arThemes;
	CStringArray	m_arColorThemes;
	CRibbonListFontButton::XItems m_arFonts;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILFRAME_H__7FD48EC5_63C2_4374_89FE_7029E3726360__INCLUDED_)
