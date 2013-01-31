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
// ChatEditorDlg.h : header file
//

#if !defined(AFX_CHATEDITORDLG_H__BB4AF02F_094E_4BB8_8609_5DFE68BFCAA9__INCLUDED_)
#define AFX_CHATEDITORDLG_H__BB4AF02F_094E_4BB8_8609_5DFE68BFCAA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CustomEditCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CChatEditorDlg dialog

class CChatEditorApp;

class CChatEditorDlg : public CDialog
{
	friend class CChatEditorApp;

// Construction
public:
	CChatEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatEditorDlg)
	enum { IDD = IDD_CHATEDITOR_DIALOG };
	CStatic	m_wndEditFrame2;
	CStatic	m_wndEditFrame1;
	CEdit	m_wndNick;
	CListBox	m_lstMembers;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatEditorDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON			m_hIcon;
	HACCEL			m_hAccel;
	CCustomEditCtrl	m_wndEditCtrl1;
	CCustomEditCtrl	m_wndEditCtrl2;
	CImageList		m_lstSym;
	//CSymMenu		m_menu;
	//CList<SYMMENU_ITEM_INFO, SYMMENU_ITEM_INFO&> m_lstMenuItemsInfo;

	// Generated message map functions
	//{{AFX_MSG(CChatEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnSmiles();
	afx_msg void OnButtonSend();
	afx_msg void OnDblclkListMembers();
	afx_msg void OnButtonSmiles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL LoadDefaultData ();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATEDITORDLG_H__BB4AF02F_094E_4BB8_8609_5DFE68BFCAA9__INCLUDED_)
