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
// MergeGridItem.cpp: implementation of the MergeGridItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "MergeGridItem.h"
#include "MergeGridCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CMergeGridItem, CBCGPGridItem)

CMergeGridItem::CMergeGridItem ()
{
	m_pImageChart = NULL;
	m_nImage = -1;
	m_bAllowEdit = FALSE;
}
//*****************************************************************************
CMergeGridItem::CMergeGridItem (CBCGPToolBarImages* pImages, int nIdx)
{
	m_pImageChart = pImages;
	m_nImage = nIdx;
	m_bAllowEdit = FALSE;
}
//*****************************************************************************
CMergeGridItem::~CMergeGridItem()
{

}
//*****************************************************************************
void CMergeGridItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);

	if (m_pImageChart != NULL && m_nImage != -1)
	{
		ASSERT_VALID (m_pImageChart);

		CRect rectFill = rect;
		rectFill.top++;

		m_pImageChart->DrawEx (pDC, rectFill, 0,
			CBCGPToolBarImages::ImageAlignHorzStretch, 
			CBCGPToolBarImages::ImageAlignVertStretch);
	}
	else
	{
		CBCGPGridItem::OnDrawValue (pDC, rect);
	}
}
//*****************************************************************************
BOOL CMergeGridItem::OnEdit (LPPOINT)
{
	return FALSE;
}
