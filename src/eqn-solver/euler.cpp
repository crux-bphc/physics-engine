#include <iostream>
#include <solvers/rksolver.hpp> 


namespace solver {
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


	

