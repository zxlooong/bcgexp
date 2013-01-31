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
// ToolBox.h: interface for the CToolBoxBar class.
//

#if !defined(AFX_TOOLBOX_H__F9C28947_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
#define AFX_TOOLBOX_H__F9C28947_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CToolBoxBar : public CBCGPToolBox
{
// Construction
public:
	CToolBoxBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBoxBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBoxBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBoxBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CToolBoxBarEx : public CBCGPToolBoxEx
{
// Construction
public:
	CToolBoxBarEx();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBoxBarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBoxBarEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBoxBarEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TOOLBOX_H__F9C28947_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
