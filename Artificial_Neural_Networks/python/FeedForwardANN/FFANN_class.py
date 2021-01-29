from numpy import sum as np_sum

from .FFANN_const import  FFANN_const
from .FFANN_init_params import  init_params
from .FFANN_call import  evaluate,call,inputSignal,calcSignal,feedForward,mulM
from .FFANN_numerical_derivative import numericalDerivative,totalNumericalDerivative
from .FFANN_aux import fill_weights_with,fill_biases_with,print_weights,print_biases,print_signals


class FFANN:
    def __init__(self, _inputs,_outputs,_hidden_nodes, activations):
        FFANN_const(self, _inputs,_outputs,_hidden_nodes, activations)
       
    def evaluate(self):
        '''
        Calculate the output without the derivatives.
        The outputs of all nored are stored in self.signals
        '''
        evaluate(self)

    def inputSignal(self,x):
        '''
        Read the input (x) and store it in self.signals[0]
        '''
        inputSignal(self,x)

    def calcSignal(self, l,j):
        '''
        Calculate the output of the j node of layer l and 
        the derivatives of s^{l}_{j} with respect s^{l-1}_{i} (far all i).
        It is intended to be used after the l-1 signals have been calulated
        within the feedForward() call
        '''
        calcSignal(self, l,j)

    def mulM(self,l):
        '''
        Matrix multiplication to be used when calculating the derivatives.
        It is intended to be used the feedForward() call
        '''
        mulM(self,l)


    def feedForward(self):
        '''
        Calculate the output and the derivatives of the network
        '''
        feedForward(self)

    def __call__(self,x): 
        '''
        Calculates the output and the derivatives of the network with self.signals[0]=x
        '''
        return call(self,x)
    

    #========================initialization========================#
    def init_params(self,_min=-1,_max=1):
        '''
        Function that initializes the weights and biases using random numbers in [_min,_max]
        '''
        init_params(self,_min=-1,_max=1)
    
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





    def numericalDerivative(self,input_node,h=1e-3):
        '''
        Numerical derivatives with respect to "input_node". Stores the result in 

        self.numericalDerivatives[j][input_node] for all j=0,1,...self.total_layers-1.

        It is still better to just run __call__(), because __call__ calculates everything (marginally) faster.  
        '''

        return numericalDerivative(self,input_node,h=1e-3)

    def totalNumericalDerivative(self,h=1e-3):
        '''
        Run numericalDerivative for all input nodes. 
        The result is stored in self.numericalDerivatives
        '''

        return totalNumericalDerivative(self,h=1e-3)



    

    #-------------------------------Aux--------------------------------#
    def fill_weights_with(self,value=0):
        fill_weights_with(self,value=0)

    def fill_biases_with(self,value):
        fill_biases_with(self,value)
    #print
    def print_weights(self):
        print_weights(self)

    def print_biases(self):
        print_biases(self)

    def print_signals(self):
        print_signals(self)