#if !defined(AFX_CEditGanttItemDlg_H__E0CCA224_220C_48A2_A647_B770631F6A8C__INCLUDED_)
#define AFX_CEditGanttItemDlg_H__E0CCA224_220C_48A2_A647_B770631F6A8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

// CEditGanttItemDlg.h : header file
//

class CBCGPGanttItem;

/////////////////////////////////////////////////////////////////////////////
// CEditGanttItemDlg dialog

class CEditGanttItemDlg : public CBCGPDialog
{
// Construction
public:
	CEditGanttItemDlg (CBCGPGanttItem& item, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditGanttItemDlg)
	enum { IDD = IDD_EDIT_GANTTITEM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditGanttItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBCGPColorButton	m_wndColorBar;
	CBCGPColorButton	m_wndColorComplete;
	CBCGPDateTimeCtrl   m_wndStartDate;
	CBCGPDateTimeCtrl   m_wndFinishDate;

	CBCGPGanttItem*     m_pGanttItem;
	BOOL                m_bMilestoneItem;

	void    ReadItemData ();
	BOOL    WriteItemData ();

	// Generated message map functions
	//{{AFX_MSG(CEditGanttItemDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEditGanttItemDlg_H__E0CCA224_220C_48A2_A647_B770631F6A8C__INCLUDED_)
