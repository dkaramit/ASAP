from numpy   import sqrt as np_sqrt

from .GradientDescent import GradientDescent
 
class VanillaGD(GradientDescent):
    def __init__(self,function,alpha=1e-2):
        '''
        function: instance of Function
        alpha: the learning rate
        '''
        GradientDescent.__init__(self,function)
        
        self.alpha=alpha

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        
        
        _x2=0
        _check=0
                        
        self.function.derivative(self.function.x)
        
        for i in range(self.dim):
            dx=self.alpha*self.function.grad[i]
            
            self.function.x[i]=self.function.x[i]-dx

            _x2=abs_tol + self.function.x[i] * rel_tol
            _check+=(dx/_x2)*(dx/_x2)

        _check=np_sqrt(1./self.dim *_check)

        self.steps.append(self.function.x[:])
        
        
        tmp_min=self.function(self.function.x)
        if tmp_min<self.f_min:
            self.function.minimum=self.function.x[:]
            self.f_min=tmp_min
            
        return _check
