import numpy as np

# Define the number of elements in the vector
num_elements = 15

# Create the equally spaced interval from 0 to 1
t_values = np.linspace(0, 1, num_elements)

# Compute the values of x(t)
x_values = 4 * np.cos(2 * np.pi * t_values + 0.2) + 3 * np.sin((np.pi**2) * t_values)

# Find the maximum and minimum values
max_value = np.max(x_values)
min_value = np.min(x_values)

# Compute the average of the element values
avg_value = np.mean(x_values)

# Find the indices where element magnitude is greater than 4
indices_greater_than_4 = np.where(np.abs(x_values) > 4)[0]

# Print the results
print("Maximum element value:", max_value)
print("Minimum element value:", min_value)
print("Average of the element values:", avg_value)
print("Indices where magnitude is greater than 4:", indices_greater_than_4)
