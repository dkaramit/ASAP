class Euler:
    '''
    Euler solver for system of differential equations in the interval [0,1].
    call it as Euler(N,init_cond,diffeq).
    
    N= number of steps to take
    
    init_cond= initial condition, y(0)
    
    diffeq= differential equation instance of an object with attribute dydt(y,t), the
    equation to be solved.
    '''
    
    def __init__(self,diffeq,init_cond,N):
        self.step_number=N
        self.step_size=1./(N-1.)#constant step size.
        self.dydt=diffeq#the differential equation to be integrated

        self.number_of_eqs=diffeq.n_eqs#number of equations. It is an attribute of the system (define the system as an object)
        
        self.steps=[0 for i in range(N)]#list of steps, ie t
        
        #initiate list of solutions for every t, ie y^(i)_{n}
        self.solution=[0 for i in range(self.number_of_eqs)]
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i]=[0 for i in range(N)]
            
        for eq_i in range(self.number_of_eqs):
            self.solution[eq_i][0]=init_cond[eq_i]#the first step is the initial condition
        
        self.current_step=0#initiate a counter (when this becomes equal to N, the solver terminates)
        
        self.end=False# to be changed to True when self.current_step=N
        
        self.y0=[0 for i in range(self.number_of_eqs)]#this is initiated to hold current steps
        
        
    
    def next_step(self):
        '''
        Take the next step.
        for Euler this is:
        y_{n}=y_{n-1}+h*dydt(y_{n-1},t_{n-1})
        '''
        if self.current_step>=self.step_number-1:
            self.end=True 
        else:
            self.current_step+=1
            t0=self.current_step*self.step_size
            self.steps[self.current_step]=t0
            
            
            for eq_i in range(self.number_of_eqs):
                self.y0[eq_i]=self.solution[eq_i][self.current_step-1]
                
            for eq_i in range(self.number_of_eqs):
                self.solution[eq_i][self.current_step]=self.solution[eq_i][self.current_step-1]                 + self.dydt(self.y0,t0)[eq_i]*self.step_size
                
            
    def solve(self):
        '''
        Run  next_step until self.end becomes True.
        '''
        while not self.end:
            self.next_step()



class diff_eq:
    def __init__(self,n=1):
        self.n_eqs=n
        
        
    def __call__(self,y,t):#to avoid passing function as an argument you can just overload the operator "()".
        
        return [(-y[0]**2+y[1]**2)*2*t**0.1,(-y[1]**2+y[0]**2)*2*t**0.1]

    
dydt=diff_eq(2)

in0=[1.2,0.6]
sol2=Euler(N=10000,init_cond=in0,diffeq=dydt)


# In[18]:


sol2.solve()

f1=open('y1_py.dat','w')
f2=open('y2_py.dat','w')
t=open('t_py.dat','w')

for i,tt in enumerate(sol2.steps):
    f1.write(str(sol2.solution[0][i])+'\n')
    f2.write(str(sol2.solution[1][i])+'\n')
    t.write(str(tt)+'\n')
f1.close()    
f2.close()
t.close()