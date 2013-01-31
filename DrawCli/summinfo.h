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
// summinfo.h : interface of the CSummInfo classes
//

#include "propset.h"
#include <objidl.h>

extern const OLECHAR szSummInfo[];

DEFINE_GUID( FMTID_SummaryInformation, 0xF29F85E0, 0x4FF9, 0x1068,
	0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9 );

class CSummInfo
{
public:
	CSummInfo();
	BOOL SetTitle(LPCTSTR szTitle);
	CString GetTitle();
	BOOL SetSubject(LPCTSTR szSubject);
	CString GetSubject();
	BOOL SetAuthor(LPCTSTR szAuthor);
	CString GetAuthor();
	BOOL SetKeywords(LPCTSTR szKeywords);
	CString GetKeywords();
	BOOL SetComments(LPCTSTR szComments);
	CString GetComments();
	BOOL SetTemplate(LPCTSTR szTemplate);
	CString GetTemplate();
	BOOL SetLastAuthor(LPCTSTR szLastAuthor);
	CString GetLastAuthor();
	BOOL IncrRevNum();
	CString GetRevNum();
	void StartEditTimeCount();
	BOOL AddCountToEditTime();
	CString GetEditTime();
	BOOL RecordPrintDate();
	CString GetLastPrintDate();
	BOOL RecordCreateDate();
	CString GetCreateDate();
	BOOL RecordSaveDate();
	CString GetLastSaveDate();
	BOOL SetNumPages(ULONG nPages);
	CString GetNumPages();
	BOOL SetNumWords(ULONG nWords);
	CString GetNumWords();
	BOOL SetNumChars(ULONG nChars);
	CString GetNumChars();
	BOOL SetAppname(LPCTSTR szAppname);
	CString GetAppname();
	BOOL SetSecurity(ULONG nLevel);
	CString GetSecurity();
	BOOL WriteToStorage(LPSTORAGE lpRootStg);
	BOOL ReadFromStorage(LPSTORAGE lpRootStg);
protected:
	CPropertySet m_propSet;
	CPropertySection* m_pSection;
	__int64 startEdit;
};
