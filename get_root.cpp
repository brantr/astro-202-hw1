#include <gsl/gsl_roots.h>
#include <gsl/gsl_multiroots.h>

#include "get_root.h"
double get_root( double (*f)(double, void *), double x_lo_in, double x_hi_in)
{
	gsl_root_fsolver *grsolve;
	const gsl_root_fsolver_type *grsolve_T;

	//set the root solver type and allocate its memory
	grsolve_T = gsl_root_fsolver_brent;
	grsolve   = gsl_root_fsolver_alloc(grsolve_T);

	gsl_function func;

	int    status;
	int    iter = 0;
	int    max_iter = 100;
	double x_lo = x_lo_in;
	double x_hi = x_hi_in;
	double r = (x_hi-x_lo)/2.0;
	double answer;
	double fp;
	double tol = 1.0e-15;

	func.function = f;
	func.params   = &fp;

	gsl_root_fsolver_set(grsolve, &func, x_lo, x_hi);
	do{
		iter++;
		status = gsl_root_fsolver_iterate(grsolve);
		r = gsl_root_fsolver_root(grsolve);
		x_lo = gsl_root_fsolver_x_lower(grsolve);
		x_hi = gsl_root_fsolver_x_upper(grsolve);
		status = gsl_root_test_interval(x_lo,x_hi,0,tol);
		if(status==GSL_SUCCESS)
			answer = r;
	}
	while(status==GSL_CONTINUE && iter<max_iter);
	if(iter==max_iter)
		printf("Something went wrong!\n");

	gsl_root_fsolver_free(grsolve);

	return r;
}