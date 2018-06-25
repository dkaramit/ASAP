'''
Things to do:
-non-overlaping batches
-variance of a statistic (use func for this example)
-Give the otion to specify burn-in perid and thinning
-N-dimension generalisation
'''







import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate


def Gauss(x,mu,sigma):
    return np.exp(-(x-mu)**2/(2*sigma**2))*1/np.sqrt(2*np.pi * sigma**2)


def func(x):
    #return (x-0.5)**2/(0.1**2)
    #return Gauss(x,0.1,0.02)
    return np.exp(-(x-0.2)**2*1000)*np.sin(50*(x-0.2))**2
    #return np.sin(6*(x-0.2))**2


N = 100000
eps = 0.01
samples = []
samples_Times=[]
candidates=[]

#example of prior (usually referred to as q(x|x')). (for reversible M-H the acceptance prob. is independent of q)
#Prior=lambda x,mu: Gauss(x,mu,eps)#I choose as proposal distribution a gaussian (see the can variable)

x=1#np.random.rand()
func_x=func(x)

N_sam=0
N_can=0
acceptance_rate=[]
_fixed_interval=True
for i in xrange(N):

    if _fixed_interval:
        while True:

            #can=np.random.normal(x,eps)# Gaussian candidate position
            can=(np.random.rand()*2-1)*eps+x# Uniform candidate position
            #can=np.random.rand()# independent candidate position (not good)
            if can<1 and can>0:#check if x stays inside [0,1] (for simplicity...)
                break
    else:
        can=np.random.normal(x,eps)   #candidate position

    func_can=func(can)
    candidates.append(can)
    N_can+=1.
    #a = min([1.,( func_can/func_x )*( Prior(x,can)/Prior(can,x) )]) #acceptance probability for general prior
    a = min([1.,func_can/func_x]) #acceptance probability for symmetric prior
    u = np.random.rand()
    if u < a :
        x = can
        samples.append(x)
        samples_Times.append(i)
        N_sam+=1.
        acceptance_rate.append(N_sam/N_can)


    func_x=func(can)






#=======================================================================================================#
#use func to calculate autocorrelation time etc. (because I don't want to search for an other statistic)
VF=np.vectorize(func)
if True:
    #use this to calculate the running mean of func.
    def cummean(V):
        _len=len(V)
        _s=0
        _c=[]
        for i in np.arange(_len):
            _s+=V[i]
            _c.append(_s/(i+1))
        return _c


    plt.plot(samples_Times,cummean(VF(samples)))#what happens to the running mean?? (can I use it to "define" a burn in?)
    plt.show()

#=======================================================================================================#
#the histogram is normalized:
#hist, bin_edges = np.histogram(samples,bins=100,density=True)
#print np.sum(hist * np.diff(bin_edges))

plots=True
if plots:
    fig, ax = plt.subplots(nrows=2, ncols=2,figsize=(15, 5))
    x=np.array([i for i in np.arange(0,1,0.0001) ])
    y=VF(x)
    norm=integrate.quad(func,0,1)[0]#normalization of func
    y=y/norm
    ax[0][0].plot(x,y,'c--')
    ax[0][0].hist(samples,bins='auto',density=True)#it would only work for normalized func...
    ax[0][1].plot(samples_Times,acceptance_rate,color=(0.5,0.5,0.5,1),linestyle='--')
    ax[1][0].plot(samples_Times,samples,'c--')
    ax[1][1].plot(candidates,'b--')

    plt.show()













#
