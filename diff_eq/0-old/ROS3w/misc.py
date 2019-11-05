from numpy import array, eye, max, arange, dot, zeros_like,argmax,zeros,imag,abs
###----------------------break complex equations to real and imaginary matrices.

def pivot_matrix(A):
    """Returns the pivoting matrix (P--permutation of rows) for A, so that 
    the largest element of each column is in the diagonal."""
    n = len(A)
    # Create an identity matrix, (permutation matrix)
    P = eye(n, dtype=float)
    # Rearrange the P such that the largest element of
    # each column of A is placed on the diagonal of of A
    
    
    for col in arange(n):
        tmp_c=array([ abs(A[i][col]) for i in arange(col, n)])
        arg_max = argmax(tmp_c)+col
        if arg_max != col:
            
            P[col], P[arg_max] = P[arg_max].copy(), P[col].copy()

    return P



def LUP_dec(M,pivot=True):
    n=len(M)
    if pivot:
        P=pivot_matrix(M)
    else:
        P=eye(n)
    A=dot(P,M)
    
    L=zeros_like(A)
    U=zeros_like(A)
    # Perform the LU Decomposition                                                                                                                                                                                                                     
    for j in range(n):
        # All diagonal entries of L are set to unity                                                                                                                                                                                                   
        L[j][j] = 1.0

        for i in range(j+1):
            s1 = sum( U[k][j] * L[i][k] for k in range(i) )
            
            U[i][j] = A[i][j] - s1

        for i in range(j, n):
            s2 = sum(U[k][j] * L[i][k] for k in range(j))
            L[i][j] = (A[i][j] - s2) / U[j][j]
            
    return L,U,P



#Solve Ly=c, Ux=y
def Solve_LU(L,U,P,c):
    #this solves P*A*x=P*c, x is also the solution to A*x=c
    n=len(c)
    b=dot(P,c)
    d=zeros_like(b)
    x=zeros_like(b)
    
    d[0]=b[0]
    for i in range(1,n):
        d[i]=b[i]-sum(  [L[i][j]*d[j] for j in range(i)] )

    x[n-1]  = d[n-1]/U[n-1][n-1]  
    for i in range(n-2,-1,-1):
        x[i]=(d[i]-sum( [U[i][j]*x[j] for j in  range(i+1,n)] ))/U[i][i]

    return x


def deriv(func,x,h=1.e-8):
    return imag(func(x+1j*h)/h)

def jacobian(Funcs,x,h=1.e-8):
    n=len(x)
    x=array(x)
    J=zeros([n,n])
    for i in range(n):
        for j in range(n):
     
            fi=lambda _y:Funcs( [x[i] if xi!=j else _y for xi in range(n)] )[i]
            J[i][j]=deriv(fi,x[j],h)
    
    return J

###############---define parameters
gam=4.358665215084e-01

a21= 6.666666666666e-01
gam21= 3.635068368900e-01
a31= 6.666666666666e-01
gam31=-8.996866791992e-01
a32= 6.666666666666e-01
gam32=-1.537997822626e-01

b1= 2.500000000000e-01
bh1= 7.467047032740e-01
b2= 2.500000000000e-01
bh2= 1.144064078371e-01
b3= 5.000000000000e-01
bh3= 1.388888888888e-01







###############---define parameters with respect to g's
p11=1.
p22=1.
p33=1.
p21=-gam21/gam
p31=-gam31/gam +gam32*gam21/gam**2
p32=-gam32/gam


q1=b1+b2*p21+b3*p31
q2=b2+b3*p32
q3=b3

qh1=bh1+bh2*p21+bh3*p31
qh2=bh2+bh3*p32
qh3=bh3

r21=a21
r31=a31+a32*p21
r32=a32

s2=gam21
s3=gam31+gam32

c2=a21
c3=a31+a32

    