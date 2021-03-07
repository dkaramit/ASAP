from numpy import ceil as np_ceil


#let's make a base class that holds the functions we'll need

class Interpolation:
    '''
    Base class for spline interpolation.
    This basic holds the search method, and declares the function (__call__), and the 1st and 2nd derivatives.
    
    the __call__ function here is such that this class corresponds to zeroth order interpolation.
    '''
    def __init__(self,data_x,data_y):
        '''
        data_x: the list for x. Note that I assume that x is sorted in ascending order! 
        data_y: the list for y 
        '''
        self.N=len(data_x)#number of elements
        self.X=[_ for _ in data_x]
        self.Y=[_ for _ in data_y]
        
        #check if X[i-1]<X[i]. This will help with the searching
        for i in range(1,self.N):
            if self.X[i-1]>=self.X[i]:
                print('x must be in increasing order!!!')
                break
    def bSearch(self,x):
        '''
        This function takes a value (x) and finds which polynomial needs to be executed.
        That is it returns i, for x between X[i] and X[i+1]. 
        '''
        L=0
        R=self.N-1
                
        while R-L>1:
            m=int((L+R)/2.); 
            if self.X[m]<x:
                L=m
            else:
                R=m
        
        return L

    
    
    def __call__(self,x):
        '''
        0th order spline
        this is not good because the binary search is defined in such way that if x=X[N-1] 
        this function returns Y[N-2].
        '''
        i=self.bSearch(x)
        return self.Y[i]
    
    
    def derivative_1(self,x):
        '''0^th order spline of the first derivative'''
        
        i=self.bSearch(x)
        return (self.Y[i]-self.Y[i+1])/(self.X[i]-self.X[i+1])
    
    def derivative_2(self,x):
        return 0



class linearSpline(Interpolation):
    '''
    linear spline interpolation class 
    '''
    def __init__(self,data_x,data_y):
        '''
        data_x: the list for x. Note that I assume that x is sorted in ascending order! 
        data_y: the list for y 
        '''

        Interpolation.__init__(self, data_x,data_y)

    def __call__(self,x):
        i=self.bSearch(x)
        a=(self.X[i+1]-x)/(self.X[i+1]-self.X[i])
        return a*self.Y[i]+(1-a)*self.Y[i+1]
    
    def derivative_1(self,x):
        '''
        1st order spline of the first derivative.
        It is better than taking the derivative of __call__
        '''
        i=self.bSearch(x)
        
        if i==self.N-2:
            return (self.Y[i]-self.Y[i+1])/(self.X[i]-self.X[i+1])
        
        a=(self.X[i+1]-x)/(self.X[i+1]-self.X[i])
        dydx0=(self.Y[i]-self.Y[i+1])/(self.X[i]-self.X[i+1])
        dydx1=(self.Y[i+1]-self.Y[i+2])/(self.X[i+1]-self.X[i+2])
    
        return a*dydx0+(1-a)*dydx1
    
    

class cubicSpline(Interpolation):
    '''
    cubic spline interpolation class 
    '''
    def __init__(self,data_x,data_y):
        '''
        data_x: the list for x. Note that I assume that x is sorted in ascending order! 
        data_y: the list for y
        '''

        Interpolation.__init__(self, data_x,data_y)
        #these are the tables we need here. y2 are the points of the second derivatives we need to find
        self.y2=[0 for _ in range(self.N)]
        #calculate the parameters (the list of second derivatives)
        self.paramCalc()
    
    def paramCalc(self):
        '''This calculates the parameters we need'''
        u=[0 for _ in range(self.N-1)]
        self.y2[0]=0
        self.y2[self.N-1]=0
        
        for i in range(1,self.N-1):
            sig=(self.X[i]-self.X[i-1])/(self.X[i+1]-self.X[i-1])
            p=sig*self.y2[i-1]+2
            self.y2[i]=(sig-1)/p
            u[i]=(self.Y[i+1]-self.Y[i])/(self.X[i+1]-self.X[i]) - (self.Y[i]-self.Y[i-1])/(self.X[i]-self.X[i-1])
            u[i]=(6*u[i]/(self.X[i+1]-self.X[i-1])-sig*u[i-1])/p
        
        
        
        for k in range(self.N-2,-1,-1): #we need k=N-2,N-1,...0
            self.y2[k]=self.y2[k]*self.y2[k+1]+u[k]
        
        
    def __call__(self,x):
        i=self.bSearch(x)
        klo=i
        khi=i+1

        h=self.X[khi]-self.X[klo]
        
        a=(self.X[khi]-x)/h
        b=(x-self.X[klo])/h

        y=a*self.Y[klo]+b*self.Y[khi]
        y+=(a*a*a-a)*self.y2[klo]*(h*h)/6.
        y+=(b*b*b-b)*self.y2[khi]*(h*h)/6.
        
        return y
    
    def derivative_1(self,x):
        '''
        The first derivative of  __call__ obtained analytically.
        '''
        i=self.bSearch(x)

        klo=i
        khi=i+1

        h=self.X[khi]-self.X[klo]
        
        a=(self.X[khi]-x)/h
        b=(x-self.X[klo])/h

        dydx=(self.Y[khi]-self.Y[klo])/h
        dydx+=-(3*a*a-1)*self.y2[klo]*h/6.
        dydx+=(3*b*b-1)*self.y2[khi]*h/6.
        
        return dydx
        
    def derivative_2(self,x):
        '''
        The second derivative of  __call__ obtained analytically.
        '''

        i=self.bSearch(x)
        a=(self.X[i+1]-x)/(self.X[i+1]-self.X[i])
        return a*self.y2[i]+(1-a)*self.y2[i+1]

    