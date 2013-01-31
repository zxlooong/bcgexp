#if !defined(AFX_FILTERLISTDLG_H__F734CBC0_578A_4D14_B8E1_FA2D2E45ED23__INCLUDED_)
#define AFX_FILTERLISTDLG_H__F734CBC0_578A_4D14_B8E1_FA2D2E45ED23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterListDlg.h : header file
//

#include "FilterGridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFilterListDlg dialog

class CFilterListDlg : public CDialog
{
// Construction
public:
	CFilterListDlg(CStringList& lstStrings, FILTER_PARAM& param, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CFilterListDlg)
	enum { IDD = IDD_FILTER_LIST };
	//}}AFX_DATA
	CCheckListBox	m_wndFilterList;

	CStringList&	m_lstStrings;
	FILTER_PARAM&	m_Param;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillList ();

	// Generated message map functions
	//{{AFX_MSG(CFilterListDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnCheckchangeFilterList();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERLISTDLG_H__F734CBC0_578A_4D14_B8E1_FA2D2E45ED23__INCLUDED_)
