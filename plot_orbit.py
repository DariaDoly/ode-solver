import numpy as np
import matplotlib.pyplot as plt

for name in ["euler", "rk4"]:
    d = np.loadtxt(f"orbit_{name}.csv", delimiter=",", skiprows=1)
    plt.plot(d[:, 1], d[:, 2], label=name)
    energy = (d[:,3]*d[:,3]+d[:,4]*d[:,4])/2-1/np.sqrt(d[:,1]*d[:,1]+d[:,2]*d[:,2])
plt.axis("equal")
plt.legend()
plt.savefig("orbits.png")