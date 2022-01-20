import get_root as gr
import numpy as np
from scipy.integrate import quad


#Part A
#integral of B_nu
def B_x_integrand(ln_x):
  x = np.exp(ln_x)
  tol = 1.0e-15
  B_denom = np.exp(x)-1  #denominator of the planck function
  exp_minus_1 = x + 0.5*(x**2) + (x**3)/6. #taylor expansion of denominator

  if( (np.fabs(B_denom - exp_minus_1) < tol) & (x<1)):
    Bx = (x**3)/exp_minus_1;
  else:
    Bx = (x**3)/B_denom

  return x * Bx  # x * dB / dlnx  * dlnx = dB/dx * dx

#Part B
#equation for finding max of dBdnu
def root_dBdnu(x):
  return x-3*(1-np.exp(-1*x))

#equation for finding max of dBdlambda
def root_dBdlambda(y):
  return y-5*(1-np.exp(-1*y));

#Part C
#equation for finding max of d2BdnudT
def root_d2BdnudT(z):
  return np.exp(z)*(z-4)+z+4;


def main():

    print("***** Question 2, Part A *****")

    #find the integral of B_nu dnu
    Bi, _ = quad(B_x_integrand,-32, 32)
    ans = np.pi**4 / 15.
    print('Normalized integral of B_nu dnu = %e.' % Bi)
    print('Fractional error in integral = %e.' % float((Bi-ans)/ans))

    print("***** Question 2, Part B *****")

    #find the maximum of dBdnu
    x_dBdnu = gr.get_root(root_dBdnu,3.)
    print('Maximum of dBdnu occurs at x = %e.' % x_dBdnu)

    #find the maximum of dBdlambda
    y_dBdlambda = gr.get_root(root_dBdlambda,3.)
    print('Maximum of dBdlambda occurs at y = %e.' % y_dBdlambda)

    print("***** Question 2, Part C *****")

    #find the maximum of d^2B/dnudT
    x_d2BdnudT = gr.get_root(root_d2BdnudT,4.)
    print('Maximum of d2BdnudT occurs at x = %e.' % x_d2BdnudT)


#execute the program
if __name__=='__main__':
    main()