import numpy as np
import matplotlib.pyplot as plt

def func(x):
    return np.sin(x)**2

def deriv(x,step):
    return (func(x+step)-func(x-step))/(2*step)

N_steps=5000
eps=0.001

x=np.random.rand()
walk=[x]
for i in np.arange(N_steps):
     x=x-deriv(x,eps)*eps
     walk.append(x)



print walk
plt.scatter(np.arange(len(walk)),walk,s=1,color='black')
plt.show()
