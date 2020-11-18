from numpy import sin,cos,tanh,exp,random
from numpy import sum as np_sum

class brains:
    '''
    Class for definition of (feed-forward) neural network.
    '''

    def __init__(self,_inputs,_outputs,_layers,_hidden_nodes):
        '''
        Constractor.

        _inputs: number of input nodes
        _outputs: number of ouput nodes
        _layers: number of hidden layers
        _nodes: list of number of layers in each hidden node

        Example
        ann=brains(2,1,3,[2,5,3])
        is a neural network with:
        2 inputs, 1 output, and 3 layers.
        The first layer has 2 nodes, the second 5. and the third 3.
        '''
        self.inputs=_inputs

        self.outputs=_outputs

        self.layers=_layers

        self.total_layers=2+_layers

        '''
        self.nodes represent the network as a list of nodes.
        That is if self.nodes gives [8,3,2,2], the network has 8 inputs,
        2 ouputs, 2 hidden layers with 3 and 2 nodes, respectively.

        Example:
        ann=brains(8,2,2,[4,5])

        gives:
        self.nodes -> [8,4,5,2]

        '''

        self.nodes=[0 for __i in range(self.total_layers)]

        #number of inputs are the nodes of the zeroth layer
        self.nodes[0]=_inputs

        #number of outputs are the nodes of the _layers+1 layer
        self.nodes[_layers+1]=_outputs

        #the next intermediate are the hidden nodes
        for __i,__n in enumerate(_hidden_nodes):
            self.nodes[__i+1]=__n

        self.total_nodes=np_sum(self.nodes)#the total number of nodes, to be passed to the individual class



    #========================initializations========================#
    def init_weights(self):
        '''
        Function that initializes the weights.
        '''

        self.weights=[]
        for l in range(self.layers+1):
            _tmp1=[]
            for n_current in range(self.nodes[l]):
                _tmp2=[]
                for n_next in range(self.nodes[l+1]):
                    #_tmp2.append( 'w^({0})_{1}{2}'.format(l,n_current,n_next) )

                    #just put random numbers from -1 to 1 for the moment
                    _tmp2.append(random.choice([-1,1])*random.random() )
                _tmp1.append(_tmp2)
            self.weights.append(_tmp1)

    def init_biases(self):
        '''
        Function that initializes the biases.
        For simplicity I define input  biases to zero (redundant, but I'll figure it out later).
        '''
        self.biases=[]
        for l in range(self.total_layers):
            _tmp=[]
            for n in range(self.nodes[l]):
                #_tmp.append('b^({l})_{n}'.format(l=l,n=n))
                if l==0:
                    _b=0
                else:
                    _b=random.choice([-1,1])*random.random()
                _tmp.append(_b)

            self.biases.append(_tmp)
    #=================================================================#


    #============activation functions============#
    '''
    Later I should add the option to change the activation functions
    using a member function like set_hidden_activation.
    '''
    def hidden_activation(self,x):
        return x

    def output_activation(self,x):
        return x
    #============================================#

    #========================input========================#
    def read_input(self,_input):
        self.input_signals=[]
        for n in range(self.nodes[0]):
            self.input_signals.append(_input[n])
    #=====================================================#

    #========================feed forward function========================#
    def feed_forward(self):
        '''
        Calculates the output of the network.
        Also sets the signals (for later use)
        '''

        self.signals=[]

        for l in range(self.total_layers):
            _tmp=[]
            for n in range(self.nodes[l]):

                if l==0:
                    _tmp.append(self.input_signals[n])

                else:
                    _sum=self.biases[l][n]
                    for j,_sig in enumerate(self.signals[l-1]):
                        _sum+=_sig*self.weights[l-1][j][n]

                    if l<self.total_layers-1:
                        _tmp.append(self.hidden_activation(_sum) )
                    else:
                        _tmp.append(self.output_activation(_sum) )

            self.signals.append(_tmp)

    #=====================================================================#

    #========================update========================#

    def update_weight(self,l,i,j,weight):
        '''
        Change the value of w^{l}_{ij} to weight
        '''
        self.weights[l][i][j]=weight

    def update_bias(self,l,i,bias):
        '''
        Change the value of b^{l}_{i} to bias
        '''
        self.biases[l][i]=bias
    #======================================================#
