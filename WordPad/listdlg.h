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

class CListDlg : public CDialog
{
public:
	//{{AFX_DATA(CListDlg)
	enum { IDD = IDD_LISTDIALOG };
	//}}AFX_DATA
	CListDlg::CListDlg(UINT idStrDlgTitle, UINT idStrListTitle,
		const CStringList& listItems, int nDefSel=0);
	CString m_strDlgTitle,m_strListTitle;
	const CStringList& m_listItems;
	int m_nSelection;

protected:
	BOOL OnInitDialog();
	//{{AFX_MSG(CListDlg)
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
