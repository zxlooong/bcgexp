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

#pragma once


// CShopTabWnd

class CShopTabWnd : public CBCGPTabWnd
{
	DECLARE_DYNCREATE(CShopTabWnd)
protected:
    const int m_nTabMenuSpace;
    BOOL  m_bDisableDrawing;

public:
	CShopTabWnd();
	virtual ~CShopTabWnd();

    virtual void RecalcLayout ();
    virtual void AdjustTabs ();

    virtual BOOL IsPtInMenuArea(const CPoint& point) const;

protected:
	DECLARE_MESSAGE_MAP()

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);


};


