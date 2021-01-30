def backPropagation(self):
    '''
    Define Delta^{f}_{ji} = \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{[N-(f+2)]}_{i}}.
    For f=0,1,2,...N-2 this is n^{(N-1)} \times n^{(N-(f+2))} matrix
    
    Notice that the Delta^{self.total_layers-2}_{ji} = \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{(0)}_{i}}
    '''
    
    
    N=self.total_layers
    
    self.Delta[0]=self.derivatives[N-2][:]
    
    for f in range(1,N-1):#don't run for f=0
        for j in range(self.nodes[N-1]):
            for i in range(self.nodes[N-(f+2)]):
                self.Delta[f][j][i]=0
                for k in range(self.nodes[N-(f+1)]):
                    self.Delta[f][j][i]+=self.Delta[f-1][j][k] * self.derivatives[N-(f+2)][k][i]
                    

def derivative_bw(self,l,j,i):
    '''
    caclulate:
    
    \dfrac{\partial s^{(N-1)}_{r}}{\partial w^{(l)}_{ji}} = \Delta^{ (N-(l+3)) }_{r j} \theta^{\prime\, (l+1)}_{j}s^{(l)}_{i}
    
    at the same time caclulate 
    
    \dfrac{\partial s^{(N-1)}_{r}}{\partial b^{(l+1)}_{j}} =\Delta^{ (N-(l+3)) }_{r j} \theta^{\prime\, (l+1)}_{j}
    
    and return the result for all r (r=# output nodes).
    
    
    '''
    N=self.total_layers
    
    if l==N-2:            
        for r in range(self.nodes[N-1]):
            if j==r:
                sum_wx = sum( [ self.weights[l][j][k] * xi for k,xi in enumerate(self.signals[l]) ] ) 
                self.dsdb[r]=self.activations[l].derivative(sum_wx+self.biases[l][j])
                self.dsdw[r]=self.dsdb[r]*self.signals[l][i]
            else:
                self.dsdb[r]=0
                self.dsdw[r]=0

    else:
        sum_wx = sum( [ self.weights[l][j][k] * xi for k,xi in enumerate(self.signals[l]) ] ) 
        for r in range(self.nodes[N-1]):
            self.dsdb[r]=self.Delta[N-(l+3)][r][j]
            self.dsdb[r]*=self.activations[l].derivative(sum_wx+self.biases[l][j])
            
            self.dsdw[r]=self.dsdb[r]*self.signals[l][i]
