import numpy as np
import matplotlib.pyplot as plt

def x(t):
    """Signal x(t)"""
    return np.sin(t) * (t > 0) + 1 * (t < 0)

def odd_decomposition(t):
    """Odd component of x(t)"""
    return 0.5 * (x(t) - x(-t))

def even_decomposition(t):
    """Even component of x(t)"""
    return 0.5 * (x(t) + x(-t))

# Generate a range of time values
t = np.linspace(-10, 10, 1000)

# Compute the odd and even components
odd = odd_decomposition(t)
even = even_decomposition(t)

# Plot the original signal and its odd and even components
plt.plot(t, x(t), label='x(t)')
plt.plot(t, odd, label='Odd Component')
plt.plot(t, even, label='Even Component')
plt.legend()
plt.xlabel('t')
plt.ylabel('Amplitude')
plt.title('Odd and Even Decomposition of x(t)')
plt.grid(True)
plt.show()
