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
// BCGPSkinsDoc.cpp : implementation of the CBCGPSkinsDoc class
//

#include "stdafx.h"
#include "BCGPSkins.h"

#include "BCGPSkinsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsDoc

IMPLEMENT_DYNCREATE(CBCGPSkinsDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPSkinsDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPSkinsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsDoc construction/destruction

CBCGPSkinsDoc::CBCGPSkinsDoc()
{
	// TODO: add one-time construction code here

}

CBCGPSkinsDoc::~CBCGPSkinsDoc()
{
}

BOOL CBCGPSkinsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsDoc serialization

void CBCGPSkinsDoc::Serialize(CArchive& ar)
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
// CBCGPSkinsDoc diagnostics

#ifdef _DEBUG
void CBCGPSkinsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPSkinsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsDoc commands
