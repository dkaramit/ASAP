from numpy import sin,cos,tanh,exp,random
from numpy import sum as np_sum

class FFANN:
    def __init__(self, _inputs,_outputs,_hidden_nodes, 
                 _hidden_func=lambda x:x,
                 _output_func=lambda x:x):
        '''
        Constructor for the class.

        _inputs: number of input nodes
        _outputs: number of ouput nodes
        
        _hidden_nodes: list of number of layers in each hidden node
        _hidden_func,_output_func: activation functions for hidden layers and output, respectively
        '''
        
        self.inputs=_inputs
        self.outputs=_outputs
        self.layers=len(_hidden_nodes)
        self.total_layers=2+self.layers #total layers = No. layers + input layer + output layer
        
        self.hidden_activation=_hidden_func
        self.output_activation=_output_func

        #an array to hold number of nodes at each layer
        self.nodes=[_inputs]
        
        for _n in _hidden_nodes:
            self.nodes.append(_n)
            
        self.nodes.append(_outputs)
        
            
        
        #declare the signals
        self.signals=[ [0 for j in range(self.nodes[l])]  for l in range(self.total_layers)]
        #in case you get confused, these are the indices
        self.signal_indices=[ ['x^({0})_{1}'.format(l,j) for j in range(self.nodes[l])]  for l in range(self.total_layers)]
        

        
        #declare the weights
        self.weights=[ [[0 for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]
        #in case you get confused, these are the indices
        self.weight_indices=[ [['w^({0})_{1}{2}'.format(l,j,i) for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]
        
        
        
        #declare the biases
        #By definition the biases of l=0 are zero, so we define biases[l][j] to refer to the l+1 layer.
        #this will help as we will be able to put the biases in the same loop as the weights (see init_params for example).
        self.biases=[ [0 for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]        
        #in case you get confused, these are the indices
        self.bias_indices=[ ['b^({0})_{1}'.format(l+1,j) for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]
        
    
        self.init_params()#initialize the weights and biases
                
    #========================initializations========================#
    def init_params(self):
        '''
        Function that initializes the weights and biasesby some random numbers.
        '''
        for l in range(self.layers+1):
            for j in range(self.nodes[l+1]):
                #You see, we defined biases in this way in order to manipulate them with the weights at the same loop. 
                self.biases[l][j] = (random.choice([-1,1])*random.random() )
                for i in range(self.nodes[l]):
                    self.weights[l][j][i] = (random.choice([-1,1])*random.random() )
    
    
    def write_params(self):
        '''
            Returns biases and weights as a vector.
            Can be used to pass the parameters to an optimization algorithm that takes vectors. 
        '''
        X=[]
        for l in range(self.layers+1):
            for j in range(self.nodes[l+1]):
                X.append(self.biases[l][j])
                for i in range(self.nodes[l]):
                    X.append(self.weights[l][j][i])
        return X
    
    def read_params(self,X):
        '''
            Read and update biases and weights from a vector X
            Can be used to read the result from an optimization algorithm that returns vectors. 
        '''
        _s=0
        for l in range(self.layers+1):
            for j in range(self.nodes[l+1]):
                self.update_bias(l,j,X[_s])
                _s+=1
                for i in range(self.nodes[l]):
                    self.update_weight(l,j,i,X[_s])
                    _s+=1
    
    def input_signal(self, x):
        '''Read the input (x).'''
        for j,_ in enumerate(x):
            self.signals[0][j] = _
    
    def calc_signal(self, l,j):
        '''calculate the output of the j node of layer l.'''
        if l == 0:
            print('for l=0 run self.input_signal')
            return 0
        
        sum_wx = np_sum( [ self.weights[l-1][j][i] * xi for i,xi in enumerate(self.signals[l-1]) ] ) 
        
        #Notice that self.biases[l-1][j] correspond to the bias of node j and layer l.
        if l == self.total_layers-1:
            self.signals[l][j] =  self.output_activation( sum_wx + self.biases[l-1][j]  )
            return 0
        
        if l < self.total_layers-1:
            self.signals[l][j] = self.hidden_activation( sum_wx + self.biases[l-1][j]  )
            return 0    
    
    #========================Feed-Forward========================#
    
    def feed_forward(self):
        '''
        Calculates the output of the network.
        Also sets the signals (for later use)
        '''
        for l in range(1,self.total_layers):
            for j in range(self.nodes[l]):
                self.calc_signal(l,j)
            
            
            
            
    #========================update========================#

    def update_weight(self,l,j,i,value):
        '''
        Change the value of w^{l}_{ji} to value
        '''
        self.weights[l][j][i]=value

    def update_bias(self,l,j,value):
        '''
        Change the value of b^{l}_{j} to value
        '''
        self.biases[l][j]=value
    #======================================================#
