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

class CSharedBitmap
{
    class CInstance;

    CInstance* m_pInstance;
public:
    CSharedBitmap();
    CSharedBitmap(const CSharedBitmap& rhs);
    CSharedBitmap& operator = (const CSharedBitmap& rhs);

    void LoadBitmap(UINT uiResourceID);
    CBCGPToolBarImages& GetBitmap() const;
    bool IsValid() const;
    CSize GetSize() const;
    void Draw(HDC dc, int x, int y) const;
    void DrawPart(HDC dc, int x, int y, int xSrc, int ySrc, int widthSrc, int heightSrc) const;
    COLORREF GetPixel(int x, int y) const;

    virtual ~CSharedBitmap();
};
