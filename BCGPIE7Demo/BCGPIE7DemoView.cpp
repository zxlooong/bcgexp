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
// BCGPIEDemoView.cpp : implementation of the CBCGPIE7DemoView class
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"

#include "BCGPIE7DemoDoc.h"
#include "BCGPIE7DemoView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CBCGPIE7DemoView::m_bWorkOffline = FALSE;
BOOL CBCGPIE7DemoView::m_bGoAddress = TRUE;

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoView

IMPLEMENT_DYNCREATE(CBCGPIE7DemoView, CHtmlView)

BEGIN_MESSAGE_MAP(CBCGPIE7DemoView, CHtmlView)
	//{{AFX_MSG_MAP(CBCGPIE7DemoView)
	ON_COMMAND(ID_GOTO_BACK, OnGoBack)
	ON_UPDATE_COMMAND_UI(ID_GOTO_BACK, OnUpdateGoBack)
	ON_COMMAND(ID_GOTO_FORWARD, OnGoForward)
	ON_UPDATE_COMMAND_UI(ID_GOTO_FORWARD, OnUpdateGoForward)
	ON_UPDATE_COMMAND_UI(ID_GOTO_HISTORY, OnUpdateGoHistory)
	ON_COMMAND(ID_GOTO_SEARCH, OnGoSearch)
	ON_UPDATE_COMMAND_UI(ID_GOTO_SEARCH_MENU, OnUpdateGoSearchMenu)
	ON_COMMAND(ID_GOTO_HOMEPAGE, OnGoHomePage)
	ON_COMMAND(ID_VIEW_STOP, OnViewStop)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_VIEW_FONTSIZE_LARGEST, OnViewFontSizeLargest)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONTSIZE_LARGEST, OnUpdateViewFontSizeLargest)
	ON_COMMAND(ID_VIEW_FONTSIZE_LARGER, OnViewFontSizeLarger)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONTSIZE_LARGER, OnUpdateViewFontSizeLarger)
	ON_COMMAND(ID_VIEW_FONTSIZE_MEDIUM, OnViewFontSizeMedium)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONTSIZE_MEDIUM, OnUpdateViewFontSizeMedium)
	ON_COMMAND(ID_VIEW_FONTSIZE_SMALLER, OnViewFontSizeSmaller)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONTSIZE_SMALLER, OnUpdateViewFontSizeSmaller)
	ON_COMMAND(ID_VIEW_FONTSIZE_SMALLEST, OnViewFontSizeSmallest)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONTSIZE_SMALLEST, OnUpdateViewFontSizeSmallest)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_PROPERTIES, OnFileProperties)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoView construction/destruction

CBCGPIE7DemoView::CBCGPIE7DemoView()
	: m_bTitleUpdated (FALSE)
{
	// TODO: add construction code here

}

CBCGPIE7DemoView::~CBCGPIE7DemoView()
{
}

BOOL CBCGPIE7DemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoView drawing

void CBCGPIE7DemoView::OnDraw(CDC* /*pDC*/)
{
	CBCGPIE7DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoView printing

BOOL CBCGPIE7DemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBCGPIE7DemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBCGPIE7DemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoView diagnostics

#ifdef _DEBUG
void CBCGPIE7DemoView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBCGPIE7DemoView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CBCGPIE7DemoDoc* CBCGPIE7DemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPIE7DemoDoc)));
	return (CBCGPIE7DemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoView message handlers
// these are all simple one-liners to do simple controlling of the browser
void CBCGPIE7DemoView::OnGoBack()
{
	CBCGPIE7DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pHistoryObj = pDoc->GoBack ();
	if (pHistoryObj != NULL)
	{
		NavigateB (pHistoryObj->GetURL (), 0, NULL);
	}
}

void CBCGPIE7DemoView::OnUpdateGoBack(CCmdUI* pCmdUI) 
{
	CBCGPIE7DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable (pDoc->IsBackAvailable ());
}

void CBCGPIE7DemoView::OnGoForward()
{
//	GoForward();
	CBCGPIE7DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pHistoryObj = pDoc->GoForward ();
	if (pHistoryObj != NULL)
	{
		NavigateB (pHistoryObj->GetURL (), 0, NULL);
	}
}

void CBCGPIE7DemoView::OnUpdateGoForward(CCmdUI* pCmdUI) 
{
	CBCGPIE7DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable (pDoc->IsFrwdAvailable ());
}

void CBCGPIE7DemoView::OnUpdateGoHistory(CCmdUI* pCmdUI)
{
	CBCGPIE7DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable (pDoc->IsBackAvailable () || pDoc->IsFrwdAvailable ());
}

void CBCGPIE7DemoView::OnGoSearch()
{
	GoSearch();
}

void CBCGPIE7DemoView::OnUpdateGoSearchMenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CBCGPIE7DemoView::OnGoHomePage()
{
	GoHome();
}

void CBCGPIE7DemoView::OnViewStop()
{
	Stop();
}

void CBCGPIE7DemoView::OnViewRefresh()
{
	Refresh();
}

// these functions control the font size.  There is no explicit command in the
// CHtmlView class to do this, but we can do it by using the ExecWB() function.
void CBCGPIE7DemoView::OnViewFontSizeLargest()
{
	if (m_nFontSize == 4l)
	{
		return;
	}

	m_nFontSize = 4l;
	COleVariant vaZoomFactor(m_nFontSize);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGPIE7DemoView::OnUpdateViewFontSizeLargest(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_nFontSize == 4l);
}

void CBCGPIE7DemoView::OnViewFontSizeLarger()
{
	if (m_nFontSize == 3l)
	{
		return;
	}

	m_nFontSize = 3l;
	COleVariant vaZoomFactor(m_nFontSize);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGPIE7DemoView::OnUpdateViewFontSizeLarger(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_nFontSize == 3l);
}

void CBCGPIE7DemoView::OnViewFontSizeMedium()
{
	if (m_nFontSize == 2l)
	{
		return;
	}

	m_nFontSize = 2l;
	COleVariant vaZoomFactor(m_nFontSize);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGPIE7DemoView::OnUpdateViewFontSizeMedium(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_nFontSize == 2l);
}

void CBCGPIE7DemoView::OnViewFontSizeSmaller()
{
	if (m_nFontSize == 1l)
	{
		return;
	}

	m_nFontSize = 1l;
	COleVariant vaZoomFactor(m_nFontSize);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGPIE7DemoView::OnUpdateViewFontSizeSmaller(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_nFontSize == 1l);
}

void CBCGPIE7DemoView::OnViewFontSizeSmallest()
{
	if (m_nFontSize == 0l)
	{
		return;
	}

	m_nFontSize = 0l;
	COleVariant vaZoomFactor(m_nFontSize);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGPIE7DemoView::OnUpdateViewFontSizeSmallest(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_nFontSize == 0l);
}

void CBCGPIE7DemoView::OnDocumentComplete(LPCTSTR lpszURL) 
{
	// make sure the main frame has the new URL.  This call also stops the animation
	((CMainFrame*)AfxGetMainWnd())->SetAddress(lpszURL);

	CBCGPIE7DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pObj = pDoc->AddURLToHistory (GetLocationName (), lpszURL);
	if (pObj != NULL)
	{
		theApp.m_History.Add (*pObj);
		// TODO: update history bar
	}

	((CMainFrame*)AfxGetMainWnd())->SetProgress (0, -1);

	COleVariant var(0l);
	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
	   NULL, &var);

	m_nFontSize = max(min(var.lVal, 4l), 0l);

	CHtmlView::OnDocumentComplete(lpszURL);
}

void CBCGPIE7DemoView::OnTitleChange(LPCTSTR lpszText) 
{
	// this will change the main frame's title bar
	if (m_pDocument != NULL)
	{
		m_pDocument->SetTitle(lpszText);
		m_bTitleUpdated = TRUE;
	}
}

void CBCGPIE7DemoView::NavigateB(LPCTSTR lpszURL, DWORD dwFlags/* = 0*/,
		LPCTSTR lpszTargetFrameName/* = NULL*/, LPCTSTR lpszHeaders/* = NULL*/,
		LPVOID lpvPostData/* = NULL*/, DWORD dwPostDataLen/* = 0*/)
{
	m_bTitleUpdated = FALSE;

	Navigate2 (lpszURL, dwFlags, lpszTargetFrameName, lpszHeaders, lpvPostData, dwPostDataLen);
}

void CBCGPIE7DemoView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD /*nFlags*/, LPCTSTR /*lpszTargetFrameName*/, CByteArray& /*baPostedData*/, LPCTSTR /*lpszHeaders*/, BOOL* /*pbCancel*/) 
{
	// start the animation so that is plays while the new page is being loaded
	((CMainFrame*)AfxGetMainWnd())->StartAnimation();

	if (!m_bTitleUpdated)
	{
		if (m_pDocument != NULL)
		{
			m_pDocument->SetTitle(lpszURL);
		}
	}
}

void CBCGPIE7DemoView::OnInitialUpdate() 
{
	CHtmlView::OnInitialUpdate ();

	m_nFontSize = 2l;

	SetOffline (m_bWorkOffline);

	if (m_bGoAddress)
	{
		GoHome();
	}
}

void CBCGPIE7DemoView::OnProgressChange(long nProgress, long nProgressMax) 
{
	((CMainFrame*)AfxGetMainWnd())->SetProgress(nProgress, nProgressMax);
	
	CHtmlView::OnProgressChange(nProgress, nProgressMax);
}

void CBCGPIE7DemoView::OnDestroy() 
{
	CHtmlView::OnDestroy();
	CView::OnDestroy();		// Fixes CHtmlView bug
}

void CBCGPIE7DemoView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndBrowser.m_hWnd))
	{
		// need to push non-client borders out of the client area
		CRect rect;
		GetClientRect(rect);
		::AdjustWindowRectEx(rect,
			m_wndBrowser.GetStyle(), FALSE, WS_EX_CLIENTEDGE);

		HDWP hdwp = ::BeginDeferWindowPos (1);

		::DeferWindowPos (hdwp, m_wndBrowser.GetSafeHwnd (), NULL, rect.left, rect.top,
			rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

		::EndDeferWindowPos (hdwp);
	}
}

void CBCGPIE7DemoView::OnFilePrintPreview() 
{
	ExecWB(OLECMDID_PRINTPREVIEW, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CBCGPIE7DemoView::OnFilePageSetup()
{
	ExecWB(OLECMDID_PAGESETUP, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

// This demonstrates how we can use the Navigate2() function to load local files
// including local HTML pages, GIFs, AIFF files, etc.
void CBCGPIE7DemoView::OnFileOpen()
{
	CString str;

	str.LoadString(IDS_HTML_FILETYPES);

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str);

	if(fileDlg.DoModal() == IDOK)
	{
		NavigateB (fileDlg.GetPathName(), 0, NULL);
	}	
}

void CBCGPIE7DemoView::OnFileSaveAs()
{
	ExecWB(OLECMDID_SAVEAS, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CBCGPIE7DemoView::OnFileProperties()
{
	ExecWB(OLECMDID_PROPERTIES, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CBCGPIE7DemoView::OnEditFind()
{
	ExecWB(OLECMDID_FIND, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CBCGPIE7DemoView::OnEditSelectAll()
{
	ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}
