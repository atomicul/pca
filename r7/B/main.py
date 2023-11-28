x, y, z, t1, t2, t3 = map(int, input().split())

print(
    'YES' if t2*(abs(x-y) + abs(x-z)) + 3*t3 <= t1*abs(x-y) else 'NO'
)
