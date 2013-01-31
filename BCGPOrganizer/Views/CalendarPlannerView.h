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
#if !defined(AFX_CALENDARPLANNERVIEW_H__46916134_E6BB_48C7_AF87_013A348A646E__INCLUDED_)
#define AFX_CALENDARPLANNERVIEW_H__46916134_E6BB_48C7_AF87_013A348A646E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarPlannerView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarPlannerView view

class CCalendarPlannerView : public CBCGPPlannerManagerView
{
protected: // create from serialization only
	CCalendarPlannerView();
	DECLARE_DYNCREATE(CCalendarPlannerView)

// Attributes
public:
	CBCGPOrganizerDoc* GetDocument();

protected:
	COleDateTime			m_LastClickedTime;
	BOOL					m_bFirstTime;

// Operations
public:
	void SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA delta);

	void CreateDemo (BOOL bRedraw = TRUE);
	void UpdateCalendar (const CPlannerOptions& options, BOOL bRedraw = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarPlannerView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL Load(const CString& strPath, BOOL bStartUp);
	virtual BOOL Save(const CString& strPath);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

	void AddEditAppointment (CBCGPAppointment* pApp, BOOL bAllDay = FALSE, BOOL bNewRecur = FALSE);

	virtual void OnAppointmentAdded (CBCGPAppointment* pApp);
	virtual UINT OnUpdateAppointment (CBCGPAppointment* pApp);
	virtual void OnAppointmentUpdated (CBCGPAppointment* pApp);
	virtual UINT OnRemoveAppointment (CBCGPAppointment* pApp);
	virtual void OnAllAppointmentsRemoved ();
	virtual void OnDblClkCtrl (UINT nFlags, CPoint point);
	virtual void OnKeyDownCtrl(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnTypeChanged (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE oldType,
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE newType);
	virtual void OnDateChanged ();

	virtual void Serialize (CArchive& ar);
	
// Implementation
public:
	virtual ~CCalendarPlannerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCalendarPlannerView)
	afx_msg void OnModeDay();
	afx_msg void OnUpdateModeDay(CCmdUI* pCmdUI);
	afx_msg void OnModeMonth();
	afx_msg void OnUpdateModeMonth(CCmdUI* pCmdUI);
	afx_msg void OnModeWeek();
	afx_msg void OnUpdateModeWeek(CCmdUI* pCmdUI);
	afx_msg void OnModeWorkweek();
	afx_msg void OnUpdateModeWorkweek(CCmdUI* pCmdUI);
	afx_msg void OnTimeLine60();
	afx_msg void OnUpdateTimeLine60(CCmdUI* pCmdUI);
	afx_msg void OnTimeLine30();
	afx_msg void OnUpdateTimeLine30(CCmdUI* pCmdUI);
	afx_msg void OnTimeLine20();
	afx_msg void OnUpdateTimeLine20(CCmdUI* pCmdUI);
	afx_msg void OnTimeLine15();
	afx_msg void OnUpdateTimeLine15(CCmdUI* pCmdUI);	
	afx_msg void OnTimeLine10();
	afx_msg void OnUpdateTimeLine10(CCmdUI* pCmdUI);
	afx_msg void OnTimeLine6();
	afx_msg void OnUpdateTimeLine6(CCmdUI* pCmdUI);
	afx_msg void OnTimeLine5();
	afx_msg void OnUpdateTimeLine5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTimeScale(CCmdUI* pCmdUI);
	afx_msg void OnGotoToday();
	afx_msg void OnUpdateGotoToday(CCmdUI* pCmdUI);
	afx_msg void OnGotoThisday();
	afx_msg void OnUpdateGotoThisday(CCmdUI* pCmdUI);
	afx_msg void OnGotoDay();
	afx_msg void OnUpdateGotoDay(CCmdUI* pCmdUI);
	afx_msg void OnCompressWeekend();
	afx_msg void OnUpdateCompressWeekend(CCmdUI* pCmdUI);
	afx_msg void OnDrawTimeFinish();
	afx_msg void OnUpdateDrawTimeFinish(CCmdUI* pCmdUI);
	afx_msg void OnDrawTimeAsIcons();
	afx_msg void OnUpdateDrawTimeAsIcons(CCmdUI* pCmdUI);
	afx_msg void OnShowToolTip();
	afx_msg void OnUpdateShowToolTip(CCmdUI* pCmdUI);
	afx_msg void OnDrawAppGradient();
	afx_msg void OnUpdateDrawAppGradient(CCmdUI* pCmdUI);
	afx_msg void OnDrawAppRounded();
	afx_msg void OnUpdateDrawAppRounded(CCmdUI* pCmdUI);
	afx_msg void OnDrawAppDuration();
	afx_msg void OnUpdateDrawAppDuration(CCmdUI* pCmdUI);
	afx_msg void OnPlannerOpenApp();
	afx_msg void OnUpdatePlannerOpenApp(CCmdUI* pCmdUI);
	afx_msg void OnPlannerRemoveApp();
	afx_msg void OnUpdatePlannerRemoveApp(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnPlannerNewAppointment();
	afx_msg void OnPlannerNewEvent();
	afx_msg void OnPlannerNewRecAppointment();
	afx_msg void OnPlannerNewRecEvent();
	afx_msg void OnUpdatePlannerNew(CCmdUI* pCmdUI);
	afx_msg void OnDrawBackground();
	afx_msg void OnUpdateDrawBackground(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT OnHighlightRibbonListItem (WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

private:
	void UpdateCaptionText ();

private:
	DWORD m_dwVersion;
};

#ifndef _DEBUG  // debug version in CalendarPlannerView.cpp
inline CBCGPOrganizerDoc* CCalendarPlannerView::GetDocument()
   { return (CBCGPOrganizerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARPLANNERVIEW_H__46916134_E6BB_48C7_AF87_013A348A646E__INCLUDED_)
