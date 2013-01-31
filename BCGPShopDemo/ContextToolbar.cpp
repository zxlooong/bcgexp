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
#include "stdafx.h"
#include "ContextToolbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CContextToolbar, CBCGPToolBar, 1)

//*******************************************************************************
CContextToolbar::CContextToolbar ()
{
    SetExclusiveRowMode (TRUE);
}
//*******************************************************************************
CContextToolbar::~CContextToolbar () 
{
}
//*******************************************************************************
int CContextToolbar::GetAvailableExpandSize () const 
{
    return m_bExclusiveRow ? 0xFFFF : // unlimited size
        CBCGPToolBar::GetAvailableExpandSize ();
}
//*******************************************************************************
void CContextToolbar::ShowButtons(UINT btnFirstID, UINT btnLastID, BOOL bVisible, BOOL bAutoAdjust)
{
    for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
    {
        CBCGPToolbarButton* pButton = 
            DYNAMIC_DOWNCAST (CBCGPToolbarButton,
            m_Buttons.GetNext (pos));
        if (pButton->m_nID >= btnFirstID && pButton->m_nID <= btnLastID)
        {
            pButton->SetVisible (bVisible);
        }
    }
    if (bAutoAdjust)
    {
        AdjustLayout ();
    }
}
//*******************************************************************************
