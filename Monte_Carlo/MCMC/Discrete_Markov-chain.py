import numpy as np

'''
The trasition matrix defines the Markov Chain. If you change to higher dimentions, then you should change the variables:
i) v
ii) state

'''
Transition=np.array([\
            [0.5,0.3,0.2],\
            [0.05,0.45,0.5],\
            [0.25,0.35,0.4],\
            ])




'''
Iterative solution to w.P=w
Iteratively find w^{(n)}=w^{(0)}.P^{(n+1)}.
'''
v=[0.1,0.1,0.8]#play around with this (the final result should not change as long as the v.v=1)

s=v[:]
N_tot=100000
for i in range(N_tot):
    s=np.dot(Transition.T,s)
    #print s
print "iterative=", s



'''
Simulation.
Simulate the Markov Chain
'''

state=[1,0,0]#This is the initial sate vector, which indicates the current state. e.g [1,0,0] indicates that the system is in state 0 (I start counting from 0).


def Transition_Probability(state,Transition):
    _probabilities=np.dot(Transition.T,state)#probabilities to move from the current state to all other states.
    return _probabilities


_N=0

_visits=np.zeros(len(state))
while True:
    if _N==N_tot:
        break

    '''
    The next state is determined by the multinomial distribution, which is included in numpy (how do you sample from the multinomial?).
    '''
    state= np.random.multinomial(1,Transition_Probability(state,Transition))
    _visits+=state#Fortunately, all notations click together. Since states are defined in "binary", we can add them up to obtain the number of visits for each state.

    _N+=1


print 'simulation=', np.array(_visits)/float(_N)#probabilities is ne fraction of visits over time.



print "As for large N_tot, the simulated result should approach the iteratitve one."











#
