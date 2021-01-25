# ASAP
Numerical calculations *as simple as possible* (ASAP).

---
![GitHub repo size](https://img.shields.io/github/repo-size/dkaramit/ASAP?color=red&style=flat-square)

![](https://img.shields.io/badge/language-C++-black.svg)  
![](https://img.shields.io/badge/language-python-black.svg)  
--
**Personal note**

I'm trying to create a collection of programs and scripts that perform various calculations.
I'm doing this to understand (and show) how various numerical tools work. 

I usually start something using python, but once I understand how it works I translate it to C++.


For the moment I have successfully implemented different kinds of Monte Carlo (including Metropolis and VEGAS integration) and various ODE solvers. I am currently working on implementation of Optimization algorithms and neural netwokrs. 


Anything that seems to be useful (in C++ which is faster), will be moved to a different resopitory to further develop it beyond just showing how it works. For the moment the diffrential equation solvers are in [NaBBODES](https://github.com/dkaramit/NaBBODES), while the VEGAS integrator is [BB_VEGAS](https://github.com/dkaramit/BB_VEGAS). I will begin experiment with how difefernt optimizers can be used to solve differential equation in [OpSDE](https://github.com/dkaramit/OpSDE).


I'll try to use packages like scipy as little as possible, but for some simple things (e.g. products, sums etc.) 
I'll use some of the ready-to-use packages for convenience and for testing my results against reliable algorithms. 
So, in order to  run these scripts without any issues, you should have at least scipy and matplotlib installed (python 2.7 and 3+ should both work).


Cheers,
Dimitris