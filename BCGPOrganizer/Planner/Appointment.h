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
// Appointment.h: interface for the CAppointment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPOINTMENT_H__7B5E460A_B963_4BB9_9705_3AF5DA729112__INCLUDED_)
#define AFX_APPOINTMENT_H__7B5E460A_B963_4BB9_9705_3AF5DA729112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPAppointment.h"
#include "BCGPAppointmentStorage.h"

#define APPOINTMENT_PROPERTY_LOCATION	BCGP_APPOINTMENT_PROPERTY_FIRST +  8
#define APPOINTMENT_PROPERTY_MEMO		BCGP_APPOINTMENT_PROPERTY_FIRST +  9
#define APPOINTMENT_PROPERTY_IMPORTANCE BCGP_APPOINTMENT_PROPERTY_FIRST + 10
#define APPOINTMENT_PROPERTY_PRIVATE    BCGP_APPOINTMENT_PROPERTY_FIRST + 11

class CAppointment : public CBCGPAppointment  
{
	DECLARE_SERIAL(CAppointment)

public:
	enum XImportance
	{
		e_ImportanceLow    = -1,
		e_ImportanceNormal =  0,
		e_ImportanceHigh   =  1
	};

public:
	CAppointment();
	CAppointment
	(
		const COleDateTime& dtStart,
		const COleDateTime& dtFinish,
		const CString& strText,
		COLORREF clrBackground = CLR_DEFAULT,
		COLORREF clrForeground = CLR_DEFAULT,
		COLORREF clrDuration   = CLR_DEFAULT
	);

	virtual ~CAppointment();

	void SetLocation (const CString& strText);
	inline const CString& GetLocation () const
	{
		return m_strLocation;
	}

	void SetMemo (const CString& strText);
	inline const CString& GetMemo () const
	{
		return m_strMemo;
	}

	void SetImportance (XImportance importance);
	inline XImportance GetImportance () const
	{
		return m_Importance;
	}

	void SetPrivate (BOOL bPrivate = TRUE);
	inline BOOL IsPrivate () const
	{
		return m_bPrivate;
	}

	virtual void GetProperties (CBCGPAppointmentPropertyList& props) const;
	virtual void SetProperties (const CBCGPAppointmentPropertyList& props);

protected:
	virtual void Serialize (CArchive& ar);

protected:
	XImportance		m_Importance;
	BOOL			m_bPrivate;
	CString			m_strLocation;
	CString			m_strMemo;
};

class CAppointmentResourceInfo : public CBCGPAppointmentBaseResourceInfo
{
	DECLARE_DYNAMIC (CAppointmentResourceInfo)

public:
	CAppointmentResourceInfo ()
	{
	}

	virtual ~CAppointmentResourceInfo ()
	{
	}

	virtual CString GetDescription () const;
	virtual COleDateTime GetWorkStart () const;
	virtual COleDateTime GetWorkEnd () const;

	void SetDescription (const CString& strDescription);
	void SetWorkInterval (const COleDateTime& dtStart, const COleDateTime& dtEnd);

	virtual void Serialize (CArchive& ar);

private:
	CString m_Description;
	COleDateTime m_WorkStart;
	COleDateTime m_WorkEnd;
};

#endif // !defined(AFX_APPOINTMENT_H__7B5E460A_B963_4BB9_9705_3AF5DA729112__INCLUDED_)
