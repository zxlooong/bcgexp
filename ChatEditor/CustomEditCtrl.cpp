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
// CustomEditCtrl.cpp: implementation of the CCustomEditCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomEditCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomEditCtrl::CCustomEditCtrl()
{
	m_nMaxScrollWidth = 80;
	m_bCopyRTFToClipboard = TRUE;
}

CCustomEditCtrl::~CCustomEditCtrl()
{

}

BEGIN_MESSAGE_MAP(CCustomEditCtrl, CBCGPEditCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CCustomEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	UpdateScrollBars ();
	return 0;
}

void CCustomEditCtrl::UpdateScrollBars ()
{
	CBCGPEditCtrl::UpdateScrollBars ();

	ShowScrollBar (SB_HORZ, FALSE); // To disable horizontal scrollbar
}
