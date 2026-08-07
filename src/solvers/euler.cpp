#include <iostream>
#include <solvers/rk_solver.hpp> 


namespace solvers {
namespace euler {
	
double EulerSolver::solve(){
    while(xn < x){
	yn += h * func(xn, yn);
	xn += h;
    }

   return yn;
}
}
}	


	

