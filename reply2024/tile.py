from enum import Enum
from typing import List, Optional
from point import Point

class Direction(Enum):
    UP = 1
    DOWN = 2
    LEFT = 3
    RIGHT = 4

    @property
    def opposite(self):
        if self == Direction.UP:
            return Direction.DOWN
        if self == Direction.DOWN:
            return Direction.UP
        if self == Direction.LEFT:
            return Direction.RIGHT
        return Direction.LEFT

    @property
    def dx(self):
        if self == Direction.LEFT:
            return -1
        if self == Direction.RIGHT:
            return 1
        return 0

    @property
    def dy(self):
        if self == Direction.UP:
            return -1
        if self == Direction.DOWN:
            return 1
        return 1

class Tile:
    _placed_count: Point | int
    id: str
    directions: List[Direction]
    cost: int

    TYPES = {
        "3": [Direction.LEFT, Direction.RIGHT],
        "5": [Direction.DOWN, Direction.RIGHT],
        "6": [Direction.DOWN, Direction.LEFT],
        "7": [Direction.LEFT, Direction.DOWN, Direction.RIGHT],
        "9": [Direction.UP, Direction.RIGHT],
        "A": [Direction.UP, Direction.LEFT],
        "B": [Direction.UP, Direction.LEFT, Direction.RIGHT],
        "C": [Direction.UP, Direction.DOWN],
        "D": [Direction.UP, Direction.DOWN, Direction.RIGHT],
        "E": [Direction.UP, Direction.DOWN, Direction.LEFT],
        "F": [Direction.UP, Direction.DOWN, Direction.LEFT, Direction.RIGHT]
    }

    def __init__(self,  id: str, cost: int, count: int):
        self.directions = self.TYPES[id]
        self.id = id
        self.cost = cost
        self._placed_count = count

    @property
    def position(self):
        return self._placed_count if type(self._placed_count) is Point else None

    @position.setter
    def position(self, value: Point):
        self._placed_count = value

    @property
    def is_placed(self):
        return self.position is not None

    @property
    def count(self):
        return self._placed_count if type(self._placed_count) is int else 1

    @property
    def break_one(self):
        if self.count <= 1:
            raise ValueError("Can't break a tile with only one in the stack")
        assert type(self._placed_count) is int
        self._placed_count -= 1
        return Tile(self.id, self.cost, 1)

    def un_place(self):
        assert self.is_placed
        self._placed_count = 1

    def __str__(self):
        if self.is_placed:
            return f"{self.id} at {self.position} with a cost of {self.cost}"
        return f"{self.count} of {self.id} with a cost of {self.cost}"

    def __repr__(self):
        return f"Tile({self.__str__})"
