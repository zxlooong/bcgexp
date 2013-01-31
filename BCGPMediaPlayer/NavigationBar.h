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
// NavigationBar.h : header file
//

#if !defined(AFX_NAVIGATIONBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_)
#define AFX_NAVIGATIONBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CNavigationBar

class CNavigationBar : public CBCGPToolBar
{
	friend class CNavigationToolbarButton;

	DECLARE_DYNCREATE(CNavigationBar)

// Construction
public:
	CNavigationBar();
	virtual ~CNavigationBar();

	BOOL Create(CWnd* pParentWnd,
			DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
			UINT nID = AFX_IDW_DIALOGBAR);
	BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = 0,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
		UINT nID = AFX_IDW_DIALOGBAR);

	void CreateButtons ();
	virtual void DWMCompositionChanged ();

	void SetPlay (BOOL bPlay = TRUE)
	{
		if (m_bPlay != bPlay)
		{
			m_bPlay = bPlay;
			InvalidateButton (CommandToIndex (ID_NAVI_PLAY));
		}
	}

	void SetProgress (double progress)
	{
		if (m_dProgress != progress)
		{
			m_dProgress = progress;
			InvalidateProgress ();
		}
	}

	void SetVolume (LONG volume)
	{
		if (m_nVolume != volume)
		{
			m_nVolume = volume;
			InvalidateButton (CommandToIndex (ID_NAVI_SOUND));
		}
	}

protected:
	virtual int GetRowHeight () const;
	virtual void DrawSeparator (CDC* pDC, const CRect& rect, BOOL bHorz);
	virtual void AdjustLayout ();
	virtual void AdjustLocations ();
	virtual void OnFillBackground (CDC* pDC);

	virtual BOOL LoadState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1){return TRUE;}
	virtual BOOL SaveState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1){return TRUE;}

	void InvalidateProgress ();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNavigationBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPToolBarImages		m_PlayH;
	CBCGPControlRenderer	m_Progress;
	CBCGPToolBarImages		m_ProgressR;

	BOOL					m_bPlay;
	double					m_dProgress;
	LONG					m_nVolume;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVIGATIONBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_)
