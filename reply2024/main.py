#!/bin/env/python3
from board import Board
from point import Point, SilverPoint, GoldPoint
import matplotlib.pyplot as plt
from typing import Iterator
from itertools import pairwise
import sys
from copy import deepcopy as clone

board = Board.from_input()

def xs(points: Iterator[Point]):
    return [x.x for x in points]

def ys(points: Iterator[Point]):
    return [y.y for y in points]

plt.scatter(xs(board.silver_points), ys(board.silver_points), color='blue')
plt.scatter(xs(board.gold_points), ys(board.gold_points), color='red')
for idx, point in enumerate(board.silver_points):
    plt.text(point.x, point.y, point.value, fontsize=9)
    plt.text(point.x, point.y + 1, hex(idx), fontsize=9)
plt.title('Plot of Points')
plt.grid(True)
plt.show()

with open('paths.txt', 'r') as f:
    path_a = f.readline().strip().split(',')
    path_a = [int(x, 16) for x in path_a]
    path_a = [board.silver_points[x] for x in path_a]
    path_b = f.readline().strip().split(',')
    path_b = [int(x, 16) for x in path_b]
    path_b = [board.silver_points[x] for x in path_b]

points_set = set()

def print_path(startPoint: Point, endPoint: Point):
    startPointCpy = clone(startPoint)
    for i in range(startPoint.x, endPoint.x + (-1 if endPoint.x < startPoint.x else 1), -1 if endPoint.x < startPoint.x else 1):
        points_set.add((i, startPoint.y))
    startPoint.x = endPoint.x
    for i in range(startPoint.y, endPoint.y + (-1 if endPoint.y < startPoint.y else 1), -1 if endPoint.y < startPoint.y else 1):
        points_set.add((startPoint.x, i))


r2, r1, r3 = board.gold_points
path_a = [r1] + path_a + [r2]
for p1, p2 in pairwise(path_a):
    print_path(p1, p2)

path_b = [r3] + path_b + [r1]
for p1, p2 in pairwise(path_b):
    print_path(p1, p2)

for x, y in points_set:
    print('F', x, y)
