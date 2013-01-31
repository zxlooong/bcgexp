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
// LinkButton.h: interface for the CLinkButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_LINKBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLinkButton : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CLinkButton)

public:
	CLinkButton();
	CLinkButton(LPCTSTR lpszLabel, LPCTSTR lpszURL);

	virtual ~CLinkButton();

	LPCTSTR GetURL () const
	{
		return m_strURL;
	}

protected:
	void Initialize ();
	virtual void CopyFrom (const CBCGPToolbarButton& src);
	virtual void Serialize (CArchive& ar);

	CString	m_strURL;

	virtual BOOL IsEditable () const
	{
		return FALSE;
	}
};

#endif // !defined(AFX_LINKBUTTON_H__9BDC9476_FAE1_11D2_A713_0090274409AC__INCLUDED_)
