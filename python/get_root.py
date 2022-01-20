from scipy.optimize import root

#find the root of a function
def get_root(f,x_init,tol=None):

    #find the root x where f==0
    res = root(f,x_init,tol=tol)

    #check to make sure the root was successfully found
    if(res.success==False):
        raise Exception('Error in finding root.','init: %e final: %e' % (x_init,res.x))

    #return the root
    return res.x