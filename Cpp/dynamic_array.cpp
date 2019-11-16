#include<iostream>


// This class defines a dynamic array. For the moment it only shows how you can do it, and it only has 
// a few functions that allow you to make the very basic operations.
// It also should be obvious that it is slower than std::vector.
template<class T>
class DynArray{
    private:
        
        int len=0;
        T *A;
        
    public:
    
    // Constructor
    DynArray(){this->A=new T[0];};
    // Constructor 
    DynArray(const DynArray<T>& X){ 
        this->len=X.len;
        this->A=new T[ X.len ];  
        for (int i = 0; i < this-> len ; i++){this->A[i]=X.A[i];}
        };
        
    // Destructor
    ~DynArray(){delete[] this->A;};

    // Overload []. It should return int& in order to be able to also set values etc.
    T& operator[](int i){return A[i];}    
    
    // This function resizes A to size new_len.
    //This is done by making a temporary array (tmp) of size new_len,
    // copying A to tmp, deleting A, makig a new A of size new_len,
    // and copying tmp to A !
    //Doing this, this->A can be call as if it where size new_len from the beginning.
    void resize(int new_len){
        T *tmp=new T[new_len];// new temporary array 
        //copy all element of A to tmp 
        for (int i = 0; i < this-> len ; i++){tmp[i]=this->A[i];}
        // delete A
        delete[] this->A;
        // define new A
        this->A=new T[new_len];
        //copy elements of tmp to A
        for (int i = 0; i < this-> len ; i++){this->A[i]=tmp[i];}
        // delete tmp
        delete[] tmp;
        // update len
        this->len=new_len;
    }

// -----------------------------------------------------------------------------------
//push_back like in std::vector. Basically resize the array by 1 and puts e in the new space.
void push_back(T e){
        if(this->len == 0){ 
            this->A[0]=e;
            this->len=1; 
        }
            else {
                    this->resize(this->len + 1);
                    this->A[this->len -1]=e;
            } 
        

        }
// -----------------------------------------------------------------------------------
    //Overload =. works exactly like the copy constructor.
    void operator=(const DynArray& X)
    {
        delete[] this->A;//delete any A you may had defined in the past
        this->len=X.len;//the length becomes the length of X
        this->A=new T[ X.len ];  //new array of the same size as X
        for (int i = 0; i < this-> len ; i++){this->A[i]=X.A[i];} //copy all elements of X   
    }

    // Just a funtion to get the current length
    int length(){return this->len;}
    
    //overload <<
    friend std::ostream& operator<<(std::ostream& os, DynArray &X)
    {
        os <<"[ " ;
        for (int i = 0; i < X.len; i++){
            os<<X[i];
            if(i<X.len-1){ os<<", "; }
        }
        os <<" ]"; 
        return os;
    }
    

};


// #define One //define oe to run 1-D DynArray or std::vector
// #define Two //define oe to run 2-D DynArray or std::vector

int main(){
    
    #ifdef One
    
    DynArray<int> T;
    
    for (int i = 0; i < 10 ; i++)
    {
        T.push_back(i);
        std::cout<<T<<std::endl;
    }
    #endif


    #ifdef Two
    // The template allows you to do something like this:
    DynArray<DynArray<double>> T;//this should behave as a 2-dimensional dynamic array.
    //to test is //define and fill tow 1-d arrays:
    DynArray<double> x;
    for (int i = 0; i < 2 ; i++){x.push_back(i);}
    DynArray<double> y=x;//The copy-constructor works!
    for (int i = 0; i < 6 ; i++){y.push_back(-i);}
    std::cout<<x<<std::endl<<y<<std::endl;

    //and then push_back these arrays to teh 2-d one.
    T.push_back(x);
    for (int i = 0; i < 3; i++)
    {
        T.push_back(y);   
    }

    T[2]=x;//you can also do this.

    //if we don't get segfault, it should print the T
    std::cout<<T<<std::endl;

    #endif
  



    return 0;
}