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
// FileViewBar.cpp: implementation of the CFileViewBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "mainfrm.h"
#include "FileViewBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileViewBar

CFileViewBar::CFileViewBar()
{
}

CFileViewBar::~CFileViewBar()
{
}


BEGIN_MESSAGE_MAP(CFileViewBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CFileViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_SOLUTION_OPEN, OnSolutionOpen)
	ON_COMMAND(ID_SOLUTION_OPEN_WITH, OnSolutionOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CFileViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create view:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS;
	
	if (!m_wndFileView.Create (dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create solution explorer\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_FileViewImages.Create (IDB_FILE_VIEW, 16, 0, RGB (255, 0, 255));
	m_wndFileView.SetImageList (&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create (this, dwDefaultToolbarStyle, IDR_SOLUTION_EXPLORER);
	m_wndToolBar.LoadToolBar (IDR_SOLUTION_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle ();

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
		
	m_wndToolBar.SetBarStyle (
		m_wndToolBar.GetBarStyle () & 
			~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner (this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame (FALSE);

	// Fill view context (dummy code, don't seek here something magic :-)):

	FillFileView ();
	AdjustLayout ();

	return 0;
}

void CFileViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void CFileViewBar::FillFileView ()
{
	HTREEITEM hRoot = m_wndFileView.InsertItem (_T("HelloBCG files"), 0, 0);
	m_wndFileView.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSrc = m_wndFileView.InsertItem (_T("Source Files"), 0, 0, hRoot);

	m_wndFileView.InsertItem (_T("HelloBCG.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem (_T("HelloBCG.rc"), 1, 1, hSrc);
	m_wndFileView.InsertItem (_T("HelloBCGDoc.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem (_T("HelloBCGView.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem (_T("MainFrm.cpp"), 1, 1, hSrc);
	m_wndFileView.InsertItem (_T("StdAfx.cpp"), 1, 1, hSrc);

	HTREEITEM hInc = m_wndFileView.InsertItem (_T("Header Files"), 0, 0, hRoot);

	m_wndFileView.InsertItem (_T("HelloBCG.h"), 2, 2, hInc);
	m_wndFileView.InsertItem (_T("HelloBCGDoc.h"), 2, 2, hInc);
	m_wndFileView.InsertItem (_T("HelloBCGView.h"), 2, 2, hInc);
	m_wndFileView.InsertItem (_T("resource.h"), 2, 2, hInc);
	m_wndFileView.InsertItem (_T("MainFrm.h"), 2, 2, hInc);
	m_wndFileView.InsertItem (_T("StdAfx.h"), 2, 2, hInc);

	HTREEITEM hRes = m_wndFileView.InsertItem (_T("Resource Files"), 0, 0, hRoot);

	m_wndFileView.InsertItem (_T("HelloBCG.ico"), 2, 2, hRes);
	m_wndFileView.InsertItem (_T("HelloBCG.rc2"), 2, 2, hRes);
	m_wndFileView.InsertItem (_T("HelloBCGDoc.ico"), 2, 2, hRes);
	m_wndFileView.InsertItem (_T("Toolbar.bmp"), 2, 2, hRes);

	m_wndFileView.Expand (hRoot, TVE_EXPAND);
	m_wndFileView.Expand (hSrc, TVE_EXPAND);
	m_wndFileView.Expand (hInc, TVE_EXPAND);
}

void CFileViewBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID (pWndTree);

	if (pWnd != pWndTree)
	{
		CBCGPDockingControlBar::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint (-1, -1))
	{
		//---------------------
		// Select clicked item:
		//---------------------
		CPoint ptTree = point;
		pWndTree->ScreenToClient (&ptTree);

		HTREEITEM hTreeItem = pWndTree->HitTest (ptTree);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem (hTreeItem);
		}
	}

	pWndTree->SetFocus ();
	theApp.GetContextMenuManager ()->ShowPopupMenu (IDR_POPUP_SOLUTION,
		point.x, point.y, this, TRUE);
}

void CFileViewBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout (FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos (NULL, rectClient.left, rectClient.top, 
								rectClient.Width (), cyTlb,
								SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos (NULL, rectClient.left + 1, rectClient.top + cyTlb + 1,
								rectClient.Width () - 2, rectClient.Height () - cyTlb - 2,
								SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileViewBar::OnProperties() 
{
	AfxMessageBox (_T("Properties...."));
	
}

void CFileViewBar::OnSolutionOpen() 
{
	// TODO: Add your command handler code here
	
}

void CFileViewBar::OnSolutionOpenWith() 
{
	// TODO: Add your command handler code here
	
}

void CFileViewBar::OnDummyCompile() 
{
	// TODO: Add your command handler code here
	
}

void CFileViewBar::OnEditCut() 
{
	// TODO: Add your command handler code here
	
}

void CFileViewBar::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CFileViewBar::OnEditClear() 
{
	// TODO: Add your command handler code here
	
}

void CFileViewBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTree;
	m_wndFileView.GetWindowRect (rectTree);
	ScreenToClient (rectTree);

	rectTree.InflateRect (1, 1);
	dc.Draw3dRect (rectTree, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DSHADOW));
}

void CFileViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	
	m_wndFileView.SetFocus ();
	
}

void CFileViewBar::OnChangeVisualStyle ()
{
	m_wndToolBar.CleanUpLockedImages ();
	m_wndToolBar.LoadBitmap (theApp.m_bHiColorIcons ? 
		IDB_SOLUTION_EXPLORER_HC : IDR_SOLUTION_EXPLORER, 0, 0, TRUE /* Locked */);

	m_FileViewImages.DeleteImageList ();

	UINT uiBmpId = theApp.m_bHiColorIcons ? 
		IDB_FILE_VIEW_HC : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap (uiBmpId))
	{
		TRACE(_T ("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT (FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap (&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create (16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add (&bmp, RGB (255, 0, 255));

	m_wndFileView.SetImageList (&m_FileViewImages, TVSIL_NORMAL);
}
