'''
Example:
How to use autocorrelation and traceplot
to determine burn-in and thinningself.
See also comments below.
'''



import numpy as np
import matplotlib.pyplot as plt


def Gauss(x,mu,sigma):
    return np.exp(-(x-mu)**2/(2*sigma**2))*1/np.sqrt(2*np.pi * sigma**2)

def func(x):
    return Gauss(x,0.2,0.01)
    #return np.sin(12*(x-0.2))**2

#vectorize func for convinience
#use func to calculate autocorrelation and the mean/variance of func. In practice, one might have a physical quantity to be estimated.
VF=np.vectorize(func)


def Metropolis(Target,xin,N=10000,eps=0.01,burn_in=0,thinning=10,_fixed_interval=True):
    '''
    burn_in: do not store the first 'burn_in' accepted steps (the first few steps could be in a region with low probability).
    thinning: store 1 every 'thinning' accepted steps (makes the more independent).
    _fixed_interval: if True keps x in [0,1].
    '''
    accepted=[]

    _n_b=0
    _n_t=0

    x=xin
    func_x=Target(x)

    for i in np.arange(N):
        if _fixed_interval:
            while True:

                can=np.random.normal(x,eps)# Gaussian candidate position
                #can=(np.random.rand()*2-1)*eps+x# Uniform candidate position
                if can<1 and can>0:#check if x stays inside [0,1] (for simplicity...)
                    break
        else:
            can=np.random.normal(x,eps)   #candidate position
        func_can=Target(can)



        a = min([1.,func_can/func_x]) #acceptance probability for symmetric prior
        u = np.random.rand()

        if u < a :
            x = can
            _n_b+=1
            _n_t+=1
            if _n_b>=burn_in and _n_t>thinning:

                _n_t=0
                accepted.append(x)#accept sample


        func_x=Target(can)
    return np.array(accepted)




#run Metropolis
accepted=Metropolis(Target=func,xin=1,N=250000,eps=0.01,burn_in=5000,thinning=10)
_len=len(accepted)
print _len

#===========================================================================================================================================#
#plot the autocorrelation function (ACF) (use it to determine the thinning)
_ACF=False #set True to see the plot
if _ACF:

    def ACF(X,N,n=5):#returns the first N ACFs
        _mu=np.mean(X)
        _len=len(X)

        if N>_len:
            N=_len

        _g=lambda k:np.sum([(X[i]-_mu)*(X[i+k]-_mu) for i in np.arange(1,_len-k)])
        acf=[_g(k) for k in np.arange(0,N,n)]
        return np.array(acf)/_g(0)

    N=51

    if N>_len:
        N=_len
    n=1

    acf=ACF(accepted,N,n)
    print np.mean(acf[10:]),np.sqrt(np.var(acf[10:],ddof=1))
    #acf=ACF(VF(accepted),N,n)
    plt.plot(np.arange(0,N,n),acf)
    plt.scatter(np.arange(0,N,n),acf,color=(0.1,0.1,0.1,1))
    plt.show()
#===========================================================================================================================================#

#===========================================================================================================================================#
#traceplot of x (use it to determine burn_in).
_trace=False #set True to see the plot
if _trace:
    plt.plot(np.arange(_len), accepted )
    plt.xscale('log')
    plt.show()
#===========================================================================================================================================#


#===========================================================================================================================================#
#break the accepted in bins of NB length and plot the variance for a various number of bins.
_NOB=False #set True to see the plots
if _NOB:

    means=[]
    vars=[]
    NBs=[]

    _len=len(accepted)
    for k in np.arange(0,50):
        NB=int(2**k)#batch length
        bins=int(_len/float(NB))
        if bins<2:
            break

        print r'Points per bin=', NB ,r'No. bins=', bins, r'Total points=',NB*bins

        #batch_means= [ np.mean([ func(accepted[batch*NB+i]) for i in np.arange(NB) ])  for batch in np.arange(bins)]
        batch_means= [ np.mean([ accepted[batch*NB+i] for i in np.arange(NB) ])  for batch in np.arange(bins)]
        means.append(np.mean(batch_means))
        vars.append( np.var(batch_means,ddof=1))



        #NBs.append(bins)
        NBs.append(NB)

    fig, ax = plt.subplots(nrows=2, ncols=1,figsize=(15, 5))

    ax[0].plot( NBs,vars )
    ax[0].scatter( NBs,vars,color=(0.1,0.1,0.1,1) )
    ax[0].set_yscale('log')
    ax[0].set_xscale('log')

    ax[1].plot( NBs,means )
    ax[1].scatter( NBs,means )
    ax[1].set_xscale('log')

    plt.show()
#===========================================================================================================================================#

















#
