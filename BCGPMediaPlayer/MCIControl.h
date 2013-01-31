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
// MCIControl.h: interface for the CMCIControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MCICONTROL_H__4DB0E3A2_5261_41BF_AFE1_100CDB7408ED__INCLUDED_)
#define AFX_MCICONTROL_H__4DB0E3A2_5261_41BF_AFE1_100CDB7408ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMCIControl  
{
public:
	CMCIControl();
	virtual ~CMCIControl();

	BOOL Create (HWND hwndParent = NULL);
	BOOL Open (const CString& strPath, BOOL bPlay = TRUE);
	BOOL Play ();
	BOOL Pause ();
	BOOL Stop ();
	BOOL Close ();

	LONG GetMode ();
	
	LONG GetLength ();
	LONG GetPosition ();
	double GetPositionPerc ();

	LONG GetVolume ();
	double GetVolumePerc ();
	BOOL SetVolume (LONG value);
	BOOL SetVolumePerc (double value);
	
	LONG GetActiveTimer ();

	inline HWND GetSafeHwnd ()
	{
		return this == NULL ? NULL : m_hwndMCI;
	}

	void AdjustSize ();

private:
	HWND	m_hwndMCI;
};

#endif // !defined(AFX_MCICONTROL_H__4DB0E3A2_5261_41BF_AFE1_100CDB7408ED__INCLUDED_)
