//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
#if !defined(AFX_TEMPDIALOGBAR_H__54540DEB_09B5_4C82_8E3A_B1A41B6FF530__INCLUDED_)
#define AFX_TEMPDIALOGBAR_H__54540DEB_09B5_4C82_8E3A_B1A41B6FF530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyDialogBar.h"
#include "TabWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CTempDialogBar dialog

class CTabBar : public CMyDialogBar
{
	DECLARE_SERIAL(CTabBar)

// Construction
public:
	CTabBar();
	virtual ~CTabBar();

	virtual int GetHeight (int height) const;
	virtual void Resize (BOOL bFull);

	void ShowFavoritesMenu ();

	void AddTab (HWND hWnd);
	void RemoveTab (HWND hWnd);
	void SetTabText (HWND hWnd);
	void SetTabIcon (HWND hWnd);
	void SetActiveTab (HWND hWnd);

	int GetTabsNum () const
	{
		return m_wndTab.GetTabsNum ();
	}

	void UpdateTabs (BOOL bRedraw);

	void EnableAero (BOOL /*bIsAero*/)
	{
		LoadImages();
	}

// Implementation
protected:

	virtual BOOL LoadImages();
	virtual void DrawButton(CBCGPButton& btn, CDC* pDC, const CRect& rect, UINT uiState);

	virtual BOOL OnInitDialog ();
	virtual void PaintMemDC ();

	// Generated message map functions
	//{{AFX_MSG(CTempDialogBar)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMyDialogBarButton	m_btnFavorites;
	CMyDialogBarMenuButton	m_btnFavoritesMenu;
	CTabWnd				m_wndTab;
	CMenu				m_menuFavorites;

	CBCGPToolBarImages	m_Favorites[2];

	CBCGPToolBarImages  m_Sides;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPDIALOGBAR_H__54540DEB_09B5_4C82_8E3A_B1A41B6FF530__INCLUDED_)
