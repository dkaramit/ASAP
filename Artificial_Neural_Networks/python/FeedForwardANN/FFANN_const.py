def FFANN_const(self, N_inputs,N_outputs, hiddenNodes, activationFunctions):
    '''
    Constructor for the class.

    N_inputs: number of input nodes
    N_outputs: number of ouput nodes
    
    hiddenNodes: list of number of nodes in each hidden layers
    activationFunctions: list of activation functions for hidden layers and output
    '''

    #self.inputs=N_inputs
    #self.outputs=N_outputs
    #self.layers=len(hiddenNodes)

    self.total_layers=2+len(hiddenNodes) #total layers = No. layers + input layer + output layer
    N=self.total_layers#define this for convinience here
    
    self.activations=activationFunctions
    #an array to hold number of nodes at each layer
    self.nodes=[N_inputs]
    
    for _n in hiddenNodes:
        self.nodes.append(_n)
        
    self.nodes.append(N_outputs)
    

    #declare the signals
    self.signals=[ [0 for j in range(self.nodes[l])]  for l in range(N)]

    #I will use this in the evaluation of numerical derivatives 
    self._signals=[ [0 for j in range(self.nodes[l])]  for l in range(N)]
    self.numericalDerivatives=[[0  for r in range(self.nodes[0])] for p in range(self.nodes[N-1]) ]
    #this will store the derivatives wrt the weights and biases
    self.dsdw=[0 for r in range(self.nodes[N-1])]
    self.dsdb=[0 for r in range(self.nodes[N-1])]
    #this will store the numerical derivatives wrt the weights and biases
    self.numerical_dsdw=[0 for r in range(self.nodes[N-1])]
    self.numerical_dsdb=[0 for r in range(self.nodes[N-1])]

    

    
    #declare the weights
    self.weights=[ [[0 for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(N-1)]
    #declare the biases
    #By definition the biases of l=0 are zero, so we define biases[l][j] to refer to the l+1 layer.
    #this will help as we will be able to put the biases in the same loop as the weights (see init_params for example).
    self.biases=[ [0 for j in range(self.nodes[l+1])]  for l in range(N-1)]        
    

    #these are the local derivatives 
    # self.derivatives[l][j][i]= \dfrac{\partial s^{l+1}_{j}}{\partial s^{(l)}_{i}}
    self.derivatives=[ [[0 for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(N-1)]
    

    #####------About self.totalDerivatives and self.Delta------#####
    '''
    Both use the chain rule to obtain derivatives. However:
    
    1. self.totalDerivatives is obtained by applying the chain-rule during feed forward 
    (i.e. its elements are \dfrac{\partial s^{l+1}_{j}}{\partial s^{(0)}_{i}} for all l).
    Therefore, this is useful when the network is already trained, and we just need its derivatives
    (since they are calculated during the feed forward).

    2. self.Delta is obtained by applying the chain-rule during back propagation
    (i.e. its elements are \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{[N-(f+2)]}_{i}} 
    for N=self.total_layers, f=N-(l+3) and l<N-2).
    This is useful as we train the network, as it cannot be caclulated during feed forward.
    '''

    # self.totalDerivatives[l][j][i] = \dfrac{\partial s^{l+1}_{j}}{\partial s^{(0)}_{i}}  
    self.totalDerivatives=[ [[0 for i in range(self.nodes[0])] for j in range(self.nodes[l+1])]  for l in range(N-1)]
    
    #self.Delta[f][j][i] = \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{[N-(f+2)]}_{i}}
    #It is filled by running backPropagation()
    self.Delta=[ [[0 for i in range(self.nodes[N-(f+2)])] for j in range(self.nodes[N-1])]  for f in range(N-1)]
    
    
    
    



    #in case you get confused, these are the indices
    self.signal_indices=[ ['s^({0})_{1}'.format(l,j) for j in range(self.nodes[l])]  for l in range(N)]
    #in case you get confused, these are the indices
    self.weight_indices=[ [['w^({0})_{1}{2}'.format(l,j,i) for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(N-1)]
    #in case you get confused, these are the indices
    self.bias_indices=[ ['b^({0})_{1}'.format(l+1,j) for j in range(self.nodes[l+1])]  for l in range(self.total_layers-1)]