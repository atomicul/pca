from itertools import accumulate
from bisect import bisect_right
t=int(input())
for _ in range(t):
    _ = input()
    step_difference = list(map(int, input().split()))
    levels = [0] + list(accumulate(step_difference))
    required_height = list(accumulate(step_difference, initial=0, func=max))


    for height in map(int, input().split()):
        print(levels[bisect_right(required_height, height)-1], end=' ')
    print()
        
