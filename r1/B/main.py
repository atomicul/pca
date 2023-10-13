from functools import reduce
_, scores = (input(), list(map(int, input().split())))

if(len(scores) == 1):
    print(0)
elif(len(scores) == 2):
    print(1)
else:
    amazing_performances = \
        reduce(lambda acc, x: (x, acc[1]+1) if x > acc[0] else acc, scores, (0, 0))[1] +\
        reduce(lambda acc, x: (x, acc[1]+1) if x < acc[0] else acc, scores, (2**32, 0))[1]

    print(amazing_performances - 2)
