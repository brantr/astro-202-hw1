#include <stdio.h>
#include <math.h>
#include "rk_int.h"
#include "get_root.h"


//integrand in df/dln nu
double B_x_integrand(double ln_x, void *params);
double root_dBdnu(double x, void *fp);
double root_dBdlambda(double x, void *fp);
double root_d2BdnudT(double x, void *fp);

int main(int argc, char **argv)
{

  double x_min = log(1.0e-32);
  double x_max = log(1.0e32);
  double dx_init = 0.01*(x_max-x_min);
  double eps = 1.0e-15;

  double fp; //parameter of the integrand, -- not needed
  int    np = 1;

  //do the integral
  double B_int_calc = integrate(B_x_integrand,&fp,np,x_min,x_max,dx_init,eps);
  double answer = pow(M_PI,4)/15.;
  printf("B_int_calc = %15.14e\tanswer = %15.14e\terror = %15.14e\n", B_int_calc, answer, (B_int_calc-answer)/answer);

  double x = get_root(root_dBdnu,0.1,10);
  printf("For Bnu,     x = %15.14e, f(x) = %15.14e\n",x,root_dBdnu(x,&fp));

  double y = get_root(root_dBdlambda,0.1,10);
  printf("For Blambda, y = %15.14e, f(y) = %15.14e\n",y,root_dBdlambda(y,&fp));

  double z = get_root(root_d2BdnudT,0.1,10);
  printf("For dBdT,    z = %15.14e, f(z) = %15.14e\n",z,root_d2BdnudT(z,&fp));
  return 0;
}

double B_x_integrand(double ln_x, void *params)
{
  double x = exp(ln_x);
  double B_denom = exp(x)-1;  //denominator of the planck function
  double tol = 1.0e-15;
  double exp_minus_1 = x + 0.5*pow(x,2) + pow(x,3)/6.;  //taylor expansion of denominator
  double Bx;

  if( fabs(B_denom - exp_minus_1) < tol && x<1)
  {
    Bx = pow(x,3)/exp_minus_1;
  }else{
    Bx = pow(x,3)/B_denom;
  }

  return x * Bx;  // x * dB / dlnx  * dlnx = dB/dx * dx
}

double root_dBdnu(double x, void *fp)
{
  return x-3*(1-exp(-1*x));
}
double root_dBdlambda(double y, void *fp)
{
  return y-5*(1-exp(-1*y));
}
double root_d2BdnudT(double z, void *fp)
{
  return exp(z)*(z-4)+z+4;
}

