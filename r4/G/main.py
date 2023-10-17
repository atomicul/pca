from itertools import accumulate
from bisect import bisect_left
t=int(input())
for _ in range(t):
    _, q = map(int, input().split())
    max_sugar_with_candies = list(accumulate(sorted(map(int, input().split()), reverse=True)))
    for _ in range(q):
        sugar = int(input())
        pos = bisect_left(max_sugar_with_candies, sugar)
        print(pos+1 if pos < len(max_sugar_with_candies) else -1)
