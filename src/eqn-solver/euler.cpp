#include <iostream>
#include <eqn-solver/eqn-solver.hpp>

namespace euler {
	
double EulerSolver::solve(){
    while(xn < x){
	yn += h * func(xn, yn);
	xn += h;
    }

   return yn;
}
}
	


	

