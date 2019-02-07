#BLG 354E 2018 Apr HW-2 Istanbul Technical University
#Yunus Güngör-Student No:150150701
#question 8

import numpy as np

from scipy.signal import convolve2d as c2d
import matplotlib.image as img

#assumed './noisyCameraman.png exists'

#form matrices
K=np.ones((3,3))*(1/9)

data = img.imread('noisyCameraman.png')
width=len(data[:,0,0])
height=len(data[0,:,0])

resultRed=c2d(data[:,:,0],K)
resultGreen=c2d(data[:,:,1],K)
resultBlue=c2d(data[:,:,2],K)

data[:,:,0]=resultRed[0:width,0:height]
data[:,:,1]=resultGreen[0:width,0:height]
data[:,:,2]=resultBlue[0:width,0:height]

img.imsave('noisyCameramanEdited.png', data)
