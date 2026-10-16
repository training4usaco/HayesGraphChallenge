import sys

name = sys.argv[1]

with open("output/" + str(name) + ".out") as f:
    cc = int(f.readline())
    scc = int(f.readline())

    deg = [int(x) for x in f.readline().split()]
    indeg = [int(x) for x in f.readline().split()]
    outdeg = [int(x) for x in f.readline().split()]

    deg_dup = [int(x) for x in f.readline().split()]
    indeg_dup = [int(x) for x in f.readline().split()]
    outdeg_dup = [int(x) for x in f.readline().split()]

with open("data/" + str(name) + ".txt") as f:
    f.readline()
    edges = [tuple(map(int, line.split())) for line in f if line.strip()]

m = len(set(edges))
m_dup = len(edges)

print(f"{name} (duplicates removed):")
print(f"  sum in = sum out = m: {sum(indeg)} = {sum(outdeg)} = {m}", sum(indeg) == sum(outdeg) == m)
print(f"  sum in + sum out >= sum deg: {sum(indeg) + sum(outdeg)} >= {sum(deg)}", sum(indeg) + sum(outdeg) >= sum(deg))

print(f"{name} (with duplicates):")
print(f"  sum in = sum out = m: {sum(indeg_dup)} = {sum(outdeg_dup)} = {m_dup}", sum(indeg_dup) == sum(outdeg_dup) == m_dup)
print(f"  sum in + sum out = sum deg: {sum(indeg_dup) + sum(outdeg_dup)} = {sum(deg_dup)}", sum(indeg_dup) + sum(outdeg_dup) == sum(deg_dup))

print(f"{name}:")
print(f"  scc >= cc: {scc} >= {cc}", scc >= cc)
