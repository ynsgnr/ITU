import numpy as np
import matplotlib.pyplot as plt
samplePerSecond = 10000
frequency = 1
duration = 10
sampleNumber = np.arange(duration * samplePerSecond)
t=frequency * sampleNumber * 1 / samplePerSecond
w=np.pi*frequency/2
signal = np.cos(w*t-(1/3)*np.pi)+3*np.cos(w*t-(7/4)*np.pi)+2*np.cos(w*t-(3/2)*np.pi)
fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_ylim([-5, 5])
p, = ax.plot(sampleNumber / samplePerSecond, np.full(sampleNumber.shape, signal))
p.set_data(sampleNumber / samplePerSecond, signal)
fig.canvas.draw()
plt.show()
