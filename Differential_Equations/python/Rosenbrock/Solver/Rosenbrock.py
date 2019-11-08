from .LU_dec.LUP import LUP
from .LU_dec.Solve_LU import Solve_LU


def dot(J,k,n):
#     define a dot product. this is the same as numpy's dot 
    Jk=[0 for i in range(n)]
    for i in range(n):
        for j in range(n):
            Jk[i]+=J[i][j]*k[j]
    return Jk

class Ros:
    
    '''
    finished. Documentation pending...
    
    '''
    
    def __init__(self,diffeq,init_cond,RK_method,Jacobian,
                      initial_step_size=1e-2,minimum_step_size=1e-5,maximum_step_size=1e-1,
                      maximum_No_steps=50000,relative_tolerance=1e-4,absolute_tolerance=1e-2,
                      beta=1):
        
        
        self.tiny=1e-20#define a tiny number. Below this, errors are ignored..
        
        #get all inputs
        self.dydt=diffeq
        self.number_of_eqs=diffeq.n_eqs
        self.h0=initial_step_size
        self.hmin=minimum_step_size
        self.hmax=maximum_step_size
        self.max_N=maximum_No_steps
        self.abs_eps=absolute_tolerance
        self.rel_eps=relative_tolerance
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
            
        self.err_n=[[0 for i in range(self.max_N)], [0 for i in range(self.max_N)]]

        #declare arrays and parameters you are going to need
        self.ynext=[0]*self.number_of_eqs
        self.ynext_star=[0]*self.number_of_eqs
        self.yn=[0]*self.number_of_eqs
        self.abs_delta=[0]*self.number_of_eqs
        self.rel_delta=[0]*self.number_of_eqs
        
        
        #initialize a counter
        self.current_step=0
        
        self.end=False# This will be chang to True when the end is reached
        

        

        
        for eq in range(self.number_of_eqs):
            self.yn[eq]=init_cond[eq]
            self.ynext[eq]=0
            self.ynext_star[eq]=0
            #self.abs_delta[eq]=0
            #self.rel_delta[eq]=0
        
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
    def step_control(self):
        _delta=0
        _r_delta=0
        for eq in range(self.number_of_eqs):
            _delta+= self.abs_delta[eq]**2.
            _r_delta+= self.rel_delta[eq]**2.
        _delta=_delta**0.5
        _r_delta=_r_delta**0.5
        
        if _r_delta<self.tiny:
            _r_delta=self.rel_eps
        if _delta<self.tiny:
            _delta=self.abs_eps

        
        if _delta>self.abs_eps or _r_delta>self.rel_eps:
            self.h=self.beta*self.h0*(self.abs_eps/_delta)**(1./(self.p+1.))
        else:
            self.h=self.beta*self.h0*(self.abs_eps/_delta)**(1./self.p )
            self.err_n[0][self.current_step]=_delta
            self.err_n[1][self.current_step]=_r_delta
            self.h_stop=False
            
        if self.h>self.hmax:
            self.h=self.hmax
            
        if self.h<self.hmin:
            self.h=self.hmin
        
        
        self.h0=self.h #h0 is redundant, but use it for clarity
                
    def next_step(self):
        '''
        Get the next step.
        '''
        if not (self.tn<1. and self.current_step<self.max_N-1):
            self.end=True 
        else:
            
            while True:
                #define a list which holds previous point (makes the code slower, but more transparent) 
                for eq_i in range(self.number_of_eqs):
                    self.yn[eq_i]=self.solution[eq_i][self.current_step]
                #this is \vec{k}_1.  
                self.calc_k()
                
                #calculate \sum_{i=1}^{s} b_{i} \vec{k}_{i}
                self.sum_bk()
                #calculate y_{n+1} and y_{n+1}^{\star}
                for eq in range(self.number_of_eqs):

                    self.ynext[eq]=self.yn[eq]+ self.bk[eq]
                    
                    self.ynext_star[eq]=self.yn[eq]+ self.bstark[eq]
                    
                    self.abs_delta[eq]=self.ynext[eq]-self.ynext_star[eq]

                    
                    if self.ynext[eq]**2.>self.tiny**2.:
                        self.rel_delta[eq]=(self.ynext[eq]-self.ynext_star[eq])/self.ynext[eq]
                    else:
                        self.rel_delta[eq]=self.abs_delta[eq]
                        
                self.step_control()
                if not self.h_stop:
                    break
            
            for eq in range(self.number_of_eqs):
                    self.yn[eq]=self.ynext[eq]
                    self.solution[eq][self.current_step+1]=self.ynext[eq]
            
            self.tn+=self.h
            if self.tn>1:
                self.tn=1
    
            self.steps[self.current_step]=self.tn
            

            self.current_step+=1
            
        
                
            
    def solve(self):
        '''
        Run  next_step until self.end becomes True.
        '''
        while not self.end:
            self.next_step()
        
        self.t=self.steps[:self.current_step]
        self.deltas=[0,0]
        self.deltas[0]=self.err_n[0][:self.current_step]
        self.deltas[1]=self.err_n[1][:self.current_step]
        self.y=[0 for i in range(self.number_of_eqs)]
        for eq_i in range(self.number_of_eqs):
            self.y[eq_i]=[0 for i in range(self.current_step)]
        
        for eq in range(self.number_of_eqs):
            for step in range(self.current_step):
                self.y[eq][step]=self.solution[eq][step]

        