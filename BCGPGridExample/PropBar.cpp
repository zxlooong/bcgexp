// PropBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "PropBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static TCHAR* lpszColorThemes [] = 
{
	_T("Theme 1"),
	_T("Theme 2"),
	_T("Theme 3"),
	NULL
};


/////////////////////////////////////////////////////////////////////////////
// CPropBar

CPropBar::CPropBar()
{
}

CPropBar::~CPropBar()
{
}


BEGIN_MESSAGE_MAP(CPropBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CPropBar)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropBar message handlers

void CPropBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	m_wndPropList.SetWindowPos (  NULL,
								  0, 
								  0, 
								  cx,
								  cy,
								  SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, CRect (0, 0, 0, 0), this, 1))
	{
		TRACE0("Failed to create Properies Grid \n");
		return -1;      // fail to create
	}

	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();

	return 0;
}

void CPropBar::SetContext (int nGridType)
{
	m_wndPropList.RemoveAll ();

	switch (nGridType)
	{
	case BCGGRID_BASIC:	// Basic grid
		{
/*			m_wndPropList.AddProperty (new CBCGPProp (
				_T("Vertical Lines"), 
				theApp.m_Options.m_bVerticalLines,
				_T("Vertical Lines"), idFieldChooser));*/
		}
		break;

	case BCGGRID_REPORT:	// Report control
		{
			m_wndPropList.AddProperty (new CBCGPProp (
				_T("Field Chooser"), 
				theApp.m_Options.m_bFieldChooser == TRUE,
				_T("Show Field Chooser"), idFieldChooser));

			m_wndPropList.AddProperty (new CBCGPProp (
				_T("\"Group By\" Box"), 
				theApp.m_Options.m_bGroupByBox == TRUE,
				_T("Show \"Group By\" Box"), idGroupByBox));
		}
		break;

	case BCGGRID_CELLTYPES:	// Cell types
		break;

	case BCGGRID_COLOR:		// Custom colors
		{
			CBCGPProp* pPropTheme = new CBCGPProp (
				_T("Color Theme"), 
				lpszColorThemes [0],
				_T("Choose the Color Theme"), idColorTheme);

			for (int i = 0; lpszColorThemes [i] != NULL; i++)
			{
				pPropTheme->AddOption (lpszColorThemes [i]);

				if (i == theApp.m_Options.m_nColorTheme)
				{
					pPropTheme->SetValue (lpszColorThemes [i]);
				}
			}

			pPropTheme->AllowEdit (FALSE);
			m_wndPropList.AddProperty (pPropTheme);
		}
		break;

	case BCGGRID_VIRTUAL:	// Virtual list
		break;

	default:
		ASSERT (FALSE);
	}

	m_wndPropList.RedrawWindow ();
}

LRESULT CPropBar::OnPropertyChanged (WPARAM, LPARAM lParam)
{
	CBCGPProp* pProp = (CBCGPProp*) lParam;

	switch ((int) pProp->GetData ())
	{
	case idFieldChooser:
		theApp.m_Options.m_bFieldChooser = (bool) pProp->GetValue ();
		break;

	case idGroupByBox:
		theApp.m_Options.m_bGroupByBox = (bool) pProp->GetValue ();
		break;

	case idColorTheme:
		{
			CString strTheme = (LPCTSTR) (_bstr_t)pProp->GetValue ();

			for (int i = 0; lpszColorThemes [i] != NULL; i++)
			{
				if (strTheme == lpszColorThemes [i])
				{
					theApp.m_Options.m_nColorTheme = i;
				}
			}
		}
		break;
	}

	theApp.UpdateGrid ();
	return 0;
}

void CPropBar::UpdatePropList ()
{
	CBCGPProp* pProp = m_wndPropList.FindItemByData (idFieldChooser);
	if (pProp != NULL)
	{
		pProp->SetValue (theApp.m_Options.m_bFieldChooser == TRUE);
	}
}
