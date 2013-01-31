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
// PropertiesViewBar.h: interface for the CPropertiesViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
#define AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPropertiesToolBar : public CBCGPToolBar
{
public:	
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)	
	{		
		CBCGPToolBar::OnUpdateCmdUI ((CFrameWnd*) GetOwner (), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList () const		{	return FALSE;	}
};

class CPropertiesViewBar : public CBCGPDockingControlBar  
{
// Construction
public:
	CPropertiesViewBar();

	void AdjustLayout ();

// Attributes
public:
	void SetVSDotNetLook (BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook (bSet);
		m_wndPropList.SetGroupNameFullWidth (bSet);
	}

	void OnChangeVisualStyle ();

protected:
	CComboBox			m_wndObjectCombo;
	CPropertiesToolBar	m_wndToolBar;
	CBCGPPropList		m_wndPropList;
	CFont				m_fntPropList;

// Attributes
protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesViewBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertiesViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSortingprop();
	afx_msg void OnUpdateSortingprop(CCmdUI* pCmdUI);
	afx_msg void OnProperies1();
	afx_msg void OnUpdateProperies1(CCmdUI* pCmdUI);
	afx_msg void OnProperies2();
	afx_msg void OnUpdateProperies2(CCmdUI* pCmdUI);
	afx_msg void OnExpand();
	afx_msg void OnUpdateExpand(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void InitPropList ();
	void SetPropListFont ();
};

#endif // !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
