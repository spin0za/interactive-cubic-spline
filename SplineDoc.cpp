// SplineDoc.cpp : implementation of the CSplineDoc class
//

#include "stdafx.h"
#include "Spline.h"

#include "SplineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc

IMPLEMENT_DYNCREATE(CSplineDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplineDoc, CDocument)
	//{{AFX_MSG_MAP(CSplineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc construction/destruction

CSplineDoc::CSplineDoc()
{
	// TODO: add one-time construction code here

}

CSplineDoc::~CSplineDoc()
{
}

BOOL CSplineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSplineDoc serialization

void CSplineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc diagnostics

#ifdef _DEBUG
void CSplineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSplineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplineDoc commands
