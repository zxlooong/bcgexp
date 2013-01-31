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
// WorkspaceObj.h: interface for the CWorkspaceObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACEOBJ_H__E9D13F55_0980_46DE_85A6_1589254B3E83__INCLUDED_)
#define AFX_WORKSPACEOBJ_H__E9D13F55_0980_46DE_85A6_1589254B3E83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWorkspaceObj : public CObject  
{
public:
	CWorkspaceObj (	const CString& strName, const UINT uiCmd, 
					const int iIconIndex,
					const UINT uiDefaultNewAction);
	virtual ~CWorkspaceObj();

	const CString	m_strName;
	const UINT		m_uiCmd;
	const int		m_iIconIndex;
	const UINT		m_uiDefaultNewAction;
};

#endif // !defined(AFX_WORKSPACEOBJ_H__E9D13F55_0980_46DE_85A6_1589254B3E83__INCLUDED_)
