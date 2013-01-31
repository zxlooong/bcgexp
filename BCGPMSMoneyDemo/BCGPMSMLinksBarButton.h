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
// LinkButton.h: interface for the CBCGPMSMLinksBarButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPMSMLINKSBARBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_BCGPMSMLINKSBARBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPMSMLinksBarButton : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CBCGPMSMLinksBarButton)

public:
	CBCGPMSMLinksBarButton ();
	CBCGPMSMLinksBarButton (LPCTSTR lpszLabel, UINT nID);

	virtual ~CBCGPMSMLinksBarButton ();

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages,
					 BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
					 BOOL bHighlight = FALSE,
					 BOOL bDrawBorder = TRUE,
					 BOOL bGrayDisabledButtons = TRUE);

protected:
	void Initialize ();

	virtual BOOL IsEditable () const
				 {
					 return FALSE;
				 }

	virtual SIZE OnCalculateSize (
					 CDC* pDC,
					 const CSize& sizeDefault,
					 BOOL bHorz);
};

#endif // !defined(AFX_BCGPMSMLINKSBARBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_)
