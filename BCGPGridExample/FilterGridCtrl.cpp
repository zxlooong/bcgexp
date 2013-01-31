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
// FilterGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpgridexample.h"
#include "FilterGridCtrl.h"
#include "FilterListDlg.h"
#include "FilterStringDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------
// Demo data
//----------

#define NAMES1_NUM	19
LPCTSTR arNames1 [NAMES1_NUM] =
{
	_T("Maria Anders"),
	_T("Ana Trujillo"),
	_T("Christina Berglund"),
	_T("Hanna Moos"),
	_T("Elizabeth Lincoln"),
	_T("Elizabeth Brown"),
	_T("Rita Muller"),
	_T("Janine Labrune"),
	_T("Ann Devon"),
	_T("Aria Cruz"),
	_T("Maria Larsson"),
	_T("Lino Rodriguez"),
	_T("Patricia McKenna"),
	_T("Helen Bennett"),
	_T("Annette Roulet"),
	_T("Yoshi Tannamuri"),
	_T("Catherine Dewey"),
	_T("Marie Bertrand"),
	_T("Isabel de Castro"),
};

#define NAMES2_NUM	42
LPCTSTR arNames2 [NAMES2_NUM] =
{
	_T("Antonio Moreno"),
	_T("Thomas Hardy"),
	_T("Frederique Citeaux"),
	_T("Martin Sommer"),
	_T("Laurence Lebihan"),
	_T("Victoria Ashworth"),
	_T("Patricio Simpson"),
	_T("Francisco Chang"),
	_T("Yang Wang"),
	_T("Pedro Afonso"),
	_T("Sven Ottlieb"),
	_T("Roland Mendel"),
	_T("Diego Roel"),
	_T("Martine Rance"),
	_T("Carine Schmitt"),
	_T("Paolo Accorti"),
	_T("Peter Franken"),
	_T("Eduardo Saavedra"),
	_T("Jose Pedro Freyre"),
	_T("Andre Fonseca"),
	_T("Howard Snyder"),
	_T("Manuel Pereira"),
	_T("Mario Pontes"),
	_T("Carlos Hernandez"),
	_T("Yoshi Latimer"),
	_T("Philip Cramer"),
	_T("Daniel Tonini"),
	_T("John Steel"),
	_T("Renate Messner"),
	_T("Jaime Yorres"),
	_T("Carlos Gonzalez"),
	_T("Felipe Izquierdo"),
	_T("Fran Wilson"),
	_T("Giovanni Rovelli"),
	_T("Jean Fresniere"),
	_T("Alexander Feuer"),
	_T("Simon Crowther"),
	_T("Yvonne Moncada"),
	_T("Rene Phillips"),
	_T("Henriette Pfalzheim"),
	_T("Guillermo Fernandez"),
	_T("Georg Pipps"),
};

#define COMPANY_NUM	9
LPCTSTR arCompany [COMPANY_NUM] =
{
	_T("Island Trading"),
	_T("France restauration"),
	_T("North/South"),
	_T("Tortuga Soft"),
	_T("Wartian Herkku"),
	_T("Morgenstern Gesundkost"),
	_T("Eastern Connection"),
	_T("Piccolo und mehr"),
	_T("Simons Brothers"),
};

#define DEPS_NUM	7
LPCTSTR arDepartments [DEPS_NUM] =
{
	_T("Administration"),
	_T("Sales Department"),
	_T("Service Department"),
	_T("Accounting Department"),
	_T("Support Team"),
	_T("Customer Service"),
	_T("Quality Assurance"),
};

#define GENDER_NUM	2
LPCTSTR arGender [GENDER_NUM] =
{
	_T("Male"),
	_T("Female"),
};

#define AGES_NUM	4
LPCTSTR arAges [AGES_NUM] =
{
	_T("Age < 25"),
	_T("25 <= Age < 40"),
	_T("40 <= Age < 50"),
	_T("Age >= 50"),
};

#define FAMILY_NUM	3
LPCTSTR arFamily [FAMILY_NUM] =
{
	_T("Single"),
	_T("Married"),
	_T("Divorced"),
};

/////////////////////////////////////////////////////////////////////////////
// CFilterGridCtrl

IMPLEMENT_DYNCREATE(CFilterGridCtrl, CBCGPGridCtrl)

CFilterGridCtrl::CFilterGridCtrl()
{
}

CFilterGridCtrl::~CFilterGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CFilterGridCtrl, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(CFilterGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFilterGridCtrl message handlers

void FILTER_PARAM::Clear ()
{
	nCol = -1;

	strFilter.Empty ();

	bAll = TRUE;
	lstStrings.RemoveAll ();
	lstValues.RemoveAll ();
}

void FILTER_PARAM::Copy (const FILTER_PARAM& src)
{
	Clear ();

	nCol = src.nCol;
	strFilter = src.strFilter;
	bAll = src.bAll;

	lstStrings.AddTail ((CStringList*) &src.lstStrings);
	lstValues.AddTail ((CList<int, int>*) &src.lstValues);
}

LRESULT CALLBACK CFilterGridCtrl::pfnFilterCallback (WPARAM wParam, LPARAM lParam)
{
	CBCGPGridRow* pRow = (CBCGPGridRow*) wParam;
	ASSERT_VALID (pRow);

	FILTER_PARAM* pParam = (FILTER_PARAM*)lParam;
	ASSERT (pParam != NULL);

	if (pRow->IsGroup ())
	{
		return FALSE; // do not hide groups
	}

	CBCGPGridItem* pItem = pRow->GetItem (pParam->nCol);
	if (pItem == NULL)
	{
		return FALSE;
	}

	ASSERT_VALID (pItem);

	//-------------------------
	// Filter by column "Name":
	//-------------------------
	if (pParam->nCol == 0)
	{
		const CString strItem = pItem->GetLabel ();
		if (strItem.Find (pParam->strFilter) == -1)
		{
			return TRUE; // hide
		}

		return FALSE;
	}

	//----------------------------
	// Filter by column "Company":
	//----------------------------
	if (pParam->nCol == 1)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstStrings.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//-------------------------------
	// Filter by column "Department":
	//-------------------------------
	if (pParam->nCol == 2)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstStrings.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//---------------------------
	// Filter by column "Gender":
	//---------------------------
	if (pParam->nCol == 3)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstStrings.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//------------------------
	// Filter by column "Age":
	//------------------------
	if (pParam->nCol == 4)
	{
		if (!pParam->bAll)
		{
			int nItemValue = 0;;
			switch (pItem->GetValue ().vt)
			{
			case VT_I4:
			case VT_INT:
			case VT_UINT:
			case VT_UI4:
				nItemValue = (long) pItem->GetValue ();
			}

			int nAgeCategory = -1;
			if (nItemValue < 25)
			{
				nAgeCategory = 0; // Age < 25
			}
			else if (nItemValue >= 25 && nItemValue < 40)
			{
				nAgeCategory = 1; // 25 <= Age < 40
			}
			else if (nItemValue >= 40 && nItemValue < 50)
			{
				nAgeCategory = 2; // 40 <= Age < 50
			}
			else
			{
				nAgeCategory = 3; // Age >= 50
			}

			if (pParam->lstValues.Find (nAgeCategory) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//----------------------------------
	// Filter by column "Family Status":
	//----------------------------------
	if (pParam->nCol == 5)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstStrings.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	return FALSE; // show all
}
//********************************************************************************
inline int Rand (int nMax)
{
	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

int CFilterGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//--------------------------
	// Set grid general options:
	//--------------------------
	EnableMarkSortedColumn (TRUE, FALSE);
	EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS | BCGP_GRID_HEADER_SORT);
	SetReadOnly ();

	//--------------------------
	// Set header button images:
	//--------------------------
	m_ImagesHeaderBtn.SetImageSize (CSize (12, 12));
	if (!m_ImagesHeaderBtn.Load (IDB_FILTER))
	{
		ASSERT (FALSE); // Failed to load image
	}

	SetHeaderBtnImageList (&m_ImagesHeaderBtn);

	//-------------
	// Add columns:
	//-------------
	InsertColumn (0, _T("Name"), 150);
	InsertColumn (1, _T("Company"), 150);
	InsertColumn (2, _T("Department"), 150);
	InsertColumn (3, _T("Gender"), 80);
	InsertColumn (4, _T("Age"), 80);
	InsertColumn (5, _T("Family Status"), 100);

	//---------------
	// Add demo data:
	//---------------
	srand( (unsigned)time( NULL ) );

	int nNames1Count = 0;
	int nNames2Count = 0;
	while (nNames1Count < NAMES1_NUM || nNames2Count < NAMES2_NUM)
	{
		BOOL bMale = Rand (2);
		int& nCount = (!bMale) ? nNames1Count : nNames2Count;
		int NUM = (!bMale) ? NAMES1_NUM : NAMES2_NUM;

		if (nCount >= NUM)
		{
			continue;
		}

		CString strName = (!bMale) ? arNames1[nCount++] : arNames2[nCount++];

		AddRec (strName,
			arCompany [Rand (COMPANY_NUM)],
			arDepartments [Rand (DEPS_NUM)],
			arGender [bMale],
			21 + Rand (45),
			arFamily [Rand (FAMILY_NUM)]);
	}

//	LoadState (_T("FilterGrid"));

	EnableFilter (CFilterGridCtrl::pfnFilterCallback, (LPARAM)&m_param);

	AdjustLayout ();

	return 0;
}
//********************************************************************************
BOOL CFilterGridCtrl::AddRec (LPCTSTR strName, LPCTSTR strCompany,
							  LPCTSTR strDepartment, LPCTSTR strGender, int nAge, LPCTSTR strFamily) 
{
	CBCGPGridRow* pRow = CreateRow (GetColumnCount ());

	pRow->GetItem (0)->SetValue (strName);
	pRow->GetItem (1)->SetValue (strCompany);
	pRow->GetItem (2)->SetValue (strDepartment);
	pRow->GetItem (3)->SetValue (strGender);
	pRow->GetItem (4)->SetValue ((long)nAge);
	pRow->GetItem (5)->SetValue (strFamily);

	AddRow (pRow, FALSE);

	return TRUE;
}
//********************************************************************************
void CFilterGridCtrl::GetStringList (CStringList& lst, int nColumn)
{
	lst.RemoveAll ();

	if (nColumn == 1)
	{
		for (int i = 0; i < COMPANY_NUM; i++)
		{
			lst.AddTail (arCompany [i]);
		}
	}

	//-------------------------------
	// Filter by column "Department":
	//-------------------------------
	if (nColumn == 2)
	{
		for (int i = 0; i < DEPS_NUM; i++)
		{
			lst.AddTail (arDepartments [i]);
		}
	}

	//---------------------------
	// Filter by column "Gender":
	//---------------------------
	if (nColumn == 3)
	{
		for (int i = 0; i < GENDER_NUM; i++)
		{
			lst.AddTail (arGender [i]);
		}
	}

	//------------------------
	// Filter by column "Age":
	//------------------------
	if (nColumn == 4)
	{
		for (int i = 0; i < AGES_NUM; i++)
		{
			lst.AddTail (arAges [i]);
		}
	}

	//----------------------------------
	// Filter by column "Family Status":
	//----------------------------------
	if (nColumn == 5)
	{
		for (int i = 0; i < FAMILY_NUM; i++)
		{
			lst.AddTail (arFamily [i]);
		}
	}
}
//********************************************************************************
void CFilterGridCtrl::OnDestroy() 
{
	SaveState (_T("FilterGrid"));
	CBCGPGridCtrl::OnDestroy();
}
//********************************************************************************
int CFilterGridCtrl::GetHeaderMenuButtonImageIndex (int nColumn, BOOL bSortArrow) const
{
	BOOL bFilterColumn = (m_param.nCol == nColumn && !m_param.bAll);
	int nIndex = bFilterColumn ? 3 : 0;

	if (bSortArrow)
	{
		int nSortVal = m_Columns.GetColumnState (nColumn);
		if (nSortVal > 0)
		{
			nIndex += 1;
		}
		else if (nSortVal < 0)
		{
			nIndex += 2;
		}
	}

	CBCGPToolBarImages* pImages = GetHeaderBtnImageList ();
	if (pImages != NULL && pImages->GetCount () >= nIndex)
	{
		return nIndex;
	}

	return CBCGPGridCtrl::GetHeaderMenuButtonImageIndex (nColumn, bSortArrow);
}
//********************************************************************************
void CFilterGridCtrl::OnHeaderMenuButtonClick (int nColumn, CRect rectMenuButton)
{
	CBCGPGridCtrl::OnHeaderMenuButtonClick (nColumn, rectMenuButton);

	SelectColumn (nColumn, FALSE);

	CStringList lstFilterStrings;
	GetStringList (lstFilterStrings, nColumn);

	FILTER_PARAM param;
	param.Copy (m_param);

	if (param.nCol != nColumn)
	{
		param.Clear ();		// Clear old column filter settings
		param.nCol = nColumn;
	}

	switch (param.nCol)
	{
	//-------------------------
	// Filter by column "Name":
	//-------------------------
	case 0:
		{
			CFilterStringDlg dlg (param, this);
			if (dlg.DoModal () == IDOK)
			{
				m_param.Copy (param);
			}
			break;
		}

	//-------------------------------------------
	// Filter by columns "Company", "Department", 
	// "Gender", "Family Status":
	//-------------------------------------------
	case 1:
	case 2:
	case 3:
	case 5:
		{
			CFilterListDlg dlg (lstFilterStrings, param, this);

			if (dlg.DoModal () == IDOK)
			{
				m_param.Copy (param);
			}

			break;
		}

	//------------------------
	// Filter by column "Age":
	//------------------------
	case 4:
		{
			CFilterListDlg dlg (lstFilterStrings, param, this);

			if (dlg.DoModal () == IDOK)
			{
				m_param.Copy (param);
			}

			// Update checked list:
			m_param.lstValues.RemoveAll ();
			for (POSITION pos = m_param.lstStrings.GetHeadPosition (); pos != NULL; )
			{
				const CString& strChecked = m_param.lstStrings.GetNext (pos);
				for (int i = 0; i < AGES_NUM; i++)
				{
					if (strChecked == arAges [i])
					{
						int nCategory = i;
						m_param.lstValues.AddTail (nCategory);
					}
				}
			}

			break;
		}
	}

	SetCurSel (NULL);
	AdjustLayout ();
}
//********************************************************************************
void CFilterGridCtrl::SetDefaultDemoFilter (int nColumn)
{
	m_param.Clear ();		// Clear old filter settings
	m_param.nCol = nColumn;

	//-------------------------
	// Filter by column "Name":
	//-------------------------
	if (m_param.nCol == 0)
	{
		m_param.strFilter = _T("Maria");
	}

	//----------------------------
	// Filter by column "Company":
	//----------------------------
	if (m_param.nCol == 1)
	{
		m_param.bAll = FALSE;
		m_param.lstStrings.AddTail (_T("North/South"));
		m_param.lstStrings.AddTail (_T("Eastern Connection"));
	}

	//-------------------------------
	// Filter by column "Department":
	//-------------------------------
	if (m_param.nCol == 2)
	{
		m_param.bAll = FALSE;
		m_param.lstStrings.AddTail (_T("Sales Department"));
		m_param.lstStrings.AddTail (_T("Accounting Department"));
		m_param.lstStrings.AddTail (_T("Service Department"));
	}

	//---------------------------
	// Filter by column "Gender":
	//---------------------------
	if (m_param.nCol == 3)
	{
		m_param.bAll = FALSE;
		m_param.lstStrings.AddTail (_T("Female"));
	}

	//------------------------
	// Filter by column "Age":
	//------------------------
	if (m_param.nCol == 4)
	{
		m_param.bAll = FALSE;
		m_param.lstValues.AddTail (1); // 25 <= Age < 40
	}

	//----------------------------------
	// Filter by column "Family Status":
	//----------------------------------
	if (m_param.nCol == 5)
	{
		m_param.bAll = FALSE;
		m_param.lstStrings.AddTail (_T("Married"));
	}

	CString str;
	str.Format (_T("Demo filter for column \"%s\""), GetColumnName (nColumn));
	AfxMessageBox (str);

	AdjustLayout ();
}