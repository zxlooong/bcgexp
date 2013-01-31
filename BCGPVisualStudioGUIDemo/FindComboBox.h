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
#if !defined(AFX_FINDCOMBOBOX_H__481CA594_2913_45FD_9878_9160E8829D5D__INCLUDED_)
#define AFX_FINDCOMBOBOX_H__481CA594_2913_45FD_9878_9160E8829D5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindComboBox.h : header file
//

class CFindComboButton : public CBCGPToolbarComboBoxButton
{
	DECLARE_SERIAL(CFindComboButton)

// Construction
public:
	CFindComboButton () :
		CBCGPToolbarComboBoxButton (ID_EDIT_FIND_COMBO, 
				CImageHash::GetImageOfCommand (ID_EDIT_FIND, FALSE),
				CBS_DROPDOWN)
	{
	}

// Attributes:
public:
	static BOOL HasFocus ()
	{
		return m_bHasFocus;
	}

protected:
	static BOOL m_bHasFocus;

// Overrides
protected:
	virtual BOOL NotifyCommand (int iNotifyCode);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDCOMBOBOX_H__481CA594_2913_45FD_9878_9160E8829D5D__INCLUDED_)
