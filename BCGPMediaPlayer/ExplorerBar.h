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
// ExplorerBar.h : header file
//

#if !defined(AFX_EXPLORERBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_)
#define AFX_EXPLORERBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExplorerBar

class CExplorerBar : public CBCGPExplorerToolBar
{
	DECLARE_DYNCREATE(CExplorerBar)

// Construction
public:
	CExplorerBar();
	virtual ~CExplorerBar();

	void CreateButtons ();

protected:
	virtual int GetRowHeight () const;
	virtual void OnLoadNavImages ();
	virtual void DrawSeparator (CDC* pDC, const CRect& rect, BOOL bHorz);
	virtual void AdjustLocations ();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExplorerBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLORERBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_)
