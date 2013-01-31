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
// HistoryObj.cpp: implementation of the CHistoryObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "HistoryObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHistoryObj::CHistoryObj(const CString& strTitle, const CString& strURL,
						const UINT uiCommand)
	: m_strTitle  (strTitle)
	, m_strURL    (strURL)
	, m_uiCommand (uiCommand)
{
}

CHistoryObj::CHistoryObj(const CHistoryObj& rObj)
	: m_strTitle  (rObj.m_strTitle)
	, m_strURL    (rObj.m_strURL)
	, m_uiCommand (rObj.m_uiCommand)
{
}

CHistoryObj::~CHistoryObj()
{
}

CString CHistoryObj::GetDomain() const
{
	CString str;

	int pos1 = m_strURL.Find(_T("///"));
	if (pos1 != -1)
	{
		pos1 += 3;
	}
	else
	{
		pos1 = m_strURL.Find(_T("//"));
		if (pos1 != -1)
		{
			pos1 += 2;
		}
	}

	if (pos1 != -1)
	{
		int pos2 = m_strURL.Find(_T("/"), pos1);
		if (pos2 == -1)
		{
			pos2 = m_strURL.GetLength () - 1;
		}

		str = m_strURL.Left (pos2);
		str = str.Right (str.GetLength () - pos1);
		str.MakeLower ();
	}

	return str;
}


CHistoryManager::CHistoryManager()
{

}

CHistoryManager::~CHistoryManager()
{
	Clean();
}

void CHistoryManager::Clean()
{
	CString key;
	XHistoryArray* ar = NULL;
	POSITION pos = m_Map.GetStartPosition ();
	while (pos != NULL)
	{
		m_Map.GetNextAssoc (pos, key, ar);
		if (ar != NULL)
		{
			for (int i = 0; i < ar->GetSize(); i++)
			{
				CHistoryObj* pObj = ar->GetAt(i);
				if (pObj != NULL)
				{
					delete pObj;
				}
			}

			ar->RemoveAll ();
			delete ar;
		}
	}

	m_Map.RemoveAll ();
}

void CHistoryManager::Load()
{
	Clean();
}

void CHistoryManager::Save() const
{

}

BOOL CHistoryManager::Add(const CHistoryObj& rObj)
{
	CString str = rObj.GetDomain ();
	if (str.IsEmpty ())
	{
		return FALSE;
	}

	XHistoryArray* ar = NULL;

	if (!m_Map.Lookup (str, ar))
	{
		ar = new XHistoryArray;
		m_Map[str] = ar;
	}

	ASSERT(ar != NULL);

	BOOL bFound = FALSE;
	for (int i = 0; i < ar->GetSize (); i++)
	{
		CHistoryObj* pObj = ar->GetAt (i);
		if (pObj != NULL && _tcsicmp (pObj->GetTitle (), rObj.GetTitle ()) == 0)
		{
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		ar->Add (new CHistoryObj (rObj));
	}

	return !bFound;
}

void CHistoryManager::FillTree(CTreeCtrl& wndTree) const
{
	wndTree.DeleteAllItems ();

	CString key;
	XHistoryArray* ar = NULL;
	POSITION pos = m_Map.GetStartPosition ();
	while (pos != NULL)
	{
		m_Map.GetNextAssoc (pos, key, ar);

		HTREEITEM hParentItem = wndTree.InsertItem (key, 3, 3);
		if (ar != NULL)
		{
			for (int i = 0; i < ar->GetSize(); i++)
			{
				CHistoryObj* pObj = ar->GetAt(i);
				if (pObj != NULL)
				{
					HTREEITEM hItem = wndTree.InsertItem (pObj->GetTitle (), 1, 1, hParentItem);
					wndTree.SetItemData (hItem, (DWORD_PTR) pObj);
				}
			}
		}
	}
}
