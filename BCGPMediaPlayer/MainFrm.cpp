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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_VIEW_COLOR_CHOOSER, OnViewColorChooser)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COLOR_CHOOSER, OnUpdateViewColorChooser)
	ON_COMMAND(ID_VIEW_EQUALIZER, OnViewEqualizer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EQUALIZER, OnUpdateViewEqualizer)
	ON_COMMAND(IDC_CH_RESET, OnColorChooserReset)
	ON_COMMAND(IDC_CH_PRESET_PREV, OnColorChooserPresetPrev)
	ON_COMMAND(IDC_CH_PRESET_NEXT, OnColorChooserPresetNext)
	ON_COMMAND(ID_EXPLORER_WEB, OnExplorerWeb)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DWMCOMPOSITIONCHANGED, OnDWMCompositionChanged)
	ON_REGISTERED_MESSAGE(BCGM_ONAFTERUPDATECAPTION, OnAfterUpdateCaption)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetMenu (NULL);

	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CVisualManager));
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	//------------------------
	// Create the address bar:
	//------------------------
	m_wndExplorerBar.EnableNavigationButtons (ID_GOTO_BACK, ID_GOTO_FORWARD, 0, 0);

	if (!m_wndExplorerBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("Failed to create address bar\n");
		return -1;      // fail to create
	}

	m_wndExplorerBar.CreateButtons ();

	//---------------------------
	// Create the navigation bar:
	//---------------------------
	if (!m_wndNavigationBar.Create (this, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("Failed to create navigation bar\n");
		return -1;      // fail to create
	}

	m_wndNavigationBar.CreateButtons ();
	m_wndNavigationBar.DWMCompositionChanged ();

	if (!m_wndColorChooserBar.Create (_T("Color Chooser"), this, FALSE, MAKEINTRESOURCE(CColorChooserBar::IDD), 
		CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_ALIGN_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY, AFX_IDW_DIALOGBAR + 1,
		CBRS_BCGP_REGULAR_TABS, CBRS_BCGP_FLOAT | CBRS_BCGP_CLOSE | CBRS_BCGP_RESIZE | CBRS_BCGP_AUTOHIDE))

	{
		TRACE0("Failed to create color chooser bar\n");
		return -1;      // fail to create
	}

	if (!m_wndEqualizerBar.Create (_T("Graphic Equalizer"), this, FALSE, MAKEINTRESOURCE(CEqualizerBar::IDD), 
		CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_ALIGN_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY, AFX_IDW_DIALOGBAR + 2,
		CBRS_BCGP_REGULAR_TABS, CBRS_BCGP_FLOAT | CBRS_BCGP_CLOSE | CBRS_BCGP_RESIZE | CBRS_BCGP_AUTOHIDE))

	{
		TRACE0("Failed to create equalizer bar\n");
		return -1;      // fail to create
	}

	EnableDocking (CBRS_ALIGN_ANY);

	AddControlBar (&m_wndNavigationBar);

	m_wndColorChooserBar.EnableDocking (CBRS_ALIGN_ANY);
	m_wndEqualizerBar.EnableDocking (CBRS_ALIGN_ANY);
	
	DockControlBar (&m_wndColorChooserBar);
	m_wndEqualizerBar.DockToWindow (&m_wndColorChooserBar, CBRS_ALIGN_BOTTOM);

	ShowControlBar (&m_wndColorChooserBar, TRUE, FALSE, FALSE);
	ShowControlBar (&m_wndEqualizerBar, TRUE, FALSE, FALSE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style |= FWS_ADDTOTITLE;
	cs.style &= ~FWS_PREFIXTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


LRESULT CMainFrame::OnDWMCompositionChanged(WPARAM,LPARAM)
{
	m_wndNavigationBar.DWMCompositionChanged ();
	return Default ();
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CFrameWnd::OnGetMinMaxInfo(lpMMI);

	lpMMI->ptMinTrackSize.x = 300;
	lpMMI->ptMinTrackSize.y = 200;
}

void CMainFrame::OnViewColorChooser() 
{
	ShowControlBar (&m_wndColorChooserBar, !m_wndColorChooserBar.IsVisible (), FALSE, FALSE);
}

void CMainFrame::OnUpdateViewColorChooser(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndColorChooserBar.IsVisible ());
}

void CMainFrame::OnViewEqualizer() 
{
	ShowControlBar (&m_wndEqualizerBar, !m_wndEqualizerBar.IsVisible (), FALSE, FALSE);
}

void CMainFrame::OnUpdateViewEqualizer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndEqualizerBar.IsVisible ());
}

LRESULT CMainFrame::OnAfterUpdateCaption(WPARAM, LPARAM)
{
	GetVisualManager ()->OnUpdateCaptionButtons (m_Impl.GetCaptionRect (), m_Impl.GetCaptionSysButtons (), this);
	return 0L;
}

void CMainFrame::OnColorChooserReset() 
{
	m_wndColorChooserBar.Reset ();
}

void CMainFrame::OnColorChooserPresetPrev() 
{
	m_wndColorChooserBar.Preset (FALSE);
}

void CMainFrame::OnColorChooserPresetNext() 
{
	m_wndColorChooserBar.Preset (TRUE);
}

void CMainFrame::OnExplorerWeb() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
}
