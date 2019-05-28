'''
This is an example of how N-dimensional Metropolis works.
Keep in mind that you might want to run Metropolis with various starting points (xin), in order to
have correct convergence.
'''
import numpy as np
import matplotlib.pyplot as plt

def func(x):
    return np.exp(-(1000.*(x[0]-0.8)**2+500.*(x[1]+0.2)**2 +1800.*(x[2]-0.3)**2))



##############################################################################
def Metropolis(Target,xin,N=10000,eps=[],burn_in=0,thinning=10,_fixed_interval=[] ):
    '''
    burn_in (integer): do not store the first 'burn_in' accepted steps (the first few steps could be in a region with low probability).
    thinning (integer): store 1 every 'thinning' accepted steps (makes the sample more independent).
    _fixed_interval (list of Dim tuples): if keeps x[i] in [_fixed_interval[i][0],_fixed_interval[i][1]].
    '''

    Dim=len(xin)
    accepted=[]

    _min=[min(_fixed_interval[d]) for d in range(Dim)]
    _max=[max(_fixed_interval[d]) for d in range(Dim)]

    _n_b=0
    _n_t=0

    x=xin[:]

    func_x=Target(x)
    for i in np.arange(N):

        can=[]
        for d in range(Dim):
            while True:
                #step=(np.random.rand()*2-1)*eps[d]
                step=np.random.normal(0,eps[d])

                if x[d]+step>_min[d] and x[d]+step<_max[d]:#check if x stays inside the cube [0,1]^dim (I want the point in here for integration)

                    break

            can.append(x[d] + step) #candidate

        func_can=Target(can)


        if func_x<1e-50:
            a=1
        else:
            a = min([1.,func_can/func_x]) #acceptance probability for symmetric prior
        u = np.random.rand()

        if u < a :
            x = can[:]
            _n_b+=1
            _n_t+=1
            if _n_b>=burn_in and _n_t>thinning:

                _n_t=0
                accepted.append(x)#accept sample


        func_x=Target(can)
    return np.array(accepted)
##############################################################################

##############################################################################
#run Metropolis
#accepted=Metropolis(Target=func,xin=[-0.,-0.5,0.1],N=10000,eps=[0.01,0.02,0.03],burn_in=0,thinning=0,_fixed_interval=[(0,1),(-1,0),(0,1)])#run this first
accepted=Metropolis(Target=func,xin=[-0.,-0.4,0.1],N=500000,eps=[0.01,0.04,0.02],burn_in=50000,thinning=80,_fixed_interval=[(0,1),(-1,0),(0,1)])#then run this
_len=len(accepted)
_Dim=len(accepted[0])
print (_len)
##############################################################################


#=================================== Plots ===================================#
#fig, ax = plt.subplots(nrows=2, ncols=2,figsize=(14,7),sharex=False)
fig=plt.figure(figsize=(14,7))
fig.subplots_adjust(bottom=0.025, left=0.025, top = 0.975, right=0.975)
#=============================================================================#
#traceplot of x (use it to determine burn_in).
print ('============== Trace-plots ===============')

sub = fig.add_subplot(2, 2, 1)
for d in range(_Dim):
    sub.plot(np.arange(_len), [i[d] for i in accepted  ] ,label='${}{}$'.format('x_',str(d)) )
    sub.legend(bbox_to_anchor=(1, 1),borderaxespad=0.,ncol=1,loc=2)
sub.set_xscale('log')
sub.set_xlabel('step')
sub.set_ylabel('x position')
sub.yaxis.set_label_coords(0.05, 0.85)
sub.xaxis.set_label_coords(0.5, 0.05)

print ('Done!')
#=============================================================================#

#=============================================================================#
#plot the autocorrelation function (ACF) (use it to determine the thinning)
print ('============== ACF ===============')
def ACF(X,N,n=5):#returns the first N ACFs
    _mu=np.mean(X)
    _len=len(X)

    if N>_len:
        N=_len

    _g=lambda k:np.sum([(X[i]-_mu)*(X[i+k]-_mu) for i in np.arange(1,_len-k)])
    acf=[_g(k) for k in np.arange(0,N,n)]
    return np.array(acf)/_g(0)

N=51#you can change this in order to see more steps
if N>_len:
    N=_len
n=1

acf= [ ACF([i[d] for i in accepted],N,n) for d in range(_Dim) ]
print( 'ACF mean and variance for lag>10')
for i in range(_Dim):
    print( i,':', np.mean(acf[i][10:]),np.sqrt(np.var(acf[i][10:],ddof=1)))

sub = fig.add_subplot(2, 2, 2)

for d in range(_Dim):
    sub.plot(np.arange(0,N,n),acf[d],label='${}{}$'.format('x_',str(d)) )
    sub.scatter(np.arange(0,N,n),acf[d],color=(0.1,0.1,0.1,1))
    sub.legend(bbox_to_anchor=(1, 1),borderaxespad=0.,ncol=1,loc=2)

sub.set_xlabel('lag')
sub.set_ylabel('ACF')
sub.yaxis.set_label_coords(0.05, 0.5)
sub.xaxis.set_label_coords(0.05, 0.05)
print ('Done!')
#=============================================================================#

#=============================================================================#
#Plot sigma and mean of func (or x if you uncomment it) for various binning.
#break the accepted in bins of NB length and plot the variance for a various number of bins.
print ('============== Bin Means ===============')

means=[]
vars=[]
_points=[]
_bins=[]
_len=len(accepted)
for k in np.arange(0,50):
    points=int(2**k)#batch length
    bins=int(_len/float(points))
    if bins<5:
        break

    print (r'Points per bin=', points ,r'No. bins=', bins, r'Total points=',points*bins)

    batch_means= [ np.mean([ func(  [accepted[batch*points+i][d] for d in np.arange(_Dim)]) for i in np.arange(points) ])  for batch in np.arange(bins)]

    means.append(np.mean(batch_means))
    vars.append( np.sqrt(np.var(batch_means,ddof=1)))


    _points.append(points)
    _bins.append(bins)


sub = fig.add_subplot(2, 1, 2)


sub.plot( _points,means ,label='Mean')
sub.plot( _points,np.array(means)+np.array(vars),color=(1,0,0,1),label='Error' )
sub.legend(bbox_to_anchor=(0.8, 1),borderaxespad=0.,ncol=1,loc=2)
sub.plot( _points,np.array(means)-np.array(vars),color=(1,0,0,1))
sub.scatter( _points,means,color=(0,0,0,1) )
#sub.set_yscale('log')
sub.set_xscale('log')
sub.set_ylabel('Mean of func')
sub.set_xlabel('No. points per bin')
sub.yaxis.set_label_coords(0.02, 0.5)
sub.xaxis.set_label_coords(0.5, 0.05)


#No. points ticks
sub.xaxis.set_tick_params(which='major',labelbottom=True,labeltop=False,bottom=True,top=False)

#the following is for tick formatting (just for fun)
def format_fn(tick_val, tick_pos):
    return tick_val
sub.xaxis.set_major_formatter(plt.FuncFormatter(format_fn) )
from matplotlib import ticker
sub.xaxis.set_major_locator(ticker.FixedLocator(_points))
sub.xaxis.set_minor_locator(ticker.FixedLocator([]))


#No. bins ticks
_xx=sub.twiny()
_xx.scatter(_points,means,color='' )
_xx.xaxis.set_tick_params(labelbottom=False,labeltop=True,bottom=False,top=True)

#the following is for tick formatting (just for fun)
def format_fn(tick_val, tick_pos):
    try:
        bins=int(_len/float(tick_val))
        return bins
    except:
        return ''
_xx.xaxis.set_major_formatter(plt.FuncFormatter(format_fn))
_xx.set_xlabel('No. bins')
_xx.xaxis.set_label_coords(0.5, 0.95)



print ('Done!')
#=============================================================================#
plt.tight_layout()
fig.suptitle(str(_Dim)+'D-Metropolis:'+str(_len)+' points',y=1)


plt.show()
#=============================================================================#






#=============================================================================#
plots=False
if plots:
    plot=(0,1)#choose which x's to plot

    pp=[[i[j] for i in accepted] for j in plot]

    plt.scatter(pp[0],pp[1],s=.3,color='black')

    plt.show()
#=============================================================================#




#
