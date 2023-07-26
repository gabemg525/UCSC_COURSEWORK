import numpy as np

t_values = [0.0, 0.1, 0.2, 0.3, 0.4]
frequencies = [10, 15, 20]

results = np.zeros((len(frequencies), len(t_values)))

for i, f in enumerate(frequencies):
    for j, t in enumerate(t_values):
        value = 3 * np.cos(2 * np.pi * f * t + 0.1)
        results[i, j] = value
        
print("Results:")
print(results)