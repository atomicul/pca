#!/usr/bin/env python3
try:
    while True:
        x, y = map(int, input().split())
        print(abs(x-y))
except EOFError:
    pass
