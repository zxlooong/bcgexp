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
#if !defined(AFX_BCGPMSMCAPTIONBARBUTTON_H__527419D9_A4DF_4B82_9755_EDAF964D781C__INCLUDED_)
#define AFX_BCGPMSMCAPTIONBARBUTTON_H__527419D9_A4DF_4B82_9755_EDAF964D781C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMCaptionBarButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCaptionBarButton window

class CBCGPMSMCaptionBarButton : public CBCGPButton
{
	DECLARE_DYNCREATE(CBCGPMSMCaptionBarButton);

public:
	CBCGPMSMCaptionBarButton ();

	virtual ~CBCGPMSMCaptionBarButton ();

	UINT GetSysCommand () const;

	void SetSysCommand (UINT uiSysCommand);

protected:
	virtual void OnDraw (CDC* pDC, const CRect& rect, UINT uiState);

protected:

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMCAPTIONBARBUTTON_H__527419D9_A4DF_4B82_9755_EDAF964D781C__INCLUDED_)
