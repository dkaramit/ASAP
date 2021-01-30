def feedForwardDerivatives(self):
    '''
    Calculate the output and the "local" derivatives of the network
    This feed forward function also fills the self.totalDerivatives,
    with self.totalDerivatives[-1] being the derivatives of the output 
    nodes with respect to the input nodes
    '''
    N=self.total_layers
    for l in range(1,N):
        for j in range(self.nodes[l]):
            self.calcSignal(l,j)
        self.mulM(l)


def mulM(self,l):
    '''
    Matrix multiplication to be used when calculating the derivatives.
    It is intended to be used the feedForwardDerivatives() call.
    self.totalDerivatives is

    self.totalDerivatives[0][j][i] = \dfrac{\partial s^{1}_{j}}{\partial s^{(0)}_{i}} 
    self.totalDerivatives[1][j][i] = \dfrac{\partial s^{2}_{j}}{\partial s^{(0)}_{i}} 
    .
    .
    .
    self.totalDerivatives[l][j][i] = \dfrac{\partial s^{l+1}_{j}}{\partial s^{(0)}_{i}} 

    using our convention, this is

    self.totalDerivatives[l][j][i] = self.derivatives[l][j][k] * self.totalDerivatives[l-1][j][k] 
    '''

    if l==1:
        self.totalDerivatives[0]= self.derivatives[0][:]
        return 
    
    for j in range(self.nodes[l]):
        for i in range(self.nodes[0]):
            self.totalDerivatives[l-1][j][i]=0
            for k in range(self.nodes[l-1]):
                self.totalDerivatives[l-1][j][i]+=self.derivatives[l-1][j][k]*self.totalDerivatives[l-2][k][i]



