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
// EditFrameView.cpp : implementation of the CEditFrameView class
//

#include "stdafx.h"

#include "BCGPOrganizer.h"
#include "EditFrameView.h"
#include "EditFrameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if _MSC_VER >= 1300
	#define WPD_CHARFORMAT CHARFORMAT2
	#define WPD_PARAFORMAT PARAFORMAT2
#else
	#define WPD_CHARFORMAT CHARFORMAT
	#define WPD_PARAFORMAT PARAFORMAT
#endif

struct CCharFormat : public WPD_CHARFORMAT
{
	CCharFormat() {cbSize = sizeof(WPD_CHARFORMAT);}
	BOOL operator==(CCharFormat& cf);
};

int GetTwipSize (CString str)
{
	LPCTSTR lpszText = str;

	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (lpszText[0] == NULL)
		return -
		1; // no text in control

	double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (*lpszText != NULL)
		return -2;   // not terminated properly

	return (d<0.) ? 0 : (int)(d*20.);
}

/////////////////////////////////////////////////////////////////////////////
// CEditFrameView

IMPLEMENT_DYNCREATE(CEditFrameView, CRichEditView)

BEGIN_MESSAGE_MAP(CEditFrameView, CRichEditView)
	//{{AFX_MSG_MAP(CEditFrameView)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FONT_BOX, OnFontDialog)
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_COMMAND(ID_FONT_COLOR, OnFontColor)
	ON_COMMAND(ID_FONT_TEXTHIGHLIGHT, OnFontTextHighlight)
	ON_COMMAND(ID_FONT_FONT, OnFontName)
	ON_COMMAND(ID_FONT_SIZE, OnFontSize)
	ON_COMMAND(ID_FONT_INCREASE, OnFontSizeIncrease)
	ON_COMMAND(ID_FONT_DECREASE, OnFontSizeDecrease)
	ON_COMMAND(ID_FONT_BOLD, OnCharBold)
	ON_UPDATE_COMMAND_UI(ID_FONT_BOLD, OnUpdateCharBold)
	ON_COMMAND(ID_FONT_ITALIC, OnCharItalic)
	ON_UPDATE_COMMAND_UI(ID_FONT_ITALIC, OnUpdateCharItalic)
	ON_COMMAND(ID_FONT_UNDERLINE, OnCharUnderline)
	ON_UPDATE_COMMAND_UI(ID_FONT_UNDERLINE, OnUpdateCharUnderline)
	ON_COMMAND(ID_FONT_STRIKETHROUGH, OnCharStrikethrough)
	ON_UPDATE_COMMAND_UI(ID_FONT_STRIKETHROUGH, OnUpdateCharStrikethrough)
	ON_COMMAND(ID_FONT_CLEARFORMAT, OnFontClear)
	ON_COMMAND(ID_EDIT_PARA_CENTER, OnParaCenter)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PARA_CENTER, OnUpdateParaCenter)
	ON_COMMAND(ID_EDIT_PARA_LEFT, OnParaLeft)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PARA_LEFT, OnUpdateParaLeft)
	ON_COMMAND(ID_EDIT_PARA_RIGHT, OnParaRight)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PARA_RIGHT, OnUpdateParaRight)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_EDIT_PARA_BULLETS, OnBullet)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PARA_BULLETS, OnUpdateBullet)
	ON_EN_CHANGE(AFX_IDW_PANE_FIRST, OnEditChange)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditFrameView construction/destruction

CEditFrameView::CEditFrameView()
{
	m_bIsEndOfPrint = FALSE;
}

CEditFrameView::~CEditFrameView()
{
}

BOOL CEditFrameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CEditFrameView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

	OnFontName ();
	OnFontSize ();

	CCharFormat cf;
	cf.dwMask    = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_STRIKEOUT | CFM_COLOR;
	cf.dwEffects = CFE_AUTOCOLOR;
	SetCharFormat (cf);
}

/////////////////////////////////////////////////////////////////////////////
// CEditFrameView diagnostics

#ifdef _DEBUG
void CEditFrameView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CEditFrameView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditFrameView message handlers

void CEditFrameView::OnEditChange()
{
}

void CEditFrameView::OnFontColor() 
{
	CBCGPRibbonBar* pRibbon = ((CEditFrameDialog*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonColorButton* pColorBtn = DYNAMIC_DOWNCAST (
		CBCGPRibbonColorButton, pRibbon->FindByID (ID_FONT_COLOR));

	if (pColorBtn != NULL)
	{
		COLORREF color = pColorBtn->GetColor ();

		if (color == -1)
		{
			CRichEditView::OnColorDefault ();
		}
		else
		{
			CRichEditView::OnColorPick (color);
		}	
	}
}

void CEditFrameView::OnFontTextHighlight ()
{
#if _MSC_VER >= 1300
/*
	CBCGPRibbonBar* pRibbon = ((CEditFrameDialog*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonColorButton* pColorBtn = DYNAMIC_DOWNCAST (
		CBCGPRibbonColorButton, pRibbon->FindByID (ID_FONT_TEXTHIGHLIGHT));

	if (pColorBtn != NULL)
	{
		COLORREF color = pColorBtn->GetColor ();

		GetCharFormatSelection();
		m_charformat.dwMask = CFM_BACKCOLOR;
		if (color == -1)
		{
			m_charformat.dwEffects = CFE_AUTOBACKCOLOR;
		}
		else
		{
			m_charformat.dwEffects   = NULL;
			m_charformat.crBackColor = color;
		}
		SetCharFormat(m_charformat);
	}
*/
#endif
}

void CEditFrameView::OnFontName() 
{
	USES_CONVERSION;

	CBCGPRibbonBar* pRibbon = ((CEditFrameDialog*) GetTopLevelFrame ())->GetRibbonBar ();
	ASSERT_VALID (pRibbon);

	CBCGPRibbonFontComboBox* pFontCombo = DYNAMIC_DOWNCAST (
		CBCGPRibbonFontComboBox, pRibbon->FindByID (ID_FONT_FONT));
	if (pFontCombo == NULL)
	{
		return;
	}

	CCharFormat cf;
	cf.szFaceName[0] = NULL;
	cf.dwMask = CFM_FACE | CFM_CHARSET;

	const CBCGPFontDesc* pDesc = pFontCombo->GetFontDesc ();
	ASSERT_VALID (pDesc);
	ASSERT(pDesc->m_strName.GetLength() < LF_FACESIZE);

#if _MSC_VER >= 1300
	lstrcpyn(cf.szFaceName, pDesc->m_strName, LF_FACESIZE);
#else
	lstrcpynA(cf.szFaceName,
		T2A((LPTSTR) (LPCTSTR) pDesc->m_strName), LF_FACESIZE);
#endif

	cf.bCharSet = pDesc->m_nCharSet;
	cf.bPitchAndFamily = pDesc->m_nPitchAndFamily;

	SetCharFormat (cf);
}

void CEditFrameView::OnFontSize ()
{
	CBCGPRibbonBar* pRibbon = ((CEditFrameDialog*) GetTopLevelFrame ())->GetRibbonBar ();
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

	if ((nSize >= 0 && nSize < 20) || nSize > 32760)
	{
		return;
	}

	if (nSize > 0)
	{
		CCharFormat cf;
		cf.dwMask = CFM_SIZE;
		cf.yHeight = nSize;

		SetCharFormat (cf);
	}
}

void CEditFrameView::OnFontSizeIncrease()
{
	CBCGPRibbonBar* pRibbon = ((CEditFrameDialog*) GetTopLevelFrame ())->GetRibbonBar ();
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

void CEditFrameView::OnFontSizeDecrease()
{
	CBCGPRibbonBar* pRibbon = ((CEditFrameDialog*) GetTopLevelFrame ())->GetRibbonBar ();
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

void CEditFrameView::OnFontClear()
{
	GetCharFormatSelection();
	m_charformat.dwMask    = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_STRIKEOUT | CFM_COLOR;
	m_charformat.dwEffects = CFE_AUTOCOLOR;
	SetCharFormat(m_charformat);
}

void CEditFrameView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRichEditView::OnLButtonUp(nFlags, point);

	if (/*GetSelectedItem () != NULL ||*/ CBCGPPopupMenu::GetActiveMenu () != NULL)
	{
		return;
	}

	long nStartChar, nEndChar;
	GetRichEditCtrl().GetSel(nStartChar, nEndChar);
	if (nStartChar == nEndChar)
	{
		return;
	}

	CBCGPRibbonFloaty* pFloaty = new CBCGPRibbonFloaty;

	CList<UINT, UINT> lstCmds;

	lstCmds.AddTail (ID_FONT_FONT);
	lstCmds.AddTail (ID_FONT_SIZE);
	lstCmds.AddTail (ID_FONT_INCREASE);
	lstCmds.AddTail (ID_FONT_DECREASE);
	lstCmds.AddTail (ID_FONT_BOLD);
	lstCmds.AddTail (ID_FONT_ITALIC);
	lstCmds.AddTail (ID_FONT_UNDERLINE);
	lstCmds.AddTail (ID_FONT_TEXTHIGHLIGHT);
	lstCmds.AddTail (ID_FONT_COLOR);
//	lstCmds.AddTail (IDR_PARA_BULLETS_MENU);

	pFloaty->SetCommands (((CEditFrameDialog*) GetTopLevelFrame ())->GetRibbonBar (),
		lstCmds);

	ClientToScreen (&point);
	pFloaty->Show (point.x, point.y);
}

void CEditFrameView::OnFontDialog() 
{
	OnFormatFont ();
}

BOOL CEditFrameView::ShowContextMenu (CPoint point)
{
	if (DYNAMIC_DOWNCAST (CBCGPFrameWnd, GetParentFrame ()) == NULL)
	{
		// Maybe, server mode, show the regular menu!
		return FALSE;
	}

	theApp.ShowPopupMenu (IDR_EDITCTRL_MENU, point, this);
/*
	CRichEditCntrItem* pItem = GetSelectedItem();
	if (pItem == NULL || !pItem->IsInPlaceActive())
	{

		return TRUE;
	}

	return FALSE;
*/
	return TRUE;
}

void CEditFrameView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	long nStartChar, nEndChar;
	GetRichEditCtrl().GetSel(nStartChar, nEndChar);
	if (nEndChar - nStartChar <= 1)
	{
		SendMessage (WM_LBUTTONDOWN, nFlags, MAKELPARAM (point.x, point.y));
	}

	CPoint ptScreen = point;
	ClientToScreen (&ptScreen);

	if (!ShowContextMenu (ptScreen))
	{
		Default ();
	}
}

void CEditFrameView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
	if (!ShowContextMenu (point))
	{
		Default ();
	}
}

void CEditFrameView::OnCharStrikethrough()
{
	OnCharEffect(CFM_STRIKEOUT, CFE_STRIKEOUT);
}

void CEditFrameView::OnUpdateCharStrikethrough(CCmdUI* pCmdUI)
{
	OnUpdateCharEffect(pCmdUI, CFM_STRIKEOUT, CFE_STRIKEOUT);
}

void CEditFrameView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (IsClipboardFormatAvailable(CF_TEXT));
}

/////////////////////////////////////////////////////////////////////////////
// CEditFrameView printing

void CEditFrameView::OnFilePrintPreview() 
{
	CEditFrameDialog* pFrame = DYNAMIC_DOWNCAST (CEditFrameDialog, GetParentFrame ());
	if (pFrame != NULL && pFrame->InitPrintPreview ())
	{
		BCGPPrintPreview (this);
	}
}

BOOL CEditFrameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEditFrameView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_bIsEndOfPrint)
	{
		pInfo->m_bContinuePrinting = FALSE;
		return;
	}

	CRichEditView::OnPrepareDC(pDC, pInfo);
}

void CEditFrameView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_bIsEndOfPrint = FALSE;

	CRichEditView::OnBeginPrinting(pDC, pInfo);
}

void CEditFrameView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_bIsEndOfPrint = TRUE;

	CRichEditView::OnEndPrinting(pDC, pInfo);
}

void CEditFrameView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo,
			POINT point, CPreviewView* pPreviewView)
{
	CRichEditView::OnEndPrintPreview(pDC, pInfo, point, pPreviewView);

	CEditFrameDialog* pFrame = DYNAMIC_DOWNCAST (CEditFrameDialog, GetParentFrame ());
	if (pFrame != NULL)
	{
		pFrame->ClosePrintPreview ();
	}
}
