#pragma once
#include <functional>

namespace solvers {
using Function = std::function<float(float, float)>;
class Solver {
    public:
	Solver(float x0, float y0, float x, float h, const Function func);
	float x0, y0, x, h, xn, yn;
	virtual float solve() = 0;
	const Function func;

};

namespace euler { //basically rk2
class EulerSolver : public Solver {
    public:
	using Solver::Solver;	
	float solve() override;

};
}

namespace rk4 {
class RK4Solver : public Solver {
    public:
	using Solver::Solver;	
	float solve() override;

};
}
}

