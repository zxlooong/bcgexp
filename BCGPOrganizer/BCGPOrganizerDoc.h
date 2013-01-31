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
// BCGPOrganizerDoc.h : interface of the CBCGPOrganizerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPORGANIZERDOC_H__A48CA9BC_BEDC_499A_9148_D1861ABCF3A9__INCLUDED_)
#define AFX_BCGPORGANIZERDOC_H__A48CA9BC_BEDC_499A_9148_D1861ABCF3A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPlannerOptions;

class CBCGPOrganizerDoc : public CDocument
{
public:
	enum XMode
	{
		e_ModeUndefined	= -1,
		e_ModeShortcuts = 0,
		e_ModeMail		= 1,
		e_ModeCalendar	= 2,
		e_ModeTasks     = 3,
		e_ModeMacros	= 4,
		e_ModeGantt		= 5
	};

protected: // create from serialization only
	CBCGPOrganizerDoc();
	DECLARE_DYNCREATE(CBCGPOrganizerDoc)

// Attributes
public:
    void            SetMode(XMode mode);
    XMode           GetMode() const;

    BOOL            CreateViews(CBCGPFrameWnd* pFrameWnd, CCreateContext* pContext);
    CView*          GetView(XMode mode);

	void LoadMacros(UINT nID, CString strName);

	void SetDateInterval (const COleDateTime& date1, const COleDateTime& date2);

	COleDateTime GetDate1 () const
	{
		return m_date1;
	}

	COleDateTime GetDate2 () const
	{
		return m_date2;
	}

// Operations
public:
	void UpdateCalendar (const CPlannerOptions& options);
	void UpdateGantt (const CGanttOptions& options);
	void UpdateZoom (int index = -1);
	const CString& GetPath () const
	{
		return m_strPath;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPOrganizerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetModifiedFlag(BOOL bModified = TRUE);
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPOrganizerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPOrganizerDoc)
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL                    m_bCalendarModified;
	CString					m_strPath;

	COleDateTime			m_date1;
	COleDateTime			m_date2;
    XMode					m_Mode;

	CView*					m_pViews[c_ViewCount];
};

/////////////////////////////////////////////////////////////////////////////

inline CBCGPOrganizerDoc::XMode CBCGPOrganizerDoc::GetMode() const
{
    return m_Mode;
}


inline CView* CBCGPOrganizerDoc::GetView(CBCGPOrganizerDoc::XMode mode)
{
	CView* pView = NULL;

	if (mode != e_ModeUndefined)
	{
		pView = m_pViews[mode];
	}

    ASSERT_VALID(pView);

    return pView;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPORGANIZERDOC_H__A48CA9BC_BEDC_499A_9148_D1861ABCF3A9__INCLUDED_)
