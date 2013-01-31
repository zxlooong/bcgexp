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
// key.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKey

class CKey
{
public:
	CKey() {m_hKey = NULL;}
	~CKey() {Close();}

// Attributes
public:
	HKEY m_hKey;
	BOOL SetStringValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
	BOOL GetStringValue(CString& str, LPCTSTR lpszValueName = NULL);

// Operations
public:
	BOOL Create(HKEY hKey, LPCTSTR lpszKeyName);
	BOOL Open(HKEY hKey, LPCTSTR lpszKeyName);
	void Close();

// Overrides

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////
