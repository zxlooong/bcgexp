//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// EqualizerBar.h : header file
//

#if !defined(AFX_EQUALIZERBAR_H__8884FB7F_AEEE_459F_A461_74A2AFA4BE0D__INCLUDED_)
#define AFX_EQUALIZERBAR_H__8884FB7F_AEEE_459F_A461_74A2AFA4BE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEqualizerBar dialog

class CEqualizerBar : public CBCGPDialogBar
{
	DECLARE_SERIAL(CEqualizerBar)
		
// Construction
public:
	CEqualizerBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEqualizerBar)
	enum { IDD = IDD_EQUALIZER_BAR };
	CBCGPSliderCtrl m_wndSlider[10];
	CBCGPStatic m_wndLabel[10];
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEqualizerBar)
	virtual void DoDataExchange(CDataExchange* pDX);	
	//}}AFX_VIRTUAL

/*	inline CBCGPToolBarImages& GetBack ()
	{
		return m_Back;
	}
*/
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEqualizerBar)
	//}}AFX_MSG
	afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
//	CBCGPToolBarImages	m_Back;
	CFont	m_LabelFont;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EQUALIZERBAR_H__8884FB7F_AEEE_459F_A461_74A2AFA4BE0D__INCLUDED_)
