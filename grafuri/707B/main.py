nodes, roads, bakeries_cnt = map(int, input().split())
if not bakeries_cnt:
    print(-1)
    exit()
adj = [[] for _ in range(nodes)]
for _ in range(roads):
    a, b, l = map(int, input().split())
    a, b = a - 1, b - 1
    adj[a].append((l, b))
    adj[b].append((l, a))

min_distt = 2**31
bakeries = {int(x)-1 for x in input().split()}
for bakery in bakeries:
    try:
        closest_city = min(x[0] for x in adj[bakery] if x[1] not in bakeries)
    except ValueError:
        continue
    min_distt = min(min_distt, closest_city)

print(min_distt if min_distt != 2**31 else -1)
