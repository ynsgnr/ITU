import numpy as np
import matplotlib.pyplot as plt
samplePerSecond = 10000
frequency = 1
duration = 10
sampleNumber = np.arange(duration * samplePerSecond)
t=frequency * sampleNumber * 1 / samplePerSecond
signal = 2+4*np.cos(500*np.pi*t+(5/4)*np.pi)-3*np.sin(60-np.pi*t)+3*np.cos(250*np.pi*(t-0.001))
transform = np.fft.rfft(signal)
spectrum = np.fft.fftfreq(signal.size, d=samplePerSecond)

fig = plt.figure()
ax = fig.add_subplot(111)
plt.plot(transform)
plt.show()
