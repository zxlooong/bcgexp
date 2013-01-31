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
// BCGPVisualStudioGUIDemoDoc.h : interface of the CBCGPVisualStudioGUIDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGCBDOTNETEXAMPLEDOC_H__1260A711_4153_43F3_ADAF_952FAD30AC46__INCLUDED_)
#define AFX_BCGCBDOTNETEXAMPLEDOC_H__1260A711_4153_43F3_ADAF_952FAD30AC46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPVisualStudioGUIDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPVisualStudioGUIDemoDoc();
	DECLARE_DYNCREATE(CBCGPVisualStudioGUIDemoDoc)

// Attributes
public:
	UINT	m_uiExampleID;
	UINT	m_uiExampleXMLSettingsID;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPVisualStudioGUIDemoDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL
	
// Implementation
public:
	void CheckTitle();

	virtual ~CBCGPVisualStudioGUIDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL	m_bTitleMark;

	void CommonInit ();

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPVisualStudioGUIDemoDoc)
	afx_msg void OnDummyBuild();
	afx_msg void OnDummyCompile();
	afx_msg void OnDummyExecute();
	afx_msg void OnDummyGo();
	afx_msg void OnDummySelectActiveConfiguration();
	afx_msg void OnDummyClean();
	afx_msg void OnDummyRebuildAll();
	afx_msg void OnToolsMacro();
	afx_msg void OnNewDialog();
	afx_msg void OnNewAccelerator();
	afx_msg void OnNewBitmap();
	afx_msg void OnNewCursor();
	afx_msg void OnNewIcon();
	afx_msg void OnNewMenu();
	afx_msg void OnNewStringTable();
	afx_msg void OnNewToolbar();
	afx_msg void OnNewVersion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCBDOTNETEXAMPLEDOC_H__1260A711_4153_43F3_ADAF_952FAD30AC46__INCLUDED_)
