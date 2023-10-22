from typing import Iterable

def count_iter(i: Iterable) -> int:
    return sum(1 for _ in i)

t=int(input())
for _ in range(t):
    input()
    a, b = input(), input()
    if len(a) == 1:
        print(1 if a != b else 0)
        continue
    diff1 = count_iter(p for p in zip(a,b) if p[0]!=p[1])
    if diff1 == 0:
        print(0)
        continue
    diff2 = count_iter(p for p in zip(a,reversed(b)) if p[0]!=p[1])
    if diff2 == 0:
        print(2)
        continue
    print(min(diff1*2-1, diff2*2))
