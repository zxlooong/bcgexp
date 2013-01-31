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
// UndoBar.cpp : implementation file
//

#include "stdafx.h"
#include "UndoBar.h"

#include "BCGPVisualStudioGUIDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CUndoBar, CBCGPPopupMenuBar, 1)

const int ID_LIST = 1;

/////////////////////////////////////////////////////////////////////////////
// CUndoBar

#pragma warning(disable: 4355)
CUndoBar::CUndoBar() :
	m_wndList (*this),
	m_nLabelHeight (0)
#pragma warning(default: 4355)
{
	m_rectLabel.SetRectEmpty ();
}

CUndoBar::~CUndoBar()
{
}


BEGIN_MESSAGE_MAP(CUndoBar, CBCGPPopupMenuBar)
	//{{AFX_MSG_MAP(CUndoBar)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUndoBar message handlers

void CUndoBar::OnFillBackground (CDC* pDC)
{
	ASSERT_VALID (pDC);

	CRect rectClient;
	GetClientRect (rectClient);

	pDC->FillRect (rectClient, &globalData.brBarFace);

	// Draw label:
	pDC->Draw3dRect (m_rectLabel, globalData.clrBarShadow, globalData.clrBarHilite);

	CFont* pOldFont = pDC->SelectObject ((CFont*) &CBCGPMenuBar::GetMenuFont ());
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (globalData.clrBarText);

	CRect rectText = m_rectLabel;
	rectText.DeflateRect (1, 1);
	pDC->DrawText (m_strLabel, rectText, DT_CENTER | DT_VCENTER);

	pDC->SelectObject (pOldFont);
}

CSize CUndoBar::CalcSize (BOOL /*bVertDock*/)
{
	return CSize (160, 115);
}

CUndoButton* CUndoBar::GetParentButton () const
{
	// Get parent button:
	CUndoButton* pUndoButton = NULL;

	CUndoMenu* pParentMenu = DYNAMIC_DOWNCAST (CUndoMenu, GetParent ());
	if (pParentMenu != NULL)
	{
		pUndoButton = DYNAMIC_DOWNCAST (CUndoButton, pParentMenu->GetParentButton ());
	}

	return pUndoButton;
}

void CUndoBar::OnSize(UINT nType, int cx, int cy) 
{
	const int nMargin = 5;

	CBCGPPopupMenuBar::OnSize(nType, cx, cy);
	
	CRect rectClient;
	GetClientRect (rectClient);

	rectClient.DeflateRect (nMargin, nMargin);

	m_rectLabel = rectClient;
	m_rectLabel.top = m_rectLabel.bottom - m_nLabelHeight;

	CRect rectList = rectClient;
	rectList.bottom = m_rectLabel.top - nMargin;

	m_wndList.MoveWindow (rectList);
}

int CUndoBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPPopupMenuBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CFont* pMenuFont = (CFont*) &CBCGPMenuBar::GetMenuFont ();

	//------------------
	// Set label height:
	//------------------
	CClientDC dc (this);
	CFont* pOldFont = dc.SelectObject (pMenuFont);

	TEXTMETRIC tm;
	dc.GetTextMetrics (&tm);

	m_nLabelHeight = tm.tmHeight + 2;

	dc.SelectObject (pOldFont);

	CRect rectDummy (0, 0, 0, 0);
	m_wndList.Create (WS_VISIBLE | WS_CHILD | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | WS_VSCROLL | LBS_MULTIPLESEL, 
						rectDummy, this, ID_LIST);
	m_wndList.ModifyStyleEx (0, WS_EX_CLIENTEDGE);

	m_wndList.SetFont (pMenuFont);

	CUndoButton* pUndoButton = GetParentButton ();
	ASSERT_VALID (pUndoButton);

	for (POSITION pos = pUndoButton->m_lstActions.GetHeadPosition (); pos != NULL;)
	{
		m_wndList.AddString (pUndoButton->m_lstActions.GetNext (pos));
	}

	return 0;
}

void CUndoBar::DoUndo ()
{
	CUndoButton* pUndoButton = GetParentButton ();
	ASSERT_VALID (pUndoButton);

	pUndoButton->m_nSelNum = m_wndList.GetSelCount () + 1;
	
	CMDIChildWnd* pChildFrame = ((CMDIFrameWnd*)GetTopLevelFrame())->MDIGetActive();

	if (pChildFrame)
	{
		CView* pView = pChildFrame->GetActiveView();

		if (pView &&
			pView->IsKindOf(RUNTIME_CLASS(CBCGPVisualStudioGUIDemoView)))
		{
			((CBCGPVisualStudioGUIDemoView*)pView)->DoUndo(pUndoButton);
		}
		else
		{
			ASSERT(FALSE);
		}
	}
	else
	{
		ASSERT(FALSE);
	}

	GetParent ()->PostMessage (WM_CLOSE);
}

void CUndoBar::SetLabel (const CString& strLabel)
{
	m_strLabel = strLabel;

	if (GetSafeHwnd () != NULL)
	{
		InvalidateRect (m_rectLabel);
		UpdateWindow ();
	}
}

//////////////////////////////////////////////////////////////////////////////
// CUndoButton

IMPLEMENT_SERIAL(CUndoButton, CBCGPToolbarMenuButton, 1)

CBCGPPopupMenu* CUndoButton::CreatePopupMenu ()
{
	if (CBCGPToolBar::IsCustomizeMode () || (m_nStyle & TBBS_DISABLED))
	{
		return NULL;
	}

	CUndoMenu* pPopupMenu = new CUndoMenu;

	ResetSelNum();

	CMDIChildWnd* pChildFrame = ((CMDIFrameWnd*)::AfxGetMainWnd())->MDIGetActive();

	if (pChildFrame)
	{
		CBCGPVisualStudioGUIDemoView* pView = (CBCGPVisualStudioGUIDemoView*)pChildFrame->GetActiveView();

		if (pView &&
			pView->IsKindOf(RUNTIME_CLASS(CBCGPVisualStudioGUIDemoView)))
		{
			CDWordArray dwaUAT;
			
			//	Setup undo actions:
			switch (m_nID)
			{
			case ID_EDIT_UNDO:
				pView->GetUndoActions(m_lstActions);

				break;
			case ID_EDIT_REDO:
				pView->GetRedoActions(m_lstActions);

				break;
			default:
				break;
			}
		}
		else
		{
			ASSERT(FALSE);
			m_lstActions.RemoveAll();
		}
	}
	else
	{
		ASSERT(FALSE);
		m_lstActions.RemoveAll();
	}

	return pPopupMenu;
}

//////////////////////////////////////////////////////////////////////////////
// CUndoMenu

IMPLEMENT_SERIAL(CUndoMenu, CBCGPPopupMenu, 1)

BEGIN_MESSAGE_MAP(CUndoMenu, CBCGPPopupMenu)
	//{{AFX_MSG_MAP(CUndoMenu)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CUndoMenu::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DWORD toolbarStyle = dwDefaultToolbarStyle;
	if (m_AnimationType != NO_ANIMATION && !CBCGPToolBar::IsCustomizeMode ())
	{
		toolbarStyle &= ~WS_VISIBLE;
	}

	if (!m_wndUndoBar.Create (this, toolbarStyle | CBRS_TOOLTIPS | CBRS_FLYBY, 1))
	{
		TRACE(_T("Can't create popup menu bar\n"));
		return -1;
	}

	CWnd* pWndParent = GetParent ();
	ASSERT_VALID (pWndParent);

	m_wndUndoBar.SetOwner (pWndParent);
	m_wndUndoBar.SetBarStyle(m_wndUndoBar.GetBarStyle() | CBRS_TOOLTIPS);

	ActivatePopupMenu (BCGCBProGetTopLevelFrame (pWndParent), this);
	RecalcLayout ();

	return 0;
}

