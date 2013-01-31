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
// BCGPMSMCaptionBarButton.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSMCaptionBarButton.h"

#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCaptionBarButton

IMPLEMENT_DYNCREATE(CBCGPMSMCaptionBarButton, CBCGPButton);

CBCGPMSMCaptionBarButton::CBCGPMSMCaptionBarButton ()
{
	m_bDrawFocus = FALSE;
}

CBCGPMSMCaptionBarButton::~CBCGPMSMCaptionBarButton ()
{
}

void CBCGPMSMCaptionBarButton::OnDraw (CDC* pDC, const CRect& /*rect*/, UINT /*uiState*/)
{
	CBCGPMSMVisualManager* pManager = DYNAMIC_DOWNCAST (CBCGPMSMVisualManager,
		CBCGPVisualManager::GetInstance ());

	long nID = GetSysCommand ();

	if (pManager == NULL || nID == 0)
	{
		ASSERT (FALSE);
	}
	else
	{
		CRect rt;
		GetClientRect(rt);

		CBCGPVisualManager::BCGBUTTON_STATE state = 
			CBCGPVisualManager::ButtonsIsRegular;

		if (m_bPushed)
		{
			state = CBCGPVisualManager::ButtonsIsPressed;
		}
		else if (m_bHighlighted)
		{
			state = CBCGPVisualManager::ButtonsIsHighlighted;
		}

		pManager->BCGPMSMDrawCaptionButton (pDC, rt, state, nID);
	}
}

UINT CBCGPMSMCaptionBarButton::GetSysCommand () const
{
    HWND hWnd = GetSafeHwnd();

    ASSERT(hWnd != NULL);

    if (hWnd != NULL)
    {
        return ::GetWindowLong (hWnd, GWL_ID);
    }

    return 0;
}

void CBCGPMSMCaptionBarButton::SetSysCommand (UINT uiSysCommand)
{
	HWND hWnd = GetSafeHwnd();

	ASSERT(hWnd != NULL);

	if (GetSysCommand () != uiSysCommand && hWnd != NULL)
	{
		::SetWindowLong (hWnd, GWL_ID, uiSysCommand);
	}
}

BEGIN_MESSAGE_MAP(CBCGPMSMCaptionBarButton, CBCGPButton)
	//{{AFX_MSG_MAP(CBCGPMSMCaptionBarButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCaptionBarButton message handlers
