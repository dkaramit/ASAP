import numpy as np
import matplotlib.pyplot as plt


N_steps=100
eps=.01
wx=[]
wy=[]


for i in range(20):
    x0=np.random.rand()
    y0=np.random.rand()

    for i in np.arange(N_steps):
        can_x=x0
        can_y=y0
        while True:
            x0=can_x+(np.random.rand()*2-1)*eps
            y0=can_y+(np.random.rand()*2-1)*eps
            if x0>0 and x0<1 and y0>0 and y0<1:
                break

        wx.append(can_x)
        wy.append(can_y)


plt.plot(wx,wy,'b--')
plt.show()
