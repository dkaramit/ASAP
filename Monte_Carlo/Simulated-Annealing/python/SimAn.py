import numpy as np




class SimulatedAnnealing:
    def __init__(self, func, dim , x0 ,  T0, k, IterationT, MinT, sigma, tol, Nstar):
        '''
        func: the function to be minimized
        dim: the number of arguments that func takes
        x0: starting point
        k: to be used for the temperature update
        IterationT: number of iterations per temperature
        MinT:  stop when the temperature becomes MinT
        sigma: new neighbours are found between x+-sigma/2
        tol,Nstar: SA Stops when |\Delta E |<tol for Nstar successive iterations
        '''
        
        self.func=func
        self.dim=dim
        self.x=x0
        self.T=T0
        self.k=k
        
        self.IterationT=IterationT
        self.MinT=MinT
        self.sigma=sigma
        self.tol=tol
        self.Nstar=Nstar
        
        self.E=self.func(x0)
            
    def nextT(self):
        '''Update the temperature'''
#         self.T=self.T/(1+k*self.T)
        self.T*=self.k
        
    def PickNeighbour(self):
        '''Pick a neighbour'''
#         return self.x+np.random.rand(dim)*sigma-sigma/2
        return self.x+np.random.normal(self.sigma,size=self.dim)#the normal seems to work nicely. 
            
    
    def BoltzmannP(self,Enew):
        '''Given a new value of the energy, return the Boltzmann factor'''
        return np.exp(-(Enew-self.E)/self.T)
    
    def runT(self):
        #use these to find the mean Delta E for a temperature 
        self.DE=0
        acc=0
        
        for _ in range(self.IterationT):
            xnew=self.PickNeighbour()
            Enew=self.func(xnew)
            
            
            if Enew<self.E or self.BoltzmannP(Enew) > np.random.rand():
                self.DE+=Enew
                acc+=1
                
                self.E=Enew
                self.x=xnew
                
        
        if acc==0:
            self.DE=0
        else:
            self.DE=np.abs(self.DE/acc-self.E) 
                
    def run(self, CList=False):
        '''
        Iterate until the temperature reaches MinT or until it reaches convergence
        CList=True stores E and IterConv values for all temperatures in self.ListIC and self.ListE
        '''
        
        
        IterConv=0
        
        if CList:
            self.ListIC=[]
            self.ListE=[]
            
        while self.T>self.MinT and self.Nstar>IterConv:
            self.runT()

            if self.DE<tol:
                IterConv+=1
            
            if self.DE>tol and IterConv>0:
                IterConv=0
            
            
            if CList:
                self.ListIC.append(IterConv)
                self.ListE.append(self.E)
            
            
            
            self.nextT()

        return self.x,self.E

                        