from .misc.misc import *


def LUP(M,N,_tiny=1e-20):
    U=[  [ M[i][j] for j in range(N)] for i in range(N) ]
    L=[  [ 0 if i!=j else 1 for j in range(N)] for i in range(N) ]
    #this is the "permutation vector". if it is e.g. [2 1 0 3] it means you make 0<->2
    P=[  i for i in range(N) ]
    
    for k in range(1,N):
        for i in range(k,N):
            #find the index of the maximum in column
            _col=[Abs(U[_r][k-1]) for _r in range(k-1,N)]
            
            #find the index of the maximum of _col
            # notice that the length of _col is N-(k-1)
            len_col=N-(k-1)
            pivot=ind_max( _col ,len_col) + k - 1 #convert the index of _col (it has a length of len_col) to the index of  a row of U   
            
            ##################################################
            #this was in LU_julia (instead of "<_tiny"  it had "== 0").
            #if you remove it, then you get a lot of infinities
            #it has to do with the fact that if U[pivot][k-1] <_tiny , then U[k-1][k-1] will be a zero, 
            #L[i][k-1] explodes. 
            #You are allowed to skip this i, then, because if U[pivot][k-1] <_tiny , then all U[i][k-1] are small!
            #Check that this is true by  uncommenting print(_col)
            if Abs(U[pivot][k-1]) < _tiny  :         
                #print(_col)
                break
            ###################################################
            #if the maximum is not at k-1, swap!
            if pivot != k-1 : 
                # Permute rows k-1 and pivot in U
                
                index_swap(P,k-1,pivot)
                
                tmpU=[U[k-1][_r] for _r in range(k-1,N)]
                
                #print(U)
                for _r in range(k-1,N):
                    U[k-1][_r]=U[pivot][_r]
                #print(U)
                for _r in range(k-1,N):
                    U[pivot][_r]=tmpU[_r-(k-1)]#again we have to convert the index of tmpU
                #print(U)
                #print("=========================")
                tmpL=[L[k-1][_r] for _r in range(k-1)]
                #print(L)
                for _r in range(k-1):
                    L[k-1][_r]=L[pivot][_r]
                #print(L)
                for _r in range(k-1):
                    L[pivot][_r]=tmpL[_r]
                    
                #print(L)
                #print("========================")
                
            L[i][k-1]=U[i][k-1]/U[k-1][k-1]
           
        
            for j in range(k-1,N):
                U[i][j]=U[i][j]-L[i][k-1]*U[k-1][j]

                
    return L,U,P
        
#========================================================================================================================================#
