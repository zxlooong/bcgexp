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
// BCGPGanttDemoDoc.h : interface of the CBCGPGanttDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPCHARTEXAMPLEDOC_H__4718123B_54FB_463B_AF7D_20FCA6FE7985__INCLUDED_)
#define AFX_BCGPCHARTEXAMPLEDOC_H__4718123B_54FB_463B_AF7D_20FCA6FE7985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPGanttDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPGanttDemoDoc();
	DECLARE_DYNCREATE(CBCGPGanttDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPGanttDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPGanttDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPGanttDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCHARTEXAMPLEDOC_H__4718123B_54FB_463B_AF7D_20FCA6FE7985__INCLUDED_)
