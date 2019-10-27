from numpy import sin,cos,sqrt

class path:
    '''
    path represents someone that walks in the corridor
    '''
    def __init__(self,y0):
        '''
        initiate bob (x is fixed x=0)
        '''
        self.x=[0]
        self.y=[y0]
        self.steps=0
        self.distance=0 #initialization of the distance parameter



    def move(self,theta,step=1e-2):
        '''
        rotate bob by theta, and move.

        eventually, theta will be given by a neural network
        (you wont have to panish if theta rotates bob more tham +-pi/2,
        since we want to find the shortest path)!
        '''
        self.x.append(self.x[self.steps]+cos(theta)*step)
        self.y.append(self.y[self.steps]+sin(theta)*step)
        self.steps+=1


    def update_distance(self):
        '''updates self.distance (step by step)'''

        i=self.steps
        if i!=0:
            dx=self.x[i]-self.x[i-1]
            dy=self.y[i]-self.y[i-1]
            self.distance+=sqrt(dx**2+dy**2)
        else:
            self.distance=0
            
    def total_distance(self):
        '''
        calculates the total length of the path
        '''
        _dist=0
        for i in range(self.steps):
            dx=self.x[i+1]-self.x[i]
            dy=self.y[i+1]-self.y[i]

            _dist+=sqrt(dx**2+dy**2)
        return _dist
