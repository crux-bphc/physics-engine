#include <iostream>
#include <solvers/rk_solver.hpp>


namespace solvers {
    Solver::Solver(float x0, float y0, float x, float h, const Function func) : x0(x0), y0(y0), x(x), h(h), func(func), xn(x0), yn(y0){};
}

