import numpy as np
import scipy.integrate as nint


def func(x):
    return np.sin(x)**2+np.cos(x**2)


def MC_1D(func,Nt=1000):
    s=[]
    for i in range(Nt):
        x=np.random.rand()
        s.append(func(x))


    #Remember that the variance of the estimator for the mean (\bar{x}=1/N /sum x_{i}) is Var[\bar{x}]=\sigma_{x}^2/N
    #(N is the sample size, and x_{i} a certain outcome or the r.v. x).
    #The variance of x itself (\sigma_{x}^2) can be estimated by S^{2}=1/(N-1) sum_{i} x_{i}.
    return np.mean(s), np.var(s,ddof=1)/Nt

N_tot=1000
N_batches=300
I=[]
V=[]
for i in np.arange(N_batches):
    _I,_V=MC_1D(func,N_tot)
    I.append(_I)
    V.append(_V)

integral=np.mean(I)
sigma= np.sqrt(np.mean(V))#the variance of the estimator I is sigma^2= 1/N_batches sum_i var(I_i) (same case as the discussion in MC_1D)
print( 'integral', integral)
print( 'sigma', sigma)



chi=(I-np.mean(I))/np.sqrt(V)
print( 'chi^2/dof',np.sum(chi**2)/(N_batches-1.))







plot=True
if not plot:
    exit()


import matplotlib.pyplot as plt


def _gauss(x,mu,sigma):
    return 1/(2*np.pi*sigma**2)**(1/2.)*np.exp(-(x-mu)**2/(2*sigma**2))
gauss=np.vectorize(_gauss)




mm=1.*np.max( np.histogram(np.random.normal(integral, sigma , N_batches),normed=False)[0])
x=np.arange(integral-3*sigma,integral+3*sigma,6*sigma/1000.)
y=gauss(x,np.mean(I),sigma)
plt.plot(x,y/np.max(y)*mm)


plt.hist( np.random.normal(integral, sigma , N_batches),color='black')
plt.hist(I,alpha=0.5,color='c')

plt.show()
