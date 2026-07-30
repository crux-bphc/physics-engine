#pragma once
#include <functional>
namespace euler {
    using Function = std::function<double(double, double)>;

    class EqnSolver {
	private:
	    double x0, y0, x, h, xn, yn;
	    const Function func;
	public:
	    EqnSolver(double x0, double y0, double x, double h, const Function func):
		x0(x0), y0(y0), x(x), h(h), func(func), xn(x0), yn(y0){};
	    double solve();
 
    };
}
