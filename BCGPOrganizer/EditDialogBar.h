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

#if !defined(AFX_EDITDIALOGBAR_H__AD5DA710_5842_45F5_88FB_8D8F27936E97__INCLUDED_)
#define AFX_EDITDIALOGBAR_H__AD5DA710_5842_45F5_88FB_8D8F27936E97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDialogBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditDialogBar window

class CEditDialogBar: public CBCGPDialogBar
{
	DECLARE_SERIAL(CEditDialogBar)

public:
	enum XResize
	{
		e_ResizeSizeH,
		e_ResizeSizeV,
		e_ResizeSizeHV,
		e_ResizeMoveH,
		e_ResizeMoveV,
		e_ResizeMoveHV
	};

	struct XResizeInfo
	{
		UINT m_id;
		XResize m_resize;
		CRect m_rectInit;

		XResizeInfo()
			: m_id       (0)
			, m_resize   (e_ResizeSizeHV)
			, m_rectInit (0, 0, 0, 0)
		{
		}

		XResizeInfo(UINT id, XResize resize)
			: m_id       (id)
			, m_resize   (resize)
			, m_rectInit (0, 0, 0, 0)
		{
		}
	};

public:
	CEditDialogBar ();
	virtual ~CEditDialogBar ();

protected:
	virtual BOOL OnInitDialogBar();

			void AddResize(UINT nID, XResize resize);
	virtual void Resize(int cx, int cy);

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT HandleInitDialog(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	CSize	m_szWindow;
	CArray<XResizeInfo, XResizeInfo&> m_ResizeInfo;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDIALOGBAR_H__AD5DA710_5842_45F5_88FB_8D8F27936E97__INCLUDED_)
