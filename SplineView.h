// SplineView.h : interface of the CSplineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEVIEW_H__58166E6B_0367_4356_8524_344CCC19DFE5__INCLUDED_)
#define AFX_SPLINEVIEW_H__58166E6B_0367_4356_8524_344CCC19DFE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSplineView : public CView
{
protected:
	int m_ParamMode;
	bool m_Moving;
	int m_Node2Move;
	CPoint m_PointOld;

	void Display(vector<CPoint> & nodes, CDC *pDC);
	void ParamDisplay(vector<CPoint> & nodes, CDC *pDC);

protected: // create from serialization only
	CSplineView();
	DECLARE_DYNCREATE(CSplineView)

// Attributes
public:
	CSplineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplineView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChordLength();
	afx_msg void OnSqrtChordLength();
	afx_msg void OnUniform();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SplineView.cpp
inline CSplineDoc* CSplineView::GetDocument()
   { return (CSplineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLINEVIEW_H__58166E6B_0367_4356_8524_344CCC19DFE5__INCLUDED_)
