import numpy as np


class SimAn:
    def __init__(self, func, dim , x0 ,  T0, k, IterationT, MinT, sigma,Convergence):
        '''
        func: the function to be minimized
        dim: the number of arguments that func takes
        x0: starting point
        k: to be used for the temperature update
        IterationT: number of iterations per temperature
        MinT:  stop when the temperature becomes MinT
        sigma: new neighbours are found between x+-sigma/2
        Convergence: Stops when the acceptance probability drops below this
        '''
        
        self.func=func
        self.dim=dim
        self.x=x0
        self.T=T0
        self.k=k
        
        self.IterationT=IterationT
        self.MinT=MinT
        self.sigma=sigma
        self.Convergence=Convergence
        
        self.E=self.func(x0)
        
        self.xnew=self.x
        
        self.Acceptanced=0
        self.TotalCheck=0
        
    def nextT(self):
        '''Update the temperature'''
#         self.T=self.T/(1+k*self.T)
        self.T*=self.k
        
    def PickNeighbour(self):
        '''Pick a neighbour'''
#         self.xnew=self.x+np.random.rand(dim)*sigma-sigma/2
        self.xnew=self.x+np.random.normal(self.sigma,size=self.dim)#the normal seems to work nicely. 
            
    
    def BoltzmannP(self,Enew):
        '''Given a new value of the energy, return the Boltzmann factor'''
        return np.exp(-(Enew-self.E)/self.T)
    
    def runT(self):
        for _ in range(self.IterationT):
            self.TotalCheck+=1

            self.PickNeighbour()
            Enew=self.func(self.xnew)
            if Enew<self.E:
                self.E=Enew
                self.x=self.xnew
                self.Acceptanced+=1
            else:
                if self.BoltzmannP(Enew) > np.random.rand() :
                    self.E=Enew
                    self.x=self.xnew
                    self.Acceptanced+=1
                
    def run(self):
        '''Iterate until the temperature reaches MinT'''
        
        while self.T>self.MinT:
            self.runT()

            if self.Acceptanced/self.TotalCheck<self.Convergence:
                break
            
            self.nextT()

        return self.x,self.func(self.x)

                        