#pragma once
#include <functional>
#include <cuda_runtime.h>

namespace cuda_solvers {
class Solver {
    public:
	__host__ __device__ Solver(float x0, float y0, float x, float h, float(*func)(float, float));
	float x0, y0, x, h, xn, yn;
	float (*func)(float, float);

};

namespace euler { //basically rk2
class EulerSolver : public Solver {
    public:
	using Solver::Solver;	
	__host__ __device__ float solve(); 

};
}

namespace rk4 {
class RK4Solver : public Solver {
    public:	
	using Solver::Solver;	
	__host__ __device__ float solve();


};
}
}

