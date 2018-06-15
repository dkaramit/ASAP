import numpy as np

def func(x,ND):
#x is a vector (list) in this function. ND is the number of dimensions.
#It is good to have this information available inside the function!
    #return  np.cos(np.prod(x)*4)
    return (np.sum(x)-0.2)/100.


def run_batch(f,ND,integral,variance,N_tot_batch=1000):
    sample=np.random.rand(N_tot_batch,ND)
    F_sample=[func(i,ND) for i in sample]
    abs_F_sample=[ np.abs(func(i,ND)) for i in sample]
    _max=np.max(abs_F_sample)

    I=0
    N_acc=0
    w=[]
    abs_w=[]
    for i in np.arange(N_tot_batch):
        _tmp_rand=np.random.rand()
        wi=F_sample[i]
        abs_wi=abs_F_sample[i]
        if _tmp_rand<=abs_wi/_max:
            N_acc+=1.
            w.append(wi)
            abs_w.append(np.abs(wi))

    norm=N_acc/float(N_tot_batch)*_max
    _I=np.mean( w/(abs_w/norm) )

    integral.append(_I)



I=[]
sigma=[]
N_batches=250
N_per_batch=50
Ndim=50
for i in range(N_batches):
    run_batch(func,Ndim,I,N_per_batch)


integral=np.mean(I)#The I's are still an average, so the central limit theorem still applies (appriximately, since N_acc is a random number).
sigma=np.sqrt(np.var(I,ddof=1))#since I cannot calculate the variance of one batch, I use this to estimate the variance.
print integral, sigma




plot=True
if not plot:
    exit()

import matplotlib.pyplot as plt


def _gauss(x,mu,sigma):
    return 1/(2*np.pi*sigma**2)**(1/2.)*np.exp(-(x-mu)**2/(2*sigma**2))
gauss=np.vectorize(_gauss)



_bins=10
mm=1.*np.max( np.histogram(np.random.normal(integral, sigma , N_batches),bins=_bins )[0])
x=np.arange(integral-3*sigma,integral+3*sigma,6*sigma/1000.)
y=gauss(x,np.mean(I),sigma)
plt.plot(x,y/np.max(y)*mm)


plt.hist( np.random.normal(integral, sigma , N_batches),color='black',bins=_bins)
plt.hist(I,color=(1,0.5,0,0.7),bins=_bins)

plt.show()
