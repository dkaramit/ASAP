import random

def RandInit(x):
    g=[]
    for i in range(int(x)):
        g+=[random.randint(0,1)]
    return g


def CellAuto(GenInit,Rules,Generations):

    cell=[]

    gen=GenInit

    rules=Rules
    temp=[]
    for i in gen:
	temp.append(i)


    for time in range(0,Generations):

	for i in range(1,len(gen)-1):

	    if gen[i-1] == 0 and gen[i] == 0 and gen[i+1] == 0:
		temp[i] = rules[0]
		#print(1,time,temp,gen)

	    if gen[i-1] == 0 and gen[i] == 0 and gen[i+1] == 1:
		temp[i] = rules[1]
		#print(2,time,temp)

	    if gen[i-1] == 0 and gen[i] == 1 and gen[i+1] == 0:
		temp[i] = rules[2]
		#print(3,time,temp,gen)

	    if gen[i-1] == 0 and gen[i] == 1 and gen[i+1] == 1:
		temp[i] = rules[3]
		#print(4,time,temp,gen)

	    if gen[i-1] == 1 and gen[i] == 0 and gen[i+1] == 0:
		temp[i] = rules[4]
		#print(5,time,temp,gen)

	    if gen[i-1] == 1 and gen[i] == 0 and gen[i+1] == 1:
		temp[i] = rules[5]
		#print(6,time,temp,gen)

	    if gen[i-1] == 1 and gen[i] == 1 and gen[i+1] == 0:
		temp[i] = rules[6]
		#print(7,time,temp,gen)

	    if gen[i-1] == 1 and gen[i] == 1 and gen[i+1] == 1:
		temp[i] = rules[7]
		#print(8,time,temp,gen)

	gen=[]
	for gg in temp:
	    gen.append(gg)
	cell.append(gen)
    return cell








cell=CellAuto(RandInit(85),RandInit(8),400)

for i in cell:
	for j in i:
		if j==0:
			print " " ,
		if j==1:
			print "*" ,
	print("\n")




#for No in range(0,1000):
#
#    cell=CellAuto(RandInit(80),RandInit(8),100)
#
#
#
 #   fname='cell-out/out'
 #   fname+=str(No+1)
 #   fname+='.dat'
#
 #   out=open(fname,'w')
#
 #   for i in cell:
#	for j in i:
#	    if j==0:
#		out.write(" " ,)
#	    if j==1:
#		out.write("*" ,)
#	out.write("\n")
 #   out.close
