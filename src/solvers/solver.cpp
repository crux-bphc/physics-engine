#include <iostream>
#include <solvers/rk_solver.hpp>


namespace solvers {
    Solver::Solver(double x0, double y0, double x, double h, const Function func) : x0(x0), y0(y0), x(x), h(h), func(func), xn(x0), yn(y0){};
}

