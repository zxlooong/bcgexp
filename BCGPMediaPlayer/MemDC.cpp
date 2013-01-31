// MemDC.cpp: implementation of the CRebarDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemDC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

class XThemeManager: public CBCGPWinXPThemeManager
{
	friend class CRebarDC;
};

CMemDC::CMemDC()
	: m_pOldBitmap (NULL)
	, m_Size       (0, 0)
{

}

CMemDC::~CMemDC()
{

}

void CMemDC::CreateDC ()
{
	if (m_DC.GetSafeHdc () != NULL)
	{
		return;
	}

	HDC hDC = ::GetDC (NULL);

	HDC hNewDC = ::CreateCompatibleDC (hDC);
	if (hNewDC != NULL)
	{
		m_DC.Attach (hNewDC);
	}

	::ReleaseDC (NULL, hDC);
}

void CMemDC::SetSize (const CSize& size)
{
	if (m_DC.GetSafeHdc () == NULL)
	{
		CreateDC ();
	}

	if (m_Bitmap.GetSafeHandle () != NULL)
	{
		if (m_Size.cx != size.cx || m_Size.cy != size.cy)
		{
			if (m_pOldBitmap != NULL)
			{
				m_DC.SelectObject (m_pOldBitmap);
			}

			m_Bitmap.DeleteObject ();
		}
	}

	m_Size = size;

	if (m_Bitmap.GetSafeHandle () == NULL)
	{
		BITMAPINFO bi = {0};

		// Fill in the BITMAPINFOHEADER
		bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth       = size.cx;
		bi.bmiHeader.biHeight      = size.cy;
		bi.bmiHeader.biSizeImage   = 0;
		bi.bmiHeader.biPlanes      = 1;
		bi.bmiHeader.biBitCount    = 32;
		bi.bmiHeader.biCompression = BI_RGB;

		LPVOID pBits = NULL;
		HBITMAP hbmp = ::CreateDIBSection (NULL, &bi, DIB_RGB_COLORS, &pBits, NULL, 0);

		if (hbmp != NULL)
		{
			m_Bitmap.Attach (hbmp);
			m_pOldBitmap = (CBitmap*) m_DC.SelectObject (&m_Bitmap);
		}
	}
}
