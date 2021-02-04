from numpy import sum as np_sum

from .FFANN_const import  FFANN_const
from .FFANN_init_params import  init_params

from .FFANN_call import  evaluate,call,inputSignal,calcSignal,feedForward

from .FFANN_backProp import  backPropagation, derivative_bw

from .FFANN_derivatives import feedForwardDerivatives,mulM

from .FFANN_numerical_derivative import numericalDerivative,totalNumericalDerivative,numericalDerivative_bw
from .FFANN_aux import fill_weights_with,fill_biases_with,printWeights,printBiases,printSignals,printDerivatives,printTotalDerivatives,printDelta,printNumericalDerivatives,printDerivatives_w,printDerivatives_b,printNumericalDerivatives_w,printNumericalDerivatives_b


class FFANN:
    def __init__(self, _inputs,_outputs,_hidden_nodes, activations):
        FFANN_const(self, _inputs,_outputs,_hidden_nodes, activations)
       
    def evaluate(self,x):
        '''
        Calculate the output without the derivatives.
        The outputs of all nored are stored in self.signals
        '''
        evaluate(self,x)

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

    def feedForward(self):
        '''
        Calculate the output and the derivatives of the network
        '''
        feedForward(self)

    def backPropagation(self):
        '''
        Define Delta^{f}_{ji} = \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{[N-(f+2)]}_{i}}.
        For f=0,1,2,...N-2 this is n^{(N-1)} \times n^{(N-(f+2))} matrix
        
        Notice that the Delta^{self.total_layers-2}_{ji} = \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{(0)}_{i}}
        '''
        backPropagation(self)


    def derivative_bw(self,l,j,i):
        '''
        caclulate

        \dfrac{\partial s^{(N-1)}_{r}}{\partial w^{(l)}_{ji}} =  
        \Delta^{ (N-(l+3)) }_{r j} \theta^{\prime\, (l+1)}_{j}s^{(l)}_{i}

        and 
        \dfrac{\partial s^{(N-1)}_{r}}{\partial w^{(l+1)}_{ji}} =  
        \Delta^{ (N-(l+3)) }_{r j} \theta^{\prime\, (l+1)}_{j}

        stores the results in self.dsdw and self.dsdb
        '''
        return derivative_bw(self,l,j,i)



    def __call__(self,x): 
        '''
        Calculates the output and the derivatives of the network with self.signals[0]=x
        '''
        return call(self,x)
    

    def mulM(self,l):
        '''
        Matrix multiplication to be used when calculating the derivatives.
        It is intended to be used the feedForward() call
        '''
        mulM(self,l)

    def feedForwardDerivatives(self):
        '''
        Calculate the output and the "local" derivatives of the network
        This feed forward function also fills the self.totalDerivatives,
        with self.totalDerivatives[-1] being the derivatives of the output 
        nodes with respect to the input nodes
        '''
        feedForwardDerivatives(self)
    #========================initialization========================#
    def init_params(self,_min=-1,_max=1):
        '''
        Function that initializes the weights and biases using random numbers in [_min,_max]
        '''
        init_params(self,_min,_max)
    
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



    def addToWeight(self,l,j,i,dw):
        '''
        Change the value of w^{l}_{ji} to w^{l}_{ji}+dw
        '''
        self.weights[l][j][i]+=dw
        # print(dw)

    def addToBias(self,l,j,db):
        '''
        Change the value of b^{l}_{j} to b^{l}_{j}+db
        '''
        self.biases[l][j]+=db
        # print(db)
        
    #======================================================#



    def numericalDerivative(self,input_node,h=1e-3):
        '''
        Numerical derivatives with respect to "input_node". Stores the result in 

        self.numericalDerivatives[j][input_node] for all j=0,1,...self.total_layers-1.

        It is still better to just run __call__(), because __call__ calculates everything (marginally) faster.  
        '''
        return numericalDerivative(self,input_node,h)

    def totalNumericalDerivative(self,h=1e-3):
        '''
        Run numericalDerivative for all input nodes. 
        The result is stored in self.numericalDerivatives
        '''
        return totalNumericalDerivative(self,h)

    def numericalDerivative_bw(self,l,j,i,h=1e-3):
        '''
        Numerical derivative of s^{self.total_layers-1}_r wrt w^{(l)}_{ji} and
        s^{self.total_layers-1}_r wrt b^{(l+1))}_{j}.

        stores the results in self.numerical_dsdw and self.numerical_dsdb 
        '''
        return numericalDerivative_bw(self,l,j,i,h)

    

    #-------------------------------Aux--------------------------------#
    def fill_weights_with(self,value=0):
        fill_weights_with(self,value)

    def fill_biases_with(self,value=0):
        fill_biases_with(self,value)
    #print
    def printWeights(self):
        printWeights(self)

    def printBiases(self):
        printBiases(self)

    def printSignals(self):
        printSignals(self)

    def printDerivatives(self):
        printDerivatives(self)

    def printTotalDerivatives(self):
        printTotalDerivatives(self)
    
    def printDelta(self):
        printDelta(self)

    def printNumericalDerivatives(self):
        printNumericalDerivatives(self)

    def printDerivatives_w(self):
        printDerivatives_w(self) 

    def printDerivatives_b(self):
        printDerivatives_b(self)        

    def printNumericalDerivatives_w(self):
        printNumericalDerivatives_w(self) 

    def printNumericalDerivatives_b(self):
        printNumericalDerivatives_b(self)        
    