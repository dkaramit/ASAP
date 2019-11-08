from .misc.misc import *



def Solve_LU(L,U,P,b,N):
    '''
    This solves M*x=b
    Input:
    L,U,P= LUP decomposition of M, which is the output of the function LUP.

    b=the right hand side of the equation
    N=the number of equations

    For examples and explanations see the jupyter notebooks on LU decomposition.
    You can also see the comments in the code.
    '''
    #I know that this uses more memory than what it needs, but I want to keep b as is.
    #(in C++ I will make it a bit beter ;) )
    b=apply_permutations_vector(b,P,N)
    d=[0 for i in range(N) ]
    x=[0 for i in range(N) ]

    d[0]=b[0]
    for i in range(1,N):
        d[i]=b[i]-Sum(  [L[i][j]*d[j] for j in range(i)],i )

    x[N-1]  = d[N-1]/U[N-1][N-1]  
    for i in range(N-2,-1,-1):
        x[i]=(d[i]-Sum( [U[i][j]*x[j] for j in  range(i+1,N)],N-(i+1) ))/U[i][i]

    b=apply_permutations_vector(b,P,N)#return b as it was
    return x
#========================================================================================================================================#
