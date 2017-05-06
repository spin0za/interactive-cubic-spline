#include "StdAfx.h"
#include "Solver.h"
#include <math.h>

CSolver::CSolver()
{
}

CSolver::~CSolver()
{
}

void CSolver::Create(vector<CPoint> & nodes)
{
	m_Nodes = nodes;
	m_Coef.resize(m_Nodes.size() - 1);
	for (int i = 0; i < m_Coef.size(); i++)
	{
		m_Coef[i].resize(3);
	}
}

void CSolver::Rank()
{
	for (int i = 0; i < m_Nodes.size(); i++)
	{
		for (int j = m_Nodes.size() - 1; j > i; j--)
		{
			if (m_Nodes[j].x < m_Nodes[j - 1].x)
			{
				int temp;
				temp = m_Nodes[j].x;
				m_Nodes[j].x = m_Nodes[j - 1].x;
				m_Nodes[j - 1].x = temp;
			}
		}
	}
}

void CSolver::Solve()
{
	int n = m_Nodes.size() - 1;
	vector<double> h, u, b, v, z;
	h.resize(n); b.resize(n);
	u.resize(n + 1); v.resize(n + 1); z.resize(n + 1);

	for (int i = 0; i < n; i++)
	{
		h[i] = m_Nodes[i + 1].x - m_Nodes[i].x;
		b[i] = 6*(m_Nodes[i + 1].y - m_Nodes[i].y)/h[i];
	}

	u[1] = 2*(h[0] + h[1]);
	v[1] = b[1] - b[0];

	for (int i = 2; i < n; i++)
	{
		u[i] = 2*(h[i] + h[i - 1]) - h[i - 1]*h[i - 1]/u[i - 1];
		v[i] = b[i] - b[i - 1] - h[i - 1]*v[i - 1]/u[i - 1];
	}

	z[n] = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		z[i] = (v[i] - h[i]*z[i + 1])/u[i];
	}
	z[0] = 0;

	for (int i = 0; i < n; i++)
	{
		m_Coef[i][0] = (z[i + 1] - z[i])/(6*h[i]);
		m_Coef[i][1] = z[i]/2;
		m_Coef[i][2] = -h[i]*z[i + 1]/6 - h[i]*z[i]/3 + (m_Nodes[i + 1].y - m_Nodes[i].y)/h[i];
	}
}

void CSolver::Result(vector<CPoint> & nodes, vector<vector<double> > & coef)
{
	coef = m_Coef;
	nodes = m_Nodes;
}

void CParamSolver::Create(vector<CPoint> & nodes)
{
	m_Nodes = nodes;
	m_xCoef.resize(m_Nodes.size() - 1);
	for (int i = 0; i < m_xCoef.size(); i++)
	{
		m_xCoef[i].resize(3);
	}
	m_yCoef.resize(m_Nodes.size() - 1);
	for (int i = 0; i < m_yCoef.size(); i++)
	{
		m_yCoef[i].resize(3);
	}
	m_Param.resize(m_Nodes.size());
}

void CParamSolver::Uniform()
{
	for (int i = 0; i < m_Nodes.size(); i++)
	{
		m_Param[i] = i*1.0/m_Nodes.size();
	}
}

void CParamSolver::ChordLength()
{
	double CumuLength = 0;
	vector<double> ChordLength;
	for (int i = 0; i < m_Nodes.size() - 1; i++)
	{
		ChordLength.push_back(Distance(m_Nodes[i], m_Nodes[i + 1]));
		CumuLength += ChordLength.back();
	}
	m_Param[0] = 0;
	for (int i = 1; i < m_Nodes.size(); i++)
	{
		m_Param[i] = m_Param[i - 1] + ChordLength[i - 1]/CumuLength;
	}
}

void CParamSolver::SqrtChordLength()
{
	double CumuSqrtLength = 0;
	vector<double> SqrtChordLength;
	for (int i = 0; i < m_Nodes.size() - 1; i++)
	{
		SqrtChordLength.push_back(sqrt(Distance(m_Nodes[i], m_Nodes[i + 1])));
		CumuSqrtLength += SqrtChordLength.back();
	}
	m_Param[0] = 0;
	for (int i = 1; i < m_Nodes.size(); i++)
	{
		m_Param[i] = m_Param[i - 1] + SqrtChordLength[i - 1]/CumuSqrtLength;
	}
}

void CParamSolver::Solve()
{
	int n = m_Nodes.size() - 1;
	vector<double> h, u, b, v, z;
	h.resize(n); b.resize(n);
	u.resize(n + 1); v.resize(n + 1); z.resize(n + 1);

	// x dimension
	for (int i = 0; i < n; i++)
	{
		h[i] = m_Param[i + 1] - m_Param[i];
		b[i] = 6*(m_Nodes[i + 1].x - m_Nodes[i].x)/h[i];
	}
	
	u[1] = 2*(h[0] + h[1]);
	v[1] = b[1] - b[0];
	
	for (int i = 2; i < n; i++)
	{
		u[i] = 2*(h[i] + h[i - 1]) - h[i - 1]*h[i - 1]/u[i - 1];
		v[i] = b[i] - b[i - 1] - h[i - 1]*v[i - 1]/u[i - 1];
	}
	
	z[n] = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		z[i] = (v[i] - h[i]*z[i + 1])/u[i];
	}
	z[0] = 0;
	
	for (int i = 0; i < n; i++)
	{
		m_xCoef[i][0] = (z[i + 1] - z[i])/(6*h[i]);
		m_xCoef[i][1] = z[i]/2;
		m_xCoef[i][2] = -h[i]*z[i + 1]/6 - h[i]*z[i]/3 + (m_Nodes[i + 1].x- m_Nodes[i].x)/h[i];
	}

	// repeat for y dimension
	for (int i = 0; i < n; i++)
	{
		h[i] = m_Param[i + 1] - m_Param[i];
		b[i] = 6*(m_Nodes[i + 1].y - m_Nodes[i].y)/h[i];
	}
	
	u[1] = 2*(h[0] + h[1]);
	v[1] = b[1] - b[0];
	
	for (int i = 2; i < n; i++)
	{
		u[i] = 2*(h[i] + h[i - 1]) - h[i - 1]*h[i - 1]/u[i - 1];
		v[i] = b[i] - b[i - 1] - h[i - 1]*v[i - 1]/u[i - 1];
	}
	
	z[n] = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		z[i] = (v[i] - h[i]*z[i + 1])/u[i];
	}
	z[0] = 0;
	
	for (int i = 0; i < n; i++)
	{
		m_yCoef[i][0] = (z[i + 1] - z[i])/(6*h[i]);
		m_yCoef[i][1] = z[i]/2;
		m_yCoef[i][2] = -h[i]*z[i + 1]/6 - h[i]*z[i]/3 + (m_Nodes[i + 1].y - m_Nodes[i].y)/h[i];
	}
}

void CParamSolver::ParamNode(vector<double> & param)
{
	param = m_Param;
}

void CParamSolver::Result(vector<vector<double> > & xcoef, vector<vector<double> > & ycoef)
{
	xcoef = m_xCoef;
	ycoef = m_yCoef;
}

double CParamSolver::Distance(CPoint p1, CPoint p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
}