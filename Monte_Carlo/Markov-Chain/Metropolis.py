
import numpy as np
import matplotlib.pyplot as plt
_tiny=1.e-80


def func(x):
    #return np.exp(-200*(x[0]-0.3)**2)*np.exp(-200*(x[1]-0.1)**2)+np.exp(-200*(x[1]-0.7)**2)*np.exp(-500*(x[0]-0.7)**2)+\
    #       np.exp(-200*(x[0]-0.1)**2)*np.exp(-200*(x[1]-0.7)**2)

    #return np.sin((x[0]-0.5)*10*np.pi)**2+np.cos((x[1]-0.5)*10*np.pi)**2
    return np.cos(100*np.pi*np.sum((x-0.5)**2.) )**2*np.exp(-20.*np.sum((x-0.5)**2))
    #return np.exp( -100*np.abs(x[0]-x[1]) )

x=[0,0]
Dim=len(x)#get the number of variables automatically (it's stupid but I sometimes I want to give x and not Dim)
#for i in range(Dim):#start at a random point
#    x[i]= np.random.rand()



n = 10000
eps = .1
batches=20


x=np.array(x)




samples = []


for run_d in range(batches):

    for i in range(Dim):#start each batch at a random point
        x[i]=  np.random.rand()

    func_x=func(x)
    for i in range(1,n):

        can=[]
        for d in range(Dim):
            while True:
                step=(np.random.rand()*2-1)*eps

                if x[d]+step<1 and x[d]+step>0:#check if x stays inside the cube [0,1]^dim (I want the point in here for integration)
                    break

            can.append(x[d] + step) #candidate
        can=np.array(can)
        func_can=func(can)




        a = min([1.,func_can/func_x]) #acceptance probability

        u = np.random.rand()
        if u < a :
            x = can
            samples.append(x)

        func_x=func(can)





print( len(samples))

x=[i[0] for i in samples]
y=[i[1] for i in samples]
plt.scatter(x,y,s=.1,color='black')
#plt.plot(x,y,'b--')
#plt.hist2d(x,y,bins=50)
plt.show()
