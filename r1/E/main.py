from itertools import accumulate

def solve():
    _ = input()
    d = list(map(int, input().split()))
    
    a = list(accumulate(d))
    for i, el in list(enumerate(a))[:-1]:
        if el > d[i+1] and d[i+1] != 0:
            print(-1)
            return

    print(' '.join(map(str, a)))

t = int(input())
for _ in range(t):
    solve()
