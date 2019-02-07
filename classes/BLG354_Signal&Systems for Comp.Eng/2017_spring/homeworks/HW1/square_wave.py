import numpy as np
import matplotlib.pyplot as plt

sample_rate_per_second = 10000

frequency_in_hertz = 2

# duration of signal
duration_in_sec = 5

# sample in time, these values will be given a function to calculate x(t)
each_sample_number = np.arange(duration_in_sec * sample_rate_per_second)

total_wave = np.full(each_sample_number.shape, 1.0/2)

fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_ylim([-2, 2])
p, = ax.plot(each_sample_number / sample_rate_per_second, np.full(each_sample_number.shape, total_wave))


for i in np.arange(1,200,2):
    print(i)
    # using exponential fourier series
    wave =  (2 * np.exp( np.complex(0, 1) * 2 * np.pi * frequency_in_hertz * each_sample_number * i / sample_rate_per_second) / (np.complex(0, 1) * np.pi * i)).real
    # using trigonometric fourier series
    #wave = 2 / (i * np.pi) * np.cos(2 * np.pi * frequency_in_hertz * each_sample_number * i / sample_rate_per_second - np.pi/2)

    # sum waves
    total_wave += wave
    p.set_data(each_sample_number / sample_rate_per_second, total_wave)
    fig.canvas.draw()
    plt.pause(0.5)

plt.show()