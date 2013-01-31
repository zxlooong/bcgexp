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
// HistoryObj.h: interface for the CHistoryObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYOBJ_H__F83C8E1D_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_HISTORYOBJ_H__F83C8E1D_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHistoryObj  
{
public:
	CHistoryObj(const CString& strTitle, const CString& strURL, const UINT uiCommand);
	CHistoryObj(const CHistoryObj& rObj);
	
	virtual ~CHistoryObj();

	LPCTSTR GetTitle () const
	{
		return m_strTitle;
	}

	LPCTSTR GetURL () const
	{
		return m_strURL;
	}

	UINT GetCommand () const
	{
		return m_uiCommand;
	}

	CString GetDomain() const;

private:
	const CString	m_strTitle;
	const CString	m_strURL;
	const UINT		m_uiCommand;
};

class CHistoryManager
{
public:
	CHistoryManager();
	virtual ~CHistoryManager();

	void Clean();

	void Load();
	void Save() const;

	BOOL Add(const CHistoryObj& obj);
	void FillTree(CTreeCtrl& wndTree) const;

protected:
	typedef CArray<CHistoryObj*, CHistoryObj*> XHistoryArray;
	typedef CMap<CString, LPCTSTR, XHistoryArray*, XHistoryArray*> XHistoryMap;

private:
	XHistoryMap m_Map;
};

#endif // !defined(AFX_HISTORYOBJ_H__F83C8E1D_F33E_11D2_A713_0090274409AC__INCLUDED_)
