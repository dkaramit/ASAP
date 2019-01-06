from numpy import linspace
import matplotlib.pyplot as plt




class corridor:

    def __init__(self, width, length,_data_size=2):
        self.right=0 #right wall
        self.left=width #left wall
        self.length=length
        self.wall=linspace(0,length,_data_size) # this will help draw the corridor
        self.boxes=[] #this will be used to define obstacles



    def add_box(self,x,y,size):
        self.boxes.append((x,y,size)) #later you need to detect if you've hit a box, and also draw them.


    def wall_detect(self,x,y):
        '''
        detects if the given point (x,y) is beyond the wall.
        It returns "Hit", "NoHit", and "Win", if the point is beyond the wall,
        inside the corridor, or is out of the corridor, respectively.

        Lets decide to "Win" if at the end of the corridor, we hit a wall.
        '''
        if x<self.length:
            if   (y<= self.left and y>=self.right ):
                return 'NoHit'
            elif (y> self.left or y<self.right ):
                return 'Hit'
        if x>=  self.length:
            return 'Win'


    def draw(self,_n_paths=0,paths=[]):
        '''
        draw the corridor, and the paths!
        '''

        fig=plt.figure(figsize=(8,3))
        fig.subplots_adjust(bottom=0.2, left=0.2, top = 0.9, right=0.9)
        #=============================================================================#
        sub = fig.add_subplot(111)

        _len=len(self.wall)
        sub.plot(self.wall, [self.right]*_len,'r')
        sub.plot(self.wall, [self.left]*_len,'r')

        if _n_paths!=0:

            if _n_paths==1:
                _lp=len(paths[0])
                sub.plot([paths[0][i] for i in range(_lp)],[paths[1][i] for i in range(_lp)])
            if _n_paths>1:
                for n,_p in enumerate(paths):
                    _lp=len(_p[0])
                    sub.plot([_p[0][i] for i in range(_lp)],[_p[1][i] for i in range(_lp)],'k:',alpha=0.3)



        sub.set_xlim(-0.1,self.length*1.1)
        sub.set_ylim(-0.1,self.left*1.1)
        plt.show()
