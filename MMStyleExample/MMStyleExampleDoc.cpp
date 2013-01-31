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
// MMStyleExampleDoc.cpp : implementation of the CMMStyleExampleDoc class
//

#include "stdafx.h"
#include "windowsx.h"
#include "MMStyleExample.h"
#include "MMStyleExampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc

IMPLEMENT_DYNCREATE(CMMStyleExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CMMStyleExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CMMStyleExampleDoc)
	ON_COMMAND(ID_FILE_PLAY, OnFilePlay)
	ON_UPDATE_COMMAND_UI(ID_FILE_PLAY, OnUpdateFilePlay)
	ON_COMMAND(ID_FILE_STOP, OnFileStop)
	ON_UPDATE_COMMAND_UI(ID_FILE_STOP, OnUpdateFileStop)
	ON_COMMAND(ID_FILE_PAUSE, OnFilePause)
	ON_UPDATE_COMMAND_UI(ID_FILE_PAUSE, OnUpdateFilePause)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc construction/destruction

CMMStyleExampleDoc::CMMStyleExampleDoc()
{
	m_bIsPause = FALSE;
	m_bIsPlay = FALSE;
	m_hwndMCI = NULL;
}

CMMStyleExampleDoc::~CMMStyleExampleDoc()
{
}

BOOL CMMStyleExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc serialization

void CMMStyleExampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc diagnostics

#ifdef _DEBUG
void CMMStyleExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMMStyleExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc commands

void CMMStyleExampleDoc::OnFilePlay() 
{
	m_bIsPause = FALSE;

	if (m_hwndMCI == NULL)
	{
		m_hwndMCI = MCIWndCreate (AfxGetMainWnd ()->GetSafeHwnd (),
		  AfxGetInstanceHandle(),
		  WS_CHILD | MCIWNDF_NOMENU | MCIWNDF_NOTIFYMODE, m_strPath);
		if (m_hwndMCI == NULL)
		{
			return;
		}
	}
	else
	{
		MCIWndHome (m_hwndMCI);
	}

	LONG lRC = MCIWndPlay (m_hwndMCI);

	if (lRC == 0)
	{
		m_bIsPlay = TRUE;
		UpdateAllViews (NULL, MMS_PLAY);
	}
}

void CMMStyleExampleDoc::OnUpdateFilePlay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (!m_bIsPlay && !m_strPath.IsEmpty ());
}

void CMMStyleExampleDoc::OnFileStop() 
{
	MCIWndStop (m_hwndMCI);
	Stop ();
}

void CMMStyleExampleDoc::OnUpdateFileStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_bIsPlay);
}

void CMMStyleExampleDoc::OnFilePause() 
{
	if (m_bIsPause)
	{
		MCIWndResume (m_hwndMCI);
		m_bIsPause = FALSE;
	}
	else
	{
		MCIWndPause (m_hwndMCI);
		m_bIsPause = TRUE;
	}

	UpdateAllViews (NULL, MMS_PAUSE);
}

void CMMStyleExampleDoc::OnUpdateFilePause(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_bIsPlay);
}

BOOL CMMStyleExampleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	m_strPath.Empty ();

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	Stop ();

	m_strPath = lpszPathName;
	
	UpdateAllViews (NULL, MMS_OPEN);
	return TRUE;
}

void CMMStyleExampleDoc::OnCloseDocument() 
{
	Stop ();
	CDocument::OnCloseDocument();
}

void CMMStyleExampleDoc::Stop ()
{
	if (m_hwndMCI != NULL)
	{
		MCIWndClose (m_hwndMCI);
	}

	m_hwndMCI = NULL;

	m_bIsPause = FALSE;
	m_bIsPlay = FALSE;

	UpdateAllViews (NULL, MMS_STOP);
}

long CMMStyleExampleDoc::GetTotal () const
{
	if (m_hwndMCI == NULL)
	{
		return 0;
	}

	return MCIWndGetLength (m_hwndMCI);
}

long CMMStyleExampleDoc::GetCurrent () const
{
	if (m_hwndMCI == NULL)
	{
		return 0;
	}

	return MCIWndGetPosition (m_hwndMCI);
}

CString	CMMStyleExampleDoc::GetSong () const
{
	if (m_strPath.IsEmpty ())
	{
		return _T("");
	}

	TCHAR fname[_MAX_FNAME];   
	TCHAR ext[_MAX_EXT];

#if _MSC_VER < 1400
	_tsplitpath (m_strPath, NULL, NULL, fname, ext);
#else
	_tsplitpath_s (m_strPath, NULL, 0, NULL, 0, fname, _MAX_FNAME, ext, _MAX_EXT);
#endif

	CString str = fname;
	str += ext;

	return str;
}
