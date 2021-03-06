from Solver.LU_dec.LUP import LUP
from Solver.LU_dec.Solve_LU import Solve_LU



def dot(J,k,n):
#     define a dot product. this is the same as numpy's dot 
    Jk=[0 for i in range(n)]
    for i in range(n):
        for j in range(n):
            Jk[i]+=J[i][j]*k[j]
    return Jk

class Ros:
    
    '''
    This is a general implementation of a Rosenbrock method solver of
    a system of differential equations in the interval [0,1].
    
    Inputs:
    n_eqs=number of equations to solve
    
    diffeq=an object with overoaded __call__ method (it behaves as a function) which returns 
           the system of dufferential equations to solve. It also has a self.n_eqs attribute
           equal to the number of the equations to be solved.
           
    init_cond= the initial consitions. 
    
    Jacobian=an object with overoaded __call__ method that gives the jacobian of the system,
    and the derivatives of \vec{f} over time.
    
    RK_method= an object with attributes s (stage), and Butcher a,b,b_{\star},c, and the \gamma's, 
               which define the method. 
               
    initial_step_size: Initial step size. Since it is adaptive, we just need to start somewhere.
    This should be of moderate size, and let the algorithm work its magic.
    
    minimum_step_size: The minimum allowed stepsize. This should be something small 
    (of the order of the error we aim)
    
    maximum_step_size: The maximum allowd stepsize. This should be larger that the minimum one.
    
    maximum_No_steps: The maximum number of steps to take. This should be here in order to avoid 
    filling up the RAM. Alternatively, you could print directly to a file, but it would make the code 
    much slower. 
    
    
    absolute_tolerance: Absolute error we aim for.
    
    beta: parameter (with value around 1) that parametrizes the agressiveness of the adaptive process.  
    
    '''
    
    def __init__(self,diffeq,init_cond,RK_method,Jacobian,
                      initial_step_size=1e-3,minimum_step_size=1e-5,maximum_step_size=1e-2,
                      maximum_No_steps=50000,absolute_tolerance=1e-5,relative_tolerance=1e-5,
                      beta=0.85,fac_max=2.):
        
        
        self.tiny=1e-20#define a tiny number. Below this, errors are ignored..
        
        #get all inputs
        self.dydt=diffeq
        self.number_of_eqs=diffeq.n_eqs
        self.h0=initial_step_size
        self.hmin=minimum_step_size
        self.hmax=maximum_step_size
        self.max_N=maximum_No_steps
        self.abs_tol=absolute_tolerance
        self.rel_tol=relative_tolerance
        self.fac_max=fac_max
        self.beta=beta
        
        
        #get the parameters that define the method
        self.s=RK_method.s
        self.p=RK_method.p
        self.a=RK_method.a
        self.b=RK_method.b
        self.bstar=RK_method.bstar
        self.c=RK_method.c
        self.gamma=RK_method.gamma
        self.g=RK_method.g
        
        #initialize the jacobian
        self.Jac=Jacobian
        
        #initialize arrays
        self.steps=[0]*self.max_N #this is faster that using a for 
        self.k=[0 for i in range(self.number_of_eqs)]#this is initiated to hold all ks 
        
        for eq_i in range(self.number_of_eqs):
            self.k[eq_i]=[0 for i in range(self.s)]
        
        #define the unit matrix
        self.Unit=[[1 if i==j else 0  for j in range(self.number_of_eqs)] for i in range(self.number_of_eqs)]
        
            
            
        self.solution=[0 for i in range(self.number_of_eqs)]
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i]=[0 for i in range(self.max_N)]
            
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i][0]=init_cond[eq_i]#the first step is the initial condition
            
        self.err_n=[0 for i in range(self.max_N)]

        #declare arrays and parameters you are going to need
        self.ynext=[0]*self.number_of_eqs
        self.ynext_star=[0]*self.number_of_eqs
        self.yn=[0]*self.number_of_eqs
        self.abs_delta=[0]*self.number_of_eqs
        
        
        #initialize a counter
        self.current_step=0
        
        self.end=False# This will be chang to True when the end is reached
        

        

        
        for eq in range(self.number_of_eqs):
            self.yn[eq]=init_cond[eq]
            self.ynext[eq]=0
            self.ynext_star[eq]=0
            #self.abs_delta[eq]=0
        
        self.h_stop=False
        self.h=self.h0
        self.tn=0
        
        
    # function to calculate the \sum_{i=1}^{current stage-1} a_{current stage,i} \vec{k}_{i}
    def sum_ak(self,stage):
        self.ak=[0]*self.number_of_eqs
        for eq_i in range(self.number_of_eqs):
            for i in range(stage-1):
                self.ak[eq_i]+=self.a[stage][i]*self.k[eq_i][i]
        
    # function to calculate the \sum_{i=1}^{current stage-1} \gamma_{current stage,i} \vec{k}_{i}
    def sum_gk(self,stage):
        self.gk=[0]*self.number_of_eqs
        for eq_i in range(self.number_of_eqs):
            for i in range(stage-1):
                self.gk[eq_i]+=self.g[stage][i]*self.k[eq_i][i]    

    # function to calculate the \sum_{i=1}^{s} b_{i} \vec{k}_{i}
    def sum_bk(self):
        self.bk=[0]*self.number_of_eqs
        self.bstark=[0]*self.number_of_eqs
        for eq_i in range(self.number_of_eqs):
            for i in range(self.s):
                self.bk[eq_i]+=self.b[i]*self.k[eq_i][i]
                self.bstark[eq_i]+=self.bstar[i]*self.k[eq_i][i]
                
    def calc_k(self):
        #get the jacobian
        J=[ [0 for j in range(self.number_of_eqs)] for i in range(self.number_of_eqs)]
        dfdt=[0 for j in range(self.number_of_eqs)]
        self.Jac(self.yn,self.tn,J,dfdt)
        #get I - h \gamma J
        _coeff=[[0  for j in range(self.number_of_eqs)] for i in range(self.number_of_eqs)]
        for i in range(self.number_of_eqs):
                for j in range(self.number_of_eqs):
                    _coeff[i][j]+=self.Unit[i][j]-self.h*self.gamma*J[i][j]
        #find LU decomposition
        L,U,P=LUP(_coeff,self.number_of_eqs)
        
        
        #prepare input for the first stage k
        _dydth=self.dydt( self.yn ,self.tn )
        _rhs=[_dydth[i]*self.h+self.gamma*self.h**2*dfdt[i] for i in  range(self.number_of_eqs)]
        #get the solution
        
        _lusol=Solve_LU(L,U,P,_rhs,self.number_of_eqs)
        
        for eq_i in range(self.number_of_eqs):
            #store the solution to \vec{k}_0
            self.k[eq_i][0]=_lusol[eq_i]

        
        #once you have \vec{k}_1, find the others.
        for stage in range(1,self.s):
            #since \sum_{i=1}^{s} a_{stage,i} \vec{k}_{i}*step_size is the same for all 
            #equations in a given stage, call here self.sum_ak
            self.sum_ak(stage)
            self.sum_gk(stage)
            #prepere the right hand side for \vec{k}_i
            _f1=[self.yn[i] + self.ak[i] for i in range(self.number_of_eqs) ]
            #I need \sum_{j=1}^{stage-1} \gamma_{stage,j}
            tmp_sum_g=0
            for j in range(self.s-1):
                tmp_sum_g+=self.g[stage][j]
            #---get the terms in the left hand side
            _dydt1=self.dydt( _f1  ,self.tn+self.c[stage]*self.h )
            _dydt1=[ i*self.h for i in  _dydt1]#first term in the rhs
            #----#
            _dydt2=[self.h**2*(self.gamma+tmp_sum_g)*dfdt[i]   for i in range(self.number_of_eqs) ]#second term
            _dydt3=dot(J,self.gk,self.number_of_eqs)
            _dydt3=[ i*self.h for i in  _dydt3]#third term
            #add all terms together
            _rhs=[_dydt1[i]+_dydt2[i]+_dydt3[i]  for i in range(self.number_of_eqs) ]
            #solve the system
            _lusol=Solve_LU(L,U,P,_rhs,self.number_of_eqs)

            for eq_i in range(self.number_of_eqs):
                self.k[eq_i][stage]=_lusol[eq_i]


        
    
    #adjust h. There are more refined ways to do this, but this is a start.  
    #adjust h. There are more refined ways to do this, but this is a start.  
    def step_control(self):
        _delta=0
        for eq in range(self.number_of_eqs):
            scale=self.abs_tol+self.rel_tol*max(abs( self.ynext[eq] ), abs( self.ynext_star[eq] ))
            _delta+= (self.abs_delta[eq]/scale)**2.
        
        _delta=(1./self.number_of_eqs*_delta)**0.5
        
        if(_delta<1):
            h_stop=False 
            self.err_n[self.current_step]=_delta 
        
        fac=min( (1/_delta) ** 1./(self.p+1)  , self.fac_max );
            
        self.h= self.beta*self.h0*fac 
        
        if self.h>self.hmax:
            self.h=self.hmax
            
        if self.h<self.hmin:
            self.h=self.hmin
        
        #if tn+h becomes larger than 1, set h=1-tn
        if self.tn+self.h>1:
            self.h=1-self.tn
                    
        self.h0=self.h #h0 is redundant, but use it for clarity
                
    def next_step(self):
        '''
        Get the next step.
        '''
        if not (self.tn<1. and self.current_step<self.max_N-1):
            self.end=True 
        else:
            self.current_step+=1
            
            while True:
                
                #this is \vec{k}_1.  
                self.calc_k()
                
                #calculate \sum_{i=1}^{s} b_{i} \vec{k}_{i}
                self.sum_bk()
                #calculate y_{n+1} and y_{n+1}^{\star}
                for eq in range(self.number_of_eqs):

                    self.ynext[eq]=self.yn[eq]+ self.bk[eq]
                    
                    self.ynext_star[eq]=self.yn[eq]+ self.bstark[eq]
                    
                    self.abs_delta[eq]=self.ynext[eq]-self.ynext_star[eq]

                    
                    
                self.step_control()
                if not self.h_stop:
                    break
            
            for eq in range(self.number_of_eqs):
                    self.yn[eq]=self.ynext[eq]
                    self.solution[eq][self.current_step]=self.ynext[eq]
            
            self.tn+=self.h
            if self.tn>1:
                self.tn=1
    
            self.steps[self.current_step]=self.tn
            

            
            
        
                
            
    def solve(self):
        '''
        Run  next_step until self.end becomes True.
        '''
        while not self.end:
            self.next_step()
        
        
        self.t=self.steps[:self.current_step+1]
        
        self.deltas=self.err_n[:self.current_step+1]
        self.y=[0 for i in range(self.number_of_eqs)]
        
        for eq_i in range(self.number_of_eqs):
            self.y[eq_i]=[0 for i in range(self.current_step+1)]
        
        for eq in range(self.number_of_eqs):
            for step in range(self.current_step+1):
                self.y[eq][step]=self.solution[eq][step]

        