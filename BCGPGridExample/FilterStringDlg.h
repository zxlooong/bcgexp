#if !defined(AFX_FILTERSTRINGDLG_H__79D3D41F_1CF8_4D8A_A785_2296CA636D02__INCLUDED_)
#define AFX_FILTERSTRINGDLG_H__79D3D41F_1CF8_4D8A_A785_2296CA636D02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterStringDlg.h : header file
//

#include "FilterGridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFilterStringDlg dialog

class CFilterStringDlg : public CDialog
{
// Construction
public:
	CFilterStringDlg(FILTER_PARAM& param, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilterStringDlg)
	enum { IDD = IDD_FILTER_STRING };
	CString	m_strFilter;
	//}}AFX_DATA

	FILTER_PARAM& m_param;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterStringDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilterStringDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERSTRINGDLG_H__79D3D41F_1CF8_4D8A_A785_2296CA636D02__INCLUDED_)
