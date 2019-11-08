class exRK:
    '''
    This is a general implementation of explicit RK solver of
    a system of differential equations in the interval [0,1].
    
    Inputs:
    n_eqs=number of equations to solve
    
    diffeq=an object with dydt(y,t) method, which is 
           the system of dufferential equations to solve
    
    init_cond= the initial consitions 
    
    N=number of steps (ie fixed stepsize)
    
    RK_method= an object with attributes s (stage), and Butcher a,b,c parameters, 
               which define the method. 
               
        
        
    The solutions (list of \vec{y}_{n}) are stored in self.solution 
    and the steps in self.steps.
               
    Example:
    #define RK4
    class RK4:
        def __init__(self):
            self.s=4
            self.c=[0,0.5,0.5,1]
            self.b=[1/6.,1/3.,1/3.,1/6.]
            self.a=[ [0 for j in range(4)] for i in range(4)]
            self.a[1][0]=0.5
            self.a[2][1]=0.5
            self.a[3][2]=1.

    rk4=RK4()#make an instance of RK4
               
    #define the system to solve
    class diff_eq:
        def __init__(self,n=1):
            self.n_eqs=n #you call this from the solver (instead of passing it as a argument to the solver)
        def dydt(self,y,t):
        return [(-y[0]**2+y[1]**2)*2,(-y[1]**2+y[0]**2)*2]
        
    dydt=diff_eq(2)#make an instance of the system
        
    sol1=exRK(dydt,[1,0.5],50)#initialize the solver
    
    sol1.solve()#solve the system!
    
    '''
    
    def __init__(self,diffeq,init_cond,N,RK_method):
        self.step_number=N
        self.step_size=1./(N-1)#constant step size.
        self.dydt=diffeq#the differential equation to be integrated
        self.number_of_eqs=diffeq.n_eqs#number of equations
        
        self.steps=[0 for i in range(N)]#list of steps, ie t
        
        #initiate list of solutions for every t, ie y^(i)_{n}
        self.solution=[0 for i in range(self.number_of_eqs)]
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i]=[0 for i in range(N)]
            
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i][0]=init_cond[eq_i]#the first step is the initial condition
        
        self.current_step=0#initiate a counter (when this becomes equal to N, the solver terminates)
        
        self.end=False# to be changed to True when self.current_step=N
        
        #get the parameters that define the method
        self.s=RK_method.s
        self.a=RK_method.a
        self.b=RK_method.b
        self.c=RK_method.c
        
        
        self.yn=[0 for i in range(self.number_of_eqs)]#this is initiated to hold current steps
        
        self.k=[0 for i in range(self.number_of_eqs)]#this is initiated to hold all ks
        for eq_i in range(self.number_of_eqs):
            self.k[eq_i]=[0 for i in range(self.s)]
        
        
    # function to calculate the \sum_{i=1}^{current stage-1} a_{current stage,i} \vec{k}_{i}*step_size
    def sum_ak(self,stage):
        ak=[0 for i in range(self.number_of_eqs)]
        
        for eq_i in range(self.number_of_eqs):
            for i in range(stage-1):
                ak[eq_i]+=self.a[stage][i]*self.k[eq_i][i]*self.step_size
        
        return ak
    
    # function to calculate the \sum_{i=1}^{s} b_{i} \vec{k}_{i}*step_size
    def sum_bk(self):
        bk=[0 for i in range(self.number_of_eqs)]
        for eq_i in range(self.number_of_eqs):
            for i in range(self.s):
                bk[eq_i]+=self.b[i]*self.k[eq_i][i]*self.step_size
        return bk

    def next_step(self):
        '''
        Get the next step.
        '''
        if self.current_step>=self.step_number-1:
            self.end=True 
        else:
            self.current_step+=1
            tn=self.current_step*self.step_size
            self.steps[self.current_step]=tn
            
            #define a list which holds previous point (makes the code slower, but more transparent) 
            for eq_i in range(self.number_of_eqs):
                self.yn[eq_i]=self.solution[eq_i][self.current_step-1]
    
            #this is \vec{k}_1.  
            for eq_i in range(self.number_of_eqs):
                self.k[eq_i][0]=self.dydt(self.yn,tn)[eq_i]
            
            #once you have \vec{k}_1, find the others.
            for stage in range(1,self.s):
                #since \sum_{i=1}^{s} a_{stage,i} \vec{k}_{i}*step_size is the same for all 
                #equations in a given stage, call here self.sum_ak
                _ak=self.sum_ak(stage)
                
                #get a d\vec{y}/dt needed for \vec_{k}_{stage}
                _dydt=self.dydt(  [self.yn[_eq]+_ak[_eq] for _eq in range(self.number_of_eqs)] ,
                                tn+self.c[stage]*self.step_size )
                for eq_i in range(self.number_of_eqs):
                    self.k[eq_i][stage]=_dydt[eq_i]
                    
            
            #calculate \sum_{i=1}^{s} b_{i} \vec{k}_{i}*step_size
            _bk=self.sum_bk()
            for eq_i in range(self.number_of_eqs):
                #calculate \vec{y}_{n+1}=\vec{y}_{n}+\sum_{i=1}^{s} b_{i} \vec{k}_{i}*step_size
                self.solution[eq_i][self.current_step]=self.yn[eq_i]+_bk[eq_i]
                
            
                
            
    def solve(self):
        '''
        Run  next_step until self.end becomes True.
        '''
        while not self.end:
            self.next_step()