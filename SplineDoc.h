// SplineDoc.h : interface of the CSplineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDOC_H__A780F47E_5307_455F_A28D_BCBF4E3AB332__INCLUDED_)
#define AFX_SPLINEDOC_H__A780F47E_5307_455F_A28D_BCBF4E3AB332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

class CSplineDoc : public CDocument
{
public:
	vector<CPoint> nodes;

protected: // create from serialization only
	CSplineDoc();
	DECLARE_DYNCREATE(CSplineDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLINEDOC_H__A780F47E_5307_455F_A28D_BCBF4E3AB332__INCLUDED_)
