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
// BCGPDBGridDemoDoc.cpp : implementation of the CBCGPDBGridDemoDoc class
//

#include "stdafx.h"
#include "BCGPDBGridDemo.h"

#include "BCGPDBGridDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoDoc

IMPLEMENT_DYNCREATE(CBCGPDBGridDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPDBGridDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPDBGridDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoDoc construction/destruction

CBCGPDBGridDemoDoc::CBCGPDBGridDemoDoc()
{
	// TODO: add one-time construction code here

}

CBCGPDBGridDemoDoc::~CBCGPDBGridDemoDoc()
{
}

BOOL CBCGPDBGridDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoDoc serialization

void CBCGPDBGridDemoDoc::Serialize(CArchive& ar)
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
// CBCGPDBGridDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPDBGridDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPDBGridDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoDoc commands
