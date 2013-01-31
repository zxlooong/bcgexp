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
// BackgndImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPSkins.h"
#include "BackgndImageDlg.h"
#include "ImageStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackgndImageDlg dialog


CBackgndImageDlg::CBackgndImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackgndImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackgndImageDlg)
	m_strFilePath = CImageStyle::m_strImagePath;
	m_iImageType = CImageStyle::m_bIsInternalImage ? 0 : 1;
	m_iBright = CImageStyle::m_nHighlight;
	m_strBright = _T("");
	//}}AFX_DATA_INIT
}


void CBackgndImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackgndImageDlg)
	DDX_Control(pDX, IDC_TEXT_COLOR, m_btnTextColor);
	DDX_Control(pDX, IDC_PICTURE_AREA, m_wndPictureArea);
	DDX_Control(pDX, IDC_BRIGHT, m_wndBright);
	DDX_Control(pDX, IDC_FILE_PATH, m_wndFilePath);
	DDX_Control(pDX, IDC_BROWSE, m_wndBrowse);
	DDX_Text(pDX, IDC_FILE_PATH, m_strFilePath);
	DDX_Radio(pDX, IDC_IMAGE_TYPE1, m_iImageType);
	DDX_Slider(pDX, IDC_BRIGHT, m_iBright);
	DDX_Text(pDX, IDC_BRIGHT_VALUE, m_strBright);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackgndImageDlg, CDialog)
	//{{AFX_MSG_MAP(CBackgndImageDlg)
	ON_BN_CLICKED(IDC_IMAGE_TYPE1, OnImageType)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_IMAGE_TYPE2, OnImageType)
	ON_EN_CHANGE(IDC_FILE_PATH, OnChangeFilePath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackgndImageDlg message handlers

BOOL CBackgndImageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_wndPictureArea.GetClientRect (&m_rectPreview);
	m_wndPictureArea.MapWindowPoints (this, &m_rectPreview);

	m_wndBright.SetRange (100, 300);
	m_wndBright.SetPos (0);
	m_strBright.Format (_T("%d"), m_iBright);

	m_btnTextColor.SetColor (CImageStyle::m_clrText);
	m_btnTextColor.EnableAutomaticButton (_T("Default"), globalData.clrBarText);
	
	UpdateData (FALSE);
	OnImageType();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBackgndImageDlg::OnOK() 
{
	UpdateData ();

	if (m_iImageType == 1)
	{
		//----------------------
		// Check image validity:
		//----------------------
		HBITMAP hbmp = (HBITMAP) ::LoadImage (
			AfxGetInstanceHandle (),
			m_strFilePath,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hbmp == NULL)
		{
			MessageBox (_T("Can not load bitmap"));
			m_wndFilePath.SetFocus ();
			return;
		}

		::DeleteObject (hbmp);
	}

	CImageStyle::m_strImagePath = m_strFilePath;
	CImageStyle::m_nHighlight = m_iBright;
	CImageStyle::m_bIsInternalImage = m_iImageType == 0;
	CImageStyle::m_clrText = m_btnTextColor.GetColor ();

	CDialog::OnOK();
}

void CBackgndImageDlg::OnImageType() 
{
	UpdateData ();

	m_wndFilePath.EnableWindow (m_iImageType == 1);
	m_wndBrowse.EnableWindow (m_iImageType == 1);

	if (m_iImageType == 1)
	{
		m_wndFilePath.SetFocus ();
	}

	UpdateBitmap ();
}

void CBackgndImageDlg::OnBrowse() 
{
	CFileDialog dlg (TRUE, _T("bmp"), m_strFilePath, OFN_HIDEREADONLY, 
		_T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), this);
	if (dlg.DoModal () == IDOK)
	{
		m_strFilePath = dlg.GetPathName ();
		UpdateData (FALSE);

		UpdateBitmap ();
	}
}

void CBackgndImageDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	UpdateData ();

	InvalidateRect (m_rectPreview, FALSE);
	UpdateWindow ();

	m_strBright.Format (_T("%d"), m_iBright);
	UpdateData (FALSE);
}

void CBackgndImageDlg::UpdateBitmap ()
{
	UpdateData ();

	if (m_Bitmap.GetSafeHandle () != NULL)
	{
		::DeleteObject (m_Bitmap.Detach ());
	}

	if (m_iImageType == 1)
	{
		HBITMAP hbmp = (HBITMAP) ::LoadImage (
			AfxGetInstanceHandle (),
			m_strFilePath,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hbmp != NULL)
		{
			m_Bitmap.Attach (hbmp);
		}
	}
	else
	{
		m_Bitmap.LoadBitmap (IDB_BACKGROUND);
	}

	InvalidateRect (m_rectPreview);
	UpdateWindow ();
}

void CBackgndImageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (m_Bitmap.GetSafeHandle () == NULL)
	{
		dc.FillSolidRect (m_rectPreview, ::GetSysColor (COLOR_3DFACE));

		CString str = _T("No image to display");
		dc.SetBkMode (TRANSPARENT);
		dc.DrawText (str, m_rectPreview, DT_CENTER | DT_VCENTER | DT_WORDBREAK);

		return;
	}

	BITMAP bmp;
	m_Bitmap.GetBitmap (&bmp);

	int cx = bmp.bmWidth;
	int cy = bmp.bmHeight;

	int cxdest;
	int cydest;

	CRect rectRest = m_rectPreview;

	if (cx > cy)
	{
		cxdest = m_rectPreview.Width ();
		cydest = cx > cxdest ? 
			m_rectPreview.Height () * cxdest / cx :
			m_rectPreview.Height () * cx / cxdest;

		rectRest.top += cydest;
	}
	else
	{
		cydest = m_rectPreview.Height ();
		cxdest = cy > cydest ? 
			m_rectPreview.Width () * cydest / cy :
			m_rectPreview.Width () * cy / cydest;

		rectRest.left += cxdest;
	}

	dc.FillSolidRect (rectRest, ::GetSysColor (COLOR_3DFACE));

	CDC dcMem;
	dcMem.CreateCompatibleDC (&dc);

	CBitmap* pBmpOld = dcMem.SelectObject (&m_Bitmap);

	dc.StretchBlt (m_rectPreview.left, m_rectPreview.top, cxdest, cydest, 
					&dcMem, 0, 0, cx, cy, SRCCOPY);

	dcMem.SelectObject (pBmpOld);

	CBCGPDrawManager dm (dc);
	dm.HighlightRect (CRect (m_rectPreview.TopLeft (), CSize (cxdest, cydest)),
						m_iBright);
}

void CBackgndImageDlg::OnChangeFilePath() 
{
	UpdateBitmap ();
}
