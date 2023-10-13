t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    chessboard = []
    for _ in range(n):
        chessboard.append(list(map(int, input().split())))

    diagonals1, diagonals2 = ([], []), ([], [])


