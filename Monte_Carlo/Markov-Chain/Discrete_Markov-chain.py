import numpy as np



EXAMPLE=3


if EXAMPLE==1:
    '''
    The trasition matrix defines the Markov Chain. If you change to higher dimentions and want to start from
    a state diferent from 0, then you should change the dimension of variables v and state, accordingly.
    '''
    Transition=np.array([\
                [0.5,0.3,0.1,0.1],\
                [0.05,0.45,0.4,0.1],\
                [0.25,0.35,0.3,0.1],\
                [0.4,0.1,0.25,0.25]
                ])#Reminder: the sum of each row sums up to 1.

if EXAMPLE==2:
    '''
    The trasition matrix defines the Markov Chain. If you change to higher dimentions and want to start from
    a state diferent from 0, then you should change the dimension of variables v and state, accordingly.
    '''
    Transition=np.array([\
                [0.2,0.7,0.1],\
                [0,0,1],\
                [1,0,0]\
                ])#Reminder: the sum of each row sums up to 1.


'''
Generate a random Markov Chain (with N_dim #states) and see if it reaches equilibrium (the most probable scenario is that it will, since I generate random rows
with numbers that add up to 1)
'''
N_dim=30
if EXAMPLE==3:
    Transition=np.random.dirichlet(np.ones(N_dim),N_dim)



#=============================================================Begin
#Number of steps in both the Iteration and Simulation.
N_tot=500000
#Doing the following you start at state 0 automatically.
len_T=len(Transition[0])
init_s=np.zeros(len_T)
init_s[0]=1


'''
Iterative solution to w.P=w.
Iteratively find w^{(n)}=w^{(0)}.P^{(n+1)}.
'''
#v=[1,0,0,0]#play around with this (the final result should not change as long as the v.v=1)
v=init_s[:]#start at state 0 automatically

'''
Simulation.
Simulate the Markov Chain
'''
#state=[1,0,0,0]#This is the initial sate vector, which indicates the current state. e.g [1,0,0] indicates that the system is in state 0 (I start counting from 0).
state=init_s[:]#start at state 0 automatically
_visits=np.zeros(len(state))





for i in np.arange(N_tot):

    '''
    Calculate v^{(n+1)}=P^{T}v^{(n)}
    '''
    v=np.dot(Transition.T,v)

    '''
    The next state in the simulation is determined by the multinomial distribution, which is included in numpy (how do you sample from the multinomial?).
    '''
    state= np.random.multinomial(1,np.dot(Transition.T,state))
    _visits+=state#Fortunately, all notations click together. Since states are defined in "binary", we can add them up to obtain the number of visits for each state.



print "iterative=", v

s=np.array(_visits)/float(N_tot)
print 'simulation=', s#probabilities is the fraction of visits over time.


print r"Maximum discrepancy:", np.max(np.abs(v-s))/np.max(np.abs(v)),r"%"

#=============================================================Done

#
