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
// BCGPShopDemoDoc.h : interface of the CBCGPShopDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPSHOPDEMODOC_H__A7F8E10D_B90A_42F1_BE21_2B964895F844__INCLUDED_)
#define AFX_BCGPSHOPDEMODOC_H__A7F8E10D_B90A_42F1_BE21_2B964895F844__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPShopDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPShopDemoDoc();
	DECLARE_DYNCREATE(CBCGPShopDemoDoc)

// Attributes
public:
    CSize GetSize() const { return m_szDocSize; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPShopDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPShopDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPShopDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CSize m_szDocSize;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPSHOPDEMODOC_H__A7F8E10D_B90A_42F1_BE21_2B964895F844__INCLUDED_)
