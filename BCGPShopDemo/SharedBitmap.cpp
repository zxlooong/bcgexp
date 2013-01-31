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

#include "stdafx.h"
#include "SharedBitmap.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CSharedBitmap

class CSharedBitmap::CInstance
{
public:
    CBCGPToolBarImages m_Bitmap;
    int m_nRefCount;
    CInstance () : m_nRefCount(1) 
    {}
};

CSharedBitmap::CSharedBitmap()
    : m_pInstance(new CSharedBitmap::CInstance)
{
}

CSharedBitmap::CSharedBitmap(const CSharedBitmap &rhs)
    : m_pInstance(rhs.m_pInstance)
{
    ++m_pInstance->m_nRefCount;
}

CSharedBitmap& CSharedBitmap::operator = (const CSharedBitmap &rhs)
{
    CSharedBitmap bmp (rhs);
    CInstance* t = m_pInstance;
    m_pInstance = bmp.m_pInstance;
    bmp.m_pInstance = t;
    return *this;
}

CSharedBitmap::~CSharedBitmap ()
{
    if (m_pInstance && --m_pInstance->m_nRefCount < 1)
    {
        delete m_pInstance;
    }
}

void CSharedBitmap::LoadBitmap (UINT uiResourceID)
{
    m_pInstance->m_Bitmap.Load (uiResourceID);
	m_pInstance->m_Bitmap.SetSingleImage ();
}

CBCGPToolBarImages& CSharedBitmap::GetBitmap() const
{
    return m_pInstance->m_Bitmap;
}

bool CSharedBitmap::IsValid() const
{
    return !!m_pInstance->m_Bitmap.IsValid ();
}

CSize CSharedBitmap::GetSize () const
{
	return m_pInstance->m_Bitmap.GetImageSize ();
}


void CSharedBitmap::Draw (HDC dc, int x, int y) const
{
    CSize sz = GetSize ();
    DrawPart (dc, x, y, 0, 0, sz.cx, sz.cy);
}

void CSharedBitmap::DrawPart (HDC dc, int x, int y, int xSrc, int ySrc, int widthSrc, int heightSrc) const
{
    if (!m_pInstance->m_Bitmap.IsValid ())
    {
        return;
    }

    CDC* pDC = CDC::FromHandle (dc);

	m_pInstance->m_Bitmap.DrawEx (pDC, CRect (x, y, x + widthSrc, y + heightSrc), 0,
		CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertTop,
		CRect (xSrc, ySrc, xSrc + widthSrc, ySrc + heightSrc));
}

COLORREF CSharedBitmap::GetPixel(int x, int y) const
{
    CSize sz = GetSize ();
    if (x < 0 || y < 0 || x >= sz.cx || y >= sz.cy)
    {
        return 0;
    }

    CDC dc;
    dc.Attach (::GetDC (NULL));
    CDC dcMem;
    dcMem.CreateCompatibleDC (&dc);
    ::ReleaseDC (NULL, dc.Detach ());

    HBITMAP bmpOld = (HBITMAP)::SelectObject (dcMem.GetSafeHdc (), m_pInstance->m_Bitmap.GetImageWell ());
    COLORREF clr = dcMem.GetPixel (x, y);
    ::SelectObject (dcMem.GetSafeHdc (), bmpOld);

    return clr;
}
