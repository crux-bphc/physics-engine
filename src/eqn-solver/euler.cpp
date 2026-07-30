#include <iostream>
#include "eqn-solver.hpp"

namespace euler {
	
double EqnSolver::solve(){
	    
    while(xn < x){
	xn += h;
	yn += h * func(xn, yn);
    }

    return yn;
}

}

	

