from typing import List
from queue import PriorityQueue
planets, portals = map(int, input().split())
adj = [[] for _ in range(planets)]
for _ in range(portals):
    a, b, time = map(int, input().split())
    a,b = a-1,b-1
    adj[a].append((b, time))
    adj[b].append((a, time))

busy_times = [set() for _ in range(planets)]
for planet in range(planets):
    for busy_time in [int(x) for x in input().split()][1:]:
        busy_times[planet].add(busy_time)

INF = 2**30
def dijkstra(start: int, end: int) -> int:
    out = [INF for _ in range(planets)]
    out[start] = 0
    pq = PriorityQueue()
    
    t = 0
    while t in busy_times[start]:
        t += 1
    pq.put((t, start))
    
    visited = [False for _ in range(planets)]
    while not pq.empty():
        dist, node = pq.get()

        if visited[node]:
            continue
        visited[node] = True

        for adj_node, adj_dist in adj[node]:
            t = dist + adj_dist
            if t >= out[adj_node]:
                continue
            out[adj_node] = t
            while t in busy_times[adj_node]:
                t += 1
            
            if not visited[adj_node]:
                pq.put((t, adj_node))

    return out[end] if out[end] != INF else -1

print(dijkstra(0, planets - 1))
