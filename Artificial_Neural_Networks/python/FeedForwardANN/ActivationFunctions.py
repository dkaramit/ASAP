from numpy import sin,cos,tanh,exp


class linearActivation:
    '''linear activation function'''
    def __init__(self):
        pass
    
    def __call__(self,x):
        return x
        
    def derivative(self,x):
        return 1



class sigmoidActivation:
    '''sigmoid activation function'''
    def __init__(self):
        pass
    
    def __call__(self,x):
        return 1/(1+exp(-x))
        
    def derivative(self,x):
        return exp(-x)*self(x)**2


class expActivation:
    '''exponential activation function'''
    def __init__(self):
        pass
    
    def __call__(self,x):
        return (1-exp(-x))
        
    def derivative(self,x):
        return exp(-x)
