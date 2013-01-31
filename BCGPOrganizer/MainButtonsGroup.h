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
#if !defined(AFX_MAINBUTTONSGROUP_H__DA3A1C0B_543C_4DD4_AC46_502F7294DA04__INCLUDED_)
#define AFX_MAINBUTTONSGROUP_H__DA3A1C0B_543C_4DD4_AC46_502F7294DA04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainButtonsGroup.h : header file
//

class CMainButtonsGroup : public CBCGPRibbonButtonsGroup
{
	DECLARE_DYNCREATE(CMainButtonsGroup)

public:
	CMainButtonsGroup(LPCTSTR lpszLabel = NULL)
	{
		SetText (lpszLabel == NULL ? _T("") : lpszLabel);
		AddButton (new CBCGPRibbonLabel (m_strText));
	}

protected:
	virtual void OnAfterChangeRect (CDC* pDC);
	virtual CSize GetRegularSize (CDC* pDC);
	virtual void OnDraw (CDC* pDC);
	virtual BOOL OnMenuKey (UINT nUpperChar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINBUTTONSGROUP_H__DA3A1C0B_543C_4DD4_AC46_502F7294DA04__INCLUDED_)
