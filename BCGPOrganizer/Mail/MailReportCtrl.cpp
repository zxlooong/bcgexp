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
// MailReportCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "../BCGPOrganizer.h"
#include "MailReportCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailReportCtrl

CMailReportCtrl::CMailReportCtrl()
{
	SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
}

CMailReportCtrl::~CMailReportCtrl()
{
}


BEGIN_MESSAGE_MAP(CMailReportCtrl, CBCGPReportCtrl)
	//{{AFX_MSG_MAP(CMailReportCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL IsStringsSimmilarTo (CString str1, CString str2)
{
	int nIndex = -1;

	//---------------------------
	// Remove all "Re: ", "FWD: "
	//---------------------------
	while ((nIndex = str1.Find (':')) >= 0)
	{
		str1 = str1.Mid (nIndex + 1);
	}

	str1.TrimLeft ();
	str1.TrimRight ();

	while ((nIndex = str2.Find (':')) >= 0)
	{
		str2 = str2.Mid (nIndex + 1);
	}

	str2.TrimLeft ();
	str2.TrimRight ();

	return str1.CompareNoCase (str2) == 0;
}

BOOL DoCompare (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	switch (iColumn)
	{
	case 7:	// Created
	case 8:	// Received
		{
			COleDateTime date1 = (DATE) pRow1->GetItem (iColumn)->GetValue ();
			COleDateTime date2 = (DATE) pRow2->GetItem (iColumn)->GetValue ();

			return date1.GetYear () == date2.GetYear () &&
				date1.GetMonth () == date2.GetMonth () &&
				date1.GetDay () == date2.GetDay ();
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMailReportCtrl message handlers

int CMailReportCtrl::CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pRow1);
	ASSERT_VALID (pRow2);

	if (DoCompare (pRow1, pRow2, iColumn))
	{
		return 0;
	}

	return CBCGPReportCtrl::CompareGroup (pRow1, pRow2, iColumn);
}

CString CMailReportCtrl::GetGroupName (int iColumn, CBCGPGridItem* pItem)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pItem);

	if (iColumn == 7 ||	// Created
		iColumn == 8)	// Received
	{
		COleDateTime date = (DATE) pItem->GetValue ();

		CString strGroup;
		strGroup.Format (_T("%s: %s"), 
			m_Columns.GetColumnName (iColumn),
			date.Format (VAR_DATEVALUEONLY));

		return strGroup;
	}

	return CBCGPReportCtrl::GetGroupName (iColumn, pItem);
}
