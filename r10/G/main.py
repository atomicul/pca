#!/bin/env python3
import enum
import sys
from typing import List, Tuple, Optional, Iterable


def main():
    lines = sys.stdin.readlines()

    board = Board(lines)

    print("White: ", end="")
    print(*board.notations(side=Side.WHITE), sep=",")

    print("Black: ", end="")
    print(*board.notations(side=Side.BLACK), sep=",")


class Side(enum.Enum):
    WHITE = 1
    BLACK = 2


class Piece:
    symbol: str
    side: Side

    def __init__(self, symbol: str):
        self.side = Side.WHITE if symbol.isupper() else Side.BLACK
        self.symbol = symbol.upper()

    def __str__(self):
        if self.side == Side.BLACK:
            return self.symbol.lower()
        return self.symbol


class Board:
    _BOARD_SIZE = 8
    board: List[List[Optional[Piece]]]

    def __init__(self, formatted: List[str]):
        meaningful_lines = (line for idx, line in enumerate(formatted) if idx % 2)
        trimmed_lines = (line.strip("|\n") for line in meaningful_lines)
        matrix = (line.split("|") for line in trimmed_lines)

        def filter_alpha(x: str):
            return "".join(char for char in x if char.isalpha())

        filtered = ((filter_alpha(square) for square in row) for row in matrix)

        self.board = [
            [Piece(piece_str) if piece_str else None for piece_str in row]
            for row in filtered
        ]

        if len(self.board) != self._BOARD_SIZE:
            raise ValueError
        if any(len(row) != self._BOARD_SIZE for row in self.board):
            raise ValueError

    def pieces_iterator(
        self, *, side: Optional[Side] = None
    ) -> Iterable[Tuple[str, Piece]]:
        def letter(x: int):
            if x not in range(0, 26):
                raise ValueError
            return chr(ord("a") + x)

        iter = enumerate(reversed(self.board), start=1)
        if side == Side.BLACK:
            iter = reversed(list(iter))
        for i, row in iter:
            for j, piece in (x for x in enumerate(row) if x[1] is not None):
                if side is None or piece.side == side:
                    yield (letter(j) + str(i), piece)

    def notations(self, *, side: Optional[Side]):
        def key(x: Tuple[str, Optional[Piece]]):
            if x[1] is None:
                return -2
            symbol = x[1].symbol
            order = "KQRBNP"
            try:
                return order.index(symbol)
            except ValueError:
                return -1

        ordering = sorted(self.pieces_iterator(side=side), key=key)

        return [
            (piece.symbol if piece.symbol != "P" else "") + position
            for position, piece in ordering
        ]


if __name__ == "__main__":
    main()
