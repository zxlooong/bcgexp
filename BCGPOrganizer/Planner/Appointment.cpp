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
// Appointment.cpp: implementation of the CAppointment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Appointment.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CAppointment, CBCGPAppointment, VERSIONABLE_SCHEMA | 1)

CAppointment::CAppointment()
{
}

CAppointment::CAppointment
(
	const COleDateTime& dtStart,
	const COleDateTime& dtFinish,
	const CString& strText,
	COLORREF clrBackground /*= CLR_DEFAULT*/,
	COLORREF clrForeground /*= CLR_DEFAULT*/,
	COLORREF clrDuration /*= CLR_DEFAULT*/
)
	: CBCGPAppointment (dtStart, dtFinish, strText, clrBackground, clrForeground, clrDuration)
	, m_Importance     (e_ImportanceNormal)
	, m_bPrivate       (FALSE)
{
}

CAppointment::~CAppointment()
{
}

void CAppointment::SetLocation (const CString& strText)
{
	if (m_strLocation != strText)
	{
		m_strLocation = strText;
	}
}

void CAppointment::SetMemo (const CString& strText)
{
	if (m_strMemo != strText)
	{
		m_strMemo = strText;
	}
}

void CAppointment::SetImportance (XImportance importance)
{
	//if (m_Importance != importance)
	{
		if (HasImage (6))
		{
			RemoveImage (6);
		}
		else if (HasImage (7))
		{
			RemoveImage (7);
		}

		m_Importance = importance;

		if (m_Importance == e_ImportanceLow)
		{
			AddImage (7, FALSE);
		}
		else if (m_Importance == e_ImportanceHigh)
		{
			AddImage (6, FALSE);
		}
	}
}

void CAppointment::SetPrivate (BOOL bPrivate)
{
	//if (m_bPrivate != bPrivate)
	{
		if (HasImage (2))
		{
			RemoveImage (2);
		}

		m_bPrivate = bPrivate;

		if (m_bPrivate)
		{
			int nImportanceImage = -1;
			if (HasImage (6))
			{
				nImportanceImage = 6;
				RemoveImage (6);
			}
			else if (HasImage (7))
			{
				nImportanceImage = 7;
				RemoveImage (7);
			}

			AddImage (2, FALSE);

			if (nImportanceImage != -1)
			{
				AddImage (nImportanceImage, FALSE);
			}
		}
	}
}

void CAppointment::Serialize (CArchive& ar)
{
	CBCGPAppointment::Serialize (ar);

    if (ar.IsStoring ())
	{
		ar << m_strLocation;
		ar << m_strMemo;
		ar << (long)m_Importance;
		ar << m_bPrivate;
	}
    else
	{
		ar >> m_strLocation;
		ar >> m_strMemo;

		long importance = 0;
		ar >> importance;
		SetImportance ((XImportance)importance);

		BOOL bPrivate = FALSE;
		ar >> bPrivate;
		SetPrivate (bPrivate);
	}
}

void CAppointment::GetProperties (CBCGPAppointmentPropertyList& props) const
{
	CBCGPAppointment::GetProperties (props);

	props.Add (APPOINTMENT_PROPERTY_LOCATION, new CBCGPAppointmentProperty (m_strLocation));
	props.Add (APPOINTMENT_PROPERTY_MEMO, new CBCGPAppointmentProperty (m_strMemo));
	props.Add (APPOINTMENT_PROPERTY_IMPORTANCE, new CBCGPAppointmentProperty ((long)m_Importance));
	props.Add (APPOINTMENT_PROPERTY_PRIVATE, new CBCGPAppointmentProperty (m_bPrivate));
}

void CAppointment::SetProperties (const CBCGPAppointmentPropertyList& props)
{
	CBCGPAppointment::SetProperties (props);

	if (props.GetCount () > 0)
	{
		CBCGPAppointmentProperty* prop = NULL;

		if (props.PropertyExists (APPOINTMENT_PROPERTY_LOCATION))
		{
			prop = (CBCGPAppointmentProperty*)props.Get (APPOINTMENT_PROPERTY_LOCATION);
			m_strLocation = *prop;
		}

		if (props.PropertyExists (APPOINTMENT_PROPERTY_MEMO))
		{
			prop = (CBCGPAppointmentProperty*)props.Get (APPOINTMENT_PROPERTY_MEMO);
			m_strMemo = *prop;
		}

		if (props.PropertyExists (APPOINTMENT_PROPERTY_IMPORTANCE))
		{
			prop = (CBCGPAppointmentProperty*)props.Get (APPOINTMENT_PROPERTY_IMPORTANCE);
			SetImportance ((XImportance)prop->GetLong ());
		}

		if (props.PropertyExists (APPOINTMENT_PROPERTY_PRIVATE))
		{
			prop = (CBCGPAppointmentProperty*)props.Get (APPOINTMENT_PROPERTY_PRIVATE);
			SetPrivate ((BOOL)*prop);
		}

		if (m_RecurrenceClone)
		{
			m_RecurrenceEcp = TRUE;
		}
	}
}



IMPLEMENT_DYNAMIC(CAppointmentResourceInfo, CBCGPAppointmentBaseResourceInfo)

CString CAppointmentResourceInfo::GetDescription () const
{
	return m_Description;
}

COleDateTime CAppointmentResourceInfo::GetWorkStart () const
{
	return m_WorkStart;
}

COleDateTime CAppointmentResourceInfo::GetWorkEnd () const
{
	return m_WorkEnd;
}

void CAppointmentResourceInfo::SetDescription (const CString& strDescription)
{
	m_Description = strDescription;
}

void CAppointmentResourceInfo::SetWorkInterval (const COleDateTime& dtStart, const COleDateTime& dtEnd)
{
	if (dtStart == dtEnd &&
		!(dtStart == COleDateTime () && dtEnd == COleDateTime ()))
	{
		return;
	}

	m_WorkStart = dtStart;
	m_WorkEnd = dtEnd;
}

void CAppointmentResourceInfo::Serialize (CArchive& ar)
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
