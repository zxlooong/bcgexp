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
// CntrItem.cpp : implementation of the CBCGPMSOffice2007DemoCntrItem class
//

#include "stdafx.h"
#include "BCGPMSOffice2007Demo.h"

#include "BCGPMSOffice2007DemoDoc.h"
#include "BCGPMSOffice2007DemoView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoCntrItem implementation

IMPLEMENT_SERIAL(CBCGPMSOffice2007DemoCntrItem, CRichEditCntrItem, 0)

CBCGPMSOffice2007DemoCntrItem::CBCGPMSOffice2007DemoCntrItem(REOBJECT* preo, CBCGPMSOffice2007DemoDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	m_uiCategoryID = 0;
}

CBCGPMSOffice2007DemoCntrItem::~CBCGPMSOffice2007DemoCntrItem()
{
	// TODO: add cleanup code here
	
}

BOOL CBCGPMSOffice2007DemoCntrItem::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow)
{
	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, pFrameWnd);
	if (pMainFrame != NULL)
	{
		return pMainFrame->OnShowControlBars (bShow);
	}
	else	// Maybe, SDI frame...
	{
		CBCGPFrameWnd* pFrame = DYNAMIC_DOWNCAST (CBCGPFrameWnd, pFrameWnd);
		if (pFrame != NULL)
		{
			return pFrame->OnShowControlBars (bShow);
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoCntrItem diagnostics

#ifdef _DEBUG
void CBCGPMSOffice2007DemoCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CBCGPMSOffice2007DemoCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
