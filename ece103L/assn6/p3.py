import numpy as np

# Define the angular frequencies
omegas = [35, 40, 45]

# Define the step size for t
step = 0.01

# Compute the largest value of t for each angular frequency
for omega in omegas:
    t = 0.0
    while True:
        value1 = np.exp(1.2) * np.cos(omega * t)
        value2 = t**3
        if value1 < 10 and value2 < 10:
            t += step
        else:
            break
    
    # Round the result to the nearest 0.01
    t = round(t - step, 2)
    print(f"For omega={omega}: Largest t = {t}")
