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
// BCGPVisualStudioGUIDemoView.h : interface of the CBCGPVisualStudioGUIDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGCBDOTNETEXAMPLEVIEW_H__FBABDE53_0288_4B70_B327_62D17730D369__INCLUDED_)
#define AFX_BCGCBDOTNETEXAMPLEVIEW_H__FBABDE53_0288_4B70_B327_62D17730D369__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPVisualStudioGUIDemoDoc;
class CBCGPVisualStudioGUIDemoView;
class CUndoButton;
class CCustomEditCtrl;

class CBCGPVisualStudioGUIDemoView : public CBCGPEditView
{
	friend class CMyFindDlg;

protected: // create from serialization only
	CBCGPVisualStudioGUIDemoView();
	DECLARE_DYNCREATE(CBCGPVisualStudioGUIDemoView)

// Attributes
public:
	CBCGPVisualStudioGUIDemoDoc* GetDocument();

protected:
	CFont				m_Font;
	CCustomEditCtrl*	m_pEdit;
	CString				m_strCaretPosFmt;

// Operations
public:
	void OnChangeVisualStyle ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPVisualStudioGUIDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

	virtual CBCGPEditCtrl* CreateEdit ();
	virtual void OnTextNotFound (LPCTSTR lpszFind);

// Implementation
public:
	virtual void AttachXMLSettings(const CString& strXMLFileName);
	virtual void GetUndoActions(CStringList& lstActions) const;
	virtual void GetRedoActions(CStringList& lstActions) const;

	void DoUndo(CUndoButton* pUndoBtn);

	virtual ~CBCGPVisualStudioGUIDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL UATToString(DWORD dwUAT, CString& strAction) const;

// Generated message map functions
protected:
	void ResetDefaultFont();
	CImageList m_imgList;

	//{{AFX_MSG(CBCGPVisualStudioGUIDemoView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditTogglebookmark();
	afx_msg void OnRemoveAllBreakpoints();
	afx_msg void OnToggleBreakpoint();
	afx_msg void OnClearAllBookmarks();
	afx_msg void OnUpdateClearAllBookmarks(CCmdUI* pCmdUI);
	afx_msg void OnEditNextbookmark();
	afx_msg void OnEditPreviousbookmark();
	afx_msg void OnEditListmembers();
	afx_msg void OnEditIncreaseIdent();
	afx_msg void OnUpdateEditIncreaseIdent(CCmdUI* pCmdUI);
	afx_msg void OnEditDecreaseIdent();
	afx_msg void OnUpdateEditDecreaseIdent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditListmembers(CCmdUI* pCmdUI);
	afx_msg void OnEditHideselection();
	afx_msg void OnEditStophidingcurrent();
	afx_msg void OnEditToggleoutlining();
	afx_msg void OnEditTogglealloutlining();
	afx_msg void OnEditCollapsetodefinitions();
	afx_msg void OnEditStopoutlining();
	afx_msg void OnUpdateEditStophidingcurrent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditHideselection(CCmdUI* pCmdUI);
	afx_msg void OnEditAutooutlining();
	afx_msg void OnUpdateEditAutooutlining(CCmdUI* pCmdUI);
	afx_msg void OnEditEnableoutlining();
	afx_msg void OnUpdateEditEnableoutlining(CCmdUI* pCmdUI);
	afx_msg void OnEditLinenumbers();
	afx_msg void OnUpdateEditLinenumbers(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditStopoutlining(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditTogglealloutlining(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditToggleoutlining(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCollapsetodefinitions(CCmdUI* pCmdUI);
	afx_msg void OnEditGotoLine();
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnUpdateCaretPos(CCmdUI* pCmdUI);
	afx_msg void OnShowHint();
	afx_msg void OnFind();
	afx_msg void OnFindNext();
	afx_msg void OnFindPrev();
	afx_msg void OnUndoAction();
	afx_msg void OnUpdateUndoAction(CCmdUI* pCmdUI);
	afx_msg void OnEditFindNextWord();
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bXMLSettings;
	
	void RestoreDefaultView(UINT uiExampleID = -1);
	BOOL RestoreDefaultData();
	virtual void GetUndoRedoActions(CStringList& lstActions, BOOL bUndo) const;
	void ResetFindCombo();
	void VerifyFindString(CBCGPToolbarComboBoxButton* pFindCombo, CString& strFindText);
};

#ifndef _DEBUG  // debug version in BCGDevStudioExampleView.cpp
inline CBCGPVisualStudioGUIDemoDoc* CBCGPVisualStudioGUIDemoView::GetDocument()
   { return (CBCGPVisualStudioGUIDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCBDOTNETEXAMPLEVIEW_H__FBABDE53_0288_4B70_B327_62D17730D369__INCLUDED_)
