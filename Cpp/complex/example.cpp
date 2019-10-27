#include "include/complex-headers.h"


using namespace std;

int main(){
cout<<"=======Begin=======\n"<<endl;


complex w;


//cin>>w;
//cout<<pow(w,2)<<endl;


complex z3;
z3.SetRe(5);
z3.SetIm(-55);
cout<<z3<<endl;
cout << conjugate(z3) << '\n';


complex *X;
X=&z3;
cout << X->Re() << '\n';
cout << (*X).Im() << '\n';




cout<<"=======End=======\n"<<endl;
return 0;
}
