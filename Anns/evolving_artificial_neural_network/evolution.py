from numpy import sum as np_sum
from numpy import abs as np_abs
from numpy import random

from brains import brains



#=============================Define individual=============================#
class individual:
    '''
    This class defines an individual (a set of genes), to be used for a genetic algorithm.
    It should consists of several member functions for cross over, mutation, given the
    fitness scores.

    Note: This should be used for evolving a neural network, since we have a fixed
    shape of genes to match our definition of weights in the barin class.

    Note: It could e done as a deived class, but lets keep it this way for simplicity.

    Note: all individuals have the same shape of genes. You can have different shapes
    in different individuals, if you want to have a varied number of genes.

    Note: it would be better to give the genes as input (not only brains).
          That is, I have to define a "standard form" for genes, and
          transforms the parameters of a problem to this standard form.
          This way, I can make a class that will work for everything.
    '''

    def __init__(self,_brain,_fitness_score):
        '''
        The constractor of a chromosome. It should take as input a neural network (instance of brains)
        the fitness score.

        '''
        self.brain=_brain
        self.genes=_brain.weights
        self.fitness_score=_fitness_score

    def update_fitness_score(self,score):
        '''updates the fitness score'''
        self.fitness_score=score

    def reset_brain(self):
        '''this set the individual to a new random state (it will be used to create new individuals)'''
        self.brain.init_biases()
        self.brain.init_weights()



    def offspring(self,other):
        '''
        offspring takes two brains (parents) and returns one  (child).
        The parents exchange some of their genes (wifgts and biases), and this makes a child.
        '''

        _child=self.brain


        #decide how many weghts you will take from other
        _n=random.randint( np_sum(_child.nodes)+1 )# "+1" is needed because of the definition of randint


        for __n in range(_n):
            '''
            remember that we represent weights as w^{l}_{ij}, with
            l: layer
            i the i^{th} node of layer l
            j the j^{th} node of layer l+1
            '''

            l= random.randint(_child.layers+1)
            i= random.randint(_child.nodes[l])
            j= random.randint(_child.nodes[l+1])

            #print '{},{},{}'.format(l,i,j)
            #print str(self.brain.weights[l][i][j]) +' <-- '+ str(other.brain.weights[l][i][j])

            _child.update_weight(l,i,j, other.brain.weights[l][i][j] )



        #decide how many biases you will take from other
        # "+1" is not needed because the input biases are always 0 (ie there are total_nodes-1 biases)
        _n=random.randint( np_sum(_child.total_nodes) )
        for __n in range(_n):
            '''
            remember that we represent biases as w^{l}_{i}, with
            l: layer
            i the i^{th} node of layer l
            '''

            l= random.randint(1,_child.layers+1)# b^{0}_{i}=0 (can't change)
            i= random.randint(_child.nodes[l])

            #print '{},{}'.format(l,i)
            #print str(self.brain.biases[l][i]) +' <-- '+ str(other.brain.biases[l][i])

            _child.update_bias(l,i, other.brain.biases[l][i])


    def mutate(self):
        '''
        Mutate an individual.
        Mutate a random number of weights and biases
        '''
        _c=self.brain

        #decide how many weghts to mutate
        _n=random.randint( np_sum(_c.nodes)+1 )# "+1" is needed because of the definition of randint

        for __n in range(_n):
            '''
            remember that we represent weights as w^{l}_{ij}, with
            l: layer
            i the i^{th} node of layer l
            j the j^{th} node of layer l+1
            '''

            l= random.randint(_c.layers+1)
            i= random.randint(_c.nodes[l])
            j= random.randint(_c.nodes[l+1])

            #print '{},{},{}'.format(l,i,j)

            _c.update_weight(l,i,j, random.choice([-1,1])*random.random())# set a weight from -1 to 1


        #decide how many biases you will take from other
        # "+1" is not needed because the input biases are always 0 (ie there are total_nodes-1 biases)
        _n=random.randint( np_sum(_c.total_nodes) )
        for __n in range(_n):
            '''
            remember that we represent biases as w^{l}_{i}, with
            l: layer
            i the i^{th} node of layer l
            '''

            l= random.randint(1,_c.layers+1)# b^{0}_{i}=0 (can't change)
            i= random.randint(_c.nodes[l])

            print '{},{}'.format(l,i)

            _c.update_bias(l,i, random.choice([-1,1])*random.random()) # set a bias from -1 to 1


#=============================Define population=============================#
#not sure that I will need a class for the population, but define it for the moment
class population:
    '''
    This class defines a population (a set of individuals).
    It should be used to monitor the population, ie take chromosomes and decide
    which ones should be mixed, and generate a new population.
    '''

    def __init__(self, _individuals,_size,_reproduction_rate,_survival_rate):
        self.individuals=_individuals
        self.size=_size
        self.reproduction_rate=_reproduction_rate
        self.survival_rate=_survival_rate


    def rank(self):
        '''rank the individuals'''

        #calculate the abs of the total fitness score
        #self._tot=float(np_abs(np_sum([_in.fitness_score for _in in self.individuals ])))

        #assign a probability to each individual and rank them
        self.ranking=sorted([ (i,_in.fitness_score) for i,_in in enumerate(self.individuals) ] ,
                         reverse=True,key=lambda _s:_s[1])

    def new_generation(self):
        '''
        evolves the individuals

        As an example, we will take the first few (self.survival_rate) individuals and pass them to the
        next generaton.
        Also, we will take the next best few individuals (given by 2*self.reproduction_rate) and
        make self.reproduction_rate childs. Then we will reset the rest
        self.size-self.reproduction_rate-self.survival_rate


        Note: missing mutation!
        '''


        ''''for i in range(self.size):
            print i,': ',self.individuals[i].brain.biases
            print '\n\n\n\n'''''

        _srv=self.ranking[:self.survival_rate]
        _srv=[i[0] for i in _srv]
        #print _srv


        #take the first self.reproduction_rate individuals to reproduce
        #this is not the best I can do, but it's good for now
        _rep=self.ranking[self.survival_rate:2*self.reproduction_rate+self.survival_rate]
        _rep=[i[0] for i in _rep]


        random.shuffle(_rep)
        #print _rep
        _rep=iter(_rep)
        while True:
            try:
                p1=_rep.next()
                p2=_rep.next()


                #print self.individuals[p1].brain.biases

                self.individuals[p1].offspring(self.individuals[p2])
                self.individuals[p2].reset_brain()


                #print self.individuals[p1].brain.biases


            except:
                break

        _die=self.ranking[self.reproduction_rate+self.survival_rate:]
        _die=[i[0] for i in _die]
        #print _die
        #choose which individuals will make a child
        for i in _die:
            self.individuals[i].reset_brain()



        ''''for i in range(self.size):
            print i,': ',self.individuals[i].brain.biases
            print '\n\n\n\n'''''
