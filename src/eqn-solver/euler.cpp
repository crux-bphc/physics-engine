#include <iostream>
#include <eqn-solver/eqn-solver.hpp>

namespace euler {
	
double EulerSolver::solve(){
	    
    while(xn < x){
	xn += h;
	yn += h * func(xn, yn);
    }

   return yn;
}
}
	


	

