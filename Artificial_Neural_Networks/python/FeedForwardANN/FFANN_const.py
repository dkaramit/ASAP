def FFANN_const(self, N_inputs,N_outputs, hiddenNodes, activationFunctions):
    '''
    Constructor for the class.

    N_inputs: number of input nodes
    N_outputs: number of ouput nodes
    
    hiddenNodes: list of number of layers in each hidden node
    activationFunctions: list of activation functions for hidden layers and output
    '''

    #self.inputs=N_inputs
    #self.outputs=N_outputs
    #self.layers=len(hiddenNodes)

    self.total_layers=2+len(hiddenNodes) #total layers = No. layers + input layer + output layer
    
    self.activations=activationFunctions
    #an array to hold number of nodes at each layer
    self.nodes=[N_inputs]
    
    for _n in hiddenNodes:
        self.nodes.append(_n)
        
    self.nodes.append(N_outputs)
    
        
    
    #declare the signals
    self.signals=[ [0 for j in range(self.nodes[l])]  for l in range(self.total_layers)]

    #I will use this in the evaluation of numerical derivatives 
    self._signals=[ [0 for j in range(self.nodes[l])]  for l in range(self.total_layers)]
    self.numericalDerivatives=[[0  for r in range(self.nodes[0])] for p in range(self.nodes[self.total_layers-1]) ]

    #in case you get confused, these are the indices
    self.signal_indices=[ ['x^({0})_{1}'.format(l,j) for j in range(self.nodes[l])]  for l in range(self.total_layers)]
    

    
    #declare the weights
    self.weights=[ [[0 for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(self.total_layers-1)]
    #in case you get confused, these are the indices
    self.weight_indices=[ [['w^({0})_{1}{2}'.format(l,j,i) for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(self.total_layers-1)]
    

    #there is no point chenging and resizing them every time I pass through mulM or calcSignal
    self.derivatives=[ [[0 for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(self.total_layers-1)]
    # totalDerivatives accumulates the derivatives in a way that  self.totalDerivatives[-1] is the derivative of the outputs wrt all inputs
    self.totalDerivatives=[ [[0 for i in range(self.nodes[0])] for j in range(self.nodes[l])]  for l in range(1,self.total_layers)]
    
    #declare the biases
    #By definition the biases of l=0 are zero, so we define biases[l][j] to refer to the l+1 layer.
    #this will help as we will be able to put the biases in the same loop as the weights (see init_params for example).
    self.biases=[ [0 for j in range(self.nodes[l+1])]  for l in range(self.total_layers-1)]        
    #in case you get confused, these are the indices
    self.bias_indices=[ ['b^({0})_{1}'.format(l+1,j) for j in range(self.nodes[l+1])]  for l in range(self.total_layers-1)]
    
