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
// FavoritesManager.h: interface for the CFavoritesManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FAVORITESMANAGER_H__E15D7C87_B803_11D4_95C8_00A0C9289F1B__INCLUDED_)
#define AFX_FAVORITESMANAGER_H__E15D7C87_B803_11D4_95C8_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ID_FAVORITE_FIRST	0xe00
#define ID_FAVORITE_LAST	0xfff

class CFavorit :  public CObject
{
	friend class CFavoritesManager;

// Construction/Destruction
public:
	CFavorit (LPCTSTR lpszName, int iIcon, LPCTSTR lpszURL, UINT uiCommand = 0);
	virtual ~CFavorit();

protected:
	CFavorit();

// Operations:
public:
	const CFavorit* FindByID (UINT uiCommandID) const;

protected:
	void CleanUp ();
	BOOL Build (CString strPath);
	BOOL CreateMenu (CMenu& menu);
	void FillTree (CTreeCtrl& wndTree, HTREEITEM htreeItemParent);

// Attributes:
public:
	const CString& GetName () const
	{
		return m_strName;
	}

	const CString& GetURL () const
	{
		return m_strURL;
	}

	int GetIcon () const
	{
		return m_iIcon;
	}

	UINT GetCommand () const
	{
		return m_uiCommand;
	}

	const CObList& GetSubItems () const
	{
		return m_lstSubItems;
	}

private:
	CString	m_strName;
	CString	m_strURL;
	UINT	m_uiCommand;
	int		m_iIcon;

	CObList	m_lstSubItems;	// List of CFavorit objects

	static CMap<CString, LPCTSTR, int, int>	m_URLIcons;
	static CMap<UINT, UINT, int, int>		m_IDIcons;
	static UINT								m_uiNextCommand;
	static int								m_iFolderIcon;
	static int								m_iInternetShortcutIcon;
};


class CFavoritesManager : public CObject
{
// Construction/Destruction
public:
	CFavoritesManager();
	virtual ~CFavoritesManager();

// Operations:
public:
	BOOL Load ();
	BOOL CreateMenu (CMenu& menu);
	void FillTree (CTreeCtrl& wndTree);

// Attributes:
public:
	HIMAGELIST	GetSysImages () const
	{
		return m_himSystem;
	}

	CSize GetSysImageSize () const
	{
		return m_SysImageSize;
	}

	int GetFolderIcon () const
	{
		return CFavorit::m_iFolderIcon;
	}

	int GetInternetShortcutIcon () const
	{
		return CFavorit::m_iInternetShortcutIcon;
	}

	int GetIDIcon (UINT uiCommandID) const;

	CString GetURLofID (UINT uiCommandID) const;

private:
	CFavorit	m_Root;

	HIMAGELIST	m_himSystem;
	CSize		m_SysImageSize;
};

#endif // !defined(AFX_FAVORITESMANAGER_H__E15D7C87_B803_11D4_95C8_00A0C9289F1B__INCLUDED_)
