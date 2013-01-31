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
// BCGPDBGridDemoDoc.h : interface of the CBCGPDBGridDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPDBGRIDDEMODOC_H__41BDE36F_29BA_4EF8_A75E_F4DB90E8C46B__INCLUDED_)
#define AFX_BCGPDBGRIDDEMODOC_H__41BDE36F_29BA_4EF8_A75E_F4DB90E8C46B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPDBGridDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPDBGridDemoDoc();
	DECLARE_DYNCREATE(CBCGPDBGridDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPDBGridDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPDBGridDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPDBGridDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPDBGRIDDEMODOC_H__41BDE36F_29BA_4EF8_A75E_F4DB90E8C46B__INCLUDED_)
