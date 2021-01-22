from numpy  import random as np_random
from numpy  import array as np_array
from numpy  import exp as np_exp

class SimulatedAnnealing:
    def __init__(self, func, region, x0, T0, sigma):
        '''
        func: the function to be minimized
                
        region: the search region
        
        x0: starting point
        
        k: to be used for the temperature update
        
        sigma: new neighbours are found between x+N(0,sigma)
        '''
        
        self.func=func
        self.region=region
        self.x=x0
        self.T=T0
        
        #sigma must be smaller than (region[d][1]- region[d][0])*2 
        self.sigma=sigma
        
        #dimension of the input
        self.dim=len(x0)
        #value of the function at x0 (so-called energy)
        self.E=self.func(x0)
        
        #use these to store the abolute minimum. At the end Emin and E should be close.
        self.E_min=self.E
        self.x_min=x0
        self.T0=T0
        
        
        self.ListProb=[]
        self.ListIC=[]
        self.ListE=[]
        self.ListEmin=[]
    
    
    def nextT(self,k):
        '''Update the temperature'''
#         self.T=self.T/(1+k*self.T)
        self.T*=k
        
    # we need the mod function to keep x in the search region in case sigma is too large 
    def mod(self,x,y):
        return float(x) - int(float(x)/float(y)) *float(y)
    def PickNeighbour(self):
        '''Pick a neighbour'''
        x=[]
        for d in range(self.dim):
            x.append(self.x[d] + np_random.rand()*self.sigma[d]-self.sigma[d]/2)
            
            if self.region[d][1]<x[d] :
                dx=x[d]-self.region[d][1]          
                dx=self.mod(dx,self.region[d][1]-self.region[d][0])
                x[d]=self.region[d][0] + dx
                
            if x[d] <self.region[d][0] :
                dx= self.region[d][0] - x[d]
                dx=  self.mod(dx,self.region[d][1]-self.region[d][0]) 
                x[d]= self.region[d][1] - dx

                
        x=np_array(x)
        return x
            
    
    def BoltzmannP(self,Enew):
        '''Given a new value of the energy, return the Boltzmann factor'''
        return np_exp(-(Enew-self.E)/self.T)
    
        
    
    
    def runT(self,IterationT):
        #use these to find the mean Delta E for a temperature 
        self.AccProb=0
        
        for _ in range(IterationT):
            xnew=self.PickNeighbour()
            Enew=self.func(xnew)
            
            #store the abolute minimum you've found so far
            if self.E<self.E_min:
                self.E_min=self.E
                self.x_min=self.x

            
            if Enew<self.E or self.BoltzmannP(Enew) > np_random.rand():
                self.AccProb+=1
                self.E=Enew
                self.x=xnew
                
        self.AccProb=self.AccProb/IterationT
    
        
    def InitT(self, IterationT, N0, k0, p0):
        '''Find an appropriace initial temperature'''
        IterT0=0
        
        while IterT0<N0:
            self.runT(IterationT)
           
            if self.AccProb>p0:
                IterT0+=1
            
            if self.AccProb<p0 and IterT0>0:
                IterT0=0
            
            self.T*=k0
                

        
       
    def run(self, CList, tol, MinT,k=1-1e-2, Nstar=5000, IterationT=100,
            N0=500, k0=1+1e-2, p0=0.8):
        '''
        Iterate until the temperature reaches MinT or until it reaches convergence (Nstart times with AccProb<tol)
        CList=True stores acceptance probabilities, IterConv, E values for all temperatures 
        in self.ListProb self.ListIC, self.ListE

        tol,Nstar: SA Stops when the acceptance probability is below tol for Nstar successive iterations
        IterationT: number of iterations per temperature
        MinT:  stop when the temperature becomes MinT
        
        To initialize the temperature:
        p0,N0,k0: increase the temperature as T->T*k0 until the acceptance probability is larger that p0
        for N0 successive iterations
        
        If N0=0, then run with T0. If N0!=0, initialize T0 by running InitT. Since T0 is attribute of this class
        you can first run with N0>0, and then run again with N0=0. During the first run, a suitable T0 will be found,
        so that you'll not have to do it again!
        '''
        if N0==0:
            self.T=self.T0;
        else:
            self.InitT(IterationT, N0, k0, p0)
            self.T0=self.T;
        
        IterConv=0
        
        
        
        self.points=[]
        while self.T>MinT and Nstar>IterConv:
            self.runT(IterationT)

            if self.AccProb<tol:
                IterConv+=1
                self.points.append(self.x)
            
            if self.AccProb>tol and IterConv>0:
                IterConv=0
                self.points=[]
            
            
            if CList:
                self.ListProb.append(self.AccProb)
                self.ListIC.append(IterConv)
                self.ListE.append(self.E)
                self.ListEmin.append(self.E_min)
            
            
            
            self.nextT(k)
            
        self.points=np_array(self.points)
        self.x,self.E= self.x_min,self.E_min
        return self.x,self.E
    
                        