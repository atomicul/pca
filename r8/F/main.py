#!/bin/env python3

class Variable:
    def __init__(self, name, noOfBytes):
        self.name = name
        self.noOfBytes = noOfBytes
try:
    while True:
        n = int(input().split()[1]) 
        variables = []
        variables_map = {}

        # Read variables
        for _ in range(n):
            name, noOfBytes = input().split()
            noOfBytes = int(noOfBytes)
            variables.append(Variable(name, noOfBytes))
            variables_map[name] = variables[-1]

        # Read variables data
        for var in variables:
            bits = ""
            for _ in range(var.noOfBytes):
                bits += input()
            var.value = int(bits, 2)

        # Query variables
        n = int(input())
        for _ in range(n):
            name = input()
            print(name, variables_map[name].value if name in variables_map else '', sep='=')

except EOFError:
    pass
