class modelFunc:
    '''
    This is how the function should look like.
    The key point is to have way to update the parameters w.
    '''
    def __init__(self,func,dfdw_i,dimensions,w0):
        '''
        func: the function that depends on parameters w
        dfdw_i: the derivative wrt w_i (see self.derivative_w to see how it should be defined).
        dimensions:list  [inpunt_dim,output_dim]
        w0: initial values of w
        '''
    
        self.f=func
        self.dfdw_i=dfdw_i
        
        self.w=w0
        self.dim=len(w0)
        
        self.dimensions=dimensions
        
        self.signal=[0 for i in range(dimensions[1])] #will store the output of self.f
        self.dsdw=[0 for i in range(dimensions[1])] #will store the output of self.dfdw_i
        
        #will store the input, to avoid passing the input every time we callthe function or its derivetive
        self.input=[0 for i in range(dimensions[1])]
    
    def __call__(self):
        self.f(self)
    
    def setInput(self,x):
        '''set the input'''
        self.input=x
    
    def derivative_w(self,i):
        self.dfdw_i(self,i)



class lossFunc:
    '''
    This is how the loss function should look like.
    We use a class, in order to encapsulate the gradient within the same object.
    '''
    def __init__(self,Q_i,dQds_i,model):
        '''
        Q: the loss function in one domension. It will be averaged over all dimensions in __call__
        dQds_i: the derivative of the loss function wrt to s_i (the i^th signal)
        
        model: instance of modelFunc 
        '''
        self.Q_i=Q_i
        self.dQds_i=dQds_i
        self.model=model
        
        
        self.dim=len(self.model.w)#dimension of w
        
        self.N=model.dimensions[1]#dimension of model.signal
            
            
        self.dQdw=0 #this will hold dQdw
        
        
    def __call__(self,target):
        sum_Q=0;
        
                
        for r in range(self.N):
            sum_Q+=self.Q_i(self.model,r,target[r])
    
        sum_Q=sum_Q/(float(self.N))

        return sum_Q
    
    def grad(self,i,target):
        self.model.derivative_w(i)
        self.dQdw=0
        
        signal=self.model.signal
        for dim in range(self.dim):
            for r in range(self.N):
                tmp_dQds=self.dQds_i(self.model,r,target[r])/(float(self.N))
                self.dQdw += tmp_dQds*self.model.dsdw[r]


class GradientDescent:
    
    def __init__(self,strategy):
            self.strategy=strategy
    
    def run(self,abs_tol=1e-5, rel_tol=1e-3, step_break=100,max_step=5000):
        '''        
        abs_tol, rel_tol, step_break: stop when _check<1 (_check is what update should return) 
        for step_break consecutive steps
        
        max_step: maximum number of steps
        '''
        _s=0
        count_steps=1
        while count_steps<=max_step:
            _check=self.strategy.update(abs_tol, rel_tol)
            
            count_steps+=1             
                
            
            if _check<1:
                _s+=1
            else:
                _s=0
            
            if _s>step_break:
                break

        return self.strategy.Q.model.w[:]