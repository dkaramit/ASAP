from numpy import sqrt as np_sqrt
from numpy import sum as np_sum

#the GradientDescent class
class GradientDescent:
    def __init__(self,target,x0,alpha=1e-1,tol=1e-8,step_break=100):
        '''
        target: the target function to be minimized, with target.Gard its gradient
                      
        x0: starting point
        
        alpha: the alpha parameter
        
        tol, step_break: stop when the gradient becomes smaller than tol/alpha for step_break consecutive steps
        '''
        
        self.target=target
        
        self.alpha=alpha
        self.tol=tol
        self.step_break=step_break
        
        
        self.x0=[_ for _ in x0]
        self.x=[_ for _ in x0]

        
        
    def update(self):
        self.grad=self.target.Grad(self.x)
        self.x = [ self.x0[i] - self.alpha*grad for i,grad in enumerate(self.grad)]
    
    def run(self):
        
        _s=0
        
        self.steps=[]#store the steps here
        
        while True:
            self.update()
            
            _check= np_sqrt(np_sum([_**2 for _ in self.grad] ))
            
            
            self.steps.append(self.x)
            
            if _check<self.tol/self.alpha:
                _s+=1
            else:
                _s=0
            
            if _s>self.step_break:
                break
        
            self.x0 = [ _ for _ in self.x]
        
        return self.x


#the target function class (you can also write your own if you know the gradient analytically)
class targetFunc:
    def __init__(self,func,h=1e-5):
        self.function =func
        self.h=h
        
    def __call__(self,x):
        return self.function(x)
    
    def Grad(self,x):
        x0=[_ for _ in x]
        x1=[_ for _ in x]
        
        grad=[]
        for dim in range(len(x)):
            x0[dim]=x[dim]-self.h
            x1[dim]=x[dim]+self.h
            
            dfdx0=self.function(x0) 
            dfdx1=self.function(x1) 

            x0[dim]=x[dim]
            x1[dim]=x[dim]
            
            grad.append((dfdx1-dfdx0)/(2*self.h))
        
        return grad
            
                    


#example:
if __name__=="__main__":
    import numpy as np

    def func(x):
        return 1-np.exp(-(x[0]**2+x[1]**2))

    target=targetFunc(func,2)

    GD=GradientDescent(target,[-0.1,2],alpha=1e-1,tol=1e-8,step_break=5e2)

    print(GD.run())