#include <iostream>
#include <solvers/rk_solver.hpp>

namespace solvers {
namespace rk4{
	
float RK4Solver::solve(){
    while(xn < x){
	float k1 = func(xn, yn);
	float k2 = func(xn + (h/2), (yn + ((h/2) * k1)));
	float k3 = func(xn + (h/2), (yn + ((h/2) * k2)));
	float k4 = func(xn + h, yn + (h * k3));
	yn += ((h/6)*(k1 + (2*k2) + (2*k3) + k4));
	xn += h;
    }

   return yn;
}
}
}
