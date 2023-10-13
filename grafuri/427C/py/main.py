from functools import reduce
junctions = int(input())
prices = list(map(int, input().split()))
streets = int(input())

adj = [[] for _ in range(junctions)]
for _ in range(streets):
    a,b = map(int, input().split())
    a,b = a-1,b-1
    adj[a].append(b)

def reverse_graph(a):
    out = [[] for _ in range(len(a))]
    for i in range(len(a)):
        for j in a[i]:
            out[j].append(i)
    return out

def dfs(a, k, visited=None):
    if visited is None:
        visited = set()
    if k not in visited:
        visited.add(k)
        for node in a[k]:
            for n in dfs(a, node, visited):
                yield n
        yield k

def connected_components(a):
    n = len(a)
    visited = set()

    topologial_order = []
    for i in range(n):
        topologial_order += dfs(a, i, visited)

    visited = set()
    b = reverse_graph(a)
    for node in reversed(topologial_order):
        if node not in visited:
            yield dfs(b, node, visited)

components = [[prices[node] for node in component] for component in connected_components(adj)]
print(sum(min(component) for component in components),
      reduce(lambda acc, x: acc*x%1000000007, \
             (len([node for node in component if node == min(component)]) for component in components)))
