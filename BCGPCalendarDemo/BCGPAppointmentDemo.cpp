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
// BCGPAppointmentDemo.cpp: implementation of the CBCGPAppointmentDemo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bcgpcalendardemo.h"
#include "BCGPAppointmentDemo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBCGPAppointmentDemo, CBCGPAppointment, VERSIONABLE_SCHEMA | 1)

CBCGPAppointmentDemo::CBCGPAppointmentDemo()
{
}

CBCGPAppointmentDemo::CBCGPAppointmentDemo
(
	const COleDateTime& dtStart,
	const COleDateTime& dtFinish,
	const CString& strText,
	COLORREF clrBackground /*= CLR_DEFAULT*/,
	COLORREF clrForeground /*= CLR_DEFAULT*/,
	COLORREF clrDuration /*= CLR_DEFAULT*/
)
	: CBCGPAppointment (dtStart, dtFinish, strText, clrBackground, clrForeground, clrDuration)
{
}

CBCGPAppointmentDemo::~CBCGPAppointmentDemo()
{
}

void CBCGPAppointmentDemo::SetLocation (const CString& strText)
{
	if (m_strLocation != strText)
	{
		m_strLocation = strText;
	}
}

void CBCGPAppointmentDemo::SetMemo (const CString& strText)
{
	if (m_strMemo != strText)
	{
		m_strMemo = strText;
	}
}

void CBCGPAppointmentDemo::Serialize (CArchive& ar)
{
	CBCGPAppointment::Serialize (ar);

    if (ar.IsStoring ())
	{
		ar << m_strLocation;
		ar << m_strMemo;
	}
    else
	{
		ar >> m_strLocation;
		ar >> m_strMemo;
	}
}

void CBCGPAppointmentDemo::GetProperties (CBCGPAppointmentPropertyList& props) const
{
	CBCGPAppointment::GetProperties (props);

	props.Add (BCGP_APPOINTMENT_PROPERTY_LOCATION, new CBCGPAppointmentProperty (m_strLocation));
	props.Add (BCGP_APPOINTMENT_PROPERTY_MEMO, new CBCGPAppointmentProperty (m_strMemo));
}

void CBCGPAppointmentDemo::SetProperties (const CBCGPAppointmentPropertyList& props)
{
	CBCGPAppointment::SetProperties (props);

	if (props.GetCount () > 0)
	{
		CBCGPAppointmentProperty* prop = NULL;

		if (props.PropertyExists (BCGP_APPOINTMENT_PROPERTY_LOCATION))
		{
			prop = (CBCGPAppointmentProperty*)props.Get (BCGP_APPOINTMENT_PROPERTY_LOCATION);
			m_strLocation = *prop;
		}

		if (props.PropertyExists (BCGP_APPOINTMENT_PROPERTY_MEMO))
		{
			prop = (CBCGPAppointmentProperty*)props.Get (BCGP_APPOINTMENT_PROPERTY_MEMO);
			m_strMemo = *prop;
		}

		if (m_RecurrenceClone)
		{
			m_RecurrenceEcp = TRUE;
		}
	}
}


IMPLEMENT_DYNAMIC(CBCGPAppointmentDemoResourceInfo, CBCGPAppointmentBaseResourceInfo)

CString CBCGPAppointmentDemoResourceInfo::GetDescription () const
{
	return m_Description;
}

COleDateTime CBCGPAppointmentDemoResourceInfo::GetWorkStart () const
{
	return m_WorkStart;
}

COleDateTime CBCGPAppointmentDemoResourceInfo::GetWorkEnd () const
{
	return m_WorkEnd;
}

void CBCGPAppointmentDemoResourceInfo::SetDescription (const CString& strDescription)
{
	m_Description = strDescription;
}

void CBCGPAppointmentDemoResourceInfo::SetWorkInterval (const COleDateTime& dtStart, const COleDateTime& dtEnd)
{
	if (dtStart == dtEnd &&
		!(dtStart == COleDateTime () && dtEnd == COleDateTime ()))
	{
		return;
	}

	m_WorkStart = dtStart;
	m_WorkEnd = dtEnd;
}

void CBCGPAppointmentDemoResourceInfo::Serialize (CArchive& ar)
{
	if (ar.IsStoring ())
	{
		ar << m_Description;
		ar << m_WorkStart;
		ar << m_WorkEnd;
	}
	else
	{
		ar >> m_Description;
		ar >> m_WorkStart;
		ar >> m_WorkEnd;
	}
}
