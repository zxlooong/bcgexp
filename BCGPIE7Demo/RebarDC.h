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
// RebarDC.h: interface for the CRebarDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REBARDC_H__C49BD6DC_2E38_41E6_A99D_A2C77A021816__INCLUDED_)
#define AFX_REBARDC_H__C49BD6DC_2E38_41E6_A99D_A2C77A021816__INCLUDED_

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

class CRebarDC: public CMemDC
{
public:
	CRebarDC();
	virtual ~CRebarDC();

	virtual void SetSize (const CSize& size);

	static CRebarDC& GetInstance ()
	{
		return m_RebarDC;
	}

private:
	static CRebarDC	m_RebarDC;
};

#endif // !defined(AFX_REBARDC_H__C49BD6DC_2E38_41E6_A99D_A2C77A021816__INCLUDED_)
