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
#if !defined(AFX_MAILREPORTCTRL_H__4C52E118_4FB2_4BBD_8D59_6F9E5A493C80__INCLUDED_)
#define AFX_MAILREPORTCTRL_H__4C52E118_4FB2_4BBD_8D59_6F9E5A493C80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailReportCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailReportCtrl window

class CMailReportCtrl : public CBCGPReportCtrl
{
// Construction
public:
	CMailReportCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailReportCtrl)
	//}}AFX_VIRTUAL

	virtual int CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn);
	virtual CString GetGroupName (int nGroupCol, CBCGPGridItem* pItem);
	
// Implementation
public:
	virtual ~CMailReportCtrl();

	//--------------
	// Drag and drop
	//--------------
	virtual BOOL OnHideInsertedGroupColumn (int /*nColumn*/) const
	{
		return TRUE;
	}

	// Generated message map functions
protected:
	//{{AFX_MSG(CMailReportCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILREPORTCTRL_H__4C52E118_4FB2_4BBD_8D59_6F9E5A493C80__INCLUDED_)
