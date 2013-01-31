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
// BCGPSkinsDoc.h : interface of the CBCGPSkinsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPSKINSDOC_H__0581DF52_DF99_4A5D_8AF2_B68B132D45ED__INCLUDED_)
#define AFX_BCGPSKINSDOC_H__0581DF52_DF99_4A5D_8AF2_B68B132D45ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPSkinsDoc : public CDocument
{
protected: // create from serialization only
	CBCGPSkinsDoc();
	DECLARE_DYNCREATE(CBCGPSkinsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPSkinsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPSkinsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPSkinsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPSKINSDOC_H__0581DF52_DF99_4A5D_8AF2_B68B132D45ED__INCLUDED_)
