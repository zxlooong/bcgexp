// MemDC.h: interface for the CRebarDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMDC_H__C49BD6DC_2E38_41E6_A99D_A2C77A021816__INCLUDED_)
#define AFX_MEMDC_H__C49BD6DC_2E38_41E6_A99D_A2C77A021816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemDC
{
public:
	CMemDC();
	virtual ~CMemDC();

	void CreateDC ();
	virtual void SetSize (const CSize& size);

	const CSize& GetSize () const
	{
		return m_Size;
	}

	CDC& GetDC ()
	{
		return m_DC;
	}

protected:
	CDC			m_DC;
	CBitmap		m_Bitmap;
	CBitmap*	m_pOldBitmap;
	
	CSize		m_Size;
};

#endif // !defined(AFX_MEMDC_H__C49BD6DC_2E38_41E6_A99D_A2C77A021816__INCLUDED_)
