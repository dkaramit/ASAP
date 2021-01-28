from numpy import sin,cos,tanh,exp,random
from numpy import sum as np_sum


class linearActivation:
    '''Example of how an activation functiion should look-like'''
    def __init__(self):
        pass
    
    def __call__(self,x):
        return x
        
    def derivative(self,x):
        return 1


class FFANN:
    def __init__(self, _inputs,_outputs,_hidden_nodes, 
                 activations=[]):
        '''
        Constructor for the class.

        _inputs: number of input nodes
        _outputs: number of ouput nodes
        
        _hidden_nodes: list of number of layers in each hidden node
        activations: list of activation functions for hidden layers and output
        '''
        
        self.inputs=_inputs
        self.outputs=_outputs
        self.layers=len(_hidden_nodes)
        self.total_layers=2+self.layers #total layers = No. layers + input layer + output layer
        
        if len(activations)==0:
            self.activations=[lambda x:x for _ in range(self.total_layers-1)]
        else:
            self.activations=[_ for _ in activations]

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
        
        self.derivatives=[ [[0 for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]
        
        
        #declare the biases
        #By definition the biases of l=0 are zero, so we define biases[l][j] to refer to the l+1 layer.
        #this will help as we will be able to put the biases in the same loop as the weights (see init_params for example).
        self.biases=[ [0 for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]        
        #in case you get confused, these are the indices
        self.bias_indices=[ ['b^({0})_{1}'.format(l+1,j) for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]
        
    
        self.init_params()#initialize the weights and biases
                
    #========================initializations========================#
    def init_params(self,_min=-1,_max=1):
        '''
        Function that initializes the weights and biasesby some random numbers.
        '''
        for l in range(self.layers+1):
            for j in range(self.nodes[l+1]):
                #You see, we defined biases in this way in order to manipulate them with the weights at the same loop. 
                self.biases[l][j] = (random.choice([_min,_max])*random.random() )
                for i in range(self.nodes[l]):
                    self.weights[l][j][i] = (random.choice([_min,_max])*random.random() ) 


    #let's overlaod __call__ for convenience
    def __call__(self,x):
        self.inputSignal(x)
        self.feedForward()
        return self.signals[self.total_layers-1]

    #-------------------------signals--------------------------------------#
    def inputSignal(self, x):
        '''Read the input (x).'''
        for j,_ in enumerate(x):
            self.signals[0][j] = _
    
    def calcSignal(self, l,j):
        '''
        calculate the output of the j node of layer l.
        It is intended to be used after the l-1 signals have been calulated.
        '''
        if l == 0:
            print('for l=0 run self.inputSignal')
            return 0
        
        #Notice that self.biases[l-1][j] correspond to the bias of node j and layer l.
        sum_wx = np_sum( [ self.weights[l-1][j][i] * xi for i,xi in enumerate(self.signals[l-1]) ] ) 
        self.signals[l][j] =  self.activations[l-1]( sum_wx + self.biases[l-1][j]  )

    
    #========================Feed-Forward========================#
    
    def feedForward(self):
        '''
        Calculates the output of the network.
        Also sets the signals (for later use)
        '''
        for l in range(1,self.total_layers):
            for j in range(self.nodes[l]):
                self.calcSignal(l,j)
            
            
            
    #=======derivatives=======================#
    def derivative(self,l,j,i):
        '''
        Return the derivative of s^{l+1}_{j} with respect s^{l}_{i}
        It is intended to be used after the l-1 signals have been calulated.
        '''
        
        arg=np_sum( [ self.weights[l][j][m] * xi for m,xi in enumerate(self.signals[l]) ] )+self.biases[l][j]  
        
        return self.activations[l].derivative(arg) * self.weights[l][j][i]
        
    
    def calcDerivatives(self):
        '''Fill self.derivatives'''
        for l in range(self.total_layers-1):
            for j in range(self.nodes[l+1]):
                for i in range(self.nodes[l]):
                    self.derivatives[l][j][i]=self.derivative(l,j,i)

    def mulM(self,l):
        '''Matrix multiplication to be used when calculating the derivatives'''
        _res=[]
        for j in range(self.nodes[l+1]):
            _tmp=[]
            for i in range(self.nodes[0]):
                _tmp.append(0)
                for k in range(self.nodes[l]):
                    _tmp[i]+=self.derivatives[l][j][k]*self.totalDerivatives[k][i]
            _res.append(_tmp)
        
        self.totalDerivatives=_res[:]
    
    def calcTotaDerivative(self,x=[]):
        '''
        calculate the derivatives of all outputs with respect to all inputs at the latest input point.
        That is, this function should run after feedFarward, otherwise the signals might be outdated 
        (Note: I should optimize it to run feefForward and derivatives at the same time, with minimal cost).
        
        The result is stored in self.totalDerivatives 
        '''
        if len(x)==0:
            self.calcDerivatives()
            self.totalDerivatives=self.derivatives[0][:]
            for l in range(1,self.total_layers-1):
                self.mulM(l)
        else:
            self(x)
            self.calcTotaDerivative()



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




    #-------------------------------Aux--------------------------------#

    def numericalDerivative(self,output_node,input_node,h=1e-3,x=[]):
        '''Vanilla numerical derivative (faster in very large networks)'''
        if len(x)==0:
            h1=h+abs(self.signals[0][input_node])*h
            
            self.signals[0][input_node]+=h1
            self.feedForward()
            f1=self.signals[self.total_layers-1][output_node]
            
            self.signals[0][input_node]-=2*h1
            self.feedForward()
            f0=self.signals[self.total_layers-1][output_node]
            
            self.signals[0][input_node]+=h1
        
            return (f1-f0)/(2*h1)
        else:
            self(x)
            return self.numericalDerivative(output_node,input_node,h,[])

    def totalNumericalDerivative(self,h=1e-3):
    
        return [[self.numericalDerivative(p,r)  for r in range(self.inputs)] for p in range(self.outputs) ]


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

    #fill everything with a given value
    def fill_weights_with(self,value=0):
        for l in range(len(self.weights)):
            for j in range(len(self.weights[l])):
                for i in range(len(self.weights[l][j])):
                    self.weights[l][j][i]=value

    def fill_biases_with(self,value):
        for l in range(len(self.biases)):
            for j in range(len(self.biases[l])):
                self.biases[l][j]=value

    #print
    def print_weights(self):
        for l in range(len(self.weights)):
            print('l=',l,':')
            for j in range(len(self.weights[l])):
                
                for i in range(len(self.weights[l][j])):
                    print(self.weights[l][j][i],'\t', end =" ")
                print('')
            print('============')
    
    def print_biases(self):
        for l in range(len(self.biases)):
            print('l=',l+1,':')
            for j in range(len(self.biases[l])):
                print(self.biases[l][j],'\t', end =" ")
            print('')
            print('============')

    def print_signals(self):
        for l in range(len(self.signals)):
            print('l=',l,':')
            for j in range(len(self.signals[l])):
                print(self.signals[l][j],'\t', end =" ")
            print('')
            print('============')