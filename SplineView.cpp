// SplineView.cpp : implementation of the CSplineView class
//

#include "stdafx.h"
#include "Spline.h"

#include "SplineDoc.h"
#include "SplineView.h"

#include "Solver.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EPS 5
#define N 50
#define MODE_FUNC 0
#define MODE_UNI 1
#define MODE_CL 2
#define MODE_SCL 3

/////////////////////////////////////////////////////////////////////////////
// CSplineView

IMPLEMENT_DYNCREATE(CSplineView, CView)

BEGIN_MESSAGE_MAP(CSplineView, CView)
	//{{AFX_MSG_MAP(CSplineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CHORD_LENGTH, OnChordLength)
	ON_COMMAND(ID_SQRT_CHORD_LENGTH, OnSqrtChordLength)
	ON_COMMAND(ID_UNIFORM, OnUniform)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplineView construction/destruction

CSplineView::CSplineView()
{
	// TODO: add construction code here

	m_ParamMode = MODE_UNI;
	m_Moving = false;
	m_Node2Move = -1;
}

CSplineView::~CSplineView()
{
}

BOOL CSplineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplineView drawing

void CSplineView::OnDraw(CDC* pDC)
{
	CSplineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

}

/////////////////////////////////////////////////////////////////////////////
// CSplineView printing

BOOL CSplineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSplineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSplineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSplineView diagnostics

#ifdef _DEBUG
void CSplineView::AssertValid() const
{
	CView::AssertValid();
}

void CSplineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSplineDoc* CSplineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplineDoc)));
	return (CSplineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplineView message handlers

void CSplineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDC *pDC = GetDC();
	HDC hDC = pDC->m_hDC;
	pDC->SelectStockObject(NULL_BRUSH);
	
	vector<CPoint> nodes = GetDocument()->nodes;
	
	if (!nodes.empty())
	{
		m_Moving = false;
		m_Node2Move = -1;
		// Moving mode: find a matching node to move
		for (int i = 0; i < nodes.size(); i++)
		{
			if (abs(nodes[i].x - point.x) < EPS && abs(nodes[i].y - point.y) < EPS)
			{
				m_Moving = true;
				m_Node2Move = i;
				m_PointOld = nodes[i];
				break;
			}
		}
		
		// Adding mode
		if (m_Node2Move < 0)
		{
			Ellipse(hDC, point.x - EPS, point.y - EPS, point.x + EPS, point.y + EPS);
			GetDocument()->nodes.push_back(point);
			
			if (m_ParamMode)
			{
				nodes = GetDocument()->nodes;
				
				if (nodes.size() == 3)
				{
					ParamDisplay(nodes, pDC);
				}
				if (nodes.size() >= 4)
				{
					// draw spline curve
					
					pDC->SetROP2(R2_NOT);

					nodes.pop_back();
					ParamDisplay(nodes, pDC);
					
					nodes.push_back(point);
					ParamDisplay(nodes,pDC);
				}
			}
		}
	}
	else
	{
		Ellipse(hDC, point.x - EPS, point.y - EPS, point.x + EPS, point.y + EPS);
		GetDocument()->nodes.push_back(point);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CSplineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDC *pDC = GetDC();
	HDC hDC = pDC->m_hDC;

	if (m_Moving)
	{
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->SetROP2(R2_NOT);

		vector<CPoint> nodes = GetDocument()->nodes;

		nodes[m_Node2Move] = m_PointOld;
		Ellipse(hDC, m_PointOld.x - EPS, m_PointOld.y - EPS, m_PointOld.x + EPS, m_PointOld.y + EPS);
		ParamDisplay(nodes, pDC);

		nodes[m_Node2Move] = point;
		Ellipse(hDC, point.x - EPS, point.y - EPS, point.x + EPS, point.y + EPS);
		ParamDisplay(nodes, pDC);

		m_PointOld = point;
		GetDocument()->nodes[m_Node2Move] = point;
	}

	CView::OnMouseMove(nFlags, point);
}

void CSplineView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_Moving = false;

	CView::OnLButtonUp(nFlags, point);
}

void CSplineView::ParamDisplay(vector<CPoint> & nodes, CDC *pDC)
{
	HDC hDC = pDC->m_hDC;
	
	CParamSolver *solver = new CParamSolver;
	vector<double> t;
	vector<vector<double> > xcoef;
	vector<vector<double> > ycoef;
	solver->Create(nodes);
	switch(m_ParamMode)
	{
	case MODE_UNI:
		solver->Uniform();
		break;
	case MODE_CL:
		solver->ChordLength();
		break;
	case MODE_SCL:
		solver->SqrtChordLength();
		break;
	}
	solver->Solve();
	solver->ParamNode(t);
	solver->Result(xcoef, ycoef);

	// draw spline curve
	for (int i = 0; i < nodes.size() - 1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double s = t[i], h = (t[i + 1] - t[i])/N;
			s += j*h;
			int x = nodes[i].x + (s - t[i])*
				(xcoef[i][2] + (s - t[i])*
				(xcoef[i][1] + (s - t[i])*xcoef[i][0]));
			int y = nodes[i].y + (s - t[i])*
				(ycoef[i][2] + (s - t[i])*
				(ycoef[i][1] + (s - t[i])*ycoef[i][0]));
			pDC->MoveTo(x, y);
			s += h;
			x = nodes[i].x + (s - t[i])*
				(xcoef[i][2] + (s - t[i])*
				(xcoef[i][1] + (s - t[i])*xcoef[i][0]));
			y = nodes[i].y + (s - t[i])*
				(ycoef[i][2] + (s - t[i])*
				(ycoef[i][1] + (s - t[i])*ycoef[i][0]));
			pDC->LineTo(x, y);
		}
	}

	delete solver;
	solver = nullptr;
}

void CSplineView::OnUniform() 
{
	// TODO: Add your command handler code here
	
	m_ParamMode = MODE_UNI;
	GetDocument()->nodes.clear();
	Invalidate();
}

void CSplineView::OnChordLength() 
{
	// TODO: Add your command handler code here
	
	m_ParamMode = MODE_CL;
	GetDocument()->nodes.clear();
	Invalidate();
}

void CSplineView::OnSqrtChordLength() 
{
	// TODO: Add your command handler code here
	
	m_ParamMode = MODE_SCL;
	GetDocument()->nodes.clear();
	Invalidate();
}