// GlobalData.h: interface for the CGlobalData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALDATA_H__956F3F4E_9517_4A8F_BA70_512792057661__INCLUDED_)
#define AFX_GLOBALDATA_H__956F3F4E_9517_4A8F_BA70_512792057661__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int c_ViewCount = 6;
const LPCTSTR c_ViewNames[c_ViewCount] =
{
	_T("Home"), 
	_T("Mail"),
	_T("Calendar"),
	_T("Tasks"),
	_T("Macros"),
	_T("Gantt")
};

const int c_CategoryCount = 6;
const LPCTSTR c_CategoryNames[c_CategoryCount] =
{
    _T("Blue Category"), 
    _T("Green Category"), 
    _T("Orange Category"), 
    _T("Purple Category"), 
    _T("Red Category"), 
    _T("Yellow Category")
};
const COLORREF c_CategoryColors[c_CategoryCount] =
{
	RGB (118, 158, 218), 
	RGB (135, 210, 126),
	RGB (244, 152,  89),
	RGB (150, 124, 210),
	RGB (229, 104, 111),
	RGB (255, 249,  90)
};

const int c_ShowasCount = 4;
const LPCTSTR c_ShowasNames[c_ShowasCount] =
{
    _T("Free"), 
    _T("Tentative"), 
    _T("Busy"), 
    _T("Out of Office")
};
const COLORREF c_ShowasColors[c_ShowasCount] =
{
	CLR_DEFAULT, 
	RGB (128, 128, 255),
	RGB (  0,   0, 255),
	RGB (128,   0, 128)
};

#endif // !defined(AFX_GLOBALDATA_H__956F3F4E_9517_4A8F_BA70_512792057661__INCLUDED_)
