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



class sigmoidActivation:
    '''Example of how an activation functiion should look-like'''
    def __init__(self):
        pass
    
    def __call__(self,x):
        return 1/(1+exp(-x))
        
    def derivative(self,x):
        return exp(-x)*self(x)**2


class expActivation:
    '''Example of how an activation functiion should look-like'''
    def __init__(self):
        pass
    
    def __call__(self,x):
        return (1-exp(-x))
        
    def derivative(self,x):
        return exp(-x)

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
        

        #there is no point chenging and resizing them every time I pass through mulM or calcSignal
        self.derivatives=[ [[0 for i in range(self.nodes[l])] for j in range(self.nodes[l+1])]  for l in range(self.layers+1)]
        # totalDerivatives accumulates the derivatives in a way that  self.totalDerivatives[-1] is the derivative of the outputs wrt all inputs
        self.totalDerivatives=[ [[0 for i in range(self.nodes[0])] for j in range(self.nodes[l])]  for l in range(1,self.total_layers)]
        
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
        # you can returnt output and its derivatives
        return self.signals[self.total_layers-1],self.totalDerivatives[self.total_layers-2]

    #-------------------------signals--------------------------------------#
    def inputSignal(self, x):
        '''Read the input (x).'''
        for j,_ in enumerate(x):
            self.signals[0][j] = _
    
    def calcSignal(self, l,j):
        '''
        calculate the output of the j node of layer l and 
        the derivatives of s^{l}_{j} with respect s^{l-1}_{i} (far all i).
        It is intended to be used after the l-1 signals have been calulated.
        '''
        #for l=0 this function is meaningless as self.signals[0] is input

        #Notice that self.biases[l-1][j] correspond to the bias of node j and layer l.
        sum_wx = sum( [ self.weights[l-1][j][i] * xi for i,xi in enumerate(self.signals[l-1]) ] ) 
        self.signals[l][j] =  self.activations[l-1]( sum_wx + self.biases[l-1][j]  )
        
        #fill also the derivatives (does the same thing as self.derivative for all i in self.nodes[l-1])
        arg=sum_wx+self.biases[l-1][j] 
        for i in range(self.nodes[l-1]):
            self.derivatives[l-1][j][i]= self.activations[l-1].derivative(arg) * self.weights[l-1][j][i]

           
    def feedForward(self):
        '''
        Calculates the output and its derivative of the network.
        '''
        
        for l in range(1,self.total_layers):
            for j in range(self.nodes[l]):
                self.calcSignal(l,j)
            self.mulM(l)
        
                
    def mulM(self,l):
        '''Matrix multiplication to be used when calculating the derivatives'''
        if l==1:
            self.totalDerivatives[0]= self.derivatives[0][:]
            return 
        
        for j in range(self.nodes[l]):
            for i in range(self.nodes[0]):
                self.totalDerivatives[l-1][j][i]=0
                for k in range(self.nodes[l-1]):
                    self.totalDerivatives[l-1][j][i]+=self.derivatives[l-1][j][k]*self.totalDerivatives[l-2][k][i]


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

    def numericalDerivative(self,output_node,input_node,h=1e-3):
        '''Vanilla numerical derivative (faster in very large networks)'''
        h1=h+abs(self.signals[0][input_node])*h
        
        self.signals[0][input_node]+=h1
        self.feedForward()
        f1=self.signals[self.total_layers-1][output_node]
        
        self.signals[0][input_node]-=2*h1
        self.feedForward()
        f0=self.signals[self.total_layers-1][output_node]
        
        self.signals[0][input_node]+=h1
    
        return (f1-f0)/(2*h1)

    def totalNumericalDerivative(self,h=1e-3):
    
        return [[self.numericalDerivative(p,r)  for r in range(self.inputs)] for p in range(self.outputs) ]


    

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