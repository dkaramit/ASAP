from numpy import random

#========================initializations========================#
def init_params(self,_min=-1,_max=1):
    '''
    Function that initializes the weights and biases using random numbers in [_min,_max]
    '''
    for l in range(self.total_layers-1):
        for j in range(self.nodes[l+1]):
            #You see, we defined biases in this way in order to manipulate them with the weights at the same loop. 
            self.biases[l][j] = (random.choice([_min,_max])*random.random() )
            for i in range(self.nodes[l]):
                self.weights[l][j][i] = (random.choice([_min,_max])*random.random() ) 
