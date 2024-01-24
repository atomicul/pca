#!/bin/env python3
import sys

n, m = map(int, input().split())

if n == m:
    sys.exit(1)

if n > m:
    message = "Dr. Chaz needs {count} more piece{plural} of chicken!"
else:
    message = "Dr. Chaz will have {count} piece{plural} of chicken left over!"

message = message.format(
    count=abs(n-m),
    plural=('s' if abs(n-m) > 1 else '')
)

print(message)
