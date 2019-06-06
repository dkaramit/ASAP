# ASAP
Numerical calculations *as simple as possible* (ASAP).

---

**Personal note**

I'm trying to create a collection of programs and scripts that perform some of various calculations 
with the goal of packaging everything together at some point. I'm doing this to understand (and show) 
how various numerical tools work. Because python is slow for such things, I'll try to write some 
scripts in python first, and later translate them in C++.

For the moment  I have successfully implemented the plain Monte Carlo (MC), Acceptance-Rejection MC flavours,
Markov-Chains (and some discrete for fun), and VEGAS (this is not complete, although the jupyter notebook for the
1-dimensional is very good). Also, I have some algorithms (Euler, inverse Euler, SDIRK-2-1-2, and ROS3w)
for systems of differential equations, although they are not documented at all. I am preparing a code
for artificial neural networks, where I have a working neural net, with an arbitrary number of hidden layers.
However, the code needs "cleaning" and documentation.  So, it may take some time until I upload it. From time to time I'll update this note, with my progress, but one should expect that it is always outdated, because most of the work is done at night, and I forget to write down what I did.

Since I am self-taught on these subjects, I cannot give you my word that the codes work as indented. So, If you are
looking for something that works better, ASAP may not be for you.  However, if you are trying to understand what makes these tools work, maybe you will find ASAP helpful. If you have questions or suggestions feel free to contact me. Since I am a postdoc, I'm busy with my research, so if I don't answer any questions, it's nothing personal.

I'll try to use packages like scipy as little as possible, but for some simple things (e.g. products, sums etc.)
I'll use some of the ready-to-use packages for convenience and for testing my results against reliable algorithms. So, in order to  run these scripts without any issues, you should have at least scipy and matplotlib installed 
(python 2.7 and 3+ should both work).



Cheers,
Dimitris