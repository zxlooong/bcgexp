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
// BCGPShopDemoDoc.cpp : implementation of the CBCGPShopDemoDoc class
//

#include "stdafx.h"
#include "BCGPShopDemo.h"

#include "BCGPShopDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoDoc

IMPLEMENT_DYNCREATE(CBCGPShopDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPShopDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPShopDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoDoc construction/destruction

CBCGPShopDemoDoc::CBCGPShopDemoDoc()
    : m_szDocSize(496, 649)
{
	// TODO: add one-time construction code here

}

CBCGPShopDemoDoc::~CBCGPShopDemoDoc()
{
}

BOOL CBCGPShopDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoDoc serialization

void CBCGPShopDemoDoc::Serialize(CArchive& ar)
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
// CBCGPShopDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPShopDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPShopDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoDoc commands
