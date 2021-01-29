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
def print_weights(self):
    for l in range(len(self.weights)):
        print('l=',l,':')
        for j in range(len(self.weights[l])):
            
            for i in range(len(self.weights[l][j])):
                print(self.weights[l][j][i],'\t', end =" ")
            print('')
        print('============')

def print_biases(self):
    for l in range(len(self.biases)):
        print('l=',l+1,':')
        for j in range(len(self.biases[l])):
            print(self.biases[l][j],'\t', end =" ")
        print('')
        print('============')

def print_signals(self):
    for l in range(len(self.signals)):
        print('l=',l,':')
        for j in range(len(self.signals[l])):
            print(self.signals[l][j],'\t', end =" ")
        print('')
        print('============')