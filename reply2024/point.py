class Point:
    x: int
    y: int

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __eq__(self, o: object) -> bool:
        return self.x == o.x and self.y == o.y

    def __str__(self) -> str:
        return f'({self.x}, {self.y})'

    def __repr__(self) -> str:
        return f'({self.x}, {self.y})'


class SilverPoint(Point):
    value: int

    def __init__(self, x: int, y: int, value: int):
        super().__init__(x, y)
        self.value = value

class GoldPoint(Point):
    def __init__(self, x: int, y: int):
        super().__init__(x, y)
