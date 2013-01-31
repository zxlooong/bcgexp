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
// BCGPCalendarDemoDoc.h : interface of the CBCGPCalendarDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPCALENDARDEMODOC_H__C2A23383_DAED_4998_9708_4325F1FD3223__INCLUDED_)
#define AFX_BCGPCALENDARDEMODOC_H__C2A23383_DAED_4998_9708_4325F1FD3223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPCalendarDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPCalendarDemoDoc();
	DECLARE_DYNCREATE(CBCGPCalendarDemoDoc)

// Attributes
public:
	void SetDateInterval (const COleDateTime& date1, const COleDateTime& date2);

	COleDateTime GetDate1 () const
	{
		return m_date1;
	}

	COleDateTime GetDate2 () const
	{
		return m_date2;
	}


protected:
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	DWORD			m_dwVersion;

// Operations
public:
	void UpdateCalendar (const CCalendarOptions& options);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPCalendarDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPCalendarDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPCalendarDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCALENDARDEMODOC_H__C2A23383_DAED_4998_9708_4325F1FD3223__INCLUDED_)
