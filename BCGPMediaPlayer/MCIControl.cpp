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
// MCIControl.cpp: implementation of the CMCIControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "MCIControl.h"
#include "windowsx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMCIControl::CMCIControl()
	: m_hwndMCI (NULL)
{

}

CMCIControl::~CMCIControl()
{
	Close ();
}

BOOL CMCIControl::Create (HWND hwndParent/* = NULL*/)
{
	if (m_hwndMCI != NULL)
	{
		return TRUE;
	}

	if (hwndParent == NULL)
	{
		hwndParent = AfxGetMainWnd ()->GetSafeHwnd ();
	}

	m_hwndMCI = MCIWndCreate (hwndParent, AfxGetInstanceHandle(), WS_CHILD | WS_VISIBLE |
		MCIWNDF_NOMENU | MCIWNDF_NOPLAYBAR | MCIWNDF_NOTIFYMODE | MCIWNDF_NOTIFYSIZE, NULL);
	if (m_hwndMCI != NULL)
	{
		::SetClassLongPtr (m_hwndMCI, GCLP_HBRBACKGROUND, (LONG_PTR)::GetStockObject (BLACK_BRUSH));
	}	

	return m_hwndMCI != NULL;
}

BOOL CMCIControl::Open (const CString& strPath, BOOL bPlay/* = TRUE*/)
{
	if (m_hwndMCI == NULL)
	{
		return FALSE;
	}

	if (strPath.IsEmpty ())
	{
		return FALSE;
	}

	Stop ();

	if (MCIWndOpen (m_hwndMCI, (LPCTSTR) strPath, 0) == 0)
	{
		MCIWndHome (m_hwndMCI);
		if (bPlay)
		{
			return Play ();
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CMCIControl::Close ()
{
	Stop ();

	if (m_hwndMCI != NULL)
	{
		MCIWndClose (m_hwndMCI);
	}

	m_hwndMCI = NULL;

	return TRUE;
}

LONG CMCIControl::GetMode ()
{
	if (m_hwndMCI == NULL)
	{
		return MCI_MODE_NOT_READY;
	}

	return MCIWndGetMode (m_hwndMCI, NULL, 0);
}

BOOL CMCIControl::Stop ()
{
	if (m_hwndMCI != NULL)
	{
		LONG mode = GetMode ();

		if (mode == MCI_MODE_PLAY || mode == MCI_MODE_PAUSE)
		{
			if (MCIWndStop (m_hwndMCI) == 0)
			{
				MCIWndHome (m_hwndMCI);
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CMCIControl::Pause ()
{
	if (m_hwndMCI != NULL && GetMode () == MCI_MODE_PLAY)
	{
		return MCIWndPause (m_hwndMCI) == 0;
	}

	return FALSE;
}

BOOL CMCIControl::Play ()
{
	if (m_hwndMCI != NULL)
	{
		LONG mode = GetMode ();

		if (mode == MCI_MODE_PAUSE)
		{
			return MCIWndResume (m_hwndMCI) == 0;
		}
		else if (mode == MCI_MODE_STOP)
		{
			return MCIWndPlay (m_hwndMCI) == 0;
		}
	}	

	return FALSE;
}

LONG CMCIControl::GetLength ()
{
	LONG lRes = 0;

	if (m_hwndMCI != NULL)
	{
		lRes = MCIWndGetLength (m_hwndMCI);
	}

	return lRes;
}

LONG CMCIControl::GetPosition ()
{
	LONG lRes = 0;

	if (m_hwndMCI != NULL)
	{
		lRes = MCIWndGetPosition (m_hwndMCI);
	}

	return lRes;
}

double CMCIControl::GetPositionPerc ()
{
	LONG length = GetLength ();
	if (length == 0)
	{
		return -1;
	}

	LONG mode = GetMode ();

	if (mode != MCI_MODE_PLAY && mode != MCI_MODE_PAUSE)
	{
		return -1;
	}

	return GetPosition () * 100.0 / (double)length;
}

LONG CMCIControl::GetVolume ()
{
	LONG lRes = 0;

	if (m_hwndMCI != NULL)
	{
		lRes = MCIWndGetVolume (m_hwndMCI);
	}

	return lRes;
}

double CMCIControl::GetVolumePerc ()
{
	if (m_hwndMCI == NULL)
	{
		return -1;
	}

	return GetVolume () / 10.0;
}

BOOL CMCIControl::SetVolume (LONG value)
{
	if (m_hwndMCI != NULL)
	{
		value = min (max (value, 0), 1000);
		return MCIWndSetVolume (m_hwndMCI, value) == 0;
	}

	return FALSE;
}

BOOL CMCIControl::SetVolumePerc (double value)
{
	return SetVolume ((LONG)(value * 10.0));
}

LONG CMCIControl::GetActiveTimer ()
{
	if (m_hwndMCI != NULL)
	{
		return MCIWndGetActiveTimer (m_hwndMCI);
	}

	return -1;
}

void CMCIControl::AdjustSize ()
{
	if (m_hwndMCI == NULL)
	{
		return;
	}

	CRect rectSrc;
	MCIWndGetSource(m_hwndMCI, &rectSrc);

	if (rectSrc.IsRectNull ())
	{
		if (::IsWindowVisible (m_hwndMCI))
		{
			::ShowWindow (m_hwndMCI, SW_HIDE);
		}
		return;
	}

	if (!::IsWindowVisible (m_hwndMCI))
	{
		::ShowWindow (m_hwndMCI, SW_SHOW);
	}

	CRect rectClient;
	::GetClientRect (m_hwndMCI, &rectClient);

    double zoom = min ((double)rectClient.Width () / (double)rectSrc.Width (), 
		(double)rectClient.Height () / (double)rectSrc.Height ());

	CRect rectDst (rectClient);
	rectDst.right  = (long)(rectSrc.Width () * zoom);
	rectDst.bottom = (long)(rectSrc.Height () * zoom);

	rectDst.OffsetRect ((rectClient.Width () - rectDst.Width ()) / 2,
		(rectClient.Height () - rectDst.Height ()) / 2);

	MCIWndPutDest(m_hwndMCI, &rectDst);
}
