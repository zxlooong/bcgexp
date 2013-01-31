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
// BCGPIE7DemoDoc.h : interface of the CBCGPIE7DemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPIE7DEMODOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_BCGPIE7DEMODOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ID_HISTORY_FIRST	0x1000
#define HISTORY_LEN	10

#include "HistoryObj.h"

typedef CList<CHistoryObj*, CHistoryObj*> _T_HistotyList;

class CBCGPIE7DemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPIE7DemoDoc();
	DECLARE_DYNCREATE(CBCGPIE7DemoDoc)

// Attributes
public:
	CArray<CHistoryObj*, CHistoryObj*>	m_arHistory;
	int	m_iHistoryOffset;

// Operations
public:
	void GetBackList (_T_HistotyList& lst) const;
	void GetFrwdList (_T_HistotyList& lst) const;

	BOOL IsBackAvailable () const
	{
		return m_iHistoryOffset < m_arHistory.GetSize () - 1;
	}

	BOOL IsFrwdAvailable ()
	{
		return m_iHistoryOffset > 0;
	}

	CHistoryObj* GoBack ()
	{
		if (m_iHistoryOffset >= m_arHistory.GetSize ())
		{
			ASSERT (FALSE);
			return NULL;
		}

		return m_arHistory [++ m_iHistoryOffset];
	}

	CHistoryObj* GoForward ()
	{
		if (m_iHistoryOffset < 1)
		{
			ASSERT (FALSE);
			return NULL;
		}

		return m_arHistory [--m_iHistoryOffset];
	}

	CHistoryObj* Go (UINT uiCmd);
	CHistoryObj* AddURLToHistory (const CString& strTitle, const CString& strURL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPIE7DemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPIE7DemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPIE7DemoDoc)
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPIE7DEMODOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_)
