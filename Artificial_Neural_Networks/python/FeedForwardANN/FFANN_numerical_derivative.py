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
