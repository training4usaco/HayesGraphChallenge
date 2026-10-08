import sys
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

name = sys.argv[1]

with open(str(name) + ".out") as f:
    cc = f.readline()
    scc = f.readline()

    deg = [int(x) for x in f.readline().split()];
    indeg = [int(x) for x in f.readline().split()];
    outdeg = [int(x) for x in f.readline().split()];

fig, ax = plt.subplots()
ax.bar(list(range(max(deg) + 1)), [deg.count(x) for x in range(max(deg) + 1)])
ax.xaxis.set_major_locator(MaxNLocator(integer=True))
ax.yaxis.set_major_locator(MaxNLocator(integer=True))
ax.set_xlabel("Degree")
ax.set_ylabel("Number of nodes")
ax.set_title(f"{name}: degree distribution")
fig.savefig(f"{name}_deg.png")
plt.close(fig)

fig, (left, right) = plt.subplots(1, 2, figsize=(10, 4))

left.bar(list(range(max(indeg) + 1)), [indeg.count(x) for x in range(max(indeg) + 1)])
left.xaxis.set_major_locator(MaxNLocator(integer=True))
left.yaxis.set_major_locator(MaxNLocator(integer=True))
left.set_xlabel("Indegree")
left.set_ylabel("Number of nodes")
left.set_title("Indegree")

right.bar(list(range(max(outdeg) + 1)), [outdeg.count(x) for x in range(max(outdeg) + 1)])
right.xaxis.set_major_locator(MaxNLocator(integer=True))
right.yaxis.set_major_locator(MaxNLocator(integer=True))
right.set_xlabel("Outdegree")
right.set_ylabel("Number of nodes")
right.set_title("Outdegree")

fig.suptitle(f"{name}: in/out degree distributions")
fig.tight_layout()
fig.savefig(f"{name}_inout.png")
plt.close(fig)