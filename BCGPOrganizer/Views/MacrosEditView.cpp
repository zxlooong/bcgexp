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
// MacrosEditView.cpp : implementation of the CMacrosEditView class
//

#include "stdafx.h"
#include "../BCGPOrganizer.h"
#include "../BCGPOrganizerDoc.h"
#include "../mainfrm.h"

#include "MacrosEditView.h"

//#include "UndoBar.h"
#include "../MacrosEdit/CustomEditCtrl.h"
#include "../MacrosEdit/GotoLineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int GetTwipSize (CString str)
{
	LPCTSTR lpszText = str;

	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (lpszText[0] == NULL)
		return -1; // no text in control

	double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (*lpszText != NULL)
		return -2;   // not terminated properly

	return (d<0.) ? 0 : (int)(d);
}

/////////////////////////////////////////////////////////////////////////////
// CMacrosEditView

IMPLEMENT_DYNCREATE(CMacrosEditView, CBCGPEditView)

BEGIN_MESSAGE_MAP(CMacrosEditView, CBCGPEditView)
	//{{AFX_MSG_MAP(CMacrosEditView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_TOGGLEBOOKMARK, OnEditTogglebookmark)
	ON_COMMAND(ID_DUMMY_REMOVE_ALL_BREAKPOINTS, OnRemoveAllBreakpoints)
	ON_COMMAND(ID_EDIT_TOGGLEBREAKPOINT, OnToggleBreakpoint)
	ON_COMMAND(ID_EDIT_CLEAR_ALLBOOKMARKS, OnClearAllBookmarks)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALLBOOKMARKS, OnUpdateBookmarks)
	ON_COMMAND(ID_EDIT_NEXTBOOKMARK, OnEditNextbookmark)
	ON_UPDATE_COMMAND_UI(ID_EDIT_NEXTBOOKMARK, OnUpdateBookmarks)
	ON_COMMAND(ID_EDIT_PREVIOUSBOOKMARK, OnEditPreviousbookmark)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PREVIOUSBOOKMARK, OnUpdateBookmarks)
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
	ON_COMMAND(ID_FONT_BOLD, OnFontBold)
	ON_UPDATE_COMMAND_UI(ID_FONT_BOLD, OnUpdateFontBold)
	ON_COMMAND(ID_FONT_ITALIC, OnFontItalic)
	ON_UPDATE_COMMAND_UI(ID_FONT_ITALIC, OnUpdateFontItalic)
	ON_COMMAND(ID_FONT_UNDERLINE, OnFontUnderline)
	ON_UPDATE_COMMAND_UI(ID_FONT_UNDERLINE, OnUpdateFontUnderline)
	ON_COMMAND(ID_FONT_STRIKETHROUGH, OnFontStrikethrough)
	ON_UPDATE_COMMAND_UI(ID_FONT_STRIKETHROUGH, OnUpdateFontStrikethrough)
	ON_COMMAND(ID_FONT_CLEARFORMAT, OnFontClear)
	ON_UPDATE_COMMAND_UI(ID_FONT_QUALITY, OnUpdateFontQuality)
	ON_COMMAND(ID_FONT_QUALITY_DEFAULT, OnFontQualityDefault)
	ON_UPDATE_COMMAND_UI(ID_FONT_QUALITY_DEFAULT, OnUpdateFontQualityDefault)
	ON_COMMAND(ID_FONT_QUALITY_NONANTIALIAZED, OnFontQualityNonAntialiazed)
	ON_UPDATE_COMMAND_UI(ID_FONT_QUALITY_NONANTIALIAZED, OnUpdateFontQualityNonAntialiazed)
	ON_COMMAND(ID_FONT_QUALITY_CLEARTYPE, OnFontQualityCleartype)
	ON_UPDATE_COMMAND_UI(ID_FONT_QUALITY_CLEARTYPE, OnUpdateFontQualityCleartype)
	ON_COMMAND(ID_FONT_FONT, OnFontName)
	ON_COMMAND(ID_FONT_SIZE, OnFontSize)
	ON_COMMAND(ID_FONT_INCREASE, OnFontSizeIncrease)
	ON_COMMAND(ID_FONT_DECREASE, OnFontSizeDecrease)
	ON_COMMAND(ID_FONT_BOX, OnFontDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacrosEditView construction/destruction

CMacrosEditView::CMacrosEditView()
	: m_bXMLSettings    (FALSE)
	, m_uiXMLSettingsID (IDR_EDITOR_XML_SETTINGS)
	, m_uiMacrosID      (0)
{
	DisableMainframeForFindDlg (FALSE);
}

CMacrosEditView::~CMacrosEditView()
{
}

BOOL CMacrosEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMacrosEditView drawing

void CMacrosEditView::OnDraw(CDC* /*pDC*/)
{
	CBCGPOrganizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CMacrosEditView diagnostics

#ifdef _DEBUG
void CMacrosEditView::AssertValid() const
{
	CBCGPEditView::AssertValid();
}

void CMacrosEditView::Dump(CDumpContext& dc) const
{
	CBCGPEditView::Dump(dc);
}

CBCGPOrganizerDoc* CMacrosEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPOrganizerDoc)));
	return (CBCGPOrganizerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMacrosEditView message handlers

void CMacrosEditView::OnContextMenu(CWnd*, CPoint point)
{
	ASSERT_VALID (m_pEdit);

	CPoint pt(point);

	ScreenToClient(&pt);
	if (pt.x < m_pEdit->m_nLeftMarginWidth)
	{
		pt.x = m_pEdit->m_nLeftMarginWidth;
		m_pEdit->SetCaret(m_pEdit->HitTest(pt));

		theApp.ShowPopupMenu (IDR_EDIT_POPUP_SELECTIONMARGIN, point, this);
	}
	else
	{
		theApp.ShowPopupMenu (IDR_EDIT_MENU, point, this);
	}
}

CBCGPEditCtrl* CMacrosEditView::CreateEdit ()
{
	m_pEdit = new CCustomEditCtrl;
	return m_pEdit;
}

int CMacrosEditView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	ResetFindCombo();

	CBCGPOrganizerDoc* pDoc = GetDocument();
	if (pDoc != NULL)
	{
		ASSERT_VALID (pDoc);
		pDoc->SetModifiedFlag(m_pEdit->IsModified());
	}

	ModifyStyle(0,WS_VISIBLE);
	return 0;
}

void CMacrosEditView::OnInitialUpdate() 
{
	CBCGPEditView::OnInitialUpdate();

	ASSERT_VALID (m_pEdit);

	if (m_uiXMLSettingsID != 0)
	{
		LPCTSTR lpszResourceName = MAKEINTRESOURCE (m_uiXMLSettingsID);
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
//DR:
	m_pEdit->EnableIntelliSense(!m_bXMLSettings);
	m_pEdit->EnableBreakpoints(TRUE);
	m_pEdit->RemoveAllBreakpoints();

/*
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
*/
	m_pEdit->EnableOutlineParser (TRUE);
	m_pEdit->UpdateAutoOutlining ();
}

void CMacrosEditView::OnUpdateCaretPos(CCmdUI* pCmdUI)
{
	ASSERT_VALID (m_pEdit);

	CString str;
	str.Format (m_strCaretPosFmt, m_pEdit->GetCurRow () + 1, m_pEdit->GetCurColumn () + 1);

	pCmdUI->SetText (str);
	
	pCmdUI->Enable();
}

void CMacrosEditView::RestoreDefaultView(UINT /*uiExampleID = -1 */)
{
	ASSERT_VALID (m_pEdit);
//DR:
/*
	if (uiExampleID == ID_EXAMPLE_CPP)
	{
		// Insert unnamed Bookmarks
		m_pEdit->ToggleMarker (3, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (11, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (20, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (30, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (45, g_dwBCGPEdit_BookMark);
		m_pEdit->ToggleMarker (48, g_dwBCGPEdit_BookMark);

		// Insert Breakpoints
		m_pEdit->ToggleBreakpoint(20);
	}
*/
}

void CMacrosEditView::LoadExample (UINT nID, CString strName)
{
	if (nID != m_uiMacrosID)
	{
		m_uiMacrosID = nID;
		m_strMacrosName = strName;

		RestoreDefaultData();

		UpdateCaptionText ();
	}
}

BOOL CMacrosEditView::RestoreDefaultData()
{
	ASSERT_VALID (m_pEdit);

	BOOL bRet = FALSE;

	if (m_uiMacrosID == 0)
	{
		return FALSE;
	}

	LPCTSTR lpszResourceName = MAKEINTRESOURCE (m_uiMacrosID);
	ASSERT(lpszResourceName != NULL);

	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, _T("EDITOR_EXAMPLES"));
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, _T("EDITOR_EXAMPLES"));
	
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
				RestoreDefaultView(m_uiMacrosID);

				bRet = TRUE;
			}

			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}
	}

	return bRet;
}

void CMacrosEditView::ResetDefaultFont()
{
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	CDC* pDC = GetDC();

	CFont* pFont = pDC->SelectObject(CFont::FromHandle(hFont));
	pDC->SelectObject(pFont);
	::DeleteObject(hFont);

	pFont->GetLogFont (&m_LogFont);

	CString strFontName(_T("Courier New"));
	CopyMemory(m_LogFont.lfFaceName,(LPCTSTR)strFontName,(strFontName.GetLength() + 1) * sizeof(TCHAR));
	m_LogFont.lfHeight      = -14;
	m_LogFont.lfWidth       = 0;
	m_LogFont.lfEscapement  = 0;
	m_LogFont.lfOrientation = 0;
	m_LogFont.lfWeight      = FW_NORMAL;
	m_LogFont.lfItalic      = 0;
	m_LogFont.lfUnderline   = 0;
	m_LogFont.lfStrikeOut   = 0;
	m_LogFont.lfQuality     = DEFAULT_QUALITY;

	UpdateFont ();

	CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();

	if (pRibbon != NULL)
	{
		ASSERT_VALID (pRibbon);

		CBCGPRibbonComboBox* pNameCombo = DYNAMIC_DOWNCAST (
			CBCGPRibbonComboBox, pRibbon->FindByID (ID_FONT_FONT));
		if (pNameCombo != NULL)
		{
			pNameCombo->SelectItem (strFontName);
		}

		CBCGPRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST (
			CBCGPRibbonComboBox, pRibbon->FindByID (ID_FONT_SIZE));
		if (pSizeCombo != NULL)
		{
			pSizeCombo->SelectItem (5);
		}
	}
}

void CMacrosEditView::ResetFindCombo()
{
//DR:
/*
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
*/
}

void CMacrosEditView::VerifyFindString(CBCGPToolbarComboBoxButton* pFindCombo,
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

void CMacrosEditView::OnShowHint()
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ShowContextTip();
}

void CMacrosEditView::OnFind()
{
//DR:
/*
	VerifyFindString(((CMainFrame*)AfxGetMainWnd())->GetFindCombo(),
					 m_strFindText);
*/
	OnFindReplace(0, 0);
}

void CMacrosEditView::OnFindNext()
{
	m_dwFindMask |= FR_DOWN;
	OnFind();
}

void CMacrosEditView::OnFindPrev()
{
	m_dwFindMask &= ~FR_DOWN;
	OnFind();
}

void CMacrosEditView::OnTextNotFound (LPCTSTR lpszFind)
{
	CString strError;
	strError.Format (IDS_STRING_NOT_FOUND_FMT, 
		lpszFind == NULL ? _T("") : lpszFind);

	MessageBox (strError);
}

void CMacrosEditView::OnLButtonDblClk(UINT /*nFlags*/, CPoint /*point*/) 
{
	//DR:
	//theApp.OnViewDoubleClick (this, IDR_BCGDEVTYPE0);
}

void CMacrosEditView::OnEditTogglebookmark() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleMarker (m_pEdit->GetCurRow (), g_dwBCGPEdit_BookMark);
}

void CMacrosEditView::OnRemoveAllBreakpoints()
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->RemoveAllBreakpoints();
}

void CMacrosEditView::OnToggleBreakpoint() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleBreakpoint();
}

void CMacrosEditView::OnClearAllBookmarks()
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->DeleteAllMarkers(g_dwBCGPEdit_BookMark);
}

void CMacrosEditView::OnEditNextbookmark() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->GoToNextMarker(g_dwBCGPEdit_BookMark, TRUE);
}

void CMacrosEditView::OnEditPreviousbookmark() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->GoToNextMarker(g_dwBCGPEdit_BookMark,FALSE);
}

void CMacrosEditView::OnUpdateBookmarks(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable(m_pEdit->HasMarkers(g_dwBCGPEdit_BookMark));	
}

//DR:
/*
void CMacrosEditView::DoUndo(CUndoButton* pUndoBtn)
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
*/
void CMacrosEditView::OnEditListmembers() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->InvokeIntelliSense();
}

void CMacrosEditView::OnUpdateEditListmembers(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);

	CObList lstIntelliSenseData;

	m_pEdit->FillIntelliSenseList(lstIntelliSenseData);
	pCmdUI->Enable(!lstIntelliSenseData.IsEmpty());
	
	m_pEdit->ReleaseIntelliSenseList(lstIntelliSenseData);
}

void CMacrosEditView::AttachXMLSettings(const CString& /*strXMLFileName*/)
{
	ASSERT_VALID (m_pEdit);

	m_pEdit->RemoveXMLSettings();
	m_pEdit->EnableBreakpoints(FALSE);

}

void CMacrosEditView::GetUndoActions(CStringList& lstActions) const
{
	GetUndoRedoActions(lstActions, TRUE);
}

void CMacrosEditView::GetRedoActions(CStringList& lstActions) const
{
	GetUndoRedoActions(lstActions, FALSE);
}

void CMacrosEditView::GetUndoRedoActions(CStringList& lstActions, BOOL bUndo) const
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

BOOL CMacrosEditView::UATToString(DWORD dwUAT, CString& strAction) const
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

void CMacrosEditView::OnEditIncreaseIdent() 
{
	ASSERT_VALID (m_pEdit);
	VERIFY(m_pEdit->IndentSelection(TRUE));
}

void CMacrosEditView::OnUpdateEditIncreaseIdent(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable(m_pEdit->IsIndentEnabled(TRUE));
}

void CMacrosEditView::OnEditDecreaseIdent() 
{
	ASSERT_VALID (m_pEdit);
	VERIFY(m_pEdit->IndentSelection(FALSE));
}

void CMacrosEditView::OnUpdateEditDecreaseIdent(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable(m_pEdit->IsIndentEnabled(FALSE));
}

BOOL CMacrosEditView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	ASSERT_VALID (m_pEdit);

	GetDocument()->SetModifiedFlag(m_pEdit->IsModified());
//DR:
//	GetDocument()->CheckTitle();

	return CBCGPEditView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMacrosEditView::OnEditFindNextWord()
{
	ASSERT_VALID (m_pEdit);

	CString strWord;
	if (m_pEdit->GetWordFromOffset (m_pEdit->GetCurOffset (), strWord))
	{
		m_pEdit->FindText (strWord, TRUE, TRUE, TRUE);
	}
}

void CMacrosEditView::OnEditHideselection() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->HideSelection ();
}

void CMacrosEditView::OnUpdateEditHideselection(CCmdUI* pCmdUI) 
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

void CMacrosEditView::OnEditStophidingcurrent() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->StopHidingCurrent ();
}

void CMacrosEditView::OnUpdateEditStophidingcurrent(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (
		m_pEdit->IsOutliningEnabled () &&
		!m_pEdit->IsAutoOutliningEnabled ());
}

void CMacrosEditView::OnEditToggleoutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleOutlining ();
}

void CMacrosEditView::OnUpdateEditToggleoutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CMacrosEditView::OnEditTogglealloutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->ToggleAllOutlining ();
}

void CMacrosEditView::OnUpdateEditTogglealloutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CMacrosEditView::OnEditCollapsetodefinitions() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->CollapseToDefinitions ();
}

void CMacrosEditView::OnUpdateEditCollapsetodefinitions(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CMacrosEditView::OnEditStopoutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->StopOutlining ();
}

void CMacrosEditView::OnUpdateEditStopoutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->Enable (
		m_pEdit->IsOutliningEnabled () &&
		m_pEdit->IsAutoOutliningEnabled ());
}

void CMacrosEditView::OnEditAutooutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->EnableAutoOutlining (!m_pEdit->IsAutoOutliningEnabled ());
}

void CMacrosEditView::OnUpdateEditAutooutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->SetCheck (m_pEdit->IsAutoOutliningEnabled () ? 1 : 0);
	pCmdUI->Enable (m_pEdit->IsOutliningEnabled ());
}

void CMacrosEditView::OnEditEnableoutlining() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->EnableOutlining (!m_pEdit->IsOutliningEnabled ());
	m_pEdit->SetOutlineMargin (m_pEdit->IsOutliningEnabled ());
}

void CMacrosEditView::OnUpdateEditEnableoutlining(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->SetCheck (m_pEdit->IsOutliningEnabled () ? 1 : 0);
}

void CMacrosEditView::OnEditLinenumbers() 
{
	ASSERT_VALID (m_pEdit);
	m_pEdit->SetLineNumbersMargin (!m_pEdit->IsLineNumbersMarginVisible ());
}

void CMacrosEditView::OnUpdateEditLinenumbers(CCmdUI* pCmdUI) 
{
	ASSERT_VALID (m_pEdit);
	pCmdUI->SetCheck (m_pEdit->IsLineNumbersMarginVisible () ? 1 : 0);
}

void CMacrosEditView::OnChangeVisualStyle ()
{
	if (m_imgList.GetSafeHandle () != NULL)
	{
		m_imgList.DeleteImageList ();
	}

	UINT uiBmpId = globalData.IsHighContastMode () || globalData.m_nBitsPerPixel <= 8
		? IDB_INTELLISENSE
		: IDB_INTELLISENSE_HC;

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

void CMacrosEditView::OnEditGotoLine() 
{
	CGotoLineDlg dlg (this);
	if (dlg.DoModal () != IDOK)
	{
		return;
	}

	m_pEdit->GoToLine (dlg.m_nLineNumber);
}

void CMacrosEditView::UpdateFont ()
{
	if (m_Font.GetSafeHandle () != NULL)
	{
		m_Font.DeleteObject ();
	}

	m_Font.CreateFontIndirect (&m_LogFont);
	m_pEdit->SetFont (&m_Font);
}

void CMacrosEditView::OnFontClear ()
{
	ResetDefaultFont ();
};

void CMacrosEditView::OnFontBold()
{
	m_LogFont.lfWeight = m_LogFont.lfWeight == FW_BOLD ? FW_NORMAL : FW_BOLD;

	UpdateFont ();
}

void CMacrosEditView::OnUpdateFontBold(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_LogFont.lfWeight == FW_BOLD);
}

void CMacrosEditView::OnFontItalic()
{
	m_LogFont.lfItalic = !m_LogFont.lfItalic;

	UpdateFont ();
}

void CMacrosEditView::OnUpdateFontItalic(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_LogFont.lfItalic);
}

void CMacrosEditView::OnFontUnderline()
{
	m_LogFont.lfUnderline = !m_LogFont.lfUnderline;

	UpdateFont ();
}

void CMacrosEditView::OnUpdateFontUnderline(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_LogFont.lfUnderline);
}

void CMacrosEditView::OnFontStrikethrough()
{
	m_LogFont.lfStrikeOut = !m_LogFont.lfStrikeOut;

	UpdateFont ();
}

void CMacrosEditView::OnUpdateFontStrikethrough(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_LogFont.lfStrikeOut);
}

void CMacrosEditView::OnUpdateFontQuality(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CMacrosEditView::OnFontQualityDefault()
{
	m_LogFont.lfQuality = DEFAULT_QUALITY;

	UpdateFont ();
}

void CMacrosEditView::OnUpdateFontQualityDefault(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_LogFont.lfQuality == DEFAULT_QUALITY);
}

void CMacrosEditView::OnFontQualityNonAntialiazed()
{
	m_LogFont.lfQuality = NONANTIALIASED_QUALITY;

	UpdateFont ();
}

void CMacrosEditView::OnUpdateFontQualityNonAntialiazed(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_LogFont.lfQuality == NONANTIALIASED_QUALITY);
}

void CMacrosEditView::OnFontQualityCleartype()
{
	m_LogFont.lfQuality = 5;

	UpdateFont ();
}

void CMacrosEditView::OnUpdateFontQualityCleartype(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_LogFont.lfQuality == 5);
}

void CMacrosEditView::OnFontName() 
{
	USES_CONVERSION;

	CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonFontComboBox* pFontCombo = DYNAMIC_DOWNCAST (
		CBCGPRibbonFontComboBox, pRibbon->FindByID (ID_FONT_FONT));
	if (pFontCombo == NULL)
	{
		return;
	}

	const CBCGPFontDesc* pDesc = pFontCombo->GetFontDesc ();
	ASSERT_VALID (pDesc);
	ASSERT(pDesc->m_strName.GetLength() < LF_FACESIZE);

#if _MSC_VER >= 1300
	lstrcpyn(m_LogFont.lfFaceName, pDesc->m_strName, LF_FACESIZE);
#else
	lstrcpynA(m_LogFont.lfFaceName,
		T2A((LPTSTR) (LPCTSTR) pDesc->m_strName), LF_FACESIZE);
#endif

	UpdateFont ();
}

void CMacrosEditView::OnFontSize ()
{
	CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST (
		CBCGPRibbonComboBox, pRibbon->FindByID (ID_FONT_SIZE));
	if (pSizeCombo == NULL)
	{
		return;
	}

	int nSize = GetTwipSize (pSizeCombo->GetItem (-1));

	if (nSize == -2)
	{
		return;
	}

	if (nSize > 32760)
	{
		return;
	}

	m_LogFont.lfHeight = -nSize;

	UpdateFont ();
}

void CMacrosEditView::OnFontSizeIncrease()
{
	CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST (
		CBCGPRibbonComboBox, pRibbon->FindByID (ID_FONT_SIZE));
	if (pSizeCombo == NULL)
	{
		return;
	}

	int nItem = pSizeCombo->GetCurSel ();

	if (nItem < pSizeCombo->GetCount () - 1)
	{
		pSizeCombo->SelectItem (nItem + 1);

		OnFontSize ();
	}
}

void CMacrosEditView::OnFontSizeDecrease()
{
	CBCGPRibbonBar* pRibbon = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST (
		CBCGPRibbonComboBox, pRibbon->FindByID (ID_FONT_SIZE));
	if (pSizeCombo == NULL)
	{
		return;
	}

	int nItem = pSizeCombo->GetCurSel ();
	if (nItem > 0)
	{
		pSizeCombo->SelectItem (nItem - 1);

		OnFontSize ();
	}
}

void CMacrosEditView::OnFontDialog()
{
	CFontDialog fd(&m_LogFont);

	if (fd.DoModal ())
	{
		UpdateFont ();
	}
}

void CMacrosEditView::UpdateCaptionText ()
{
	CBCGPOrganizerDoc* pDoc = GetDocument ();
	if (pDoc == NULL || pDoc->GetMode () != CBCGPOrganizerDoc::e_ModeMacros)
	{
		return;
	}

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());

	if (pFrame != NULL)
	{
		pFrame->SetCaptionText (m_strMacrosName);
	}
}

void CMacrosEditView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPEditView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		UpdateCaptionText ();
	}
}
