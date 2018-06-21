import numpy as np
import matplotlib.pyplot as plt


def func(x):
    #return np.exp(-(x-0.2)**2/(2*0.01**2))*1/np.sqrt(2*np.pi * 0.01**2)
    return np.exp(-(x-0.3)**2/(2*0.01**2))*np.sin(x-0.32)**2


N = 5000
eps = .001

samples = []
all_steps=[]


x=np.random.rand()
func_x=func(x)
for i in xrange(N):



    while True:
        step=(np.random.rand()*2-1)*eps
        if x+step<1 and x+step>0:#check if x stays inside the cube [0,1]^dim (I want the point in here for integration)
            break

    can=x + step #candidate

    func_can=func(can)



    all_steps.append(can)


    a = min([1.,func_can/func_x]) #acceptance probability

    u = np.random.rand()
    if u < a :
        x = can
        samples.append(x)

    func_x=func(can)







'''
x=np.array([i for i in np.arange(0,1,0.001) ])
y=func(x)
mm=np.max(np.histogram(samples,bins=40)[0])
mmm=np.max(y)
plt.plot(x,y/mmm*mm,'c--')
plt.hist(samples,bins=40,histtype='barstacked')
'''
plt.plot(all_steps,'b--')
plt.plot(samples,'c--')

plt.show()













#
