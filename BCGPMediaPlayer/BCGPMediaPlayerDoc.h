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
// BCGPMediaPlayerDoc.h : interface of the CBCGPMediaPlayerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPMEDIAPLAYERDOC_H__5BE431BD_93C6_4ED1_A05A_91701007BE19__INCLUDED_)
#define AFX_BCGPMEDIAPLAYERDOC_H__5BE431BD_93C6_4ED1_A05A_91701007BE19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MCIControl.h"

class CBCGPMediaPlayerDoc : public CDocument
{
protected: // create from serialization only
	CBCGPMediaPlayerDoc();
	DECLARE_DYNCREATE(CBCGPMediaPlayerDoc)

// Attributes
public:
	inline CMCIControl& GetMCIControl ()
	{
		return m_MCIControl;
	}
	CString GetFileName () const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMediaPlayerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPMediaPlayerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMediaPlayerDoc)
	afx_msg void OnNaviStop();
	afx_msg void OnUpdateNaviStop(CCmdUI* pCmdUI);
	afx_msg void OnNaviPlay();
	afx_msg void OnUpdateNaviPlay(CCmdUI* pCmdUI);
	afx_msg void OnNaviPrev();
	afx_msg void OnUpdateNaviPrev(CCmdUI* pCmdUI);
	afx_msg void OnNaviNext();
	afx_msg void OnUpdateNaviNext(CCmdUI* pCmdUI);
	afx_msg void OnNaviSound();
	afx_msg void OnUpdateDefault(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	enum XNavi
	{
		e_NaviNone = 0,
		e_NaviPrev = 1,
		e_NaviNext = 2
	};

private:
	CMCIControl	m_MCIControl;
	LONG		m_nVolume;

	XNavi		m_Navi;
	CStringList	m_Prev;
	CStringList	m_Next;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMEDIAPLAYERDOC_H__5BE431BD_93C6_4ED1_A05A_91701007BE19__INCLUDED_)
