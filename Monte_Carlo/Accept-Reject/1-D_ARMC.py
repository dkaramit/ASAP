'''
----------Acceptance-rejection Monte-Carlo for 1-D integrals------------------

Using the key point that variance is reduced if we sample according to |f(x)|,
we calculate the integral of a function in [0,1].

What we do in sort is:

1) I=\int_{0}^{1} dx f(x)=\int_{0}^{1} dx \frac{f(x)}{C*|f(x)|} C*|f(x)|, with
C=(\int_{0}^{1} dx |f(x)|)^{-1}.

2) We sample according to |f(x)|, and we calculate
    i)C=N_accepted/N_total*|f_max| (the maximum of |f(x)|)
    ii)I=1/N_accepted \sum_{i=1}^{N_accepted} \frac{f(x_i)}{C*|f(x_i)|}
'''






#For the moment I will try to use numpy as little as possible, in order to
#compare the speed of later versions.

import numpy as np
import matplotlib.pyplot as plt





#define the function to be integrated
def func(x):
    return -np.sin(5*x)*np.cos(10*x)+x**2. #good
    #return np.sin((x-0.5))*5 #not good



#define the sample size
N_tot=5000

#generate sample
sample=np.random.rand(N_tot)

#the value of the function for each sample point
F_sample=[func(i) for i in sample]

#the absolute value of the function for each sample point
abs_F_sample=[ np.abs(func(i)) for i in sample]

#the maximum of abs_F_sample in the sample
_max=np.max(abs_F_sample)

#initialize a lit to store the accepted x's and the corresponding
#(random values) for y
_accepted_x=[]
_accepted_y=[]

#initialize the integral estimator
I=0

#initialize the counter of accepted events
N_acc=0


#loop in the sample
for i in np.arange(N_tot):

    #generate a y (acceptance probability for each x)
    _tmp_rand=np.random.rand()

    #the value of func for the current sample point
    wi=F_sample[i]
    abs_wi=abs_F_sample[i]

    #if x gives a y below  abs_wi (devided by the maximum, i.e. normalized at 1,
    #for simplicity), accepte the sample point.
    if _tmp_rand<=abs_wi/_max:

        #fill the lists with the accepted results
        _accepted_x.append(sample[i])
        _accepted_y.append(_tmp_rand)

        #add one to the number of accepteed results (as a float, since we'll
        #divide with this number)
        N_acc+=1.

        #add  f(x_i)/|f(x_i)|
        I+=wi/np.abs(wi)



#this is the normalization of |f(x)|
norm=N_acc/float(N_tot)*_max

#this is the integral!
print  (I/(N_acc/norm))




plt.scatter(_accepted_x,_accepted_y)

plt.plot(np.arange(0,1,0.01),\
[np.abs(func(i))/_max for i in np.arange(0,1,0.01)] )

plt.show()
