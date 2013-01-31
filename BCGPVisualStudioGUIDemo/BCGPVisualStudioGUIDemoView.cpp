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
// BCGPVisualStudioGUIDemoView.cpp : implementation of the CBCGPVisualStudioGUIDemoView class
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"

#include "BCGPVisualStudioGUIDemoDoc.h"
#include "BCGPVisualStudioGUIDemoView.h"

#include "MainFrm.h"
#include "UndoBar.h"

#include "CustomEditCtrl.h"
#include "GotoLineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoView

IMPLEMENT_DYNCREATE(CBCGPVisualStudioGUIDemoView, CBCGPEditView)

BEGIN_MESSAGE_MAP(CBCGPVisualStudioGUIDemoView, CBCGPEditView)
	//{{AFX_MSG_MAP(CBCGPVisualStudioGUIDemoView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_TOGGLEBOOKMARK, OnEditTogglebookmark)
	ON_COMMAND(ID_DUMMY_REMOVE_ALL_BREAKPOINTS, OnRemoveAllBreakpoints)
	ON_COMMAND(ID_EDIT_TOGGLEBREAKPOINT, OnToggleBreakpoint)
	ON_COMMAND(ID_EDIT_CLEAR_ALLBOOKMARKS, OnClearAllBookmarks)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALLBOOKMARKS, OnUpdateClearAllBookmarks)
	ON_COMMAND(ID_EDIT_NEXTBOOKMARK, OnEditNextbookmark)
	ON_COMMAND(ID_EDIT_PREVIOUSBOOKMARK, OnEditPreviousbookmark)
	ON_COMMAND(ID_EDIT_LISTMEMBERS, OnEditListmembers)
	ON_COMMAND(ID_EDIT_INCREASE_IDENT, OnEditIncreaseIdent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INCREASE_IDENT, OnUpdateEditIncreaseIdent)
	ON_COMMAND(ID_EDIT_DECREASE_IDENT, OnEditDecreaseIdent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DECREASE_IDENT, OnUpdateEditDecreaseIdent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LISTMEMBERS, OnUpdateEditListmembers)
	ON_COMMAND(ID_EDIT_HIDESELECTION, OnEditHideselection)
	ON_COMMAND(ID_EDIT_STOPHIDINGCURRENT, OnEditStophidingcurrent)
	ON_COMMAND(ID_EDIT_TOGGLEOUTLINING, OnEditToggleoutlining)
	ON_COMMAND(ID_EDIT_TOGGLEALLOUTLINING, OnEditTogglealloutlining)
	ON_COMMAND(ID_EDIT_COLLAPSETODEFINITIONS, OnEditCollapsetodefinitions)
	ON_COMMAND(ID_EDIT_STOPOUTLINING, OnEditStopoutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STOPHIDINGCURRENT, OnUpdateEditStophidingcurrent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_HIDESELECTION, OnUpdateEditHideselection)
	ON_COMMAND(ID_EDIT_AUTOOUTLINING, OnEditAutooutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_AUTOOUTLINING, OnUpdateEditAutooutlining)
	ON_COMMAND(ID_EDIT_ENABLEOUTLINING, OnEditEnableoutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ENABLEOUTLINING, OnUpdateEditEnableoutlining)
	ON_COMMAND(ID_EDIT_LINENUMBERS, OnEditLinenumbers)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LINENUMBERS, OnUpdateEditLinenumbers)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STOPOUTLINING, OnUpdateEditStopoutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TOGGLEALLOUTLINING, OnUpdateEditTogglealloutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TOGGLEOUTLINING, OnUpdateEditToggleoutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COLLAPSETODEFINITIONS, OnUpdateEditCollapsetodefinitions)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LISTMEMBERS, OnUpdateEditListmembers)
	ON_COMMAND(ID_EDIT_GOTO_LINE, OnEditGotoLine)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(IDS_CARET_POS, OnUpdateCaretPos)
	ON_COMMAND(ID_EDIT_SHOWHINT, OnShowHint)
	ON_COMMAND(ID_EDIT_FIND_COMBO, OnFind)
	ON_COMMAND(ID_EDIT_FINDPREV, OnFindPrev)
	ON_COMMAND(ID_EDIT_FINDNEXT, OnFindNext)
	ON_COMMAND(ID_EDIT_NEXT_WORD, OnEditFindNextWord)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoView construction/destruction

CBCGPVisualStudioGUIDemoView::CBCGPVisualStudioGUIDemoView()
{
	m_bXMLSettings = FALSE;
}

CBCGPVisualStudioGUIDemoView::~CBCGPVisualStudioGUIDemoView()
{
}

BOOL CBCGPVisualStudioGUIDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoView drawing

void CBCGPVisualStudioGUIDemoView::OnDraw(CDC* /*pDC*/)
{
	CBCGPVisualStudioGUIDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoView diagnostics

#ifdef _DEBUG
void CBCGPVisualStudioGUIDemoView::AssertValid() const
{
	CBCGPEditView::AssertValid();
}

void CBCGPVisualStudioGUIDemoView::Dump(CDumpContext& dc) const
{
	CBCGPEditView::Dump(dc);
}

CBCGPVisualStudioGUIDemoDoc* CBCGPVisualStudioGUIDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPVisualStudioGUIDemoDoc)));
	return (CBCGPVisualStudioGUIDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoView message handlers

void CBCGPVisualStudioGUIDemoView::OnContextMenu(CWnd*, CPoint point)
{
	ASSERT_VALID (m_pEdit);

	CPoint pt(point);

	ScreenToClient(&pt);
	if (pt.x < m_pEdit->m_nLeftMarginWidth)
	{
		pt.x = m_pEdit->m_nLeftMarginWidth;
		m_pEdit->SetCaret(m_pEdit->HitTest(pt));

		theApp.ShowPopupMenu (IDR_POPUP_SELECTIONMARGIN, point, this);
	}
	else
	{
		theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
	}
}

CBCGPEditCtrl* CBCGPVisualStudioGUIDemoView::CreateEdit ()
{
	m_pEdit = new CCustomEditCtrl;
	return m_pEdit;
}

int CBCGPVisualStudioGUIDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	ASSERT_VALID (m_pEdit);

	m_strCaretPosFmt.LoadString (IDS_CARET_POS);

	ResetDefaultFont();

	OnChangeVisualStyle ();

	m_pEdit->EnableToolTips ();

	m_pEdit->EnableOutlining ();
	m_pEdit->EnableAutoOutlining ();
	m_pEdit->SetOutlineMargin ();
	m_pEdit->SetLineNumbersMargin (TRUE, 30);
	m_pEdit->EnableOutlineParser (FALSE);
	DisableMainframeForFindDlg (FALSE);

	ResetFindCombo();

	CBCGPVisualStudioGUIDemoDoc* pDoc = GetDocument();
	if (pDoc != NULL)
	{
		ASSERT_VALID (pDoc);
		pDoc->SetModifiedFlag(m_pEdit->IsModified());
	}

	ModifyStyle(0,WS_VISIBLE);
	return 0;
}

void CBCGPVisualStudioGUIDemoView::OnInitialUpdate() 
{
	CBCGPEditView::OnInitialUpdate();

	ASSERT_VALID (m_pEdit);

	UINT uiExampleXMLSettingsID = GetDocument()->m_uiExampleXMLSettingsID;
	if (uiExampleXMLSettingsID != 0)
	{
		LPCTSTR lpszResourceName = MAKEINTRESOURCE (uiExampleXMLSettingsID);
		ASSERT(lpszResourceName != NULL);

		HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, _T("EDITOR_XML_SETTINGS"));
		HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, _T("EDITOR_XML_SETTINGS"));
		
		if (hRsrc == NULL)
		{
			ASSERT(FALSE);
		}
		else
		{
			HGLOBAL hGlobal = LoadResource(hInst, hRsrc);

			if (hGlobal == NULL)
			{
				ASSERT(FALSE);
			}
			else
			{
				LPCTSTR lpszXML = (LPCTSTR)LockResource(hGlobal);

				if (lpszXML == NULL)
				{
					ASSERT(FALSE);
				}
				else
				{
					DWORD dwSize = SizeofResource(hInst, hRsrc);
					CString strText = lpszXML;

					m_pEdit->LoadXMLSettingsFromBuffer (strText.Left (dwSize));
				}

				UnlockResource(hGlobal);
				FreeResource(hGlobal);
			}
		}
	}

	const CString& strPathName = GetDocument()->GetPathName();

	switch (GetDocument()->m_uiExampleID)
	{
	case ID_EXAMPLE_CPP:
		m_pEdit->EnableIntelliSense(!m_bXMLSettings && strPathName.IsEmpty());
		m_pEdit->EnableBreakpoints(TRUE);
		break;

	case ID_EXAMPLE_WEB:
		m_pEdit->m_bCheckColorTags = TRUE;

	default:
		m_pEdit->EnableIntelliSense(FALSE);
		m_pEdit->EnableBreakpoints(FALSE);
		m_pEdit->RemoveAllBreakpoints();
	}

	if (strPathName.IsEmpty())
	{
		RestoreDefaultData();
		GetDocument()->SetModifiedFlag(m_pEdit->IsModified());
		GetDocument()->CheckTitle();
	}

	m_pEdit->EnableOutlineParser (TRUE);
	m_pEdit->UpdateAutoOutlining ();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateCaretPos(CCmdUI* pCmdUI)
{
	ASSERT_VALID (m_pEdit);

	CString str;
	str.Format (m_strCaretPosFmt, m_pEdit->GetCurRow () + 1, m_pEdit->GetCurColumn () + 1);

	pCmdUI->SetText (str);
	
	pCmdUI->Enable();
}

void CBCGPVisualStudioGUIDemoView::RestoreDefaultView(UINT uiExampleID /* = -1 */)
{
	ASSERT_VALID (m_pEdit);

	if (uiExampleID == ID_EXAMPLE_CPP)
	{
		// Insert unnamed Bookmarks
		m_pEdit->ToggleMarker (3, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (11, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (21, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (30, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (45, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (53, g_dwBCGPEdit_BookMark);

		// Insert Breakpoints
		m_pEdit->ToggleBreakpoint(21);

		// Insert Current Line marker:
		m_pEdit->ToggleCurrentLine (48);
	}
}

BOOL CBCGPVisualStudioGUIDemoView::RestoreDefaultData()
{
	ASSERT_VALID (m_pEdit);

	UINT uiID = GetDocument()->m_uiExampleID;
	if (uiID == 0)
	{
		return FALSE;
	}

	BOOL bRet = FALSE;
	LPCTSTR lpszResourceName = MAKEINTRESOURCE (uiID);
	ASSERT(lpszResourceName != NULL);

	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, _T("Examples"));
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, _T("Examples"));
	
	if (hRsrc == NULL)
	{
		ASSERT(FALSE);
	}
	else
	{
		HGLOBAL hGlobal = LoadResource(hInst, hRsrc);

		if (hGlobal == NULL)
		{
			ASSERT(FALSE);
		}
		else
		{
			LPCTSTR lpszText = (LPCTSTR)LockResource(hGlobal);

			if (lpszText == NULL)
			{
				ASSERT(FALSE);
			}
			else
			{
				DWORD dwSize = SizeofResource(hInst, hRsrc);
				CString strText = lpszText;

				m_pEdit->SetWindowText(strText.Left (dwSize));
				RestoreDefaultView(uiID);

				bRet = TRUE;
			}

			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}
	}

	return bRet;
}

void CBCGPVisualStudioGUIDemoView::ResetDefaultFont()
{
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	CDC* pDC = GetDC();

	CFont* pFont = pDC->SelectObject(CFont::FromHandle(hFont));
	pDC->SelectObject(pFont);
	::DeleteObject(hFont);

	LOGFONT lf;
	pFont->GetLogFont (&lf);

	CString strFontName(_T("Courier New"));
	CopyMemory(lf.lfFaceName,(LPCTSTR)strFontName,(strFontName.GetLength() + 1) * sizeof(TCHAR));
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;

	m_Font.CreateFontIndirect(&lf);
	m_pEdit->SetFont (&m_Font);
}

void CBCGPVisualStudioGUIDemoView::ResetFindCombo()
{
	CBCGPToolbarComboBoxButton* pFindCombo = ((CMainFrame*)AfxGetMainWnd())->GetFindCombo();

	if ((pFindCombo != NULL) && (pFindCombo->GetCount()))
	{
		CString strText;
		pFindCombo->GetComboBox()->SetCurSel(0);
		pFindCombo->GetComboBox()->GetLBText(0,strText);
		
		if (!strText.IsEmpty())
		{
			pFindCombo->SetText(strText);
			m_strFindText = strText;
		}
	}
}

void CBCGPVisualStudioGUIDemoView::VerifyFindString(CBCGPToolbarComboBoxButton* pFindCombo,
											   CString& strFindText)
{
	if (pFindCombo == NULL)
	{
		return;
	}

	BOOL bIsLastCommandFromButton = CBCGPToolBar::IsLastCommandFromButton(pFindCombo);
	
	if (bIsLastCommandFromButton)
	{
		strFindText = pFindCombo->GetText();
	}

	CComboBox* pCombo = pFindCombo->GetComboBox();

	if (!strFindText.IsEmpty())
	{
		const int nCount = pCombo->GetCount();
		int ind = 0;
		CString strCmpText;

		while (ind < nCount)
		{
			pCombo->GetLBText(ind, strCmpText);

			if (strCmpText.GetLength() == strFindText.GetLength())
			{
				if (strCmpText == strFindText)
					break;
			}

			ind++;
		}
		
		if (ind < nCount)
		{
			pCombo->DeleteString(ind);
		}

		pCombo->InsertString(0,strFindText);
		pCombo->SetCurSel(0);
		
		if (!bIsLastCommandFromButton)
		{
			pFindCombo->SetText(strFindText);
		}
	}
}

void CBCGPVisualStudioGUIDemoView::OnShowHint()
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ShowContextTip();
}

void CBCGPVisualStudioGUIDemoView::OnFind()
{
	VerifyFindString(((CMainFrame*)AfxGetMainWnd())->GetFindCombo(),
					 m_strFindText);
	OnFindReplace(0, 0);
}

void CBCGPVisualStudioGUIDemoView::OnFindNext()
{
	m_dwFindMask |= FR_DOWN;
	OnFind();
}

void CBCGPVisualStudioGUIDemoView::OnFindPrev()
{
	m_dwFindMask &= ~FR_DOWN;
	OnFind();
}

void CBCGPVisualStudioGUIDemoView::OnTextNotFound (LPCTSTR lpszFind)
{
	CString strError;
	strError.Format (IDS_STRING_NOT_FOUND_FMT, 
		lpszFind == NULL ? _T("") : lpszFind);

	MessageBox (strError);
}

void CBCGPVisualStudioGUIDemoView::OnLButtonDblClk(UINT /*nFlags*/, CPoint /*point*/) 
{
	theApp.OnViewDoubleClick (this, IDR_BCGDEVTYPE0);
}

void CBCGPVisualStudioGUIDemoView::OnEditTogglebookmark() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleMarker (m_pEdit->GetCurRow (), g_dwBCGPEdit_BookMark);
}

void CBCGPVisualStudioGUIDemoView::OnRemoveAllBreakpoints()
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->RemoveAllBreakpoints();
}

void CBCGPVisualStudioGUIDemoView::OnToggleBreakpoint() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleBreakpoint();
}

void CBCGPVisualStudioGUIDemoView::OnClearAllBookmarks()
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->DeleteAllMarkers(g_dwBCGPEdit_BookMark);
}

void CBCGPVisualStudioGUIDemoView::OnUpdateClearAllBookmarks(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable(m_pEdit->HasMarkers(g_dwBCGPEdit_BookMark));	
}

void CBCGPVisualStudioGUIDemoView::OnEditNextbookmark() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->GoToNextMarker(g_dwBCGPEdit_BookMark, TRUE);
}

void CBCGPVisualStudioGUIDemoView::OnEditPreviousbookmark() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->GoToNextMarker(g_dwBCGPEdit_BookMark,FALSE);
}

void CBCGPVisualStudioGUIDemoView::DoUndo(CUndoButton* pUndoBtn)
{
	ASSERT_VALID (m_pEdit);

	if (pUndoBtn == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	switch (pUndoBtn->m_nID) 
	{
	case ID_EDIT_UNDO:
		{
			for (int ind = 0; ind < pUndoBtn->GetSelNum(); ind++)
			{
				if (!m_pEdit->OnUndo())
				{
					break;
				}
			}
		}
		break;

	case ID_EDIT_REDO:
		{
			for (int ind = pUndoBtn->GetSelNum(); --ind >= 0;)
			{
				if (!m_pEdit->OnRedo())
				{
					break;
				}
			}
		}
		break;

	default:
		ASSERT(FALSE);
	}
}

void CBCGPVisualStudioGUIDemoView::OnEditListmembers() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->InvokeIntelliSense();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditListmembers(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);

	CObList lstIntelliSenseData;

	m_pEdit->FillIntelliSenseList(lstIntelliSenseData);
	pCmdUI->Enable(!lstIntelliSenseData.IsEmpty());
	
	m_pEdit->ReleaseIntelliSenseList(lstIntelliSenseData);
}

void CBCGPVisualStudioGUIDemoView::AttachXMLSettings(const CString& /*strXMLFileName*/)
{
	ASSERT_VALID (m_pEdit);

	m_pEdit->RemoveXMLSettings();
	m_pEdit->EnableBreakpoints(FALSE);

}

void CBCGPVisualStudioGUIDemoView::GetUndoActions(CStringList& lstActions) const
{
	GetUndoRedoActions(lstActions, TRUE);
}

void CBCGPVisualStudioGUIDemoView::GetRedoActions(CStringList& lstActions) const
{
	GetUndoRedoActions(lstActions, FALSE);
}

void CBCGPVisualStudioGUIDemoView::GetUndoRedoActions(CStringList& lstActions, BOOL bUndo) const
{
	ASSERT_VALID (m_pEdit);

	CDWordArray dwaUAT;
	
	//	Get undo/redo actions:
	if (bUndo)
	{
		m_pEdit->GetUndoActions(dwaUAT);
	}
	else
	{
		m_pEdit->GetRedoActions(dwaUAT);
	}
	
	//	Setup undo/redo actions:
	lstActions.RemoveAll();
	
	int nIndex = (int)dwaUAT.GetSize();
	if ( nIndex != 0)
	{
		CString strAction;

		while (nIndex--)
		{
			strAction.Empty();

			if (!UATToString(dwaUAT.GetAt(nIndex), strAction))
			{
				ASSERT(FALSE);
				strAction.LoadString(IDS_UAT_UNKNOWN);
			}

			if (strAction.IsEmpty())
			{
				ASSERT(FALSE);
				strAction = _T("<?>");
			}

			lstActions.AddHead(strAction);
		}
	}
}

BOOL CBCGPVisualStudioGUIDemoView::UATToString(DWORD dwUAT, CString& strAction) const
{
	switch (dwUAT & UAT_REASON) 
	{
	case g_dwUATUndefined:
		strAction.LoadString(IDS_UAT_UNDEFINED);
		break;

	case g_dwUATTyping:
		strAction.LoadString(IDS_UAT_TYPING);
		break;

	case g_dwUATCut:
		strAction.LoadString(IDS_UAT_CUT);
		break;

	case g_dwUATPaste:
		strAction.LoadString(IDS_UAT_PASTE);
		break;

	case g_dwUATDelete:
		strAction.LoadString(IDS_UAT_DELETE);
		break;

	case g_dwUATBackspace:
		strAction.LoadString(IDS_UAT_BACKSPACE);
		break;

	case g_dwUATDragDrop:
		strAction.LoadString(IDS_UAT_DRAGDROP);
		break;

	case g_dwUATEnter:
		strAction.LoadString(IDS_UAT_ENTER);
		break;

	case g_dwUATIndent:
		strAction.LoadString(IDS_UAT_INDENT);
		break;		

	case g_dwUATUnindent:
		strAction.LoadString(IDS_UAT_UNINDENT);
		break;

	case g_dwUATTab:
		strAction.LoadString(IDS_UAT_TAB);
		break;		

	case g_dwUATReplace:
		strAction.LoadString(IDS_UAT_REPLACE);
		break;		

	default:
		return FALSE;
	}

	return TRUE;
}

void CBCGPVisualStudioGUIDemoView::OnEditIncreaseIdent() 
{
	ASSERT_VALID (m_pEdit);
	VERIFY(m_pEdit->IndentSelection(TRUE));
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditIncreaseIdent(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable(m_pEdit->IsIndentEnabled(TRUE));
}

void CBCGPVisualStudioGUIDemoView::OnEditDecreaseIdent() 
{
	ASSERT_VALID (m_pEdit);
	VERIFY(m_pEdit->IndentSelection(FALSE));
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditDecreaseIdent(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable(m_pEdit->IsIndentEnabled(FALSE));
}

BOOL CBCGPVisualStudioGUIDemoView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	ASSERT_VALID (m_pEdit);

	GetDocument()->SetModifiedFlag(m_pEdit->IsModified());
	GetDocument()->CheckTitle();

	return CBCGPEditView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CBCGPVisualStudioGUIDemoView::OnEditFindNextWord()
{
	ASSERT_VALID (m_pEdit);

	CString strWord;
	if (m_pEdit->GetWordFromOffset (m_pEdit->GetCurOffset (), strWord))
	{
		m_pEdit->FindText (strWord, TRUE, TRUE, TRUE);
	}
}

void CBCGPVisualStudioGUIDemoView::OnEditHideselection() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->HideSelection ();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditHideselection(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);

	int nStart = 0;
	int nEnd = 0;
	m_pEdit->GetSel (nStart, nEnd);

	pCmdUI->Enable (
		nStart >= 0 && nEnd >= 0 && (nStart != nEnd) &&
		m_pEdit->IsOutliningEnabled () &&
		!m_pEdit->IsAutoOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnEditStophidingcurrent() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->StopHidingCurrent ();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditStophidingcurrent(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (
		m_pEdit->IsOutliningEnabled () &&
		!m_pEdit->IsAutoOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnEditToggleoutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleOutlining ();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditToggleoutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnEditTogglealloutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleAllOutlining ();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditTogglealloutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnEditCollapsetodefinitions() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->CollapseToDefinitions ();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditCollapsetodefinitions(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnEditStopoutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->StopOutlining ();
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditStopoutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (
		m_pEdit->IsOutliningEnabled () &&
		m_pEdit->IsAutoOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnEditAutooutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->EnableAutoOutlining (!m_pEdit->IsAutoOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditAutooutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->SetCheck (m_pEdit->IsAutoOutliningEnabled () ? 1 : 0);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnEditEnableoutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->EnableOutlining (!m_pEdit->IsOutliningEnabled ());
	m_pEdit->SetOutlineMargin (m_pEdit->IsOutliningEnabled ());
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditEnableoutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->SetCheck (m_pEdit->IsOutliningEnabled () ? 1 : 0);
}

void CBCGPVisualStudioGUIDemoView::OnEditLinenumbers() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->SetLineNumbersMargin (!m_pEdit->IsLineNumbersMarginVisible ());
}

void CBCGPVisualStudioGUIDemoView::OnUpdateEditLinenumbers(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->SetCheck (m_pEdit->IsLineNumbersMarginVisible () ? 1 : 0);
}

void CBCGPVisualStudioGUIDemoView::OnChangeVisualStyle ()
{
	if (m_imgList.GetSafeHandle () != NULL)
	{
		m_imgList.DeleteImageList ();
	}

	UINT uiBmpId = theApp.m_bHiColorIcons ? 
		IDB_IMG_INTELLISENSE_HC : IDB_IMG_INTELLISENSE;

	CBitmap bmp;
	if (!bmp.LoadBitmap (uiBmpId))
	{
		TRACE(_T ("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT (FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap (&bmpObj);

	UINT nFlags = ILC_MASK;

	switch (bmpObj.bmBitsPixel)
	{
	case 4:
	default:
		nFlags |= ILC_COLOR4;
		break;

	case 8:
		nFlags |= ILC_COLOR8;
		break;

	case 16:
		nFlags |= ILC_COLOR16;
		break;

	case 24:
		nFlags |= ILC_COLOR24;
		break;

	case 32:
		nFlags |= ILC_COLOR32;
		break;
	}

	m_imgList.Create (16, bmpObj.bmHeight, nFlags, 0, 0);
	m_imgList.Add (&bmp, RGB (255, 255, 255));

	m_pEdit->SetIntelliSenseImgList (&m_imgList);
}

void CBCGPVisualStudioGUIDemoView::OnEditGotoLine() 
{
	CGotoLineDlg dlg (this);
	if (dlg.DoModal () != IDOK)
	{
		return;
	}

	m_pEdit->GoToLine (dlg.m_nLineNumber);
}
