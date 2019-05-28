'''
This is a 2-dimensional example of the rejection method for
better monte carlo estimation. It works as the 1-D case (see 1-D_ARMC.py).
We write this code, in order for the user to understand how the
N-dimensional case is implimented.

As you can see, the 2-D case is almost identical to the 1-D.
The only difference is in #1-4
'''
import numpy as np

def func(x,y):#1
    return y*np.sin(10*(x+1))

N_tot=5000

sample=np.random.rand(N_tot,2)#2

F_sample=[func(i,j) for i,j in sample]#3
abs_F_sample=[ np.abs(func(i,j)) for i,j in sample]#4
_max=np.max(abs_F_sample)


I=0
N_acc=0
for i in np.arange(N_tot):
    _tmp_rand=np.random.rand()
    wi=F_sample[i]
    abs_wi=abs_F_sample[i]
    if _tmp_rand<=abs_wi/_max:
        N_acc+=1.
        I+=wi/np.abs(wi)

norm=N_acc/float(N_tot)*_max
print  (I/(N_acc/norm))
