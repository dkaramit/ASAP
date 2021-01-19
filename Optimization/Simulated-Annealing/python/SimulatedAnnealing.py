import numpy as np

class SimulatedAnnealing:
    def __init__(self, func, region , x0 ,  T0, k, IterationT, MinT, sigma, tol, Nstar, p0,N0,k0):
        '''
        func: the function to be minimized
        
        region: the search region
        
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
        self.region=region
        self.x=x0
        self.T=T0
        self.k=k
        
        self.IterationT=IterationT
        self.MinT=MinT
        
        #sigma must be smaller than (region[d][1]- region[d][0])*2 
        self.sigma=sigma
        
#         for d in range(dim):
#             if ( self.sigma[d] > (region[d][1]- region[d][0])*2 ):
#                 self.sigma[d] =  (region[d][1]- region[d][0])*2
        
        
        self.tol=tol
        self.Nstar=Nstar
        
        self.p0=p0
        self.N0=N0
        self.k0=k0
        self.dim=len(x0)
        
        self.E=self.func(x0)
        
        #use these to store the abolute minimum. At the end Emin and E should be close.
        self.E_min=self.E
        self.x_min=x0
        self.T0=T0
        
        
        self.ListProb=[]
        self.ListIC=[]
        self.ListE=[]
        self.ListEmin=[]
    
    
    def nextT(self):
        '''Update the temperature'''
#         self.T=self.T/(1+k*self.T)
        self.T*=self.k
        
    # we need the mod function to keep x in the search region in case sigma is too large 
    def mod(self,x,y):
        return float(x) - int(float(x)/float(y)) *float(y)
    def PickNeighbour(self):
        '''Pick a neighbour'''
        x=[]
        for d in range(self.dim):
            # x.append(self.x[d] + np.random.rand()*self.sigma[d]-self.sigma[d]/2)
            x.append(self.x[d] + np.random.normal(0,self.sigma[d]) ) 
            
            if self.region[d][1]<x[d] :
                dx=x[d]-self.region[d][1]          
                dx=self.mod(dx,self.region[d][1]-self.region[d][0])
                x[d]=self.region[d][0] + dx
                
            if x[d] <self.region[d][0] :
                dx= self.region[d][0] - x[d]
                dx=  self.mod(dx,self.region[d][1]-self.region[d][0]) 
                x[d]= self.region[d][1] - dx

                
        x=np.array(x)
        return x
            
    
    def BoltzmannP(self,Enew):
        '''Given a new value of the energy, return the Boltzmann factor'''
        return np.exp(-(Enew-self.E)/self.T)
    
        
    
    
    def runT(self):
        #use these to find the mean Delta E for a temperature 
        self.AccProb=0
        
        for _ in range(self.IterationT):
            xnew=self.PickNeighbour()
            Enew=self.func(xnew)
            
            #store the abolute minimum you've found so far
            if self.E<self.E_min:
                self.E_min=self.E
                self.x_min=self.x

            
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
                

        
       
    def run(self, CList=False, restart = False):
        '''
        Iterate until the temperature reaches MinT or until it reaches convergence (Nstart times with AccProb<tol)
        CList=True stores acceptance probabilities, IterConv, E values for all temperatures 
        in self.ListProb self.ListIC, self.ListE
        '''
        if restart:
            self.T=self.T0;
        else:
            self.InitT()
            self.T0=self.T;
        
        IterConv=0
        
        
        
        self.points=[]
        while self.T>self.MinT and self.Nstar>IterConv:
            self.runT()

            if self.AccProb<self.tol:
                IterConv+=1
                self.points.append(self.x)
            
            if self.AccProb>self.tol and IterConv>0:
                IterConv=0
                self.points=[]
            
            
            if CList:
                self.ListProb.append(self.AccProb)
                self.ListIC.append(IterConv)
                self.ListE.append(self.E)
                self.ListEmin.append(self.E_min)
            
            
            
            self.nextT()
            
        self.points=np.array(self.points)
        self.x,self.E= self.x_min,self.E_min
        return self.x,self.E
    
                        