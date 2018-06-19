import numpy as np


Transition=np.array([\
            [0.5,0.3,0.2],\
            [0.05,0.45,0.5],\
            [0.25,0.35,0.4],\
            ])




'''
Iterative solution to w.P=w
'''
v=[0.1,0.1,0.8]#play around with this (the final result should not change as long as the v.v=1)

s=v[:]
N_tot=50000
for i in range(N_tot):
    s=np.dot(Transition.T,s)
    #print s
print "iterative=", s



'''
Simulation
'''
state=[1,0,0]#This is the initial sate vector, which indicates the current state. e.g [1,0,0] indicates that the system is in state 0 (I start counting from 0).

#state=v[:]#I can set any initial probability (since MC is ergodic)

def Read_State(state):
    return state.index(1)#the state is the index of the state vector.


def Transition_Probability(state,Transition):
    _probabilities=np.dot(Transition.T,state)#probabilities to move from the current state to all other states.
    return _probabilities


_N=0

_visits=[0,0,0]
while True:
    if _N==N_tot:
        break

    '''

    The next state is determined by the multinomial distribution, which is included in numpy (how do you sample from the multinomial?).

    '''
    state= np.random.multinomial(1,Transition_Probability(state,Transition))
    _visits+=state#fortunately, all definitions click together. Since stetes are defined in "binary", sowe can add them up to give us the #of visits of each state.

    _N+=1


print 'simulation=', np.array(_visits)/float(_N)#probabilities is ne fraction of visits over time :)















#
