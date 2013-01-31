#if !defined(AFX_ABOUTDIALOG_H__404484F9_23F7_4C9A_92B3_0E382339C0D9__INCLUDED_)
#define AFX_ABOUTDIALOG_H__404484F9_23F7_4C9A_92B3_0E382339C0D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

class CAboutDialog : public CDialog
{
public:
	CAboutDialog();

// Dialog Data
	//{{AFX_DATA(CAboutDialog)
	enum { IDD = IDD_ABOUTBOX };
	CBCGPURLLinkButton	m_bntURL;
	CBCGPURLLinkButton	m_btnMail;
	CString	m_strVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDIALOG_H__404484F9_23F7_4C9A_92B3_0E382339C0D9__INCLUDED_)
