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
// BCGPDBGridDemoView.cpp : implementation of the CBCGPDBGridDemoView class
//

#include "stdafx.h"
#include "BCGPDBGridDemo.h"

#include "BCGPDBGridDemoDoc.h"
#include "BCGPDBGridDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_GRIDCTRL 1

/////////////////////////////////////////////////////////////////////////////

BOOL CMyODBCGridCtrl::OnGetPageHeaderRect (CDC* /*pDC*/, CPrintInfo* pInfo, CRect& rect)
{
	ASSERT (pInfo != NULL);

	int nHeaderHeight = 200;
	rect = pInfo->m_rectDraw;
	rect.bottom = rect.top + nHeaderHeight;

	return TRUE;
}

BOOL CMyODBCGridCtrl::OnGetPageFooterRect (CDC* /*pDC*/, CPrintInfo* pInfo, CRect& rect)
{
	ASSERT (pInfo != NULL);

	int nFooterHeight = 200;
	rect = pInfo->m_rectDraw;
	rect.top = rect.bottom - nFooterHeight;

	return TRUE;
}

void CMyODBCGridCtrl::OnPrintPageHeader(CDC* pDC, CPrintInfo* pInfo)
{
	CRect rectHeader;
	BOOL bPageHeader = OnGetPageHeaderRect (pDC, pInfo, rectHeader);

	CBCGPODBCGridCtrl::OnPrintPageHeader(pDC, pInfo);

	if (bPageHeader)
	{
		// Draw header:
		pDC->FillSolidRect (rectHeader, RGB(245,245,245));

		CString str = _T("Header: ");

		CString s;
		if (AfxExtractSubString(s, pInfo->m_strPageDesc, 0))
		{
			TCHAR szBuf[80];
			wsprintf(szBuf, s, pInfo->m_nCurPage);
			str += szBuf;
		}

		pDC->DrawText (str, rectHeader, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

void CMyODBCGridCtrl::OnPrintPageFooter(CDC* pDC, CPrintInfo* pInfo)
{
	CRect rectFooter;
	BOOL bPageFooter = OnGetPageFooterRect (pDC, pInfo, rectFooter);

	CBCGPODBCGridCtrl::OnPrintPageFooter(pDC, pInfo);

	if (bPageFooter)
	{
		// Draw footer:
		pDC->FillSolidRect (rectFooter, RGB(245,245,245));

		CString str;
		str.Format (_T("Footer: page #%u"), pInfo->m_nCurPage);

		pDC->DrawText (str, rectFooter, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoView

//tmp
UINT BCGM_ITEM_CHANGED = ::RegisterWindowMessage (_T("BCGM_ITEM_CHANGED"));

IMPLEMENT_DYNCREATE(CBCGPDBGridDemoView, CBCGPGridView)

BEGIN_MESSAGE_MAP(CBCGPDBGridDemoView, CBCGPGridView)
	//{{AFX_MSG_MAP(CBCGPDBGridDemoView)
	ON_COMMAND(ID_VIEW_FIELDCHOOSER, OnViewFieldchooser)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FIELDCHOOSER, OnUpdateViewFieldchooser)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoView construction/destruction

CBCGPDBGridDemoView::CBCGPDBGridDemoView()
{
	m_pNewGrid = NULL;
	m_nDataType = 0;
	m_nSourceType = 1;

	TCHAR szFilePath [_MAX_PATH];
	if (::GetModuleFileName (NULL, szFilePath, _MAX_PATH) > 0)
	{
		TCHAR szPath[MAX_PATH];   
		TCHAR szDrive[_MAX_DRIVE];   
		TCHAR szDir[_MAX_DIR];
		TCHAR szFile[_MAX_FNAME];   
		TCHAR szExt[_MAX_EXT];

#if _MSC_VER < 1400
		_tsplitpath (szFilePath, szDrive, szDir, szFile, szExt);
		_tmakepath (szPath, szDrive, szDir, _T("bcgpaddressbook"), _T("mdb"));
#else
		_tsplitpath_s (szFilePath, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFile, _MAX_FNAME, szExt, _MAX_EXT);
		_tmakepath_s (szPath, szDrive, szDir, _T("bcgpaddressbook"), _T("mdb"));
#endif
		m_strDefaultDBPath = szPath;
	}
}

CBCGPDBGridDemoView::~CBCGPDBGridDemoView()
{
}

BOOL CBCGPDBGridDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPGridView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoView drawing

void CBCGPDBGridDemoView::OnDraw(CDC* /*pDC*/)
{
//	CBCGPDBGridDemoDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoView printing

void CBCGPDBGridDemoView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CBCGPDBGridDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CBCGPGridView::OnPreparePrinting (pInfo);
}

void CBCGPDBGridDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnBeginPrinting (pDC, pInfo);
}

void CBCGPDBGridDemoView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnEndPrinting (pDC, pInfo);
}

void CBCGPDBGridDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);

	CBCGPGridView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoView diagnostics

#ifdef _DEBUG
void CBCGPDBGridDemoView::AssertValid() const
{
	CBCGPGridView::AssertValid();
}

void CBCGPDBGridDemoView::Dump(CDumpContext& dc) const
{
	CBCGPGridView::Dump(dc);
}

CBCGPDBGridDemoDoc* CBCGPDBGridDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPDBGridDemoDoc)));
	return (CBCGPDBGridDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoView message handlers

void CBCGPDBGridDemoView::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}

void CBCGPDBGridDemoView::ReplaceGrid (CBCGPDBGridCtrl* pNewGrid)
{
	ASSERT_VALID (pNewGrid);

	if (m_pWndGridCtrl != NULL)
	{
		delete m_pWndGridCtrl;
	}

	m_pWndGridCtrl = pNewGrid;
	
	ASSERT_VALID (m_pWndGridCtrl);
	ASSERT (m_pWndGridCtrl->IsKindOf (RUNTIME_CLASS (CBCGPGridCtrl)));
	
	if (!m_pWndGridCtrl->Create (WS_CHILD | WS_VISIBLE, 
		CRect (0, 0, 0, 0), this, ID_GRIDCTRL))
	{
		TRACE0("CBCGPGridView::OnCreate: cannot create grid control\n");
		return;
	}

	CRect rc;
	GetClientRect (&rc);
	if (m_pWndGridCtrl->GetSafeHwnd () != NULL)
	{
		m_pWndGridCtrl->SetWindowPos (NULL, -1, -1, rc.Width (), rc.Height (),
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	}

	((CBCGPDBGridCtrl*) m_pWndGridCtrl)->SetDbSort ();
}

void CBCGPDBGridDemoView::OnInitialUpdate() 
{
	CBCGPGridView::OnInitialUpdate();
}

void CBCGPDBGridDemoView::OnViewFieldchooser() 
{
	if (m_pWndGridCtrl->GetSafeHwnd () == NULL)
	{
		return;
	}

	m_pWndGridCtrl->ShowColumnsChooser (
		!m_pWndGridCtrl->IsColumnsChooserVisible ());
}

void CBCGPDBGridDemoView::OnUpdateViewFieldchooser(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_pWndGridCtrl != NULL &&
		m_pWndGridCtrl->IsColumnsChooserVisible ());
	pCmdUI->Enable (m_pWndGridCtrl->GetSafeHwnd () != NULL);
}

HBITMAP CreateBitmapFromBinaryData (LPBYTE pBuff)
{ 
	pBuff += 78 + sizeof (BITMAPFILEHEADER);

	BITMAPINFO* pbmi = (BITMAPINFO*) pBuff;

	CWindowDC dc (NULL);
	LPVOID pBits = NULL;
	
	HBITMAP hbmp = ::CreateDIBSection (dc, pbmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	if (hbmp != NULL)
	{ 
		BITMAP bitmap;
		::GetObject (hbmp, sizeof (BITMAP), (LPVOID) &bitmap);
	
		int nColors = (bitmap.bmPlanes * bitmap.bmBitsPixel);
		
		if (nColors == 1)
			nColors= 1;
		else if (nColors <= 4) 
			nColors = 4; 
		else if (nColors <= 8) 
			nColors = 8; 
		else if (nColors <= 16) 
			nColors = 16; 
		else if (nColors <= 24) 
			nColors = 24; 
		else 
			nColors = 32; 
		
		int nColorTableCount = (nColors <= 8) ? (1 << nColors) : 0;

		memcpy (pBits, &pbmi->bmiColors [nColorTableCount],
				pbmi->bmiHeader.biSizeImage);
	} 
	
	return hbmp;
} 

class CIconItem : public CBCGPGridItem
{
public:
	CIconItem (HBITMAP hbmp)
	{
		BITMAP bitmap;
		::GetObject (hbmp, sizeof (BITMAP), (LPVOID) &bitmap);

		m_Image.SetImageSize (CSize (bitmap.bmWidth, bitmap.bmHeight));
		m_Image.SetTransparentColor (RGB (255, 255, 255));
		m_Image.AddImage (hbmp);

		m_bAllowEdit = FALSE;
	}

protected:
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	CBCGPToolBarImages	m_Image;
};

void CIconItem::OnDrawValue (CDC* pDC, CRect rect)
{
	CBCGPGridItem::OnDrawValue (pDC, rect);

	CSize sizeImage = m_Image.GetImageSize ();	// Assumes square - in the sample DB
	int nSize = min (rect.Width (), rect.Height ()) - 2;
	CSize sizeDest = CSize (nSize, nSize);

	CBCGPDrawState ds;
	m_Image.PrepareDrawImage (ds, sizeDest);

	COLORREF clrTextCold = pDC->GetTextColor ();

	m_Image.Draw (pDC, 
		rect.CenterPoint ().x - nSize / 2, 
		rect.CenterPoint ().y - nSize / 2, 0);

	m_Image.EndDrawImage (ds);
	pDC->SetTextColor (clrTextCold);
}

BOOL CMyODBCGridCtrl::OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow)
{
	ASSERT_VALID (pRow);
	ASSERT_VALID (m_pRecordSet);
	ASSERT (!m_pRecordSet->IsEOF ());
	ASSERT (!m_pRecordSet->IsBOF ());

	CDBVariant varValue;
	m_pRecordSet->GetFieldValue ((short) nColumn, varValue);

	if (varValue.m_dwType != DBVT_BINARY)
	{
		return SetFieldData (varValue, pRow, nColumn, nRow);
	}

	CLongBinary* pBinary = varValue.m_pbinary;
	if (pBinary != NULL)
	{
		ASSERT_VALID (pBinary);

		LPBYTE pBuff = (LPBYTE) GlobalLock (pBinary->m_hData);
		if (pBuff != NULL)
		{
			HBITMAP hBmp = CreateBitmapFromBinaryData (pBuff);
			if (hBmp != NULL)
			{
				pRow->ReplaceItem (nColumn, new CIconItem (hBmp), FALSE);
				::DeleteObject (hBmp);
			}

			::GlobalUnlock (pBinary->m_hData);
		}
	}

	return TRUE;
}

BOOL CMyADOGridCtrl::OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow)
{
	ASSERT_VALID (pRow);
	ASSERT (m_pRecordSet != NULL);
	ASSERT (m_pRecordSet->GetState () == adStateOpen);
	ASSERT (!m_pRecordSet->ADOEOF);

	try
	{
		_variant_t varValue = 
			m_pRecordSet->Fields->GetItem (_variant_t ((short) nColumn))->GetValue ();

		if (varValue.vt != (VT_ARRAY | VT_UI1))
		{
			return CBCGPADOGridCtrl::OnAddData (pRow, nColumn, nRow);
		}

		LPBYTE pData = NULL;

		COleSafeArray array (varValue);
		array.AccessData ((void**) &pData);

		HBITMAP hBmp = CreateBitmapFromBinaryData (pData);
		if (hBmp != NULL)
		{
			pRow->ReplaceItem (nColumn, new CIconItem (hBmp), FALSE);
			::DeleteObject (hBmp);
		}

		array.UnaccessData ();
	}
	catch (COleException* pEx)
	{
		pEx->ReportError ();
		pEx->Delete ();
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError ();
		pEx->Delete ();
	}
	catch (_com_error& err)
	{
		MessageBox (err.ErrorMessage ());
	}

	return TRUE;
}

#ifndef _WIN64

BOOL CMyDAOGridCtrl::OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow)
{
	ASSERT_VALID (pRow);
	ASSERT_VALID (m_pRecordSet);
	ASSERT (!m_pRecordSet->IsEOF ());
	ASSERT (!m_pRecordSet->IsBOF ());

	COleVariant varValue;
	m_pRecordSet->GetFieldValue ((short) nColumn, varValue);

	if (varValue.vt != (VT_ARRAY | VT_UI1))
	{
		return CBCGPDAOGridCtrl::OnAddData (pRow, nColumn, nRow);
	}

	try
	{
		LPBYTE pData = NULL;

		COleSafeArray array ((VARIANT) varValue);
		array.AccessData ((void**) &pData);

		HBITMAP hBmp = CreateBitmapFromBinaryData (pData);
		if (hBmp != NULL)
		{
			pRow->ReplaceItem (nColumn, new CIconItem (hBmp), FALSE);
			::DeleteObject (hBmp);
		}

		array.UnaccessData ();
	}
	catch (COleException* pEx)
	{
		pEx->ReportError ();
		pEx->Delete ();
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError ();
		pEx->Delete ();
	}
	catch (_com_error& err)
	{
		MessageBox (err.ErrorMessage ());
	}

	return TRUE;
}

#endif
