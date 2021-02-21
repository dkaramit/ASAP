from numpy import random as np_random


def SGD(self, strategy, data_in, data_out, abs_tol=1e-5, rel_tol=1e-3, step_break=100,max_step=5000):
    '''
    You have to pass the data (data_in are the inputs and data_out their corresponding outputs),
    and define the loss (and its derivative).

    strategy: the strategy that will be used to update the parameters

    data_in,data_out: the inputs and the corresponding outputs to be used for training

    abs_tol,rel_tol: determine the scale of a parameter 
    (e.g. the scale of w^{(l)}_{ji} is scale=abs_tol+rel_tol*self.weights[l][j][i])

    step_break:if the average scale (over the dimension of the output signal) is smaller than the gradient
    for step_break number of steps, the SGD exits the loop.

    max_step: SGD exits after max_step steps regardless of convergence. 
    '''
    #size of data
    data_size=len(data_in)
    
    _s=0
    count_steps=1
    while count_steps<=max_step:
        
        #get a random data point (it will be passed to the strategy.update function)
        index=np_random.randint(data_size)
        x=data_in[index]
        t=data_out[index]
        #run for x as the input, in order to get the output signal and be prepeared
        #to get its derivatives over the parameters.
        self.inputSignal(x)
        self.feedForward()
        self.backPropagation()

        
        #strategy should have an update member. During this, w's and b's are updated.
        #it can return sumething that becomes less than one, when the gradient becomes
        #small enough (we can change it later, to make the convergence conditions more 
        #involved). 
        #It also should have access to "self" because it will need to know the 
        #structure of the network, the loss, and take their derivatives.
        _check=strategy.update(t, abs_tol, rel_tol)

        count_steps+=1             
        if _check<1:
            _s+=1
        else:
            _s=0
        
        if _s>step_break:
            break
    #print(count_steps)
