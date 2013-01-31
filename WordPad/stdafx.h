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
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
//

#ifndef _UNICODE
#define VC_EXTRALEAN        // use stripped down Win32 headers
#endif

#define CONVERTERS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxcmn.h>
#include <afxrich.h>
#include <afxpriv.h>

#define HORZ_TEXTOFFSET 15
#define VERT_TEXTOFFSET 5

class CDisplayIC : public CDC
{
public:
	CDisplayIC() { CreateIC(_T("DISPLAY"), NULL, NULL, NULL); }
};

#if _MSC_VER >= 1300
	#define WPD_CHARFORMAT CHARFORMAT2
	#define WPD_PARAFORMAT PARAFORMAT2
#else
	#define WPD_CHARFORMAT CHARFORMAT
	#define WPD_PARAFORMAT PARAFORMAT
#endif

struct CCharFormat : public WPD_CHARFORMAT
{
	CCharFormat() {cbSize = sizeof(WPD_CHARFORMAT);}
	BOOL operator==(CCharFormat& cf);
};

struct CParaFormat : public WPD_PARAFORMAT
{
	CParaFormat() {cbSize = sizeof(WPD_PARAFORMAT);}
	BOOL operator==(WPD_PARAFORMAT& pf);
};

#include "doctype.h"
#include "chicdial.h"

#include <BCGCBProInc.h>			// BCGPro Control Bar

#if _MSC_VER >= 1400

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#pragma warning (disable : 4996)
#endif
