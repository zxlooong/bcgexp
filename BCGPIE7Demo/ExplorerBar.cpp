//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// WorkspaceBar.cpp : implementation of the CExplorerBar class
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "ExplorerBar.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT idTree = 1;
const UINT idTreeTool = 101;
const int nBorderSize = 1;

IMPLEMENT_DYNAMIC(CExplorerTreeCtrl, CTreeCtrl)

BEGIN_MESSAGE_MAP(CExplorerTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CExplorerTreeCtrl)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CExplorerTreeCtrl::CExplorerTreeCtrl()
	: m_pToolTip  (NULL)
	, m_hToolItem (NULL)
	, m_bFavorites(FALSE)
{
}

CExplorerTreeCtrl::~CExplorerTreeCtrl()
{
}

void CExplorerTreeCtrl::OnDestroy()
{
	if (m_pToolTip != NULL)
	{
		CBCGPTooltipManager::DeleteToolTip (m_pToolTip);
		m_pToolTip = NULL;
	}

	CTreeCtrl::OnDestroy ();
}

int CExplorerTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate (lpCreateStruct) == -1)
	{
		return -1;
	}

	if (CBCGPTooltipManager::CreateToolTip (m_pToolTip, this, BCGP_TOOLTIP_TYPE_DEFAULT))
	{
		m_pToolTip->Activate (FALSE);
		m_pToolTip->AddTool (this, _T(""));
		m_pToolTip->SetMaxTipWidth (150);
		m_pToolTip->SetWindowPos (&wndTop, -1, -1, -1, -1,
								SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return TRUE;
}

BOOL CExplorerTreeCtrl::PreTranslateMessage(MSG* pMsg)
{
	if (m_pToolTip->GetSafeHwnd () != NULL)
	{
		m_pToolTip->RelayEvent (pMsg);
	}

	return CTreeCtrl::PreTranslateMessage (pMsg);
}

BOOL CExplorerTreeCtrl::PreCreateWindow (CREATESTRUCT& cs)
{
	cs.style &= ~TVS_INFOTIP;
	cs.style |= TVS_NOTOOLTIPS;

	return CTreeCtrl::PreCreateWindow (cs);
}

void CExplorerTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	static CString c_strToolTip;

	CTreeCtrl::OnMouseMove(nFlags, point);

	if (m_pToolTip->GetSafeHwnd () != NULL)
	{
		CString str;

		HTREEITEM hItem = HitTest (point);
		if (hItem != NULL && !ItemHasChildren (hItem))
		{
			DWORD dwData = (DWORD)GetItemData (hItem);
			if (dwData != 0)
			{
				if (m_bFavorites)
				{
					str = ((CFavorit*)dwData)->GetURL ();
				}
				else
				{
					str = ((CHistoryObj*)dwData)->GetURL ();
				}
			}
		}

		if (str.IsEmpty ())
		{
			hItem = NULL;
		}
		else
		{
			const int maxlen = 41;
			if (str.GetLength () > maxlen + 3)
			{
				str = str.Left (maxlen);
				str += _T("...");
			}
		}

		if (m_hToolItem != hItem)
		{
			c_strToolTip = str;

			m_hToolItem = hItem;
			m_pToolTip->Pop ();
			m_pToolTip->UpdateTipText (c_strToolTip, this);
			m_pToolTip->Activate (!c_strToolTip.IsEmpty ());
		}	
	}
}


/////////////////////////////////////////////////////////////////////////////
// CExplorerBar

BEGIN_MESSAGE_MAP(CExplorerBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CExplorerBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_FAVORITES, OnFavorites)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FAVORITES, OnUpdateFavorites)
	ON_COMMAND(ID_VIEW_HISTORY, OnHistory)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HISTORY, OnUpdateHistory)
	ON_NOTIFY(TVN_SELCHANGED, idTree, OnSelectTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExplorerBar construction/destruction

CExplorerBar::CExplorerBar()
	: m_bFavorites (TRUE)
{
}

CExplorerBar::~CExplorerBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CExplorerBar message handlers

int CExplorerBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tree windows.
	// TODO: create your own tab windows here:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | 
								TVS_LINESATROOT | TVS_DISABLEDRAGDROP | 
								TVS_TRACKSELECT | TVS_FULLROWSELECT | 
								TVS_SINGLEEXPAND;
	
	if (!m_wndTree.Create (dwViewStyle, rectDummy, this, idTree))
	{
		TRACE0("Failed to create workspace view\n");
		return -1;      // fail to create
	}
	
	m_wndToolBar.Create (this, dwDefaultToolbarStyle, IDR_EXPLORER_BAR);
	m_wndToolBar.LoadToolBar (IDR_EXPLORER_BAR, 0, 0, TRUE /* Is locked */);


	OnChangeVisualStyle ();

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetBarStyle (
		m_wndToolBar.GetBarStyle () & 
			~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_VIEW_FAVORITES), _T("Favorites"));
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_VIEW_HISTORY), _T("History"));

	m_wndToolBar.SetOwner (this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame (FALSE);

	AdjustLayout ();

	if (m_bFavorites)
	{
		FillFavorites ();
	}
	else
	{
		FillHistory ();
	}

	return 0;
}

void CExplorerBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void CExplorerBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTree;
	m_wndTree.GetWindowRect (rectTree);
	ScreenToClient (rectTree);

	rectTree.InflateRect (nBorderSize, nBorderSize);
	dc.Draw3dRect (rectTree,	::GetSysColor (COLOR_3DSHADOW), 
								::GetSysColor (COLOR_3DSHADOW));
}

void CExplorerBar::AdjustLayout ()
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
	m_wndTree.SetWindowPos (NULL, rectClient.left + 1, rectClient.top + cyTlb + 1,
								rectClient.Width () - 2, rectClient.Height () - cyTlb - 2,
								SWP_NOACTIVATE | SWP_NOZORDER);
}

void CExplorerBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	
	m_wndTree.SetFocus ();
}

void CExplorerBar::OnChangeVisualStyle ()
{
	m_wndToolBar.CleanUpLockedImages ();
	m_wndToolBar.LoadBitmap 
		(
			theApp.m_nColorMode >= 16
				? IDR_EXPLORER_BAR_32
				: theApp.m_nColorMode >= 8 
					? IDR_EXPLORER_BAR_256
					: IDR_EXPLORER_BAR, 
			0, 0, TRUE
		);

	if (m_ilTree.GetSafeHandle () != NULL)
	{
		m_ilTree.DeleteImageList ();
	}

	UINT uiBmpId = theApp.m_nColorMode < 8 ? 
		IDB_EXPLORER_ICONS : IDB_EXPLORER_ICONS_256;

	CBitmap bmp;
	if (!bmp.LoadBitmap (uiBmpId))
	{
		TRACE(_T ("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT (FALSE);
		return;
	}

	UINT nFlags = ILC_MASK;
	nFlags |= theApp.m_nColorMode < 8 ? ILC_COLOR4 : ILC_COLOR8;

	m_ilTree.Create (16, 16, nFlags, 0, 0);
	m_ilTree.Add (&bmp, RGB (255, 0, 255));

	if (!m_bFavorites)
	{
		m_wndTree.SetImageList (&m_ilTree, TVSIL_NORMAL);
	}
}

CSize CExplorerBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CSize size = CBCGPDockingControlBar::CalcFixedLayout (bStretch, bHorz);

	size.cx = min (size.cx, 450);

	return size;
}

void CExplorerBar::FillFavorites ()
{
	m_wndTree.SetRedraw (FALSE);
	m_wndTree.DeleteAllItems ();
	theApp.m_Favorites.FillTree (m_wndTree);
	m_wndTree.SetRedraw (TRUE);
}

void CExplorerBar::FillHistory ()
{
	m_wndTree.SetRedraw (FALSE);
	m_wndTree.DeleteAllItems ();
	m_wndTree.SetImageList (&m_ilTree, TVSIL_NORMAL);
	theApp.m_History.FillTree (m_wndTree);
	m_wndTree.SetRedraw (TRUE);
}

void CExplorerBar::OnFavorites ()
{
	if (!m_bFavorites)
	{
		m_bFavorites = TRUE;
		FillFavorites ();
		m_wndTree.SetFavorites (m_bFavorites);
	}
}

void CExplorerBar::OnUpdateFavorites (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (m_bFavorites);
}

void CExplorerBar::OnHistory ()
{
	if (m_bFavorites)
	{
		m_bFavorites = FALSE;
		FillHistory ();
		m_wndTree.SetFavorites (m_bFavorites);
	}
}

void CExplorerBar::OnUpdateHistory (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (!m_bFavorites);
}

void CExplorerBar::OnSelectTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;

	LPNMTREEVIEW pNMTree = (LPNMTREEVIEW)pNMHDR;

	if (pNMTree == NULL || (pNMTree->action != TVC_BYMOUSE && pNMTree->action != TVC_BYKEYBOARD))
	{
		return;
	}

	HTREEITEM hTreeItem = m_wndTree.GetSelectedItem ();
	if (hTreeItem != NULL)
	{
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
		ASSERT_VALID (pFrame);

		if (m_bFavorites)
		{
			CFavorit* pFavorit = (CFavorit*) m_wndTree.GetItemData (hTreeItem);
			if (pFavorit != NULL && !pFavorit->GetURL ().IsEmpty ())
			{
				pFrame->Navigate (pFavorit->GetURL ());
			}
		}
		else
		{
			CHistoryObj* pHistory = (CHistoryObj*) m_wndTree.GetItemData (hTreeItem);
			if (pHistory != NULL && pHistory->GetURL () != NULL)
			{
				pFrame->Navigate (pHistory->GetURL ());
			}
		}
	}	
}
