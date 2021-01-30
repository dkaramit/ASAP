from copy import deepcopy


def numericalDerivative(self,input_node,h=1e-3):
    '''
    Numerical derivatives with respect to "input_node". Stores the result in 
    
    self.numericalDerivatives[j][input_node] for all j=0,1,...self.total_layers-1.

    It is still better to just run __call__(), because __call__ calculates everything (marginally) faster.  
    '''
    
    h1=h+abs(self.signals[0][input_node])*h
    self._signals[0]=self.signals[0][:]
    
    self.signals[0][input_node]+=h1
    self._signals[0][input_node]-=h1
    
    for l in range(1,self.total_layers-1):
        for j in range(self.nodes[l]):
            sum_wx1=0
            sum_wx0=0
            for i in range(self.nodes[l-1]):

                sum_wx1 += self.weights[l-1][j][i] * self.signals[l-1][i] 
                sum_wx0 += self.weights[l-1][j][i] * self._signals[l-1][i]

            self.signals[l][j]  =  self.activations[l-1]( sum_wx1 + self.biases[l-1][j]  )
            self._signals[l][j] =  self.activations[l-1]( sum_wx0 + self.biases[l-1][j]  )

    #run the last layer outside the loop becasuse the last j-loop gives us the derivatives!
    l=self.total_layers-1
    for j in range(self.nodes[l]):
        sum_wx1=0
        sum_wx0=0
        for i in range(self.nodes[l-1]):

            sum_wx1 += self.weights[l-1][j][i] * self.signals[l-1][i] 
            sum_wx0 += self.weights[l-1][j][i] * self._signals[l-1][i]

        f1 =  self.activations[l-1]( sum_wx1 + self.biases[l-1][j]  )
        f0 =  self.activations[l-1]( sum_wx0 + self.biases[l-1][j]  )
        self.numericalDerivatives[j][input_node]=(f1-f0)/(2*h1)


    self.signals[0][input_node]-=h1



def totalNumericalDerivative(self,h=1e-3):
    '''
    Run numericalDerivative for all input nodes. 
    The result is stored in self.numericalDerivatives
    '''
    for r in range(self.nodes[0]):
        self.numericalDerivative(r)

    #return self.numericalDerivatives


def numericalDerivative_bw(self,l,j,i,h=1e-3):
    '''
    numerical derivative

    \dfrac{\partial s^{(N-1)}_{r}}{\partial w^{(l)}_{ji}} and 
    \dfrac{\partial s^{(N-1)}_{r}}{\partial b^{(l+1)}_{j}} 
    (for all r=0,1,...self.nodes[self.total_layers-1])

    using the formula: 

    \dfrac{\partial s^{(N-1)}_{r}}{\partial s^{(l+1)}_{j}} \theta^{\prime\, (l+1)}_{j}s^{(l)}_{i}

    Notice that we need to update only the signals at layers greater that l+2!
    '''

    N=self.total_layers

    h1=h+abs(self.signals[l+1][j])*h

    tmp=deepcopy(self.signals) #copying in python -.- 

    self._signals=deepcopy(self.signals)

    sum_wx = sum( [ self.weights[l][j][k] * self.signals[l][k] for k in range(self.nodes[l]) ] ) 
    factor_w=self.activations[l].derivative(sum_wx +self.biases[l][j])*self.signals[l][i]
    factor_b=self.activations[l].derivative(sum_wx +self.biases[l][j])

    self.signals[l+1][j]=self.signals[l+1][j]+h1
    self._signals[l+1][j]=self._signals[l+1][j]-h1

    for l1 in range(l+2,N):
        for j1 in range(self.nodes[l1]):
            sum_wx1=0
            sum_wx0=0
            for i1 in range(self.nodes[l1-1]):

                sum_wx1 += self.weights[l1-1][j1][i1] * self.signals[l1-1][i1] 
                sum_wx0 += self.weights[l1-1][j1][i1] * self._signals[l1-1][i1]

            self.signals[l1][j1]  =  self.activations[l1-1]( sum_wx1 + self.biases[l1-1][j1]  )
            self._signals[l1][j1] =  self.activations[l1-1]( sum_wx0 + self.biases[l1-1][j1]  )


    f1=self.signals[N-1][:]
    f0=self._signals[N-1][:]


    #after everything, restore the signals (only everything after l+1 is changed, but deepcopy should be faster in general)
    self.signals=deepcopy(tmp) 

    self.numerical_dsdw=[ (f1[r]-f0[r])/(2.*h1 )*factor_w for  r in range(self.nodes[N-1])]
    self.numerical_dsdb=[ (f1[r]-f0[r])/(2.*h1 )*factor_b for  r in range(self.nodes[N-1])]
