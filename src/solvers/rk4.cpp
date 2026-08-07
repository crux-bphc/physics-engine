#include <iostream>
#include <solvers/rk_solver.hpp>

namespace solvers {
namespace rk4{
	
double RK4Solver::solve(){
    while(xn < x){
	double k1 = func(xn, yn);
	double k2 = func(xn + (h/2), (yn + ((h/2) * k1)));
	double k3 = func(xn + (h/2), (yn + ((h/2) * k2)));
	double k4 = func(xn + h, yn + (h * k3));
	yn += ((h/6)*(k1 + (2*k2) + (2*k3) + k4));
	xn += h;
    }

   return yn;
}
}
}
