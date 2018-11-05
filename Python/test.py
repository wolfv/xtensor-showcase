import rayshade
import numpy as np

from matplotlib import pyplot as plt

volcano = np.loadtxt("../assets/volcano.csv", delimiter=",", dtype=np.float32)
print(volcano)
result = rayshade.rshade(volcano)

plt.imshow(result)
plt.show()

big = np.loadtxt("../assets/big.csv", delimiter=",", dtype=np.float32)

result_big = rayshade.rshade(big)
plt.imshow(result_big)
plt.show()
