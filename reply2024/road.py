from typing import List
from .board import Board
from .tile import Tile, Direction
from .point import Point

class Road:
    board: Board
    tiles: List[Tile]
    coming_from: Direction
    positions: List[Point]

    def __init__(self, board: Board, initial_tile: Tile, initial_position: Point, going_to: Direction):
        self.board = board
        self.tiles = [initial_tile]
        self.positions = [Point(0, 0)]
        assert going_to in initial_tile.directions
        self.coming_from = going_to.opposite

    def go_to_options(self):
        return set(tiles[-1].directions) - set([self.coming_from])

    def add_tile(self, tile: Tile, going_to: Direction):
        if going_to not in tile.directions:
            raise ValueError("Tile can't be placed in this direction (destination issue)")
        if going_to.opposite not in self.tiles[-1].directions:
            raise ValueError("Tile can't be placed in this direction (origin issue)")

        self.tiles.append(tile)
        self.coming_from = going_to.opposite
