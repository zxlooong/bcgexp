#if !defined(AFX_RESOURCEDLG_H__B02B7103_292C_4098_AB54_CC777395EAF1__INCLUDED_)
#define AFX_RESOURCEDLG_H__B02B7103_292C_4098_AB54_CC777395EAF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResourceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResourceDlg dialog

class CBCGPAppointmentDemoResourceInfo;

class CResourceDlg : public CBCGPDialog
{
// Construction
public:
	CResourceDlg(CBCGPAppointmentDemoResourceInfo& rInfo, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResourceDlg)
	enum { IDD = IDD_RESOURCE_EDIT_DLG };
	CBCGPButton	m_btnInterval;
	CBCGPStatic	m_stDateTimeStart;
	CBCGPDateTimeCtrl	m_TimeStart;
	CBCGPStatic	m_stDateTimeEnd;
	CBCGPDateTimeCtrl	m_TimeEnd;
	CString	m_strDescription;
	BOOL	m_bVisible;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResourceDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnIntervalCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBCGPAppointmentDemoResourceInfo& m_Info;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESOURCEDLG_H__B02B7103_292C_4098_AB54_CC777395EAF1__INCLUDED_)
