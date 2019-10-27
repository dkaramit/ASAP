# ASAP
Numerical calculations *as simple as possible* (ASAP).

---

**Personal note**

I'm trying to create a collection of programs and scripts that perform various calculations.
I'm doing this to understand (and show) how various numerical tools work. Because python is slow 
for such things, I'll try to write some scripts in python first, and later translate them in C++.

For the moment  I have successfully implemented the plain Monte Carlo (MC), Acceptance-Rejection MC flavours,
Markov-Chains (and some discrete for fun), and VEGAS (this is not complete, although the jupyter notebook for the
1-dimensional is very good). Also, I have worked out some algorithms for systems of differential equations, 
and started to put some documentation (I'm also rewriting the code in a more transparent object-oriented way). 
I am preparing a code for artificial neural networks (slowly), where I have a working neural net, with an arbitrary 
number of hidden layers. Again, the code needs "cleaning" and documentation.  So, it may take some time until I upload it. From time to 
time I'll update this note, with my progress, but one should expect that it is always outdated, because most of the work is done at 
night, and I forget to write down what I did.  Documentation and useful comments are added in the codes or in jupyter notebooks, 
so don't pay attention to the commit messages because I am too lazy to rewrite anything.

Since I am self-taught on these subjects, I cannot give you my word that the codes work as indented (although I'm using some of them 
for my research for cross-checking). So, If you are looking for something that works better, ASAP may not be for you.  However, if you 
are trying to understand what makes these tools work, maybe you will find ASAP helpful. If you have questions or suggestions feel free 
to contact me. Since I am a postdoc, I'm busy with my research, so if I don't answer any questions, it's nothing personal.

I'll try to use packages like scipy as little as possible, but for some simple things (e.g. products, sums etc.) 
I'll use some of the ready-to-use packages for convenience and for testing my results against reliable algorithms. 
So, in order to  run these scripts without any issues, you should have at least scipy and matplotlib installed (python 2.7 and 3+ should 
both work).


Cheers,
Dimitris