#BLG 354E 2018 May HW-3 Istanbul Technical University
#Yunus Güngör-Student No:150150701
#question 3

import numpy as np
import time

def fft(data):
    l = len(data)
    if l<=1: return data

    #split data into even and odd indexes
    #and compute fourier transform on that small arrays
    #since exp(-j2pi/n) is symetric and periodic
    evenSide = fft(data[0::2])
    oddSide = fft(data[1::2])

    #Calculate common multipliers exp(-j2pi/2^i)
    i=np.arange(l//2)
    m=np.exp((-2*np.pi*i)/l)

    #Mulitiplication of extra multiplier for odd side
    m=m*oddSide

    #Addition to form final coefficents
    evenSide=evenSide+m
    oddSide=oddSide-m

    return np.concatenate((evenSide, oddSide))


samplePerSecond = 512
frequency = 1
duration = 16
timesToRun = 5
sampleNumber = np.arange(duration * samplePerSecond)

#define signal
piDivededByCount = np.pi/(duration-samplePerSecond)
#Signal can be defined as an array of samples from any function
signal = 1+np.sin(2*piDivededByCount*sampleNumber)+3*np.cos(2*piDivededByCount*sampleNumber)+np.cos(4*piDivededByCount*sampleNumber+np.pi/2)

start = time.time()
for x in range(0, timesToRun):
    implementedTransform = fft(signal)
end = time.time()
print('Time it takes to calculate for implemented FFT:')
print(((end - start)/timesToRun))
print()
start = time.time()
for x in range(0, timesToRun):
    numPyTransform = np.fft.fft(signal)
end = time.time()
print('Time it takes to calculate for built in FFT:')
print(((end - start)/timesToRun))
print()
print('Error margin between implementation and built in:')
error=implementedTransform-numPyTransform
r=0
for i in range(len(error)):
    r=r+np.sqrt(error[i]*error[i])
r=r/len(error)
print(np.abs(r))
print()
print('Actual coefficencts calculated by implemented: ')
print(implementedTransform)
print()
print('Actual coefficencts calculated by built in: ')
print(numPyTransform)
