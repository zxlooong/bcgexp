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
#if !defined(AFX_CUSTOMEDITCTRL_H__086075A9_8FCA_49AF_A2CD_1F3EB13AFF50__INCLUDED_)
#define AFX_CUSTOMEDITCTRL_H__086075A9_8FCA_49AF_A2CD_1F3EB13AFF50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomEditCtrl window

static const DWORD g_dwBreakPointType = g_dwBCGPEdit_FirstUserDefinedMarker;
static const DWORD g_dwColorBreakPointType = g_dwBCGPEdit_FirstUserDefinedMarker << 1;
static const DWORD g_dwColorHeaderType = g_dwColorBreakPointType << 1;

class CCustomEditCtrl : public CBCGPEditCtrl
{
// Construction
public:
	CCustomEditCtrl();

// Attributes
public:
	BOOL	m_bCheckColorTags;	// TRUE if check for tags (<....>) in "OnGetCharColor"

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomEditCtrl)
	//}}AFX_VIRTUAL
	
// Implementation
public:
	BOOL ToggleBreakpoint(int nCurrRow = -1);
	void RemoveAllBreakpoints();
	BOOL IsEnableBreakpoints() const {  return m_bEnableBreakpoints; }
	BOOL EnableBreakpoints(BOOL bFl);

	virtual BOOL FindText(LPCTSTR lpszFind, BOOL bNext = TRUE, BOOL bCase = TRUE, BOOL bWholeWord = FALSE);

	// Marker Support
	virtual void OnDrawMarker(CDC* pDC, CRect rectMarker, const CBCGPEditMarker* pMarker);

	// Tooltip Support
	virtual BOOL OnGetTipText (CString& strTipString);

	virtual BOOL CanUpdateMarker (CBCGPEditMarker* pMarker) const
	{
		if (pMarker->m_dwMarkerType & g_dwColorHeaderType)
		{
			return FALSE;
		}

		return TRUE;
	}

	virtual BOOL CanRemoveMarker (CBCGPEditMarker* pMarker) const  
	{
		if (pMarker->m_dwMarkerType & g_dwColorHeaderType)
		{
			return FALSE;
		}

		return TRUE;
	}

// Destruction
	virtual ~CCustomEditCtrl();

	// IntelliSense Support
	virtual BOOL FillIntelliSenseList(CObList& lstIntelliSenseData,	LPCTSTR lpszIntelliSense = NULL) const;
	void ReleaseIntelliSenseList(CObList& lstIntelliSenseData);

protected:
	// IntelliSense Support
	virtual BOOL OnBeforeInvokeIntelliSense (const CString& strBuffer, int& nCurrOffset, CString& strIntelliSence) const;
	virtual BOOL IsIntelliSenceWord(const CString& strWord) const;
	virtual BOOL IntelliSenseCharUpdate(const CString& strBuffer, int nCurrOffset, TCHAR nChar, CString& strIntelliSense);

	// Generated message map functions
protected:
	static CStringList m_lstFind;
	
	virtual void OnFailedOperation (DWORD dwOpType);
	virtual BOOL CheckIntelliMark(const CString& strBuffer, int& nOffset, CString& strWordSuffix) const;
	virtual void OnGetCharColor (TCHAR ch, int nOffset, COLORREF& clrText, COLORREF& clrBk);

	//{{AFX_MSG(CCustomEditCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL	m_bEnableBreakpoints;
	CMapStringToPtr m_mIntelliString;
	CMapStringToString m_mTipString;

	void PrepareIntelliSense();
	inline static int GetNextPos(const CString& strBuffer, const CString& strSkipChars, int& nPos, BOOL bForward);
	BOOL FillIntelliSenceWord(const CString& strBuffer, int nOffset, CString& strIntelliSence) const;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMEDITCTRL_H__086075A9_8FCA_49AF_A2CD_1F3EB13AFF50__INCLUDED_)
