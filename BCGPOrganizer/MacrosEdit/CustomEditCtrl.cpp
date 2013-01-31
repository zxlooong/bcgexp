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
#include "../BCGPOrganizer.h"
#include "CustomEditCtrl.h"
#include "../MainFrm.h"

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
	{_T("Drawing"), 0},
	{_T("IO"), 0},
	{ NULL }
};

static StringIndex g_aStringIndex11[] =
{
	{_T("Font"), 2},
	{_T("Image"), 2},
	{_T("Point"), 1},
	{_T("Rectangle"), 1},
	{_T("Size"), 1},
	{ NULL }
};

static StringIndex g_aStringIndex12[] =
{
	{_T("Directory"), 2},
	{_T("File"), 2},
	{_T("Path"), 2},
	{ NULL }
};

static StringIndex g_aStringIndex121[] =
{
	{_T("CreateDirectory"), 3},
	{_T("Delete"), 3},
	{_T("Exists"), 3},
	{_T("GetDirectories"), 3},
	{_T("GetDirectoryRoot"), 3},
	{_T("GetFiles"), 3},
	{_T("Move"), 3},
	{ NULL }
};

static StringIndex g_aStringIndex122[] =
{
	{_T("AppendText"), 3},
	{_T("Copy"), 3},
	{_T("Create"), 3},
	{_T("CreateText"), 3},
	{_T("Delete"), 3},
	{_T("Exists"), 3},
	{_T("GetAttributes"), 3},
	{_T("Move"), 3},
	{_T("Open"), 3},
	{_T("OpenRead"), 3},
	{_T("OpenText"), 3},
	{_T("OpenWrite"), 3},
	{_T("SetAttributes"), 3},
	{ NULL }
};

static StringIndex g_aStringIndex123[] =
{
	{_T("AltDirectorySeparatorChar"), 7},
	{_T("DirectorySeparatorChar"), 7},
	{_T("InvalidPathChars"), 7},
	{_T("PathSeparator"), 7},
	{_T("VolumeSeparatorChar"), 7},
	{_T("ChangeExtension"), 3},
	{_T("Combine"), 3},
	{_T("GetDirectoryName"), 3},
	{_T("GetExtension"), 3},
	{_T("GetFileName"), 3},
	{_T("GetFileNameWithoutExtension"), 3},
	{_T("GetFullPath"), 3},
	{_T("GetPathRoot"), 3},
	{_T("GetTempFileName"), 3},
	{_T("GetTempPath"), 3},
	{_T("HasExtension"), 3},
	{_T("IsPathRooted"), 3},
	{ NULL }
};

static StringIndex g_aStringIndex2[] =
{
	{_T("DBNull"), 7},
	{_T("ChangeType"), 3},
	{_T("GetTypeCode"), 3},
	{_T("IsDBNull"), 3},
	{_T("ToBoolean"), 3},
	{_T("ToByte"), 3},
	{_T("ToChar"), 3},
	{_T("ToDateTime"), 3},
	{_T("ToDecimal"), 3},
	{_T("ToDouble"), 3},
	{_T("ToInt16"), 3},
	{_T("ToInt32"), 3},
	{_T("ToInt64"), 3},
	{_T("ToSByte"), 3},
	{_T("ToSingle"), 3},
	{_T("ToString"), 3},
	{_T("ToUInt16"), 3},
	{_T("ToUInt32"), 3},
	{_T("ToUInt64"), 3},
	{ NULL }
};

struct IntelliStringArray
{
	LPCTSTR lpszName;
	StringIndex* ptr;
};

static IntelliStringArray g_aIntelliStringArray[] =
{
	{_T("System."), g_aStringIndex1},
	{_T("System.Drawing."), g_aStringIndex11},
	{_T("System.IO."), g_aStringIndex12},
	{_T("System.IO.Directory."), g_aStringIndex121},
	{_T("System.IO.File."), g_aStringIndex122},
	{_T("System.IO.Path."), g_aStringIndex123},
	{_T("Drawing."), g_aStringIndex11},
	{_T("IO."), g_aStringIndex12},
	{_T("IO.Directory."), g_aStringIndex121},
	{_T("IO.File."), g_aStringIndex122},
	{_T("IO.Path."), g_aStringIndex123},
	{_T("Directory."), g_aStringIndex121},
	{_T("File."), g_aStringIndex122},
	{_T("Path."), g_aStringIndex123},
	{_T("Convert."), g_aStringIndex2},
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
	ON_WM_LBUTTONUP()
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

		if (m_bGradientMarkers && globalData.m_nBitsPerPixel > 8)
		{
			CBCGPDrawManager dm (*pDC);

			CRect rectInner = rectMarker;
			int nBorder = rectMarker.Height () / 2 - 2;
			rectInner.DeflateRect (nBorder, nBorder, nBorder + 1, nBorder + 1);
			dm.FillGradient2 (rectInner, RGB (255, 169, 179), RGB (201, 50, 50), 45);

			dm.DrawGradientRing (rectMarker,
				RGB (182, 47, 41),
				RGB (255, 169, 179),
				RGB (133, 11, 13),
				45, nBorder);
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
	else
	{
		CBCGPEditCtrl::OnDrawMarker (pDC, rectMarker, pMarker);
	}
}

int CCustomEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPEditCtrl::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

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
		SetLineColorMarker (nCurrRow, RGB (255, 255, 255), 
			                RGB (127, 0, 0), TRUE, 0, g_dwColorBreakPointType);
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

void CCustomEditCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CBCGPEditCtrl::OnLButtonUp(nFlags, point);

	CString strSel = GetSelText ();

	if (CBCGPPopupMenu::GetActiveMenu () != NULL || strSel.IsEmpty ())
	{
		return;
	}

	CBCGPRibbonFloaty* pFloaty = new CBCGPRibbonFloaty;

	CList<UINT, UINT> lstCmds;

	lstCmds.AddTail (ID_EDIT_COPY);
	lstCmds.AddTail (ID_EDIT_CUT);
	lstCmds.AddTail (ID_EDIT_PASTE);
	lstCmds.AddTail (ID_EDIT_FIND);
	lstCmds.AddTail (ID_EDIT_REPLACE);

	pFloaty->SetCommands (((CMainFrame*) GetTopLevelFrame ())->GetRibbonBar (),
		lstCmds);

	ClientToScreen (&point);
	pFloaty->Show (point.x, point.y);
}

