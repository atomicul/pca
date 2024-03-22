from point import Point, GoldPoint, SilverPoint
from tile import Tile
from typing import List


class Board:
    width: int
    height: int
    silver_points: List[SilverPoint]
    gold_points: List[GoldPoint]
    tiles: List[Tile]

    def __init__(self, width, height, silver_coins, gold_coins, tiles):
        self.width = width
        self.height = height
        self.silver_points = silver_coins
        self.gold_points = gold_coins
        self.tiles = tiles

    @staticmethod
    def from_input():
        w, h, g, s, t = map(int, input().split())

        golden_points = []
        for _ in range(g):
            x, y = map(int, input().split())
            golden_points.append(GoldPoint(x, y))

        silver_points = []
        for _ in range(s):
            x, y, value = map(int, input().split())
            silver_points.append(SilverPoint(x, y, value))

        tiles = []
        for _ in range(t):
            id, cost, count = input().split()
            cost, count = map(int, (cost, count))
            tiles.append(Tile(id, cost, count))

        return Board(w, h, silver_points, golden_points, tiles)
