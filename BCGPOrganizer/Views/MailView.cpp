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
// ReportDemoView.cpp : implementation of the CMailView class
//

#include "stdafx.h"
#include "../BCGPOrganizer.h"
#include "../BCGPOrganizerDoc.h"
#include "../mainfrm.h"

#include "MailView.h"
#include "../Mail/MailFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlagItem class

CFlagItem::CFlagItem(
	CBCGPToolBarImages&	icons,
	int nSelectedIcon,
	DWORD /*dwData*/) :
	m_Icons (icons)
{
	m_varValue = (long) nSelectedIcon;
	AllowEdit (FALSE);
}

BOOL CFlagItem::OnClickValue (UINT uiMsg, CPoint point)
{
	if (CBCGPGridItem::OnClickValue (uiMsg, point))
	{
		return TRUE;
	}

	if (uiMsg == WM_LBUTTONDOWN)
	{
		int nIndex = (long) m_varValue;

		if (nIndex < 0)
		{
			return FALSE;
		}

		if (nIndex > m_Icons.GetCount ())
		{
			return FALSE;
		}

		// shift nIndex
		nIndex++;
		nIndex %= m_Icons.GetCount ();

		m_varValue = (long) nIndex;

		CBCGPGridItemID id = GetGridItemID ();
		m_pGridRow->OnItemChanged (this, id.m_nRow, id.m_nColumn);
		Redraw ();

		return TRUE;
	}

	return FALSE;
}

void CFlagItem::OnDrawValue (CDC* pDC, CRect rect)
{
	int nIndex = (long) m_varValue;

	// fill background
	CRect rectFill = rect;
	rectFill.top++;
	rectFill.right++;
	pDC->FillRect (rectFill, &globalData.brLight);

	if (nIndex < 0)
	{
		return;
	}

	if (nIndex > m_Icons.GetCount ())
	{
		return;
	}

	IMAGEINFO imageInfo;
	memset (&imageInfo, 0, sizeof (IMAGEINFO));

	CPoint pt = rect.TopLeft ();
	CSize sizeIcon = m_Icons.GetImageSize ();

	int xOffset = (rect.Width () - sizeIcon.cx) / 2;
	int yOffset = (rect.Height () - sizeIcon.cy) / 2;
	pt.Offset (max (0, xOffset), max (0, yOffset));

	CBCGPDrawState ds;
	m_Icons.PrepareDrawImage (ds);
	m_Icons.Draw (pDC, pt.x, pt.y, nIndex);
	m_Icons.EndDrawImage (ds);
}

/////////////////////////////////////////////////////////////////////////////
// CMailView

IMPLEMENT_DYNCREATE(CMailView, CBCGPReportView)

BEGIN_MESSAGE_MAP(CMailView, CBCGPReportView)
	//{{AFX_MSG_MAP(CMailView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_GRID_VIEW_EXPAND_ALL, OnExpandAll)
	ON_COMMAND(ID_GRID_VIEW_COLLAPSE_ALL, OnCollapseAll)
	ON_COMMAND(ID_GRID_VIEW_FIELDCHOOSER, OnViewFieldchooser)
	ON_UPDATE_COMMAND_UI(ID_GRID_VIEW_FIELDCHOOSER, OnUpdateViewFieldchooser)
	ON_COMMAND(ID_GRID_VIEW_GROUPBOX, OnViewGroupbox)
	ON_UPDATE_COMMAND_UI(ID_GRID_VIEW_GROUPBOX, OnUpdateViewGroupbox)
	ON_COMMAND(ID_GRID_VIEW_COLUMN_AUTO_RESIZE, OnViewColumnAutoResize)
	ON_UPDATE_COMMAND_UI(ID_GRID_VIEW_COLUMN_AUTO_RESIZE, OnUpdateViewColumnAutoResize)
	ON_COMMAND(ID_MAIL_NEW, OnNew)
	ON_COMMAND(ID_MAIL_REMOVE, OnDelete)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK, OnOpen)
	ON_UPDATE_COMMAND_UI(ID_MAIL_REMOVE, OnUpdateDelete)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailView construction/destruction

CMailView::CMailView()
	: m_bFirstTime (TRUE)
{
	// TODO: add construction code here

}

CMailView::~CMailView()
{
}

BOOL CMailView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPReportView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMailView drawing

void CMailView::OnDraw(CDC* pDC)
{
	CBCGPReportView::OnDraw (pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMailView printing

void CMailView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CMailView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMailView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPReportView::OnBeginPrinting (pDC, pInfo);
}

void CMailView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPReportView::OnEndPrinting (pDC, pInfo);
}

void CMailView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
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
	
	CBCGPReportView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMailView diagnostics

#ifdef _DEBUG
void CMailView::AssertValid() const
{
	CBCGPReportView::AssertValid();
}

void CMailView::Dump(CDumpContext& dc) const
{
	CBCGPReportView::Dump(dc);
}

CBCGPOrganizerDoc* CMailView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPOrganizerDoc)));
	return (CBCGPOrganizerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMailView message handlers

void CMailView::OnContextMenu(CWnd*, CPoint point)
{
	if (point == CPoint (-1, -1))
	{
		CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
		if (pSel != NULL)
		{
			CRect rect = pSel->GetRect ();
			ClientToScreen (&rect);

			point.x = rect.left;
			point.y = rect.bottom;
		}
	}

	theApp.ShowPopupMenu (IDR_MAIL_MENU, point, this);
}

BOOL CMailView::AddMail (int nIcon, LPCTSTR strFrom, LPCTSTR strTo,
		 LPCTSTR strSubject, COleDateTime dateCreated, COleDateTime dateReceived, long lSize, 
		 IMPORTANCE importance/* = IMPORTANCE_NORMAL*/,
		 BOOL bHasAttachment/* = FALSE*/,
		 int nFlag/* = 0*/)
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	CBCGPGridRow* pRow = pReportCtrl->CreateRow (pReportCtrl->GetColumnCount ());

	//----------------
	// Set importance:
	//----------------
	int nImportanceIcon = -1;
	switch (importance)
	{
	case IMPORTANCE_HIGH:
		nImportanceIcon = 2;
		break;

	case IMPORTANCE_LOW:
		nImportanceIcon = 3;
		break;
	}

	pRow->GetItem (0)->SetImage (nImportanceIcon, FALSE);
	pRow->GetItem (1)->SetImage (nIcon, FALSE);
	pRow->GetItem (2)->SetImage (bHasAttachment ? 5 : -1, FALSE);

	pRow->GetItem (3)->SetValue (strFrom, FALSE);
	pRow->GetItem (4)->SetValue (strSubject, FALSE);
	pRow->GetItem (5)->SetValue (strTo, FALSE);

	pRow->ReplaceItem (7, new CBCGPGridDateTimeItem (dateCreated), FALSE);
	pRow->ReplaceItem (8, new CBCGPGridDateTimeItem (dateReceived), FALSE);

	pRow->GetItem (9)->SetValue (lSize, FALSE);

	pRow->ReplaceItem (11, new CFlagItem (m_Flags, nFlag), FALSE);

	pReportCtrl->AddRow (pRow, FALSE);

	return TRUE;
}

inline int Rand (int nMax)
{
	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

void CMailView::CreateDemo(BOOL bRedraw/* = TRUE*/)
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);

	pReportCtrl->RemoveAll ();

	#define NAMES_NUM	7
	LPCTSTR arNames [NAMES_NUM] =
	{
		_T("John Smith"),
		_T("Support Team"),
		_T("Peter Brown"),
		_T("Matt Johnson"),
		_T("James Lee"),
		_T("Customer Service"),
		_T("Webmaster"),
	};

	#define SUBJ_NUM	8
	LPCTSTR arSubjs [SUBJ_NUM] =
	{
		_T("Important information"),
		_T("Customer Newsletter"),
		_T("Question"),
		_T("Business proposal"),
		_T("Request more info about your products"),
		_T("Thank you!"),
		_T("Your application has been approved"),
		_T("Please read this message"),
	};

	srand( (unsigned)time( NULL ) );

	for (int i = 0; i < 100; i++)
	{
		COleDateTime now = COleDateTime::GetCurrentTime ();
		COleDateTimeSpan span (
			Rand (5),
			Rand (23),
			Rand (59),
			0);
		COleDateTimeSpan span2 (
			0,
			Rand (2),
			Rand (59),
			Rand (59));

		AddMail (Rand (2), // Icon
			arNames [Rand (NAMES_NUM)],
			arNames [Rand (NAMES_NUM)],
			arSubjs [Rand (SUBJ_NUM)],
			now - span - span2,
			now - span, 
			Rand (200),
			(IMPORTANCE) Rand (3),
			Rand (2), 
			Rand (7));
	}

	if (bRedraw)
	{
		pReportCtrl->AdjustLayout ();
	}
}

void CMailView::OnInitialUpdate() 
{
	CBCGPReportView::OnInitialUpdate();
	
	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;

		CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
		ASSERT_VALID (pReportCtrl);

		//------------------
		// Load grid images:
		//------------------
		CBitmap bmp;
		bmp.LoadBitmap (IDB_MAIL_ICONS);

		m_Images.Create (16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
		m_Images.Add (&bmp, (CBitmap*) NULL);

		pReportCtrl->SetImageList (&m_Images);

		//------------------------------
		// Load images for "flag" items:
		//------------------------------
		m_Flags.SetImageSize (CSize (14, 14));
		m_Flags.SetTransparentColor (RGB (255, 0, 255));
		m_Flags.Load (IDB_MAIL_FLAGS);

		//----------------
		// Insert columns:
		//----------------
		pReportCtrl->InsertColumn (0, _T("Importance"), 20, 1);
		pReportCtrl->InsertColumn (1, _T("Icon"), 20, 0);
		pReportCtrl->InsertColumn (2, _T("Attachment"), 20, 2);
		pReportCtrl->InsertColumn (3, _T("From"), 150);
		pReportCtrl->InsertColumn (4, _T("Subject"), 150);
		pReportCtrl->InsertColumn (5, _T("To"), 140);
		pReportCtrl->InsertColumn (6, _T("CC"), 120);
		pReportCtrl->InsertColumn (7, _T("Created"), 130);
		pReportCtrl->InsertColumn (8, _T("Received"), 130);
		pReportCtrl->InsertColumn (9, _T("Size"), 80);
		pReportCtrl->InsertColumn (10, _T("Category"), 80);
		pReportCtrl->InsertColumn (11, _T("Flag Status"), 20, 3);

		//pReportCtrl->SetHeaderAlign (0, HDF_CENTER);
		//pReportCtrl->SetHeaderAlign (1, HDF_CENTER);
		//pReportCtrl->SetHeaderAlign (2, HDF_CENTER);

		//pReportCtrl->SetColumnAlign (0, HDF_CENTER); // Importance
		//pReportCtrl->SetColumnAlign (1, HDF_CENTER); // Icon
		//pReportCtrl->SetColumnAlign (2, HDF_CENTER); // Attachment
		pReportCtrl->SetColumnAlign (9, HDF_RIGHT);  // Size

		pReportCtrl->SetColumnLocked (0);
		pReportCtrl->SetColumnLocked (2);
		pReportCtrl->SetColumnLocked (11);

		pReportCtrl->SetColumnVisible (4, FALSE);
		pReportCtrl->SetColumnVisible (5, FALSE);
		pReportCtrl->SetColumnVisible (6, FALSE);
		pReportCtrl->SetColumnVisible (8, FALSE);
		pReportCtrl->SetColumnVisible (10, FALSE);

		//-------------------
		// Set group columns:
		//-------------------
		pReportCtrl->InsertGroupColumn (0, 8 /* Received */);
		pReportCtrl->InsertGroupColumn (1, 4 /* Subject */);

		//--------------------------
		// Create header image list:
		//--------------------------
		m_ImagesHeader.Create (IDB_MAIL_HEADER, 12, 0, RGB (255, 0, 255));

		pReportCtrl->SetHeaderImageList (&m_ImagesHeader);

		pReportCtrl->EnableHeader ();
		pReportCtrl->EnableColumnAutoSize (TRUE);

		pReportCtrl->SetWholeRowSel (TRUE);
		pReportCtrl->SetSingleSel (TRUE);
		pReportCtrl->EnableMarkSortedColumn (TRUE);

		pReportCtrl->EnableGroupByBox (TRUE);
		
		pReportCtrl->LoadState (NULL);

		CreateDemo();
	}

}

int CMailView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CMailView::OnDestroy() 
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);

	pReportCtrl->SaveState (NULL);

	CBCGPReportView::OnDestroy();
}

void CMailView::OnExpandAll() 
{
	GetReportCtrl ()->ExpandAll ();
}

void CMailView::OnCollapseAll() 
{
	GetReportCtrl ()->ExpandAll (FALSE);
}


void CMailView::OnViewFieldchooser() 
{
	GetReportCtrl ()->ShowColumnsChooser (
		!GetReportCtrl ()->IsColumnsChooserVisible ());
}

void CMailView::OnUpdateViewFieldchooser(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (GetReportCtrl ()->IsColumnsChooserVisible ());
}

void CMailView::OnViewGroupbox() 
{
	GetReportCtrl ()->EnableGroupByBox (!GetReportCtrl ()->IsGroupByBox ());
}

void CMailView::OnUpdateViewGroupbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (GetReportCtrl ()->IsGroupByBox ());
}

void CMailView::OnViewColumnAutoResize() 
{
	GetReportCtrl ()->EnableColumnAutoSize (!GetReportCtrl ()->IsColumnAutoSizeEnabled ());
}

void CMailView::OnUpdateViewColumnAutoResize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (GetReportCtrl ()->IsColumnAutoSizeEnabled ());
}

BOOL CMailView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pNMHDR = (NMHDR*)(lParam);
	if (pNMHDR != NULL && pNMHDR->code == BCGPGN_SELCHANGED)
	{
		UpdateCaptionText ();

		*pResult = 0L;
		return TRUE;
	}
	
	return CBCGPReportView::OnNotify(wParam, lParam, pResult);
}

void CMailView::UpdateCaptionText ()
{
	CBCGPOrganizerDoc* pDoc = GetDocument ();
	if (pDoc == NULL || pDoc->GetMode () != CBCGPOrganizerDoc::e_ModeMail)
	{
		return;
	}

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());

	if (pFrame != NULL)
	{
		CString str;
		CBCGPGridCtrl* pGridCtrl = GetGridCtrl ();
		if (pGridCtrl != NULL)
		{
			CBCGPGridRow* pRow = pGridCtrl->GetCurSel ();
			if (pRow != NULL && !pRow->IsGroup ())
			{
				str = _T("From: ") + pRow->GetItem (3)->FormatItem ();
				str += _T("; Subject: ") + pRow->GetItem (4)->FormatItem ();
			}
		}

		if (str.IsEmpty ())
		{
			str = _T(" ");
		}

		pFrame->SetCaptionText (str);
	}
}

void CMailView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPReportView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		UpdateCaptionText ();
	}
}

void CMailView::OnNew()
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	CBCGPGridRow* pRow = pReportCtrl->CreateRow (pReportCtrl->GetColumnCount ());

	CMailFrame frame (*pRow, FALSE, this);
	if (frame.DoModal () == IDOK)
	{
		delete pRow;
		//pReportCtrl->AddRow (pRow, TRUE);
	}
	else
	{
		delete pRow;
	}
}

void CMailView::OnDelete()
{
}

void CMailView::OnUpdateDelete(CCmdUI* pCmdUI)
{
	CBCGPGridRow* pRow = GetGridCtrl ()->GetCurSel ();
	pCmdUI->Enable (pRow != NULL && !pRow->IsGroup ());
}

LRESULT CMailView::OnOpen (WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	CBCGPGridRow* pRow = GetGridCtrl ()->GetCurSel ();

	if (pRow == NULL || pRow->IsGroup ())
	{
		return 0L;
	}

	CMailFrame frame (*pRow, TRUE, this);
	if (frame.DoModal () != IDOK)
	{
		if (frame.IsDeleted ())
		{
			PostMessage (WM_COMMAND, ID_MAIL_REMOVE, 0);
		}
	}

	return 0L;
}
