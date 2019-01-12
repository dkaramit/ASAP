from numpy import random,zeros_like


def multinomial(n,probabilities):
    '''
    works like  numpy.random.multinomial!

    You can draw from a multinomial using the following:
    1) get the probabilities for each state.
    That is a list with probabilities, [p1,p2,...,pn], each coresponding to an outcome

    2) calculate a list containing the cumulative probabilities (c=[p1, p1+p2, p1+p2+p3, ...,1])

    3) draw a random number, r, form 0 to 1

    4) if r<=c[i], return i.
    '''


    cumulatives=[]
    _cm=0
    for i in probabilities:
        _cm+=i
        cumulatives.append(_cm)


    state=zeros_like(probabilities)

    for i in range(n):
        _r=random.rand()
        for i,_p in enumerate(cumulatives):
            if _r<=_p:
                state[i]+=1
                break

    return state



if __name__=='__main__':
    '''Test run of the function'''
    _N=500
    _initial_p=[0.1,0.1,0.5,0.2,0.01,0.09]


    _m= multinomial(_N,_initial_p)

    print _initial_p,sum(_initial_p)

    _produced_p=[i/float(_N) for i in _m]
    print _produced_p, sum(_produced_p)

    print _m
