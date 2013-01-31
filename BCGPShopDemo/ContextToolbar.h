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

#pragma once

// The context toolbar occupies a whole row like CBCGPMenuBar.

class CContextToolbar : public CBCGPToolBar
{
    DECLARE_SERIAL(CContextToolbar)

public:
    CContextToolbar ();
    ~CContextToolbar ();

    virtual int GetAvailableExpandSize () const;

    void ShowButtons (UINT btnFirstID, UINT btnLastID, BOOL bVisible, BOOL bAutoAdjust = TRUE);
};
