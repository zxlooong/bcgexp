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
#if !defined(AFX_PLANNERCLOCKICONS_H__B8C60AAF_318B_462A_A4E4_B8697060C209__INCLUDED_)
#define AFX_PLANNERCLOCKICONS_H__B8C60AAF_318B_462A_A4E4_B8697060C209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlannerClockIcons.h : header file
//

#include "BCGPPlannerClockIcons.h"

/////////////////////////////////////////////////////////////////////////////
// CPlannerClockIcons

class CPlannerClockIcons : public CBCGPPlannerClockIcons
{
	DECLARE_DYNCREATE(CPlannerClockIcons)

public:
	virtual ~CPlannerClockIcons();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Overrides
public:
	
protected:

	CPlannerClockIcons();

protected:
	virtual BOOL Initialize ();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANNERCLOCKICONS_H__B8C60AAF_318B_462A_A4E4_B8697060C209__INCLUDED_)
