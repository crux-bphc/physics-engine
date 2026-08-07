#pragma once
#include <functional>

namespace solvers {
using Function = std::function<double(double, double)>;
class Solver {
    public:
	Solver(double x0, double y0, double x, double h, const Function func);
	double x0, y0, x, h, xn, yn;
	virtual double solve() = 0;
	const Function func;

};

namespace euler { //basically rk2
class EulerSolver : public Solver {
    public:
	using Solver::Solver;	
	double solve() override;

};
}

namespace rk4 {
class RK4Solver : public Solver {
    public:
	using Solver::Solver;	
	double solve() override;

};
}
}

