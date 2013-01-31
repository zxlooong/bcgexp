#if !defined(AFX_PROPBAR_H__DCFA96A5_D72F_4D1E_A904_D379C3191236__INCLUDED_)
#define AFX_PROPBAR_H__DCFA96A5_D72F_4D1E_A904_D379C3191236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropBar window

class CPropBar : public CBCGPDockingControlBar
{
// Construction
public:
	CPropBar();

// Attributes
protected:
	CBCGPPropList m_wndPropList;

protected:
	enum
	{
		idFieldChooser,
		idGroupByBox,
		idColorTheme,
	};

// Operations
public:
	void SetContext (int nGridType);
	void UpdatePropList ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPBAR_H__DCFA96A5_D72F_4D1E_A904_D379C3191236__INCLUDED_)
