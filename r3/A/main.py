t = int(input())
for _ in range(t):
    _ = input()
    order = map(lambda x: x[0], \
                sorted( \
                        enumerate(map(int, input().split())), \
                        key=lambda x: x[1]))
    weather = sorted(map(int, input().split()))
    print(*(x[1] for x in sorted(zip(order, weather))))

