#include <iostream>
#include <eqn-solver/eqn-solver.hpp>
#include <cmath>

namespace euler {
	
double EulerSolver::solve(){
    while(xn < x){
	yn += h * func(xn, yn);
	xn += h;
    }

   return yn;
}
}
	


	

