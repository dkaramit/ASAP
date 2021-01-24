# ASAP
Numerical calculations *as simple as possible* (ASAP).

---
![GitHub repo size](https://img.shields.io/github/repo-size/dkaramit/ASAP?color=red&style=flat-square)

![](https://tokei.rs/b1/github/dkaramit/ASAP)
--
**Personal note**

I'm trying to create a collection of programs and scripts that perform various calculations.
I'm doing this to understand (and show) how various numerical tools work. Because python is slow 
for such things, I'll try to write some scripts in python first, and later translate them in C++.

For the moment  I have successfully implemented the plain Monte Carlo (MC), Acceptance-Rejection MC flavours,
Markov-Chains (and some discrete for fun), and VEGAS (both in python and C++) I have also implemented some algorithms for systems of differential equations, in python and C++.
Explanations can be found in the corresponding jupyter notebooks, while both python and C++ have an abundance of comments.
If you are interested in how the work, look for the python versions first. The C++ ones are translations of the python scripts, but they have C++ specific things that can make them difficult to understand at first.
I am preparing a code for artificial neural networks (slowly), where I have a working neural net, with an arbitrary  number of hidden layers. Again, the code needs "cleaning" and documentation.  So, it may take some time until I upload it. From time to  time I'll update this note, with my progress, but one should expect that it is always outdated, because most of the work is done at night, and I forget to write down what I did.  Documentation and useful comments are added in the codes or in jupyter notebooks, so don't pay attention to the commit messages because I am too lazy to rewrite anything.

Anything that seems to be useful (in C++ which is faster), will be moved to a different resopitory to further develope it beyond just showing how it works. For the moment the diffrential equation solvers are in [NaBBODES](https://github.com/dkaramit/NaBBODES), while the VEGAS integrator is is [BB_VEGAS](https://github.com/dkaramit/BB_VEGAS).


I'll try to use packages like scipy as little as possible, but for some simple things (e.g. products, sums etc.) 
I'll use some of the ready-to-use packages for convenience and for testing my results against reliable algorithms. 
So, in order to  run these scripts without any issues, you should have at least scipy and matplotlib installed (python 2.7 and 3+ should both work).




Cheers,
Dimitris