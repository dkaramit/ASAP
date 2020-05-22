import numpy as np

class SimulatedAnnealing:
    def __init__(self, func, dim , x0 ,  T0, k, IterationT, MinT, sigma, tol, Nstar, p0,N0,k0):
        '''
        func: the function to be minimized
        
        dim: the number of arguments that func takes
        
        x0: starting point
        
        k: to be used for the temperature update
        
        IterationT: number of iterations per temperature
        
        MinT:  stop when the temperature becomes MinT
        sigma: new neighbours are found between x+N(0,sigma)
        
        tol,Nstar: SA Stops when the acceptance probability is below tol for Nstar successive iterations
        
        To initialize the temperature:
        p0,N0,k0: increase the temperature as T->T*k0 until the acceptance probability is larger that p0
        for N0 successive iterations
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
        
        self.p0=p0
        self.N0=N0
        self.k0=k0
        
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
        self.AccProb=0
        
        for _ in range(self.IterationT):
            xnew=self.PickNeighbour()
            Enew=self.func(xnew)
            
            
            if Enew<self.E or self.BoltzmannP(Enew) > np.random.rand():
                self.AccProb+=1
                self.E=Enew
                self.x=xnew
                
        self.AccProb=self.AccProb/self.IterationT

        
    def InitT(self):
        '''Find an appropriace initial temperature'''
        IterT0=0
        
        while IterT0<self.N0:
            self.runT()
           
            if self.AccProb>self.p0:
                IterT0+=1
            
            if self.AccProb<self.p0 and IterT0>0:
                IterT0=0
            
            self.T*=self.k0
                

        
        
    def run(self, CList=False):
        '''
        Iterate until the temperature reaches MinT or until it reaches convergence (Nstart times with AccProb<tol)
        CList=True stores acceptance probabilities, IterConv, E values for all temperatures 
        in self.ListProb self.ListIC, self.ListE
        '''
        #run to find initial temperature that has large acceptance probability 
        self.InitT()
        
        IterConv=0
        
        if CList:
            self.ListProb=[]
            self.ListIC=[]
            self.ListE=[]
            
        while self.T>self.MinT and self.Nstar>IterConv:
            self.runT()

            if self.AccProb<self.tol:
                IterConv+=1
            
            if self.AccProb>self.tol and IterConv>0:
                IterConv=0
            
            
            if CList:
                self.ListProb.append(self.AccProb)
                self.ListIC.append(IterConv)
                self.ListE.append(self.E)
            
            
            
            self.nextT()

        return self.x,self.E

                        