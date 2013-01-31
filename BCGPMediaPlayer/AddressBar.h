#if !defined(AFX_ADDRESSBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_)
#define AFX_ADDRESSBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddressBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddressBar

class CAddressBar : public CBCGPExplorerToolBar
{
	DECLARE_DYNCREATE(CAddressBar)

// Construction
public:
	CAddressBar();
	virtual ~CAddressBar();

	void CreateButtons ();

protected:
	virtual int GetRowHeight () const;
	virtual void OnLoadNavImages ();
	virtual void DrawSeparator (CDC* pDC, const CRect& rect, BOOL bHorz);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddressBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRESSBAR_H__3108F6A3_320E_4244_AA91_6E4035798E63__INCLUDED_)
