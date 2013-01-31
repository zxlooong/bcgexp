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
// MergeGridCtrl.h : header file
//

#if !defined(AFX_MERGEGRIDCTRL_H__56170B45_D9F3_4EA8_A6B5_C53C2308F22C__INCLUDED_)
#define AFX_MERGEGRIDCTRL_H__56170B45_D9F3_4EA8_A6B5_C53C2308F22C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPGridCtrl.h"
#include "MergeGridItem.h"

/////////////////////////////////////////////////////////////////////////////
// CMergeGridCtrl

class CMergeGridCtrl : public CBCGPGridCtrl
{
	DECLARE_DYNCREATE(CMergeGridCtrl)
	
// Construction
public:
	CMergeGridCtrl();
	virtual ~CMergeGridCtrl();

public:
	BOOL ReplaceItem (CBCGPGridItemID id, CBCGPGridItem *pNewItem);
	virtual CBCGPGridItem* CreateItem (int nRow, int nColumn);
	virtual BOOL CanMergeRange (const CBCGPGridRange& /*range*/, BOOL /*bMerge*/);

protected:
	virtual BOOL OnTrackHeader ()
	{
		return FALSE; // do not resize columns inside client area by mouse, only at header
	}

	// Generated message map functions
protected:
	//{{AFX_MSG(CMergeGridCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPToolBarImages	m_ImageChart;
	CBCGPGridRange		m_rangeChart;		// range boundaries
	BOOL		m_bProtectRangeChart;
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_MERGEGRIDCTRL_H__56170B45_D9F3_4EA8_A6B5_C53C2308F22C__INCLUDED_)
