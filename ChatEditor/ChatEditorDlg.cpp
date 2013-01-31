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
// ChatEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatEditor.h"
#include "ChatEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR lpcszSymNames [] = 
{
	_T ("smile"),
	_T ("big smile"),
	_T ("cool"),
	_T ("blush"),
	_T ("tongue"),
	_T ("shy"),
	_T ("wink"),
	_T ("clown"),
	_T ("frown"),
	_T ("shocked")
};

LPCTSTR lpcszSymAliaces [] = 
{
	_T (":)"),	
	_T (":D"),
	_T ("8D"),
	_T (":I"),
	_T (":P"),
	_T ("8)"),
	_T (";)"),
	_T (":o)"),
	_T (":("),
	_T (":O")
};

/////////////////////////////////////////////////////////////////////////////
// CChatEditorDlg dialog

CChatEditorDlg::CChatEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatEditorDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle( ), 
		MAKEINTRESOURCE(IDR_ACCELERATOR));
}

void CChatEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatEditorDlg)
	DDX_Control(pDX, IDC_STATIC_EDIT2, m_wndEditFrame2);
	DDX_Control(pDX, IDC_STATIC_EDIT1, m_wndEditFrame1);
	DDX_Control(pDX, IDC_EDIT_NICK, m_wndNick);
	DDX_Control(pDX, IDC_LIST_MEMBERS, m_lstMembers);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CChatEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_SMILES, OnSmiles)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_LBN_DBLCLK(IDC_LIST_MEMBERS, OnDblclkListMembers)
	ON_BN_CLICKED(IDC_BUTTON_SMILES, OnButtonSmiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatEditorDlg message handlers

BOOL CChatEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// First Editor initialization:
	CRect rectEdit;
	m_wndEditFrame1.GetWindowRect (rectEdit);
	ScreenToClient (rectEdit);

	m_wndEditCtrl1.m_nLeftMarginWidth = 0;
	m_wndEditCtrl1.Create (WS_VISIBLE | WS_CHILD | WS_BORDER, rectEdit, this, 1);
	m_wndEditCtrl1.SetReadOnly (TRUE);
	m_wndEditCtrl1.m_nDlgCode = DLGC_WANTALLKEYS | DLGC_WANTMESSAGE;

	// Second Editor initialization:
	m_wndEditFrame2.GetWindowRect (rectEdit);
	ScreenToClient (rectEdit);

	m_wndEditCtrl2.m_nLeftMarginWidth = 0;
	m_wndEditCtrl2.Create (WS_VISIBLE | WS_CHILD | WS_BORDER, rectEdit, this, 1);
	m_wndEditCtrl2.m_nDlgCode = DLGC_WANTALLKEYS | DLGC_WANTMESSAGE;

	CBitmap bmp;
	bmp.LoadBitmap (IDB_BMP_IMAGES);

	m_lstSym.Create (15, 15, ILC_COLOR24 | ILC_MASK, 10, 0);
	m_lstSym.Add (&bmp, RGB (255, 255, 255));
	m_wndEditCtrl1.SetSymImgList (&m_lstSym);
	m_wndEditCtrl2.SetSymImgList (&m_lstSym);

	for (int i = 0; i < m_lstSym.GetImageCount (); i++)
	{
		BCGP_EDIT_SYM_DEF symDef;
		symDef.m_nIndex = i;
		symDef.m_chReplacement = (TCHAR) (128 + i);
		symDef.m_strSymText = lpcszSymNames [i];
		symDef.m_strSymSequence = lpcszSymAliaces [i];
		m_wndEditCtrl1.m_lstSymDefs.AddTail (symDef);
		m_wndEditCtrl2.m_lstSymDefs.AddTail (symDef);
	}

	m_wndEditCtrl1.m_bEnableSymSupport = TRUE;
	m_wndEditCtrl2.m_bEnableSymSupport = TRUE;

	// Load XML settings for text highlighting
	m_wndEditCtrl1.LoadXMLSettings(_T("bcgpedit-chat.xml"));
	m_wndEditCtrl2.LoadXMLSettings(_T("bcgpedit-chat.xml"));

	m_wndNick.SetWindowText(_T("Dmitry"));
	m_lstMembers.AddString (_T("Albert"));
	m_lstMembers.AddString (_T("Anna"));
	m_lstMembers.AddString (_T("Vadim"));
	m_lstMembers.AddString (_T("Robert"));

	LoadDefaultData ();
	m_wndEditCtrl2.SetFocus ();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CChatEditorDlg::LoadDefaultData ()
{
	BOOL bRet = FALSE;
	LPCTSTR lpszResourceName = MAKEINTRESOURCE (IDR_EXAMPLE_CHAT);
	ASSERT(lpszResourceName != NULL);

	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, _T("Examples"));
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, _T("Examples"));
	
	if (hRsrc == NULL)
	{
		ASSERT(FALSE);
	}
	else
	{
		HGLOBAL hGlobal = LoadResource(hInst, hRsrc);

		if (hGlobal == NULL)
		{
			ASSERT(FALSE);
		}
		else
		{
			LPSTR lpszText = (LPSTR)LockResource(hGlobal);

			if (lpszText == NULL)
			{
				ASSERT(FALSE);
			}
			else
			{
				DWORD dwSize = SizeofResource(hInst, hRsrc);
				USES_CONVERSION;
				CString strText = A2T(lpszText);

				m_wndEditCtrl1.SetWindowText(strText.Left (dwSize));
				m_wndEditCtrl1.EndOfText ();
				bRet = TRUE;
			}

			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}
	}

	return bRet;
}

void CChatEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
#ifndef _BCGPEDIT_STANDALONE
		BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
#endif
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatEditorDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
	CPoint pt(point);
	ScreenToClient(&pt);

	CWnd* pFocusedWnd = GetFocus ();
	if (&m_wndEditCtrl1 == pFocusedWnd)
	{
		CMenu menu;
		if (menu.LoadMenu(IDR_CONTEXT_MENU1))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);

			pPopup->EnableMenuItem (ID_EDIT_COPY, m_wndEditCtrl1.IsCopyEnabled() ? MF_ENABLED : MF_GRAYED);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, 
				AfxGetMainWnd());
		}
		return;
	}
	else if (&m_wndEditCtrl2 == pFocusedWnd)
	{
		CMenu menu;
		if (menu.LoadMenu(IDR_CONTEXT_MENU2))
		{
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT_VALID(pPopup);

			// Enable menu items:
			pPopup->EnableMenuItem (ID_EDIT_CUT, m_wndEditCtrl2.IsCutEnabled() ? MF_ENABLED : MF_GRAYED);
			pPopup->EnableMenuItem (ID_EDIT_COPY, m_wndEditCtrl2.IsCopyEnabled() ? MF_ENABLED : MF_GRAYED);
			pPopup->EnableMenuItem (ID_EDIT_PASTE, m_wndEditCtrl2.IsPasteEnabled() ? MF_ENABLED : MF_GRAYED);

			// Add an item for each available smile:
			CMenu* pSmilesMenu = pPopup->GetSubMenu (pPopup->GetMenuItemCount()-1);
			ASSERT_VALID (pSmilesMenu);

			const int cnMaxSmilesCount = min(10, m_lstSym.GetImageCount ());
			CBitmap bmp[10];
			for (int i = 0; i < cnMaxSmilesCount; i++)
			{
				CString str;
				str.Format(_T("%s\t%s"), lpcszSymAliaces[i], lpcszSymNames[i]);
				pSmilesMenu->AppendMenu(MF_STRING, ID_SMILE1+i, str);

				bmp[i].LoadBitmap (MAKEINTRESOURCE(IDB_BITMAP1+i));

				pSmilesMenu->SetMenuItemBitmaps(ID_SMILE1+i, MF_BYCOMMAND, &(bmp[i]), &(bmp[i]));
			}
			pSmilesMenu->DeleteMenu(0, MF_BYPOSITION);

			// Track menu:
			UINT unResult = pPopup->TrackPopupMenu(
				TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY, 
				point.x, point.y, AfxGetMainWnd());

			// Handle menu results:
			if (unResult <= 0)
			{
				return;
			}

			switch (unResult)
			{
			case ID_EDIT_CUT:
				OnEditCut ();
				return;
			case ID_EDIT_COPY:
				OnEditCopy ();
				return;
			case ID_EDIT_PASTE:
				OnEditPaste ();
				return;
			}

			if (unResult - ID_SMILE1 <= (UINT)cnMaxSmilesCount)
			{
				m_wndEditCtrl2.InsertText (lpcszSymAliaces[unResult-ID_SMILE1], 
					m_wndEditCtrl2.GetCurOffset(), TRUE);
			}

		}
		return;
	}
}

BOOL CChatEditorDlg::PreTranslateMessage(MSG* pMsg) 
{
   if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST) 
   {
	   if (pMsg->message == WM_CHAR && pMsg->wParam == VK_ESCAPE)
	   {
		   OnCancel ();
		   return TRUE;
	   }
      // Translate the message using accelerator table
      ASSERT(m_hAccel);
      return ::TranslateAccelerator(//&m_wndEditCtrl,
		  m_hWnd, m_hAccel, pMsg);
   }
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CChatEditorDlg::OnEditCopy() 
{
	CWnd* pWnd = GetFocus ();
	if (&m_wndEditCtrl1 == pWnd)
	{
		m_wndEditCtrl1.Copy();
	}
	else if (&m_wndEditCtrl2 == pWnd)
	{
		m_wndEditCtrl2.Copy();
	}
}

void CChatEditorDlg::OnEditCut() 
{
	if (&m_wndEditCtrl2 == GetFocus ())
	{
		m_wndEditCtrl2.Cut();
	}
}

void CChatEditorDlg::OnEditPaste() 
{
	if (&m_wndEditCtrl2 == GetFocus ())
	{
		m_wndEditCtrl2.Paste();
	}
}

void CChatEditorDlg::OnEditSelectAll() 
{
	CWnd* pWnd = GetFocus ();
	if (&m_wndEditCtrl1 == pWnd)
	{
		m_wndEditCtrl1.MakeSelection (CBCGPEditCtrl::ST_ALL_TEXT);
	}
	else if (&m_wndEditCtrl2 == pWnd)
	{
		m_wndEditCtrl2.MakeSelection (CBCGPEditCtrl::ST_ALL_TEXT);
	}
}

void CChatEditorDlg::OnEditUndo() 
{
	if (&m_wndEditCtrl2 == GetFocus ())
	{
		m_wndEditCtrl2.OnUndo();
	}
}

void CChatEditorDlg::OnEditRedo() 
{
	if (&m_wndEditCtrl2 == GetFocus ())
	{
		m_wndEditCtrl2.OnRedo();
	}
}

void CChatEditorDlg::OnSmiles() 
{
	m_wndEditCtrl2.SetFocus ();
	m_wndEditCtrl2.InvokeSymList ();
}

void CChatEditorDlg::OnButtonSend() 
{
	CString string = m_wndEditCtrl2.GetText ();
	CString strNick;
	m_wndNick.GetWindowText (strNick);
	CString strTime = CTime::GetCurrentTime().Format(_T("%I:%M %p"));

	CString strText;
	strText.Format(_T("\r\n[%s] %s: %s"), strTime, strNick, string);

	m_wndEditCtrl1.EndOfText (FALSE);
	m_wndEditCtrl1.InsertText (strText, m_wndEditCtrl1.GetCurOffset(), TRUE);
	m_wndEditCtrl2.SetWindowText (_T(""));
	m_wndEditCtrl2.Invalidate ();

}

void CChatEditorDlg::OnDblclkListMembers() 
{
	// TODO: Add your control notification handler code here
	int nRecipient = m_lstMembers.GetCurSel();
	if (nRecipient != LB_ERR)
	{
		CString string;
		m_lstMembers.GetText(nRecipient, string);
		if (!string.IsEmpty())
		{
			CString strText;
			strText.Format(_T("to %s: "), string);
			m_wndEditCtrl2.EndOfText (FALSE);
			m_wndEditCtrl2.InsertText (strText, m_wndEditCtrl2.GetCurOffset(), TRUE);
			m_wndEditCtrl2.SetFocus ();
		}
	}
	
}

void CChatEditorDlg::OnButtonSmiles() 
{
	CMenu menu;
	if (menu.LoadMenu(IDR_MENU_SMILES))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		CMenu* pSmilesMenu = pPopup;
		ASSERT_VALID (pSmilesMenu);
		
		// Add an item for each available smile:
		const int cnMaxSmilesCount = min(10, m_lstSym.GetImageCount ());
		CBitmap bmp[10];
		for (int i = 0; i < cnMaxSmilesCount; i++)
		{
			CString str;
			str.Format(_T("%s\t%s"), lpcszSymAliaces[i], lpcszSymNames[i]);
			pSmilesMenu->AppendMenu(MF_STRING, ID_SMILE1+i, str);

			bmp[i].LoadBitmap (MAKEINTRESOURCE(IDB_BITMAP1+i));

			pSmilesMenu->SetMenuItemBitmaps(ID_SMILE1+i, MF_BYCOMMAND, &(bmp[i]), &(bmp[i]));
		}
		pSmilesMenu->DeleteMenu(0, MF_BYPOSITION);

		// Track menu:
		CWnd* pWnd = GetDlgItem (IDC_BUTTON_SMILES);
		ASSERT_VALID (pWnd);

		CRect rectButton;
		pWnd->GetWindowRect (rectButton);

		UINT unResult = pPopup->TrackPopupMenu(
			TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY, 
			rectButton.left + rectButton.Width(), rectButton.top, AfxGetMainWnd());

		// Handle menu results:
		if (unResult <= 0)
		{
			return;
		}

		if (unResult - ID_SMILE1 <= (UINT)cnMaxSmilesCount)
		{
			m_wndEditCtrl2.InsertText (lpcszSymAliaces[unResult-ID_SMILE1], 
				m_wndEditCtrl2.GetCurOffset(), TRUE);
			m_wndEditCtrl2.SetFocus ();
		}
	}
}
