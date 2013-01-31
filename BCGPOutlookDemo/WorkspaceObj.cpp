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
// WorkspaceObj.cpp: implementation of the CWorkspaceObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPOutlookDemo.h"
#include "WorkspaceObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorkspaceObj::CWorkspaceObj (const CString& strName, const UINT uiCmd, 
							  const int iIconIndex,
							  const UINT uiDefaultNewAction) :
	m_strName (strName),
	m_uiCmd (uiCmd),
	m_iIconIndex (iIconIndex),
	m_uiDefaultNewAction (uiDefaultNewAction)
{
}

CWorkspaceObj::~CWorkspaceObj()
{

}
