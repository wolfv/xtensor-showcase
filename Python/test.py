import rayshade
import numpy as np

from matplotlib import pyplot as plt

print("Loading Volcano data...")
volcano = np.loadtxt("../assets/volcano.csv", delimiter=",", dtype=np.float32)
print("Shading Volcano...")
result = rayshade.rayshade(volcano)
print("Displaying...")
plt.imshow(result)
plt.show()

print("Loading Mountain Data...")
# big = np.loadtxt("../assets/big.csv", delimiter=",", dtype=np.float32)

# print("Shading Mountain Data...")
# result_big = rayshade.rayshade(big)

# print("Displaying...")
# plt.imshow(result_big)
# plt.show()

import timeit

setup = """
import numpy as np
import rayshade
import python_impl

volcano = np.loadtxt("../assets/volcano.csv", delimiter=",", dtype=np.float32)
"""

print("Benchmarking Python:")

N = 100
print(timeit.timeit("rayshade.rayshade(volcano)", setup, number=N) / N)
N = 1
print(timeit.timeit("python_impl.rayshade(volcano)", setup, number=N) / N)