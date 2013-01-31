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
// GanttView.cpp : implementation file
//

#include "stdafx.h"
#include "../BCGPOrganizer.h"
#include "../BCGPOrganizerDoc.h"

#include "../MainFrm.h"

#include "GanttView.h"
#include "../Gantt/GanttFrame.h"
#include "../Gantt/GotoDayDialog2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//                          Chart scaling
//////////////////////////////////////////////////////////////////////////

static const COleDateTimeSpan s_arrAvailableScales[] =
{
    COleDateTimeSpan(0, 8, 0, 0),
    COleDateTimeSpan(0, 6, 0, 0),
    COleDateTimeSpan(0, 4, 0, 0),
    COleDateTimeSpan(0, 3, 0, 0),
    COleDateTimeSpan(0, 2, 0, 0),
    COleDateTimeSpan(0, 1, 30, 0),
    COleDateTimeSpan(0, 1, 0, 0),
    COleDateTimeSpan(0, 0, 40, 0),

    COleDateTimeSpan(0, 0, 30, 0), // 100%

    COleDateTimeSpan(0, 0, 20, 0),
    COleDateTimeSpan(0, 0, 15, 0),
    COleDateTimeSpan(0, 0, 12, 0),
    COleDateTimeSpan(0, 0, 8, 0),
    COleDateTimeSpan(0, 0, 4, 0),
    COleDateTimeSpan(0, 0, 2, 0),
    COleDateTimeSpan(0, 0, 0, 45),
    COleDateTimeSpan(0, 0, 0, 30)
};

const int nScalesCount = sizeof(s_arrAvailableScales) / sizeof(*s_arrAvailableScales);

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
// CGanttView

IMPLEMENT_DYNCREATE(CGanttView, CBCGPGanttView)

BEGIN_MESSAGE_MAP(CGanttView, CBCGPGanttView)
	//{{AFX_MSG_MAP(CGanttView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_GANTT_DRAW_BACKGROUND, OnDrawBackground)
	ON_UPDATE_COMMAND_UI(ID_GANTT_DRAW_BACKGROUND, OnUpdateDrawBackground)
    ON_COMMAND(ID_GANTT_LINK, OnGanttLinkItems)
    ON_UPDATE_COMMAND_UI(ID_GANTT_LINK, OnUpdateGanttLinkItems)
    ON_COMMAND(ID_GANTT_UNLINK, OnGanttUnlinkItems)
    ON_UPDATE_COMMAND_UI(ID_GANTT_UNLINK, OnUpdateGanttUnlinkItems)
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
	ON_COMMAND(ID_GOTO_TODAY, OnGotoToday)
	ON_UPDATE_COMMAND_UI(ID_GOTO_TODAY, OnUpdateGotoToday)
	ON_COMMAND(ID_GOTO_DAY, OnGotoDay)
	ON_UPDATE_COMMAND_UI(ID_GOTO_DAY, OnUpdateGotoDay)	
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CBCGPGanttView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPGanttView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_REGISTERED_MESSAGE(BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, OnHighlightRibbonListItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGanttView construction/destruction

CGanttView::CGanttView()
	: m_bFirstTime (TRUE)
{
}

CGanttView::~CGanttView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGanttView diagnostics

#ifdef _DEBUG
void CGanttView::AssertValid() const
{
	CBCGPGanttView::AssertValid();
}

void CGanttView::Dump(CDumpContext& dc) const
{
	CBCGPGanttView::Dump(dc);
}

CBCGPOrganizerDoc* CGanttView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPOrganizerDoc)));
	return (CBCGPOrganizerDoc*)m_pDocument;
}
#endif //_DEBUG

void CGanttView::OnInitialUpdate()
{
	CBCGPGanttView::OnInitialUpdate();

	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;

		UpdateGantt (theApp.m_OptionsGantt, FALSE);

		CreateDemo (TRUE);

		GetChart ()->SetTimeDelta (s_arrAvailableScales[nScalesCount / 2], TRUE);
	}
}

void CGanttView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPGanttView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		UpdateCaptionText ();
		OnChartScaleChanged ();
	}
}

void CGanttView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CGanttView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGanttView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGanttView::OnBeginPrinting (pDC, pInfo);
}

void CGanttView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGanttView::OnEndPrinting(pDC, pInfo);
}

void CGanttView::CreateDemo (BOOL bRedraw /*= TRUE*/)
{
    CBCGPGanttControl& control = GetControl ();

	if (bRedraw)
	{
		control.SetRedraw (FALSE);
	}

    CBCGPGanttChart* pChart = GetChart ();
    ASSERT_VALID (pChart);

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
    control.SetProgressColumnIndex (iCol);
	pGrid->SetItemRTC (iCol++, RUNTIME_CLASS (CProgressItem));

    // Fill data

    const int c_arrItems [11][5] =
    {
        // is_group, level, begin, end, complete
          { FALSE,    0,      3,    4,    32 },
          { FALSE,    0,      5,    7,    10 },
          { TRUE,     0,      2,    10,    0 },
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

    control.AdjustLayout ();

    control.LoadState (_T("Demo"));

	if (bRedraw)
	{
		control.SetRedraw (TRUE);
		control.RedrawWindow ();
	}

    GetControl ().UpdateGrid ();

	GetDocument ()->SetModifiedFlag (FALSE);
}

void CGanttView::UpdateGantt (const CGanttOptions& options, BOOL bRedraw /*= TRUE*/)
{
	CBCGPGanttChart* pChart = GetChart ();

	pChart->SetRedraw (FALSE);

	pChart->SetColorScheme (options.m_clrBackground);

	pChart->SetRedraw (TRUE);

	if (bRedraw)
	{
		pChart->RedrawWindow ();
	}

	if (options.m_ShowToolTip != pChart->IsShowToolTip ())
	{
		pChart->SetShowToolTip (options.m_ShowToolTip != 0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGanttView message handlers

int CGanttView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGanttView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetControl ().SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

	return 0;
}

void CGanttView::OnDestroy () 
{
    GetControl ().SaveState (_T("Demo"));
	CBCGPGanttView::OnDestroy ();
}

void CGanttView::UpdateCaptionText ()
{
	CBCGPOrganizerDoc* pDoc = GetDocument ();
	if (pDoc == NULL || pDoc->GetMode () != CBCGPOrganizerDoc::e_ModeGantt)
	{
		return;
	}

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
	if (pFrame != NULL)
	{
		CString strText;

		if (GetControl ().GetChart ()->GetSafeHwnd () != NULL)
		{

		}

		pFrame->SetCaptionText (strText);
	}
}

void CGanttView::OnDrawBackground()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST (CMainFrame, GetTopLevelFrame ());
	if (pFrame != NULL)
	{
		COLORREF clr = pFrame->GetGanttBackground ();
		GetChart ()->SetColorScheme (clr);
		theApp.m_OptionsGantt.m_clrBackground = clr;
	}
}

void CGanttView::OnUpdateDrawBackground(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

class XBCGPRibbonColorButton: public CBCGPRibbonColorButton
{
	friend class CGanttView;
};

LRESULT CGanttView::OnHighlightRibbonListItem (WPARAM wp, LPARAM lp)
{
	int nIndex = (int) wp;

	CBCGPBaseRibbonElement* pElem = (CBCGPBaseRibbonElement*) lp;
	ASSERT_VALID (pElem);

	const UINT uiCommand = pElem->GetID ();

	if (uiCommand == ID_GANTT_DRAW_BACKGROUND)
	{
		COLORREF clr = theApp.m_OptionsGantt.m_clrBackground;

		if (nIndex != -1)
		{
			XBCGPRibbonColorButton* pColor = 
				(XBCGPRibbonColorButton*)DYNAMIC_DOWNCAST(CBCGPRibbonColorButton, pElem);
			if (pColor != NULL)
			{
				clr = pColor->GetColorByIndex (nIndex);
			}
		}

		GetChart()->SetColorScheme (clr);
	}

	return 0L;
}

BOOL CGanttView::OnChartScaleChanging (BOOL bIncrease)
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart != NULL)
    {
        ASSERT_VALID (pChart);

		int index = -1;
		COleDateTimeSpan dtCurrent (pChart->GetTimeDelta ());
		for (int i = 0; i < nScalesCount; ++i)
        {
            if (s_arrAvailableScales[i] == dtCurrent)
            {
				index = i;
				break;
			}
		}

        if (bIncrease)
        {
			index++;
		}
		else
		{
			index--;
		}

		UpdateZoom (index);
    }

	return TRUE;
}

void CGanttView::OnChartScaleChanged ()
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart != NULL)
    {
        ASSERT_VALID (pChart);

		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
		if (pFrame != NULL)
		{
			int index = -1;
			COleDateTimeSpan dtCurrent (pChart->GetTimeDelta ());
			for (int i = 0; i < nScalesCount; ++i)
            {
                if (s_arrAvailableScales[i] == dtCurrent)
                {
					index = i;
					break;
				}
			}

			pFrame->GetZoomSlider ()->SetPos (index);
		}
    }
}

void CGanttView::UpdateZoom (int index)
{
    CBCGPGanttChart* pChart = GetChart ();

    if (pChart != NULL)
    {
        ASSERT_VALID (pChart);

		index = max (min (index, nScalesCount - 1), 0);

		pChart->SetTimeDelta (s_arrAvailableScales [index], TRUE);
	}
}

void CGanttView::OnContextMenu(CWnd*, CPoint point)
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
		theApp.ShowPopupMenu (nID, point, this);
	}
}

BOOL CGanttView::OnChartDoubleClickItem (UINT /*nFlags*/, CBCGPGanttItem* pItem)
{
	ASSERT_VALID (pItem);

	AddEditTask (pItem);

	return TRUE;
}

void CGanttView::AddEditTask (CBCGPGanttItem* pItem, BOOL bMilestone/* = FALSE*/)
{
	CBCGPGanttItem* pItemEdit = pItem;

	BOOL bAdd = pItemEdit == NULL;

	if (bAdd)
	{
		pItemEdit = new CBCGPGanttItem;
	}
	else
	{
		bMilestone = pItemEdit->IsMileStone ();
	}

	CGanttFrame dlg (*pItemEdit, bMilestone, FALSE, this);
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


void CGanttView::OnGanttLinkItems()
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

void CGanttView::OnUpdateGanttLinkItems(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (GetChart()->GetSelectedItemsCount() >= 2);
}

void CGanttView::OnGanttUnlinkItems()
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

void CGanttView::OnUpdateGanttUnlinkItems(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (GetChart()->GetSelectedItemsCount() >= 2);
}

void CGanttView::OnGanttNewTask()
{
	AddEditTask (NULL, FALSE);
}

void CGanttView::OnUpdateGanttNew(CCmdUI* /*pCmdUI*/)
{
}

void CGanttView::OnGanttNewMilestone()
{
	AddEditTask (NULL, TRUE);
}

void CGanttView::OnGanttOpenItem()
{
	CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSelected;
	GetChart()->GetSelectedItems (arrSelected);

	if (arrSelected.GetSize () == 1)
	{
		AddEditTask (arrSelected[0], arrSelected[0]->IsMileStone ());
	}
}

void CGanttView::OnUpdateGanttOpenItem(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetChart()->GetSelectedItemsCount() == 1);
}

void CGanttView::OnGanttRemoveItem()
{
	CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSelected;
	GetChart()->GetSelectedItems (arrSelected);

	GetControl ().SetRedraw (FALSE);

	int i = 0;

	for (i = arrSelected.GetSize (); i > 0; --i)
	{
		GetChart ()->RemoveItem (arrSelected[i - 1]);
	}

	GetControl ().SetRedraw (TRUE);
	GetControl ().RedrawWindow ();
}

void CGanttView::OnUpdateGanttRemoveItem(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetChart()->GetSelectedItemsCount() > 0);
}

void CGanttView::OnMarkComplete()
{
	CArray <CBCGPGanttItem*, CBCGPGanttItem*> arrSelected;
	GetChart()->GetSelectedItems (arrSelected);

	GetControl ().SetRedraw (FALSE);

	int i = 0;

	for (i = 0; i < arrSelected.GetSize (); i++)
	{
		arrSelected[i]->SetCompleted ();
	}

	GetControl ().SetRedraw (TRUE);
	GetControl ().RedrawWindow ();
}

void CGanttView::OnUpdateMarkComplete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetChart()->GetSelectedItemsCount() > 0);
}

void CGanttView::OnGotoToday() 
{
	COleDateTime dt (COleDateTime::GetCurrentTime ());
	dt.SetDate (dt.GetYear (), dt.GetMonth (), dt.GetDay ());

	GetChart ()->GotoDateTime (dt);
}

void CGanttView::OnUpdateGotoToday(CCmdUI* /*pCmdUI*/) 
{
}

void CGanttView::OnGotoDay() 
{
	COleDateTime dt (COleDateTime::GetCurrentTime ());
	dt.SetDate (dt.GetYear (), dt.GetMonth (), dt.GetDay ());

	CGotoDayDialog2 dlg(dt, 
		CBCGPPlannerManagerCtrl::GetSystemFirstDayOfWeek (),
		this);

	if (dlg.DoModal () == IDOK)
	{
		dt = dlg.GetDate ();

		GetChart ()->GotoDateTime (dt);
	}
}

void CGanttView::OnUpdateGotoDay(CCmdUI* /*pCmdUI*/) 
{
}
