import numpy as np



'''
Generate a random Markov Chain (with N_dim #states) and see if it reaches equilibrium (the most probable scenario is that it will, since I generate random rows
with numbers that add up to 1)
'''
N_dim=15
Transition=np.random.dirichlet(np.ones(N_dim),N_dim)

'''
#Example, that should give equilibrium=[0.5,0,0.5]
N_dim=3
Transition=np.array([\
            [0.7,0,0.3],\
            [0.5,0,0.5],\
            [0.3,0,0.7]\
            ])#Reminder: the sum of each row sums up to 1.
'''


#=============================================================Begin
#Number of steps in both the Iteration and (the maximum of) Simulation.
N_tot=50000
#Doing the following you start at state 0 automatically.
len_T=len(Transition[0])
init_s=np.zeros(len_T)
init_s[0]=1







v=init_s[:]
for i in np.arange(N_tot):

    '''
    Iterative solution:
    Calculate v^{(n+1)}=P^{T}v^{(n)}
    '''
    v=np.dot(Transition.T,v)





'''
Simulate the Markov Chain
'''
#state=[1,0,0,0]#This is the initial sate vector, which indicates the current state. e.g [1,0,0] indicates that the system is in state 0 (I start counting from 0).
state=init_s[:]#start at state 0 automatically
_visits=np.zeros(len(state))
fN_tot=float(N_tot)
tolerance=1e-6
means=[]
for transition in np.arange(1,N_tot+1):
    '''
    Simulation:
    The next state in the simulation is determined by the multinomial distribution,
    which is included in numpy ( you can find how to samlpe from the multinomial in misc/multinomial.py ).

    To determine if the chain has converged, get the mean positions every 1000 transitions. This will give you
    a list  N_dim*2 means. The chains has convered if the relative variance of the means is below some
    threshold (tolerance variable).
    '''
    state= np.random.multinomial(1,np.dot(Transition.T,state))
    #Fortunately, all notations click together. Since states are defined in "binary",
    #we can add them up to obtain the number of visits for each state.

    _visits+=state
    equilibrium=_visits/float(transition)

    #get the mean position for 1000 transitions
    if transition%(1000) != 0:
        #mean position
        _m=np.sum(  [ e*i for i,e in enumerate(equilibrium)]  )
        means.append( _m )
    #after N_dim*2 transitions, check if it has converged. If not, reset the list of means and continue.
    else:
        if np.var(means)/np.mean(means)<tolerance:
            s=equilibrium
            print 'converged after {} transitions. Equilibrium state: {}'.format(transition, equilibrium)
            #print v
            #find maximum discrepancy between iterative and simulated
            _md=0
            for i,e in enumerate(v):
                if e==0:
                    _diff=np.abs(e-equilibrium[i])
                else:
                    _diff=np.abs(e-equilibrium[i])/float(e)
                if _md<_diff:
                    _md=_diff
            print r"Maximum discrepancy between iterative and simulated equilibrium state:", _md

            exit()
        print transition , np.mean(means), np.var(means)



        means=[]














#=============================================================Done

#
