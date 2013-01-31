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
// wordpdoc.h : interface of the CWordPadDoc class
//

class CFormatBar;
class CWordPadSrvrItem;
class CWordPadView;

class CWordPadDoc : public CRichEditDoc
{
protected: // create from serialization only
	CWordPadDoc();
	DECLARE_DYNCREATE(CWordPadDoc)

// Attributes
public:
	int m_nDocType;
	int m_nNewDocType;
	void SetDocType(int nDocType, BOOL bNoOptionChange = FALSE);
	CWordPadView* GetView();
	CLSID GetClassID();
	LPCTSTR GetSection();

// Operations
public:
	void SaveState(int nType);
	void RestoreState(int nType);
	virtual CFile* GetFile(LPCTSTR pszPathName, UINT nOpenFlags,
		CFileException* pException);
	virtual BOOL DoSave(LPCTSTR pszPathName, BOOL bReplace = TRUE);
	int MapType(int nType);
	void ForceDelayed(CFrameWnd* pFrameWnd);

// Overrides
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual void Serialize(CArchive& ar);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordPadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void OnCloseDocument();
	virtual void ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void PreCloseFrame(CFrameWnd* pFrameArg);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CWordPadDoc)
	afx_msg void OnViewOptions();
	afx_msg void OnUpdateOleVerbPopup(CCmdUI* pCmdUI);
	afx_msg void OnFileSendMail();
	afx_msg void OnUpdateIfEmbedded(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateObjectVerbMenu(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////