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
// BCGPAppointmentDemo.h: interface for the CBCGPAppointmentDemo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPAPPOINTMENTDEMO_H__7B5E460A_B963_4BB9_9705_3AF5DA729112__INCLUDED_)
#define AFX_BCGPAPPOINTMENTDEMO_H__7B5E460A_B963_4BB9_9705_3AF5DA729112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPAppointment.h"
#include "BCGPAppointmentStorage.h"

#define BCGP_APPOINTMENT_PROPERTY_LOCATION	BCGP_APPOINTMENT_PROPERTY_FIRST + 8
#define BCGP_APPOINTMENT_PROPERTY_MEMO		BCGP_APPOINTMENT_PROPERTY_FIRST + 9

class CBCGPAppointmentDemo : public CBCGPAppointment  
{
	DECLARE_SERIAL(CBCGPAppointmentDemo)

public:
	CBCGPAppointmentDemo();
	CBCGPAppointmentDemo
	(
		const COleDateTime& dtStart,
		const COleDateTime& dtFinish,
		const CString& strText,
		COLORREF clrBackground = CLR_DEFAULT,
		COLORREF clrForeground = CLR_DEFAULT,
		COLORREF clrDuration   = CLR_DEFAULT
	);

	virtual ~CBCGPAppointmentDemo();

	void SetLocation (const CString& strText);
	const CString& GetLocation () const
	{
		return m_strLocation;
	}

	void SetMemo (const CString& strText);
	const CString& GetMemo () const
	{
		return m_strMemo;
	}

	virtual void GetProperties (CBCGPAppointmentPropertyList& props) const;
	virtual void SetProperties (const CBCGPAppointmentPropertyList& props);

protected:
	virtual void Serialize (CArchive& ar);

protected:
	CString m_strLocation;
	CString m_strMemo;
};

class CBCGPAppointmentDemoResourceInfo : public CBCGPAppointmentBaseResourceInfo
{
	DECLARE_DYNAMIC (CBCGPAppointmentDemoResourceInfo)

public:
	CBCGPAppointmentDemoResourceInfo ()
	{
	}

	virtual ~CBCGPAppointmentDemoResourceInfo ()
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

#endif // !defined(AFX_BCGPAPPOINTMENTDEMO_H__7B5E460A_B963_4BB9_9705_3AF5DA729112__INCLUDED_)
