#BLG 354E 2018 Apr HW-2 Istanbul Technical University
#Yunus Güngör-Student No:150150701
#question 6

import numpy as np

def MyConv(x,h):
    #reverse x first:
    reversex=np.zeros(len(x))
    for i in range(0,len(x)):
        reversex[i]=x[len(x)-i-1]

    y=np.zeros(len(x)+len(h))

    indexX=len(x)-1 #origin for x

    for i in range(0,len(y)):
        for j in range(indexX,len(x)):
            #print('i: '+str(i))
            #print('j: '+str(j))
            #print('h: '+str(j-indexX))
            #print('------')
            if ((j-indexX)<len(h) and j>-1): #ignore zero values for h and x
                y[i]=y[i]+h[j-indexX]*reversex[j]
        indexX=indexX-1
    return(y)

print('MyConv function: ')
print(MyConv([2,4,6,4,2],[3,-1,2,1]))
print('\nConvolve function: ')
print(np.convolve([2,4,6,4,2],[3,-1,2,1]))
