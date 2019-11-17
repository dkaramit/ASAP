class RKF:
    
    '''
    This is a general implementation of explicit RKF solver of
    a system of differential equations in the interval [0,1].
    
    Inputs:
    n_eqs=number of equations to solve
    
    diffeq=an object with overoaded __call__ method (is behaves as a function) which returns 
           the system of dufferential equations to solve. It also has a self.n_eqs attribute
           equal to the number of the equations to be solved.
           
    init_cond= the initial consitions. 

    
    RK_method= an object with attributes s (stage), and Butcher a,b,b_{\star},c parameters, 
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
    
    def __init__(self,diffeq,init_cond,RK_method,
                      initial_step_size=1e-2,minimum_step_size=1e-5,maximum_step_size=1e-1,
                      maximum_No_steps=50000,absolute_tolerance=1e-2,
                      beta=0.5):
        
        
        self.tiny=1e-20#define a tiny number. Below this, errors are ignored..
        
        #get all inputs
        self.dydt=diffeq
        self.number_of_eqs=diffeq.n_eqs
        self.h0=initial_step_size
        self.hmin=minimum_step_size
        self.hmax=maximum_step_size
        self.max_N=maximum_No_steps
        self.abs_eps=absolute_tolerance
        self.beta=beta
        
        #get the parameters that define the method
        self.s=RK_method.s
        self.p=RK_method.p
        self.a=RK_method.a
        self.b=RK_method.b
        self.bstar=RK_method.bstar
        self.c=RK_method.c
        
        #initialize arrays
        self.steps=[0]*self.max_N #this is faster than using a for 
        self.k=[0 for i in range(self.number_of_eqs)]#this is initiated to hold all ks
        for eq_i in range(self.number_of_eqs):
            self.k[eq_i]=[0 for i in range(self.s)]
        self.solution=[0 for i in range(self.number_of_eqs)]
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i]=[0 for i in range(self.max_N)]
            
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i][0]=init_cond[eq_i]#the first step is the initial condition
            
        self.err_n=[0 for i in range(self.max_N)]

        #declare arrays and parameters you are going to need
        #self.ak=[0]*self.number_of_eqs
        #self.bk=[0]*self.number_of_eqs
        #self.bstark=[0]*self.number_of_eqs
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
        
        
    # function to calculate the \sum_{i=1}^{current stage-1} a_{current stage,i} \vec{k}_{i}*step_size
    def sum_ak(self,stage):
        self.ak=[0]*self.number_of_eqs
        
        for eq_i in range(self.number_of_eqs):
            for i in range(stage-1):
                self.ak[eq_i]+=self.a[stage][i]*self.k[eq_i][i]*self.h
        
        
    
    # function to calculate the \sum_{i=1}^{s} b_{i} \vec{k}_{i}*step_size
    def sum_bk(self):
        self.bk=[0]*self.number_of_eqs
        self.bstark=[0]*self.number_of_eqs
        for eq_i in range(self.number_of_eqs):
            for i in range(self.s):
                self.bk[eq_i]+=self.b[i]*self.k[eq_i][i]*self.h
                self.bstark[eq_i]+=self.bstar[i]*self.k[eq_i][i]*self.h

    
    #adjust h. There are more refined ways to do this, but this is a start.  
    def step_control(self):
        _delta=0
        _r_delta=0
        for eq in range(self.number_of_eqs):
            _delta+= self.abs_delta[eq]**2.
        _delta=_delta**0.5
        
        if _delta<self.tiny:
            _delta=self.abs_eps

        
        if _delta>self.abs_eps :
            self.h=self.beta*self.h0*(self.h0*self.abs_eps/_delta)**(1./self.p)
        else:
            self.h=self.beta*self.h0*(self.abs_eps/_delta)**(1./(self.p +1.) )
            self.err_n[self.current_step]=_delta
            self.h_stop=False
            
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
#             print('end')
        else:
            self.current_step+=1
            
            while True:                
                #this is \vec{k}_1.  
                for eq_i in range(self.number_of_eqs):
                    self.k[eq_i][0]=self.dydt(self.yn,self.tn)[eq_i]

                #once you have \vec{k}_1, find the others.
                for stage in range(1,self.s):
                    #since \sum_{i=1}^{s} a_{stage,i} \vec{k}_{i}*step_size is the same for all 
                    #equations in a given stage, call here self.sum_ak
                    self.sum_ak(stage)
                    #get a d\vec{y}/dt needed for \vec_{k}_{stage}
                    _tmp_sum=[self.yn[i] + self.ak[i] for i in range(self.number_of_eqs) ]
                    _dydt=self.dydt( _tmp_sum ,self.tn+self.c[stage]*self.h )
                    for eq_i in range(self.number_of_eqs):
                        self.k[eq_i][stage]=_dydt[eq_i]


                #calculate \sum_{i=1}^{s} b_{i} \vec{k}_{i}*step_size
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
            self.steps[self.current_step]=self.tn
            

            
            
        
                
            
    def solve(self):
        '''
        Run  next_step until self.end becomes True.
        '''
        while not self.end:
            self.next_step()
            
#             print(self.tn)
        
        
        self.t=self.steps[:self.current_step+1]
        
        self.deltas=self.err_n[:self.current_step+1]
        self.y=[0 for i in range(self.number_of_eqs)]
        for eq_i in range(self.number_of_eqs):
            self.y[eq_i]=[0 for i in range(self.current_step+1)]
        
        for eq in range(self.number_of_eqs):
            for step in range(self.current_step+1):
                self.y[eq][step]=self.solution[eq][step]

        