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
// srvritem.h : interface of the CWordPadSrvrItem class
//

class CWordPadDoc;
class CWordPadView;

class CEmbeddedItem : public COleServerItem
{
	DECLARE_DYNAMIC(CEmbeddedItem)

// Constructors
public:
	CEmbeddedItem(CWordPadDoc* pContainerDoc, int nBeg = 0, int nEnd = -1);

// Attributes
	int m_nBeg;
	int m_nEnd;
	LPDATAOBJECT m_lpRichDataObj;
	CWordPadDoc* GetDocument() const
		{ return (CWordPadDoc*) COleServerItem::GetDocument(); }
	CWordPadView* GetView() const;

// Implementation
public:
	BOOL OnDrawEx(CDC* pDC, CSize& rSize, BOOL bOutput);
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};


/////////////////////////////////////////////////////////////////////////////
