The C++ directory is here, in order to implement some of the python scripts in pure C++.


My problem with the translation from python to C++ is the use of numpy and some purely pythonic workarounds
for arrays. For example, the ROS3w method relies in the way I send lists of functions to be evaluated,
which in C++ is not so easy unless you don't care about memory management...

The discrete and Metropolis MCMCs can be easily made into C++, since there is no great need for numpy.

In the future, I'd like to write a multidimensional VEGAS for integration, and Rosenbrock Methods for differential
equations. However, it would be better to have the other in python first, so it will be a while.
