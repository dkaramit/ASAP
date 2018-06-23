import numpy as np
import matplotlib.pyplot as plt

def Gauss(x,mu,sigma):
    return np.exp(-(x-mu)**2/(2*sigma**2))*1/np.sqrt(2*np.pi * sigma**2)

def func(x):
    #return np.exp(-(x-0.3)**2/(2*0.01**2))*np.sin(x-0.32)**2
    return np.exp(-(x-0.5)**2*100)*np.sin(9*(x-0.42))**2
    #return np.sin(6*(x-0.2))**2

N = 500000
eps = .01

samples = []

Prior=lambda x,mu: Gauss(x,mu,eps)#I choose as proposal distribution the gaussian (see the step variable)
center=0#we can make the sampler irreversible by shifting the proposal (be careful with this. it may not converge at all...)


x=0.#np.random.rand()
func_x=func(x)
for i in xrange(N):



    while True:

        step=np.random.normal(center,eps)

        if x+step<1 and x+step>0:#check if x stays inside the cube [0,1]^dim (I want the point in here for integration)
            break

    can=x + step #candidate

    func_can=func(can)





    a = min([1.,func_can/func_x*( Prior(x,can+center)/Prior(can,x+center) )]) #acceptance probability for non-symmetric prior
    #a = min([1.,func_can/func_x]) #acceptance probability for symmetric prior
    u = np.random.rand()
    if u < a :
        x = can
        samples.append(x)

    func_x=func(can)



print len(samples)

fig, ax = plt.subplots(nrows=1, ncols=2,figsize=(10, 5))

x=np.array([i for i in np.arange(0,1,0.001) ])
y=func(x)
mm=np.max(np.histogram(samples,bins=40)[0])
mmm=np.max(y)
ax[0].plot(x,y/mmm*mm,'c--')
ax[0].hist(samples,bins=40,histtype='barstacked')


ax[1].plot(samples,'c--')

plt.show()













#
