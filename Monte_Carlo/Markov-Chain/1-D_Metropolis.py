import numpy as np
import matplotlib.pyplot as plt

def Gauss(x,mu,sigma):
    return np.exp(-(x-mu)**2/(2*sigma**2))*1/np.sqrt(2*np.pi * sigma**2)

def func(x):
    return Gauss(x,0.2,0.01)
    #return np.cos(4*(x-0.2))**2
    #return np.exp(-x)

#vectorize func for convinience
#use func to calculate autocorrelation and the mean/variance of func. In practice, one might have a physical quantity to be estimated.
VF=np.vectorize(func)



##############################################################################
def Metropolis(Target,xin,N=10000,eps=0.01,burn_in=0,thinning=10,_fixed_interval=True):
    '''
    burn_in (integer): do not store the first 'burn_in' accepted steps (the first few steps could be in a region with low probability).
    thinning (integer): store 1 every 'thinning' accepted steps (makes the sample more independent).
    _fixed_interval (boolean): if True keps x in [0,1].
    '''
    accepted=[]

    _n_b=0
    _n_t=0

    x=xin
    func_x=Target(x)

    for i in np.arange(N):
        if _fixed_interval:
            while True:

                #can=np.random.normal(x,eps)# Gaussian candidate position
                can=(np.random.rand()*2-1)*eps+x# Uniform candidate position
                if can<1 and can>0:#check if x stays inside [0,1] (for simplicity...)
                    break
        else:
            can=np.random.normal(x,eps)   #candidate position
        func_can=Target(can)


        if func_x<1e-50:
            a=1
        else:
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
##############################################################################

##############################################################################
#run Metropolis
accepted=Metropolis(Target=func,xin=0,N=50000,eps=0.01,burn_in=1000,thinning=50)
_len=len(accepted)
print _len
##############################################################################


#Plots
fig, ax = plt.subplots(nrows=2, ncols=2,figsize=(12,6),sharex=False)

#=============================================================================#
#traceplot of x (use it to determine burn_in).
ax[0,0].plot(np.arange(_len), accepted )
ax[0,0].set_xscale('log')
ax[0,0].set_xlabel('step')
ax[0,0].set_ylabel('x position')
#=============================================================================#

#=============================================================================#
#plot the autocorrelation function (ACF) (use it to determine the thinning)
def ACF(X,N,n=5):#returns the first N ACFs
    _mu=np.mean(X)
    _len=len(X)

    if N>_len:
        N=_len

    _g=lambda k:np.sum([(X[i]-_mu)*(X[i+k]-_mu) for i in np.arange(1,_len-k)])
    acf=[_g(k) for k in np.arange(0,N,n)]
    return np.array(acf)/_g(0)

N=51#you can change this in order to see more steps
if N>_len:
    N=_len
n=1

acf=ACF(accepted,N,n)
#acf=ACF(VF(accepted),N,n)
print np.mean(acf[10:]),np.sqrt(np.var(acf[10:],ddof=1))
ax[0,1].plot(np.arange(0,N,n),acf)
ax[0,1].scatter(np.arange(0,N,n),acf,color=(0.1,0.1,0.1,1))
ax[0,1].set_xlabel('lag')
ax[0,1].set_ylabel('ACF')
#=============================================================================#


#=============================================================================#
#Plot sigma and mean of func (or x if you uncomment it) for various binning.
#break the accepted in bins of NB length and plot the variance for a various number of bins.
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

    batch_means= [ np.mean([ func(accepted[batch*NB+i]) for i in np.arange(NB) ])  for batch in np.arange(bins)]
    #batch_means= [ np.mean([ accepted[batch*NB+i] for i in np.arange(NB) ])  for batch in np.arange(bins)]
    means.append(np.mean(batch_means))
    vars.append( np.sqrt(np.var(batch_means,ddof=1)))

    #NBs.append(bins)
    NBs.append(NB)

ax[1,0].plot( NBs,means )
ax[1,0].scatter( NBs,means,color=(0,0,0,1) )
ax[1,0].set_yscale('log')
ax[1,0].set_xscale('log')
ax[1,0].set_ylabel('Mean of func')
ax[1,0].set_xlabel('No. bins')

ax[1,1].plot( NBs,vars )
ax[1,1].scatter( NBs,vars,color=(0,0,0,1) )
ax[1,1].set_xscale('log')
ax[1,1].set_ylabel('Sigma of the mean')
ax[1,1].set_xlabel('No. bins')
#=============================================================================#
plt.tight_layout()

fig.suptitle('Metropolis',y=1)


plt.show()

#=============================================================================#


#=============================================================================#
#normalized Histogram of sample vs normalized target distribution
'''plots=False
if plots:
    import scipy.integrate as integrate

    fig, ax = plt.subplots(nrows=1, ncols=1,figsize=(9, 4.5))
    x=np.array([i for i in np.arange(0,1,0.0001) ])
    y=VF(x)
    norm=integrate.quad(func,0,1)[0]#normalization of func
    y=y/norm
    ax.plot(x,y,'c--')
    ax.hist(accepted,bins='auto',density=True)#it would only work for normalized func...

    plt.show()
'''#=============================================================================#


#
