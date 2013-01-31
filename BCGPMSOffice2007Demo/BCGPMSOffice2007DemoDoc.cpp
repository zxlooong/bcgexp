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
// BCGPMSOffice2007DemoDoc.cpp : implementation of the CBCGPMSOffice2007DemoDoc class
//

#include "stdafx.h"
#include "BCGPMSOffice2007Demo.h"

#include "BCGPMSOffice2007DemoDoc.h"
#include "CntrItem.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoDoc

IMPLEMENT_DYNCREATE(CBCGPMSOffice2007DemoDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CBCGPMSOffice2007DemoDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CBCGPMSOffice2007DemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_CLOSE, OnClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoDoc construction/destruction

CBCGPMSOffice2007DemoDoc::CBCGPMSOffice2007DemoDoc()
{
	// TODO: add one-time construction code here

}

CBCGPMSOffice2007DemoDoc::~CBCGPMSOffice2007DemoDoc()
{
}

BOOL CBCGPMSOffice2007DemoDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CBCGPMSOffice2007DemoDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	CRichEditDoc::SetPathName(lpszPathName, bAddToMRU);
}

CRichEditCntrItem* CBCGPMSOffice2007DemoDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CBCGPMSOffice2007DemoCntrItem(preo, (CBCGPMSOffice2007DemoDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoDoc serialization

void CBCGPMSOffice2007DemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoDoc diagnostics

#ifdef _DEBUG
void CBCGPMSOffice2007DemoDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CBCGPMSOffice2007DemoDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

void CBCGPMSOffice2007DemoDoc::OnClose()
{
}


/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoDoc commands
