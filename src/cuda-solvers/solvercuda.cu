#include <iostream>
#include <solvers/rk_solver_cuda.cuh>

namespace cuda_solvers {
    Solver::Solver(float x0, float y0, float x, float h, float(*func)(float, float)) : x0(x0), y0(y0), x(x), h(h),  xn(x0), func(func), yn(y0){};
}

