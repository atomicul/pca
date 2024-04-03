#!/bin/env python3
from math import sqrt
from typing import List, Optional, Set, Iterator
from copy import copy


def main():
    t = int(input())
    for _ in range(t):
        n, r = map(int, input().split())
        points = [Point(*map(int, input().split())) for _ in range(n)]
        space = Rectangle(-10000, -10000, 20000, 20000)
        tree = QuadTree(space)

        for p in points:
            tree.add_point(p)


class Point:
    x: int
    y: int

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance(self, other: "Point"):
        return sqrt(abs(self.x - other.x) ** 2 + abs(self.y - other.y) ** 2)

    def __eq__(self, other):
        if not isinstance(other, Point):
            return False
        return self.x == other.x and self.y == other.y

    def __hash__(self) -> int:
        return hash((self.x, self.y))

    def __str__(self):
        return f"({self.x}, {self.y})"


class Rectangle:
    l: int
    r: int
    t: int
    b: int

    def __init__(self, x, y, w, h):
        self.l = x
        self.t = y
        self.r = x + w
        self.b = y + h

    @property
    def w(self):
        return self.r - self.l

    @property
    def h(self):
        return self.b - self.t

    @property
    def center(self) -> Point:
        return Point(self.l + self.w // 2, self.t + self.h // 2)

    def contains(self, p: Point):
        return p.x in range(self.l, self.r) and p.y in range(self.t, self.b)

    def __str__(self):
        return f"({self.l}, {self.t}, {self.r}, {self.b})"


class QuadTree:
    rect: Rectangle
    parent: Optional["QuadTree"]
    children: List["QuadTree"]
    point: Optional[Point]

    def __init__(self, rect: Rectangle):
        self.parent = None
        self.children = []
        self.rect = copy(rect)
        self.point = None

    @property
    def is_leaf(self):
        return len(self.children) == 0

    @property
    def is_root(self):
        return self.parent is None

    def add_point(self, p: Point, *, _force_new_region=False):
        if self.is_leaf and not _force_new_region:
            if self.point is None:
                self.point = copy(p)
            else:
                p1 = self.point
                self.point = None
                self.add_point(p1, _force_new_region=True)
                self.add_point(p)
            return

        subtree = next((x for x in self.children if x.rect.contains(p)), None)

        r = self.rect
        subtree = subtree or QuadTree(
            Rectangle(
                r.l if p.x < r.center.x else r.center.x,
                r.t if p.y < r.center.y else r.center.y,
                r.w // 2,
                r.h // 2,
            )
        )

        if subtree not in self.children:
            self.children.append(subtree)
            subtree.parent = self

        subtree.add_point(p)

    def points(self) -> Iterator[Point]:
        if self.point:
            yield self.point
        for child in self.children:
            yield from child.points()

    def closest_points(
        self,
        p: Point,
        *,
        _region: Optional["QuadTree"] = None,
        _found_points: Optional[Set[Point]] = None,
    ):
        if _found_points is None:
            _found_points = set()

        if _region is None:
            if self.point == p:
                _region = self
            else:
                for child in self.children:
                    yield from child.closest_points(p, _found_points=_found_points)

        if _region is None:
            return

        new_points = set(_region.points()) - _found_points
        yield from sorted(new_points, key=lambda x: p.distance(x))

        for p in new_points:
            _found_points.add(p)

        if not _region.is_root:
            yield from self.closest_points(
                p, _region=_region.parent, _found_points=_found_points
            )


if __name__ == "__main__":
    main()
