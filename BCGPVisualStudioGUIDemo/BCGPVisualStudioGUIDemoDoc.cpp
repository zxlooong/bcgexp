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
// BCGPVisualStudioGUIDemoDoc.cpp : implementation of the CBCGPVisualStudioGUIDemoDoc class
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"

#include "BCGPVisualStudioGUIDemoDoc.h"
#include "BCGPVisualStudioGUIDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoDoc

IMPLEMENT_DYNCREATE(CBCGPVisualStudioGUIDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPVisualStudioGUIDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPVisualStudioGUIDemoDoc)
	ON_COMMAND(ID_DUMMY_BUILD, OnDummyBuild)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_DUMMY_EXECUTE, OnDummyExecute)
	ON_COMMAND(ID_DUMMY_GO, OnDummyGo)
	ON_COMMAND(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, OnDummySelectActiveConfiguration)
	ON_COMMAND(ID_DUMMY_CLEAN, OnDummyClean)
	ON_COMMAND(ID_DUMMY_REBUILD_ALL, OnDummyRebuildAll)
	ON_COMMAND(ID_TOOLS_MACRO, OnToolsMacro)
	ON_COMMAND(ID_NEW_DIALOG, OnNewDialog)
	ON_COMMAND(ID_NEW_ACCELERATOR, OnNewAccelerator)
	ON_COMMAND(ID_NEW_BITMAP, OnNewBitmap)
	ON_COMMAND(ID_NEW_CURSOR, OnNewCursor)
	ON_COMMAND(ID_NEW_ICON, OnNewIcon)
	ON_COMMAND(ID_NEW_MENU, OnNewMenu)
	ON_COMMAND(ID_NEW_STRING_TABLE, OnNewStringTable)
	ON_COMMAND(ID_NEW_TOOLBAR, OnNewToolbar)
	ON_COMMAND(ID_NEW_VERSION, OnNewVersion)
	//}}AFX_MSG_MAP
	ON_CBN_SELENDOK(ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, OnDummySelectActiveConfiguration)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoDoc construction/destruction

CBCGPVisualStudioGUIDemoDoc::CBCGPVisualStudioGUIDemoDoc()
{
	m_bTitleMark = FALSE;
	m_uiExampleID = 0;
	m_uiExampleXMLSettingsID = 0;
}

CBCGPVisualStudioGUIDemoDoc::~CBCGPVisualStudioGUIDemoDoc()
{
}

BOOL CBCGPVisualStudioGUIDemoDoc::OnNewDocument() 
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	CommonInit ();
	return TRUE;
}

BOOL CBCGPVisualStudioGUIDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	CommonInit ();
	return TRUE;
}

void CBCGPVisualStudioGUIDemoDoc::CommonInit ()
{
	if (GetDocTemplate () == theApp.m_pDocTemplateCpp)
	{
		m_uiExampleID = ID_EXAMPLE_CPP;
		m_uiExampleXMLSettingsID = IDR_EDITOR_XML_SETTINGS_CPP;
		return;
	}

	if (GetDocTemplate () == theApp.m_pDocTemplateWeb)
	{
		m_uiExampleID = ID_EXAMPLE_WEB;
		m_uiExampleXMLSettingsID = IDR_EDITOR_XML_SETTINGS_WEB;
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoDoc serialization

void CBCGPVisualStudioGUIDemoDoc::Serialize(CArchive& ar)
{
	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CBCGPVisualStudioGUIDemoView* pView = DYNAMIC_DOWNCAST (CBCGPVisualStudioGUIDemoView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->SerializeRaw(ar);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPVisualStudioGUIDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPVisualStudioGUIDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoDoc commands

void CBCGPVisualStudioGUIDemoDoc::OnDummyBuild() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPVisualStudioGUIDemoDoc::OnDummyCompile() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPVisualStudioGUIDemoDoc::OnDummyExecute() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPVisualStudioGUIDemoDoc::OnDummyGo() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPVisualStudioGUIDemoDoc::OnDummySelectActiveConfiguration() 
{
	CBCGPToolbarComboBoxButton* pSrcCombo = NULL;

	CObList listButtons;
	if (CBCGPToolBar::GetCommandButtons (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, listButtons) > 0)
	{
		for (POSITION posCombo = listButtons.GetHeadPosition (); 
			pSrcCombo == NULL && posCombo != NULL;)
		{
			CBCGPToolbarComboBoxButton* pCombo = 
				DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton, listButtons.GetNext (posCombo));

			if (pCombo != NULL && 
				CBCGPToolBar::IsLastCommandFromButton (pCombo))
			{
				pSrcCombo = pCombo;
			}
		}
	}

	if (pSrcCombo != NULL)
	{
		ASSERT_VALID (pSrcCombo);

		LPCTSTR lpszSelItem = pSrcCombo->GetItem ();
		CString strSelItem = (lpszSelItem == NULL) ? _T("") : lpszSelItem;

		AfxMessageBox (strSelItem);
	}
	else
	{
		AfxMessageBox (_T("Show \"Set Active Configuration\" dialog...."));
	}
}

void CBCGPVisualStudioGUIDemoDoc::OnDummyClean() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPVisualStudioGUIDemoDoc::OnDummyRebuildAll() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPVisualStudioGUIDemoDoc::OnToolsMacro() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPVisualStudioGUIDemoDoc::OnNewDialog() 
{
   AfxMessageBox(_T("New Dialog"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewAccelerator() 
{
	AfxMessageBox(_T("New Accelerator"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewBitmap() 
{
	AfxMessageBox(_T("New Bitmap"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewCursor() 
{
	AfxMessageBox(_T("New Cursor"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewIcon() 
{
	AfxMessageBox(_T("New Icon"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewMenu() 
{
	AfxMessageBox(_T("New Menu"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewStringTable() 
{
	AfxMessageBox(_T("New StringTable"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewToolbar() 
{
   AfxMessageBox(_T("New Toolbar"));
}

void CBCGPVisualStudioGUIDemoDoc::OnNewVersion() 
{
	AfxMessageBox(_T("New Version"));
}

void CBCGPVisualStudioGUIDemoDoc::SetTitle(LPCTSTR lpszTitle) 
{
	CString strTitle(lpszTitle);
	
	if (IsModified())
	{
		if (!m_bTitleMark)
		{
			m_bTitleMark = TRUE;
			strTitle += _T(" *");
		}
	}
	else
	{
		if (m_bTitleMark)
		{
			strTitle.ReleaseBuffer(strTitle.GetLength() - 2);
			m_bTitleMark = FALSE;
		}
	}
	
	CDocument::SetTitle(strTitle.GetBuffer(0));
}

void CBCGPVisualStudioGUIDemoDoc::CheckTitle() 
{
	if (IsModified() ^ m_bTitleMark)
	{
		SetTitle(GetTitle());
	}	
}

