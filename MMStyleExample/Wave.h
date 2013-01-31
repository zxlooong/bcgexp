//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// Wave.h: interface for the CWave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVE_H__A64AE70F_6641_4995_A8AD_9940D35591D2__INCLUDED_)
#define AFX_WAVE_H__A64AE70F_6641_4995_A8AD_9940D35591D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWaveBuffer;

class CWaveBuffer {
    public:
        CWaveBuffer();
        ~CWaveBuffer();
        BOOL Init(HWAVEOUT hWave, int Size);
        void Done();
        BOOL Write(PBYTE pData, int nBytes, int& BytesWritten);
        void Flush();

    private:
        WAVEHDR      m_Hdr;
        HWAVEOUT     m_hWave;
        int          m_nBytes;
};

class CWaveOut {
    public:
        CWaveOut(LPCWAVEFORMATEX Format, int nBuffers, int BufferSize);
        ~CWaveOut();
        void Write(PBYTE Data, int nBytes);
        void Flush();
        void Wait();
        void Reset();
    private:
        const HANDLE       m_hSem;
        const int          m_nBuffers;
        int          m_CurrentBuffer;
        BOOL         m_NoBuffer;
        CWaveBuffer *m_Hdrs;
        HWAVEOUT     m_hWave;
};

HRESULT RenderFileToMMStream(WCHAR * pszFileName, IMultiMediaStream **ppMMStream);
HRESULT RenderStreamToDevice(IMultiMediaStream *pMMStream);

#endif // !defined(AFX_WAVE_H__A64AE70F_6641_4995_A8AD_9940D35591D2__INCLUDED_)
