import numpy as np

def func(x,ND):
#x is a vector (list) in this function. ND is the number of dimensions.
#It is good to have this information available inside the function!
    #return  np.cos(np.prod(x)*4)
    return (np.sum(x)-0.2)**3



Ndim=10#number of dimensions (good convergence for large Ndim)
N_tot=5000
sample=np.random.rand(N_tot,Ndim)
F_sample=[func(i,Ndim) for i in sample]
abs_F_sample=[ np.abs(func(i,Ndim)) for i in sample]
_max=np.max(abs_F_sample)


I=0
N_acc=0
w=[]
abs_w=[]
for i in np.arange(N_tot):
    _tmp_rand=np.random.rand()
    wi=F_sample[i]
    abs_wi=abs_F_sample[i]
    if _tmp_rand<=abs_wi/_max:
        N_acc+=1
        w.append(wi)
        abs_w.append(abs_wi)


norm=float(N_acc)/float(N_tot)*_max



I=np.mean( w/(abs_w/norm) )
print (I)
#Cannot find an estimator for the variance. In fact, this proccedure seems to be
# one experiment. So I can do this many times, i.e. moving to batches!
