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
// BCGPCalendarDemoView.h : interface of the CBCGPCalendarDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPCALENDARDEMOVIEW_H__A4C4F42D_FB57_402E_B33F_2B20898B4E7B__INCLUDED_)
#define AFX_BCGPCALENDARDEMOVIEW_H__A4C4F42D_FB57_402E_B33F_2B20898B4E7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPCalendarDemoView : public CBCGPPlannerManagerView
{
protected: // create from serialization only
	CBCGPCalendarDemoView();
	DECLARE_DYNCREATE(CBCGPCalendarDemoView)

// Attributes
public:
	CBCGPCalendarDemoDoc* GetDocument();

protected:
	COleDateTime			m_LastClickedTime;
	BOOL					m_bFirstTime;

// Operations
public:
	void SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA delta);

	void CreateDemo (BOOL bRedraw = TRUE);
	void UpdateCalendar (const CCalendarOptions& options, BOOL bRedraw = TRUE);

	void CompleteResourceCombo () const;
	void CompleteResourceCombo (CBCGPToolbarComboBoxButton* button) const;

	virtual void Serialize (CArchive& ar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPCalendarDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

	void AddEditAppointment (CBCGPAppointment* pApp, BOOL bAllDay = FALSE, BOOL bNewRecur = FALSE);
	void AddEditResource (BOOL bAdd);

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
	virtual void OnResourceIDChanged ();

// Implementation
public:
	virtual ~CBCGPCalendarDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPCalendarDemoView)
	afx_msg void OnModeDay();
	afx_msg void OnUpdateModeDay(CCmdUI* pCmdUI);
	afx_msg void OnModeMonth();
	afx_msg void OnUpdateModeMonth(CCmdUI* pCmdUI);
	afx_msg void OnModeWeek();
	afx_msg void OnUpdateModeWeek(CCmdUI* pCmdUI);
	afx_msg void OnModeWorkweek();
	afx_msg void OnUpdateModeWorkweek(CCmdUI* pCmdUI);
	afx_msg void OnModeMulti();
	afx_msg void OnUpdateModeMulti(CCmdUI* pCmdUI);
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnResource();
	afx_msg void OnUpdateResource(CCmdUI* pCmdUI);
	afx_msg void OnResourceAdd();
	afx_msg void OnUpdateResourceAdd(CCmdUI* pCmdUI);
	afx_msg void OnResourceRemove();
	afx_msg void OnUpdateResourceRemove(CCmdUI* pCmdUI);
	afx_msg void OnResourceProp();
	afx_msg void OnUpdateResourceProp(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BCGPCalendarDemoView.cpp
inline CBCGPCalendarDemoDoc* CBCGPCalendarDemoView::GetDocument()
   { return (CBCGPCalendarDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCALENDARDEMOVIEW_H__A4C4F42D_FB57_402E_B33F_2B20898B4E7B__INCLUDED_)
