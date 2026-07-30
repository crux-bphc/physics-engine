#pragma once

namespace euler {
    class EqnSolver {
	private:
	    double x0, y0, x, h, xn, yn;
	    double(*func)(double, double);
	public:
	    EqnSolver(double x0, double y0, double x, double h, double(*func)(double,double)):
		x0(x0), y0(y0), x(x), h(h), func(func), xn(x0), yn(y0){};
	    double solve();
 
    };
}
