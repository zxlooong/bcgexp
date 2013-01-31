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
// BCGPGridExampleView.cpp : implementation of the CBCGPGridExampleView class
//

#include "stdafx.h"
#include "BCGPGridExample.h"

#include "MainFrm.h"

#include "BCGPGridExampleDoc.h"
#include "BCGPGridExampleView.h"

#include "BasicGridCtrl.h"
#include "ReportGridCtrl.h"
#include "CellTypesGridCtrl.h"
#include "ColorGridCtrl.h"
#include "VirtualGridCtrl.h"
#include "MergeGridCtrl.h"
#include "FilterGridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleView

IMPLEMENT_DYNCREATE(CBCGPGridExampleView, CBCGPGridView)

BEGIN_MESSAGE_MAP(CBCGPGridExampleView, CBCGPGridView)
	//{{AFX_MSG_MAP(CBCGPGridExampleView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FIELD_CHOOSER, OnFieldChooser)
	ON_UPDATE_COMMAND_UI(ID_FIELD_CHOOSER, OnUpdateFieldChooser)
	ON_COMMAND(ID_GROUP_BY_BOX, OnGroupByBox)
	ON_UPDATE_COMMAND_UI(ID_GROUP_BY_BOX, OnUpdateGroupByBox)
	ON_COMMAND(ID_REPORT_PREVIEW, OnReportPreview)
	ON_UPDATE_COMMAND_UI(ID_REPORT_PREVIEW, OnUpdateReportPreview)
	ON_COMMAND(ID_COLOR_THEME_COMBO, OnColorThemeCombo)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_VIEW_BACK, OnViewBack)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BACK, OnUpdateViewBack)
	ON_COMMAND(ID_VIEW_FORWARD, OnViewForward)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORWARD, OnUpdateViewForward)
	ON_COMMAND(ID_MERGE_CELLS, OnGridMerge)
	ON_COMMAND(ID_UNMERGE_CELLS, OnGridUnmerge)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CBCGPGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPGridView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ON_HIDE_COLUMNCHOOSER, OnHideColumnChooser)
	ON_CBN_SELENDOK(ID_COLOR_THEME_COMBO, OnColorThemeCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleView construction/destruction

CBCGPGridExampleView::CBCGPGridExampleView()
{
	m_pCurrGrid = NULL;
	m_nCurrType = -1;
	m_nNavHistoryIndex = -1;
}

CBCGPGridExampleView::~CBCGPGridExampleView()
{
}

BOOL CBCGPGridExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPGridView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleView drawing

void CBCGPGridExampleView::OnDraw(CDC* /*pDC*/)
{
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleView printing

void CBCGPGridExampleView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CBCGPGridExampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CBCGPGridView::OnPreparePrinting (pInfo);
}

void CBCGPGridExampleView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnBeginPrinting (pDC, pInfo);
}

void CBCGPGridExampleView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnEndPrinting (pDC, pInfo);
}

void CBCGPGridExampleView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleView diagnostics

#ifdef _DEBUG
void CBCGPGridExampleView::AssertValid() const
{
	CBCGPGridView::AssertValid();
}

void CBCGPGridExampleView::Dump(CDumpContext& dc) const
{
	CBCGPGridView::Dump(dc);
}

CBCGPGridExampleDoc* CBCGPGridExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPGridExampleDoc)));
	return (CBCGPGridExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleView message handlers

void CBCGPGridExampleView::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}

void CBCGPGridExampleView::SetViewType (int nType, BOOL bByNavigationButtons)
{
	if (nType < 0 || nType >= BCGGRID_VIEWS_NUM)
	{
		nType = BCGGRID_BASIC;
	}

	CBCGPGridCtrl* pGridCtrl = m_arGrids [nType];
	ASSERT_VALID (pGridCtrl);

	m_nCurrType = nType;

	CList<UINT, UINT> lstHiddenCommands;

	if (m_nCurrType != BCGGRID_MERGE)
	{
		lstHiddenCommands.AddHead (ID_MERGE_CELLS);
		lstHiddenCommands.AddHead (ID_UNMERGE_CELLS);
	}

	if (m_nCurrType != BCGGRID_REPORT)
	{
		lstHiddenCommands.AddHead (ID_FIELD_CHOOSER);
		lstHiddenCommands.AddHead (ID_GROUP_BY_BOX);
		lstHiddenCommands.AddHead (ID_REPORT_PREVIEW);
	}

	if (m_nCurrType != BCGGRID_COLOR)
	{
		lstHiddenCommands.AddHead (ID_COLOR_LABEL);
		lstHiddenCommands.AddHead (ID_COLOR_THEME_COMBO);
	}

	((CMainFrame*)GetParent ())->SetHiddenCommands (lstHiddenCommands);

	if (pGridCtrl != m_pCurrGrid)
	{
		if (m_pCurrGrid->GetSafeHwnd () != NULL)
		{
			m_pCurrGrid->ShowWindow (SW_HIDE);
			m_pCurrGrid->ShowColumnsChooser (FALSE);
		}

		m_pCurrGrid = pGridCtrl;
		UpdateGrid ();

		m_pCurrGrid->SetScrollBarsStyle (
			m_nCurrType != BCGGRID_COLOR ?
				CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER :
				CBCGPScrollBar::BCGP_SBSTYLE_OWNER_DRAW);
		m_pCurrGrid->ShowWindow (SW_SHOW);
	}

	m_pWndGridCtrl = m_pCurrGrid;

	AdjustLayout ();
	m_pCurrGrid->SetFocus ();

	if (bByNavigationButtons)
	{
		((CMainFrame*)GetParent ())->UpdateCurrentView (nType);
	}
	else
	{
		m_arNavigationHistory.Add (nType);
		m_nNavHistoryIndex = (int) m_arNavigationHistory.GetSize () - 1;
	}
}

int CBCGPGridExampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create grid:
	CRect rectClient;
	GetClientRect (rectClient);
		
	for (int i = 0; i < BCGGRID_VIEWS_NUM; i++)
	{
		CBCGPGridCtrl* pGridCtrl = NULL;

		switch (i)
		{
		case BCGGRID_BASIC:
			pGridCtrl = new CBasicGridCtrl;
			break;

		case BCGGRID_REPORT:
			pGridCtrl = new CReportGridCtrl;
			break;

		case BCGGRID_CELLTYPES:
			pGridCtrl = new CCellTypesGridCtrl;
			break;

		case BCGGRID_COLOR:
			pGridCtrl = new CColorGridCtrl;
			break;

		case BCGGRID_VIRTUAL:
			pGridCtrl = new CVirtualGridCtrl;
			break;

		case BCGGRID_MERGE:
			pGridCtrl = new CMergeGridCtrl;
			break;

		case BCGGRID_FILTER:
			pGridCtrl = new CFilterGridCtrl;
			break;

		default:
			ASSERT (FALSE);
			return -1;
		}

		if (pGridCtrl == NULL)
		{
			ASSERT (FALSE);
			return -1;
		}

		ASSERT_VALID (pGridCtrl);

		if (!pGridCtrl->Create (WS_CHILD, rectClient, this, 1))
		{
			ASSERT (FALSE);
			return -1;
		}

		m_arGrids.Add (pGridCtrl);
	}
	
	SetViewType (((CMainFrame*)GetParent ())->GetCurrentViewType ());
	return 0;
}

BOOL CBCGPGridExampleView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CBCGPGridExampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void CBCGPGridExampleView::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPGridView::OnSetFocus(pOldWnd);
	
	if (m_pCurrGrid->GetSafeHwnd () != NULL)
	{
		m_pCurrGrid->SetFocus ();
	}
}

void CBCGPGridExampleView::OnDestroy() 
{
	for (int i = 0; i < m_arGrids.GetSize (); i++)
	{
		CBCGPGridCtrl* pGridCtrl = m_arGrids [i];
		if (pGridCtrl->GetSafeHwnd () != NULL)
		{
			pGridCtrl->DestroyWindow ();
			delete pGridCtrl;
		}
	}

	m_pCurrGrid = NULL;
	m_pWndGridCtrl = NULL;

	CBCGPGridView::OnDestroy();
}

void CBCGPGridExampleView::OnUpdateVisualManager ()
{
	if (m_pCurrGrid == NULL)
	{
		return;
	}

	ASSERT_VALID (m_pCurrGrid);

	switch (m_nCurrType)
	{
	case BCGGRID_COLOR:
		CColorGridCtrl* pColorGrid = (CColorGridCtrl*) m_pCurrGrid;
		pColorGrid->UpdateColorTheme ();
		break;
	}
}

void CBCGPGridExampleView::UpdateGrid ()
{
	if (m_pCurrGrid == NULL)
	{
		return;
	}

	ASSERT_VALID (m_pCurrGrid);

	switch (m_nCurrType)
	{
	case BCGGRID_BASIC:
		break;

	case BCGGRID_REPORT:
		m_pCurrGrid->EnableGroupByBox (theApp.m_Options.m_bGroupByBox);
		m_pCurrGrid->ShowColumnsChooser (theApp.m_Options.m_bFieldChooser);
		{
			CBCGPReportCtrl* pReportCtrl = DYNAMIC_DOWNCAST (CBCGPReportCtrl, m_pCurrGrid);
			if (pReportCtrl != NULL)
			{
				CWaitCursor wait;
				pReportCtrl->EnablePreviewRow (theApp.m_Options.m_bReportPreview);
			}
		}
		break;

	case BCGGRID_CELLTYPES:
		break;

	case BCGGRID_COLOR:
		{
			CColorGridCtrl* pColorGrid = (CColorGridCtrl*) m_pCurrGrid;
			pColorGrid->UpdateColorTheme ();
		}
		break;

	case BCGGRID_VIRTUAL:
		break;

	case BCGGRID_MERGE:
		break;

	case BCGGRID_FILTER:
		break;
	}
}

LRESULT CBCGPGridExampleView::OnHideColumnChooser (WPARAM, LPARAM)
{
	theApp.m_Options.m_bFieldChooser = FALSE;
	return 0;
}

void CBCGPGridExampleView::AdjustLayout ()
{
	if (m_pCurrGrid->GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	m_pCurrGrid->SetWindowPos (NULL, 0, 0, rectClient.Width (), rectClient.Height (),
							SWP_NOACTIVATE | SWP_NOZORDER);
}

void CBCGPGridExampleView::OnFieldChooser() 
{
	theApp.m_Options.m_bFieldChooser = !theApp.m_Options.m_bFieldChooser;
	UpdateGrid ();
}

void CBCGPGridExampleView::OnUpdateFieldChooser(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (theApp.m_Options.m_bFieldChooser);
}

void CBCGPGridExampleView::OnGroupByBox() 
{
	theApp.m_Options.m_bGroupByBox = !theApp.m_Options.m_bGroupByBox;
	UpdateGrid ();
}

void CBCGPGridExampleView::OnUpdateReportPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (theApp.m_Options.m_bReportPreview);
}

void CBCGPGridExampleView::OnReportPreview() 
{
	theApp.m_Options.m_bReportPreview = !theApp.m_Options.m_bReportPreview;
	UpdateGrid ();
}

void CBCGPGridExampleView::OnUpdateGroupByBox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (theApp.m_Options.m_bGroupByBox);
}

void CBCGPGridExampleView::OnColorThemeCombo() 
{
	CBCGPToolbarComboBoxButton* pCombobox = ((CMainFrame*)GetParent ())->GetColorCombo ();
	ASSERT_VALID (pCombobox);

	theApp.m_Options.m_nColorTheme = pCombobox->GetCurSel ();
	UpdateGrid ();

	if (m_pCurrGrid->GetSafeHwnd () != NULL)
	{
		m_pCurrGrid->SetFocus ();
	}
}

void CBCGPGridExampleView::OnEditSelectAll() 
{
	if (m_pCurrGrid->GetSafeHwnd () != NULL)
	{
		CBCGPGridItemID idItem;
		m_pCurrGrid->SetCurSel (idItem, SM_ALL);
	}
}

void CBCGPGridExampleView::OnViewBack() 
{
	m_nNavHistoryIndex--;
	SetViewType (m_arNavigationHistory [m_nNavHistoryIndex], TRUE);
}

void CBCGPGridExampleView::OnUpdateViewBack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_nNavHistoryIndex > 0);
}

void CBCGPGridExampleView::OnViewForward() 
{
	m_nNavHistoryIndex++;
	SetViewType (m_arNavigationHistory [m_nNavHistoryIndex], TRUE);
}

void CBCGPGridExampleView::OnUpdateViewForward(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_nNavHistoryIndex >= 0 && m_nNavHistoryIndex < m_arNavigationHistory.GetSize () - 1);
}

void CBCGPGridExampleView::OnGridMerge() 
{
	if (m_pCurrGrid != NULL && BCGGRID_MERGE == m_nCurrType)
	{
		ASSERT_VALID (m_pCurrGrid);

		m_pCurrGrid->MergeSelection ();
	}
}

void CBCGPGridExampleView::OnGridUnmerge() 
{
	if (m_pCurrGrid != NULL && BCGGRID_MERGE == m_nCurrType)
	{
		ASSERT_VALID (m_pCurrGrid);

		m_pCurrGrid->UnMergeSelection ();
	}
}

void CBCGPGridExampleView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (bActivate)
	{
		OnUpdateVisualManager ();
	}
	
	CBCGPGridView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
