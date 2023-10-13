from itertools import accumulate

t = int(input())
for _ in range(t):
    coins = int(input().split()[1])
    teleporters = list(map(int, input().split()))

    price_of_using_teleporter = map(sum, enumerate(teleporters, 1))
    price_of_using_n_teleporters = accumulate(sorted(price_of_using_teleporter))
    
    ans = None
    for i, price in enumerate(price_of_using_n_teleporters):
        if price > coins:
            ans = i
            break

    if ans is None:
        ans = len(teleporters)
    print(ans)
