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
// CustomEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "CustomEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct TipString
{
	LPCTSTR lpszTip;
	LPCTSTR lpszContent;
};

static TipString g_aTipText[] = 
{
	{_T("CMyClass"),_T("class CMyClass")},
	{_T("ind"),_T("int ind = -1")},
	{_T("memset"),_T("void * memset(void *, int, size_t)")},
	{_T("m_lf"),_T("LOGFONT CMyClass::m_lf")},
	{_T("m_bTrace"),_T("BOOL CMyClass::m_bTrace")},
	{_T("OnDestroy"),_T("void CMyClass::OnDestroy ()")},
	{_T("DoMain"),_T("int CMyClass::DoMain ()")},
	{_T("printf"),_T("int printf (const char *, ...)")}, 
	{_T("GetAppName"),_T("const char* CMyClass::GetAppName()")},
	{_T("EnableTrace"),_T("void CMyClass::EnableTrace(BOOL bTrace = TRUE)")},
	{_T("bTrace"),_T("BOOL bTrace = TRUE")},
	{_T("DO_TRACE"),_T("#define DO_TRACE(bTrace, lpszText)  { if (bTrace) { printf(\"%s\\n\",lpszText); } }")},
	{_T("main"),_T("int main(int argc, char* argv[])")},
	{_T("pMyClass"),_T("CMyClass* pMyClass = new CMyClass(argc, argv)")},
	{_T("nRet"),_T("int nRet = pMyClass->DoMain()")}
};

struct StringIndex
{
	LPCTSTR lpszName;
	int		nIndex;
};

static StringIndex g_aStringIndex1[] =
{
	{_T("CMyClass"), 3},
	{_T("DoMain"), 3},
	{_T("EnableTrace"), 3},
	{_T("GetAppName"), 3},
	{_T("m_argc"), 5},
	{_T("m_argv"), 5},
	{_T("m_bTrace"), 4},
	{_T("m_lf"), 4},
	{_T("OnDestroy"), 6},
	{ NULL }
};

static StringIndex g_aStringIndex2[] =
{
	{_T("lfHeight"), 7},
	{_T("lfWidth"), 7},
	{_T("lfEscapement"), 7},
	{_T("lfOrientation"), 7},
	{_T("lfWeight"), 7},
	{_T("lfItalic"), 7},
	{_T("lfUnderline"), 7},
	{_T("lfStrikeOut"), 7},
	{_T("lfCharSet"), 7},
	{_T("lfOutPrecision"), 7},
	{_T("lfClipPrecision"), 7},
	{_T("lfQuality"), 7},
	{_T("lfPitchAndFamily"), 7},
	{_T("lfFaceName"), 7},
	{ NULL }
};

struct IntelliStringArray
{
	LPCTSTR lpszName;
	StringIndex* ptr;
};

static IntelliStringArray g_aIntelliStringArray[] =
{
	{_T("this->"), g_aStringIndex1},
	{_T("pMyClass->"), g_aStringIndex1},
	{_T("CMyClass::"), g_aStringIndex1},
	{_T("this->m_lf."), g_aStringIndex2},
	{_T("pMyClass->m_lf."), g_aStringIndex2},
	{_T("CMyClass::m_lf."), g_aStringIndex1},
	{_T ("this->m_lf.lfFaceName->"), NULL},
	{_T ("pMyClass->m_lf.lfFaceName->"), NULL},
	{_T ("this->m_argv->"), NULL},
	{_T ("pMyClass->m_argv->"), NULL},
};


/////////////////////////////////////////////////////////////////////////////
// CCustomEditCtrl

CStringList CCustomEditCtrl::m_lstFind;

CCustomEditCtrl::CCustomEditCtrl()
{
	m_bEnableBreakpoints = FALSE;
	m_bCheckColorTags = FALSE;
	m_bCopyRTFToClipboard = TRUE;
	EnableGradientMarkers (TRUE);

	PrepareIntelliSense();
}

void CCustomEditCtrl::PrepareIntelliSense()
{
	int ind;
	for (ind = sizeof(g_aIntelliStringArray) / (sizeof(IntelliStringArray));
		 ind-- != 0;
		 m_mIntelliString.SetAt(g_aIntelliStringArray[ind].lpszName,g_aIntelliStringArray[ind].ptr));

	for (ind = sizeof(g_aTipText) / sizeof(TipString);
		 ind-- != 0;
		 m_mTipString.SetAt(g_aTipText[ind].lpszTip,g_aTipText[ind].lpszContent));
}

CCustomEditCtrl::~CCustomEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CCustomEditCtrl, CBCGPEditCtrl)
	//{{AFX_MSG_MAP(CCustomEditCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustomEditCtrl message handlers

BOOL CCustomEditCtrl::FindText(LPCTSTR lpszFind, BOOL bNext /* = TRUE */, BOOL bCase /* = TRUE */, BOOL bWholeWord /* = FALSE */)
{
	POSITION pos = m_lstFind.Find(lpszFind);
	if (pos != NULL)
	{
		m_lstFind.RemoveAt (pos);
	}

	m_lstFind.AddHead(lpszFind);

	return CBCGPEditCtrl::FindText(lpszFind, bNext, bCase, bWholeWord);
}

void CCustomEditCtrl::OnDrawMarker (CDC* pDC, CRect rectMarker, const CBCGPEditMarker* pMarker)
{
	if (pMarker->m_dwMarkerType & g_dwBreakPointType)
	{
		rectMarker.DeflateRect (1, 1);
		rectMarker.left = rectMarker.left + rectMarker.Width () / 2 - rectMarker.Height () / 2;
		rectMarker.right = rectMarker.left + rectMarker.Height ();

		if (m_bGradientMarkers && globalData.m_nBitsPerPixel >= 32)
		{
			m_ImageBreak.DrawEx (pDC, rectMarker, 0,
				CBCGPToolBarImages::ImageAlignHorzCenter,
				CBCGPToolBarImages::ImageAlignVertTop);
		}
		else
		{
			CBrush br (RGB (127, 0, 0));
			CPen pen (PS_SOLID, 1, RGB (127, 0, 0));
			CBrush* pBrOld = pDC->SelectObject (&br);
			CPen* pOldPen = pDC->SelectObject (&pen);

			pDC->Ellipse (rectMarker);
			pDC->SelectObject (pBrOld);
			pDC->SelectObject (pOldPen);
		}
	}
	else if (pMarker->m_dwMarkerType & g_dwCurrLineType)
	{
		if (m_bGradientMarkers && globalData.m_nBitsPerPixel >= 32)
		{
			m_ImageCurrent.DrawEx (pDC, rectMarker, 0,
				CBCGPToolBarImages::ImageAlignHorzCenter,
				CBCGPToolBarImages::ImageAlignVertTop);
		}
		else
		{
			CBrush br (RGB (255, 255, 0));
			CPen pen (PS_SOLID, 1, RGB (127, 0, 0));
			CBrush* pBrOld = pDC->SelectObject (&br);
			CPen* pOldPen = pDC->SelectObject (&pen);

			pDC->Ellipse (rectMarker);
			pDC->SelectObject (pBrOld);
			pDC->SelectObject (pOldPen);
		}
	}
	else
	{
		CBCGPEditCtrl::OnDrawMarker (pDC, rectMarker, pMarker);
	}
}

int CCustomEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (m_lstFind.IsEmpty ())
	{
		CBCGPToolbarComboBoxButton* pSrcCombo = NULL;
		CObList listButtons;

		if (CBCGPToolBar::GetCommandButtons (ID_EDIT_FIND_COMBO, listButtons) > 0)
		{
			for (POSITION posCombo = listButtons.GetHeadPosition (); 
				pSrcCombo == NULL && posCombo != NULL;)
			{
				CBCGPToolbarComboBoxButton* pCombo = 
					DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton, listButtons.GetNext (posCombo));

				if (pCombo != NULL)
				{
					pSrcCombo = pCombo;
				}
			}
		}

		if (pSrcCombo != NULL)
		{
			if (const int nMax = (int) pSrcCombo->GetCount())
			{
				CString sText;
				CComboBox* pCombo = pSrcCombo->GetComboBox();
				
				for (int i = 0; i < nMax; i++)
				{
					pCombo->GetLBText(i,sText);
					m_lstFind.AddTail (sText);
				}

				pCombo->SetCurSel(0);
			}
		}
	}

	m_ImageBreak.Load (IDB_BREAK);
	m_ImageBreak.SetSingleImage ();

	m_ImageCurrent.Load (IDB_CURRENT);
	m_ImageCurrent.SetSingleImage ();

	return 0;
}

BOOL CCustomEditCtrl::CheckIntelliMark(const CString& strBuffer, int& nOffset, CString& strWordSuffix) const
{
	BOOL bIntelliMark = (strBuffer.GetAt (nOffset) == _T ('.'));

	if (bIntelliMark)
	{
		strWordSuffix = _T('.');
	}
	else if (strBuffer.GetAt (nOffset) == _T ('>'))
	{
		int nTempOffset = nOffset;
		
		if (GetNextPos(strBuffer, m_strNonSelectableChars, nTempOffset, FALSE) >= 0)
		{
			if (strBuffer.GetAt (nTempOffset) == _T ('-'))
			{
				strWordSuffix = _T("->");
				nOffset = nTempOffset;
				bIntelliMark = TRUE;
			}
		}
	}
	else if (strBuffer.GetAt (nOffset) == _T (':'))
	{
		int nTempOffset = nOffset;
		
		if (GetNextPos(strBuffer, m_strNonSelectableChars, nTempOffset, FALSE) >= 0)
		{
			if (strBuffer.GetAt (nTempOffset) == _T (':'))
			{
				strWordSuffix = _T("::");
				nOffset = nTempOffset;
				bIntelliMark = TRUE;
			}
		}
	}

	if (bIntelliMark)
	{
		nOffset--;
	}

	return bIntelliMark;
}

BOOL CCustomEditCtrl::OnBeforeInvokeIntelliSense (const CString& strBuffer, int& nCurrOffset, CString& strIntelliSence) const
{
	if (!IsIntelliSenseEnabled())
	{
		return FALSE;
	}
	
	strIntelliSence.Empty();

	int nOffset = nCurrOffset;

	if (nOffset > strBuffer.GetLength())
	{
		nOffset = strBuffer.GetLength();
	}

	if (nOffset >= 0)
	{
		for (--nOffset;
			 nOffset >= 0 &&
			 m_strIntelliSenseChars.Find(strBuffer.GetAt(nOffset)) == -1 &&
			 (m_strNonSelectableChars.Find(strBuffer.GetAt(nOffset)) >= 0 ||
			  m_strWordDelimeters.Find(strBuffer.GetAt(nOffset)) == -1);
			 nOffset--);

		if (nOffset >= 0 &&
			FillIntelliSenceWord(strBuffer,nOffset,strIntelliSence) &&
			IsIntelliSenceWord(strIntelliSence))
		{
			nCurrOffset = nOffset + 1;
			return TRUE;
		}
	}
	else
	{
		ASSERT(FALSE);
	}

	return FALSE;
}

BOOL CCustomEditCtrl::FillIntelliSenseList (CObList& lstIntelliSenseData,
											LPCTSTR lpszIntelliSense /* = NULL */) const
{
	if (lpszIntelliSense == NULL)
	{
		BOOL bRet;
		CString strIntelliSence;
		int nCurrOffset = m_nCurrOffset;
		
		if (!OnBeforeInvokeIntelliSense(m_strBuffer, nCurrOffset, strIntelliSence))
		{
			return FALSE;
		}

		bRet = FillIntelliSenseList(lstIntelliSenseData, strIntelliSence.GetBuffer(0));
		ASSERT(bRet);

		return bRet;
	}

	if (!IsIntelliSenseEnabled() ||
		!IsIntelliSenceWord(lpszIntelliSense))
	{
		return FALSE;
	}
	
	StringIndex* pStringIndex;

	if (!m_mIntelliString.Lookup(lpszIntelliSense, (void*&)pStringIndex))
	{
		return FALSE;
	}
	
	CBCGPIntelliSenseData* pData;
	lstIntelliSenseData.RemoveAll();
	
	for (int ind = 0; pStringIndex[ind].lpszName != NULL; ind++)
	{
		pData = new CBCGPIntelliSenseData;
		pData->m_strItemName = pStringIndex[ind].lpszName;
		pData->m_nImageListIndex = pStringIndex[ind].nIndex;
		lstIntelliSenseData.AddTail (pData);
	}

	return TRUE;
}

BOOL CCustomEditCtrl::IsIntelliSenceWord(const CString& strWord) const
{
	if (!IsIntelliSenseEnabled())
	{
		return FALSE;
	}
	
	StringIndex* pStringIndex;
	
	if (m_mIntelliString.Lookup(strWord, (void*&)pStringIndex))
	{
		return TRUE; 
	}

	return FALSE;
}

BOOL CCustomEditCtrl::OnGetTipText (CString& strTipString)
{
	CPoint point;
	::GetCursorPos (&point);
	ScreenToClient (&point);

	CString strText;
	BOOL bIsHyperlink = m_bEnableHyperlinkSupport && GetHyperlinkToolTip (strText);
	BOOL bIsHiddenTextFromPoint = !bIsHyperlink && m_bEnableOutlining && GetHiddenTextFromPoint (point, strText);
	BOOL bIsWordFromPoint = !bIsHyperlink && !bIsHiddenTextFromPoint && GetWordFromPoint (point, strText);

	if ((bIsHiddenTextFromPoint || bIsHyperlink) && strText == strTipString)
	{
		return TRUE;
	}
	else if (m_mTipString.Lookup(strTipString,strTipString))
	{
		return TRUE; 
	}
	else if (IsIntelliSenseEnabled() && !bIsWordFromPoint)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CCustomEditCtrl::IntelliSenseCharUpdate(const CString& strBuffer, int nCurrOffset, TCHAR nChar, CString& strIntelliSense)
{
	if (!IsIntelliSenseEnabled())
	{
		return FALSE;
	}
	
	if (nChar == _T('.'))
	{
		if ((nCurrOffset > 0) && (nCurrOffset <= strBuffer.GetLength()) &&
			strBuffer.GetAt(nCurrOffset - 1) == nChar)
		{
			CString strWord;
			int nOffset = nCurrOffset;

			if (!OnBeforeInvokeIntelliSense(strBuffer, nOffset, strWord))
			{
				nOffset = strWord.GetLength();
				if ((nOffset > 1) && (strWord.GetAt(nOffset - 1) == nChar))
				{
					strWord.SetAt(nOffset - 1, _T('-'));
					strWord += _T('>');
					nOffset++;

					if (IsIntelliSenceWord(strWord))
					{
						strIntelliSense = _T("->");
						return TRUE;
					}
				}
			}
		}
		else
		{
			ASSERT(FALSE);
		}
	}

	return FALSE;
}

BOOL CCustomEditCtrl::EnableBreakpoints(BOOL bFl /* = TRUE */)
{
	const BOOL bEnableBreakpoints = m_bEnableBreakpoints;
	m_bEnableBreakpoints = bFl;

	return bEnableBreakpoints;
}

int CCustomEditCtrl::GetNextPos(const CString& strBuffer, const CString& strSkipChars, int& nPos, BOOL bForward)
{
	if (bForward)
	{
		for (int nLen = strBuffer.GetLength();
			 nPos < nLen &&
			 strSkipChars.Find(strBuffer.GetAt(nPos)) >= 0;
			 nPos++);
	}
	else
	{
		for (--nPos;
			 nPos >= 0 &&
			 strSkipChars.Find(strBuffer.GetAt(nPos)) >= 0;
			 nPos--);
	}

	return nPos;
}

BOOL CCustomEditCtrl::FillIntelliSenceWord(const CString& strBuffer, int nOffset, CString& strIntelliSence) const
{
	CString strISWord, strWordSuffix;

	if (!CheckIntelliMark(strBuffer,nOffset,strWordSuffix) || nOffset >= 0)
	{
		do
		{
			int nStartOffset = -1,
				nEndOffset = -1;
			
			FindWordStartFinish (nOffset, strBuffer, nStartOffset, nEndOffset);
			
			if ((nStartOffset < nEndOffset) && (nStartOffset >= 0))
			{
				const CString& strWord = strBuffer.Mid(nOffset = nStartOffset, nEndOffset - nStartOffset);
				strISWord = strWord + strWordSuffix + strISWord;
			}
			else
			{
				strISWord = strWordSuffix + strISWord;
				break;
			}

			strWordSuffix.Empty();
		}
		while (GetNextPos(strBuffer, m_strNonSelectableChars, nOffset, FALSE) >= 0 &&
			   CheckIntelliMark(strBuffer,nOffset,strWordSuffix) &&
			   nOffset >= 0);
	}

	if ((strISWord = strWordSuffix + strISWord).IsEmpty())
	{
		return FALSE;
	}

	strIntelliSence = strISWord;
	return TRUE;
}

void CCustomEditCtrl::ReleaseIntelliSenseList(CObList& lstIntelliSenseData)
{
	for (POSITION pos = lstIntelliSenseData.GetHeadPosition();
		 pos != NULL;
		 delete lstIntelliSenseData.GetNext(pos));

	lstIntelliSenseData.RemoveAll();
}

void CCustomEditCtrl::OnGetCharColor (TCHAR ch, int nOffset, COLORREF& clrText, COLORREF& clrBk)
{
	if (m_bCheckColorTags)
	{
		
		TCHAR chOpen = _T ('<');
		TCHAR chClose = _T ('>');
		
		if (ch == chOpen || ch == chClose || ch == _T ('/'))
		{
			clrText = RGB (0, 0, 255);
		}
		else 
		{
			COLORREF clrDefaultBack = GetDefaultBackColor ();
			COLORREF clrDefaultTxt = GetDefaultTextColor ();
			int nBlockStart, nBlockEnd;
			if (!IsInBlock (nOffset, chOpen, chClose, nBlockStart, nBlockEnd))
			{
				clrText = clrDefaultTxt;
				clrBk = clrDefaultBack;
			}
			else if (GetCharAt (nBlockStart + 1) == _T ('%') && 
					 GetCharAt (nBlockEnd - 1) == _T ('%'))
			{

			}
			else if (clrText == clrDefaultTxt)
			{
				if (ch == _T ('='))
				{
					clrText = RGB (0, 0, 255);
				}
				else
				{
					clrText = RGB (255, 0, 0);
				}
			}
		}
	}
}

void CCustomEditCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (IsEnableBreakpoints() &&
		point.x < m_nLeftMarginWidth)
	{
		ToggleBreakpoint();
	}
	
	CBCGPEditCtrl::OnLButtonDblClk(nFlags, point);
}

BOOL CCustomEditCtrl::ToggleBreakpoint(int nCurrRow /* = -1 */)
{
	if (nCurrRow == -1)
	{
		nCurrRow = GetCurRow();
	}

	BOOL bMarkerSet = ToggleMarker (nCurrRow, g_dwBreakPointType, NULL, FALSE);

	if (bMarkerSet)
	{
		SetLineColorMarker (nCurrRow, RGB (0, 0, 0), 
			                RGB (255, 127, 127), TRUE, 0, g_dwColorBreakPointType, 2);
	}
	else
	{
		DeleteMarker (nCurrRow, g_dwColorBreakPointType);
	}

	return bMarkerSet;
}

void CCustomEditCtrl::RemoveAllBreakpoints()
{
	DeleteAllMarkers(g_dwBreakPointType | g_dwColorBreakPointType);
}

BOOL CCustomEditCtrl::ToggleCurrentLine (int nCurrRow/* = -1*/)
{
	if (nCurrRow == -1)
	{
		nCurrRow = GetCurRow();
	}

	return ToggleMarker (nCurrRow, g_dwCurrLineType, NULL, FALSE);
}

void CCustomEditCtrl::OnFailedOperation(DWORD dwOpType)
{
	UINT uiID = 0;
		
	switch (dwOpType)
	{
	case g_dwOpDelete:
	case g_dwOpPaste:
	case g_dwOpCopy:
	case g_dwOpCut:
		uiID = IDS_EDITFAILED;
		break;
	case g_dwOpPgUp:
		uiID = IDS_PGUPFAILED;
		break;
	case g_dwOpDragDrop:		
	case g_dwOpIndent:
		// usually fail for reasons that shouldn't draw any attention
		return;
	}

	if (uiID != 0)
	{
		CString strMsg;

		strMsg.LoadString(uiID);
		::AfxMessageBox(strMsg);
	}

	switch (dwOpType)
	{
	case g_dwOpDelSelText:
		return;
	}

	::MessageBeep((UINT)-1);
}
