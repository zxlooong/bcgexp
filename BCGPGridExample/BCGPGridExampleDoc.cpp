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
// BCGPGridExampleDoc.cpp : implementation of the CBCGPGridExampleDoc class
//

#include "stdafx.h"
#include "BCGPGridExample.h"

#include "BCGPGridExampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleDoc

IMPLEMENT_DYNCREATE(CBCGPGridExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPGridExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPGridExampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleDoc construction/destruction

CBCGPGridExampleDoc::CBCGPGridExampleDoc()
{
	// TODO: add one-time construction code here

}

CBCGPGridExampleDoc::~CBCGPGridExampleDoc()
{
}

BOOL CBCGPGridExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleDoc serialization

void CBCGPGridExampleDoc::Serialize(CArchive& ar)
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
// CBCGPGridExampleDoc diagnostics

#ifdef _DEBUG
void CBCGPGridExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPGridExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleDoc commands
