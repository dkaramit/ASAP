import numpy as np


def func(x):
    return np.exp(-np.sum(x)/50.)

def MC(func,Ndim,Nt=1000):
    s=[]
    for i in range(Nt):
        x=np.random.rand(Ndim)
        s.append(func(x))
    return np.mean(s), np.var(s,ddof=1)/Nt



Ndim=100
N_tot=100
N_batches=1000
I=[]
V=[]
for i in np.arange(N_batches):
    _I,_V=MC(func,Ndim,N_tot)
    I.append(_I)
    V.append(_V)

integral=np.mean(I)
sigma= np.sqrt(np.mean(V))#the variance of the estimator I is sigma^2= 1/N_batches sum_i var(I_i) (the mean var(I_i))
print 'integral', integral
print 'sigma', sigma


chi=(I-np.mean(I))/np.sqrt(V)
print 'chi^2/dof',np.sum(chi**2)/(N_batches-1.)







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
plt.plot(x,y)


plt.hist( np.random.normal(integral, sigma , N_batches),color='black',density=True)
plt.hist(I,alpha=0.5,color='c',density=True)

plt.show()
