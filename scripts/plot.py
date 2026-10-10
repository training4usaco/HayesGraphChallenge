import sys
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

name = sys.argv[1]

with open("output/" + str(name) + ".out") as f:
    cc = f.readline()
    scc = f.readline()

    deg = [int(x) for x in f.readline().split()];
    indeg = [int(x) for x in f.readline().split()];
    outdeg = [int(x) for x in f.readline().split()];

    deg_dup = [int(x) for x in f.readline().split()];
    indeg_dup = [int(x) for x in f.readline().split()];
    outdeg_dup = [int(x) for x in f.readline().split()];

def hist(ax, vals, label):
    ax.bar(list(range(max(vals) + 1)), [vals.count(x) for x in range(max(vals) + 1)])
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    ax.yaxis.set_major_locator(MaxNLocator(integer=True))
    ax.set_xlabel(label)
    ax.set_ylabel("Number of nodes")

def plot_deg(deg, title, file):
    fig, ax = plt.subplots()
    hist(ax, deg, "Degree")
    ax.set_title(title)
    fig.savefig(file)
    plt.close(fig)

def plot_inout(indeg, outdeg, title, file):
    fig, (left, right) = plt.subplots(1, 2, figsize=(10, 4))

    hist(left, indeg, "Indegree")
    left.set_title("Indegree")

    hist(right, outdeg, "Outdegree")
    right.set_title("Outdegree")

    fig.suptitle(title)
    fig.tight_layout()
    fig.savefig(file)
    plt.close(fig)

plot_deg(deg, f"{name}: degree distribution (duplicates removed)", f"figures/{name}_deg.png")
plot_inout(indeg, outdeg, f"{name}: in/out degree distributions (duplicates removed)", f"figures/{name}_inout.png")

plot_deg(deg_dup, f"{name}: degree distribution (with duplicates)", f"figures/{name}_deg_with_dupes.png")
plot_inout(indeg_dup, outdeg_dup, f"{name}: in/out degree distributions (with duplicates)", f"figures/{name}_inout_with_dupes.png")
