#fill everything with a given value
def fill_weights_with(self,value=0):
    for l in range(len(self.weights)):
        for j in range(len(self.weights[l])):
            for i in range(len(self.weights[l][j])):
                self.weights[l][j][i]=value

def fill_biases_with(self,value):
    for l in range(len(self.biases)):
        for j in range(len(self.biases[l])):
            self.biases[l][j]=value

#print
def printWeights(self):
    print("w^{(l)}_{ji}")
    for l in range(len(self.weights)):
        print("l= ",l,"\t size:",self.nodes[l+1],"x",self.nodes[l])
        for j in range(len(self.weights[l])):
            for i in range(len(self.weights[l][j])):
                print(self.weights[l][j][i], end ="\t")
            print('')
        print('============')

def printBiases(self):
    print("b^{(l)}_{j}")
    for l in range(len(self.biases)):
        print("l= ",l+1,"\t size:",self.nodes[l+1])
        for j in range(len(self.biases[l])):
            print(self.biases[l][j],end ="\t")
        print('')
        print('============')

def printSignals(self):
    print("s^{(l)}_{j}")
    for l in range(len(self.signals)):
        print("l= ",l,"\t size:",self.nodes[l])
        for j in range(len(self.signals[l])):
            print(self.signals[l][j], end ="\t")
        print('')
        print('============')


def printDerivatives(self):
    print(r"\dfrac{\partial s^{l+1}_{j}}{\partial s^{(l)}_{i}}")
    for l in range (self.total_layers-1):
        print("l= ",l,"\t size:",self.nodes[l+1],"x",self.nodes[l])
        for j in range(self.nodes[l+1]):
            for i in range(self.nodes[l]):
                print(self.derivatives[l][j][i],end="\t")
            
            print('')
        print('')



def printTotalDerivatives(self):
    print(r"\dfrac{\partial s^{l+1}_{j}}{\partial s^{(0)}_{i}}")
    for l in range (self.total_layers-1):
        print("l= ",l,"\t size:",self.nodes[l+1],"x",self.nodes[0])
        for j in range(self.nodes[l+1]):
            for i in range(self.nodes[0]):
                print(self.totalDerivatives[l][j][i],end='\t')
            print('')
        print('')



def printDelta(self):
    print(r"\dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{[N-(f+2)]}_{i}}")
    for f in range(self.total_layers-1):
        print("f= ",f,"\t size:",self.nodes[self.total_layers-1],"x",self.nodes[self.total_layers-(f+2)])
        for j in range(self.nodes[self.total_layers-1]):
            for i in range(self.nodes[self.total_layers-(f+2)]):
                print(self.Delta[f][j][i],end='\t')
            print('')
        print()



def printNumericalDerivatives(self):
    print(r"\dfrac{\partial s^{(N-1)}_{p}}{\partial s^{(0)}_{r}}")
    print("size:",self.nodes[self.total_layers-1],"x",self.nodes[0])
    for p in range(self.nodes[self.total_layers-1]):
        for r in range(self.nodes[0]):
            print(self.numericalDerivatives[p][r],end='\t')
        print()
    print()


def printDerivatives_w(self):
    for l in range(self.total_layers-1):
        for j in range(self.nodes[l+1]):
            for i in range(self.nodes[l]):
                self.derivative_bw(l,j,i)
                print("\dfrac{{ds_j}}{{w^({0})_{1}{2}}}=".format(l,j,i),self.dsdw)
            print('')
        print('')
        
def printDerivatives_b(self):
    for l in range(self.total_layers-1):
        for j in range(self.nodes[l+1]):
            self.derivative_bw(l,j,0)
            print("\dfrac{{ds_j}}{{b^({0})_{1}}}=".format(l+1,j),self.dsdb)
        print('')
            

def printNumericalDerivatives_w(self):
    for l in range(self.total_layers-1):
        for j in range(self.nodes[l+1]):
            for i in range(self.nodes[l]):
                self.numericalDerivative_bw(l,j,i)
                print("\dfrac{{ds_j}}{{w^({0})_{1}{2}}}=".format(l,j,i),self.numerical_dsdw)
            print('')
        print('')
        
def printNumericalDerivatives_b(self):
    for l in range(self.total_layers-1):
        for j in range(self.nodes[l+1]):
            self.numericalDerivative_bw(l,j,0)
            print("\dfrac{{ds_j}}{{b^({0})_{1}}}=".format(l+1,j),self.numerical_dsdb)
        print('')
            