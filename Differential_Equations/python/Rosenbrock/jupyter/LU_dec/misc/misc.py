def Abs(x):
    '''
    Input x  and you'll get the abs.
    '''
    #Not the best way, but it is an easy way to not use numpy
    return (x**2)**0.5

#========================================================================================================================================#    
def ind_max(row,N):
    '''
    Find the index of the maximum of a list (row) of lentgth N.
    '''
    _in=0
    _max=row[0]
    i=0
    while i<N:#the end of the row should be included (convension in how I use LUP..)
        if row[i]>_max:
            _max=row[i]
            _in=i
        i+=1
            
    return _in

#========================================================================================================================================#
def Sum(List,N):
    '''
    Calculates the sum of a List of size N
    '''
    s=0
    for i in range(N):
        s+=List[i]
    return s
#========================================================================================================================================#
def index_swap(A,index_1,index_2):
    '''
        index_swap takes an array and interchanges 
         A[index_1] with A[index_2].
         
         Example:
             A=[0,1,2,3]
             index_swap(A,0,2)
             A
             >>[2, 1, 0, 3]
    '''
    
    tmp=A[index_1]
    A[index_1]=A[index_2]
    A[index_2]=tmp
    
    
def apply_permutations_vector(A,P,N):
    '''
    Applies the permutations given by P from LUP
    to a list A of length N, and returns the result.
    Example:
    A=[1,2,5,8,3]
    P=[2,4,0,3,1]

    apply_permutations_vector(A,P,5)
    >>[5, 3, 1, 8, 2]
    '''
    #that is, you make a list like this (P basically gives you the indices of A):)
    
    Ap=[A[ P[i] ] for i in range(N)]

    return Ap
    
def apply_permutations_matrix(M,P,N):
    '''
    Applies the permutations given by P from LUP
    to a N*N array M of length N, and returns the result.
    
    M=[
    [ 0,  2,  2 , 3 , 5],
    [-3, -1,  1 , 5 , 9],
    [ 1, -1,  1 , 4 , 7],
    [ 1, -1,  1 , 0 , 2],
    [ 1, -1,  1 , 0 , 3]
    ]

    P=[2,0,1,4,3]

    apply_permutations_matrix(M,P,5)
    >>[
      [ 1, -1, 1, 4, 7],
      [ 0,  2, 2, 3, 5],
      [-3, -1, 1, 5, 9],
      [ 1, -1, 1, 0, 3],
      [ 1, -1, 1, 0, 2]
      ]
    '''
    Mp=[ [M[ P[i] ][j]for j in range(N)] for i in range(N) ]
    

    return Mp
#========================================================================================================================================#
