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
// BCGPGanttDemoView.cpp : implementation of the CBCGPGanttDemoView class
//

#include "stdafx.h"
#include "BCGPGanttDemo.h"

#include "BCGPGanttDemoDoc.h"
#include "BCGPGanttDemoView.h"
#include "GanttDlg.h"
#include "GotoDayDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CProgressItem : public CBCGPGridPercentItem
{
	DECLARE_DYNCREATE(CProgressItem)

protected:
    CProgressItem ()
	{
		m_nMinValue = 0;
		m_nMaxValue = 100;
		m_dwFlags |= BCGP_GRID_ITEM_HAS_SPIN;
	};

public:
    CProgressItem (double value, DWORD_PTR dwData = 0)
		: CBCGPGridPercentItem (value, dwData)
	{
		m_nMinValue = 0;
		m_nMaxValue = 100;
		m_dwFlags |= BCGP_GRID_ITEM_HAS_SPIN;
	}

protected:
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
	{
		CWnd* pWnd = CBCGPGridPercentItem::CreateInPlaceEdit (rectEdit, bDefaultFormat);
		if (pWnd != NULL)
		{
			bDefaultFormat = FALSE;
		}

		return pWnd;
	}
	virtual BOOL OnEdit (LPPOINT lptClick)
	{
		if (CBCGPGridPercentItem::OnEdit (lptClick))
		{
			CString strText;
			strText.Format (_T("%d"), (long)((double)m_varValue * 100.0 + 0.5));
			m_pWndInPlace->SetWindowText (strText);

			return TRUE;
		}

		return FALSE;
	}
	virtual CString FormatItem ()
	{
		CString strText;
		strText.Format (_T("%d%%"), (long)((double)m_varValue * 100.0 + 0.5));

		return strText;
	}

	virtual void OnDrawValue (CDC* pDC, CRect rect);
};

IMPLEMENT_DYNCREATE(CProgressItem, CBCGPGridPercentItem)

void CProgressItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);
	
	COLORREF clrTextOld = (COLORREF)-1;
	COLORREF clrText = OnFillBackground (pDC, rect);

	if (m_pWndInPlace != NULL)
	{
		return;
	}

	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	rect.DeflateRect (TEXT_MARGIN, 2);

	CString strText (GetLabel ());
	CSize szText = pDC->GetTextExtent (_T("100%"));

	pDC->DrawText (strText, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

	CRect rectProgress = rect;
	rectProgress.left += szText.cx + TEXT_MARGIN;
	rectProgress.top += max (0, (rectProgress.Height () - szText.cy) / 2);
	rectProgress.bottom	= min (rectProgress.bottom, rectProgress.top + szText.cy);

	if (rectProgress.Width () > 0 &&
		rectProgress.Width () > rectProgress.Height ())
	{
		long nProgressCurr = (long)((double)m_varValue * 100.0 + 0.5);

		CRect rectComplete = rectProgress;

		rectComplete.right = rectComplete.left + 
			nProgressCurr * rectComplete.Width () / 100;

		CBCGPRibbonProgressBar dummy;
		CBCGPVisualManager::GetInstance ()->OnDrawRibbonProgressBar (
				pDC, &dummy, rectProgress, rectComplete, FALSE);
	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}

	m_bValueIsTrancated = pDC->GetTextExtent (strText).cx > rect.Width ();
}


/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoView

IMPLEMENT_DYNCREATE(CBCGPGanttDemoView, CBCGPGanttView)

BEGIN_MESSAGE_MAP(CBCGPGanttDemoView, CBCGPGanttView)
	//{{AFX_MSG_MAP(CBCGPGanttDemoView)
    ON_COMMAND(ID_GANTT_LINK, OnGanttLinkItems)
    ON_UPDATE_COMMAND_UI(ID_GANTT_LINK, OnUpdateGanttLinkItems)
    ON_COMMAND(ID_GANTT_UNLINK, OnGanttUnlinkItems)
    ON_UPDATE_COMMAND_UI(ID_GANTT_UNLINK, OnUpdateGanttUnlinkItems)
	ON_COMMAND(ID_GANTT_ZOOM_IN, OnGanttZoomIn)
	ON_UPDATE_COMMAND_UI(ID_GANTT_ZOOM_IN, OnUpdateGanttZoomIn)
	ON_COMMAND(ID_GANTT_ZOOM_OUT, OnGanttZoomOut)
	ON_UPDATE_COMMAND_UI(ID_GANTT_ZOOM_OUT, OnUpdateGanttZoomOut)
	ON_COMMAND(ID_GANTT_NEW, OnGanttNewTask)
	ON_UPDATE_COMMAND_UI(ID_GANTT_NEW, OnUpdateGanttNew)
	ON_COMMAND(ID_GANTT_NEW_TASK, OnGanttNewTask)
	ON_UPDATE_COMMAND_UI(ID_GANTT_NEW_TASK, OnUpdateGanttNew)
	ON_COMMAND(ID_GANTT_NEW_MILESTONE, OnGanttNewMilestone)
	ON_UPDATE_COMMAND_UI(ID_GANTT_NEW_MILESTONE, OnUpdateGanttNew)
	ON_COMMAND(ID_GANTT_OPEN_TASK, OnGanttOpenItem)
	ON_UPDATE_COMMAND_UI(ID_GANTT_OPEN_TASK, OnUpdateGanttOpenItem)
	ON_COMMAND(ID_GANTT_REMOVE_TASK, OnGanttRemoveItem)
	ON_UPDATE_COMMAND_UI(ID_GANTT_REMOVE_TASK, OnUpdateGanttRemoveItem)
	ON_COMMAND(ID_GANTT_MARK_COMPLETE, OnMarkComplete)
	ON_UPDATE_COMMAND_UI(ID_GANTT_MARK_COMPLETE, OnUpdateMarkComplete)
	ON_COMMAND(ID_GANTT_GOTO_TODAY, OnGotoToday)
	ON_COMMAND(ID_GANTT_GOTO_DAY, OnGotoDay)
    ON_WM_CONTEXTMENU()
    ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CBCGPGanttView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPGanttView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoView construction/destruction

CBCGPGanttDemoView::CBCGPGanttDemoView()
	: m_bFirstTime (TRUE)
{
}

CBCGPGanttDemoView::~CBCGPGanttDemoView()
{
}

BOOL CBCGPGanttDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPGanttView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoView drawing

void CBCGPGanttDemoView::OnDraw(CDC* /*pDC*/)
{
}

void CBCGPGanttDemoView::OnInitialUpdate()
{
	CBCGPGanttView::OnInitialUpdate();

	GetControl ().SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;
		CreateDemo (TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoView printing

void CBCGPGanttDemoView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CBCGPGanttDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBCGPGanttDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGanttView::OnBeginPrinting (pDC, pInfo);
}

void CBCGPGanttDemoView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGanttView::OnEndPrinting (pDC, pInfo);
}

void CBCGPGanttDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);

	// Page margins:
	double dLeftOffset = 0.5;
	double dTopOffset = 0.5;
	double dRightOffset = 0.5;
	double dBottomOffset = 0.5;
	pInfo->m_rectDraw.DeflateRect(
		(int)(pDC->GetDeviceCaps(LOGPIXELSX) * dLeftOffset),
		(int)(pDC->GetDeviceCaps(LOGPIXELSY) * dTopOffset),
		(int)(pDC->GetDeviceCaps(LOGPIXELSX) * dRightOffset),
		(int)(pDC->GetDeviceCaps(LOGPIXELSY) * dBottomOffset));
	
	CBCGPGanttView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoView diagnostics

#ifdef _DEBUG
void CBCGPGanttDemoView::AssertValid() const
{
	CBCGPGanttView::AssertValid();
}

void CBCGPGanttDemoView::Dump(CDumpContext& dc) const
{
	CBCGPGanttView::Dump(dc);
}

CBCGPGanttDemoDoc* CBCGPGanttDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPGanttDemoDoc)));
	return (CBCGPGanttDemoDoc*)m_pDocument;
}
#endif //_DEBUG

void CBCGPGanttDemoView::GetSelectedItems (CArray <CBCGPGanttItem*, CBCGPGanttItem*>& arrSelected) const
{
    arrSelected.RemoveAll ();

    const CBCGPGanttChart* pChart = GetChart ();
    if (pChart == NULL)
    {
        return;
    }

    ASSERT_VALID (pChart);
    pChart->GetSelectedItems (arrSelected);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoView message handlers

void CBCGPGanttDemoView::OnContextMenu(CWnd*, CPoint point)
{
	UINT nID = 0;

	CPoint pt (point);

	CRect rect;
	GetChart ()->GetWindowRect (rect);

	if (rect.PtInRect (pt))
	{
		nID = IDR_GANTT_CLIENT;

		GetChart ()->ScreenToClient (&pt);
		if (GetChart ()->ItemFromPoint (pt) != NULL)
		{
			nID = IDR_GANTT_TASK;
		}
	}

	if (nID != 0)
	{
#ifndef _BCGPGANTT_STANDALONE
		theApp.ShowPopupMenu (nID, point, this);
#else
		CMenu menu;
		menu.LoadMenu (nID);

		CMenu* pPopupMenu = menu.GetSubMenu (0);
		pPopupMenu->TrackPopupMenu (0, point.x, point.y, this);
#endif
	}
}

void CBCGPGanttDemoView::CreateDemo (BOOL /*bRedraw*/)
{
	GetControl ().SetRedraw (FALSE); // start updating grid and chart

    CBCGPGanttChart* pChart = GetChart ();
    ASSERT_VALID (pChart);

    CBCGPGanttControl& control = GetControl ();

    // Setup grid columns

    CBCGPGanttGrid* pGrid = GetGrid ();
    int iCol = 0;

    pGrid->InsertColumn (iCol, _T("Task Name"), 100);
    control.SetNameColumnIndex (iCol++);

    pGrid->InsertColumn (iCol, _T("Start"), 72);
    control.SetStartDateColumnIndex (iCol++);

    pGrid->InsertColumn (iCol, _T("Finish"), 72);
    control.SetFinishDateColumnIndex (iCol++);

    pGrid->InsertColumn (iCol, _T("Progress"), 60);
    control.SetProgressColumnIndex (iCol++);

    // Fill data

    const int c_arrItems [11][5] =
    {
        // is_group, level, begin, end, complete
          { FALSE,    0,      3,    4,    32 },
          { FALSE,    0,      5,    7,    10 },
          { TRUE,     0,      2,    10,    0  },
          { FALSE,    1,      2,    6,    70 },
          { FALSE,    1,      8,    8,     0 }, // a milestone
          { FALSE,    1,      5,    9,     0 },
          { FALSE,    1,      4,    7,    40 },
          { FALSE,    1,      8,    10,    0 },
          { FALSE,    0,      1,    3,   100 },
          { FALSE,    0,      1,    1,   100 }, // a milestone
          { FALSE,    0,      0,    5,    80 }
    };

    COleDateTime t = COleDateTime::GetCurrentTime ();
	t.SetDate (t.GetYear (), t.GetMonth (), t.GetDay ()); // reset time

    CBCGPGanttItem* pItem;

    for (int i = 0; i < 11; ++i)
    {
        pItem = new CBCGPGanttItem;

        pItem->SetGroupItem (c_arrItems[i][0]);

        CString sName;
        sName.Format (c_arrItems[i][0] ? _T("Project #%d") : _T("Task #%d"), i + 1);
        pItem->SetName (sName);
        pItem->SetHierarchyLevel (c_arrItems[i][1]);
        pItem->SetInterval (t + COleDateTimeSpan(c_arrItems[i][2], 0, 0, 0), t + COleDateTimeSpan(c_arrItems[i][3], 0, 0, 0));
        pItem->SetProgress (c_arrItems[i][4] / 100.0);

        pChart->AddItem (pItem);
    }

    // Connect some items
    pChart->AddConnection (pChart->GetItemByIndex (0), pChart->GetItemByIndex (10), BCGPGANTTLINK_START_TO_START);
    pChart->AddConnection (pChart->GetItemByIndex (0), pChart->GetItemByIndex (1), BCGPGANTTLINK_FINISH_TO_START);
    pChart->AddConnection (pChart->GetItemByIndex (3), pChart->GetItemByIndex (5), BCGPGANTTLINK_FINISH_TO_FINISH);
    pChart->AddConnection (pChart->GetItemByIndex (6), pChart->GetItemByIndex (7), BCGPGANTTLINK_FINISH_TO_START);

    GetControl ().AdjustLayout ();

    GetControl ().LoadState (_T("Demo"));

	GetControl ().SetRedraw (TRUE);
	GetControl ().RedrawWindow ();

	GetDocument ()->SetModifiedFlag (FALSE);

    GetControl ().UpdateGrid ();
}

////////////////////////////////////////////////////////////////////////////
////                          Chart scaling
////////////////////////////////////////////////////////////////////////////

void CBCGPGanttDemoView::OnGanttZoomIn() 
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart != NULL)
    {
        ASSERT_VALID (pChart);
        pChart->IncreaseScale ();
    }
}

void CBCGPGanttDemoView::OnUpdateGanttZoomIn(CCmdUI* pCmdUI) 
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart->GetSafeHwnd () != NULL)
    {
        pCmdUI->Enable (TRUE);
        return;
    }

    pCmdUI->Enable (FALSE);
}

void CBCGPGanttDemoView::OnGanttZoomOut() 
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart != NULL)
    {
        ASSERT_VALID (pChart);
        pChart->DecreaseScale ();
    }
}

void CBCGPGanttDemoView::OnUpdateGanttZoomOut(CCmdUI* pCmdUI) 
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart->GetSafeHwnd () != NULL)
    {
        pCmdUI->Enable (TRUE);
        return;
    }

    pCmdUI->Enable (FALSE);
}

void CBCGPGanttDemoView::OnGanttLinkItems()
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart != NULL)
    {
        ASSERT_VALID (pChart);

        CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSel;
        pChart->GetSelectedItems (arrSel);

        int nItems = (int) arrSel.GetSize ();
        if (nItems < 2)
        {
            return;
        }

        CBCGPGanttItem* pSourceItem = arrSel[0];

        for (int i = 1; i < nItems; ++i)
        {
            pChart->AddConnection (pSourceItem, arrSel[i], BCGPGANTTLINK_FINISH_TO_FINISH);
        }
    }
}

void CBCGPGanttDemoView::OnUpdateGanttLinkItems(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (GetChart()->GetSelectedItemsCount() >= 2);
}

void CBCGPGanttDemoView::OnGanttUnlinkItems()
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart != NULL)
    {
        ASSERT_VALID (pChart);

        CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSel;
        pChart->GetSelectedItems (arrSel);

        int nItems = (int) arrSel.GetSize ();

        for (int i = 0; i < nItems; ++i)
        {
            int k;

            for (k = i + 1; k < nItems; ++k)
            {
                pChart->RemoveConnection (arrSel[i], arrSel[k]);
                pChart->RemoveConnection (arrSel[k], arrSel[i]);
            }
        }
    }
}

void CBCGPGanttDemoView::OnUpdateGanttUnlinkItems(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (GetChart()->GetSelectedItemsCount() >= 2);
}

BOOL CBCGPGanttDemoView::OnChartDoubleClickItem (UINT /*nFlags*/, CBCGPGanttItem* pItem)
{
	ASSERT_VALID (pItem);

	AddEditTask (pItem);

	return TRUE;
}

void CBCGPGanttDemoView::AddEditTask (CBCGPGanttItem* pItem, BOOL bMilestone/* = FALSE*/)
{
	CBCGPGanttItem* pItemEdit = pItem;

	BOOL bAdd = pItemEdit == NULL;

	if (bAdd)
	{
		pItemEdit = new CBCGPGanttItem;

		CBCGPGanttChart* pChart = GetChart ();
		if (pChart != NULL)
		{
			ASSERT_VALID (pChart);
			COleDateTime dtStart = pItemEdit->GetStartTime();
			COleDateTime dtEnd = pItemEdit->GetFinishTime();
			pItemEdit->SetInterval (pChart->SnapDateToGrid (dtStart), pChart->SnapDateToGrid (dtEnd));
		}

	}
	else
	{
		bMilestone = pItemEdit->IsMileStone ();
	}

	CGanttDlg dlg (*pItemEdit, bMilestone, FALSE, this);
	if (dlg.DoModal () != IDOK)
	{
		if (bAdd)
		{
			delete pItemEdit;
		}
		else
		{
			if (dlg.IsDeleted ())
			{
				OnGanttRemoveItem ();
			}
		}

		return;
	}

	if (bAdd)
	{
		GetChart ()->AddItem (pItemEdit);
	}
}

void CBCGPGanttDemoView::OnGanttNewTask()
{
	AddEditTask (NULL, FALSE);
}

void CBCGPGanttDemoView::OnUpdateGanttNew(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (TRUE);
}

void CBCGPGanttDemoView::OnGanttNewMilestone()
{
	AddEditTask (NULL, TRUE);
}

void CBCGPGanttDemoView::OnGanttOpenItem()
{
	CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSelected;
	GetChart()->GetSelectedItems (arrSelected);

	if (arrSelected.GetSize () == 1)
	{
		AddEditTask (arrSelected[0], arrSelected[0]->IsMileStone ());
	}
}

void CBCGPGanttDemoView::OnUpdateGanttOpenItem(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (GetChart()->GetSelectedItemsCount() == 1);
}

void CBCGPGanttDemoView::OnGanttRemoveItem()
{
	CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSelected;
	GetChart()->GetSelectedItems (arrSelected);

	GetControl ().SetRedraw (FALSE);

	int i = 0;

	for (i = (int)arrSelected.GetSize (); i > 0; --i)
	{
		GetChart ()->RemoveItem (arrSelected[i - 1]);
	}

	GetControl ().SetRedraw (TRUE);
	GetControl ().RedrawWindow ();
}

void CBCGPGanttDemoView::OnUpdateGanttRemoveItem(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (GetChart()->GetSelectedItemsCount() > 0);
}

void CBCGPGanttDemoView::OnMarkComplete()
{
	CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSelected;
	GetChart()->GetSelectedItems (arrSelected);

	GetControl ().SetRedraw (FALSE);

	int i = 0;

	for (i = 0; i < (int) arrSelected.GetSize (); i++)
	{
		arrSelected[i]->SetCompleted ();
	}

	GetControl ().SetRedraw (TRUE);
	GetControl ().RedrawWindow ();
}

void CBCGPGanttDemoView::OnUpdateMarkComplete(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (GetChart()->GetSelectedItemsCount() > 0);
}

void CBCGPGanttDemoView::OnGotoToday() 
{
	COleDateTime dt (COleDateTime::GetCurrentTime ());
	dt.SetDate (dt.GetYear (), dt.GetMonth (), dt.GetDay ());

	GetChart ()->GotoDateTime (dt);
}

void CBCGPGanttDemoView::OnGotoDay() 
{
	COleDateTime dt (COleDateTime::GetCurrentTime ());
	dt.SetDate (dt.GetYear (), dt.GetMonth (), dt.GetDay ());

	CGotoDayDialog dlg(dt, 
		CBCGPPlannerManagerCtrl::GetSystemFirstDayOfWeek (),
		this);

	if (dlg.DoModal () == IDOK)
	{
		dt = dlg.GetDate ();

		GetChart ()->GotoDateTime (dt);
	}
}

void CBCGPGanttDemoView::OnDestroy () 
{
    GetControl ().SaveState (_T("Demo"));
	CBCGPGanttView::OnDestroy ();
}
