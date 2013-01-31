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
// ToolBox.cpp: implementation of the CResourceViewBar class.
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "MainFrm.h"
#include "ToolBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBoxBar

CToolBoxBar::CToolBoxBar()
{
	CBCGPOutlookWnd::EnableAnimation ();
}

CToolBoxBar::~CToolBoxBar()
{
}

BEGIN_MESSAGE_MAP(CToolBoxBar, CBCGPToolBox)
	//{{AFX_MSG_MAP(CToolBoxBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CToolBoxBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	AddToolsPage (_T("Windows Forms"), IDB_TOOLS_PAGE1, 16, 
		_T("Pointer\nLabel\nButton\nTextBox\nMainMenu\nCheckBox\nRadioButton\nGroupBox\nPictureBox\nPanel\nDataGrid\nListBox\nCheckedListBox\nComboBox\nListView\nTreeView\nTabControl\nDateTimePicker\nMonthCalendar\nHScrollBar\nVScrollBar\nTimer\nSplitter\nDomainUpDown\nNumericUpDown\nTrackBar\nProgressBar\nRichTextBox"));

	GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);

	AddToolsPage (_T("Components"),	IDB_TOOLS_PAGE2, 16, _T("Pointer\nDataSet\nOleDbDataAdapter\nOleDbConnection"));
	AddToolsPage (_T("Data"),	IDB_TOOLS_PAGE3, 16, _T("Pointer\nFileSystemWatch\nEventLog\nDirectoryEntry"));

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CToolBoxBarEx

CToolBoxBarEx::CToolBoxBarEx()
{
}

CToolBoxBarEx::~CToolBoxBarEx()
{
}

BEGIN_MESSAGE_MAP(CToolBoxBarEx, CBCGPToolBoxEx)
	//{{AFX_MSG_MAP(CToolBoxBarEx)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CToolBoxBarEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolBoxEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	AddToolsPage (_T("Windows Forms"), IDB_TOOLS_PAGE1_HC, 16, 
		_T("Pointer\nLabel\nButton\nTextBox\nMainMenu\nCheckBox\nRadioButton\nGroupBox\nPictureBox\nPanel\nDataGrid\nListBox\nCheckedListBox\nComboBox\nListView\nTreeView\nTabControl\nDateTimePicker\nMonthCalendar\nHScrollBar\nVScrollBar\nTimer\nSplitter\nDomainUpDown\nNumericUpDown\nTrackBar\nProgressBar\nRichTextBox"));
	GetPage (0)->SetMode (CBCGPToolBoxPage::ToolBoxPageMode_Images);

	AddToolsPage (_T("Components"),	IDB_TOOLS_PAGE2_HC, 16, _T("Pointer\nDataSet\nOleDbDataAdapter\nOleDbConnection"));
	AddToolsPage (_T("Data"),	IDB_TOOLS_PAGE3_HC, 16, _T("Pointer\nFileSystemWatch\nEventLog\nDirectoryEntry"));

	return 0;
}
