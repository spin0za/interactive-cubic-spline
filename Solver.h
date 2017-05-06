#ifndef SOLVER
#define SOLVER

#include <vector>
using namespace std;

class CSolver
{
public:
	CSolver();
	virtual ~CSolver();

	void Create(vector<CPoint> &);
	void Rank();
	void Solve();
	void Result(vector<CPoint> &, vector<vector<double> > &);

protected:
	vector<CPoint> m_Nodes;
	vector<vector<double> > m_Coef;
};

class CParamSolver : public CSolver
{
public:
	void Create(vector<CPoint> &);
	void Uniform();
	void ChordLength();
	void SqrtChordLength();
	void Solve();
	void ParamNode(vector<double> &);
	void Result(vector<vector<double> > &, vector<vector<double> > &);
	double Distance(CPoint, CPoint);

protected:
	vector<double> m_Param;
	vector<vector<double> > m_xCoef;
	vector<vector<double> > m_yCoef;
};

#endif