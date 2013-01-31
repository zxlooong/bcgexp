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
// BCGPMSOffice2007DemoDoc.h : interface of the CBCGPMSOffice2007DemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPMSOFFICE2007DEMODOC_H__8F91944C_DA02_4C09_A6C8_6F7C572B9E37__INCLUDED_)
#define AFX_BCGPMSOFFICE2007DEMODOC_H__8F91944C_DA02_4C09_A6C8_6F7C572B9E37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPMSOffice2007DemoDoc : public CRichEditDoc
{
protected: // create from serialization only
	CBCGPMSOffice2007DemoDoc();
	DECLARE_DYNCREATE(CBCGPMSOffice2007DemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSOffice2007DemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CBCGPMSOffice2007DemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMSOffice2007DemoDoc)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSOFFICE2007DEMODOC_H__8F91944C_DA02_4C09_A6C8_6F7C572B9E37__INCLUDED_)
