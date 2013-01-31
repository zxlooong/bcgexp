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
// LinkButton.h: interface for the CBCGPMSMCategorieBarButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_LINKBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPMSMCategorieBarButton : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CBCGPMSMCategorieBarButton)

public:
	CBCGPMSMCategorieBarButton ();
	CBCGPMSMCategorieBarButton (LPCTSTR lpszLabel, UINT nID);

	virtual ~CBCGPMSMCategorieBarButton ();

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

	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
};

#endif // !defined(AFX_LINKBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_)
