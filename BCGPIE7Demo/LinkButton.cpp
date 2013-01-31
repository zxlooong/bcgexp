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
// LinkButton.cpp: implementation of the CLinkButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "LinkButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLinkButton, CBCGPToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinkButton::CLinkButton()
{
	Initialize ();
}
//***************************************************************************************
CLinkButton::CLinkButton(LPCTSTR lpszLabel, LPCTSTR lpszURL)
{
	m_strURL = lpszURL;
	m_strText = lpszLabel;

	Initialize ();
}
//***************************************************************************************
CLinkButton::~CLinkButton()
{

}
//***************************************************************************************
void CLinkButton::Initialize ()
{
	m_nID = ID_LINK_1;
	SetImage (CImageHash::GetImageOfCommand (ID_LINK_1));
	m_bImage = m_bText = TRUE;
}
//*********************************************************************************
void CLinkButton::CopyFrom (const CBCGPToolbarButton& src)
{
	CBCGPToolbarButton::CopyFrom (src);

	const CLinkButton& srcLinkButton = (const CLinkButton&) src;
	m_strURL = srcLinkButton.m_strURL;
}					
//***************************************************************************************
void CLinkButton::Serialize (CArchive& ar)
{
	CBCGPToolbarButton::Serialize (ar);

	if (ar.IsLoading ())
	{
		ar >> m_strURL;
	}
	else
	{
		ar << m_strURL;
	}
}
