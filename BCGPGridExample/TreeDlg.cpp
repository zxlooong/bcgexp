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
// TreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "TreeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

inline int Rand (int nMax)
{
	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeDlg dialog


CTreeDlg::CTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeDlg)
	DDX_Control(pDX, IDC_TREE_RECT, m_wndTreeLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeDlg message handlers

BOOL CTreeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Create grid tree:
	CRect rectGrid;
	m_wndTreeLocation.GetClientRect (&rectGrid);
	m_wndTreeLocation.MapWindowPoints (this, &rectGrid);

	m_wndGridTree.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);

	m_wndGridTree.EnableColumnAutoSize (TRUE);
	m_wndGridTree.SetSingleSel (FALSE);
	m_wndGridTree.EnableGroupByBox (FALSE);
	m_wndGridTree.SetReadOnly ();
	m_wndGridTree.SetWholeRowSel ();
	m_wndGridTree.EnableHeader (TRUE, 0);

	// Load grid images:
	CBitmap bmp;
	bmp.LoadBitmap (IDB_ICONS);

	m_Images.Create (16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_Images.Add (&bmp, RGB (255, 0, 255));

	m_wndGridTree.SetImageList (&m_Images);

	// Set grid colors
	CBCGPGridColors colors;
	colors.m_LeftOffsetColors.m_clrBackground = globalData.clrWindow;

	m_wndGridTree.SetColorTheme (colors);
	
	m_wndGridTree.InsertColumn (0, _T("Name"), 80);
	m_wndGridTree.InsertColumn (1, _T("Size"), 30);
	m_wndGridTree.InsertColumn (2, _T("Type"), 50);
	m_wndGridTree.InsertColumn (3, _T("Date"), 80);
	m_wndGridTree.InsertColumn (4, _T("Attributes"), 30);

	m_wndGridTree.SetColumnAlign (1, HDF_RIGHT);

	srand ((unsigned)time (NULL));

	const int nColumns = m_wndGridTree.GetColumnCount ();

	// Create root item:
	CBCGPGridRow* pRoot = m_wndGridTree.CreateRow (nColumns);
	ASSERT_VALID (pRoot);

	pRoot->AllowSubItems ();
	pRoot->GetItem (0)->SetValue (_T("My Computer"));
	pRoot->GetItem (0)->SetImage (0);

	m_wndGridTree.AddRow (pRoot, FALSE);

	// Create "disk C":
	CBCGPGridRow* pDiskC = m_wndGridTree.CreateRow (nColumns);
	ASSERT_VALID (pDiskC);

	pDiskC->GetItem (0)->SetValue (_T("My Local Disk (C:)"));
	pDiskC->GetItem (0)->SetImage (1);
	pDiskC->AllowSubItems ();

	pRoot->AddSubItem (pDiskC, FALSE);

	// Create "Users":
	CBCGPGridRow* pUsers = m_wndGridTree.CreateRow (nColumns);
	ASSERT_VALID (pUsers);

	pUsers->GetItem (0)->SetValue (_T("Users"));
	pUsers->GetItem (0)->SetImage (3);

	pRoot->AddSubItem (pUsers, FALSE);

	// Create "Network":
	CBCGPGridRow* pNetwork = m_wndGridTree.CreateRow (nColumns);
	ASSERT_VALID (pNetwork);

	pNetwork->GetItem (0)->SetValue (_T("Network"));
	pNetwork->GetItem (0)->SetImage (4);

	pRoot->AddSubItem (pNetwork, FALSE);

	// Create "c:\\Images":
	CBCGPGridRow* pFolder1 = m_wndGridTree.CreateRow (nColumns);
	ASSERT_VALID (pFolder1);

	pFolder1->GetItem (0)->SetValue (_T("Images"));
	pFolder1->GetItem (0)->SetImage (2);
	pFolder1->AllowSubItems ();

	pDiskC->AddSubItem (pFolder1, FALSE);
	FillImagesFoder (pFolder1);

	// Create "c:\\Music":
	CBCGPGridRow* pFolder2 = m_wndGridTree.CreateRow (nColumns);
	ASSERT_VALID (pFolder2);

	pFolder2->GetItem (0)->SetValue (_T("Music"));
	pFolder2->GetItem (0)->SetImage (2);
	pFolder2->AllowSubItems ();

	pDiskC->AddSubItem (pFolder2, FALSE);
	FillMusicFoder (pFolder2);

	// Create "c:\\My Project":
	CBCGPGridRow* pFolder3 = m_wndGridTree.CreateRow (nColumns);
	ASSERT_VALID (pFolder3);

	pFolder3->GetItem (0)->SetValue (_T("My Project"));
	pFolder3->GetItem (0)->SetImage (2);
	pFolder3->AllowSubItems ();

	pDiskC->AddSubItem (pFolder3, FALSE);
	FillProjectFoder (pFolder3);

	m_wndGridTree.AdjustLayout ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTreeDlg::FillImagesFoder (CBCGPGridRow* pFolder)
{
	ASSERT_VALID (pFolder);

	const int nColumns = m_wndGridTree.GetColumnCount ();

	for (int i = 0; i < 2; i++)
	{
		CBCGPGridRow* pFile = m_wndGridTree.CreateRow (nColumns);
		ASSERT_VALID (pFile);

		CString strFileName;
		strFileName.Format (_T("Image%04d"), Rand (200));

		// Set name + icon:
		pFile->GetItem (0)->SetValue ((LPCTSTR) strFileName);
		pFile->GetItem (0)->SetImage (5);

		// Set size:
		pFile->GetItem (1)->SetValue ((long) Rand (3000));

		// Set type:
		pFile->GetItem (2)->SetValue (_T("Image file"));

		// Set date:
		COleDateTime date = COleDateTime::GetCurrentTime () -
			COleDateTimeSpan (Rand (200), 0, 0, 0);

		pFile->ReplaceItem (3, new CBCGPGridDateTimeItem (date));

		// Set attributes:
		pFile->GetItem (4)->SetValue (Rand (2) % 2 ? _T("r") : _T(""));

		pFolder->AddSubItem (pFile, FALSE);
	}
}

void CTreeDlg::FillMusicFoder (CBCGPGridRow* pFolder)
{
	ASSERT_VALID (pFolder);

	const int nColumns = m_wndGridTree.GetColumnCount ();

	for (int i = 0; i < 3; i++)
	{
		CBCGPGridRow* pFile = m_wndGridTree.CreateRow (nColumns);
		ASSERT_VALID (pFile);

		CString strFileName;
		strFileName.Format (_T("Song%04d"), Rand (200));

		// Set name + icon:
		pFile->GetItem (0)->SetValue ((LPCTSTR) strFileName);
		pFile->GetItem (0)->SetImage (6);

		// Set size:
		pFile->GetItem (1)->SetValue ((long) Rand (3000));

		// Set type:
		pFile->GetItem (2)->SetValue (_T("Music file"));

		// Set date:
		COleDateTime date = COleDateTime::GetCurrentTime () -
			COleDateTimeSpan (Rand (200), 0, 0, 0);

		pFile->ReplaceItem (3, new CBCGPGridDateTimeItem (date));

		// Set attributes:
		pFile->GetItem (4)->SetValue (Rand (2) % 2 ? _T("r") : _T(""));

		pFolder->AddSubItem (pFile, FALSE);
	}
}

void CTreeDlg::FillProjectFoder (CBCGPGridRow* pFolder)
{
	ASSERT_VALID (pFolder);

	LPCTSTR arNames [] =
	{
		_T("test.cpp"),
		_T("test.sln"),
		_T("test.h"),
		_T("stdafx.h"),
		_T("stdafx.cpp"),
		_T("testView.cpp"),
		_T("testView.h"),
		NULL
	};

	const int nColumns = m_wndGridTree.GetColumnCount ();

	for (int i = 0; arNames [i] != NULL; i++)
	{
		CBCGPGridRow* pFile = m_wndGridTree.CreateRow (nColumns);
		ASSERT_VALID (pFile);

		CString strFileName = arNames [i];
		BOOL bIsCPP = strFileName.Find (_T(".cpp")) >= 0;
		BOOL bIsH = strFileName.Find (_T(".h")) >= 0;

		// Set name + icon:
		pFile->GetItem (0)->SetValue ((LPCTSTR) strFileName);
		pFile->GetItem (0)->SetImage (bIsCPP ? 7 : bIsH ? 8 : 9);

		// Set size:
		pFile->GetItem (1)->SetValue ((long) Rand (300));

		// Set type:
		pFile->GetItem (2)->SetValue (bIsCPP ? _T("C++ Source") :
			bIsH ? _T("C/C++ Header") : _T("VS Solution"));

		// Set date:
		COleDateTime date = COleDateTime::GetCurrentTime () -
			COleDateTimeSpan (Rand (200), 0, 0, 0);

		pFile->ReplaceItem (3, new CBCGPGridDateTimeItem (date));

		// Set attributes:
		pFile->GetItem (4)->SetValue (Rand (2) % 2 ? _T("r") : _T(""));

		pFolder->AddSubItem (pFile, FALSE);
	}
}
