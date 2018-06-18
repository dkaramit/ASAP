import numpy as np
import matplotlib.pyplot as plt

def func(x,y):
    return np.exp(-(x-0.5)**2*2500)*np.exp(-(y-0.5)**2*100)


N_steps=7000
eps=.05
wx=[]
wy=[]


for i in range(10):
    x0=np.random.rand()
    y0=np.random.rand()

    for i in np.arange(N_steps):
        can_x=x0
        can_y=y0
        while True:
            x0=can_x+(np.random.rand()*2-1)*eps
            y0=can_y+(np.random.rand()*2-1)*eps
            if x0>0 and x0<1 and y0>0 and y0<1\
            and func(x0,y0)/func(can_x,can_y)>0.5:#random walk in [0,1] 2D cube, towards the maximum (hence func(x0,y0)/func(can_x,can_y)>0.5)
                break

        wx.append(can_x)
        wy.append(can_y)


plt.scatter(wx,wy,s=1,color='black')
plt.show()
