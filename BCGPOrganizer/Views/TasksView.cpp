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
// TasksView.cpp : implementation file
//

#include "stdafx.h"
#include "../BCGPOrganizer.h"
#include "../BCGPOrganizerDoc.h"
#include "../mainfrm.h"

#include "TasksView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_GRIDCTRL 1

static LPCTSTR s_szFileName  = _T("organizer_tasks.mdb");
static LPCTSTR s_szTableName = _T("Tasks");

CImageList CTasksView::m_Images;

/////////////////////////////////////////////////////////////////////////////
// CTasksView

//tmp
UINT BCGM_ITEM_CHANGED = ::RegisterWindowMessage (_T("BCGM_ITEM_CHANGED"));

IMPLEMENT_DYNCREATE(CTasksView, CBCGPGridView)

BEGIN_MESSAGE_MAP(CTasksView, CBCGPGridView)
	//{{AFX_MSG_MAP(CTasksView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_GRID_VIEW_EXPAND_ALL, OnExpandAll)
	ON_COMMAND(ID_GRID_VIEW_COLLAPSE_ALL, OnCollapseAll)
	ON_COMMAND(ID_GRID_VIEW_FIELDCHOOSER, OnViewFieldchooser)
	ON_UPDATE_COMMAND_UI(ID_GRID_VIEW_FIELDCHOOSER, OnUpdateViewFieldchooser)
	ON_COMMAND(ID_GRID_VIEW_GROUPBOX, OnViewGroupbox)
	ON_UPDATE_COMMAND_UI(ID_GRID_VIEW_GROUPBOX, OnUpdateViewGroupbox)
	ON_COMMAND(ID_GRID_VIEW_COLUMN_AUTO_RESIZE, OnViewColumnAutoResize)
	ON_UPDATE_COMMAND_UI(ID_GRID_VIEW_COLUMN_AUTO_RESIZE, OnUpdateViewColumnAutoResize)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_TASKS_SHOW_ALL, OnShowAll)
	ON_COMMAND(ID_TASKS_SHOW_TASKS, OnShowTasks)
	ON_COMMAND(ID_TASKS_SHOW_TODO, OnShowToDo)
	ON_COMMAND(ID_DUMMY, OnDummy)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTasksView construction/destruction

CTasksView::CTasksView()
	: m_bFirstTime (TRUE),
	m_nFilter (2)
{
}

CTasksView::~CTasksView()
{
}

BOOL CTasksView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPGridView::PreCreateWindow(cs);
}

void CTasksView::OnShowAll()
{
	m_nFilter = 2;

	if (m_pWndGridCtrl->GetSafeHwnd () != NULL)
	{
		m_pWndGridCtrl->SaveState (NULL);
	}

	Refresh ();
}

void CTasksView::OnShowTasks()
{
	m_nFilter = 1;

	if (m_pWndGridCtrl->GetSafeHwnd () != NULL)
	{
		m_pWndGridCtrl->SaveState (NULL);
	}

	Refresh ();
}

void CTasksView::OnShowToDo()
{
	m_nFilter = 0;

	if (m_pWndGridCtrl->GetSafeHwnd () != NULL)
	{
		m_pWndGridCtrl->SaveState (NULL);
	}

	Refresh ();
}

void CTasksView::OnDummy()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTasksView drawing

void CTasksView::OnDraw(CDC* /*pDC*/)
{
//	CBCGPOrganizerDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTasksView printing

void CTasksView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CTasksView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CBCGPGridView::OnPreparePrinting (pInfo);
}

void CTasksView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnBeginPrinting (pDC, pInfo);
}

void CTasksView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnEndPrinting (pDC, pInfo);
}

void CTasksView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);

	CBCGPGridView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CTasksView diagnostics

#ifdef _DEBUG
void CTasksView::AssertValid() const
{
	CBCGPGridView::AssertValid();
}

void CTasksView::Dump(CDumpContext& dc) const
{
	CBCGPGridView::Dump(dc);
}

CBCGPOrganizerDoc* CTasksView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPOrganizerDoc)));
	return (CBCGPOrganizerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTasksView message handlers

void CTasksView::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_TASKS_MENU, point, this);
}

void CTasksView::OnInitialUpdate() 
{
	CBCGPGridView::OnInitialUpdate();

	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;

		CBitmap bmp;
		if (bmp.LoadBitmap (IDB_TASKS_ICONS))
		{
			m_Images.Create (16, 16, ILC_COLOR32 | ILC_MASK, 2, 0);
			m_Images.Add (&bmp, (CBitmap*)NULL);
		}

		m_ImagesHeader.Create (IDB_TASKS_HEADER, 12, 0, RGB (255, 0, 255));

		CADOGridCtrl* pGridCtrl = (CADOGridCtrl*) GetGridCtrl ();
		ASSERT_VALID (pGridCtrl);

		pGridCtrl->m_nFilter = m_nFilter;

		pGridCtrl->EnableColumnAutoSize (TRUE);
		pGridCtrl->SetWholeRowSel (TRUE);
		pGridCtrl->SetSingleSel (TRUE);

		CString strPath (GetDocument ()->GetPath () + s_szFileName);

		BOOL bResult = FALSE;
		if (pGridCtrl->OpenMSAccessFile (strPath))
		{
			CStringList lstFields;
			pGridCtrl->GetFieldList (s_szTableName, lstFields);

			if (!lstFields.IsEmpty ())
			{
				m_strSQL =  (_T("SELECT "));
				for (POSITION pos = lstFields.GetHeadPosition (); pos != NULL;)
				{
					CString strField (lstFields.GetNext (pos));

					if (strField.CompareNoCase ("id") != 0)
					{
						if (strField.Find(_T(" ")) != -1)
						{
							strField = _T("[") + strField;
							strField += _T("]");
						}

						m_strSQL += strField;
						if (pos != NULL)
						{
							m_strSQL += _T(",");
						}
					}
				}

				m_strSQL += _T(" FROM ");
				m_strSQL += s_szTableName;

				bResult = Refresh ();
			}

			if (!bResult)
			{
				pGridCtrl->Close ();
			}
		}

		pGridCtrl->SetReadOnly ();
	}
}

void CTasksView::OnDestroy() 
{
	if (m_pWndGridCtrl->GetSafeHwnd () != NULL)
	{
		m_pWndGridCtrl->SaveState (NULL);
	}

	CBCGPGridView::OnDestroy();
}

void CTasksView::OnExpandAll() 
{
	if (m_pWndGridCtrl->GetSafeHwnd () == NULL)
	{
		return;
	}

	m_pWndGridCtrl->ExpandAll ();
}

void CTasksView::OnCollapseAll() 
{
	if (m_pWndGridCtrl->GetSafeHwnd () == NULL)
	{
		return;
	}

	m_pWndGridCtrl->ExpandAll (FALSE);
}

void CTasksView::OnViewFieldchooser() 
{
	if (m_pWndGridCtrl->GetSafeHwnd () == NULL)
	{
		return;
	}

	m_pWndGridCtrl->ShowColumnsChooser (
		!m_pWndGridCtrl->IsColumnsChooserVisible ());
}

void CTasksView::OnUpdateViewFieldchooser(CCmdUI* pCmdUI) 
{
	BOOL bEnable = m_pWndGridCtrl->GetSafeHwnd () != NULL;
	pCmdUI->Enable (bEnable);
	pCmdUI->SetCheck (bEnable && m_pWndGridCtrl->IsColumnsChooserVisible ());
}

void CTasksView::OnViewGroupbox() 
{
	if (m_pWndGridCtrl->GetSafeHwnd () == NULL)
	{
		return;
	}

	m_pWndGridCtrl->EnableGroupByBox (!m_pWndGridCtrl->IsGroupByBox ());
}

void CTasksView::OnUpdateViewGroupbox(CCmdUI* pCmdUI) 
{
	BOOL bEnable = m_pWndGridCtrl->GetSafeHwnd () != NULL;
	pCmdUI->Enable (bEnable);
	pCmdUI->SetCheck (bEnable && m_pWndGridCtrl->IsGroupByBox ());
}

void CTasksView::OnViewColumnAutoResize() 
{
	if (m_pWndGridCtrl->GetSafeHwnd () == NULL)
	{
		return;
	}

	m_pWndGridCtrl->EnableColumnAutoSize (!m_pWndGridCtrl->IsColumnAutoSizeEnabled ());
}

void CTasksView::OnUpdateViewColumnAutoResize(CCmdUI* pCmdUI) 
{
	BOOL bEnable = m_pWndGridCtrl->GetSafeHwnd () != NULL;
	pCmdUI->Enable (bEnable);
	pCmdUI->SetCheck (bEnable && m_pWndGridCtrl->IsColumnAutoSizeEnabled ());
}

BOOL CTasksView::Refresh ()
{
	CADOGridCtrl* pGridCtrl = (CADOGridCtrl*) GetGridCtrl ();
	ASSERT_VALID (pGridCtrl);

	pGridCtrl->m_nFilter = m_nFilter;
	
	pGridCtrl->SetRedraw (FALSE);

	if (!pGridCtrl->OpenSQL (m_strSQL))
	{
		pGridCtrl->SetRedraw ();
		return FALSE;
	}

	pGridCtrl->SetColumnVisible (8, FALSE);

	if (m_ImagesHeader.GetSafeHandle () != NULL)
	{
		pGridCtrl->SetHeaderImageList (&m_ImagesHeader);
		pGridCtrl->EnableHeader ();

		CBCGPGridColumnsInfo& info = pGridCtrl->GetColumnsInfo ();
		info.SetColumnWidth (0, 20);
		info.SetColumnImage (0, 0);
		info.SetColumnImage (1, 1);

		pGridCtrl->SetHeaderAlign (0, HDF_CENTER);
		pGridCtrl->SetHeaderAlign (1, HDF_CENTER);

		pGridCtrl->SetColumnLocked (0);
		pGridCtrl->SetColumnLocked (1);
	}

	pGridCtrl->SetDbSort ();
	pGridCtrl->LoadState (NULL);
	pGridCtrl->AdjustLayout ();

	pGridCtrl->SetRedraw ();
	pGridCtrl->RedrawWindow ();

	return TRUE;
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

class CLookUpItem : public CBCGPGridItem
{
public:
	struct XOptionItem
	{
		XOptionItem ()
			: m_Name (_T(""))
			, m_ID   (0)
		{
		}
		
		XOptionItem (const CString& name, long id)
			: m_Name (name)
			, m_ID   (id)
		{

		}

		CString m_Name;
		long    m_ID;
	};

	typedef CArray<XOptionItem, const XOptionItem&> XOptionArray;

public:
	CLookUpItem(const _variant_t& varValue)
		: CBCGPGridItem (varValue)
	{
	}

	virtual ~CLookUpItem()
	{
	}

	void AddOptions ()
	{
		for (int i = 0; i < m_Array.GetSize(); i++)
		{
			AddOption (m_Array[i].m_Name, TRUE);
		}
	}

	virtual BOOL TextToVar (const CString& strText)
	{
		BOOL bFound = FALSE;
		long nItem  = -1;

		for (int i = 0; i < m_Array.GetSize (); i++)
		{
			if (strText.Compare (m_Array[i].m_Name) == 0)
			{
				nItem = m_Array[i].m_ID;
				bFound = TRUE;
				break;
			}
		}

		if (bFound)
		{
			m_varValue = (long) nItem;
			return TRUE;
		}

		return FALSE;
	}

	virtual CString FormatItem ()
	{
		long nItem = (long) m_varValue;

		for (int i = 0; i < m_Array.GetSize (); i++)
		{
			if (nItem == m_Array[i].m_ID)
			{
				return m_Array[i].m_Name;
			}
		}

		return CString ();
	}

protected:

	XOptionArray m_Array;
};

class CTypeItem : public CLookUpItem
{
public:
	CTypeItem(const _variant_t& varValue)
		: CLookUpItem (varValue)
	{
		//m_Array.Add (XOptionItem (_T("Task"), 0));
		//m_Array.Add (XOptionItem (_T("To-Do"), 1));
		m_bAllowEdit = FALSE;
	}

	virtual ~CTypeItem()
	{
	}

protected:
	virtual void OnDrawValue (CDC* pDC, CRect rect)
	{
		if (CTasksView::m_Images.GetImageCount () == 0)
		{
			CLookUpItem::OnDrawValue (pDC, rect);
			return;
		}

		long nValue = (long) m_varValue;

		int nSize = min (rect.Width (), rect.Height ()) - 2;
		CPoint pt (rect.CenterPoint ());
		pt.x -= nSize / 2;
		pt.y -= nSize / 2;

		CTasksView::m_Images.Draw (pDC, nValue == 1 ? 1 : 0, pt, ILD_NORMAL);
	}
};

class CPriorityItem : public CLookUpItem
{
public:
	CPriorityItem(const _variant_t& varValue)
		: CLookUpItem (varValue)
	{
		m_Array.Add (XOptionItem (_T("Low"), 2));
		m_Array.Add (XOptionItem (_T("Normal"), 1));
		m_Array.Add (XOptionItem (_T("High"), 0));
	}

	virtual ~CPriorityItem()
	{
	}

protected:
	virtual void OnDrawValue (CDC* pDC, CRect rect)
	{
		if (CTasksView::m_Images.GetImageCount () == 0)
		{
			CLookUpItem::OnDrawValue (pDC, rect);
			return;
		}

		long nValue = (long) m_varValue;

		if (nValue != 1)
		{
			int nSize = min (rect.Width (), rect.Height ()) - 2;
			CPoint pt (rect.CenterPoint ());
			pt.x -= nSize / 2;
			pt.y -= nSize / 2;

			CTasksView::m_Images.Draw (pDC, nValue == 2 ? 3 : 2, pt, ILD_NORMAL);
		}
	}
};

class CCategoryItem : public CLookUpItem
{
public:
	CCategoryItem(const _variant_t& varValue)
		: CLookUpItem (varValue)
	{
		m_Array.Add (XOptionItem (_T("None"), 0));
		m_Array.Add (XOptionItem (_T("Blue Category"), 1));
		m_Array.Add (XOptionItem (_T("Green Category"), 2));
		m_Array.Add (XOptionItem (_T("Orange Category"), 3));
		m_Array.Add (XOptionItem (_T("Purple Category"), 4));
		m_Array.Add (XOptionItem (_T("Red Category"), 5));
		m_Array.Add (XOptionItem (_T("Yellow Category"), 6));
	}

	virtual ~CCategoryItem()
	{
	}

protected:
	virtual void OnDrawValue (CDC* pDC, CRect rect)
	{
		if (CTasksView::m_Images.GetImageCount () == 0)
		{
			CLookUpItem::OnDrawValue (pDC, rect);
			return;
		}

		long nValue = (long) m_varValue;

		if (nValue != 0)
		{
			int nSize = min (rect.Width (), rect.Height ()) - 2;
			CPoint pt (rect.CenterPoint ());
			pt.x -= nSize / 2;
			pt.y -= nSize / 2;

			CTasksView::m_Images.Draw (pDC, nValue + 3, pt, ILD_NORMAL);
		}
	}
};

class CStatusItem : public CLookUpItem
{
public:
	CStatusItem(const _variant_t& varValue)
		: CLookUpItem (varValue)
	{
		m_Array.Add (XOptionItem (_T("Not Started"), 0));
		m_Array.Add (XOptionItem (_T("In Progress"), 1));
		m_Array.Add (XOptionItem (_T("Completed"), 2));
		m_Array.Add (XOptionItem (_T("Waiting on someone else"), 3));
		m_Array.Add (XOptionItem (_T("Deferred"), 4));
	}

	virtual ~CStatusItem()
	{
	}
};

BOOL CADOGridCtrl::OnAddData (CBCGPGridRow* pRow, int nColumn, int nRow)
{
	ASSERT_VALID (pRow);
	ASSERT (m_pRecordSet != NULL);
	ASSERT (m_pRecordSet->GetState () == adStateOpen);
	ASSERT (!m_pRecordSet->ADOEOF);

	try
	{
		FieldPtr field = m_pRecordSet->Fields->GetItem (_variant_t ((short) nColumn));
		if (field.GetInterfacePtr () != NULL)
		{
			_bstr_t name (field->GetName ());

			if (name == _bstr_t("Start Date") || name == _bstr_t("Due Date"))
			{
				pRow->ReplaceItem (nColumn, new CBCGPGridDateTimeItem (field->GetValue (), 0, CBCGPDateTimeCtrl::DTM_DATE), FALSE);
				return TRUE;
			}

			CLookUpItem* pItem = NULL;

			if (name == _bstr_t("Type"))
			{
				pItem = new CTypeItem (field->GetValue ());
			}
			else if (name == _bstr_t("Priority"))
			{
				pItem = new CPriorityItem (field->GetValue ());
			}
			else if (name == _bstr_t("Status"))
			{
				pItem = new CStatusItem (field->GetValue ());
			}
			else if (name == _bstr_t("Category"))
			{
				pItem = new CCategoryItem (field->GetValue ());
			}

			if (pItem != NULL)
			{
				pItem->AddOptions ();
				pRow->ReplaceItem (nColumn, pItem, FALSE);

				return TRUE;
			}
		}

		return CBCGPADOGridCtrl::OnAddData (pRow, nColumn, nRow);
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

BOOL CADOGridCtrl::OnBeforeAddRow (CBCGPGridRow* pRow, int /*nRow*/)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pRow);

	if (m_nFilter == 2)
	{
		return TRUE;
	}

	long nType = (long) pRow->GetItem (0)->GetValue ();
	return (nType == m_nFilter);
}

BOOL CTasksView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pNMHDR = (NMHDR*)(lParam);
	if (pNMHDR != NULL && pNMHDR->code == BCGPGN_SELCHANGED)
	{
		UpdateCaptionText ();

		*pResult = 0L;
		return TRUE;
	}
	
	return CBCGPGridView::OnNotify(wParam, lParam, pResult);
}

void CTasksView::UpdateCaptionText ()
{
	CBCGPOrganizerDoc* pDoc = GetDocument ();
	if (pDoc == NULL || pDoc->GetMode () != CBCGPOrganizerDoc::e_ModeTasks)
	{
		return;
	}

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());

	if (pFrame != NULL)
	{
		CString str;
		CBCGPGridCtrl* pGridCtrl = GetGridCtrl ();
		if (pGridCtrl != NULL)
		{
			CBCGPGridRow* pRow = pGridCtrl->GetCurSel ();
			if (pRow != NULL && !pRow->IsGroup ())
			{
				str = _T("Subject: ") + pRow->GetItem (2)->FormatItem ();
				str += _T("; Status: ") + pRow->GetItem (6)->FormatItem ();
			}
		}

		if (str.IsEmpty ())
		{
			str = _T(" ");
		}

		pFrame->SetCaptionText (str);
	}
}

void CTasksView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPGridView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		UpdateCaptionText ();
	}
}
