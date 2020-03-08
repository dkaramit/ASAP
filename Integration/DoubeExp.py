from numpy import tanh,sinh,cosh,pi,abs


class DoubleExp:
    def g(self,t):
        return tanh( pi/2. * sinh(t)  )
    def dgdt(self,t):
        return pi/2. *cosh(t)/cosh( pi/2. * sinh(t)  )**2.
    
    
    def F(self,t):
        #this will be used to determine the error
        return self.func( self.g(t) )*self.dgdt(t)

    def d2Fdt(self,t,_h=1e-8):
        '''
        This will give the second derivatives we need for the error estimation.
        For the moment take derivatives numerically. 
        Later I will do the derivatives of g analytically, but for the moment should be fine.
        '''
        return (self.F(t+_h )- 2 * self.F(t ) +  self.F(t -_h ))/(2.*_h**2.)
        
        
        
    def __init__(self,func,_exp=1,_exp_max=15,rtol=1e-5,atol=1e-5,p=10,Nmax=1000):
        '''
        func: function to be integrated in the interval [-1,1].
        exp: initial value of h=2^-exp
        exp_min: the minimum exp, with hmin= 2^{-exp_max} 
        p: precision.
        
        Nmax=maximum number of evaluations
        
        Note that x_{-j}=-x_j and w_{-j}=-w_j .
        '''
        self.func=func
        
        self._exp=_exp
        self._exp_max=_exp_max
        
        self.h=2**-_exp
        self.hmin=2**-_exp_max
        
        self.rtol=rtol
        self.atol=atol
        self.eps=10**(-p)
        
        #initialize N
        self.N=0
        
        
        #eval will tell us if we have already evaluated the integral for given N and h (no need to sum thingswe already have)
        self.eval=True
        self.h_stop=False
        
        
        #initialize the integral and the error. 
        #As you update h and N, you need to add to the sum only new values produced
        #Also, since h changes, multipy by h at the end of the evaluation.
        self.integral=self.func( self.g(0) ) *self.dgdt(0)
        self.err=self.d2Fdt(0)
        

    def error(self,_h=1e-8):
        '''find the absolute error take derivatives numerically. 
        Later I will do the derivatives of g analytically, but for the moment should be fine.
        '''
        pass
    
    def N_start(self):
        '''
        Find an appropriate N to start.
        As you update h, just update N->N*2 (later we may use something better) 
        '''
        
        #start from this. 
        tmp_N=1
        while True:
            #remember that x_j=-x_{-j}, w_j = w_{-j}
            _x=self.g(self.h*tmp_N)
            _w=self.dgdt(self.h*tmp_N)
            _f1=_w*self.func(_x) 
            _f2= _w*self.func(-_x)
            
            if abs(_f1)<self.eps and abs(_f2 )<self.eps :
                self.eval=False
                break
            else:
                
                self.integral+=_f1+_f2
                self.err+=self.d2Fdt( tmp_N*self.h)
                                
                self.N=tmp_N
                tmp_N+=1
        

        
    def evaluate(self):
        '''
        Evaluate the integral for given h and N.
        Also evaluate the error.
        
        Note for later: since we update h->h/2, we just need to update the sum including only the new
        addition we make. That is, you only calculate for odd j! 
        '''
#         if self.eval:
#             for j in range(1,self.N,2):
        j=1
        while self.eval:
            _x=self.g(self.h*j)
            _w=self.dgdt(self.h*j)

            self.integral+=_w*(self.func(_x) + self.func(-_x))
            self.err+=self.d2Fdt( j*self.h)+self.d2Fdt( -j*self.h)
            j+=2    
            if j>self.N-2:
                self.eval=False
                break

            
            
    def h_control(self):
        '''
        Determines if  the error is acceptable. If not, decrese h until it is (or hmin is found).
        '''
        abs_err=abs(self.err*self.h*(self.h/(2*pi))**2.)
        
        _sc=self.atol + self.rtol*abs(self.integral)
        
        if abs_err/_sc <1 :
            self.h_stop=True
        else:
            if self.h<self.hmin:
                self.h_stop=True
            else:
                self.h=self.h/2
                self.N=self.N*2
                self.eval=True



    def integrate(self):
        if self.N==0:
            self.N_start()
        
        while self.h_stop==False:
            self.h_control()
            self.evaluate()
            
        self.eval=False
        return (self.integral*self.h , abs(self.err*self.h*(self.h/(2*pi))**2.)  )
    


            


if __name__ == "__main__":
    def F(x):
        return 1/((1+x)**0.5 +(1-x)**0.5 +2  )


    DE=DoubleExp(func=F,_exp=5,p=8,rtol=1e-8,atol=1e-8)

    print(
        'result: {0[0]} \nerror: {0[1]} \nexact: {1}'.format(
        DE.integrate(),4*2**0.5-pi-2)
        )
