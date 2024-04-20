#!/bin/env python3
from copy import deepcopy as copy
from typing import Iterator, List
from matplotlib import pyplot as plt
from itertools import pairwise
import sys

file = open(sys.argv[1], 'r')

def test_case(t):
    w, h = map(int, file.readline().split())
    rect = Rectangle(h, 0, w, 0)
    tree = Point()

    for y in range(h):
        for x, char in enumerate(file.readline()):
            if char == 'X':
                tree = Point(x, y)

    positions = [Point()]
    new_positions = []
    while True:
        plt.text(tree.x, tree.y, 'X')
        draw_path(rect, positions + new_positions)

        dir = input()
        if dir.upper() == "U":
            new_positions = []
            continue
        positions += new_positions
        new_positions = []

        if dir.upper().strip() == "DONE":
            break
                             

        continous = dir.isupper()
        dir = dir.upper()

        if not continous:
            new_pos = copy(positions[-1])
            new_pos.move(dir)
            new_positions = [new_pos]
            if not validate_path(rect, tree, positions + new_positions):
                new_positions = []
        else:
            while validate_path(rect, tree, positions + new_positions):
                new_pos = copy((positions + new_positions)[-1])
                new_pos.move(dir)
                new_positions.append(new_pos)
            new_positions = new_positions[:-1]

    for a,b in pairwise(positions):
        print(a.direction(b), end='')
    print()


class Point:
    x: int
    y: int

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def move(self, dir: str):
        if dir == 'W':
            self.y += 1
        elif dir == 'D':
            self.x += 1
        elif dir == 'S':
            self.y -= 1
        elif dir == 'A':
            self.x -= 1

    def direction(self, other):
        if self.x == other.x:
            if self.y < other.y:
                return 'W'
            else:
                return 'S'
        elif self.y == other.y:
            if self.x < other.x:
                return 'D'
            else:
                return 'A'
        return None

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self) -> int:
        return hash((self.x, self.y))

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"

    def __repr__(self) -> str:
        return f"Point{self}"

class Rectangle:
    t: int
    l: int
    r: int
    b: int

    def __init__(self, t=0, l=0, r=0, b=0):
        self.t = t
        self.l = l
        self.r = r
        self.b = b

    @property
    def width(self):
        return self.r - self.l + 1

    @property
    def height(self):
        return self.t - self.b + 1

    def contains(self, p: Point) -> bool:
        return self.l <= p.x < self.r and self.b <= p.y < self.t

    def all_points(self) -> Iterator[Point]:
        for y in range(self.b, self.t):
            for x in range(self.l, self.r):
                yield Point(x, y)

    def __str__(self) -> str:
        return f"({self.b}, {self.l}, {self.t}, {self.r})"

    def __repr__(self) -> str:
        return f"Rectangle{self}"
        

def get_positions(path) -> List[Point]:
    position = Point()

    positions = [copy(position)]
    for dir in path:
        position.move(dir)
        positions.append(copy(position))

    top_left = Point()

    for p in positions:
        top_left.x = min(top_left.x, p.x)
        top_left.y = max(top_left.y, p.y)

    positions = [Point(p.x - top_left.x, top_left.y - p.y) for p in positions]

    return positions
    

def draw_path(rect, positions):
    plt.xlim(rect.l - 1, rect.r + 1)
    plt.ylim(rect.b - 1, rect.t + 1)
    plt.plot([p.x for p in positions], [p.y for p in positions])
    plt.show(block=False)
    plt.pause(1)
    plt.close()
    plt.clf()


def validate_path(rect, tree, path):
    if any(not rect.contains(p) for p in path):
        return False

    if any(p == tree for p in path):
        return False

    if len(path) != len(set(path)):
        return False

    return True


if __name__ == '__main__':
    n = int(file.readline())
    for i in range(n):
        test_case(i)

