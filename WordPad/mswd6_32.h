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

#ifndef MSWD6_32_H
#define MSWD6_32_H

typedef unsigned long (pascal *PFN_RTF_CALLBACK)(int, int);

extern "C" int pascal InitConverter32(HANDLE, char *);
extern "C" HANDLE pascal RegisterApp32(unsigned long, void *);
extern "C" int pascal IsFormatCorrect32(HANDLE, HANDLE);
extern "C" int pascal ForeignToRtf32(HANDLE, void *, HANDLE, HANDLE, HANDLE, PFN_RTF_CALLBACK);
extern "C" int pascal RtfToForeign32(HANDLE, LPSTORAGE, HANDLE, HANDLE, PFN_RTF_CALLBACK);

#endif
