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
// formatta.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormatTabDlg dialog

class CFormatTabDlg : public CCSDialog
{
// Construction
public:
	CFormatTabDlg(WPD_PARAFORMAT& pf, CWnd* pParent = NULL);    // standard constructor
	~CFormatTabDlg();
	WPD_PARAFORMAT m_pf;
	LONG* m_tabarray;
	int m_nCount;

// Dialog Data
	//{{AFX_DATA(CFormatTabDlg)
	enum { IDD = IDD_FORMAT_TAB };
	CButton m_buttonClearAll;
	CButton m_buttonSet;
	CButton m_buttonClear;
	CComboBox   m_comboBox;
	//}}AFX_DATA

// Implementation
protected:
	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
	void UpdateButton(CButton& button, BOOL b);
	void UpdateButtons();
	BOOL Set();
	BOOL AddTabToArray(LONG lTab);
	BOOL RemoveTabFromArray(LONG lTab);
	void RemoveTabFromArrayByIndex(int nIndex);
	void UpdateListBox();
	void SetEditFocus();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

	// Generated message map functions
	//{{AFX_MSG(CFormatTabDlg)
	afx_msg void OnClickedClear();
	afx_msg void OnClickedClearAll();
	afx_msg void OnClickedSet();
	afx_msg void OnEditChange();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
