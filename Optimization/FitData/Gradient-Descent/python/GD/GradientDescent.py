# Generic classes for the target and loss functions
class modelBase:
    '''
    This is the base class for the function. The key point is to have way to update the parameters w.
    '''
    def __init__(self,dimensions,w0):
        '''
        func: the function that depends on parameters w
        dfdw_i: the derivative wrt w_i (see self.derivative_w to see how it should be defined).
        dimensions:list  [inpunt_dim,output_dim]
        w0: initial values of w
        '''
    
        self.w=w0
        self.dim=len(w0)
        
        self.dimensions=dimensions
        
        self.signal=[0 for i in range(dimensions[1])] #will store the output of self.f
        self.dsdw=[0 for i in range(dimensions[1])] #will store the output of self.dfdw_i
        
        #will store the input, to avoid passing the input every time we callthe function or its derivetive
        self.input=[0 for i in range(dimensions[1])]
    
    def setInput(self,x):
        '''set the input'''
        self.input=x

    def __call__(self):
        pass
    
    def derivative_w(self,i):
        pass



class lossFunc:
    '''
    This is how the loss function should look like.
    We use a class, in order to encapsulate the gradient within the same object.
    '''
    def __init__(self,data_in,data_out,Q_i,dQds_i,model):
        '''
        data_in, data_out: the input, output data to be used in order to minimize the loss
        
        Q: the loss function in one domension. It will be averaged over all dimensions in __call__
        dQds_i: the derivative of the loss function wrt to s_i (the i^th signal)
        
        model: instance of modelFunc 
        '''
        self.data_in=data_in
        self.data_out=data_out
        self.data_size=len(self.data_in)
        
        self.Q_i=Q_i
        self.dQds_i=dQds_i
        self.model=model
        
        self.dim=len(self.model.w)#dimension of w
        self.N=model.dimensions[1]#dimension of model.signal
        self.dQdw=0 #this will hold dQdw
        
        #we need this to hold the average gadient over all data points
        self.grad=[0 for _ in range(self.dim)]

        
        
    def __call__(self,target):
        sum_Q=0;
         
        for r in range(self.N):
            sum_Q+=self.Q_i(self.model.signal[r],target[r])
    
        sum_Q=sum_Q/(float(self.N))

        return sum_Q
    
    

    def averageGrad(self):
        #get the average gradient over all data
        for index in range(self.data_size):
            t=self.data_out[index]
            self.model.setInput(self.data_in[index])
            self.model()

            for i in range(self.dim):
                self.model.derivative_w(i)
                self.dQdw=0

                for r in range(self.N):
                    tmp_dQds=self.dQds_i(self.model.signal[r], t[r])/(float(self.N))
                    self.dQdw += tmp_dQds*self.model.dsdw[r]

                self.grad[i]+=self.dQdw/self.data_size


class GradientDescent:
    
    def __init__(self,loss):
        '''
        loss: the loss function
        '''
        
        self.Q=loss
    
        
        self.steps=[]
        self.steps.append(self.Q.model.w[:])
        self.dim=self.Q.model.dim
    
    def update(self):
        pass
    
    def run(self,abs_tol=1e-5, rel_tol=1e-3, step_break=100,max_step=5000):
        '''        
        abs_tol, rel_tol, step_break: stop when _check<1 (_check is what update should return) 
        for step_break consecutive steps
        
        max_step: maximum number of steps
        '''
        _s=0
        count_steps=1
        while count_steps<=max_step:
            _check=self.update(abs_tol, rel_tol)
            self.steps.append(self.Q.model.w[:])
            
            count_steps+=1             
                
            
            if _check<1:
                _s+=1
            else:
                _s=0
            
            if _s>step_break:
                break

        return self.Q.model.w[:]