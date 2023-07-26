import numpy as np
import matplotlib.pyplot as plt

# Define the frequencies
f1 = 0.2
f2 = 0.425

# Define the time range
t = np.arange(0, 10, 0.1)

# Compute the values of s1, s2, and s3
s1 = np.sin(2 * np.pi * f1 * t)
s2 = np.sin(2 * np.pi * f2 * t + 0.4)
s3 = s1 + s2

# Plot s1, s2, and s3 on the same graph
plt.plot(t, s1, label='s1')
plt.plot(t, s2, label='s2')
plt.plot(t, s3, label='s3')

# Add labels and legends
plt.xlabel('t')
plt.ylabel('Amplitude')
plt.legend()

# Show the plot
plt.show()
