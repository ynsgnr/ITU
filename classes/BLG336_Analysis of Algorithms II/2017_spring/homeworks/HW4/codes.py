#BLG 354E 2018 Apr HW-4 Istanbul Technical University
#Yunus Güngör-Student No:150150701

import numpy as np

import matplotlib.pyplot as plt
import wave
import sys
import scipy.io
from scipy import signal

def demodulator(input,freq,phase,filter):
    samplingRate=44100
    time=len(input)/samplingRate
    output=np.zeros(len(filteredSignal))
    for i in range(0,len(filteredSignal)):
        output[i]=input[i]*np.cos(carrierFreq*1000*2*np.pi*i/samplingRate)
    print(output)
    w,freqResponse=signal.freqz(filter)
    return np.convolve(output,freqResponse)

def cut(signal):
    threshold = 100 #minumum threshold signal (used for cutting)

    #determine begining
    i=0
    while(signal[i]<threshold):
        i=i+1
    begining=i

    #determine ending
    i=len(signal)-1
    while(signal[i]<threshold):
        i=i-1
    ending=i

    return signal[begining:ending] #cut

#assumed required sound file's name is record.wav
#assumed given FIR lowpass filter's name is firFilter_b_Coeffs

data = wave.open('record.wav')
sound = data.readframes(-1)
sound = np.fromstring(sound,'int16')
sound = cut(sound)

#plot sound
plt.figure(1)
plt.plot(sound)
plt.title('Sound Signal')

#get filter
filter = scipy.io.loadmat('firFilter_b_Coeffs')
filter = filter['b'][0]

#apply filter
w,freqResponse = signal.freqz(filter)
filteredSignal=np.convolve(sound,freqResponse)

#plot signal
plt.figure(2)
plt.plot(freqResponse)
plt.title('Frequency Response of Given filter')

#plot signal
plt.figure(3)
plt.plot(filteredSignal)
plt.title('Filtered Signal')

#calculate spectrogram
f, t, spectrogram = signal.spectrogram(filteredSignal)
plt.figure(4)
plt.pcolormesh(t, f, spectrogram)
plt.ylabel('F')
plt.xlabel('T')
plt.title('Spectrogram of filtered signal')

print('Estimated Bandwith:')
print(np.max(np.abs(spectrogram))-np.min(np.abs(spectrogram)))

carrierFreq=8.5 #khz
samplingRate=44100
amSignal=np.zeros(len(filteredSignal))
for i in range(0,len(filteredSignal)):
    amSignal[i]=filteredSignal[i]*np.cos(carrierFreq*1000*2*np.pi*i/samplingRate)
#plot signal
plt.figure(5)
plt.plot(amSignal)
plt.title('AM Signal')

output=demodulator(amSignal,carrierFreq,np.pi/2,filter)
#plot signal
plt.figure(6)
plt.plot(output)
plt.title('Output Signal')


#normalize Signal
min=min(output)
max=max(output)
normalSignal = (output-min)/(max-min)
#plot signal
plt.figure(7)
plt.plot(normalSignal)
plt.title('Normalized Signal')

plt.show()
