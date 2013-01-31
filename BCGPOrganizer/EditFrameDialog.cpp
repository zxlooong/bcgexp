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
// EditFrameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "bcgporganizer.h"
#include "EditFrameDialog.h"
#include "EditFrameView.h"

#include "mainfrm.h"

#include "keys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditFrameDialog

IMPLEMENT_DYNCREATE(CEditFrameDialog, CFrameDialog)

CEditFrameDialog::CEditFrameDialog()
	: CFrameDialog ()
{
}

CEditFrameDialog::CEditFrameDialog(UINT nIDResource, CWnd* pParentWnd /*= NULL*/)
	: CFrameDialog (nIDResource, pParentWnd)
{
}

CEditFrameDialog::~CEditFrameDialog()
{
}

void CEditFrameDialog::SetText (const CString& rText)
{
	m_EditView->SetWindowText (rText);
}

void CEditFrameDialog::GetText (CString& rText) const
{
	m_EditView->GetWindowText (rText);
}

void CEditFrameDialog::CreateDocumentColors ()
{
	typedef struct 
	{
		COLORREF	color;
		TCHAR*		szName;
	} 
	ColorTableEntry;

	int i = 0;
	int nNumColours = 0;

	static ColorTableEntry colorsMain [] = 
	{
		{	RGB (255, 255, 255),	_T("White, Background 1")	},
		{	RGB (0, 0, 0),			_T("Black, Text 1")			},
		{	RGB (238, 236, 225),	_T("Tan, Background 2")		},
		{	RGB (31, 73, 125),		_T("Dark Blue, Text 2")		},
		{	RGB (79, 129, 189),		_T("Blue, Accent 1")		},
		{	RGB (192, 80, 77),		_T("Red, Accent 2")			},
		{	RGB (155, 187, 89),		_T("Olive Green, Accent 3")	},
		{	RGB (128, 100, 162),	_T("Purple, Accent 4")		},
		{	RGB (75, 172, 198),		_T("Aqua, Accent 5")		},
		{	RGB (245, 150, 70),		_T("Orange, Accent 6")		}
	};

	static ColorTableEntry colorsAdditional [] = 
	{
		{	RGB (242, 242, 242),	_T("White, Background 1, Darker 5%")	},
		{	RGB (127, 127, 127),	_T("Black, Text 1, Lighter 50%")		},
		{	RGB (214, 212, 202),	_T("Tan, Background 2, Darker 10%")		},
		{	RGB (210, 218, 229),	_T("Dark Blue, Text 2, Lighter 80%")	},
		{	RGB (217, 228, 240),	_T("Blue, Accent 1, Lighter 80%")		},
		{	RGB (244, 219, 218),	_T("Red, Accent 2, Lighter 80%")		},
		{	RGB (234, 241, 221),	_T("Olive Green, Accent 3, Lighter 80%")},
		{	RGB (229, 223, 235),	_T("Purple, Accent 4, Lighter 80%")		},
		{	RGB (216, 237, 242),	_T("Aqua, Accent 5, Lighter 80%")		},
		{	RGB (255, 234, 218),	_T("Orange, Accent 6, Lighter 80%")		},

		{	RGB (215, 215, 215),	_T("White, Background 1, Darker 15%")	},
		{	RGB (89, 89, 89),		_T("Black, Text 1, Lighter 35%")		},
		{	RGB (177, 176, 167),	_T("Tan, Background 2, Darker 25%")		},
		{	RGB (161, 180, 201),	_T("Dark Blue, Text 2, Lighter 60%")	},
		{	RGB (179, 202, 226),	_T("Blue, Accent 1, Lighter 60%")		},
		{	RGB (233, 184, 182),	_T("Red, Accent 2, Lighter 60%")		},
		{	RGB (213, 226, 188),	_T("Olive Green, Accent 3, Lighter 60%")},
		{	RGB (203, 191, 215),	_T("Purple, Accent 4, Lighter 60%")		},
		{	RGB (176, 220, 231),	_T("Aqua, Accent 5, Lighter 60%")		},
		{	RGB (255, 212, 181),	_T("Orange, Accent 6, Lighter 60%")		},

		{	RGB (190, 190, 190),	_T("White, Background 1, Darker 25%")	},
		{	RGB (65, 65, 65),		_T("Black, Text 1, Lighter 25%")		},
		{	RGB (118, 117, 112),	_T("Tan, Background 2, Darker 35%")		},
		{	RGB (115, 143, 175),	_T("Dark Blue, Text 2, Lighter 40%")	},
		{	RGB (143, 177, 213),	_T("Blue, Accent 1, Lighter 40%")		},
		{	RGB (222, 149, 147),	_T("Red, Accent 2, Lighter 40%")		},
		{	RGB (192, 213, 155),	_T("Olive Green, Accent 3, Lighter 40%")},
		{	RGB (177, 160, 197),	_T("Purple, Accent 4, Lighter 40%")		},
		{	RGB (137, 203, 218),	_T("Aqua, Accent 5, Lighter 40%")		},
		{	RGB (255, 191, 145),	_T("Orange, Accent 6, Lighter 40%")		},

		{	RGB (163, 163, 163),	_T("White, Background 1, Darker 35%")	},
		{	RGB (42, 42, 42),		_T("Black, Text 1, Lighter 15%")		},
		{	RGB (61, 61, 59),		_T("Tan, Background 2, Darker 50%")		},
		{	RGB (20, 57, 92),		_T("Dark Blue, Text 2, Darker 25%")		},
		{	RGB (54, 96, 139),		_T("Blue, Accent 1, Darker 25%")		},
		{	RGB (149, 63, 60),		_T("Red, Accent 2, Darker 25%")			},
		{	RGB (114, 139, 71),		_T("Olive Green, Accent 3, Darker 25%")	},
		{	RGB (97, 76, 119),		_T("Purple, Accent 4, Darker 25%")		},
		{	RGB (41, 128, 146),		_T("Aqua, Accent 5, Darker 25%")		},
		{	RGB (190, 112, 59),		_T("Orange, Accent 6, Darker 25%")		},

		{	RGB (126, 126, 126),	_T("White, Background 1, Darker 50%")	},
		{	RGB (20, 20, 20),		_T("Black, Text 1, Lighter 5%")			},
		{	RGB (29, 29, 28),		_T("Tan, Background 2, Darker 90%")		},
		{	RGB (17, 40, 64),		_T("Dark Blue, Text 2, Darker 50%")		},
		{	RGB (38, 66, 94),		_T("Blue, Accent 1, Darker 50%")		},
		{	RGB (100, 44, 43),		_T("Red, Accent 2, Darker 50%")			},
		{	RGB (77, 93, 49),		_T("Olive Green, Accent 3, Darker 50%")	},
		{	RGB (67, 53, 81),		_T("Purple, Accent 4, Darker 50%")		},
		{	RGB (31, 86, 99),		_T("Aqua, Accent 5, Darker 50%")		},
		{	RGB (126, 77, 42),		_T("Orange, Accent 6, Darker 50%")		},
	};

	static ColorTableEntry colorsStandard [] = 
	{
		{	RGB (200, 15, 18),		_T("Dark Red")		},
		{	RGB (255, 20, 24),		_T("Red")			},
		{	RGB (255, 191, 40),		_T("Orange")		},
		{	RGB (255, 255, 49),		_T("Yellow")		},
		{	RGB (138, 207, 87),		_T("Light Green")	},
		{	RGB (0, 175, 84),		_T("Green")			},
		{	RGB (0, 174, 238),		_T("Light Blue")	},
		{	RGB (0, 111, 189),		_T("Blue")			},
		{	RGB (0, 36, 95),		_T("Black")			},
		{	RGB (114, 50, 157),		_T("Purple")		},
	};

	m_lstMainColors.RemoveAll ();
	nNumColours = sizeof (colorsMain) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstMainColors.AddTail (colorsMain [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsMain [i].color, colorsMain [i].szName);
	};

	m_lstAdditionalColors.RemoveAll ();
	nNumColours = sizeof (colorsAdditional) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstAdditionalColors.AddTail (colorsAdditional [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsAdditional [i].color, colorsAdditional [i].szName);
	};

	m_lstStandardColors.RemoveAll ();
	nNumColours = sizeof (colorsStandard) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstStandardColors.AddTail (colorsStandard [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsStandard [i].color, colorsStandard [i].szName);
	};
}

BOOL CEditFrameDialog::CreateRibbonBar ()
{
	CreateDocumentColors ();

	return CFrameDialog::CreateRibbonBar ();
}

void CEditFrameDialog::AddTabs ()
{
	CFrameDialog::AddTabs ();

	AddTab_Format ();
}

void CEditFrameDialog::AddQAT ()
{
	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail (ID_EDIT_UNDO);
	lstQATCmds.AddTail (ID_EDIT_REPEAT);

	m_wndRibbonBar.SetQuickAccessCommands (lstQATCmds);
}

void CEditFrameDialog::AddTab_Format ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("Format Text\no"), IDB_EDITCTRL_SMALL, IDB_EDITCTRL_LARGE);

	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (_T("Clipboard"), m_PanelImages.ExtractIcon (0));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_PASTE, _T("Paste"), 0, 0));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, _T("Cut"), 1, -1));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, _T("Copy"), 2, -1));

	CBCGPRibbonFontComboBox::m_bDrawUsingFont = TRUE;
	CBCGPRibbonPanel* pPanelFont = pCategory->AddPanel (_T("Font"), m_PanelImages.ExtractIcon (1));
	CBCGPRibbonButtonsGroup* pFontGroup = new CBCGPRibbonButtonsGroup;

	CBCGPRibbonFontComboBox* pFontCombo = new CBCGPRibbonFontComboBox (ID_FONT_FONT);
	pFontCombo->SelectItem (_T("Arial"));
	pFontGroup->AddButton (pFontCombo);

	CBCGPRibbonComboBox* pFontSizeCombo = new CBCGPRibbonComboBox (ID_FONT_SIZE, TRUE, 20);
	pFontSizeCombo->AddItem (_T("8"));
	pFontSizeCombo->AddItem (_T("9"));
	pFontSizeCombo->AddItem (_T("10"));
	pFontSizeCombo->AddItem (_T("11"));
	pFontSizeCombo->AddItem (_T("12"));
	pFontSizeCombo->AddItem (_T("14"));
	pFontSizeCombo->AddItem (_T("16"));
	pFontSizeCombo->AddItem (_T("18"));
	pFontSizeCombo->AddItem (_T("20"));
	pFontSizeCombo->AddItem (_T("22"));
	pFontSizeCombo->AddItem (_T("24"));
	pFontSizeCombo->AddItem (_T("26"));
	pFontSizeCombo->AddItem (_T("28"));
	pFontSizeCombo->AddItem (_T("36"));
	pFontSizeCombo->AddItem (_T("48"));
	pFontSizeCombo->AddItem (_T("72"));
	pFontSizeCombo->SelectItem (4);
	pFontGroup->AddButton (pFontSizeCombo);

	pPanelFont->Add (pFontGroup);

	pPanelFont->AddToolBar (IDR_EDITCTRL_FONT);

	CBCGPRibbonColorButton* pFontColorHighlightBtn = new CBCGPRibbonColorButton ();
	pFontColorHighlightBtn->EnableOtherButton (_T("Other..."));
	pFontColorHighlightBtn->SetColor (RGB (255, 255, 255));

	pPanelFont->ReplaceByID (ID_FONT_TEXTHIGHLIGHT, pFontColorHighlightBtn);

	CBCGPRibbonColorButton* pFontColorBtn = new CBCGPRibbonColorButton ();
	pFontColorBtn->SetDefaultCommand (FALSE);
	pFontColorBtn->EnableAutomaticButton (_T("&Automatic"), RGB (0, 0, 0));
	pFontColorBtn->EnableOtherButton (_T("&More Colors..."), _T("More Colors"));
	pFontColorBtn->SetColumns (10);
	pFontColorBtn->SetColorBoxSize (CSize (17, 17));
	pFontColorBtn->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pFontColorBtn->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE);
	pFontColorBtn->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);

	pPanelFont->ReplaceByID (ID_FONT_COLOR, pFontColorBtn);

	//pPanelFont->EnableLaunchButton (ID_FONT_BOX);

	CBCGPRibbonPanel* pPanelEditing = pCategory->AddPanel (_T("Editing"), m_PanelImages.ExtractIcon (2));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_UNDO, _T("Undo"), 3, -1));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_REDO, _T("Redo"), 5, -1));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_REPEAT, _T("Repeat"), 4, -1));

	pPanelEditing->Add (new CBCGPRibbonSeparator ());

	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_FIND, _T("Find"), 6, -1));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_REPLACE, _T("Replace"), 7, -1));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_SELECT_ALL, _T("Select All"), 8, -1));
}

void CEditFrameDialog::SetKeys ()
{
	CFrameDialog::SetKeys ();

	for (int i = 0; stdKeys [i].uiCmd != 0; i++)
	{
		CString str = stdKeys [i].lpszKey;

		int nAmpIndex = str.Find (_T('&'));

		if (nAmpIndex >= 0)
		{
			CString str1 = str.Left (nAmpIndex);
			CString str2 = str.Mid (nAmpIndex + 1);

			m_wndRibbonBar.SetElementKeys (stdKeys [i].uiCmd, str1, str2);
		}
		else
		{
			m_wndRibbonBar.SetElementKeys (stdKeys [i].uiCmd, str);
		}
	}
}

BOOL CEditFrameDialog::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* /*pContext*/)
{
	CCreateContext context;
	context.m_pCurrentFrame = this;
	context.m_pNewViewClass = RUNTIME_CLASS(CEditFrameView);

	m_EditView = (CEditFrameView*)CFrameDialog::CreateView(&context, AFX_IDW_PANE_FIRST);

	return m_EditView != NULL;
}

BOOL CEditFrameDialog::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, 
							 CWnd* pParentWnd, CCreateContext* pContext)
{
	if (!CFrameDialog::LoadFrame (nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	m_EditView->SetFocus ();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CEditFrameDialog, CFrameDialog)
	//{{AFX_MSG_MAP(CEditFrameDialog)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditFrameDialog message handlers

void CEditFrameDialog::OnFilePrint()
{
	m_EditView->PostMessage (WM_COMMAND, LOWORD(GetCurrentMessage()->wParam));
}
