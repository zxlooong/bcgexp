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
// MergeGridItem.h: interface for the CMergeGridItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGEGRIDITEM_H__EA3D58C0_EE6C_43CE_BD45_359DC88E9315__INCLUDED_)
#define AFX_MERGEGRIDITEM_H__EA3D58C0_EE6C_43CE_BD45_359DC88E9315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPGridCtrl.h"

class CMergeGridItem : public CBCGPGridItem  
{
	DECLARE_DYNCREATE(CMergeGridItem)

public:
	CMergeGridItem ();
	CMergeGridItem (CBCGPToolBarImages* pImages, int nIdx);
	virtual ~CMergeGridItem();

public:
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual BOOL OnEdit (LPPOINT lptClick);

	void SetImage (CBCGPToolBarImages* pImages, int nIdx)
	{
		m_pImageChart = pImages;
		m_nImage = nIdx;
	}

	int GetImage () const
	{
		return m_nImage;
	}

	CBCGPToolBarImages*	m_pImageChart;
	int					m_nImage;
};

#endif // !defined(AFX_MERGEGRIDITEM_H__EA3D58C0_EE6C_43CE_BD45_359DC88E9315__INCLUDED_)
