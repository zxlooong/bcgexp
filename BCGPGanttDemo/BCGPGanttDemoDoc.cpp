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
// BCGPGanttDemoDoc.cpp : implementation of the CBCGPGanttDemoDoc class
//

#include "stdafx.h"
#include "BCGPGanttDemo.h"
#include "BCGPGanttDemoDoc.h"
#include "BCGPGanttDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoDoc

IMPLEMENT_DYNCREATE(CBCGPGanttDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPGanttDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPGanttDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoDoc construction/destruction

CBCGPGanttDemoDoc::CBCGPGanttDemoDoc()
{
	// TODO: add one-time construction code here

}

CBCGPGanttDemoDoc::~CBCGPGanttDemoDoc()
{
}

BOOL CBCGPGanttDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

    POSITION pos = GetFirstViewPosition ();
    ASSERT (pos != NULL);

    CBCGPGanttView* pView = DYNAMIC_DOWNCAST (CBCGPGanttView, GetNextView (pos));
    ASSERT_VALID (pView);

    CBCGPGanttItemStorageBase* pStorage = pView->GetChart ()->GetStorage ();
    if (pStorage != NULL)
    {
        pView->GetChart ()->GetStorage ()->RemoveAll ();

        UpdateAllViews (pView);
    }

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoDoc serialization

void CBCGPGanttDemoDoc::Serialize(CArchive& ar)
{
    POSITION pos = GetFirstViewPosition ();
    ASSERT (pos != NULL);

    CBCGPGanttView* pView = DYNAMIC_DOWNCAST (CBCGPGanttView, GetNextView (pos));
    ASSERT_VALID (pView);

    pView->GetChart ()->GetStorage ()->Serialize (ar);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPGanttDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPGanttDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoDoc commands
