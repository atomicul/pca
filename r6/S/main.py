import sys
from math import floor, ceil

lines = [i.strip(' \n') for i in sys.stdin.readlines()]

maxWidth = max(len(i) for i in lines)

print('*' * (maxWidth + 2))

approximateLeft = True
for line in lines:
    pad = (maxWidth - len(line)) / 2

    left_round_fn, right_round_fn = ceil, floor
    if approximateLeft:
        left_round_fn, right_round_fn = right_round_fn, left_round_fn
    if pad != int(pad):
        approximateLeft = not approximateLeft

    print('*', end='')
    print(' ' * left_round_fn(pad), end='')
    print(line, end='')
    print(' ' * right_round_fn(pad), end='')
    print('*')

print('*' * (maxWidth + 2))
