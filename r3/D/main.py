from itertools import repeat
def chessNotationToPair(s):
    return (ord(s[0])-ord('a'), int(s[1])-1)
rook = chessNotationToPair(input())
knight = chessNotationToPair(input())

knight_moves = [(2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (-1, 2), (1, -2), (-1, -2)]

unavailable_squares = set()
add_pairs = lambda x, y: (x[0]+y[0], x[1]+y[1])
for i in map(add_pairs, repeat(knight), knight_moves):
    unavailable_squares.add(i)

for i in map(add_pairs, repeat(rook), knight_moves):
    unavailable_squares.add(i)

unavailable_squares.add(knight)

for i in range(0, 8):
    unavailable_squares.add((i, rook[1]))
    unavailable_squares.add((rook[0], i))

unavailable_squares = {x for x in unavailable_squares if x[0] >= 0 and x[0] < 8 and x[1] >= 0 and x[1] < 8}
print(64-len(unavailable_squares))
