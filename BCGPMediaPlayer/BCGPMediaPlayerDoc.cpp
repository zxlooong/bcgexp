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
// BCGPMediaPlayerDoc.cpp : implementation of the CBCGPMediaPlayerDoc class
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"

#include "BCGPMediaPlayerDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerDoc

IMPLEMENT_DYNCREATE(CBCGPMediaPlayerDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPMediaPlayerDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPMediaPlayerDoc)
	ON_COMMAND(ID_GOTO_BACK, OnNaviPrev)
	ON_UPDATE_COMMAND_UI(ID_GOTO_BACK, OnUpdateNaviPrev)
	ON_COMMAND(ID_GOTO_FORWARD, OnNaviNext)
	ON_UPDATE_COMMAND_UI(ID_GOTO_FORWARD, OnUpdateNaviNext)
	ON_COMMAND(ID_NAVI_STOP, OnNaviStop)
	ON_UPDATE_COMMAND_UI(ID_NAVI_STOP, OnUpdateNaviStop)
	ON_COMMAND(ID_NAVI_PLAY, OnNaviPlay)
	ON_UPDATE_COMMAND_UI(ID_NAVI_PLAY, OnUpdateNaviPlay)
	ON_COMMAND(ID_NAVI_PREV, OnNaviPrev)
	ON_UPDATE_COMMAND_UI(ID_NAVI_PREV, OnUpdateNaviPrev)
	ON_COMMAND(ID_NAVI_NEXT, OnNaviNext)
	ON_UPDATE_COMMAND_UI(ID_NAVI_NEXT, OnUpdateNaviNext)
	ON_COMMAND(ID_NAVI_SOUND, OnNaviSound)
	ON_UPDATE_COMMAND_UI(ID_NAVI_SOUND, OnUpdateDefault)
	ON_UPDATE_COMMAND_UI(ID_NAVI_VOLUME, OnUpdateDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerDoc construction/destruction

CBCGPMediaPlayerDoc::CBCGPMediaPlayerDoc()
	: m_nVolume (-1)
    , m_Navi    (e_NaviNone)
{
}

CBCGPMediaPlayerDoc::~CBCGPMediaPlayerDoc()
{
}

BOOL CBCGPMediaPlayerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerDoc serialization

void CBCGPMediaPlayerDoc::Serialize(CArchive& ar)
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
// CBCGPMediaPlayerDoc diagnostics

#ifdef _DEBUG
void CBCGPMediaPlayerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPMediaPlayerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerDoc commands

void CBCGPMediaPlayerDoc::OnNaviStop()
{
	GetMCIControl ().Stop ();
}

void CBCGPMediaPlayerDoc::OnUpdateNaviStop(CCmdUI* pCmdUI) 
{
	LONG mode  = GetMCIControl ().GetMode ();
	pCmdUI->Enable (mode == MCI_MODE_PLAY || mode == MCI_MODE_PAUSE);
}

void CBCGPMediaPlayerDoc::OnNaviPlay()
{
	if (GetMCIControl ().GetMode () == MCI_MODE_PLAY)
	{
		GetMCIControl ().Pause ();
	}
	else
	{
		GetMCIControl ().Play ();
	}
}

void CBCGPMediaPlayerDoc::OnUpdateNaviPlay(CCmdUI* pCmdUI) 
{
	LONG mode  = GetMCIControl ().GetMode ();
	pCmdUI->Enable (mode == MCI_MODE_STOP || mode == MCI_MODE_PLAY || mode == MCI_MODE_PAUSE);
}

void CBCGPMediaPlayerDoc::OnNaviPrev()
{
	m_Navi = e_NaviPrev;
	theApp.OpenDocumentFile (m_Prev.RemoveTail ());
}

void CBCGPMediaPlayerDoc::OnUpdateNaviPrev(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (m_Prev.GetCount () > 0);
}

void CBCGPMediaPlayerDoc::OnNaviNext()
{
	m_Navi = e_NaviNext;
	theApp.OpenDocumentFile (m_Next.RemoveTail ());
}

void CBCGPMediaPlayerDoc::OnUpdateNaviNext(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (m_Next.GetCount () > 0);
}

void CBCGPMediaPlayerDoc::OnNaviSound()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd ();
	if (pFrame != NULL)
	{
		LONG volume = m_nVolume;
		if (m_nVolume == -1)
		{
			m_nVolume = (LONG)GetMCIControl ().GetVolumePerc ();
		}
		else
		{
			m_nVolume = -1;
		}

		GetMCIControl ().SetVolumePerc (volume == -1 ? 0 : volume);
		pFrame->GetNavigationBar ().SetVolume (volume);
	}
}

void CBCGPMediaPlayerDoc::OnUpdateDefault(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

BOOL CBCGPMediaPlayerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	XNavi navi = m_Navi;
	m_Navi = e_NaviNone;

	if (!GetMCIControl ().Open (lpszPathName))
	{
		return FALSE;
	}

	CString strPathName = m_strPathName;

	SetModifiedFlag (FALSE);

	switch (navi)
	{
	case e_NaviNone:
		if (!strPathName.IsEmpty ())
		{
			m_Prev.AddTail (strPathName);
			m_Next.RemoveAll ();
		}
		break;
	case e_NaviPrev:
		if (!strPathName.IsEmpty ())
		{
			m_Next.AddTail (strPathName);
		}
		break;
	case e_NaviNext:
		if (!strPathName.IsEmpty ())
		{
			m_Prev.AddTail (strPathName);
		}
		break;
	}

	return TRUE;
}

CString	CBCGPMediaPlayerDoc::GetFileName () const
{
	if (m_strPathName.IsEmpty ())
	{
		return _T("");
	}

	TCHAR fname[_MAX_FNAME];   
	TCHAR ext[_MAX_EXT];

#if _MSC_VER < 1400
	_tsplitpath (m_strPathName, NULL, NULL, fname, ext);
#else
	_tsplitpath_s (m_strPathName, NULL, 0, NULL, 0, fname, _MAX_FNAME, ext, _MAX_EXT);
#endif

	CString str = fname;
	str += ext;

	return str;
}
