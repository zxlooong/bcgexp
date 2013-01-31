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
// BCGPGridExampleDoc.h : interface of the CBCGPGridExampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPGRIDEXAMPLEDOC_H__50861CE4_440C_4E7A_9928_D3D6DDED3A6F__INCLUDED_)
#define AFX_BCGPGRIDEXAMPLEDOC_H__50861CE4_440C_4E7A_9928_D3D6DDED3A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPGridExampleDoc : public CDocument
{
protected: // create from serialization only
	CBCGPGridExampleDoc();
	DECLARE_DYNCREATE(CBCGPGridExampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPGridExampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPGridExampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPGridExampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPGRIDEXAMPLEDOC_H__50861CE4_440C_4E7A_9928_D3D6DDED3A6F__INCLUDED_)
